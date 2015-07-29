# This Makefile requires GNU make.

# Query the shell to compile the code correctly for different architectures.
OSTYPE = $(shell uname)

ifeq ($(OSTYPE),CYGWIN_NT-5.1)
OS = -D_CYGWIN_
endif

ifeq ($(OSTYPE),Linux)
OS = -D_LINUX_
DEBUG = -g
#NUMA = -DNUMA_SUPPORT
CFLAGS = $(DEBUG) -Wall -O3 $(OS) $(NUMA) -DMMAP_POPULATE -fstrict-aliasing -Wstrict-aliasing 
LIBS = -lpthread -lrt
endif

ifeq ($(OSTYPE),SunOS)
OS =  -D_SOLARIS_
DEBUG = -g
#NUMA = -DNUMA_SUPPORT
CFLAGS = $(DEBUG) -Wall -O3 $(OS) $(NUMA) -D_FILE_OFFSET_BITS=64 
LIBS = -lm -lrt -lthread -lmtmalloc -llgrp
endif

ifeq ($(OSTYPE),Darwin)
OS = -D_DARWIN_
DEBUG = -g
CFLAGS = $(DEBUG) -Wall -O3 $(OS)
LIBS = -lpthread
endif

ARCHTYPE = $(shell uname -p)

ifeq ($(ARCHTYPE),sparc)
ARCH = -DCPU_V9
endif

ifeq ($(shell uname -m),x86_64)
ARCH = -D__x86_64__
endif

CFLAGS += $(ARCH)

# The $(OS) flag is included here to define the OS-specific constant so that
# only the appropriate portions of the application get compiled. See the README
# file for more information.
AR = ar
RANLIB = ranlib
LDFLAGS =

PHOENIX = phoenix
LIB_PHOENIX = lib$(PHOENIX)

LINKAGE = static
ifeq ($(LINKAGE),static)
TARGET = $(LIB_PHOENIX).a
LIB_DEP = $(HOME)/$(LIB_DIR)/$(TARGET)
endif

ifeq ($(LINKAGE),dynamic)
TARGET = $(LIB_PHOENIX).so
LIB_DEP =
endif

SRC_DIR = src
LIB_DIR = lib
INC_DIR = include
TESTS_DIR = tests
