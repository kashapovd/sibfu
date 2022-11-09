// module memory
// #(parameter N=4)
// (
// 	input clk, enable, reset,
// 	input [N-1:0] d,
// 	output reg [N-1:0] q
// );
//
// 	always @ (posedge clk or negedge reset)
// 	begin
// 		if (!reset)
// 		begin
// 			q <= {N{1'b0}};
// 		end
// 		else if (enable == 1'b1)
// 		begin
// 			q <= d;
// 		end
// 	end
//
// endmodule

// module memory
// #(parameter DATA_WIDTH=4, parameter ADDR_WIDTH=4)
// (
// 	input [ADDR_WIDTH-1:0] addr,
// 	input clk,
// 	output reg [DATA_WIDTH-1:0] q
// );
//
// 	reg [DATA_WIDTH-1:0] rom[2**ADDR_WIDTH-1:0];
//
// 	initial
// 	begin
// 		rom[4'b0000] = 4'b1001;
// 		rom[4'b0001] = 4'b0100;
// 		rom[4'b0010] = 4'b0001;
// 		rom[4'b0011] = 4'b1011;
// 		rom[4'b0100] = 4'b1010;
// 	end
//
// 	always @ (posedge clk)
// 	begin
// 		q <= rom[addr];
// 	end
//
// endmodule

module memory
#(parameter DATA_WIDTH=4, parameter ADDR_WIDTH=4)
(
	input [(DATA_WIDTH-1):0] data,
	input [(ADDR_WIDTH-1):0] addr,
	input we, clk, reset,
	output [(DATA_WIDTH-1):0] q
);

	reg [DATA_WIDTH-1:0] ram[2**ADDR_WIDTH-1:0];
	reg [ADDR_WIDTH-1:0] addr_reg;
	
	always @ (posedge clk or negedge reset)
	begin		
		if (!reset) 
			addr_reg <= {ADDR_WIDTH{1'b0}};
		else
		begin
			addr_reg <= addr;
			if (we)
				ram[addr] <= data;
		end
	end
	
	assign q = ram[addr_reg];

endmodule

