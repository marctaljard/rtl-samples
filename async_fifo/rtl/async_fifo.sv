// Asynchronous FIFO: write and read sides on unrelated clocks.
// Signal names follow Cummings, "Simulation and Synthesis Techniques for
// Asynchronous FIFO Design" (SNUG 2002), so the paper maps directly onto this code.
// Decide and document in README.md:
//   - why pointers cross domains in Gray code, not binary
//   - how many synchroniser stages and why
//   - why full is pessimistic on the write side and empty on the read side
//   - how each side's reset is synchronised
module async_fifo #(
    parameter int WIDTH  = 8,
    parameter int ADDR_W = 4          // depth = 2**ADDR_W
) (
    // write domain
    input  logic             wclk,
    input  logic             wrst_n,  // active-low reset
    input  logic             winc,
    input  logic [WIDTH-1:0] wdata,
    output logic             wfull,
    // read domain
    input  logic             rclk,
    input  logic             rrst_n,
    input  logic             rinc,
    output logic [WIDTH-1:0] rdata,
    output logic             rempty
);
    // TODO: your implementation
endmodule
