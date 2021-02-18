`define DELAY 20
module new_instructions_testbench();

reg [31:0] in;
wire [31:0] out;

new_instructions test_new_instructions (in, out);

initial begin
	in = 32'b00000000000000000000000000000000;
	#`DELAY;
	
	in = 32'b10000011111111111000000000000000;
	#`DELAY;
	
	in = 32'b00000000000001000000000000000000;
	#`DELAY;
end

initial begin
	$monitor("in=%32b, out=%32b", in, out);
end

endmodule
