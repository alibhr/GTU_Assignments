module extender16_32(extention,in ,out);
input [15:0] in;
input extention;
output [31:0] out;

assign out [ 0] = in [ 0] ;
assign out [ 1] = in [ 1] ;
assign out [ 2] = in [ 2] ;
assign out [ 3] = in [ 3] ;
assign out [ 4] = in [ 4] ;
assign out [ 5] = in [ 5] ;
assign out [ 6] = in [ 6] ;
assign out [ 7] = in [ 7] ;
assign out [ 8] = in [ 8] ;
assign out [ 9] = in [ 9] ;
assign out [10] = in [10] ;
assign out [11] = in [11] ;
assign out [12] = in [12] ;
assign out [13] = in [13] ;
assign out [14] = in [14] ;
assign out [15] = in [15] ;
assign out [16] = extention;
assign out [17] = extention;
assign out [18] = extention;
assign out [19] = extention;
assign out [20] = extention;
assign out [21] = extention;
assign out [22] = extention;
assign out [23] = extention;
assign out [24] = extention;
assign out [25] = extention;
assign out [26] = extention;
assign out [27] = extention;
assign out [28] = extention;
assign out [29] = extention;
assign out [30] = extention;
assign out [31] = extention;

endmodule
