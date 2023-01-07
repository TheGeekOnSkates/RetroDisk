# RetroDisk

RetroDisk is a C library for reading and writing disk files for the C64, VIC-20 and other Commodore psystems.  Without adding other code to main(), compiles to ~250 bytes (not great for an unexpanded VIC but darn good for all the others).  Commodore's 1541 disk drive was kinda crazy, with its own OS (and some REALLY cryptic commands to control it).  With this library, you don't need to know CBM DOS inside-out-and-backwards (I have a lot to learn myself) to be able to read and write to disk.
