module instruction_separator
(instruction, instruction31_26, instruction25_21, instruction20_16, instruction15_11, instruction15_0, instruction25_0, instruction5_0);

input [31:0] instruction;
output [5:0] instruction31_26;
output [4:0] instruction25_21, instruction20_16, instruction15_11;
output [15:0] instruction15_0;
output [25:0] instruction25_0;
output [5:0] instruction5_0;

assign instruction15_0[ 0] = instruction[ 0] ;
assign instruction15_0[ 1] = instruction[ 1] ;
assign instruction15_0[ 2] = instruction[ 2] ;
assign instruction15_0[ 3] = instruction[ 3] ;
assign instruction15_0[ 4] = instruction[ 4] ;
assign instruction15_0[ 5] = instruction[ 5] ;
assign instruction15_0[ 6] = instruction[ 6] ;
assign instruction15_0[ 7] = instruction[ 7] ;
assign instruction15_0[ 8] = instruction[ 8] ;
assign instruction15_0[ 9] = instruction[ 9] ;
assign instruction15_0[10] = instruction[10] ;
assign instruction15_0[11] = instruction[11] ;
assign instruction15_0[12] = instruction[12] ;
assign instruction15_0[13] = instruction[13] ;
assign instruction15_0[14] = instruction[14] ;
assign instruction15_0[15] = instruction[15] ;

assign instruction15_11[0] = instruction[11] ;
assign instruction15_11[1] = instruction[12] ;
assign instruction15_11[2] = instruction[13] ;
assign instruction15_11[3] = instruction[14] ;
assign instruction15_11[4] = instruction[15] ;

assign instruction20_16[0] = instruction[16] ;
assign instruction20_16[1] = instruction[17] ;
assign instruction20_16[2] = instruction[18] ;
assign instruction20_16[3] = instruction[19] ;
assign instruction20_16[4] = instruction[20] ;

assign instruction25_21[0] = instruction[21] ;
assign instruction25_21[1] = instruction[22] ;
assign instruction25_21[2] = instruction[23] ;
assign instruction25_21[3] = instruction[24] ;
assign instruction25_21[4] = instruction[25] ;

assign instruction31_26[0] = instruction[26] ;
assign instruction31_26[1] = instruction[27] ;
assign instruction31_26[2] = instruction[28] ;
assign instruction31_26[3] = instruction[29] ;
assign instruction31_26[4] = instruction[30] ;
assign instruction31_26[5] = instruction[31] ;

assign instruction25_0[ 0] = instruction[ 0] ;
assign instruction25_0[ 1] = instruction[ 1] ;
assign instruction25_0[ 2] = instruction[ 2] ;
assign instruction25_0[ 3] = instruction[ 3] ;
assign instruction25_0[ 4] = instruction[ 4] ;
assign instruction25_0[ 5] = instruction[ 5] ;
assign instruction25_0[ 6] = instruction[ 6] ;
assign instruction25_0[ 7] = instruction[ 7] ;
assign instruction25_0[ 8] = instruction[ 8] ;
assign instruction25_0[ 9] = instruction[ 9] ;
assign instruction25_0[10] = instruction[10] ;
assign instruction25_0[11] = instruction[11] ;
assign instruction25_0[12] = instruction[12] ;
assign instruction25_0[13] = instruction[13] ;
assign instruction25_0[14] = instruction[14] ;
assign instruction25_0[15] = instruction[15] ;
assign instruction25_0[16] = instruction[16] ;
assign instruction25_0[17] = instruction[17] ;
assign instruction25_0[18] = instruction[18] ;
assign instruction25_0[19] = instruction[19] ;
assign instruction25_0[20] = instruction[20] ;
assign instruction25_0[21] = instruction[21] ;
assign instruction25_0[22] = instruction[22] ;
assign instruction25_0[23] = instruction[23] ;
assign instruction25_0[24] = instruction[24] ;
assign instruction25_0[25] = instruction[25] ;

assign instruction5_0[0] = instruction[0] ;
assign instruction5_0[1] = instruction[1] ;
assign instruction5_0[2] = instruction[2] ;
assign instruction5_0[3] = instruction[3] ;
assign instruction5_0[4] = instruction[4] ;
assign instruction5_0[5] = instruction[5] ;

endmodule
