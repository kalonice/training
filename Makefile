.ONESHELL:
SHELL=/bin/bash

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    PROCESSORS = $(shell nproc)
endif
ifeq ($(UNAME), Darwin)
    PROCESSORS = $(shell sysctl -n hw.ncpu)
endif

BUILD_DIR	:= ./build
RM			:= rm -rf

EXECUTABLE_NAME := "training"
TEST_EXECUTABLE_NAME := ${EXECUTABLE_NAME}-ut

.PHONY: all clean

all: ut

deps:
	set -e
	if [ ! -d "$(BUILD_DIR)" ]; then mkdir $(BUILD_DIR); fi
	cd $(BUILD_DIR)

ut: deps
	set -e
	cd $(BUILD_DIR) && cmake ../ -DBUILD_TESTS=ON && make -j ${PROCESSORS} ${TEST_EXECUTABLE_NAME}
	$(BUILD_DIR)/bin/${TEST_EXECUTABLE_NAME}

app: deps
	set -e
	cd $(BUILD_DIR) && cmake ../ -DBUILD_TESTS=OFF && make -j ${PROCESSORS} ${EXECUTABLE_NAME}

install: app
	set -e
	cd $(BUILD_DIR) && cmake ../ -DBUILD_TESTS=OFF && make install

clean:
	$(RM) $(BUILD_DIR)

cpplint:
	set -e
	python ./3rdparty/cpplint.py --filter=-legal/copyright,-runtime/threadsafe_fn,-build/include,-readability/utf8 --linelength=100 \
    $(shell find ./src ./include ./test -name \*.hpp -print -o -name \*.h -print -o -name \*.cpp -print -o -name \*.c -print | sed -e ':a;N;$!ba;s/\n/ /g')
