#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "wing_protocol.h"

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024 // Why are constants defined like this?

void main_loop() {
	int sockfd;
	struct sockaddr_in dest_addr;
	WingPacket packet;

	// Create raw socket -- How exciting!
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (sockfd < 0) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	// Prepare WING packet
	create_packet(&packet, 0, "Hello from WING packet!", sizeof("Hello from Wing packet!"));  

	// Setup destination address
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(8080);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Send the WING protocol packet
	int bytes_sent = send_raw_packet("127.0.0.1", "127.0.0.1", &packet, sockfd); 
	if (bytes_sent < 0) {
		perror("Packet send failed");
	} else {
		printf("Sent WING packet\n");
	}

	close(sockfd);
}

int main() {
	main_loop();
	return 0;
}

