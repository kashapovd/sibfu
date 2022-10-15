module counter_with_saturation
#(parameter N=4)
(
	input clk, enable, reset,
	input [N-1:0] sr_max,
	output [N-1:0] sr_out
);

	// Declare the shift register
	reg [N-1:0] sr;
	reg [N-1:0] max;

	// Shift everything over, load the incoming bit
	always @ (posedge clk or negedge reset)
	begin
		if (!reset)
		begin
			// Load N zeros 
			sr <= {N{1'b0}};
		end
		else if (enable == 1'b1)
		begin
			max <= sr_max;
			sr <= sr + 1'b1;
			if (sr == max)
			begin
				sr <= {N{1'b0}};
			end
		end
	end

	// Catch the outgoing bit
	assign sr_out = sr;

endmodule