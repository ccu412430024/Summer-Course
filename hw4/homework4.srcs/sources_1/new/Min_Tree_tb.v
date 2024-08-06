`timescale 100ps / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/08/03 14:06:02
// Design Name: 
// Module Name: Min_Tree_tb
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

module Min_Tree_tb();
    parameter PERIOD	= 20;
    reg [4:0] m0, m1, m2, m3, m4, m5, m6, m7;
    wire [4:0] min1;
    wire [4:0] min2;
    wire [2:0] min1_index;
    reg [9:0] err_cnt;
    reg [9:0] err_cnt_new;
    integer k;

    parameter test_n = 100;
    
    //test module
    Min_Tree Min_Tree1( .m0(m0), .m1(m1), .m2(m2), .m3(m3), .m4(m4), .m5(m5), .m6(m6), .m7(m7), .min1(min1), .min2(min2), .idx(min1_index)); 
    
    task random_generate;
        output [4:0] m0, m1, m2, m3, m4, m5, m6, m7;

        begin
            m0 = {$random}%32;
            m1 = {$random}%32;
            m2 = {$random}%32;
            m3 = {$random}%32;
            m4 = {$random}%32;
            m5 = {$random}%32;
            m6 = {$random}%32;
            m7 = {$random}%32;
        end
    endtask

    task check;
        input [4:0] m0, m1, m2, m3, m4, m5, m6, m7;
        input [4:0] min1, min2;
        input [2:0] idx;
        input [4:0] err_cnt;
        output [4:0] err_cnt_new;

        integer i;
        reg [4:0] message[0:7];
        reg [4:0] min1_check, min2_check;
        reg [4:0] tmp;
        reg [2:0] idx_check;

        begin
            message[0] = m0;
            message[1] = m1;
            message[2] = m2;
            message[3] = m3;
            message[4] = m4;
            message[5] = m5;
            message[6] = m6;
            message[7] = m7;
            min1_check = 5'b11111;
            min2_check = 5'b11111;
            tmp = 5'b11111;

            for(i=0;i<8;i=i+1) begin
                if(message[i] < min1_check) begin
                    tmp = min1_check;
                    min1_check = message[i];
                    if (tmp < min2_check)
                        min2_check = tmp;
                    else
                        min2_check = min2_check;
                    idx_check = i;
                    // $display("min1: %d, min2: %d", min1_check, min2_check);
                end
                else if (message[i] >= min1_check && message[i] < min2_check)begin
                    min1_check = min1_check;
                    min2_check = message[i];
                    tmp = tmp;
                    idx_check = idx_check;

                    // $display("min1: %d, min2: %d", min1_check, min2_check);

                end
                else begin
                    min1_check = min1_check;
                    min2_check = min2_check;
                    tmp = tmp;
                    idx_check = idx_check;

                    // $display("min1: %d, min2: %d", min1_check, min2_check);
                end
            end

            if (min1 != min1_check) begin
                $display("Wrong min1!");
                $display("Your min1: %d, answer: %d", min1, min1_check);
                err_cnt_new = err_cnt + 1;
            end
            else if (min2 != min2_check) begin
                $display("Wrong min2!");
                $display("Your min2: %d, answer: %d", min2, min2_check);
                err_cnt_new = err_cnt + 1;
            end
            else if (idx != idx_check) begin
                $display("Wrong idx!");
                $display("Your idx: %d, answer: %d", idx, idx_check);
                err_cnt_new = err_cnt + 1;
            end
            else begin
                err_cnt_new = err_cnt;
            end

        end
    endtask

    task result_display;
        input [9:0] err_cnt;

        begin
            $display("---------------Result---------------");
            $display("Total error: ", err_cnt);
        end
    endtask
    
    //test bench
    initial begin
        err_cnt = 10'd0;
        err_cnt_new = 10'd0;
        m0 = 5'd0; m1 = 5'd0; m2 = 5'd0; m3 = 5'd0; m4 = 5'd0; m5 = 5'd0; m6 = 5'd0; m7 = 5'd0; 

        for(k=0;k<test_n;k=k+1) begin
            #(PERIOD)  
                random_generate(m0, m1, m2, m3, m4, m5, m6, m7);
            #(PERIOD/10)
                check(m0, m1, m2, m3, m4, m5, m6, m7, min1, min2, min1_index, err_cnt, err_cnt_new);
                if (err_cnt != err_cnt_new)
                    $display("Wrong at %d test", k);
                err_cnt = err_cnt_new;
        end

        #(PERIOD*5) $finish;
    end

    initial begin
        #((PERIOD + PERIOD/10)*(test_n+1)) 
            result_display(err_cnt);
    end

endmodule
