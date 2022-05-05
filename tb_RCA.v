`timescale 1ns/1ns
module tb_RCA();
reg[3:0] x, y;
reg c_in;
wire[3:0] s;
wire c_out;

RCA u0(.x(x), .y(y), .c_in(c_in), .s(s), .c_out(c_out));

initial
begin
c_in = 0; 
x = 4'b0000; y = 4'b0000;
#100; x = 4'b0001; y = 4'b0001;
#100; x = 4'b0011; y = 4'b0011;
#100; x = 4'b0100; y = 4'b0110;
#100; x = 4'b0101; y = 4'b0111;
#100; x = 4'b0110; y = 4'b0110;
#100; x = 4'b0111; y = 4'b1000;
#100; x = 4'b1000; y = 4'b1001;
#100; x = 4'b1001; y = 4'b1011;
#100; x = 4'b1011; y = 4'b1100;
#100; x = 4'b1110; y = 4'b1101;
#100; x = 4'b1111; y = 4'b1111;
end

endmodule

