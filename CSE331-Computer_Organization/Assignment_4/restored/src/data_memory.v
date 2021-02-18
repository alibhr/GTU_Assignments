module data_memory(clk, address, write_data, mem_write, mem_read, read_data);

input [31:0] address, write_data;
input mem_write, mem_read, clk;
output reg [31:0] read_data;

reg [31:0] temp;

reg [7:0] data_regs [47:0];

always @* begin
	temp[ 7: 0] = data_regs[address + 32'b11];
	temp[15: 8] = data_regs[address + 32'b10];
	temp[23:16] = data_regs[address + 32'b01];
	temp[31:24] = data_regs[address];
	
	read_data = mem_read ? temp : 32'b00;

end


always @(posedge clk) begin
	
	if(mem_write) begin
		data_regs[address] <= write_data[31:24];
		data_regs[address + 32'b01] <= write_data[23:16];
		data_regs[address + 32'b10] <= write_data[15: 8];
		data_regs[address + 32'b11] <= write_data[ 7: 0];
	end
	
end

endmodule
