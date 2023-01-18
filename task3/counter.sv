module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input logic clk,
    input logic rst,
    input logic en,
    input logic param_value,
    output logic [WIDTH-1:0] count  // count output 
);

always_ff @(posedge clk)
    //if (rst) count <= {WIDTH{1'b0}};
    if (rst) count <= param_value;
    else     count <= count + {{WIDTH-1{1'b0}},en};
    
endmodule
