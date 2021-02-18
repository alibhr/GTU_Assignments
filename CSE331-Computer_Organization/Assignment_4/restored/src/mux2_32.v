module mux2_32(select, input1, input2, out);

input select;
input [31:0] input1, input2;
output [31:0] out;

mux2_1 m0  (select, input1[ 0], input2[ 0], out[ 0]);
mux2_1 m1  (select, input1[ 1], input2[ 1], out[ 1]);
mux2_1 m2  (select, input1[ 2], input2[ 2], out[ 2]);
mux2_1 m3  (select, input1[ 3], input2[ 3], out[ 3]);
mux2_1 m4  (select, input1[ 4], input2[ 4], out[ 4]);
mux2_1 m5  (select, input1[ 5], input2[ 5], out[ 5]);
mux2_1 m6  (select, input1[ 6], input2[ 6], out[ 6]);
mux2_1 m7  (select, input1[ 7], input2[ 7], out[ 7]);
mux2_1 m8  (select, input1[ 8], input2[ 8], out[ 8]);
mux2_1 m9  (select, input1[ 9], input2[ 9], out[ 9]);
mux2_1 m10 (select, input1[10], input2[10], out[10]);
mux2_1 m11 (select, input1[11], input2[11], out[11]);
mux2_1 m12 (select, input1[12], input2[12], out[12]);
mux2_1 m13 (select, input1[13], input2[13], out[13]);
mux2_1 m14 (select, input1[14], input2[14], out[14]);
mux2_1 m15 (select, input1[15], input2[15], out[15]);
mux2_1 m16 (select, input1[16], input2[16], out[16]);
mux2_1 m17 (select, input1[17], input2[17], out[17]);
mux2_1 m18 (select, input1[18], input2[18], out[18]);
mux2_1 m19 (select, input1[19], input2[19], out[19]);
mux2_1 m20 (select, input1[20], input2[20], out[20]);
mux2_1 m21 (select, input1[21], input2[21], out[21]);
mux2_1 m22 (select, input1[22], input2[22], out[22]);
mux2_1 m23 (select, input1[23], input2[23], out[23]);
mux2_1 m24 (select, input1[24], input2[24], out[24]);
mux2_1 m25 (select, input1[25], input2[25], out[25]);
mux2_1 m26 (select, input1[26], input2[26], out[26]);
mux2_1 m27 (select, input1[27], input2[27], out[27]);
mux2_1 m28 (select, input1[28], input2[28], out[28]);
mux2_1 m29 (select, input1[29], input2[29], out[29]);
mux2_1 m30 (select, input1[30], input2[30], out[30]);
mux2_1 m31 (select, input1[31], input2[31], out[31]);

endmodule
