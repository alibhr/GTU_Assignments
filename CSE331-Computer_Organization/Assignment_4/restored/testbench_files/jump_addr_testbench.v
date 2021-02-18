`define DELAY 20
module jump_addr_testbench();

reg [3:0] PC31_28;
reg [25:0] instruction25_0;
wire [31:0] out;

jump_addr jump_addr_test (PC31_28, instruction25_0, out);

initial begin
	PC31_28 = 4'b0011;
	instruction25_0 = 26'b10000000011000010000000001;
	#`DELAY;
	
	PC31_28 = 4'b1111;
	instruction25_0 = 26'b10000000011000010000000001;
	#`DELAY;
	
	PC31_28 = 4'b1100;
	instruction25_0 = 26'b10000000011000010000000001;
	#`DELAY;
	
	PC31_28 = 4'b0000;
	instruction25_0 = 26'b10000000011000010000000001;
	#`DELAY;

end

initial begin
	$monitor("PC31_28=%4b, instruction25_0=%26b, out=%32b", PC31_28, instruction25_0, out);
end

endmodule
