#include "wing_protocol.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

// This checksum method doesn't work super well. It should be made more robust in the future.
uint16_t calculate_checksum(const char* data, size_t length) {
	uint16_t checksum = 0;
	for (size_t i = 0; i < length; i++) {
		checksum += data[i];
	}
	return checksum;
}

void create_packet(WingPacket* packet, uint8_t type, const char* data, size_t length) {
	packet->packet_type = type;
	packet->length = length;
	memcpy(packet->payload, data, length);
	packet->checksum = calculate_checksum(data, length);
}

int validate_packet(const WingPacket* packet) {
	return packet->checksum == calculate_checksum(packet->payload, packet->length);
}

char* process_message(const char* input) {
	char* response = malloc(strlen(input) + 16);
	snprintf(response, strlen(input) + 16, "ACK: %s", input);
	return response;
}

void encode_wing_packet(WingPacket* packet, const char* message) {
	packet->protocol_id = WING_PROTOCOL_ID;
	packet->length = strlen(message);
	strcpy((char*)packet->payload, message);
}

void decode_wing_packet(const WingPacket* packet, char* message_buffer, size_t buffer_size) {
	strncpy(message_buffer, (char*)packet->payload, buffer_size - 1);
	message_buffer[buffer_size - 1] = '\0';
}

// Stuff because raw packets are cool!
void create_ip_header(
		struct iphdr* ip_header, 
		const char* source_ip, 
		const char* dest_ip,
		size_t packet_length
		) {
	ip_header->ihl = 5; // Internet header length
	ip_header->version = 4; // IPv4
	ip_header->tos = 0;
	ip_header->tot_len = packet_length; // Total packet length
	ip_header->id = htonl(54321); // Random ID
	ip_header->frag_off = 0; // Frament offset
	ip_header->ttl = 255; // Time to live
	ip_header->protocol = IPPROTO_RAW; // Protocol type
	ip_header->check = 0; // check sum -- this will be updated later
	ip_header->saddr = inet_addr(source_ip); // Source address
	ip_header->daddr = inet_addr(dest_ip); // Destination address
}

int send_raw_packet(const char* source_ip, const char* dest_ip, WingPacket* wing_pkt, int socketfd) {
	//Maybe add some logic here to make sure that the socket is good?
	//This includes checks on AF_INET (Ipv4), SOCK_RAW, and IPPROTO_RAW
	
	// Create IP header for the raw socket
	size_t packet_length = sizeof(struct iphdr) + sizeof(WingPacket);
	struct iphdr ip_header;
	create_ip_header(&ip_header, source_ip, dest_ip, packet_length);

	// Create buffer to hold both IP header and WingPacket
	char packet[packet_length];
	memcpy(packet, &ip_header, sizeof(ip_header)); // Copy IP header.
	memcpy(packet + sizeof(ip_header), wing_pkt, sizeof(WingPacket)); // Copy actual WingPacket
	
	// Calculate checksum for the IP header
	ip_header.check = calculate_checksum((char*)&ip_header, sizeof(ip_header));

	// Send the complete packet (IP header + WingPacket)
	ssize_t bytes_sent = sendto(socketfd, packet, packet_length, 0, NULL, 0);
	if (bytes_sent < 0) {
		perror("Packet send failed");
		return -1;
	}

	printf("Sent raw IP packet with WING payload!\n");
	return 0;
}

