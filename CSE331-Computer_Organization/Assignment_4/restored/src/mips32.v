module mips32(clk);

input clk;

wire [31:0] instruction_address, instruction, sign_extended, zero_extended, lower_extended, j_addr;
wire [31:0] mux1, mux5, mux6, mux7, mux8, mux9, mux10, mux11;
wire [4:0] mux2, mux3, mux4;
wire [2:0] alu_select;
wire [31:0] read_data1, read_data2, alu_result, data_from_dmem, n_result, adder1, shifted, adder2;
wire ignore_carry, ZeroBit, ignore_carry1, branch, JorJal, ignore_carry2;

//instruction seperator
wire [5:0] instruction31_26;
wire [4:0] instruction25_21, instruction20_16, instruction15_11;
wire [15:0] instruction15_0;
wire [25:0] instruction25_0;
wire [5:0] instruction5_0;

//control
wire  RegDst, Beq, Bne, MemRead, MemtoReg, MemWrite, ALUsrc, RegWrite1, RegWrite2, Lui, J, Jal, Ori, Jr;
wire [1:0] ALUop;

//program counter
PC pc (clk, mux1, instruction_address);

//instruction memory
instruction_memory inst_mem (clk, instruction_address, instruction);

//instruction seperator
instruction_separator instructionSeparator 
	(instruction, instruction31_26, instruction25_21, instruction20_16, instruction15_11, instruction15_0, instruction25_0, instruction5_0);

//control
control Control
	(instruction31_26, instruction5_0, RegDst, Beq, Bne, MemRead, MemtoReg, ALUop, MemWrite, ALUsrc, RegWrite1, RegWrite2, Lui, J, Jal, Jr, Ori);

mux_2_1_5bit MUX2 (RegDst, instruction20_16, instruction15_11, mux2);
mux_2_1_5bit MUX3 (Jal, instruction25_21, 5'b11111, mux3);
mux_2_1_5bit MUX4 (Ori, mux3, instruction20_16, mux4);

//sign extend
sign_extend16_32 S_Extend (instruction15_0, sign_extended);

//zero extend
zero_extend16_32 Z_Extend (instruction15_0, zero_extended);

//lui helper
lui_helper L_Extend (instruction15_0, lower_extended);

//jump address calculator
jump_addr J_ADDR (instruction_address[31:28], instruction25_0, j_addr);

//Alu control
ALU_Control alu_control(instruction5_0, ALUop, alu_select);

//register
mips_registers register (read_data1, read_data2, instruction25_21, instruction20_16, mux7, mux6, mux2, mux4, RegWrite1, RegWrite2, clk);

mux2_32 MUX10(Ori, sign_extended, zero_extended, mux10);
mux2_32 MUX8 (ALUsrc, read_data2, mux10, mux8);

//ALU
alu_32bit ALU (read_data1, mux8, alu_select, alu_result, ignore_carry, ZeroBit);

//Data memory
data_memory DataMemory (clk, alu_result, read_data2, MemWrite, MemRead, data_from_dmem);

new_instructions n_instructioins (alu_result, n_result);
mux2_32 MUX5 (MemtoReg, n_result, data_from_dmem, mux5);
mux2_32 MUX7 (Lui, mux5, lower_extended, mux7);

// PC+4
adder_32bit Adder1 (instruction_address, 32'b100, 1'b0, adder1, ignore_carry1);

mux2_32 MUX6 (Jal, alu_result, adder1, mux6);

shift_left2 Shifter (mux10, shifted);

adder_32bit Adder2 (adder1, shifted, 1'b0, adder2, ignore_carry2);

is_branch Branch (Beq, Bne, ZeroBit, branch);

mux2_32 MUX9 (branch, adder1, adder2, mux9);

or(JorJal, J, Jal);
mux2_32 MUX1 (JorJal, mux11, j_addr, mux1);

mux2_32 MUX11 (Jr, mux9, read_data1, mux11);

endmodule
