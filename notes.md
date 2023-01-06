# TO-DO's:

* Get reading working

	Currently giving me "31:syntax error:00:00"



* Once reading is done, crazy idea time: How about a word processor?!  Here's my idea for how that would work:
	- Cursor around anywhere on the screen, type what you want.
	- F7 opens a file
	- F8 saves a file
	- I have other ideas for F1-F6 (color modes, multiple pages, etc. but I'll have to cross that bridge when I come to it). :)
This will also help me to iron out the many kinks (see below)


## Kinks

* Appending - looks like there is no cbm_append, but maybe try multiple calls to cbm_write.  If that's the case, just document how to do it correctly.
* On a similar token, what about READING in chunks like that?   Like fread, I mean.  cbm_read?
* Deleting - Doesn't look like it's gonna work... or there is yet another misdocumented hack I don't know about (seriously, all their docs say cbm_k_this and cbm_k_that, but I discovered how to REALLY do I/O from cbm.h itself).
* Loading prg as cartridge file - for some reason VICE doesn't like that.  TheVIC20 is totally fine with it (and in fact I think it loads PRGs I create to cartridge by default).  So whatever VICE's problem is, I guess the solution will be going with TheVIC20 when the time comes to try again.
* If that works, try writing to a disk without inserting one to test the error condition - what happens if my write function fails?
