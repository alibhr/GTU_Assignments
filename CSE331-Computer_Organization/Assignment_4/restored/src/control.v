module control
(op, funct, RegDst, Beq, Bne, MemRead, MemtoReg, ALUop, MemWrite, ALUsrc, RegWrite1, RegWrite2, Lui, J, Jal, Jr, Ori);

input [5:0] op, funct;
output  RegDst, Beq, Bne, MemRead, MemtoReg, MemWrite, ALUsrc, RegWrite1, RegWrite2, Lui, J, Jal, Jr, Ori;
output [1:0] ALUop;
wire lw, sw, ori, lui, beq, bne, r_type, j, jal, jr, op_resut, funct_result;
wire not_op0, not_op1, not_op2, not_op3, not_op4, not_op5;
wire not_funct0, not_funct1, not_funct2, not_funct4, not_funct5;
wire not_jr;

not (not_op0, op[0]);
not (not_op1, op[1]);
not (not_op2, op[2]);
not (not_op3, op[3]);
not (not_op4, op[4]);
not (not_op5, op[5]);

not NOT0_f (not_funct0, funct[0]);
not NOT1_f (not_funct1, funct[1]);
not NOT2_f (not_funct2, funct[2]);
not NOT4_f (not_funct4, funct[4]);
not NOT5_f (not_funct5, funct[5]);

and and_LW (lw, not_jr, op[5], not_op4, not_op3, not_op2, op[1], op[0]);

and6in and_SW (sw, op[5], not_op4, op[3], not_op2, op[1], op[0]);

and and_ORI (ori, not_jr, not_op5, not_op4, op[3], op[2], not_op1, op[0]);

and and_LUI (lui, not_jr, not_op5, not_op4, op[3], op[2], op[1], op[0]);

and6in and_BEQ (beq, not_op5, not_op4, not_op3, op[2], not_op1, not_op0);

and6in and_BNE (bne, not_op5, not_op4, not_op3, op[2], not_op1, op[0]);

and and_r_type (r_type, not_jr, not_op5, not_op4, not_op3, not_op2, not_op1, not_op0);

and6in and_J (j, not_op5, not_op4, not_op3, not_op2, op[1], not_op0);

and and_JAL (jal, not_jr, not_op5, not_op4, not_op3, not_op4, op[1], op[0]);


and And1 (op_resut, not_op0, not_op1, not_op2, not_op3, not_op4, not_op5);
and And2 (funct_result, not_funct0, not_funct1, not_funct2, funct[3], not_funct4, not_funct5);
and and_JR (jr, op_resut, funct_result);

not NOT_JR (not_jr, jr);

or or_RegDst (RegDst, r_type, 1'b0);
or or_Beq (Beq, beq, 1'b0);
or or_Bne (Bne, bne, 1'b0);
or or_MemRead (MemRead, lw, 1'b0);
or or_MemtoReg (MemtoReg, lw, 1'b0);
or or_ALUop0 (ALUop[0], ori, beq, bne);
or or_ALUop1 (ALUop[1], ori, r_type);
or or_MemWrite (MemWrite, sw, 1'b0);
or or_ALUsrc (ALUsrc, lw, sw, ori);
or or_RegWrite1 (RegWrite1, lw, lui, r_type);
or or_RegWrite2 (RegWrite2, ori, r_type, jal);
or or_Lui (Lui, lui, 1'b0);
or or_J (J, j, 1'b0);
or or_Jal (Jal, jal, 1'b0);
or or_Ori (Ori, ori, 1'b0);
or or_JR (Jr, jr, 1'b0);

endmodule
