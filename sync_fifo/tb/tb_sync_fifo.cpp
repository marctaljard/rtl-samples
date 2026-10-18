// Self-checking testbench for sync_fifo. Follow the pattern in smoke/tb/tb_counter.cpp.
#include <cstdint>
#include <cstdio>
#include <deque>
#include <memory>
#include <random>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vsync_fifo.h"

int main(int argc, char** argv) {
    auto ctx = std::make_unique<VerilatedContext>();
    ctx->commandArgs(argc, argv);
    ctx->traceEverOn(true);
    auto dut = std::make_unique<Vsync_fifo>(ctx.get());
    VerilatedVcdC tfp;
    dut->trace(&tfp, 99);
    tfp.open("sync_fifo.vcd");

    auto tick = [&] {
        dut->clk = 0; dut->eval(); tfp.dump(ctx->time()); ctx->timeInc(5);
        dut->clk = 1; dut->eval(); tfp.dump(ctx->time()); ctx->timeInc(5);
    };

    std::mt19937 rng(1);
    std::deque<uint8_t> model;        // reference model
    int errors = 0;

    dut->rst = 1; dut->wr_en = 0; dut->rd_en = 0; tick(); dut->rst = 0;

    // TODO: your stimulus and checks. Suggested tests:
    //   1. fill to full, check `full`, check a further write is ignored
    //   2. drain to empty, check data order and `empty`
    //   3. 10,000 cycles of random simultaneous reads and writes against `model`
    //   4. read and write on the same cycle when full, and when empty

    tfp.close();
    dut->final();
    std::printf("sync_fifo: %s (%d errors)\n", errors ? "FAIL" : "PASS", errors);
    return errors ? 1 : 0;
}
