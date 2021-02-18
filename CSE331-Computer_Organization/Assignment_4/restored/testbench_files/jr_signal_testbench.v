`define DELAY 20
module jr_signal_testbench();

reg [5:0] op, funct;
wire s;

jr_signal jr_signal_test (op, funct, s);

initial begin
	op=6'b000000;
	funct=6'b000000;
	#`DELAY;
	
	op=6'b000000;
	funct=6'b001000;
	#`DELAY;
	
	op=6'b100000;
	funct=6'b001000;
	#`DELAY;
	
	op=6'b010100;
	funct=6'b011010;
	#`DELAY;
end

initial begin
	$monitor("op=%6b, funct=%6b, s=%1b", op, funct, s);
end

endmodule
