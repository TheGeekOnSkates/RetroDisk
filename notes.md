# TO-DO's:

## Writing

* Try loading the program onto a cartridge; if it can save to disk without having to be ON the disk, NOW we're talking real power!  And fewer hoops to jump thru. :)
* If that works, try writing to a disk without inserting one to test the error condition - what happens if my write function fails?

## After that

* Research cbm_append, if there is such a thing - or maybe it's multiple calls to cbm_write?
* Since "@0:" works, does "S0:" for deleting?  If so, add a delete function!
* Once writing is done, it's on to READING!
* Once reading is done, crazy idea time: How about a word processor?!  Here's my idea for how that would work:
	- Cursor around anywhere on the screen, type what you want.
	- F7 opens a file
	- F8 saves a file
	- I have other ideas for F1-F6 (color modes, multiple pages, etc. but I'll have to cross that bridge when I come to it). :)

