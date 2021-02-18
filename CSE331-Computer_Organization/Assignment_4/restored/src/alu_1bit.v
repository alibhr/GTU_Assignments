module alu_1bit(a, b, op_code, c_in, result, c_out);

input a, b, c_in;
input [2:0] op_code;
output result, c_out;
wire bXOROp, aANDb, aORb, NaANDb, aXORb, aXbAndC, aXbOrC, NaXbAndC, sum;
wire [1:0] select_bits;

assign select_bits = op_code[1:0];

my_xor b_XOR_Op (b, op_code[2], bXOROp);
and a_AND_b (aANDb, a, bXOROp);
or a_OR_b (aORb, a, bXOROp);
not N_a_AND_b (NaANDb, aANDb);
and a_XOR_b (aXORb, NaANDb, aORb);

and aXbAndC_ (aXbAndC, c_in, aXORb);
or aXbOrC_ (aXbOrC, c_in, aXORb);

not NaXbAndC_ (NaXbAndC, aXbAndC);
and and_sum (sum, NaXbAndC, aXbOrC);

or carr_out_ (c_out, aANDb, aXbAndC);

mux4_1 alu_result (select_bits, aANDb, aORb, sum, aXORb, result);

endmodule

/*
ALUop		Function
000		AND
001		OR
010		ADD
110		SUBTRACT
011		XOR
*/
