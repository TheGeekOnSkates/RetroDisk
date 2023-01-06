# TO-DO's:

## Writing

* Fix the issues with the file name; kinda hard without using library functions, but then again, no harm in trying!  If I can use strlen, sprintf and malloc/free and my PRG size isn't insane (if it even compiles) on an unexpanded VIC, I'm golen.  If not... might have some harder work to do (maybe ask that users pass in i.e. "  test,seq  " so my code can safely add "@0" or ",w" without having to jump thru too many hoops)
* Try appending - can I go with ",a" instead of ",w"?  If not, how would that work?
* Also, try editing disk data from a cartridge; if it can save to disk without having to be ON the disk, NOW we're talking real power!  And fewer hoops tojump thru. :)
* If that works, try writing to a disk without inserting one to test the error condition - what happens if my write function fails?

## After that

* Once writing is done, it's on to READING!
* Once reading is done, crazy idea time: How about a word processor?!  Here's my idea for how that would work:
	- Cursor around anywhere on the screen, type what you want.
	- F7 opens a file
	- F8 saves a file
	- I have other ideas for F1-F6 (color modes, multiple pages, etc. but I'll have to cross that bridge when I come to it). :)

