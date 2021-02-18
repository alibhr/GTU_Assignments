module jr_signal(op, funct, s);

input [5:0] op, funct;
output s;
wire op_resut, funct_result;

wire not_op0, not_op1, not_op2, not_op3, not_op4, not_op5;
wire not_funct0, not_funct1, not_funct2, not_funct4, not_funct5;

not NOT0_o (not_op0, op[0]);
not NOT1_o (not_op1, op[1]);
not NOT2_o (not_op2, op[2]);
not NOT3_o (not_op3, op[3]);
not NOT4_o (not_op4, op[4]);
not NOT5_o (not_op5, op[5]);

not NOT0_f (not_funct0, funct[0]);
not NOT1_f (not_funct1, funct[1]);
not NOT2_f (not_funct2, funct[2]);
not NOT4_f (not_funct4, funct[4]);
not NOT5_f (not_funct5, funct[5]);


and And1 (op_resut, not_op0, not_op1, not_op2, not_op3, not_op4, not_op5);

and And2 (funct_result, not_funct0, not_funct1, not_funct2, funct[3], not_funct4, not_funct5);

and result_and (s, op_resut, funct_result);

endmodule
