`define DELAY 20
module sign_extend_testbench();

reg [15:0] in;
wire [31:0] out;

sign_extend16_32 sign_extend_test (in ,out);

initial begin
	in = 16'b0000000000000000;
	#`DELAY;
	
	in = 16'b1111111111111111;
	#`DELAY;
	
	in = 16'b0000000011111111;
	#`DELAY;
	
	in = 16'b1111111100000000;
	#`DELAY;
end

initial begin
	$monitor("in=%16b, out=%32b", in, out);
end

endmodule
