# Shared build rules. Each module directory sets TOP and includes this file.
#   make        build and run the testbench
#   make lint   strict lint of the RTL only
#   make wave   build and run, then open the waveform in GTKWave
VERILATOR ?= verilator
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
	gtkwave $(TOP).vcd &

clean:
	rm -rf $(OBJ) *.vcd
