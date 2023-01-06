#ifndef _RETRODISK_H
#define _RETRODISK_H

#include <cbm.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

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
	static int8_t result, length;
	length = strlen(fileName);
	fileName[length - 2] = ',';
	fileName[length - 1] = 'w';
	result = cbm_open(15, diskDriveNumber, 15, fileName + 2);
	if (result != 0) return errno;
	result = cbm_write(15, (char *)buffer, bufferSize);
	if (result == -1) {
		cbm_close(15);
		return errno;
	}
	fileName[length - 2] = '\0';
	fileName[0] = '@';
	fileName[1] = '0';
	fileName[2] = ':';
	result = cbm_save(fileName, diskDriveNumber, (char*)buffer, bufferSize);
	cbm_close(15);
	return result == -1 ? errno : 0;
}

#endif
