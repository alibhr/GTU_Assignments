module PC(clk, new_value, current_value);

input clk;
input [31:0] new_value;
output [31:0] current_value;

reg[31:0] program_counter;

assign current_value = program_counter;

initial begin
	program_counter = 32'b00;
end

always @(posedge clk) begin
	program_counter <= new_value;
end

endmodule
