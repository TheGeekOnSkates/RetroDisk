# Resources

I finally got some good sites where I can further research CBM DOS:

1. https://www.wikiwand.com/en/Commodore_DOS
2. https://petlibrary.tripod.com/errmsg.htm

The first one is hands-down the most thorough, but the other one explains the funky error I was getting.



# TO-DO's:

* Write docs.  As far as I'm concerned, this initial build is DONE!!! :)
* Crazy idea time: How about a word processor?!  Here's my idea for how that would work:
	- Cursor around anywhere on the screen, type what you want.
	- F7 opens a file
	- F8 saves a file
	- I have other ideas for F1-F6 (color modes, multiple pages, etc. but I'll have to cross that bridge when I come to it). :)
This will also help me to iron out the kinks and research some other cool stuff that could make the library better (see below)


## Kinks

* Loading prg as cartridge file - for some reason VICE doesn't like that.  TheVIC20 is totally fine with it (and in fact I think it loads PRGs I create to cartridge by default).  So whatever VICE's problem is, I guess the solution will be going with TheVIC20 when the time comes to try again.
* If that works, try writing to a disk without inserting one to test the error condition - what happens if my write function fails?


## Other random (but potentially very important) notes

1. Apparently, there was once [a bug in the save-with-replace routine](https://en.wikipedia.org/wiki/Commodore_DOS#The_save-with-replace_bug).  This library uses it for convenience, because nowadays most everybody is on emulators or modern replicas like TheC64.  And even people with original hardware may have patched disk drives (one guy documented how to fix it, and Commodore eventually fixed it themselves).  I'm kind of on the fence about this issue... save-with-replace has always worked great for me on VICE and TheVIC20, so I don't see any harm in having it there.  On the other hand, having it first delete the old file and then re-create a new one seems like it would have more things that could go wrong, which is just as bad (no data, "scrambled" data, same difference).  But of course I can always change it later if I ever score a real 1541 and discover it has this bug.
2. If you look at [cbm.h](https://github.com/cc65/cc65/blob/master/include/cbm.h), you'll see that the cbm_* functions set "__oserror", not errno.  However,normally in C (and in fact in most languages), anything starting with __ is very much an internal thing, signaling programmers to not mess with it.  So I'm sticking with errno for now; I can always change it later if necessary.


## To be researched

* Appending - looks like there is no cbm_append, but maybe try multiple calls to cbm_write.  If that's the case, just document how to do it correctly.
* On a similar token, what about READING in chunks like that?   If multiple cbm_write calls works, can I try multiple cbm_read calls?
