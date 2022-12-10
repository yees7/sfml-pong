CXX := g++
CXX_FLAGS := -c

BIN := bin
SRC := src
BUILD := build

MAINFILE := $(SRC)/main.cpp

TARGET := $(BIN)/main

SOURCES := $(shell find $(SRC) -name *.cpp)
OBJECTS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SOURCES))))
DEPS := $(OBJECTS:.o=.d)

LDPATHS := $(addprefix -l, sfml-graphics sfml-window sfml-system)
# Tasks

run: build
	@echo -e "\nExecuting..."
	./$(TARGET) $(ARGS)

build: clean all

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo -e "\nBuilding..."
	mkdir -p $(dir $@)
	$(CXX) $(OBJECTS) -o $@ $(LDPATHS)

$(BUILD)/%.o: $(SRC)/%.cpp
	@echo -e "\nCompiling $<..."
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -o $@ $< $(LDPATHS)

.PHONY: clean
clean:
	@echo "Clearing..."
	rm -rf build

-include $(DEPS)