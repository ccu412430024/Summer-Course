`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/06/2024 12:57:13 PM
// Design Name: 
// Module Name: testbench
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_Min_Tree;

    // 宣告輸入為reg，輸出為wire
    reg clk;
    reg reset;
    reg [4:0] m0, m1, m2, m3, m4, m5, m6, m7;
    wire [4:0] min1, min2;
    wire [2:0] idx;

    // 實例化 Min_Tree 模組
    Min_Tree uut (
        .clk(clk),
        .reset(reset),
        .m0(m0), .m1(m1), .m2(m2), .m3(m3),
        .m4(m4), .m5(m5), .m6(m6), .m7(m7),
        .min1(min1),
        .min2(min2),
        .idx(idx)
    );

    // 時鐘產生
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 時鐘週期為10個時間單位
    end

    // 測試激勵
    initial begin
        // 初始化輸入
        reset = 1;
        m0 = 5'b00000; m1 = 5'b00001; m2 = 5'b00010; m3 = 5'b00011;
        m4 = 5'b00100; m5 = 5'b00101; m6 = 5'b00110; m7 = 5'b00111;
        
        // 等待全域重置完成
        #10;
        reset = 0;
        
        // 測試案例1: 輸入為排序好的值
        m0 = 5'b01010; m1 = 5'b01000; m2 = 5'b00111; m3 = 5'b01111;
        m4 = 5'b00101; m5 = 5'b01100; m6 = 5'b00001; m7 = 5'b01110;
        #10;
        
        // 測試案例2: 隨機輸入
        m0 = 5'b11010; m1 = 5'b10111; m2 = 5'b00011; m3 = 5'b11101;
        m4 = 5'b00101; m5 = 5'b01000; m6 = 5'b01111; m7 = 5'b10000;
        #10;
        
        // 測試案例3: 重複值輸入
        m0 = 5'b01010; m1 = 5'b01010; m2 = 5'b00100; m3 = 5'b00100;
        m4 = 5'b11000; m5 = 5'b11000; m6 = 5'b11110; m7 = 5'b11110;
        #10;

        // 測試案例4: 所有輸入值相同
        m0 = 5'b01111; m1 = 5'b01111; m2 = 5'b01111; m3 = 5'b01111;
        m4 = 5'b01111; m5 = 5'b01111; m6 = 5'b01111; m7 = 5'b01111;
        #10;

        // 測試案例5: 最小值和最大值的邊界情況
        m0 = 5'b00000; m1 = 5'b11111; m2 = 5'b11111; m3 = 5'b11111;
        m4 = 5'b11111; m5 = 5'b11111; m6 = 5'b11111; m7 = 5'b11111;
        #10;

        // 結束模擬
        $finish;
    end

endmodule
