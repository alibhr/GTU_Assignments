`define DELAY 20
module control_testbench();

reg [5:0] op, funct;
reg [14:0] expected;
wire RegDst, Beq, Bne, MemRead, MemtoReg, MemWrite, ALUsrc, RegWrite1, RegWrite2, Lui, J, Jal, Jr, Ori;
wire [1:0] ALUop;

control control_test (op, RegDst, Beq, Bne, MemRead, MemtoReg, ALUop, MemWrite, ALUsrc, RegWrite1, RegWrite2, Lui, J, Jal, Jr, Ori);

initial begin

	op = 6'b100011;
	funct = 6'b00000;
	expected = 15'b000110001100000;
	#`DELAY;
	
	op = 6'b101100;
	funct = 6'b00000;
	expected = 15'b000000011000000;

	#`DELAY;
	
	op = 6'b001100;
	funct = 6'b00000;
	expected = 15'b000001101010001;
	#`DELAY;
	
	op = 6'b001111;
	funct = 6'b00000;
	expected = 15'b000000000101000;
	#`DELAY;
	
	op = 6'b000100;
	funct = 6'b00000;
	expected = 15'b010000100000000;
	#`DELAY;
	
	op = 6'b000101;
	funct = 6'b00000;
	expected = 15'b001000100000000;
	#`DELAY;
	
	op = 6'b000000;
	funct = 6'b00000;
	expected = 15'b100001000110000;
	#`DELAY;
	
	op = 6'b000010;
	funct = 6'b00000;
	expected = 15'b000000000000100;
	#`DELAY;
	
	op = 6'b000011;
	funct = 6'b00000;
	expected = 15'b000000000010010;
	#`DELAY;
	
end

initial begin
	$monitor("op=%6b, RegDst=%1b, Beq=%1b, Bne=%1b, MemRead=%1b, MemtoReg=%1b, ALUop=%2b, MemWrite=%1b, ALUsrc=%1b, RegWrite1=%1b, RegWrite2=%1b, Lui=%1b, J=%1b, Jal=%1b, Ori=%1b, expected=%16b", 
		op, RegDst, Beq, Bne, MemRead, MemtoReg, ALUop, MemWrite, ALUsrc, RegWrite1, RegWrite2, Lui, J, Jal, Ori, expected);
end

endmodule
