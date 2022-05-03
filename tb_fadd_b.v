`timescale 1ns/1ns
module tb_fadd_b();
reg x, y, c_in;
wire s, c_out;

fadd_b u0(.x(x), .y(y), .c_in(c_in), .s(s), .c_out(c_out));

initial
begin
x=0; y=0; c_in=0;
#100; x=0; y=0; c_in=1;
#100; x=0; y=1; c_in=0;
#100; x=0; y=1; c_in=1;
#100; x=1; y=0; c_in=0;
#100; x=1; y=0; c_in=1;
#100; x=1; y=1; c_in=0;
#100; x=1; y=1; c_in=1;
end

endmodule
