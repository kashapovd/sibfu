module lab06
#(parameter BIT = 4, OPCODE = 4)
(
   output reg [BIT-1:0] c,
	output reg flag,
	input [OPCODE-1:0] instr,
	input [BIT-1:0] a,
	input [BIT-1:0] b
);
parameter
NOP = 	4'b0000,
NOT = 	4'b0001,
LSHIFT = 4'b0010,
RSHIFT = 4'b0011,
NEG = 	4'b0100, /* новая операция -а */
LAND = 	4'b1001,
LOR = 	4'b1010,
ADD = 	4'b1011,
SUB = 	4'b1100,
XOR = 	4'B1101,
INC = 	4'B1110,
XNOR = 	4'B1111;

	always @ (*) 
		case (instr)
		NOP: {flag,c} = 0;
		NOT: {flag, c} = {1'b0, ~a};
		LSHIFT: {flag, c} = {a, 1'b0};
		RSHIFT: {c, flag} = {1'b0, a};		
		LAND: {flag, c} = {1'b0, a & b}; 
		LOR: {flag, c} = {1'b0, a | b};
		ADD: {flag, c} = a+b;
		SUB: {flag, c} = a-b;
		NEG: {flag, c} = {1'b0, -a};
		XOR: {flag, c} = {1'b0, a ^ b};
		INC: {flag, c} = a+1;
		XNOR: {flag, c} = {1'b0, ~(a ^ b)};
		default: {flag, c} = {BIT+1{1'b0}}; 
  endcase	
endmodule