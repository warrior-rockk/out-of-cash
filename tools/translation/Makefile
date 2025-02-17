SRC_DIR := ../../
SRCS	:= $(wildcard ${SRC_DIR}*.C)
OBJ_DIR := csv/
OBJS    := $(patsubst ${SRC_DIR}%.C, ${OBJ_DIR}%.csv, ${SRCS})
TR_DIR	:= c/
TRS 	:= $(patsubst ${OBJ_DIR}%.csv, ${TR_DIR}%.c, ${OBJS})

all: extract replace
extract: ${OBJS}
replace: ${TRS}

${OBJ_DIR}%.csv: ${SRC_DIR}%.C
	python3 extract.py -f $^ -o $@
	cp $^ ${TR_DIR}

${TR_DIR}%.c: ${OBJ_DIR}%.csv
	python3 replace.py -f $@ -d $^ 
	
.PHONY: clean info

clean:
	rm ${OBJS}
	rm ${TRS}

info:
	@echo ${OBJS}
	@echo ${TRS}