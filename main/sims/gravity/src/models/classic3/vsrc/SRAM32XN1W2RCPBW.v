/*
Arch-Simulator-SIG                                                     - 2024
Reduced Instruction Set Micro Devices (RISMD) organization, Kumonda221 - 2024

> SRAM32XN1W2RCPBW.v

!!! FOR CONCEPT DEMO ONLY !!!  

------------------------------------------------------------------------------------------------
*NOTICE: This is not guaranteed to be a correct model of the actual hardware and synthesiable.
         Recommended to be replaced on FPGA/ASIC synthesis.

------------------------------------------------------------------------------------------------
SRAM32XN1W2RCPBW : SRAM 32xN with 1 Write and 2 Read Ports with 
                   Clock Synchronized on Posedge & Bit Write Enable.

------------------------------------------------------------------------------------------------
This is a model of a 32xN SRAM with 1 Write and 2 Read Ports 
with Clock Synchronized on Posedge & Bit Write Enable.

NO LATCH inferred in this model.
The data output (QA, QB) was left unchanged when the read enable (REA, REB) is non-active.

Port A - Read Port 0
Port B - Read Port 1
Port C - Write Port
------------------------------------------------------------------------------------------------
*/


module SRAM32XN1W2RCPBW #(
    parameter WORD_COUNT    = 32
) (
    CLK,

    WEC,
    BWC,
    DC,
    AC,

    REA,
    AA,
    QA,

    REB,
    AB,
    QB
);

    // I/O definitions
    input   wire                            CLK;    // Clock - Posedge Synchronized

    input   wire                            WEC;    // Write Enable     - Active on LOW     - Port C
    input   wire [31:0]                     BWC;    // Bit Write Enable - Active on LOW     - Port C
    input   wire [31:0]                     DC;     // Write Data                           - Port C
    input   wire [$clog2(WORD_COUNT)-1:0]   AC;     // Write Address                        - Port C

    input   wire                            REA;    // Read Enable      - Active on LOW     - Port A
    input   wire [$clog2(WORD_COUNT)-1:0]   AA;     // Read Address                         - Port A
    output  reg  [31:0]                     QA;     // Read Data                            - Port A

    input   wire                            REB;    // Read Enable      - Active on LOW     - Port B
    input   wire [$clog2(WORD_COUNT)-1:0]   AB;     // Read Address                         - Port B
    output  reg  [31:0]                     QB;     // Read Data                            - Port B


    // Internal 
    reg [31:0] array [WORD_COUNT-1:0];    // Memory Array

    always @(posedge CLK) begin
        
        if (WEC == 1'b0) begin
            array[AC] <= (DC & BWC) | (array[AC] & ~BWC);
        end
    end


    always @(posedge CLK) begin

        if (REA == 1'b0) begin
            QA <= array[AA];
        end

        if (REB == 1'b0) begin
            QB <= array[AB];
        end
    end


    //

endmodule
