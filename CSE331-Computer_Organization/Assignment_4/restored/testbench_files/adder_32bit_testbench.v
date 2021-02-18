`define DELAY 20
module adder_32bit_testbench();

reg [31:0] a, b;
reg carry_in;
wire [31:0] out;
wire carry_out;

adder_32bit test_adder (a, b, carry_in, out, carry_out);

initial begin
	a = 32'b00000000000000000000000000000010;
	b = 32'b00000000000000000000000000000011;
	carry_in = 1'b0;
	#`DELAY;

	a = 32'b11111111111111111111111111111111;
	b = 32'b11111111111111111111111111111111;
	carry_in = 1'b0;
	#`DELAY;

	a = 32'b01001000010001000000100101000010;
	b = 32'b00100010001000100000100000100011;
	carry_in = 1'b0;
	#`DELAY;
	
	a = 32'b11001000010001000100100101000010;
	b = 32'b10100010001000100000100110100011;
	carry_in = 1'b0;
	#`DELAY;

end

initial begin
	$monitor("time=%2d, carry_out=%1b, out=%32b", $time, carry_out, out);
end

endmodule
