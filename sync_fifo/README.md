# sync_fifo

**Status:** in progress

Single-clock FIFO with full and empty flags.

## Run

    make          # build and run the testbench
    make lint     # strict lint (-Wall)
    make wave     # run, then open sync_fifo.vcd in the waveform viewer

## Interface
Port list and parameters: see [`rtl/sync_fifo.sv`](rtl/sync_fifo.sv).

## Design decisions
<!-- Answer every question in the header comment of rtl/sync_fifo.sv, each with the reason. -->

## Verification
<!-- Reference model used; directed tests (list them); random test (cycles, seed);
     the deliberate bug you introduced and confirmed the testbench caught. -->

## Known limitations
<!-- What it does not handle or has not been tested for, stated plainly. -->
