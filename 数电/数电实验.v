任务一：
module project1(sw_i,led_o);
    input [3:0]sw_i;
    output [1:0]led_o;
    wire a,b;
    nand(a,sw_i[3],sw_i[2]);
    nand(b,sw_i[3],sw_i[1]);
    nand(led_o[0],a,b);
endmodule

任务二：
module project2(sw_i,led_o);
    input [3:0] sw_i;
    output [1:0] led_o;
    wire n1,n2,n3,n4;
    wire a,b,c,d,e,f;
    not (n1,sw_i[3]); 
    not (n2,sw_i[2]);
    not (n3,sw_i[1]);
    not (n4,sw_i[0]); 
    
    nand (a,n1,sw_i[1],sw_i[0]);
    nand (b,n1,sw_i[2]);
    nand (c,sw_i[3],n2,n3);
    nand (d,n1,n2);
    nand (e,n1,n3);
    nand (f,n1,n4);
    
    nand (led_o[0],a,b,c);
    nand (led_o[1],d,e,f);
endmodule

任务三：
module project3(
    input [3:0] sw_i,
    output reg [7:0] disp_seg_o,
    output reg [7:0] disp_an_o
);
    always @(*)
    begin
        disp_an_o = 8'b11111101;//0亮1灭
        case(sw_i) // 从左到右:点gfedcba .
            4'b0000: disp_seg_o = 8'b11000000;    
            4'b0001: disp_seg_o = 8'b11111001;    
            4'b0010: disp_seg_o = 8'b10100100;   
            4'b0011: disp_seg_o = 8'b10110000;  
            4'b0100: disp_seg_o = 8'b10011001;   
            4'b0101: disp_seg_o = 8'b10010010;   
            4'b0110: disp_seg_o = 8'b10000010;   
            4'b0111: disp_seg_o = 8'b11111000;   
            4'b1000: disp_seg_o = 8'b10000000;   
            4'b1001: disp_seg_o = 8'b10011000;   
            default: disp_seg_o = 8'b11111111;    // 大于9全灭  
        endcase
    end  
endmodule

任务四（ljy解法）：
module project4(
input[15:0]sw_i,
input wire clk,
output reg[7:0]disp_seg_o,
output[7:0]disp_an_o
    );

    parameter para=25;
    
    wire EN=sw_i[0];//使能端
    wire BNTC=sw_i[1];//清零端
    reg[31:0]clk_cnt;//实时计数器
    reg[3:0]cnt;//当前计数,0~9
    reg clear;//每当cnt从9到0，或者BNTC按下时，触发清零信号
    
    assign disp_an_o=8'b11111101;
    
    always @(posedge clk)begin
        if(EN)begin
            clk_cnt<=clk_cnt+1;
            cnt<=clk_cnt[para+3:para];
            clear<=BNTC||(cnt==4'b1010);  

            if(clear)begin 
                clk_cnt<=0;
                cnt<=4'b0000;
            end
        end
    end
    
    always@(posedge clk_cnt[para-2])begin
      case(cnt) 
                4'b0000:disp_seg_o=8'b11000000;
                4'b0001:disp_seg_o=8'b11111001;
                4'b0010:disp_seg_o=8'b10100100;
                4'b0011:disp_seg_o=8'b10110000;
                4'b0100:disp_seg_o=8'b10011001;
                4'b0101:disp_seg_o=8'b10010010;
                4'b0110:disp_seg_o=8'b10000010;
                4'b0111:disp_seg_o=8'b11111000;
                4'b1000:disp_seg_o=8'b10000000;
                4'b1001:disp_seg_o=8'b10010000;
       endcase
      end
endmodule

任务四（官方解法）：
module project4(input[15:0]sw_i,input clk,output reg[7:0]disp_seg_o,output reg[7:0]disp_an_o);
    parameter para=24;
    wire clk24;
    wire EN;
    wire BTNC;
    reg[31:0]clk_cnt;
    reg[3:0]cnt;
    
    assign EN=sw_i[1];
    assign BTNC=sw_i[15];
    
    always@(posedge clk)begin
        if(BTNC)clk_cnt<=0;
        if(EN)clk_cnt<=clk_cnt+1;
    end
    
    assign clk24=clk_cnt[para];//divide fluquency
    
    always@(posedge clk24)begin
        disp_an_o<=8'b11111110;
        if(BTNC)cnt<=4'b0000;
        else if(EN)begin
            case(cnt)
                4'b0000:disp_seg_o<=8'b11000000;
                4'b0001:disp_seg_o<=8'b11111001;
                4'b0010:disp_seg_o<=8'b10100100;
                4'b0011:disp_seg_o<=8'b10110000;
                4'b0100:disp_seg_o<=8'b10011001;
                4'b0101:disp_seg_o<=8'b10010010;
                4'b0110:disp_seg_o<=8'b10000010;
                4'b0111:disp_seg_o<=8'b11111000;
                4'b1000:disp_seg_o<=8'b10000000;
                4'b1001:disp_seg_o<=8'b10010000;
                default:disp_seg_o<=8'b11000000;
            endcase
            if(cnt>=4'b1001)cnt<=4'b0000;
            else cnt<=cnt+1;
        end
    end
    
endmodule



任务五：
module DTriger(
    input CP,
    input RST,
    input D,
    output reg Q
);
    always @(posedge CP or posedge RST)
    begin
        if (RST) 
            Q <= 0;
        else 
            Q <= D;
    end
endmodule

module project5(
    input CPU_RESETN,//复位信号，低电平有效
    input BTNC,
    input [1:1] sw_i,//X
    output reg [15:0] led_o,
    output reg [7:0] disp_an_o,
    output reg [7:0] disp_seg_o
);
    wire Q1, Q2, D1, D2, X; 
    assign X = sw_i[1];
    assign D1 = X;
    assign D2 = ((~X)&Q1)|(X&Q2&~Q1);
    
    // 实例化两个触发器D
    DTriger dt1(
        .CP(BTNC),
        .RST(~CPU_RESETN),
        .D(D1),
        .Q(Q1)
    );
    DTriger dt2(
        .CP(BTNC),
        .RST(~CPU_RESETN),
        .D(D2),
        .Q(Q2)
    );

    // 直接根据Q1和Q2控制LED和七段显示器
    always @(posedge BTNC or negedge CPU_RESETN) 
    begin
        disp_an_o = 8'b11111101; // 选择第0位数码管
        if (~CPU_RESETN)          //复位
        begin
            led_o <= 16'b0;
            disp_seg_o <= 8'b11000000;  //0
        end
        else 
        begin
            // 根据Q1和Q2的值直接控制LED和七段显示器
            led_o[0] <= Q2 & ~Q1 & X; 
            if (Q2 & ~Q1 & X)
                disp_seg_o <= 8'b11111001; //1
            else 
                disp_seg_o <= 8'b11000000; //0
        end
    end
endmodule