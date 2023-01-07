#ifndef _RETRODISK_H
#define _RETRODISK_H

#include <cbm.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

static uint8_t RD_Load(uint8_t *buffer, uint16_t bufferSize, char* fileName, uint8_t diskDriveNumber) {
	// Declare variables
	static int8_t result, length;
	
	// Open the file for reading
	length = strlen(fileName);
	fileName[length - 2] = ',';
	fileName[length - 1] = 'r';
	result = cbm_open(2, diskDriveNumber, 2, fileName);
	if (result != 0) return errno;

	// Read the file
	// Read the file - here's where it's snaffooing.
	// How is this a "31;SYNTAX ERROR;00:00"?  What the puck does that mean?
	// The code compiles and runs fine... what's syntactically wrong here?
	// Those cc65 guys rock at building compilers/assemblers, but OMGosh
	// do they ever suuuuuck puuuuucks at writing DOCS!!! :P
	// Or could it be some kind of 1982 NULL pointer shenanigans going on under the hood? :P
	result = cbm_read(2, buffer, bufferSize);
	cbm_close(2);
	return result == -1 ? errno : 0;
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
	result = cbm_open(15, diskDriveNumber, 15, fileName + 3);	// Was + 2, double check on that (cuz "@0:")
	if (result != 0) return errno;

	// Write the data
	result = cbm_write(15, (char *)buffer, bufferSize);
	if (result == -1) {
		cbm_close(15);
		return errno;
	}

	// Edit the string so the disk drive understands what we want
	fileName[length - 2] = '\0';
	fileName[0] = '@';
	fileName[1] = '0';
	fileName[2] = ':';

	// Save, close and we're done
	result = cbm_save(fileName, diskDriveNumber, (char*)buffer, bufferSize);
	cbm_close(15);
	return result == -1 ? errno : 0;
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
	if (result != 0) return errno;
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
	if (result != 0) return errno;
	cbm_close(15);
	return 0;
}

#endif
