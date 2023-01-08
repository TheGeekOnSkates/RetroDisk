: notes s" micro notes.md" system ;

: readme s" micro README.md" system ;

: size s" wc --bytes ./test.prg" system ;

: build
	s" clear" system
	s" cl65 ./*.c -t c64 -o test.prg" system
	$? 0 = if
		.\" \x1b[1;32mBuild worked.\x1b[0m" cr
		." Once you have it on a D64 image, use the word RUN to test." cr
		s" rm ./*.o" system
		." File size (in bytes): " size
	else
		.\" \x1b[1;31mBuild failed.\x1b[0m" cr
	then
;

: run
	s" x64 ./test.d64" system
	s" clear" system
;

: go s" micro test.c" system build ;
