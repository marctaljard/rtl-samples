# rtl-samples

[![tests](https://github.com/marctaljard/rtl-samples/actions/workflows/ci.yml/badge.svg)](https://github.com/marctaljard/rtl-samples/actions/workflows/ci.yml)

Small, carefully verified SystemVerilog building blocks. Each module has a self-checking
Verilator testbench written in C++ that compares the design against a reference model on
every cycle, and a README recording the design decisions and what the tests do and do not
cover.

| Module | What it is | Status |
|---|---|---|
| [`sync_fifo`](sync_fifo/) | Single-clock FIFO | in progress |
| [`async_fifo`](async_fifo/) | Dual-clock FIFO with Gray-code pointer crossing | in progress |
| [`rr_arbiter`](rr_arbiter/) | N-way round-robin arbiter | in progress |

## Quick start

**1. Install the tools**

| Platform | Command |
|---|---|
| Windows | Install WSL (`wsl --install` in PowerShell, then reboot), open Ubuntu, then run the Ubuntu line below |
| Ubuntu / WSL | `sudo apt update && sudo apt install -y verilator g++ make gtkwave` |
| macOS | `brew install verilator surfer` (Surfer is the waveform viewer here: the GTKWave cask is discontinued, x86-only and blocked by Gatekeeper) |

Check: `verilator --version` should print 5.x.

**2. Clone and run the toolchain check**

    git clone https://github.com/marctaljard/rtl-samples.git
    cd rtl-samples
    make -C smoke            # expect: counter: PASS (0 errors)

**3. Work on a module**

    make -C sync_fifo        # build and run its testbench
    make -C sync_fifo lint   # strict lint (-Wall)
    make -C sync_fifo wave   # run, then open the waveform

`make` at the top level runs every finished module; CI runs `make lint test` on every push.

## How each module is verified
- **Reference model in C++** — e.g. `std::deque` for the FIFOs — checked against the design every cycle
- **Directed tests** for edge cases: full, empty, simultaneous read/write at the boundaries, reset
- **Random tests** — at least 10,000 cycles with a fixed seed, so any failure reproduces exactly
- **Strict lint** — Verilator `-Wall`, no unexplained waivers
- **Waveforms** — every run writes a `.vcd` file for inspection

## Layout

    <module>/rtl/        SystemVerilog source
    <module>/tb/         C++ testbench and reference model
    <module>/README.md   design decisions, verification, known limitations
    smoke/               toolchain check: a counter and a complete example testbench
    mk/verilator.mk      shared build rules
    docs/workflow.md     how a module goes from empty to done

## References
- C. E. Cummings, *Simulation and Synthesis Techniques for Asynchronous FIFO Design*, SNUG 2002
- C. E. Cummings, *Clock Domain Crossing (CDC) Design & Verification Techniques Using SystemVerilog*, SNUG 2008
- [Verilator documentation](https://verilator.org/guide/latest/)
