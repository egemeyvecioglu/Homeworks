`timescale 1ns / 1ps
module lab4ROM (input [3:0] romAddr, output reg[4:0] romOutput);
	
	reg [4:0] Mem [0:15];
	
	initial
	begin
	Mem[4'b0000]=5'b00000;
	Mem[4'b0001]=5'b00001;
	Mem[4'b0010]=5'b00110;
	Mem[4'b0011]=5'b00111;
	Mem[4'b0100]=5'b01011;
	Mem[4'b0101]=5'b01100;
	Mem[4'b0110]=5'b01101;
	Mem[4'b0111]=5'b01110;
	Mem[4'b1000]=5'b11101;
	Mem[4'b1001]=5'b11110;
	Mem[4'b1010]=5'b11111;
	Mem[4'b1011]=5'b10000;
	Mem[4'b1100]=5'b10111;
	Mem[4'b1101]=5'b11000;
	Mem[4'b1110]=5'b11001;
	Mem[4'b1111]=5'b11010;
	end
	
	always@(romAddr)
	begin
	romOutput=Mem[romAddr];
	end

endmodule
																							
module lab4RAM (
	input ramMode, //0:read, 1:write
	input [3:0] ramAddr, 
	input [4:0] ramInput,
	input  ramOp, //0:polynomial, 1:derivative
	input [1:0] ramArg,  //00:+1, 01:+2, 10:-1, 11:-2
	input CLK, 
	output reg [8:0] ramOutput);
	
	reg [8:0] Mem [0:15];
	integer i;
	integer number;
	integer sum;
	initial
	begin
	for(i=0;i<16;i=i+1)Mem[i]=9'b000000000;
	end
	
	initial ramOutput = 9'b000000000;
	
	always@(ramMode)
	begin
		if(!ramMode) ramOutput = Mem[ramAddr];
	end
	
	always@(posedge CLK)
	begin
	if(ramMode)
	begin
		number=(-1**ramArg[1])*(ramArg[0]+1);
		sum=0;
		if(ramOp)
		begin
			for(i=1;i<5;i=i+1)
			begin
				sum=sum+(-1**(ramInput[i]))* i * ((number)**(i-1));
			end
		end
		
		else
		begin
			for(i=0;i<5;i=i+1)
			begin
				sum=sum+(-1**ramInput[i]) * ((number)**i);
			end

		end

		Mem[ramAddr][8] = sum<0?1:0;
		sum = sum<0?-sum:sum;
		Mem[ramAddr][7:0] = sum;
	end
	
	end


endmodule


module polMEM(input mode, input [3:0] memAddr, input op, input [1:0] arg, input CLK, output wire [8:0] memOutput);

	/*Don't edit this module*/
	wire [4:0]  romOutput;

	lab4ROM RO(memAddr, romOutput);
	lab4RAM RA(mode, memAddr, romOutput, op, arg, CLK, memOutput);



endmodule
