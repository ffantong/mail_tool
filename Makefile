#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = -lws2_32 -lssl -lcrypto -lwsock32 -lgdi32 -static

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/mail

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/mail

OBJ_DEBUG = $(OBJDIR_DEBUG)/file_utils.o $(OBJDIR_DEBUG)/main.o $(OBJDIR_DEBUG)/map.o $(OBJDIR_DEBUG)/smtp.o $(OBJDIR_DEBUG)/sock.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/file_utils.o $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/map.o $(OBJDIR_RELEASE)/smtp.o $(OBJDIR_RELEASE)/sock.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/file_utils.o: file_utils.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c file_utils.c -o $(OBJDIR_DEBUG)/file_utils.o

$(OBJDIR_DEBUG)/main.o: main.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.c -o $(OBJDIR_DEBUG)/main.o

$(OBJDIR_DEBUG)/map.o: map.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c map.c -o $(OBJDIR_DEBUG)/map.o

$(OBJDIR_DEBUG)/smtp.o: smtp.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c smtp.c -o $(OBJDIR_DEBUG)/smtp.o

$(OBJDIR_DEBUG)/sock.o: sock.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c sock.c -o $(OBJDIR_DEBUG)/sock.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/file_utils.o: file_utils.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c file_utils.c -o $(OBJDIR_RELEASE)/file_utils.o

$(OBJDIR_RELEASE)/main.o: main.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.c -o $(OBJDIR_RELEASE)/main.o

$(OBJDIR_RELEASE)/map.o: map.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c map.c -o $(OBJDIR_RELEASE)/map.o

$(OBJDIR_RELEASE)/smtp.o: smtp.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c smtp.c -o $(OBJDIR_RELEASE)/smtp.o

$(OBJDIR_RELEASE)/sock.o: sock.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c sock.c -o $(OBJDIR_RELEASE)/sock.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release
