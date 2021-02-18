`define DELAY 20
module mips32_testbench();

reg clk;

mips32 mips32_test (clk);

initial begin
	clk = 0;
	$readmemb("registers.txt", mips32_test.register.registers);
	$readmemb("data_memory.txt", mips32_test.DataMemory.data_regs);
	$readmemb("instruction_memory.txt", mips32_test.inst_mem.my_memory);
	
	#`DELAY;
	
	#1000 $writememb("register_out.txt", mips32_test.register.registers);
	#1000 $writememb("data_out.txt", mips32_test.DataMemory.data_regs);
end

initial begin
	//$monitor("pc=%32b, mux1=%32b, JorJal=%1b, mux9=%32b, j_addr=%32b, mux1=%32b", mips32_test.instruction_address, mips32_test.mux1,mips32_test.JorJal, mips32_test.mux9, mips32_test.j_addr, mips32_test.mux1);
	$monitor("instruction31_26=%6b, RegDst=%1b, Beq=%1b, Bne=%1b, MemRead=%1b, MemtoReg=%1b, ALUop=%2b, MemWrite=%1b, ALUsrc=%1b, RegWrite1=%1b, RegWrite2=%1b, Lui=%1b, J=%1b, Jal=%1b, Jr=%1b, Ori=%1b, pc=%32b"
		,mips32_test.instruction31_26, mips32_test.RegDst, mips32_test.Beq, mips32_test.Bne, mips32_test.MemRead, mips32_test.MemtoReg, mips32_test.ALUop, mips32_test.MemWrite, mips32_test.ALUsrc, mips32_test.RegWrite1, mips32_test.RegWrite2, mips32_test.Lui, mips32_test.J, mips32_test.Jal, mips32_test.Jr, mips32_test.Ori, mips32_test.instruction_address);
	//$monitor("branch=%1b, adder1=%32b, adder2=%32b, mux9=%32b", mips32_test.branch, mips32_test.adder1, mips32_test.adder2, mips32_test.mux9);
	//$monitor("instruction_address=%32b, adder1=%32b, shifted=%32b, adder2=%32b", mips32_test.instruction_address, mips32_test.adder1, mips32_test.shifted, mips32_test.adder2);
	//$monitor("Ori=%1b, sign_extended=%32b, zero_extended=%32b, mux10=%32b", mips32_test.Ori, mips32_test.sign_extended, mips32_test.zero_extended, mips32_test.mux10);
	//$monitor("ALUsrc=%1b, read_data2=%32b, mux10=%32b, mux8=%32b, zero=%1b",mips32_test.ALUsrc, mips32_test.read_data2, mips32_test.mux10, mips32_test.mux8, mips32_test.ZeroBit);
	//$monitor("mux10=%32b, shifted=%32b", mips32_test.mux10, mips32_test.shifted);
	//$monitor("adder1=%32b, shifted=%32b, adder2=%32b, ignore_carry2=%1b", mips32_test.adder1, mips32_test.shifted, mips32_test.adder2, mips32_test.ignore_carry2);
	//$monitor("instruction_address=%32b", mips32_test.instruction_address);
	//$monitor("time = %2d, clk=%1b", $time, clk);
end

always begin
	#10 clk = ~clk;
end

endmodule
