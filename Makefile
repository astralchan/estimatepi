include config.mk

OUT := estimatepi
MAN := ${OUT}.1
DOC := doc
SRC := src
BIN := bin

.PHONY: all build clean install uninstall

all: build

build:
	@echo "Building project..."
	mkdir -p ${BIN}
	${CC} ${CCFLAGS} -o ${BIN}/${OUT} ${SRC}/main.c
	@echo "Done"

clean:
	@echo "Cleaning source directory..."
	rm -rf ${BIN}
	@echo "Done"

install:
	@echo "Installing binary..."
	mkdir -p ${BINPREFIX}
	cp -p ${BIN}/${OUT} ${BINPREFIX}
	@echo "Done"
	@echo "Installing man page..."
	mkdir -p ${MANPREFIX}/man1
	cp -p ${DOC}/${MAN} ${MANPREFIX}/man1
	@echo "Done"

uninstall:
	@echo "Uninstalling binary..."
	rm -f ${BINPREFIX}/${OUT}
	@echo "Done"
	@echo "Uninstalling man page..."
	rm -f ${MANPREFIX}/man1/${MAN}
	@echo "Done"
