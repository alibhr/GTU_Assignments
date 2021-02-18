module and6in(out, i0, i1, i2, i3, i4, i5);

input i0, i1, i2, i3, i4, i5;
output out;
wire layer0_0, layer0_1, layer0_2, layer1_0, layer1_1;

and AND0 (layer0_0, i0, i1);
and AND1 (layer0_1, i2, i3);
and AND2 (layer0_2, i4, i5);

and AND3 (layer1_0, layer0_0, layer0_1);
and AND4 (out, layer1_0, layer0_2);

endmodule
