module instruction_memory(clk, address, instruction);

input clk;
input [31:0] address;
output reg [31:0] instruction;

reg [7:0] my_memory [87:0] ;

always @* begin
	instruction[ 7: 0] <= my_memory[address + 32'b11];
	instruction[15: 8] <= my_memory[address + 32'b10];
	instruction[23:16] <= my_memory[address + 32'b01];
	instruction[31:24] <= my_memory[address];
end
	
endmodule
