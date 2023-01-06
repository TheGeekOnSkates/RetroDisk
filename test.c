#include <conio.h>
#include <string.h>
#include "RetroDisk.h"

int main() {
	char test[160];
	uint8_t result;

	cputs("Testing READING...\r\n");
	result = RD_Load(test, 160, (char*)"   data,seq  ", 8);
	switch(result) {
		case 0:
			cputs((const char*) test);
			cputs("It worked... I think");
			break;
		default:
			cputs("Ruh-roh!");
			break;
	}

	/*
	cputs("Testing my padding idea...\r\n");
	result = RD_Save(test, 160, (char*)"   data,seq  ", 8);
	switch(result) {
		case 0:
			cputs("Bingo!");
			break;
		default:
			cputs("Ruh-roh!");
			break;
	}
	*/
	return 0;
}
