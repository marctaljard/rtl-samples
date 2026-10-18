// Pattern used by every testbench in this repo:
//   1. drive inputs, 2. tick the clock, 3. update a C++ reference model,
//   4. compare DUT outputs to the model every cycle, 5. exit non-zero on any mismatch.
#include <cstdint>
#include <cstdio>
#include <memory>
#include <random>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vcounter.h"

int main(int argc, char** argv) {
    auto ctx = std::make_unique<VerilatedContext>();
    ctx->commandArgs(argc, argv);
    ctx->traceEverOn(true);
    auto dut = std::make_unique<Vcounter>(ctx.get());
    VerilatedVcdC tfp;
    dut->trace(&tfp, 99);
    tfp.open("counter.vcd");

    auto tick = [&] {                 // one full clock cycle
        dut->clk = 0; dut->eval(); tfp.dump(ctx->time()); ctx->timeInc(5);
        dut->clk = 1; dut->eval(); tfp.dump(ctx->time()); ctx->timeInc(5);
    };

    std::mt19937 rng(1);              // fixed seed: failures are reproducible
    uint8_t model = 0;
    int errors = 0;

    dut->rst = 1; dut->en = 0; tick(); dut->rst = 0;

    for (int cycle = 0; cycle < 1000; ++cycle) {
        dut->en = rng() & 1;
        if (dut->en) model++;         // reference model, updated on the same edge
        tick();
        if (dut->count != model) {
            std::printf("cycle %d: expected %u got %u\n", cycle, model, dut->count);
            ++errors;
        }
    }
    tfp.close();
    dut->final();
    std::printf("counter: %s (%d errors)\n", errors ? "FAIL" : "PASS", errors);
    return errors ? 1 : 0;
}
