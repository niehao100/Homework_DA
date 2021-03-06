//By neil 
//2015.9.2
module Control(OpCode,  Funct, irq , reset,
                PCSrc,
                RegDst,  RegWrite,
                ALUSrc1, ALUSrc2,    ALUFun,
                Sign,
                MemRead, MemWrite,   MemtoReg, 
                ExtOp, LuOp);
 input [5:0] OpCode;
 input [5:0] Funct;
 input irq,reset;//,clk;
 output reg [2:0] PCSrc;
 output reg [1:0] RegDst;
 output reg RegWrite;
 output reg ALUSrc1;
 output reg ALUSrc2;
 output reg [5:0] ALUFun;
 output reg Sign;
 output reg MemWrite;
 output reg MemRead;
 output reg [1:0] MemtoReg;
 output reg ExtOp;
 output reg LuOp;

 
 initial begin
     PCSrc       <=   3'b0;
     RegDst      <=   2'b0;
     RegWrite    <=   1'b0;
     ALUSrc1     <=   1'b0;
     ALUSrc2     <=   1'b0;
     ALUFun      <=   6'b000000;
     Sign        <=   1'b0;
     MemWrite    <=   1'b0;
     MemRead     <=   1'b0;
     MemtoReg    <=   2'b0;
     ExtOp       <=   1'b1;
     LuOp        <=   1'b0;
 end


 always @(*) begin  
	  PCSrc       <=   3'b0;
     RegDst      <=   2'b0;
     RegWrite    <=   1'b0;
     ALUSrc1     <=   1'b0;
     ALUSrc2     <=   1'b0;
     ALUFun      <=   6'b000000;
     Sign        <=   1'b0;
     MemWrite    <=   1'b0;
     MemRead     <=   1'b0;
     MemtoReg    <=   2'b0;
     ExtOp       <=   1'b1;
     LuOp        <=   1'b0;
     if(reset==1) begin
         if(irq==1) begin//              
					 PCSrc<=3'b100;
           RegDst<=2'b11;
           RegWrite<=1'b1;
           MemtoReg<=2'b10;
         end
         else begin
             case(OpCode)
                 6'b0: begin//                 
                 RegWrite    <= 1'b1;                    
							case( Funct )
                         6'h20:begin//add
                             Sign<= 1'b1;
                         end

                         6'h21:begin//addu
                         end

                         6'h22:begin//sub
                             Sign<= 1'b1;
                             ALUFun<=6'b1;
                         end

                         6'h23:begin//subu
                             ALUFun<=6'b1;
                         end

                         6'h24:begin//and
                             ALUFun<=6'b011000;
                         end

                         6'h25:begin//or
                             ALUFun<=6'b011110;
                         end

                         6'h26:begin//xor
                             ALUFun<=6'b010110;
                         end

                         6'h27:begin//nor
                             ALUFun<=6'b011010;
                         end

                         6'h0 :begin//sll 
                             ALUSrc1<=1'b1;
                             ALUFun<=6'b100000;
                         end

                         6'h02:begin//srl
                             ALUSrc1<=1'b1;
                             ALUFun<=6'b100001;   
                         end

                         6'h03:begin//sra
                             ALUSrc1<=1'b1;
                             ALUFun<=6'b100011;
                         end

                         6'h2a:begin//slt
                             Sign<=1'b1;
                             ALUFun<=6'b110101;
                         end

                         6'h2b:begin//sltu
                             ALUFun<=6'b110101;
                         end

                         6'h08: begin//jr
                             PCSrc<= 3'b011;
                             RegWrite<=1'b0;    
                         end           

                         6'h09: begin//jalr
                             PCSrc <= 3'b011;
                             MemtoReg<=2;
                         end
								 default:begin
								 end
                     endcase
                 end

                 6'h23: begin//lw
                     RegWrite<=1'b1;
                     RegDst<=2'b01;
                     MemRead<=1'b1;
                     MemtoReg<=2'b01;
                     ALUSrc2<=1'b1;
                 end

                 6'h2b: begin//sw
                     MemWrite<=1'b1;
                     ALUSrc2<=1'b1;
                 end

                 6'h0f: begin//lui
                     RegWrite<=1'b1;
                     RegDst<=2'b01;
                     ALUSrc2<=1'b1;
                     LuOp<=1'b1;
                 end

                 6'h08: begin//addi
                     RegWrite<=1'b1;
                     RegDst<=2'b01;
                     ALUSrc2<=1'b1;
                     Sign<=1'b1;
                 end

                 6'h09: begin//addiu
                     RegWrite<=1'b1;
                     RegDst<=2'b01;
                     ALUSrc2<=1'b1;
                 end

                 6'h0c: begin//andi
                     RegWrite<=1'b1;
                     RegDst<=2'b01;
                     ALUSrc2<=1'b1;
                     ExtOp<=1'b0;
                     ALUFun<=6'b011000;
                 end

                 6'h0a: begin//slti
                     RegWrite<=1'b1;
                     RegDst<=2'b1;
                     ALUSrc2<=1'b1;
                     Sign<=1'b1;
                     ALUFun<=6'b110101;
                 end

                 6'h0b: begin//sltiu
                     RegWrite<=1'b1;
                     RegDst<=2'b1;
                     ALUSrc2<=1'b1;
                     ALUFun<=6'b110101;
                 end

                 6'h04: begin//beq
                     PCSrc<=3'b001;
                     Sign<=1'b1;
                     ALUFun<=6'b110011;
                 end 

                 6'h05: begin//bne
                     PCSrc<=3'b001;
                     Sign<=1'b1;
                     ALUFun<=6'b110001;
                 end 

                 6'h06: begin//blez
                     PCSrc<=3'b001;
                     Sign<=1'b1;
                     ALUFun<=6'b111101;
                 end 

                 6'h07: begin//bgtz
                     PCSrc<=3'b001;
                     Sign<=1'b1;
                     ALUFun<=6'b111111;
                 end
                 6'h01: begin//bgez
                     PCSrc<=3'b001;
                     Sign<=1'b1;
                     ALUFun<=6'b111001;
                 end

                 6'h02: begin//j
                     PCSrc<=3'b010;
                 end 

                 6'h03: begin//jal
                     RegWrite<=1'b1;
                     PCSrc<=3'b010;
                     MemtoReg<=2'b10;
                     RegDst<=2'b10;
                 end 

                 default: begin                    
					PCSrc<=3'b101;
                     RegDst<=2'b11;
                     RegWrite<=1'b1;
                     MemtoReg<=2'b10;
                 end
             endcase
         end
     end
 end
endmodule



