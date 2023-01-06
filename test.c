#include <conio.h>
#include <string.h>
#include "RetroDisk.h"

int main() {
	char test[160];
	uint8_t result;
	strcpy(test, "okay, it's really getting late here, and I really like that song, but it's time to make like a pc and crash. :d");

	cputs("Testing OVERWRITING...\r\n");
	result = RD_Save(test, 160, "data,seq,w", 8);
	switch(result) {
		case 0:
			cputs("Bingo!");
			break;
		default:
			cputs("Ruh-roh!");
			break;
	}
	
	/*
	// OLD CODE - I this this was for reading
	int8_t result;
	char test[30];
	result = cbm_open(15,8,15,"test.seq,r");
	if (result != 0) {
		cprintf("Error opening: %d\r\n", result);
		return 0;
	}
	result = cbm_read(15, test, 30);
	if (result == -1) {
		cprintf("Error reading: %d\r\n", result);
		return 0;
	}
	else cprintf("Wrote %d bytes.\r\n", result);
	cbm_close(15);
	POKE(646,1);
	cprintf("%s\n", test);
	*/
	return 0;
}
