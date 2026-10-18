// Synchronous FIFO: one clock, write and read ports.
// Decide and document in README.md before writing logic:
//   - read latency: first-word fall-through, or rd_data valid one cycle after rd_en?
//   - how you detect full vs empty (extra pointer bit, or an occupancy counter) and why
//   - behaviour on write-when-full and read-when-empty (ignore? assert?)
//   - whether DEPTH must be a power of two
module sync_fifo #(
    parameter int WIDTH = 8,
    parameter int DEPTH = 16
) (
    input  logic             clk,
    input  logic             rst,      // synchronous, active high
    input  logic             wr_en,
    input  logic [WIDTH-1:0] wr_data,
    output logic             full,
    input  logic             rd_en,
    output logic [WIDTH-1:0] rd_data,
    output logic             empty
);
    // TODO: your implementation
endmodule
