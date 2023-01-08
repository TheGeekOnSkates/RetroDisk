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

#ifndef _RETRODISK_H
#define _RETRODISK_H

#include <cbm.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

extern unsigned char _oserror;

/**
 * Reads a file into memory
 @ param[out] The data read will be stored here (can be text or binary)
 * @param[in] The size of the buffer, in bytes
 * @param[in] The name of the file to read, padded with two spaces to the right
 * @param[in] The disk drive number (will usually be 8, but can be any number you would use in BASIC - how many disk drives did they support at once? :D )
 * @returns Zero if it works, or an error code (using standard C "errno") if it doesn't
 */
static uint8_t RD_Load(uint8_t *buffer, uint16_t bufferSize, char* fileName, uint8_t diskDriveNumber) {
	// Declare variables
	static int8_t result, length;
	
	// Open the file for reading
	length = strlen(fileName);
	fileName[length - 2] = ',';
	fileName[length - 1] = 'r';
	result = cbm_open(2, diskDriveNumber, 2, fileName);
	if (result != 0) return _osmaperrno(_oserror);

	// The first 2 bytes are something internal, probably
	// a file delimiter or the size of the file or something.
	// We'll just skip those.
	result = cbm_read(2, buffer, 2);

	// Read the file
	result = cbm_read(2, buffer, bufferSize);
	cbm_close(2);
	return result == -1 ? _osmaperrno(_oserror) : 0;
}

/**
 * Saves data to disk
 * @param[in] The data (can be a string or binary)
 * @param[in] Size of the buffer, in bytes (chars)
 * @param[in] Name of the file to save as.  The format for this needs to be:
 *		- three bytes for the left pad (more on that later)
 *		- the file name
 *		- a comma
 *		- either "prg" or "seq" (are there other types?)
 *		- two bytes for the right pad
 *	The "padding" on the left and right is used to set certain "flags" that
 *	tell the disk drive what to do.  You can spare 5 bytes, right? :)
 *	An example of the format would be "   my-file,seq  "
 * @param[in] Disk drive number (usually 8)
 * @returns Zero if it works, or a an error code (errno) if not
 * @remarks It works!  HOWEVER...
 *		- APPENDING to files is not possible - at least, now how I've coded
 *			it here.  Might be another way (is there a cbm_append?)
 *		- I also haven't tested the error conditions, like what happens if
 *			something fails.  My use of errno comes from old research I did
 *			on cc65's docs.
 * Question: What if the compiled binary is a PRG in the cartridge port?
 * Can it still write to disk?  Another experiment worth doing
 */
static uint8_t RD_Save(uint8_t *buffer, uint16_t bufferSize, char* fileName, uint8_t diskDriveNumber) {
	// Declare variables
	static int8_t result, length;

	// Open the file for writing
	length = strlen(fileName);
	fileName[length - 2] = ',';
	fileName[length - 1] = 'w';
	result = cbm_open(15, diskDriveNumber, 15, fileName + 3);	// Was + 2, double check on that (because "@0:")
	if (result != 0) return _osmaperrno(_oserror);

	// Write the data
	result = cbm_write(15, (char *)buffer, bufferSize);
	if (result == -1) {
		cbm_close(15);
		return _osmaperrno(_oserror);
	}

	// Edit the string so the disk drive understands what we want
	fileName[length - 2] = '\0';
	fileName[0] = '@';
	fileName[1] = '0';
	fileName[2] = ':';

	// Save, close and we're done
	result = cbm_save(fileName, diskDriveNumber, (char*)buffer, bufferSize);
	cbm_close(15);
	return result == -1 ? _osmaperrno(_oserror) : 0;
}

static uint8_t RD_Rename(char* fileName, uint8_t diskDriveNumber) {
	// Declare variables
	static int8_t result;

	// Replace the pad with "R0:" - keep in mind the character sets
	fileName[0] = 'r';
	fileName[1] = '0';
	fileName[2] = ':';
	
	// Open the file for deleting
	result = cbm_open(15, diskDriveNumber, 15, fileName);
	if (result != 0) return _osmaperrno(_oserror);
	cbm_close(15);
	return 0;
}

static uint8_t RD_Delete(char* fileName, uint8_t diskDriveNumber) {
	// Declare variables
	static int8_t result;

	// Replace the pad with "S0:" - keep in mind the character sets
	fileName[0] = 's';
	fileName[1] = '0';
	fileName[2] = ':';
	
	// Open the file for deleting
	result = cbm_open(15, diskDriveNumber, 15, fileName);
	if (result != 0) return _osmaperrno(_oserror);
	cbm_close(15);
	return 0;
}

#endif
