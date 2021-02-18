module adder_half(a, b, sum, carry_out);

input a, b;
output sum, carry_out;

my_xor xor1 (a, b, sum);
and carry_and (carry_out, a, b);

endmodule

/*
a		b		out	carry_out
0		0		0		0
0		1		1		0
1		0		1		0
1		1		0		1
*/
