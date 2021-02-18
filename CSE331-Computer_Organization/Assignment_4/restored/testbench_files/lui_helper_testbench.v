`define DELAY 20
module lui_helper_testbench();

reg [15:0] in;
wire [31:0] out;

lui_helper lui_helper_test (in ,out);

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
