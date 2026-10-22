
//You should initially set incr[7:0] to 1. Then use the 
//vbdPlot() function to plot output data sample to Vbuddy. 


//Here are two things you should do:

 //   Since you are generating a continuous sinewave, the number
 // of simulation cycle should be increased to a large value, 
 //say, 1,000,000!
//Because of this large number of simulation cycles before termination, 
//you need to have an elegant way to exit the simulation
//Use the vbdGetkey() function to check if a key has been pressed.
   // either simulation finished, or 'q' is pressed
  //  if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
    //  exit(0);                // ... exit if finish OR 'q' pressed


#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vsinegen.h"

#include "vbuddy.cpp"     // include vbuddy code
#define MAX_SIM_CYC 1000000
#define ADDRESS_WIDTH 8
#define ROM_SZ 256


int main(int argc, char **argv, char **env){
    int simcyc;
    int tick;

    Verilated::commandArgs(argc, argv);

    Vsinegen* top = new Vsinegen;
    
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("sinegen.vcd");

    if (vbdOpen()!=1) return(-1);
    vbdHeader("lab 2 sinegen");

    top->clk = 1;
    top->rst = 1;
    top->en = 0;
    top->incr = 1;
    top->incr = vbdValue();

    for(simcyc=0; simcyc<MAX_SIM_CYC; simcyc++){
        top->rst = (simcyc < 2) || !vbdFlag();
        for(tick=0; tick<2; tick++){
            tfp->dump (2*simcyc+tick);
            top->clk = !top->clk;
            top->eval ();
        }
    
    

    vbdPlot(int (top->dout1 ), 0, 255);
    vbdPlot(int (top->dout2), 0, 255);
    vbdCycle(simcyc);

    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) exit(0);

    }

    vbdClose();
    tfp->close(); 
    exit(0);

}