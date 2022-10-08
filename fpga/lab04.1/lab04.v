module add_arr (
	sum,
	c_out, 
	a, 
	b, 
	c_in);
output wire [3:0] sum;
output wire c_out;
input wire [3:0] a;
input wire [3:0] b; 
input wire c_in;

	wire [4:0] w_c;
	genvar i;
	assign w_c[0]=c_in;
	assign c_out=w_c[4];
	
generate
	for (i=0; i<4; i=i+1) 
	begin: array
		assign sum[i] = (a[i] ^ b[i]) ^ w_c[i];
		assign w_c[i+1] = (a[i] & b[i]) | ((a[i] ^ b[i]) & w_c[i]);
	end
endgenerate

endmodule

module add_add (
	sum,
	c_out, 
	a, 
	b, 
	c_in);

output wire [3:0] sum;
output wire c_out;
input wire [3:0] a;
input wire [3:0] b; 
input wire c_in;

	assign {c_out, sum} = a+b+c_in;

endmodule

module cmp_err (
sum_1,
c_1,
sum_2,
c_2,
sum,
c_out,
err
);

output wire [3:0] sum;
output wire c_out;
output wire err;
input wire [3:0] sum_1;
input wire [3:0] sum_2; 
input wire c_1;
input wire c_2;

assign err = ! ({c_1,sum_1}=={c_2,sum_2});
assign {c_out,sum} = err ? 0:{c_1,sum_1};

endmodule

module lab04 (
	sum,
	c_out, 
	err,
	a, 
	b, 
	c_in,
	interference
);

output wire [3:0] sum;
output wire c_out, err;
input wire [3:0] a;
input wire [3:0] b; 
input wire c_in;
input wire [3:0]interference;

wire [3:0] w_s1, w_s2;
wire w_c1, w_c2;

add_arr ADD_1 (.sum(w_s1), .c_out(w_c1), .a(a), .b(b), .c_in(c_in));
add_add ADD_2 (.sum(w_s2), .c_out(w_c2), .a(a), .b(b), .c_in(c_in));
cmp_err ERR (.sum_1(w_s1 | interference), .c_1(w_c1), .sum_2(w_s2), .c_2(w_c2), .sum(sum), .c_out(c_out), .err(err));

endmodule
