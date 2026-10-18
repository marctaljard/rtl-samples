# Workflow: from empty module to done

Order: `sync_fifo` → `async_fifo` → `rr_arbiter`. Roughly 1.5–2 hours each.

1. **Decide before coding (10 min).** Answer every question in the header comment of
   `rtl/<module>.sv` in the module README's *Design decisions* section.
2. **Write the RTL (30–45 min).** Run `make -C <module> lint` until clean.
3. **Write the reference model (10 min)** in the testbench — the simplest correct C++ version.
4. **Directed tests (15 min)** for each edge case listed in the testbench TODO comments.
5. **Random test (10 min):** ≥10,000 cycles, fixed seed, compare every cycle.
6. **Break it on purpose (5 min):** introduce one bug (e.g. off-by-one on full). The testbench
   must catch it. If it doesn't, your checks are too weak. Revert.
7. **Look at the waveform once** (`make -C <module> wave`) at a full→empty transition.
8. **Write the README:** Verification and Known limitations.
9. **Review:** re-read the RTL and testbench against the done checklist; fix must-fix items.
10. **Ship:** add the module to `MODULES` in the top-level Makefile, update the status table,
    commit, push, confirm CI is green.
11. **Explain-back:** explain the module aloud in 2 minutes without notes.

## Done checklist
- [ ] lint clean  - [ ] reference model  - [ ] directed tests  - [ ] ≥10k random cycles
- [ ] deliberate bug caught  - [ ] README complete  - [ ] in MODULES  - [ ] CI green
- [ ] explained aloud without notes
