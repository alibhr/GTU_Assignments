`define DELAY 20
module shift_left2_testbench();

reg [31:0] in;
wire [31:0] out;

shift_left2 shift_left2_test (in ,out);

initial begin
	in = 32'b11111111111111111111111111111111;
	#`DELAY;
	
	in = 32'b00000000111111110000000011111111;
	#`DELAY;
	
	in = 32'b11111111000000001111111100000000;
	#`DELAY;
end

initial begin
	$monitor("in=%32b, out=%32b", in, out);
end

endmodule
