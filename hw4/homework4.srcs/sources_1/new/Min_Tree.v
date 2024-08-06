`timescale 100ps / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/05/2024 09:09:13 PM
// Design Name: Min_Tree
// Module Name: Min_Tree
// Project Name: homework3
// Target Devices: xc7k70tfbv676-1
// Tool Versions: Vivado 2024.1
// Description: A module to find the minimum 1, minimum 2, and minimum 1’s index
// 
// Dependencies: 
// 
// Revision:
// Revision 1.01
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Min_Tree (
    input [4:0] m0, m1, m2, m3, m4, m5, m6, m7,
    output reg [4:0] min1, min2,
    output reg [2:0] idx
);

    reg [4:0] min_temp1, min_temp2;
    reg [2:0] min_idx;
    reg [7:0] valid; // Used to track the values that have been processed

    always @(*) begin
        // Initialize the minimum values to the maximum possible 5-bit value
        min_temp1 = 5'b11111; // Set to the maximum value
        min_temp2 = 5'b11111; // Set to the maximum value
        min_idx = 3'b000;   // Initialize the index for the minimum value
        valid = 8'b00000000;    // Reset the valid bits

        // Find the minimum value and its index
        if (m0 < min_temp1) begin
            min_temp1 = m0;
            min_idx = 3'b000;
        end
        if (m1 < min_temp1) begin
            min_temp1 = m1;
            min_idx = 3'b001;
        end
        if (m2 < min_temp1) begin
            min_temp1 = m2;
            min_idx = 3'b010;
        end
        if (m3 < min_temp1) begin
            min_temp1 = m3;
            min_idx = 3'b011;
        end
        if (m4 < min_temp1) begin
            min_temp1 = m4;
            min_idx = 3'b100;
        end
        if (m5 < min_temp1) begin
            min_temp1 = m5;
            min_idx = 3'b101;
        end
        if (m6 < min_temp1) begin
            min_temp1 = m6;
            min_idx = 3'b110;
        end
        if (m7 < min_temp1) begin
            min_temp1 = m7;
            min_idx = 3'b111;
        end

        // Mark the minimum value as processed
        valid[min_idx] = 1'b1;
        
        // Find the second minimum value
        if (valid[0] == 1'b0 && m0 < min_temp2) min_temp2 = m0;
        if (valid[1] == 1'b0 && m1 < min_temp2) min_temp2 = m1;
        if (valid[2] == 1'b0 && m2 < min_temp2) min_temp2 = m2;
        if (valid[3] == 1'b0 && m3 < min_temp2) min_temp2 = m3;
        if (valid[4] == 1'b0 && m4 < min_temp2) min_temp2 = m4;
        if (valid[5] == 1'b0 && m5 < min_temp2) min_temp2 = m5;
        if (valid[6] == 1'b0 && m6 < min_temp2) min_temp2 = m6;
        if (valid[7] == 1'b0 && m7 < min_temp2) min_temp2 = m7;

        // Assign the final minimum values and the index of the minimum value
        min1 = min_temp1;
        min2 = min_temp2;
        idx = min_idx;
    end
endmodule
