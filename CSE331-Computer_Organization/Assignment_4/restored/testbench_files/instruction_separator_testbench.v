`define DELAY 20
module instruction_separator_testbench();

reg [31:0] instruction;
wire [5:0] instruction31_26;
wire [4:0] instruction25_21, instruction20_16, instruction15_11;
wire [15:0] instruction15_0;
wire [25:0] instruction25_0;
wire [5:0] instruction5_0;

instruction_separator instruction_separator_test (instruction, instruction31_26, instruction25_21 ,instruction20_16, instruction15_11, instruction15_0, instruction25_0, instruction5_0);

initial begin
	instruction = 32'b100001_10001_10001_10000_00000000001;
	#`DELAY;
	
	instruction = 32'b100001_10001_10001_10001_10000000001;
	#`DELAY;
	
	instruction = 32'b100001_10000_00000_00000_00000000001;
	#`DELAY;
	
	instruction = 32'b100001_10001_10001_10001_00000100001;
	#`DELAY;
	
end

initial begin
	$monitor("instruction=%32b, instruction31_26=%6b, instruction25_21=%5b, instruction20_16=%5b, instruction15_11=%5b, instruction15_0=%15b, instruction25_0=%26b, instruction5_0=%6b", 
		instruction, instruction31_26, instruction25_21, instruction20_16, instruction15_11, instruction15_0, instruction25_0, instruction5_0);
end

endmodule
