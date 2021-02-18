module mips_registers(read_data1, read_data2, read_reg1, read_reg2, write_data1, write_data2, write_reg1, write_reg2, write_signal1, write_signal2, CLK);

output [31:0] read_data1, read_data2;
input [4:0] read_reg1, read_reg2, write_reg1, write_reg2;
input [31:0] write_data1, write_data2;
input write_signal1, write_signal2, CLK;

reg [31:0] registers [31:0];

assign read_data1 = registers[read_reg1];
assign read_data2 = registers[read_reg2];

always @(posedge CLK)begin
	if(write_signal1) begin
		registers[write_reg1] <= write_data1;
	end
	if(write_signal2) begin
		registers[write_reg2] <= write_data2;
	end
end

endmodule
