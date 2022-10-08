module bin_to_gray 
(	
	input [3:0] bin,
	output reg [3:0] gray
);
	
	always @ (*) begin
		gray[3] = bin[3];
		gray[2] = bin[2] ^ bin[3];
		gray[1] = bin[1] ^ bin[2];
		gray[0] = bin[0] ^ bin[1];
	end
	
endmodule