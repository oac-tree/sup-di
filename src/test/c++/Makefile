.PHONY: all

LIBVERSION=$(shell cat ../../main/VERSION)
LIBMAJOR=$(shell cat ../../main/VERSION | cut -d'.' -f1)
LIBMINOR=$(shell cat ../../main/VERSION | cut -d'.' -f2)
LIBMAINT=$(shell cat ../../main/VERSION | cut -d'.' -f3)

UNIT_TEST_EXE=unit-tests

TARGET=../../../target

BIN_DIR := $(TARGET)/bin
BUILD_DIR := ./build

UNIT_TEST := $(BUILD_DIR)/unit/$(UNIT_TEST_EXE)

BUILD_TYPE = RelWithDebInfo

CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DLIBVERSION=$(LIBVERSION) -DLIBSOVERSION=$(LIBMAJOR)
CMAKE_FLAGS += -DCMAKE_INSTALL_PREFIX=$(TARGET)

ifeq ($(COVERAGE),true)
CMAKE_FLAGS += -DCOVERAGE=true
else
CMAKE_FLAGS += -DCOVERAGE=false
endif

all: unit-tests

unit-tests: cmake-target
	@mkdir -p $(BIN_DIR)
	cp $(UNIT_TEST) $(BIN_DIR)/

cmake-target:
	@mkdir -p $(BUILD_DIR)
	cmake -B$(BUILD_DIR) $(CMAKE_FLAGS)
	$(MAKE) -C $(BUILD_DIR) install
