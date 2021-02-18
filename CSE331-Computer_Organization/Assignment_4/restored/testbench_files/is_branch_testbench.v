`define DELAY 20
module is_branch_testbench();

reg beq, bne, Z;
wire out;

is_branch is_branch_test (beq, bne, Z, out);

initial begin
	beq = 1'b0;
	bne = 1'b0;
	Z = 1'b0;
	#`DELAY;
	
	beq = 1'b0;
	bne = 1'b0;
	Z = 1'b1;
	#`DELAY;
	
	beq = 1'b0;
	bne = 1'b1;
	Z = 1'b0;
	#`DELAY;
	
	beq = 1'b0;
	bne = 1'b1;
	Z = 1'b1;
	#`DELAY;
	
	beq = 1'b1;
	bne = 1'b0;
	Z = 1'b0;
	#`DELAY;
	
	beq = 1'b1;
	bne = 1'b0;
	Z = 1'b1;
	#`DELAY;
	
	beq = 1'b1;
	bne = 1'b1;
	Z = 1'b0;
	#`DELAY;
	
	beq = 1'b1;
	bne = 1'b1;
	Z = 1'b1;
	#`DELAY;
end

initial begin
	$monitor("beq=%1b, bne%1b, Z%1b, out%1b", beq, bne, Z, out);
end

endmodule
