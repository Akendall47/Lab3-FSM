module lfsr_7 (
    input  logic       clk,
    input  logic       rst,
    input  logic       en,
    output logic [6:0] data_out
);

    logic [6:0] sreg;

    always_ff @(posedge clk or posedge rst) begin
        if (rst)
            sreg <= 7'b1;
        else if (en)
            // Right shift; feedback = bit2 ^ bit6 (from test)
            sreg <= {sreg[5:0], sreg[2] ^ sreg[6]};

    end

    assign data_out = sreg;

endmodule
