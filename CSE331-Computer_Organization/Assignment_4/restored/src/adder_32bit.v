module adder_32bit(a, b, carry_in, out, carry_out);

input [31:0] a, b;
input carry_in;
output [31:0] out;
output carry_out;
wire [30:0] t;

adder_full add_full1  (a[0],  b[0],  carry_in, out[0], t[0]);

adder_full add_full2  (a[1],  b[1],  t[0],  out[1],  t[1] );
adder_full add_full3  (a[2],  b[2],  t[1],  out[2],  t[2] );
adder_full add_full4  (a[3],  b[3],  t[2],  out[3],  t[3] );
adder_full add_full5  (a[4],  b[4],  t[3],  out[4],  t[4] );
adder_full add_full6  (a[5],  b[5],  t[4],  out[5],  t[5] );
adder_full add_full7  (a[6],  b[6],  t[5],  out[6],  t[6] );
adder_full add_full8  (a[7],  b[7],  t[6],  out[7],  t[7] );
adder_full add_full9  (a[8],  b[8],  t[7],  out[8],  t[8] );
adder_full add_full10 (a[9],  b[9],  t[8],  out[9],  t[9] );
adder_full add_full11 (a[10], b[10], t[9],  out[10], t[10]);
adder_full add_full12 (a[11], b[11], t[10], out[11], t[11]);
adder_full add_full13 (a[12], b[12], t[11], out[12], t[12]);
adder_full add_full14 (a[13], b[13], t[12], out[13], t[13]);
adder_full add_full15 (a[14], b[14], t[13], out[14], t[14]);
adder_full add_full16 (a[15], b[15], t[14], out[15], t[15]);
adder_full add_full17 (a[16], b[16], t[15], out[16], t[16]);
adder_full add_full18 (a[17], b[17], t[16], out[17], t[17]);
adder_full add_full19 (a[18], b[18], t[17], out[18], t[18]);
adder_full add_full20 (a[19], b[19], t[18], out[19], t[19]);
adder_full add_full21 (a[20], b[20], t[19], out[20], t[20]);
adder_full add_full22 (a[21], b[21], t[20], out[21], t[21]);
adder_full add_full23 (a[22], b[22], t[21], out[22], t[22]);
adder_full add_full24 (a[23], b[23], t[22], out[23], t[23]);
adder_full add_full25 (a[24], b[24], t[23], out[24], t[24]);
adder_full add_full26 (a[25], b[25], t[24], out[25], t[25]);
adder_full add_full27 (a[26], b[26], t[25], out[26], t[26]);
adder_full add_full28 (a[27], b[27], t[26], out[27], t[27]);
adder_full add_full29 (a[28], b[28], t[27], out[28], t[28]);
adder_full add_full30 (a[29], b[29], t[28], out[29], t[29]);
adder_full add_full31 (a[30], b[30], t[29], out[30], t[30]);

adder_full add_full32 (a[31], b[31], t[30], out[31], carry_out);

endmodule
