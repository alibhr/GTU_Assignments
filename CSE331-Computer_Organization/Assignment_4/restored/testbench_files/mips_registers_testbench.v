`define DELAY 20
module mips_registers_testbench();

reg clk;
reg  [4:0] read_reg1, read_reg2, write_reg1, write_reg2; 
reg  write_signal1, write_signal2;
reg [31:0] write_data1, write_data2; 
wire [31:0] read_data1, read_data2;

mips_registers registers (read_data1, read_data2, read_reg1, read_reg2, write_data1, write_data2, write_reg1, write_reg2, write_signal1, write_signal2, clk);

initial begin
	clk = 0;
	
	read_reg1 = 5'b00000;
	read_reg2 = 5'b00001;
	write_reg1 = 5'b00000;
	write_reg2 = 5'b00001;
	write_data1 = 32'b00000000000000000000000000000010;
	write_data2 = 32'b00000000000000000000000000000011;
	write_signal1 = 1'b1;
	write_signal2 = 1'b1;
	#`DELAY;

	read_reg1 = 5'b00010;
	read_reg2 = 5'b00011;
	write_reg1 = 5'b00010;
	write_reg2 = 5'b00011;
	write_data1 = 32'b00000000000000000000000000000110;
	write_data2 = 32'b00000000000000000000000000000111;
	write_signal1 = 1'b1;
	write_signal2 = 1'b1;
	#`DELAY;
	
	read_reg1 = 5'b00111;
	read_reg2 = 5'b00111;
	write_reg1 = 5'b00111;
	write_reg2 = 5'b00111;
	write_data1 = 32'b11000000000000000000000000000000;
	write_data2 = 32'b10000000000000000000000000000000;
	write_signal1 = 1'b1;
	write_signal2 = 1'b1;
	#`DELAY;

end

always begin
	#10 clk = ~clk;
end

initial begin
	$monitor("time=%2d, read_data1=%32b, read_data2=%32b", $time, read_data1, read_data2);
end

endmodule
