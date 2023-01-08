# RetroDisk

## Overview

RetroDisk is a C library for reading and writing disk files for the C64, VIC-20 and other Commodore psystems.  The standard C functions (fopen, fread, fwrite, fclose, fprintf etc.) don't work on these computers, because the disk drive they use requires some really unconventional (by today's standards) commands.  It was a separate computer entirely, and admittedly there's still a lot I don't know about how to use it.  But I don't think you should have to.  Not unless you want to realy go deep (which is awesome for those who do, but most of us don't).  So this library is for those of us who don't know the 1541 disk drive and disk OS ("CBM DOS") internals inside-out-and-backwards.  I went with the ZLib license (just cuz it's the same one cc65 uses - also, I can actually make sense of it and don't see any freedom-related gotchas).


## If you want to "go deep" (and I do recommend it)

If you want to learn how to do more than my little library can, cc65 has what I consider to be two levels of abstraction:

The top level, and the one my library uses, consists of the following functions:

* cbm_open
* cbm_read
* cbm_write
* cbm_close

If you are familiar with CBM DOS in BASIC, these are the the way to go.  They're the most straightforward and also the most similar to BASIC.  But they're not really documented anywhere except [on their GitHub](https://github.com/cc65/cc65/blob/master/include/cbm.h).  Eventually, I'd like to add functions that wrap these, because you can't really unlock the full potential of working with disks in cc65 without being able to make multiple read/write calls.  I'm still exploring a lot of this myself, so idk if I'm even right in saying that (like will multiple cbm_reads or cbm_writes do what I think they will?  lol... obviously on the to-do list). :)

Below that, you have the functions listed in [their function reference](https://cc65.github.io/doc/funcref.html#ss2.11), the cbm_k_* line of functions.  Some of these correspond with things I've seen in Assembly (like "setnam" to set the file name), but frankly you'll only ever need them if you're doing something really unusual.  I've read posts about people using them to talk to RS 232 serial ports and all kinds of crazy awesome stuff.  So if you want to talk to hardware directly, these are probably the functions you'll want.


## API reference

The whole library is contained in RetroDisk.h.  The functions it exports are:


### A word about "padding" mentioned in my docs

So, CBM DOS has certain expectations about how commands should be formatted.  If you've ever seen chaotic nonsense like `OPEN 15,8,15,"S0:MY-FILE":CLOSE 15` you know what I'm talking about.  But the whole point of a library like this is so you don't have to know all the gory details of junk like that.  You just read and write files.  So if you look at test.c, where I have working examples of all the functions in this library, you'll see what I mean.  Basically what it means is, you need to do "   myfile  " or "myfile  " etc. depending on what function you're using.


### A word about file names

They should all be made up of just letters (not sure if spaces are allowed), and then ahve a comma, and either "seq" or "prg".  Unless you're doing something really unusual, file names will almost always be things like "myfile,seq" (again, that's a comma, not a period).


### RD_Load

Reads a file into memory

#### Parameters

* buffer (`uin8_t *`): The data read will be stored here (can be text or binary)
* bufferSize (`uint16_t`) The size of the buffer, in bytes
* fileName (`char *`) The name of the file to read, padded with two spaces to the right
* diskDriveNumber (`uint8_t`) The disk drive number (will usually be 8, but can be any number you would use in BASIC - how many disk drives did they support at once? :D )

#### Return value

Zero if it works, or an error code (using standard C "errno") if it doesn't


## RD_Save

### RD_Load

Saves a block of memory to a file

#### Parameters

* buffer (`uin8_t *`): The data (can be text or binary)
* bufferSize (`uint16_t`) The size of the data, in bytes
* fileName (`char *`) The name of the file to read, padded with three spaces to the left, and two to the right
* diskDriveNumber (`uint8_t`) The disk drive number (will usually be 8, but can be any number you would use in BASIC - how many disk drives did they support at once? :D )

#### Return value

Zero if it works, or an error code (using standard C "errno") if it doesn't

#### Remarks

There is a bug on some versions of real Commodore 1541 floppy drives, known as the "save-with-replace bug".  The bug, though I haven't seen it, would supposedly "scramble" data on save.  This function is susceptible to that bug.  I figured, nowadays, most people use emulators, and even those with original hardware usually use those SD2IEC things.  And someone figured out how to patch it, and Commodore fixed it themselves on later-model disk drives... so to me it's just not that big an issue.  But it's absolutely worth mentioning because if you're using an older 1541 without that patch, this would be annoying.

However, the alternative (to me) is potentially even worse.  From what I've read, the recommended way to overwrite a file was to delete ("scratch") it first, and THEN save without the "@0:" (the command for "save, overwriting the old version").  But if a delete fails, then you're pretty much in the same situation - you lost your data.  So I'm okay with not working around the bug, since the alternative could actually affect more users.  But of course, if I'm way out in left field and this bug is super-common and super-annoying, of course I can add an RD_SaveNoRewrite() or something like that.


### RD_Rename

Renames a file

#### Parameters

* fileName (`char *`) A string padded with 3 spaces on the left and 2 on the right, withthe format "newname=oldname"
* diskDriveNumber (`uint8_t`) The disk drive number (will usually be 8, but can be any number you would use in BASIC - how many disk drives did they support at once? :D )

#### Return value

Zero if it works, or an error code (using standard C "errno") if it doesn't


### RD_Delete

Deletes a file

#### Parameters

* fileName (`char *`) The name of the file, padded with 3 bytes on the left
* diskDriveNumber (`uint8_t`) The disk drive number (will usually be 8, but can be any number you would use in BASIC - how many disk drives did they support at once? :D )

#### Return value

Zero if it works, or an error code (using standard C "errno") if it doesn't

