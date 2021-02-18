module is_branch(beq, bne, Z, out);

input beq, bne, Z;
output out;
wire not_beq, not_bne, not_Z;
wire temp1, temp2;

not NEQ (not_beq, beq);
not NNE (not_bne, bne);
not NZ (not_Z, Z);

and3in nbeq_bne_nz (temp1, not_beq, bne, not_Z);
and3in beq_nbne_z (temp2, beq, not_bne, Z);

or result (out, temp1, temp2);

endmodule
