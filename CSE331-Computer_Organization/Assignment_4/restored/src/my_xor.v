module my_xor(a, b, out);

input a, b;
output out;
wire not_a, not_b, a1, b1;

not notA (not_a, a);
not notB (not_b, b);

and and1(a1 , not_a, b);
and and2(b1 , a, not_b);

or or1 (out, a1, b1);

endmodule
