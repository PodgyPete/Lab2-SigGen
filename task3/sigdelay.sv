module sigdelay #(
    parameter A_WIDTH = 9,
              D_WIDTH = 8
)(
    input  logic clk,
    input  logic rst,
    input  logic wr,
    input  logic rd,
    input  logic [A_WIDTH-1:0] offset,
    input  logic [D_WIDTH-1:0] mic_signal,
    output logic [D_WIDTH-1:0] delayed_signal
);

    logic [A_WIDTH-1:0] wr_addr;
    logic [A_WIDTH-1:0] rd_addr;

// incrementing write addresses
counter #(A_WIDTH) addrCounter (
    .clk (clk),
    .rst (rst),
    .en (1'b1),
    .count (wr_addr),
    .incr (1'b1)
);

//read delayed by offset
assign rd_addr = wr_addr - offset;

// stores incoming audio + outputs offset audio
ram2ports #(A_WIDTH, D_WIDTH) audioRam (
    .clk (clk),
    .wr_en (wr),
    .rd_en (rd),
    .wr_addr (wr_addr),
    .rd_addr (rd_addr),
    .din (mic_signal),
    .dout (delayed_signal)
);

endmodule