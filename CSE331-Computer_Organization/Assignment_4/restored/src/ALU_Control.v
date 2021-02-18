module ALU_Control(fun, alu_op, alu_select);

input [5:0] fun;
input [1:0] alu_op;
output [2:0] alu_select;
wire not_op1, not_op0, not_f2;
wire and0_0, and0_1, and1_0, and1_1, and2_0, and2_1, and2_2;

not NOT_OP1 (not_op1, alu_op[1]);
not NOT_OP0 (not_op0, alu_op[0]);
not NOT_F2 (not_f2, fun[2]);

//s2
and AND00 (and0_0, not_op1, alu_op[0]);
and AND01 (and0_1, alu_op[1], not_op0, not_f2, fun[1]);
or OR0 (alu_select[2], and0_0, and0_1);

//s1
and AND10 (and1_0, not_op0, not_f2);
and AND11 (and1_1, not_op0, fun[1]);
or OR1 (alu_select[1], and1_0, and1_1, not_op1);

//s0
and AND20 (and2_0, alu_op[1], fun[0]);
and AND21 (and2_1, alu_op[1], fun[2], fun[1]);
and AND22 (and2_2, alu_op[1], alu_op[0]);
or OR2 (alu_select[0], and2_0, and2_1, and2_2);

endmodule
