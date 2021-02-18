module and3in(out, in0, in1, in2);
input in0, in1, in2;
output out;
wire temp;

and(temp, in0, in1);
and(out, temp, in2);

endmodule
