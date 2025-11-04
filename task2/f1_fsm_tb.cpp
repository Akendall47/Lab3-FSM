#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vf1_fsm.h"      // generated from your Verilog module
#include "vbuddy.cpp"   // include Vbuddy I/O library

#define MAX_SIM_CYC 1000000

int main(int argc, char **argv, char **env) {
    int simcyc;   // simulation cycle counter
    int tick;     // each clock cycle has two ticks (posedge + negedge)

    Verilated::commandArgs(argc, argv);

    // Instantiate the DUT (Device Under Test)
    Vf1_fsm* top = new Vf1_fsm;

    // Enable waveform tracing
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("f1_fsm.vcd");

    // Initialize Vbuddy
    if (vbdOpen() != 1) return -1;
    vbdHeader("L3T1: F1 FSM Sequence");
    vbdSetMode(1);  // Rotary switch mode 1 (vbdFlag controls 'en')

    // Initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en  = 0;

    // Apply reset for a few cycles
    for (int i = 0; i < 5; i++) {
        for (tick = 0; tick < 2; tick++) {
            top->clk = !top->clk;
            top->eval();
            tfp->dump(2 * i + tick);
        }
    }
    top->rst = 0; // Release reset

    // Main simulation loop
    for (simcyc = 0; simcyc < MAX_SIM_CYC; simcyc++) {

        // Read rotary switch flag for 'en' signal
        top->en = vbdFlag();

        // Toggle clock twice per cycle (posedge + negedge)
        for (tick = 0; tick < 2; tick++) {
            tfp->dump(2 * simcyc + tick);
            top->clk = !top->clk;
            top->eval();
        }

        // Display output on Vbuddy neopixel bar
        vbdBar(top->data_out & 0xFF);

        // Display simulation cycle on 7-seg
        vbdCycle(simcyc);

        // Quit on 'q' key or simulation end
        if (Verilated::gotFinish() || vbdGetkey() == 'q')
            break;
    }

    // Clean up
    vbdClose();
    tfp->close();
    delete top;
    exit(0);
}
