# This is the make file for the realmake program. This make file
# will include all options to build, compile, or uninstall the realmake
# utility. This make file should be included with each release of realmake
#
# License: This software is licensed under the GPL. You are
# free to make any modifications, updates, changes, and distribute
# this code provided you release all of the source code under the 
# GPL.
# 
# DISCLAIMER: THIS SOFTWARE IS PROVIDED AS IS WITH NO WARRANTIES OR
# ANY PROMISE TO MAINTAIN DATA INTEGRITY. BY USING THIS SOFTWARE, YOU
# ACKNOWLEDGE THAT YOU UNDERSTAND THE RISKS INVOLVED AND RELEASE ALL
# DEVELOPERS, OWNERS, AND ANYONE ASSOCIATION WITH THE DEVELOPMENT OF
# THIS SOFTWARE FROM ANY LIABILITY.

# First off, some good old flag arguments
CC=g++
CFLAGS=-c -Wall
BIN=bin
SRC=src
NAME=$(BIN)/realmake
OBJ=$(BIN)/main.o $(BIN)/realmake_base.o $(BIN)/misc.o $(BIN)/realmake_c.o \
$(BIN)/realmake_cpp.o $(BIN)/realmake_java.o

# Now, the actual compile magic

all: $(NAME)

$(NAME): $(BIN) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(BIN):
	mkdir $(BIN)

$(BIN)/main.o: $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(SRC)/main.cpp -o $(BIN)/main.o

$(BIN)/realmake_base.o: $(SRC)/realmake_base.cpp
	$(CC) $(CFLAGS) $(SRC)/realmake_base.cpp -o $(BIN)/realmake_base.o

$(BIN)/misc.o: $(SRC)/misc.cpp
	$(CC) $(CFLAGS) $(SRC)/misc.cpp -o $(BIN)/misc.o
	
$(BIN)/realmake_c.o: $(SRC)/realmake_c.cpp
	$(CC) $(CFLAGS) $(SRC)/realmake_c.cpp -o $(BIN)/realmake_c.o

$(BIN)/realmake_cpp.o: $(SRC)/realmake_cpp.cpp
	$(CC) $(CFLAGS) $(SRC)/realmake_cpp.cpp -o $(BIN)/realmake_cpp.o

$(BIN)/realmake_java.o: $(SRC)/realmake_java.cpp
	$(CC) $(CFLAGS) $(SRC)/realmake_java.cpp -o $(BIN)/realmake_java.o

# Use this to clean house

clean:
	rm -rf $(BIN)
