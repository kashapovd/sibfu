module mealy
(
	input	clk, reset,
	input wire [1:0] in,
	output reg [1:0] out,
	output wire [1:0] debug_state
);

	reg [1:0] state;

	parameter A0 = 2'b00, A1 = 2'b01, A2 = 2'b10, A3 = 2'b11;
	parameter S0 = 2'b00, S1 = 2'b01, S2 = 2'b10, S3 = 2'b11;
	parameter Y0 = 2'b00, Y1 = 2'b01	, Y2 = 2'b10, Y3 = 2'b11;
	
	assign debug_state = state;

	always @ (posedge clk or negedge reset) begin
	if (!reset)
		state <= S0;
	else
		case (state)
			S0: 
				begin
					case (in)
						A0: state <= S0;
						A1: state <= S1;
						A2: state <= S0;
						A3: state <= S2;
					endcase
				end
			S1:
				begin
					case (in)
						A0: state <= S1;
						A1: state <= S1;
						A2: state <= S1;
						A3: state <= S2;
					endcase
				end
			S2:
				begin
					case (in)
						A0: state <= S0;
						A1: state <= S2;
						A2: state <= S0;
						A3: state <= S3;
					endcase
				end
			S3:
				begin
					case (in)
						A0: state <= S2;
						A1: state <= S0;
						A2: state <= S0;
						A3: state <= S3;
					endcase
				end
		endcase
	end
	
	always @ (state or in)
	begin
			case (state)
				S0:
					begin
						case (in)
							A0: out <= Y0;
							A1: out <= Y0;
							A2: out <= Y1;
							A3: out <= Y3;
						endcase
					end
				S1:
					begin
						case (in)
							A0: out <= Y1;
							A1: out <= Y2;
							A2: out <= Y3;
							A3: out <= Y1;
						endcase
					end
				S2:
					begin
						case (in)
							A0: out <= Y1;
							A1: out <= Y2;
							A2: out <= Y0;
							A3: out <= Y0;
						endcase
					end
				S3:
					begin
						case (in)
							A0: out <= Y1;
							A1: out <= Y2;
							A2: out <= Y3;
							A3: out <= Y1;
						endcase
					end
			endcase
	end

endmodule
