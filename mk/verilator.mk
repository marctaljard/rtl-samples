# Shared build rules. Each module directory sets TOP and includes this file.
#   make        build and run the testbench
#   make lint   strict lint of the RTL only
#   make wave   build and run, then open the waveform (WAVE_VIEWER=... to override)
VERILATOR ?= verilator
# The GTKWave cask is x86-only, unsigned and discontinued, so macOS uses Surfer.
ifeq ($(shell uname -s),Darwin)
WAVE_VIEWER ?= surfer
else
WAVE_VIEWER ?= gtkwave
endif
RTL  := $(wildcard rtl/*.sv)
TB   := $(wildcard tb/*.cpp)
OBJ  := obj_dir

.PHONY: all test lint wave clean
all: test

$(OBJ)/V$(TOP): $(RTL) $(TB)
	$(VERILATOR) --cc --exe --build -j 0 -Wall --trace --top-module $(TOP) \
	  -CFLAGS "-std=c++17 -O1" -Mdir $(OBJ) $(RTL) $(TB)

test: $(OBJ)/V$(TOP)
	./$(OBJ)/V$(TOP)

lint:
	$(VERILATOR) --lint-only -Wall --top-module $(TOP) $(RTL)

wave: test
	$(WAVE_VIEWER) $(TOP).vcd &

clean:
	rm -rf $(OBJ) *.vcd
