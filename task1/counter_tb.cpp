#include "Vcounter.h" // for module counter
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc,char **argv,char **env)
{
    int i; // i counts the number of clock cycles to simulate
    int clk; // clock signal, 1 or 0

    Verilated::commandArgs(argc,argv);

    // init top verilog instance
    // instantiate the counter as Vcounter, which is the name of all generated files. This is the DUT.
    Vcounter* top = new Vcounter;
    // init trace dump
    // trun on signal tracing
    Verilated::traceEverOn(true);
    // tell verilator to dump the waveform data to counter.vcd
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp,99);
    tfp->open("counter.vcd");

    // initialise simulation inputs
    top -> clk = 1;
    top -> rst = 1;
    top -> en = 0;

    // run the simulation for many clock cycles
    for (i=0;i<300;i++)
    {
        // dump variables into VCD file and toggle clock
        for (clk=0;clk<2;clk++)
        {
            tfp -> dump(2*i+clk); // unit is in ps!
            top -> clk = !top -> clk;
            top -> eval();
        }

        // change rst and en signals during simulation
        top -> rst = (i<2) | (i==15);
        top -> en = (i>4);
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}