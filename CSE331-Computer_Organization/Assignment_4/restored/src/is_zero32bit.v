module is_zero32bit(in, out);

input [31:0] in;
output out;
wire [15:0] layer1;
wire [7:0] layer2;
wire [3:0] layer3;
wire [1:0] layer4;
wire temp;

or or_l1_1  (layer1[ 0], in[ 0], in[ 1]);
or or_l1_2  (layer1[ 1], in[ 2], in[ 3]);
or or_l1_3  (layer1[ 2], in[ 4], in[ 5]);
or or_l1_4  (layer1[ 3], in[ 6], in[ 7]);
or or_l1_5  (layer1[ 4], in[ 8], in[ 9]);
or or_l1_6  (layer1[ 5], in[10], in[11]);
or or_l1_7  (layer1[ 6], in[12], in[13]);
or or_l1_8  (layer1[ 7], in[14], in[15]);
or or_l1_9  (layer1[ 8], in[16], in[17]);
or or_l1_10 (layer1[ 9], in[18], in[19]);
or or_l1_11 (layer1[10], in[20], in[21]);
or or_l1_12 (layer1[11], in[22], in[23]);
or or_l1_13 (layer1[12], in[24], in[25]);
or or_l1_14 (layer1[13], in[26], in[27]);
or or_l1_15 (layer1[14], in[28], in[29]);
or or_l1_16 (layer1[15], in[30], in[31]);

or or_l2_1 (layer2[0], layer1[ 0], layer1[ 1]);
or or_l2_2 (layer2[1], layer1[ 2], layer1[ 3]);
or or_l2_3 (layer2[2], layer1[ 4], layer1[ 5]);
or or_l2_4 (layer2[3], layer1[ 6], layer1[ 7]);
or or_l2_5 (layer2[4], layer1[ 8], layer1[ 9]);
or or_l2_6 (layer2[5], layer1[10], layer1[11]);
or or_l2_7 (layer2[6], layer1[12], layer1[13]);
or or_l2_8 (layer2[7], layer1[14], layer1[15]);

or or_l3_1 (layer3[0], layer2[0], layer2[1]);
or or_l3_2 (layer3[1], layer2[2], layer2[3]);
or or_l3_3 (layer3[2], layer2[4], layer2[5]);
or or_l3_4 (layer3[3], layer2[6], layer2[7]);

or or_l4_1 (layer4[0], layer3[0], layer3[1]);
or or_l4_2 (layer4[1], layer3[2], layer3[3]);

or or_final (temp, layer4[0], layer4[1]);

not not_final(out, temp);

endmodule
