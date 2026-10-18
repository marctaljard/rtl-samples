// Self-checking testbench for rr_arbiter.
#include <cstdint>
#include <cstdio>
#include <memory>
#include <random>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vrr_arbiter.h"

int main(int argc, char** argv) {
    auto ctx = std::make_unique<VerilatedContext>();
    ctx->commandArgs(argc, argv);
    ctx->traceEverOn(true);
    auto dut = std::make_unique<Vrr_arbiter>(ctx.get());
    VerilatedVcdC tfp;
    dut->trace(&tfp, 99);
    tfp.open("rr_arbiter.vcd");

    auto tick = [&] {
        dut->clk = 0; dut->eval(); tfp.dump(ctx->time()); ctx->timeInc(5);
        dut->clk = 1; dut->eval(); tfp.dump(ctx->time()); ctx->timeInc(5);
    };

    std::mt19937 rng(1);
    int errors = 0;

    dut->rst = 1; dut->req = 0; tick(); dut->rst = 0;

    // TODO: your stimulus and checks. Properties to check every cycle:
    //   1. gnt is zero or one-hot
    //   2. gnt is a subset of req (never grant a non-requester)
    //   3. if req != 0, some grant is given (no idle cycles with pending requests)
    //   4. fairness: with all inputs requesting, grants rotate in order
    //   5. no starvation: a held request is granted within N grants
    // A C++ reference model that predicts the exact grant is the strongest check.

    tfp.close();
    dut->final();
    std::printf("rr_arbiter: %s (%d errors)\n", errors ? "FAIL" : "PASS", errors);
    return errors ? 1 : 0;
}
