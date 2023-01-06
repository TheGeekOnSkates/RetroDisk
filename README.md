# RetroDisk

The idea is simple: an easy-to-use API for loading/saving data on retro systems.
Actually getting there... well, that's anything but simple. :D

## My goal for version 1.0

The initial release will focus on 8-bit Commodore computers.  On the C64 (and VIC-20, and PET, and probably C128 and Plus/4), working with files is pretty straightforward:

```
LOAD "FILE", 8
SAVE "FILE", 8

REM DELETING AND OVERWRITING GOT A LITTLE TRICKER, BUT NOT IMPOSSIBLE

REM TO OVERWRITE AN EXISTING FILE
SAVE "@0:FILE", 8

REM TO DELETE (HARDEST)
OPEN 15,8,15,"S0:FILE":CLOSE 15
```

So what I'd like to do is wrap the cc65 built-in functions (or Assembly if necessary) so we use something like:

```
// "rd_" is for RetroDisk;
// namespacing is usually a smart move for libraries. :)

void rd_load(
	uint8_t* buffer,
	uint16_t bufferSize,
	const char* file_name,
	uint8_t diskDrive
);	// The buffer will contain the data that was read

void rd_save(
	uint8_t* buffer,
	uint16_t bufferSize,
	const char* file_name,
	uint8_t diskDrive
);	// Automatically overwrites if file exists

void rd_delete(
	const char* file_name,
	uint8_t diskDrive
);
```

Getting there may require some much-more-loew-level calls, to cbm.h or dio.h or who knows what else... but where there's a will there's a way! :)
