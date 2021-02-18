module zero_extend16_32(in ,out);

input [15:0] in;
output [31:0] out;

// There are some warning because some signal pins are permanent
// https://electronics.stackexchange.com/questions/39074/altera-optimisation-stuck-at-gnd-due-to-stuck-port-data-in
// https://stackoverflow.com/questions/22722812/vhdl-warning-warning-13024-output-pins-are-stuck-at-vcc-or-gnd-on-crucial-o
extender16_32 extender_ (1'b0, in, out);

endmodule
