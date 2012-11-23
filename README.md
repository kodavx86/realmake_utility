
		REALMAKE


I. Introduction

Welcome to the README file for the realmake utility. This file
contatins basic information on building the realmake utility.

Now, realmake is still in the early stages of development
so this README file is going to be pretty short. More stuff
may be added for later versions of realmake, so be sure to
check this file with each release for new updates.


II. Building realmake

First, here are the files that should have been included
with your distribution for Realmake:

	Makefile
	README.txt
	headers/
	realmake.1
	src/
	test/

To build the realmake utility, just execute this command:

	make -f Makefile

The realmake utility should be in a bin/ directory when
building is done (i.e. ./bin/realmake)

Here's a brief summary of the files:

	Makefile	-> makefile for building realmake utility
	README.txt	-> what you're reading right now
	headers/	-> header files for compiling realmake
	realmake.1	-> man page for realmake utility
	src/		-> source code for realmake utility
	test/		-> test suite for realmake utility


III. Testing realmake

If you want to check if realmake is working after building it,
here's how you can run the test suite (note: you'll need python
to use this test suite):

	cd test/
	python test_realmake.py rm_test.txt

If all tests are successful, you should see this message:

	all realmake tests passed!

If you don't see this message, please send a copy of the message
on a bug report to the realmake project at github.com/kodavx86/realmake_utility


IV. Updates

	version 2.1
		- updated information in realmake.1 man page
		- corrected directory information in README.md file
		- updated version number displayed with -h option to 2.1

	version 2.0:
                - support compilation of C++ and Java code
                - added new C++ and Java test cases

	version 1.0: 
		- support compilation of C code
		- implemented configuration flags
		- includes test suite


V. Authors

	Tyler Vodak (kodavx86@gmail.com)
