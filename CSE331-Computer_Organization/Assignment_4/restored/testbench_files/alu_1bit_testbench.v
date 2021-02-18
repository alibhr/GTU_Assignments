`define DELAY 20
module alu_1bit_testbench();

reg a, b, c_in;
reg [2:0] op_code;
wire result, c_out;

alu_1bit test_ALU (a, b, op_code, c_in, result, c_out);

initial begin
  /* test and */
  op_code = 3'b000;
  a = 1'b1;
  b = 1'b0;
  c_in = 1'b0;
  #`DELAY;
  
  
  /* test or */
  op_code = 3'b001;
  a = 1'b1;
  b = 1'b0;
  c_in = 1'b0;
  #`DELAY;
  
  
  /* test0 add */
  op_code = 3'b010;
  a = 1'b1;
  b = 1'b0;
  c_in = 1'b0;
  #`DELAY;
  
  
  /* test1 add */
  op_code = 3'b010;
  a = 1'b1;
  b = 1'b1;
  c_in = 1'b0;
  #`DELAY;
  
  
  /* test2 add */
  op_code = 3'b010;
  a = 1'b0;
  b = 1'b0;
  c_in = 1'b0;
  #`DELAY;
  
  
  /* test0 subtract */
  op_code = 3'b110;
  a = 1'b1;
  b = 1'b0;
  c_in = 1'b0;
  #`DELAY;
  
  
  /* test1 subtract */
  op_code = 3'b110;
  a = 1'b1;
  b = 1'b1;
  c_in = 1'b0;
  #`DELAY;
  
  
  /* test2 subtract */
  op_code = 3'b110;
  a = 1'b0;
  b = 1'b1;
  c_in = 1'b0;
  #`DELAY;
  
  
  /* test3 subtract */
  op_code = 3'b110;
  a = 1'b0;
  b = 1'b0;
  c_in = 1'b0;
  #`DELAY;
  
  
  /* test0 xor */
  op_code = 3'b011;
  a = 1'b0;
  b = 1'b0;
  c_in = 1'b0;
  #`DELAY;
  
  /* test1 xor */
  op_code = 3'b011;
  a = 1'b1;
  b = 1'b0;
  c_in = 1'b0;
  #`DELAY;
  
  /* test2 xor */
  op_code = 3'b011;
  a = 1'b0;
  b = 1'b1;
  c_in = 1'b0;
  #`DELAY;
  
  /* test3 xor */
  op_code = 3'b011;
  a = 1'b1;
  b = 1'b1;
  c_in = 1'b0;
	/*
	///////////////////////////////////AND
	a=1'b0;
	b=1'b0;
	op_code = 3'b000;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b1;
	op_code = 3'b000;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b0;
	op_code = 3'b000;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b0;
	b=1'b1;
	op_code = 3'b000;
	c_in=op_code[2];
	#`DELAY;
	
	///////////////////////////////////OR
	a=1'b0;
	b=1'b0;
	op_code = 3'b001;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b1;
	op_code = 3'b001;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b0;
	op_code = 3'b001;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b0;
	b=1'b1;
	op_code = 3'b001;
	c_in=op_code[2];
	#`DELAY;
	
	///////////////////////////////////ADD carry = 0
	a=1'b0;
	b=1'b0;
	op_code = 3'b010;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b1;
	op_code = 3'b010;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b0;
	op_code = 3'b010;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b0;
	b=1'b1;
	op_code = 3'b010;
	c_in=op_code[2];
	#`DELAY;
	
	///////////////////////////////////ADD carry = 1
	a=1'b0;
	b=1'b0;
	op_code = 3'b010;
	c_in=1'b1;
	#`DELAY;
	
	a=1'b1;
	b=1'b1;
	op_code = 3'b010;
	c_in=1'b1;
	#`DELAY;
	
	a=1'b1;
	b=1'b0;
	op_code = 3'b010;
	c_in=1'b1;
	#`DELAY;
	
	a=1'b0;
	b=1'b1;
	op_code = 3'b010;
	c_in=1'b1;
	#`DELAY;
	
	///////////////////////////////////SUBTRACT
	a=1'b0;
	b=1'b0;
	op_code = 3'b110;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b1;
	op_code = 3'b110;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b0;
	op_code = 3'b110;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b0;
	b=1'b1;
	op_code = 3'b110;
	c_in=op_code[2];
	#`DELAY;
	
	///////////////////////////////////XOR
	a=1'b0;
	b=1'b0;
	op_code = 3'b011;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b1;
	op_code = 3'b011;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b1;
	b=1'b0;
	op_code = 3'b011;
	c_in=op_code[2];
	#`DELAY;
	
	a=1'b0;
	b=1'b1;
	op_code = 3'b011;
	c_in=op_code[2];
	#`DELAY;
	*/
	
end

initial begin
	$monitor("a=%1b, b=%1b, op_code=%3b, c_in=%1b, result=%1b, c_out=%1b", a, b, op_code, c_in, result, c_out);
end
endmodule

/*
ALUop		Function
000		AND
001		OR
010		ADD
110		SUBTRACT
011		XOR
*/
