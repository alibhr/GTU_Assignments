module new_instructions(in, out);

input [31:0] in;
output [31:0] out;
wire lt, eq, gt, not_lt, not_eq;
wire t0, t1;

zero_cmp32bit compare (in, lt, eq, gt);

not notLT (not_lt, lt);
my_xor eXORg (eq, gt, t0);
and tANDl (out[0], t0, not_lt);

not notEQ (not_eq, eq);
my_xor lXORg (lt, gt, t1);
and tANDe (out[1], t1, not_eq);

// There are some warning because signal of these pins are permanent
// https://electronics.stackexchange.com/questions/39074/altera-optimisation-stuck-at-gnd-due-to-stuck-port-data-in
// https://stackoverflow.com/questions/22722812/vhdl-warning-warning-13024-output-pins-are-stuck-at-vcc-or-gnd-on-crucial-o
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
assign out[16] = 1'b0;
assign out[17] = 1'b0;
assign out[18] = 1'b0;
assign out[19] = 1'b0;
assign out[20] = 1'b0;
assign out[21] = 1'b0;
assign out[22] = 1'b0;
assign out[23] = 1'b0;
assign out[24] = 1'b0;
assign out[25] = 1'b0;
assign out[26] = 1'b0;
assign out[27] = 1'b0;
assign out[28] = 1'b0;
assign out[29] = 1'b0;
assign out[30] = 1'b0;
assign out[31] = 1'b0;

endmodule
