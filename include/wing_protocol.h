#ifndef WING_PROTOCOL_H

#define WING_PROTOCOL_H
#define WING_PROTOCOL_ID 204 // I like this number! Court room I got married in.

#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint16_t protocol_id; 
	uint8_t packet_type;
	uint16_t length;
	uint16_t checksum;
	char payload[512];
} WingPacket;

uint16_t calculate_checksum(const char* data, size_t lenght);
void create_packet(WingPacket *packet, uint8_t type, const char* data, size_t length);
int validate_packet(const WingPacket* packet);
char* process_message(const char* input);
int send_raw_packet(const char* source_ip, const char* dest_ip, WingPacket* wing_pkt, int socketfd);

#endif

