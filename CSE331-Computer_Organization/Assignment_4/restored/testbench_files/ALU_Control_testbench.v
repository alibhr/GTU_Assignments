`define DELAY 20
module ALU_Control_testbench();

reg [5:0] fun;
reg [1:0] alu_op;
reg [2:0] expected;
wire [2:0] alu_select;

ALU_Control ALU_Control_test (fun, alu_op, alu_select);

initial begin
	//
	alu_op = 2'b00;
	fun = 6'b000000;
	expected = 3'b010;
	#`DELAY;
	
	alu_op = 2'b00;
	fun = 6'b111111;
	expected = 3'b010;
	#`DELAY;
	
	alu_op = 2'b00;
	fun = 6'b011011;
	expected = 3'b010;
	#`DELAY;
	
	//
	alu_op = 2'b01;
	fun = 6'b000000;
	expected = 3'b110;
	#`DELAY;
	
	alu_op = 2'b01;
	fun = 6'b111111;
	expected = 3'b110;
	#`DELAY;
	
	alu_op = 2'b01;
	fun = 6'b011011;
	expected = 3'b110;
	#`DELAY;
	
	//
	alu_op = 2'b11;
	fun = 6'b000000;
	expected = 3'b001;
	#`DELAY;
	
	alu_op = 2'b11;
	fun = 6'b111111;
	expected = 3'b001;
	#`DELAY;
	
	alu_op = 2'b11;
	fun = 6'b011011;
	expected = 3'b001;
	#`DELAY;
	
	//
	alu_op = 2'b10;
	fun = 6'b100000;
	expected = 3'b010;
	#`DELAY;
	
	alu_op = 2'b10;
	fun = 6'b100010;
	expected = 3'b110;
	#`DELAY;
	
	alu_op = 2'b10;
	fun = 6'b100100;
	expected = 3'b000;
	#`DELAY;
	
	alu_op = 2'b10;
	fun = 6'b100101;
	expected = 3'b001;
	#`DELAY;
	
	alu_op = 2'b10;
	fun = 6'b100110;
	expected = 3'b011;
	#`DELAY;

end

initial begin
	$monitor("fun=%6b, alu_op=%2b, alu_select=%3b, expected=%3b", fun, alu_op, alu_select, expected);
end

endmodule
