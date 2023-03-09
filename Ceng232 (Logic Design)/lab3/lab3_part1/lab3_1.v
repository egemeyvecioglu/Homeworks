`timescale 1ns / 1ps

module ab(input A, input B, input clk, output reg Q);

    initial Q = 0;
	 
	 always @ (posedge clk) 
		 case({A,B})
         2'b00 :  Q <= Q;  
         2'b01 :  Q <= 1;  
         2'b10 :  Q <= 0;  
         2'b11 :  Q <= ~Q;  
      endcase 
endmodule

module ic1337(input I0,
              input I1,
              input I2,
              input clk,

              output Q0,
              output Q1,
              output Z);
				  wire w1;
				  wire w2;		  
				  assign w1 = ~I2 & I1 & I0;
				  assign w2 = I0~^(I1&~I2);
				  ab ab1(w1,I2,clk,Q0);
				  ab ab2(~I2,w2,clk,Q1);
				  assign Z = Q0 ^ Q1;
				  
endmodule
