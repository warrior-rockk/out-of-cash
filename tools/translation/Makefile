SRC_DIR := ../../
SRCS	:= $(wildcard ${SRC_DIR}*.C)
OBJ_DIR := csv/
OBJS    := $(patsubst ${SRC_DIR}%.C, ${OBJ_DIR}%.csv, ${SRCS})

extract: ${OBJS}

${OBJ_DIR}%.csv: ${SRC_DIR}%.C
	python3 extract.py -f $^ -o $@ 

.PHONY: clean info

clean:
	rm ${OBJS}

info:
	@echo ${OBJS}