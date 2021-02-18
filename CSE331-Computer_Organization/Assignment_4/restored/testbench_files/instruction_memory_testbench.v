`define DELAY 20
module instruction_memory_testbench();

reg clk;
reg [31:0] address;
wire [31:0] instruction;

instruction_memory instruction_memory_test (clk, address, instruction);

initial begin
	$readmemb("instruction_memory.txt", instruction_memory_test.my_memory);
	clk = 0;
	
	address=32'b00000000000000000000000000000000;
	#`DELAY;

end


always begin
	#10 clk = ~clk;
end

initial begin
	$monitor("clk=%1b, address=%32b, instruction=%32b",clk, address, instruction);
end

endmodule
