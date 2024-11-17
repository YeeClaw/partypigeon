#include "wing_protocol.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

