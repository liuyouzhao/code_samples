# Prefix platform
PLATFORM=x86
BUILD=build

# Makefile main logic
ROOT=$(shell pwd)
PRE_ROOT=$(ROOT)
CC    =gcc
AS    =as
LD    =gcc
OC    =cp
LDIR  =
LDIR2 =

OUT_DIR = ./out/$(PLATFORM)
OUT_BIN = output
BOARD       =
CPU         =

C_CFLAGS += -I./ -Os
AFLAGS=
CFLAGS= $(C_CFLAGS)

LDFLAGS = -lc -lm 
