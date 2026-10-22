module ram2ports #(
    parameter A_WIDTH = 9,
    D_WIDTH = 8
)(
    input logic clk,
    input logic wr_en,
    input logic rd_en,
    input logic [A_WIDTH-1:0] wr_addr,
    input logic [A_WIDTH-1:0] rd_addr,
    input logic [D_WIDTH-1:0] din,
    output logic [D_WIDTH-1:0] dout
);

logic [D_WIDTH-1:0] ram_array [2**A_WIDTH-1:0];

always_ff @(posedge clk) begin
    if (wr_en)
        ram_array[wr_addr] <= din;
    if (rd_en)
        dout <= ram_array[rd_addr];
end

endmodule
