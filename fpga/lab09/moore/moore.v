module moore
(
	input	clk, reset,
	input [1:0] in,
	output reg [1:0] out,
	output wire [1:0] debug_state
);

	reg [1:0] state;
	
	parameter A0 = 2'b00, A1 = 2'b01, A2 = 2'b10, A3 = 2'b11;
	parameter S0 = 2'b00, S1 = 2'b01, S2 = 2'b10, S3 = 2'b11;
	parameter Y0 = 2'b00, Y1 = 2'b01	, Y2 = 2'b10;
	
	assign debug_state = state;
	
	always @ (state) begin
		case (state)
			S0:
				out = Y0;
			S1:
				out = Y0;
			S2:
				out = Y1;
			S3:
				out = Y2;
		endcase
	end

	always @ (posedge clk or negedge reset) begin
		if (!reset)
			state <= S0;
		else
			case (state)
				S0: 
					begin
						case (in)
							A0: state <= S3;
							A1: state <= S0;
							A2: state <= S2;
							A3: state <= S1;
						endcase
					end
				S1:
					begin
						case (in)
							A0: state <= S0;
							A1: state <= S1;
							A2: state <= S2;
							A3: state <= S1;
						endcase
					end
				S2:
					begin
						case (in)
							A0: state <= S0;
							A1: state <= S2;
							A2: state <= S1;
							A3: state <= S2;
						endcase
					end
				S3:
					begin
						case (in)
							A0: state <= S1;
							A1: state <= S1;
							A2: state <= S1;
							A3: state <= S1;
						endcase
					end
			endcase
	end

endmodule
