`define DELAY 20
module data_memory_testbench();

reg [31:0] address, write_data;
reg mem_write, mem_read, clk;
wire [31:0] read_data;

data_memory data_memory_test (clk, address, write_data, mem_write, mem_read, read_data);

initial begin
	$readmemb("data_memory.txt", data_memory_test.data_regs);

	clk = 0;
	address = 32'b00;
	write_data = 32'b1111;
	mem_write = 1'b0;
	mem_read = 1'b1;
	#`DELAY;
	
	address = 32'b01;
	write_data = 32'b111;
	mem_write = 1'b0;
	mem_read = 1'b1;
	#`DELAY;
	
	address = 32'b01;
	write_data = 32'b11;
	mem_write = 1'b1;
	mem_read = 1'b1;
	#`DELAY;
	
end


always begin
	#10 clk = ~clk;
end

initial begin
	$monitor("address=%32b, write_data=%32b, mem_write=%1b, mem_read=%1b, read_data=%32b",
		address, write_data, mem_write, mem_read, read_data);
end

endmodule
