/**************************************************************************

(C) 2023 The Geek on Skates

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from
the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software in
a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not
be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

**************************************************************************/

#include <conio.h>
#include <string.h>
#include <peekpoke.h>
#include "RetroDisk.h"

int main() {
	// Declare variables
	char test[160];
	uint8_t error;
	size_t length;

	// Since we're on the C64, let's make the text white
	POKE(646, 1);
	
	// We'll start by creating a new file
	cputs("Testing WRITING...\r\n");
	strcpy(test, "This is the data that will be saved to disk.");
	length = strlen(test);
	error = RD_Save(test, length, (char*)"   test1data,seq  ", 8);
	if (error) {
		cputs("Failed to save:  ");
		cputc(error + '0');
		cputs("\r\n");
		return 0;
	}
	
	// Now, let's rename it to something else...
	cputs("File saved.  Renaming...\r\n");
	error = RD_Rename("   test2data=test1data", 8);
	if (error) {
		cputs("Failed to rename:  ");
		cputc(error + '0');
		cputs("\r\n");
		return 0;
	}

	// Clear the contents of our buffer, so we know that when we read,
	// the data in our buffer will actually be what was read.
	memset(test, 0, 160);

	// Now, let's read the contents of that file
	cputs("File renamed.  Reading...\r\n");
	error = RD_Load(test, length, (char*)"test2data,seq  ", 8);
	if (error) {
		cputs("Failed to read:  ");
		cputc(error + '0');
		cputs("\r\n");
		return 0;
	}

	// Print it (again, note the)
	cputs("File read.  Content: ");
	POKE(646, 7);
	cputs((const char*)test);
	POKE(646, 1);
	cputs("\r\n\n");
	
	// Now, let's delete the file - we don't really need it anymore
	cputs("Deleting...\r\n");
	error = RD_Delete("   test2data", 8);
	if (error) {
		cputs("Failed to read:  ");
		cputc(error + '0');
		cputs("\r\n");
		return 0;
	}
	cputs("Done.\r\n\n");
	return 0;
}
