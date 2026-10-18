// Self-checking testbench for async_fifo with two unrelated clocks.
#include <cstdint>
#include <cstdio>
#include <deque>
#include <memory>
#include <random>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vasync_fifo.h"

int main(int argc, char** argv) {
    auto ctx = std::make_unique<VerilatedContext>();
    ctx->commandArgs(argc, argv);
    ctx->traceEverOn(true);
    auto dut = std::make_unique<Vasync_fifo>(ctx.get());
    VerilatedVcdC tfp;
    dut->trace(&tfp, 99);
    tfp.open("async_fifo.vcd");

    // Two clocks with unrelated half-periods (in simulation time units).
    // Try several pairs: write faster than read, read faster than write, near-equal.
    const uint64_t W_HALF = 5, R_HALF = 7;
    uint64_t next_w = W_HALF, next_r = R_HALF;
    dut->wclk = 0; dut->rclk = 0;

    // Advance to the next clock edge (either domain). Returns which clock just rose.
    enum Edge { NONE, WRISE, RRISE };
    auto step = [&]() -> Edge {
        uint64_t t = std::min(next_w, next_r);
        ctx->time(t);
        Edge e = NONE;
        if (t == next_w) { dut->wclk = !dut->wclk; next_w += W_HALF; if (dut->wclk) e = WRISE; }
        if (t == next_r) { dut->rclk = !dut->rclk; next_r += R_HALF; if (dut->rclk) e = (e == WRISE) ? NONE : RRISE; }
        dut->eval();
        tfp.dump(t);
        return e;
    };

    std::mt19937 rng(1);
    std::deque<uint8_t> model;
    int errors = 0;

    dut->wrst_n = 0; dut->rrst_n = 0; dut->winc = 0; dut->rinc = 0;
    for (int i = 0; i < 20; ++i) step();
    dut->wrst_n = 1; dut->rrst_n = 1;

    // TODO: your stimulus and checks. Drive winc/wdata just after a write-clock
    // rising edge and rinc just after a read-clock rising edge.
    // Suggested tests:
    //   1. burst-write until wfull, then burst-read until rempty: order preserved
    //   2. long random run in both domains against `model`
    //   3. repeat with the clock ratio swapped
    // Note: wfull/rempty may assert late by a few cycles (that is the design);
    // your checks should allow for it rather than expect cycle-exact flags.

    tfp.close();
    dut->final();
    std::printf("async_fifo: %s (%d errors)\n", errors ? "FAIL" : "PASS", errors);
    return errors ? 1 : 0;
}
