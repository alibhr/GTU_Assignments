module zero_cmp32bit(number, lt, eq, gt);

input [31:0] number;
output lt, eq, gt;
wire not_msb, not_eq;

not notMSB (not_msb, number[31]);

is_zero32bit comparator_helper (number, eq);

not notEQ (not_eq, eq);

and (lt, not_eq, number[31]);
and (gt, not_eq, not_msb);

endmodule
