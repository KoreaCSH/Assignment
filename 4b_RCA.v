module RCA(x, y, c_in, s, c_out);
input[3:0] x, y;
input c_in;
output[3:0] s;
output c_out;

wire c1, c2, c3;

fadd_b u0(.x(x[0]), .y(y[0]), .c_in(c_in), .s(s[0]), .c_out(c1));
fadd_b u1(.x(x[1]), .y(y[1]), .c_in(c1), .s(s[1]), .c_out(c2));
fadd_b u2(.x(x[2]), .y(y[2]), .c_in(c2), .s(s[2]), .c_out(c3));
fadd_b u3(.x(x[3]), .y(y[3]), .c_in(c3), .s(s[3]), .c_out(c_out));

endmodule
