
#include <stdio.h>
#include <verilated.h>
#include "Vscr1_top_tb_ahb.h"
#ifdef VCD_TRACE
#include "verilated_vcd_c.h"
#endif // #ifdef VCD_TRACE

#define STRINGIFY(s) _STRINGIFY(s)
#define _STRINGIFY(s) #s

vluint64_t main_time = 0;

int main(int argc, char** argv) {

    const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
    contextp->debug(0);
    contextp->commandArgs(argc, argv);
    const std::unique_ptr<Vscr1_top_tb_ahb> top{new Vscr1_top_tb_ahb{contextp.get(), "TOP"}};

#ifdef VCD_TRACE
    contextp->traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
#ifdef TRACE_LVLV
    top->trace(tfp, TRACE_LVLV);
#else
    top->trace(tfp, 99);  // Trace 99 levels of hierarchy by default
#endif // #ifdef TRACE_LVLV

#ifdef VCD_FNAME
    tfp->open(STRINGIFY(VCD_FNAME));
#else
    tfp->open("./simx.vcd");
#endif // #ifdef VCD_FNAME
#endif // #ifdef VCD_TRACE

    while (!contextp->gotFinish()) {
        if ((main_time % 10) == 1) {
            top->clk = 1;
        }
        if ((main_time % 10) == 6) {
            top->clk = 0;
        }
        top->eval();
        main_time++;
#ifdef VCD_TRACE
        tfp->dump(main_time);
#endif // #ifdef VCD_TRACE
    }
    top->final();
    contextp->coveragep()->write("coverage.dat");
#ifdef VCD_TRACE
    tfp->close();
#endif // #ifdef VCD_TRACE
}

