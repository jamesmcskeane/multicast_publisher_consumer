BIN=bin
CONFIG=config

${BUILD}:
    ${MKDIR_P} ${BUILD}

INCLUDE_PATH=-I${CURDIR}/configManager/ \
             -I${CURDIR}/moduleRegister/ \
             -I${CURDIR}/multicast/


CC=g++
CFLAGS=-std=c++0x -g -Wall


all: program

program : main.o ConfigManager.o
	$(CC) $(CFLAGS) $(INCLUDE_PATH) ConfigManager.o main.o -o run

main.o: main.cpp
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) main.cpp

ConfigManager.o: configManager/ConfigManager.cc
	$(CC) -c $(CFLAGS) $(INCLUDE_PATH) configManager/ConfigManager.cpp


clean:
	rm -rf *o program
