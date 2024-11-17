#ifndef WING_PROTOCOL_H
#define WING_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint8_t packet_type;
	uint16_t length;
	uint16_t checksum;
	char payload[256];
} WingPacket;

uint16_t calculate_checksum(const char* data, size_t lenght);
void create_packet(WingPacket *packet, uint8_t type, const char* data, size_t length);
int validate_packet(const WingPacket* packet);

#endif

