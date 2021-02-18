module mux4_1(select, in0, in1, in2, in3, out);

input [1:0]  select;
input in0, in1, in2, in3;
output out;
wire not_s0, not_s1, and0, and1, and2, and3, or0, or1;

not notS0 (not_s0, select[0]);
not notS1 (not_s1, select[1]);

and3in and0_ (and0, select[0], select[1], in3);
and3in and1_ (and1, not_s0, select[1], in2);
and3in and2_ (and2, select[0], not_s1, in1);
and3in and3_ (and3, not_s0, not_s1, in0);

or or0_ (or0, and0, and1);
or or1_ (or1, and2, and3);

or last_step (out, or0, or1);

endmodule
