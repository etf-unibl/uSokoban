APP_NAME=uSokoban
TARGET_MCU=ATMEGA32

TOOLCHAIN_DIR=C:\mikroC
COMPILER=mikroCAvr
CC=$(TOOLCHAIN_DIR)\$(COMPILER)
CFLAGS=-MSF -DBG -p$(TARGET_MCU) -DL -SSA -O11111114 -fo8 -BOOTSZ2048 -BOOTOP0

SRC_DIR_CYGWIN=$(shell pwd)
SRC_DIR=$(shell cygpath -w $(SRC_DIR_CYGWIN))
INCLUDE_DIR="$(SRC_DIR)\..\includes\"

MODULES=cntrl\ display\ engine\ glcd\ vga\ map\

MODULES_SEARCH_PATHS=$(foreach module,$(MODULES), -SP"$(SRC_DIR)\$(module)")

MODULES_SEARCH_PATHS+= -SP"$(SRC_DIR)\"

SEARCH_PATHS= \
 -SP"$(TOOLCHAIN_DIR)\Defs\" \
 -SP"$(TOOLCHAIN_DIR)\Uses\lte64kw\" \
 -SP"$(TOOLCHAIN_DIR)\Examples\Development systems\EasyAVR7\Glcd" \
 $(MODULES_SEARCH_PATHS)

SRCS_TMP=$(subst \ ,.c ,$(MODULES))
SRCS=$(foreach src,$(SRCS_TMP), "$(src)")
SRCS+="main.c"

LIBS= \
"__Lib_Math.mcl" \
"__Lib_MathDouble.mcl" \
"__Lib_System.mcl" \
"__Lib_Delays.mcl" \
"__Lib_ADC_ref3.mcl" \
"__Lib_GlcdFonts.mcl" \
"__Lib_Glcd.mcl" \
"__Lib_TouchPanel.mcl"  

BINARY_OUTPUT="..\bin\$(APP_NAME)"

all:
	-mkdir -p $(BINARY_OUTPUT)
	${CC} ${CFLAGS} -N${BINARY_OUTPUT} -IP${INCLUDE_DIR} ${SEARCH_PATHS} ${SRCS} ${LIBS}