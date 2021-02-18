module adder_full(a, b, carry_in, out, carry_out);

input a, b, carry_in;
output out, carry_out;
wire temp, carry1, carry2;

adder_half f_half_adder (a, b, temp, carry1);
adder_half s_half_adder (temp, carry_in, out, carry2);

or carry_or (carry_out, carry1, carry2);

endmodule
