module mux_2_1_5bit(select, input1, input2, out);

input select;
input [4:0] input1, input2;
output [4:0] out;

mux2_1 m0  (select, input1[ 0], input2[ 0], out[ 0]);
mux2_1 m1  (select, input1[ 1], input2[ 1], out[ 1]);
mux2_1 m2  (select, input1[ 2], input2[ 2], out[ 2]);
mux2_1 m3  (select, input1[ 3], input2[ 3], out[ 3]);
mux2_1 m4  (select, input1[ 4], input2[ 4], out[ 4]);

endmodule
