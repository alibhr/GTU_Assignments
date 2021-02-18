`define DELAY 20
module mux_2_1_5bit_testbench();

reg select;
reg [4:0] input1, input2;
wire [4:0] out;

mux_2_1_5bit mux_2_1_5bit_test (select, input1, input2, out);

initial begin
	input1 = 5'b00111;
	input2 = 5'b11000;
	select = 1'b0;
	#`DELAY;
	
	input1 = 5'b00111;
	input2 = 5'b11000;
	select = 1'b1;
	#`DELAY;
end

initial begin
	$monitor("select=%1b, input1=%5b, input2=%5b, out=%5b", select, input1, input2, out);
end

endmodule
