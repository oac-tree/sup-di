.PHONY: all

UNIT_TEST_EXE=unit-tests
PERFORMANCE_TEST_EXE=performance-tests

TARGET=../../../target

BIN_DIR := $(TARGET)/bin
BUILD_DIR := ./build

UNIT_TEST := $(BUILD_DIR)/unit/$(UNIT_TEST_EXE)
PERFORMANCE_TEST := $(BUILD_DIR)/performance/$(PERFORMANCE_TEST_EXE)

BUILD_TYPE = RelWithDebInfo

CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

ifeq ($(COVERAGE),true)
CMAKE_FLAGS += -DCOVERAGE=true
else
CMAKE_FLAGS += -DCOVERAGE=false
endif

all: unit-tests performance-tests

unit-tests: cmake-target
	@mkdir -p $(BIN_DIR)
	cp $(UNIT_TEST) $(BIN_DIR)/

performance-tests: cmake-target
	@mkdir -p $(BIN_DIR)
	cp $(PERFORMANCE_TEST) $(BIN_DIR)/

cmake-target:
	@mkdir -p $(BUILD_DIR)
	cmake -B$(BUILD_DIR) $(CMAKE_FLAGS)
	$(MAKE) -C $(BUILD_DIR)
