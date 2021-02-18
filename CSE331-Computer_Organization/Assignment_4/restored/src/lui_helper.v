module lui_helper(in, out);

input [15:0] in;
output [31:0] out;

// https://electronics.stackexchange.com/questions/39074/altera-optimisation-stuck-at-gnd-due-to-stuck-port-data-in
// https://stackoverflow.com/questions/22722812/vhdl-warning-warning-13024-output-pins-are-stuck-at-vcc-or-gnd-on-crucial-o
assign out[ 0] = 1'b0;
assign out[ 1] = 1'b0;
assign out[ 2] = 1'b0;
assign out[ 3] = 1'b0;
assign out[ 4] = 1'b0;
assign out[ 5] = 1'b0;
assign out[ 6] = 1'b0;
assign out[ 7] = 1'b0;
assign out[ 8] = 1'b0;
assign out[ 9] = 1'b0;
assign out[10] = 1'b0;
assign out[11] = 1'b0;
assign out[12] = 1'b0;
assign out[13] = 1'b0;
assign out[14] = 1'b0;
assign out[15] = 1'b0;

assign out[16] = in[ 0];
assign out[17] = in[ 1];
assign out[18] = in[ 2];
assign out[19] = in[ 3];
assign out[20] = in[ 4];
assign out[21] = in[ 5];
assign out[22] = in[ 6];
assign out[23] = in[ 7];
assign out[24] = in[ 8];
assign out[25] = in[ 9];
assign out[26] = in[10];
assign out[27] = in[11];
assign out[28] = in[12];
assign out[29] = in[13];
assign out[30] = in[14];
assign out[31] = in[15];

endmodule
