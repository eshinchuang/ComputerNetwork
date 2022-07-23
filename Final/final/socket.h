#include<iostream>
typedef uint16_t in_port_t;
//typedef unsigned int uint16_t;


typedef uint32_t in_addr_t;
//typedef unsigned long int uint32_t; 



struct in_addr{
	in_addr_t s_addr;
};

struct socksddr_in{
	uint8_t sin_len;
	//sa_family_t sin_family;
	in_port_t sin_port;
	struct in_addr sin_addr;
	char sin_zero[8];
};

