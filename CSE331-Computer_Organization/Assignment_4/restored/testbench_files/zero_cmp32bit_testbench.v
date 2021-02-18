`define DELAY 20
module zero_cmp32bit_testbench();

reg [31:0] number;
wire lt, eq, gt;

zero_cmp32bit test_comparator (number, lt, eq, gt);

initial begin
	number=32'b10000000000000000000000000000000;
	#`DELAY;
	
	number=32'b00000000000000000000000000000000;
	#`DELAY;
	
	number=32'b00001100000000000011000000111000;
	#`DELAY;
	
	number=32'b11110000000000111000000000000000;
	#`DELAY;
	
	number=32'b00000000000000000000000000000000;
	#`DELAY;
	
	number=32'b01001100010000000011000010111000;
	#`DELAY;
end

initial begin
	$monitor("number=%32b, lt=%1b, eq=%1b, gt=%1b",number, lt, eq, gt);
end

endmodule
