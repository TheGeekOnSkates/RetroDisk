#ifndef _RETRODISK_H
#define _RETRODISK_H

#include <cbm.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

/**
 * Saves data to disk
 * @param[in] The data
 * @param[in] Size of the buffer, in bytes (chars)
 * @param[in] Name of the file to save as
 * @param[in] Disk drive number (usually 8)
 * @returns Zero if it works, or a an error code (errno) if not
 * @remarks It works!  HOWEVER...
  *		- I haven't tested appending yet
 *		- There's also a slight problem with the file open/save parameters:
 *			If you'll notice lines 52-53: there is no ",w" at the end.  So
 *			I may have to either make that a 5th parameter (which would be
 *			kinda silly IMO) or mod the string before passing to cbm_save.
 *		- I also haven't tested the error conditions, like what happens if
 *			something fails.  My use of errno comes from old research I did
 *			on cc65's docs.
 * Question: What if the compiled binary is a PRG in the cartridge port?
 * Can it still write to disk?  Another experiment worth doing
 */
static uint8_t RD_Save(uint8_t *buffer, uint16_t bufferSize, const char* fileName, uint8_t diskDriveNumber) {
	int8_t result;
	result = cbm_open(15, diskDriveNumber, 15, fileName);
	if (result != 0) return errno;
	result = cbm_write(15, (char *)buffer, bufferSize);
	if (result == -1) {
		cbm_close(15);
		return errno;
	}
	// No ",w" at the end of the file name
	result = cbm_save("@0:test,seq", diskDriveNumber, (char*)buffer, bufferSize);
	cbm_close(15);
	return result == -1 ? errno : 0;
}

#endif
