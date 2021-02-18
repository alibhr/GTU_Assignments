module sign_extend16_32(in ,out);

input [15:0] in;
output [31:0] out;

extender16_32 extender__ (in[15], in, out);

endmodule
