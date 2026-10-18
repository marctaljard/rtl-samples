// Toolchain check and worked example of the testbench pattern used in this repo.
// 8-bit counter with synchronous active-high reset and count enable.
module counter #(
    parameter int WIDTH = 8
) (
    input  logic             clk,
    input  logic             rst,
    input  logic             en,
    output logic [WIDTH-1:0] count
);
    always_ff @(posedge clk) begin
        if (rst)     count <= '0;
        else if (en) count <= count + 1'b1;
    end
endmodule
