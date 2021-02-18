module and_gate_6in(in1, in2, in3, in4, in5, in6, out);

input in1, in2, in3, in4, in5, in6;
output out;

wire x1, x2, x3, x4;

and(x1, in1, in2);
and(x2, in3, in4);
and(x3, in5, in6);
and(x4, x1, x2);

and(out, x3, x4);

endmodule
