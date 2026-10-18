// Round-robin arbiter: N requesters, at most one grant per cycle, one-hot.
// After a requester is granted, it becomes lowest priority.
// Decide and document in README.md:
//   - combinational grant (same cycle as req) or registered grant (next cycle)?
//   - how priority rotates (mask-based, double-width priority encoder, or other)
//   - fairness guarantee: worst-case wait for a continuously requesting input
module rr_arbiter #(
    parameter int N = 4
) (
    input  logic         clk,
    input  logic         rst,         // synchronous, active high
    input  logic [N-1:0] req,
    output logic [N-1:0] gnt
);
    // TODO: your implementation
endmodule
