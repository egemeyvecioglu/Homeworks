`timescale 1ns / 1ps 
module lab3_2(
			input[4:0] smartCode,
			input CLK, 
			input lab, //0:Digital, 1:Mera
			input [1:0] mode, //00:exit, 01:enter, 1x: idle 
			output reg [5:0] numOfStuInMera,
			output reg [5:0] numOfStuInDigital,
			output reg restrictionWarnMera,//1:show warning, 0:do not show warning
			output reg isFullMera, //1:full, 0:not full
			output reg isEmptyMera, //1: empty, 0:not empty
			output reg unlockMera,	//1:door is open, 0:closed
			output reg restrictionWarnDigital,//1:show warning, 0:do not show warning
			output reg isFullDigital, //1:full, 0:not full
			output reg isEmptyDigital, //1: empty, 0:not empty
			output reg unlockDigital //1:door is open, 0:closed
	);
	 
	// You may declare your variables below	
	
	initial begin
			numOfStuInMera=0;
			numOfStuInDigital=0;
			restrictionWarnMera=0;
			isFullMera=0;
			isEmptyMera=1'b1;
			unlockMera=0;		
			restrictionWarnDigital=0;
			isFullDigital=0;
			isEmptyDigital=1'b1;
			unlockDigital=0;
	end
	integer a;
	integer i;
	always @(posedge CLK) begin
			unlockMera=0;
			unlockDigital=0;			
			
			restrictionWarnMera=0;
			restrictionWarnDigital=0;
			
			isEmptyDigital = numOfStuInDigital==0?1'b1:1'b0;
			isFullDigital = numOfStuInDigital==30?1'b1:1'b0;
			isEmptyMera = numOfStuInMera==0?1'b1:1'b0;
			isFullMera = numOfStuInMera==30?1'b1:1'b0;

			if(mode[0]==1 && mode[1]==0)
					begin
						if(lab==0)
							begin
								if(numOfStuInDigital <30)
									begin
										if(numOfStuInDigital <15) unlockDigital=1;
										else
											begin
												a=0;
												for(i=0;i<5;i=i+1)
													begin
														if(smartCode[i]==1) a=a+1;
													end
												a=a%2;
												if(a==1)unlockDigital=1;
												else restrictionWarnDigital=1;
											end
									end
								else isFullDigital=1;
								
								if(unlockDigital==1) 
								begin
								numOfStuInDigital=numOfStuInDigital+1;
								if(numOfStuInDigital==30) isFullDigital=1;
								if(numOfStuInDigital>0) isEmptyDigital=0;
								end
							end
						else
							begin
								if(numOfStuInMera < 30)
									begin
										if(numOfStuInMera <15) unlockMera=1;
										else
											begin
												a=0;
												for(i=0;i<5;i=i+1)
													begin
														if(smartCode[i]==1) a=a+1;
													end
												a=a%2;
												if(a==0)unlockMera=1;
												else restrictionWarnMera=1;
											end
									end
								else isFullMera=1;
								
								if(unlockMera==1) 
									begin
									numOfStuInMera=numOfStuInMera+1;
									if(numOfStuInMera==30) isFullMera=1;
									if(numOfStuInMera>0) isEmptyMera=0;
									end
								
							end
						
					end
				
			else if(mode[0]==0 && mode[1]==0)
				begin
					if(lab==0 && !isEmptyDigital)
						begin
							unlockDigital=1;
							numOfStuInDigital=numOfStuInDigital-1;
							if(numOfStuInDigital==0) isEmptyDigital=1;
							if(numOfStuInDigital<30) isFullDigital=0;
						end
					else if(lab==1 && !isEmptyMera)
						begin
							unlockMera=1;
							numOfStuInMera=numOfStuInMera-1;
							if(numOfStuInMera==0) isEmptyMera=1;
							if(numOfStuInMera<30) isFullMera=0;
						end
				end 

				
			
	
	
	end

	
endmodule

