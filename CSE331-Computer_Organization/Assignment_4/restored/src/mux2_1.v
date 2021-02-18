module mux2_1(select, input1, input2, out);
input select, input1, input2;
output out;

wire x1, x2, s_not;


not(s_not, select);
and(x1, s_not, input1);
and(x2, select, input2);
or(out, x1, x2);

endmodule

/*
S		i0		i1		out
0		0		0		0
0		0		1		0
0		1		0		1
0		1		1		1
1		0		0		0
1		0		1		1
1		1		0		0
1		1		1		1
out = S'.io + S.i1
*/
