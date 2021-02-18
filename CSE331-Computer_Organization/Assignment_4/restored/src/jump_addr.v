module jump_addr(PC31_28, instruction25_0, out);

input [3:0] PC31_28;
input [25:0] instruction25_0;
output [31:0] out;

assign out[0] = 1'b0;
assign out[1] = 1'b0;

assign out[ 2] = instruction25_0[ 0] ;
assign out[ 3] = instruction25_0[ 1] ;
assign out[ 4] = instruction25_0[ 2] ;
assign out[ 5] = instruction25_0[ 3] ;
assign out[ 6] = instruction25_0[ 4] ;
assign out[ 7] = instruction25_0[ 5] ;
assign out[ 8] = instruction25_0[ 6] ;
assign out[ 9] = instruction25_0[ 7] ;
assign out[10] = instruction25_0[ 8] ;
assign out[11] = instruction25_0[ 9] ;
assign out[12] = instruction25_0[10] ;
assign out[13] = instruction25_0[11] ;
assign out[14] = instruction25_0[12] ;
assign out[15] = instruction25_0[13] ;
assign out[16] = instruction25_0[14] ;
assign out[17] = instruction25_0[15] ;
assign out[18] = instruction25_0[16] ;
assign out[19] = instruction25_0[17] ;
assign out[20] = instruction25_0[18] ;
assign out[21] = instruction25_0[19] ;
assign out[22] = instruction25_0[20] ;
assign out[23] = instruction25_0[21] ;
assign out[24] = instruction25_0[22] ;
assign out[25] = instruction25_0[23] ;
assign out[26] = instruction25_0[24] ;
assign out[27] = instruction25_0[25] ;

assign out[28] = PC31_28[0] ;
assign out[29] = PC31_28[1] ;
assign out[30] = PC31_28[2] ;
assign out[31] = PC31_28[3] ;

endmodule
