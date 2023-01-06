#include <conio.h>
#include <string.h>
#include "RetroDisk.h"

int main() {
	char test[160];
	uint8_t result;

	size_t i = 0;

	cputs("Testing READING...\r\n");
	result = RD_Load(test, 160, (char*)"   data,seq  ", 8);
	switch(result) {
		case 0:
			cputs("Before");
			// Could THIS be the line that's buggin out?
			//cputs((const char*) test);
			cputs("After");

			// Yup, that's exactly what it was!
			// How about I try something else...
			for(i = 7; i<160; i++) cputc(test[i]);
			// That gave a slightly different result:
			// It still spewed nonsensicalities about a syntax error,
			// but THEN it printed a bunch of "garbage" characters.
			// This has got to be the head-scratchinest project of all time.........
			// Hypotheses:
			//		a. The Commodore guys were drunk off their butts when they designed this epic can of Stoopid :D
			//		b. Something in the returned text tells BASIC "The user goofed", and so trying to print it shows a {{random{random{randomness}}}} * puck. :D
			//		c. The read failed, even though cc65 seems to suggest it didn't, and something deeeeeeeeeeeeeeeeeeep in the internals is upset. :P
			//		d. Some kind of pointer going out of scope, deep under the hood of cc65?  I mean that wouldn't make sense, but sense is not a word I usually associate with Commodore disk drives. :P
			//		e. The Flux Capacitor got fried, sending any semblance of logic down the toilet.
			// Next test: How about moving the start value of i up higher?
			// Well............ scratch-scratch-scratch..... time to call it a night.
			// If I move it up to 150, I don't get the wackadoodle error message,
			// but I still don't get my text.  Whatever's giving the VIC a belly-ache, depuzzling it is gonna be like cracking flippin' time travel! :P
			// After further playing with the numbers, I realize what's going on: Something in cbm_read, or one of the quiggadillion sub-sub-sub-subcomponents it accesses, is actually sticking that baloney in my string.
			// If I run the program as-is, I get something like "AX ERROR,00,00" followed by da'crap.  So, the first "31,SYNT" (the first 7 characters) are not printed.  That's how I know this is the problem.
			// So the question now becomes, what, by the Lion's mane, can I do about it?  I don't even understnad what's failing, much less why.
			// It's definitely something inside cbm_read, somewhere, somehow, somewhy... but only my Lord and the cc65 devs could ever understand it.  Or maybe the drunken lumberjack who slapped together the 1541! :D
			
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
