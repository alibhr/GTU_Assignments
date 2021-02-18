module alu_32bit(a, b, op_code, result, c_out, Z);

input [31:0] a, b;
input [2:0] op_code;
output [31:0] result;
output c_out, Z;
wire [30:0] carry_out;

alu_1bit alu1_0  (a[ 0], b[ 0], op_code, op_code  [ 2], result[ 0], carry_out[ 0]);
alu_1bit alu1_1  (a[ 1], b[ 1], op_code, carry_out[ 0], result[ 1], carry_out[ 1]);
alu_1bit alu1_2  (a[ 2], b[ 2], op_code, carry_out[ 1], result[ 2], carry_out[ 2]);
alu_1bit alu1_3  (a[ 3], b[ 3], op_code, carry_out[ 2], result[ 3], carry_out[ 3]);
alu_1bit alu1_4  (a[ 4], b[ 4], op_code, carry_out[ 3], result[ 4], carry_out[ 4]);
alu_1bit alu1_5  (a[ 5], b[ 5], op_code, carry_out[ 4], result[ 5], carry_out[ 5]);
alu_1bit alu1_6  (a[ 6], b[ 6], op_code, carry_out[ 5], result[ 6], carry_out[ 6]);
alu_1bit alu1_7  (a[ 7], b[ 7], op_code, carry_out[ 6], result[ 7], carry_out[ 7]);
alu_1bit alu1_8  (a[ 8], b[ 8], op_code, carry_out[ 7], result[ 8], carry_out[ 8]);
alu_1bit alu1_9  (a[ 9], b[ 9], op_code, carry_out[ 8], result[ 9], carry_out[ 9]);
alu_1bit alu1_10 (a[10], b[10], op_code, carry_out[ 9], result[10], carry_out[10]);
alu_1bit alu1_11 (a[11], b[11], op_code, carry_out[10], result[11], carry_out[11]);
alu_1bit alu1_12 (a[12], b[12], op_code, carry_out[11], result[12], carry_out[12]);
alu_1bit alu1_13 (a[13], b[13], op_code, carry_out[12], result[13], carry_out[13]);
alu_1bit alu1_14 (a[14], b[14], op_code, carry_out[13], result[14], carry_out[14]);
alu_1bit alu1_15 (a[15], b[15], op_code, carry_out[14], result[15], carry_out[15]);
alu_1bit alu1_16 (a[16], b[16], op_code, carry_out[15], result[16], carry_out[16]);
alu_1bit alu1_17 (a[17], b[17], op_code, carry_out[16], result[17], carry_out[17]);
alu_1bit alu1_18 (a[18], b[18], op_code, carry_out[17], result[18], carry_out[18]);
alu_1bit alu1_19 (a[19], b[19], op_code, carry_out[18], result[19], carry_out[19]);
alu_1bit alu1_20 (a[20], b[20], op_code, carry_out[19], result[20], carry_out[20]);
alu_1bit alu1_21 (a[21], b[21], op_code, carry_out[20], result[21], carry_out[21]);
alu_1bit alu1_22 (a[22], b[22], op_code, carry_out[21], result[22], carry_out[22]);
alu_1bit alu1_23 (a[23], b[23], op_code, carry_out[22], result[23], carry_out[23]);
alu_1bit alu1_24 (a[24], b[24], op_code, carry_out[23], result[24], carry_out[24]);
alu_1bit alu1_25 (a[25], b[25], op_code, carry_out[24], result[25], carry_out[25]);
alu_1bit alu1_26 (a[26], b[26], op_code, carry_out[25], result[26], carry_out[26]);
alu_1bit alu1_27 (a[27], b[27], op_code, carry_out[26], result[27], carry_out[27]);
alu_1bit alu1_28 (a[28], b[28], op_code, carry_out[27], result[28], carry_out[28]);
alu_1bit alu1_29 (a[29], b[29], op_code, carry_out[28], result[29], carry_out[29]);
alu_1bit alu1_30 (a[30], b[30], op_code, carry_out[29], result[30], carry_out[30]);
alu_1bit alu1_31 (a[31], b[31], op_code, carry_out[30], result[31], c_out);

is_zero32bit ZeroBit (result, Z);

endmodule

/*
ALUop		Function
000		AND
001		OR
010		ADD
110		SUBTRACT
011		XOR
*/
