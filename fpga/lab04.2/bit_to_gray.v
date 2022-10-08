module bit_to_gray 
(	
	input [3:0] bin,
	output [3:0] gray
);
	
	assign gray[3] = bin[3];
	assign gray[2] = bin[2] ^ bin[3];
	assign gray[1] = bin[1] ^ bin[2];
	assign gray[0] = bin[0] ^ bin[1];
	
endmodule