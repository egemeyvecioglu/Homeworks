`timescale 1ns / 1ps

module lab4_2(// INPUTS
              input wire      mode,
              input wire[2:0] opCode,
              input wire[3:0] value,
              input clk,
              input reset,
              // OUTPUTS
              output reg[9:0] result,
              output reg cacheFull,
              output reg invalidOp,
              output reg overflow);
	reg [9:0] p0;
	reg [9:0] p1;
	integer i;
	integer load_counter;
	integer execute_counter;
	integer start_execute;
	reg [2:0] Mem [0:31];
	reg [3:0] mValue [0:31];
    //================//
    // INITIAL BLOCK  //
    //================//
    //Modify the lines below to implement your design
    initial begin
        p0 = 10'b0000000000;
		p1 = 10'b0000000000;

		for(i=0;i<32;i=i+1)  begin Mem[i]= 3'b011; end
		for(i=0;i<32;i=i+1)  begin mValue[i]=5'b00000; end

		load_counter=0;
        execute_counter=0;

		result=0;
		invalidOp=0;
        start_execute=0;
	end

    //================//
    //      LOGIC     //
    //================//
    //Modify the lines below to implement your design
    always @(posedge clk or posedge reset)
    begin
		if(reset)
		begin
			cacheFull=0;
			load_counter=0;
			result=10'b0000000000;
			p0 = 10'b0000000000;
			p1 = 10'b0000000000;
			invalidOp=0;
			overflow=0;
            start_execute=0;
			execute_counter=0;
			for(i=0;i<32;i=i+1)  begin Mem[i]= 3'b011; end
			for(i=0;i<32;i=i+1)  begin mValue[i]=5'b00000; end

		end
		
		else
		begin

            if(!mode)
            begin
                cacheFull = load_counter==32?1'b1:1'b0;
                if(opCode == 3'b011 || opCode == 3'b111) invalidOp=1;
                else
                begin
                    invalidOp=0;
                    if(!cacheFull)
                    begin
                        Mem[load_counter]=opCode;
                        mValue[load_counter]=value;
                        load_counter = load_counter+1;				
                    end

                end
                cacheFull = load_counter==32?1'b1:1'b0;
            end
		
		
            if(mode && load_counter)
            begin
			overflow=0;
            case(Mem[execute_counter])
                    3'b000: 
                    begin
                    overflow = p0+mValue[execute_counter]>=1024?1:0;
                    result=p0+mValue[execute_counter];
                    p0=result;
                    end
                    
                    3'b001: 
                    begin
                    overflow = p0 + p1 + mValue[execute_counter]>=1024?1:0;
                    result= p0 + p1 + mValue[execute_counter];
                    p1=p0;
                    p0=result;
                    end
                    
                    3'b010: 
                    begin
                    overflow = p0 * p1 + mValue[execute_counter]>=1024?1:0;
                    result= p0 * p1 + mValue[execute_counter];
                    p1=p0;
                    p0=result;
                    end
                    				
					
                    3'b100: 
                    begin
                    result = p0[9]+p0[8]+p0[7]+p0[6]+p0[5]+p0[4]+p0[3]+p0[2]+p0[1]+p0[0];
                    p1=p0;
                    p0=result;				
                    end 
                    
                    3'b101:
                    begin				
                    for(i=0;i<10;i=i+1)
                    begin
                        result[i]=p0[9-i];
                    end
                    p1=p0;
                    p0=result;		
                    end
                    
                    3'b110:start_execute=mValue[execute_counter];
                    
            endcase
                execute_counter = execute_counter+1;
				execute_counter = execute_counter==load_counter?start_execute:execute_counter;
            end
		end
    end
endmodule
