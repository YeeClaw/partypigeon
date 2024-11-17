#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include "wing_protocol.h"

int main() {
    int sockfd;
    struct sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);
    WingPacket packet;

    // Create raw socket
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Buffer for incoming packets
    char buffer[1024];

    // Receive WING protocol packet
    ssize_t bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                      (struct sockaddr *)&src_addr, &addr_len);
    if (bytes_received < 0) {
        perror("Packet receive failed");
    } else {
		// Extract IP header and WingPacket from the received buffer
		struct iphdr* ip_header = (struct iphdr*)buffer;
		char* payload = buffer + (ip_header->ihl << 2); // Skip IP header

		// Copy the payload into WingPacket
		memcpy(&packet, payload, sizeof(packet));

		// Validate and process the WingPacket
		if (validate_packet(&packet)) {
			printf("Received valid message: %s\n", packet.payload);
		} else {
			printf("Invalid packet checksum\n");
		}
    }

    close(sockfd);
    return 0;
}
