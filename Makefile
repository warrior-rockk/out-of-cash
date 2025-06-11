#recursive search functions trought folders (don't use if resources are on root folder)
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

#detect SO
ifeq ($(OS),Windows_NT)
	OS := Windows_NT
	OS_INC_DIR := 'D:/Instalables/Proyectos/Programacion DOS/cross-compile/djgpp/include'
	OS_GCC	   := 'D:/Instalables/Proyectos/Programacion DOS/cross-compile/djgpp/bin/i586-pc-msdosdjgpp-gcc'	
	OS_LIB_DIR := ./
	OS_DOSBOX  := 'D:/Instalables/Proyectos/Old Days/bin/DOSBox/DosBox.exe'
else
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        OS := Linux
    endif
    ifeq ($(UNAME_S),Darwin)
        OS := Mac
		OS_INC_DIR := /Users/warrior/Downloads/allegro-xc/allegro-4.2.2-xc/include
		OS_GCC	   := /Users/warrior/Downloads/djgpp/bin/i586-pc-msdosdjgpp-gcc	
		OS_LIB_DIR := /Users/warrior/Downloads/allegro-xc/allegro-4.2.2-xc/lib/djgpp
		OS_DOSBOX  := /Applications/dosbox-x.app/Contents/MacOS/dosbox-x --fastbioslogo
    endif
endif

#project definition
APP  				:= OUTCASH.EXE
SRC_EXT				:= C
#project folders
SRC_DIR				:= ./
BUILD_DIR			:= ./build/
RESOURCES_DIR		:= ./
STATIC_DIR			:= ./static/
INCLUDES_DIR		:= ${OS_INC_DIR}
LIBS_DIR			:= ${OS_LIB_DIR}
DEBUG_BIN_DIR   	:= ${BUILD_DIR}debug/bin/
DEBUG_OBJS_DIR  	:= ${BUILD_DIR}debug/obj/
DEBUG_RES_DIR		:= ${DEBUG_BIN_DIR}/
RELEASE_BIN_DIR 	:= ${BUILD_DIR}release/bin/
RELEASE_OBJS_DIR  	:= ${BUILD_DIR}release/obj/
RELEASE_RES_DIR		:= ${RELEASE_BIN_DIR}/
#objects
SRCS  				:= $(wildcard ${SRC_DIR}*.${SRC_EXT})
RESOURCES			:= $(wildcard ${RESOURCES_DIR}*.DAT) $(wildcard ${RESOURCES_DIR}*.TXT)
DEBUG_OBJS 			:= $(patsubst ${SRC_DIR}%.${SRC_EXT}, ${DEBUG_OBJS_DIR}%.o, ${SRCS})
DEBUG_RESOURCES		:= ${patsubst ${RESOURCES_DIR}%, ${DEBUG_RES_DIR}%,${RESOURCES}}
RELEASE_OBJS 		:= $(patsubst ${SRC_DIR}%.${SRC_EXT}, ${RELEASE_OBJS_DIR}%.o, ${SRCS})
RELEASE_RESOURCES	:= ${patsubst ${RESOURCES_DIR}%, ${RELEASE_RES_DIR}%,${RESOURCES}}
#compiler/linker flags
CC					:= ${OS_GCC}
DEBUG_CFLAGS  		:= -g -fgnu89-inline -DDEBUGMODE -I ${INCLUDES_DIR}
RELEASE_CFLAGS 		:= -Wall -O3 -fgnu89-inline -I ${INCLUDES_DIR}
LDFLAGS 			:= -fgnu89-inline -L ${LIBS_DIR} -lalleg

#all targets
all: debug release

#main targets
debug: ${DEBUG_BIN_DIR}${APP} ${DEBUG_RESOURCES}
release: ${RELEASE_BIN_DIR}${APP} ${RELEASE_RESOURCES}

#binary target (debug)
${DEBUG_BIN_DIR}${APP}: ${DEBUG_OBJS} 
	mkdir -p ${DEBUG_BIN_DIR}	
	
	@echo "## Linking Debug ${APP}"
	${CC} $^ -o $@ ${DEBUG_CFLAGS} ${LDFLAGS}
	
	@echo "## Copy static files"
	cp -r ${STATIC_DIR}/*.* ${DEBUG_BIN_DIR}
	
#compile objects generating dependency files (debug)
${DEBUG_OBJS_DIR}%.o: ${SRC_DIR}%.${SRC_EXT}
	mkdir -p ${DEBUG_OBJS_DIR}	
	${CC} -x c -c -MD $< -o $@ ${DEBUG_CFLAGS}

#copy resources (debug)
${DEBUG_RES_DIR}%: ${RESOURCES_DIR}%
	mkdir -p  $(@D)
	cp $< $@

#binary target (release)
${RELEASE_BIN_DIR}${APP}: ${RELEASE_OBJS}
	mkdir -p ${RELEASE_BIN_DIR}

	@echo "## Linking Release ${APP}"
	${CC} $^ -o $@ ${RELEASE_CFLAGS} ${LDFLAGS}

	@echo "## Copy static files"
	cp -r ${STATIC_DIR}/*.* ${RELEASE_BIN_DIR}
	
#compile objects generating dependency files (release)
${RELEASE_OBJS_DIR}%.o: ${SRC_DIR}%.${SRC_EXT}
	mkdir -p ${RELEASE_OBJS_DIR}
	${CC} -x c -c -MD $< -o $@ ${RELEASE_CFLAGS}

#copy resources (release)
${RELEASE_RES_DIR}%: ${RESOURCES_DIR}%
	mkdir -p  $(@D)
	cp $< $@

#dependency includes
-include ${DEBUG_OBJS_DIR}*.d
-include ${RELEASE_OBJS_DIR}*.d

#run targets
run_debug: debug
	cd ${DEBUG_BIN_DIR} && ${OS_DOSBOX} ${APP} -conf dosbox.conf -exit -noconsole
run_release: release
	cd ${RELEASE_BIN_DIR} && ${OS_DOSBOX} ${APP} -conf dosbox.conf -exit -noconsole

.PHONY: clean info

clean:
	rm -rvf ${BUILD_DIR}

info:	
	@echo "Operating system:"
	@echo ${OS}
	@echo "Src objects:"
	@echo "${SRCS}"
	@echo "Resources:"
	@echo "${RESOURCES}"
	