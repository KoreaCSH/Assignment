module fadd_b(x, y, c_in, s, c_out);
input x, y, c_in;
output s, c_out;

reg s, c_out;

always@(x, y, c_in)
begin
 if ( x == 0 && y == 0 && c_in == 0 )
  begin
   s = 0; c_out = 0;
  end

 else if ( x == 0 && y == 0 && c_in == 1 )
  begin
   s = 1; c_out = 0;
  end

 else if ( x == 0 && y == 1 && c_in == 0 )
  begin
   s = 1; c_out = 0;
  end

 else if ( x == 0 && y == 1 && c_in == 1 )
  begin
   s = 0; c_out = 1;
  end

 else if ( x == 1 && y == 0 && c_in == 0 )
  begin
   s = 1; c_out = 0;
  end

 else if ( x == 1 && y == 0 && c_in == 1 )
  begin
   s = 0; c_out = 1;
  end

 else if ( x == 1 && y == 1 && c_in == 0 )
  begin
   s = 0; c_out = 1;
  end

 else if ( x == 1 && y == 1 && c_in == 1 )
  begin
   s = 1; c_out = 1;
  end

end

endmodule
