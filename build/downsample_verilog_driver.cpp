#include "Vdownsample_verilog.h"
#include "verilated.h"
#include <iostream>
#include <fstream>
#include <verilated_vcd_c.h>
#include <sys/types.h>
#include <sys/stat.h>

// Based on https://www.veripool.org/projects/verilator/wiki/Manual-verilator#CONNECTING-TO-C
vluint64_t main_time = 0;       // Current simulation time
// This is a 64-bit integer to reduce wrap over issues and
// allow modulus.  You can also use a double, if you wish.

double sc_time_stamp () {       // Called by $time in Verilog
    return main_time;           // converts to double, to match
                                // what SystemC does
}

#if VM_TRACE
VerilatedVcdC* tracer;
#endif

void my_assert(
    unsigned int got,
    unsigned int expected,
    int i,
    const char* port) {
  if (got != expected) {
    std::cerr << std::endl;  // end the current line
    std::cerr << "Got      : 0x" << std::hex << got << std::endl;
    std::cerr << "Expected : 0x" << std::hex << expected << std::endl;
    std::cerr << "i        : " << std::dec << i << std::endl;
    std::cerr << "Port     : " << port << std::endl;
#if VM_TRACE
    // Dump one more timestep so we see the current values
    main_time++;
    tracer->dump(main_time);
    tracer->close();
#endif
    exit(1);
  }
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Vdownsample_verilog* top = new Vdownsample_verilog;

#if VM_TRACE
  Verilated::traceEverOn(true);
  tracer = new VerilatedVcdC;
  top->trace(tracer, 99);
  mkdir("logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  tracer->open("logs/downsample_verilog.vcd");
#endif

  top->RESET = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->RESET = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->RESET = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 0;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 0 & 65535, 11, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 1;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 18, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 19, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 2;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 25, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 2;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 2;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 2;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 2;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 46, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 2 & 65535, 47, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 48, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 3;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 54, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 55, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 4;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 4;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 4;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 4;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 4;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 4;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 86, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 4;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 92, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 4 & 65535, 93, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 94, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 5;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 100, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 101, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 6;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 107, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 6 & 65535, 108, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 109, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 7;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 115, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 7;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 7;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 126, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 127, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 8;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 133, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 8;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 139, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 8 & 65535, 140, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 141, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 9;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 9;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 152, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 10;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 10;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 10;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 10;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 173, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 10;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 10;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 184, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 10 & 65535, 185, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 186, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 11;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 192, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 11;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 198, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 12;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 204, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 12 & 65535, 205, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 206, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 13;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 212, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 213, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 14;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 14;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 14;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 14;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 14;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 14;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 244, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 14;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 250, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 14 & 65535, 251, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 252, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 15;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 258, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 15;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 15;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 15;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 274, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 16;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 280, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 16;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 16;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 16;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 296, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 16;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 16;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 307, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 16;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 313, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 16 & 65535, 314, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 315, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 17;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 17;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 326, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 18;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 332, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 18 & 65535, 333, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 334, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 19;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 340, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 341, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 20;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 20;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 352, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 20 & 65535, 353, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 354, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 21;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 360, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 21;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 366, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 22;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 372, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 22 & 65535, 373, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 374, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 23;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 23;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 385, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 24;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 391, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 24;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 397, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 24;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 24;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 408, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 24 & 65535, 409, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 410, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 25;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 416, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 26;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 26;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 427, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 26 & 65535, 428, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 429, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 27;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 435, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 27;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 441, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 27;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 447, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 448, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 28;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 28;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 459, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 28;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 28;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 470, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 28 & 65535, 471, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 472, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 29;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 29;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 483, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 484, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 30;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 490, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 30 & 65535, 491, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 492, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 31;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 498, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 31;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 31;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 509, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 32;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 515, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 516, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 33;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 522, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 34;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 528, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 529, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 35;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 535, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 536, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 36;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 542, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 543, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 37;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 549, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 550, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 38;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 556, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 39;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 562, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 40;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 568, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 41;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 574, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 575, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 42;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 581, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 43;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 587, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 44;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 593, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 45;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 599, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 600, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 46;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 606, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 46;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 612, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 46;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 618, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 47;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 624, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 47;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 630, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 631, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 48;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 48;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 48;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 48;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 48;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 657, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 48;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 663, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 664, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 49;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 49;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 675, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 49;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 681, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 49;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 687, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 50;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 693, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 50;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 699, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 50;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 705, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 50;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 711, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 51;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 51;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 51;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 51;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 732, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 51;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 738, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 51;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 744, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 52;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 750, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 53;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 756, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 53;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 762, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 53;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 768, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 769, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 54;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 775, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 54;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 781, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 54;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 54;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 792, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 55;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 798, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 56;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 804, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 56;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 810, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 56;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 816, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 56;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 822, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 57;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 57;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 833, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 57;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 57;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 57;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 849, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 58;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 58;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 860, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 58;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 866, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 867, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 59;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 873, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 60;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 879, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 61;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 885, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 62;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 891, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 892, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 63;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 63;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 903, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 63;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 63;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 914, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 915, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 64;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 64;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 64;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 64;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 936, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 64;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 64;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 947, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 64;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 953, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 64 & 65535, 954, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 955, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 65;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 961, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 66;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 967, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 66;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 973, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 66;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 979, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 66;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 985, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 66 & 65535, 986, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 987, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 67;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 993, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 994, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 68;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1000, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 68;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 68;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 68;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 68;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1021, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 68 & 65535, 1022, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1023, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 69;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1029, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1030, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 70;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1036, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 70;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1042, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 70;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 70;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1053, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 70;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1059, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 70 & 65535, 1060, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1061, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 71;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1067, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 71;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1073, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 72;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 72;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 72;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 72;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1094, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 72 & 65535, 1095, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1096, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 73;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1102, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1103, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 74;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1109, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 74 & 65535, 1110, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1111, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 75;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1117, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 75;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1123, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1124, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 76;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 76;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 76;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 76;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1145, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 76 & 65535, 1146, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1147, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 77;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1153, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 77;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1159, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1160, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 78;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1166, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 78 & 65535, 1167, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1168, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 79;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1174, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 80;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1180, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 80 & 65535, 1181, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1182, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 81;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 81;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1193, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1194, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 82;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1200, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 82 & 65535, 1201, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1202, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 83;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1208, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 84;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1214, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 84 & 65535, 1215, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1216, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 85;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 85;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 85;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1232, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 85;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 85;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 85;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1248, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 85;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1254, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 85;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1260, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 85;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1266, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 86;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1272, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 86 & 65535, 1273, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1274, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 87;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1280, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1281, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 88;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1287, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 88;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1293, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 88 & 65535, 1294, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1295, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 89;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1301, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1302, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 90;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 90;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 90;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1318, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 90 & 65535, 1319, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1320, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 91;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1326, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1327, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 92;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 92;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 92;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 92;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1348, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 92 & 65535, 1349, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1350, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 93;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1356, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 93;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1362, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 93;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1368, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 93;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1374, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 94;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 94;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 94;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 94;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1395, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 94 & 65535, 1396, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1397, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 95;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1403, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1404, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 96;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1410, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 96;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1416, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 96;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1422, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 97;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 97;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 97;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1438, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1439, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 98;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1445, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 98;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1451, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 99;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1457, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1458, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 100;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1464, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 100;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 100;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 100;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 100;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1485, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 101;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1491, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 102;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1497, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1498, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 103;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1504, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1505, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 104;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1511, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1512, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 105;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1518, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 105;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1524, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 106;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1530, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 106;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1536, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 107;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 107;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1547, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 107;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 107;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1558, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1559, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 108;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1565, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 109;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1571, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 110;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1577, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1578, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 111;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1584, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 111;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1590, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 112;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1596, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1597, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 113;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1603, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 114;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1609, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 115;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 115;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1620, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 116;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1626, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 116;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1632, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 116;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1638, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 116;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1644, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 116;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1650, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1651, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 117;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1657, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1658, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 118;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 118;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1669, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 119;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1675, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1676, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 120;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1682, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1683, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 121;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1689, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 122;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1695, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 123;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1701, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1702, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 124;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 124;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1713, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 124;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1719, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1720, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 125;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 125;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1731, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1732, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 126;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 126;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 126;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 126;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 126;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1758, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 127;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1764, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 127;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 127;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1775, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1776, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 128;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 128;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1787, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 128 & 65535, 1788, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1789, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 129;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1795, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1796, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 130;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1802, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 130;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 130;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 130;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 130;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1823, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 130;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1829, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 130 & 65535, 1830, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1831, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 131;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1837, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 131;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 1843, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 132;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1849, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 132;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 132;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1860, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 132 & 65535, 1861, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1862, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 133;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 133;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1873, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 133;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1879, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 133;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1885, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 1886, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 134;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 134;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 134;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1902, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 134;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 134;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 134;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1918, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 134;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 134;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 134;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1934, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 134;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 1940, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 134 & 65535, 1941, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 1942, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1948, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1959, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 1990, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 135;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2001, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 135;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2007, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 136;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2013, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 136 & 65535, 2014, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2015, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 137;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2021, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2022, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 138;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2028, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 138 & 65535, 2029, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2030, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 139;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 139;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2041, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2042, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 140;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2048, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 140 & 65535, 2049, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2050, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 141;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 141;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 141;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2066, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2067, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 142;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2073, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 142 & 65535, 2074, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2075, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 143;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2081, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 144;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2087, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 144;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2093, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 144 & 65535, 2094, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2095, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 145;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2101, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 145;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2107, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 145;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 145;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2118, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 145;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2124, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2125, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 146;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2131, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 146;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 146;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 146;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2147, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 146;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 146;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2158, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 146;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2164, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 146;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2170, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 146;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2176, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 146 & 65535, 2177, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2178, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 147;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 147;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2189, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2190, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 148;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2196, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 148 & 65535, 2197, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2198, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 149;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2204, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 149;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2210, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2211, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 150;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 150;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2222, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 150 & 65535, 2223, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2224, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 151;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2230, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2231, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 152;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 152;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 152;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2247, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 152;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 152;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2258, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 152;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 152;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2269, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 152;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 152;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2280, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 152 & 65535, 2281, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2282, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 153;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 153;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 153;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2298, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 153;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2304, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2305, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 154;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 154;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2316, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 154;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 154;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2327, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 154;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2333, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 154 & 65535, 2334, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2335, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 155;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 155;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 155;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 155;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2356, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 156;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 156;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 156;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 156;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2377, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 156 & 65535, 2378, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2379, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 157;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2385, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 157;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2391, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 158;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 158;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 158;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 158;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 158;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 158;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 158;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2427, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 158 & 65535, 2428, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2429, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 159;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2435, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2436, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 160;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 160;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2447, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 161;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2453, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 161;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2459, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 161;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 161;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 161;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2475, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 161;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 161;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2486, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2487, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 162;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2493, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 162;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2499, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 163;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2505, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2506, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 164;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 164;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2517, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2518, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 165;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 165;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2529, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 165;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2535, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 165;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2541, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2542, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 166;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2548, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 167;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2554, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2555, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 168;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2561, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 168;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2567, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 169;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2573, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 170;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2579, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 171;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 171;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2590, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 171;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2596, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 171;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 171;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 171;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 171;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2617, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2618, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 172;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2624, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 172;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 172;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2635, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2636, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 173;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2642, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2643, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 174;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2649, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2650, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 175;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2656, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2657, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 176;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2663, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 177;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2669, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 178;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 178;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2680, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2681, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 179;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2687, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 180;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2693, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 181;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2699, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 181;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 181;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 181;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 181;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2720, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2721, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 182;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 182;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 182;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2737, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2738, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 183;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2744, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2745, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 184;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2751, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 185;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2757, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 186;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2763, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 186;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2769, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 187;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2775, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 188;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 188;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 188;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 188;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2796, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2797, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 189;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2803, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 190;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2809, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 190;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2815, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 190;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2821, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2822, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 191;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2828, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 191;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2834, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 192;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 192;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 192;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 192;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 192;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2860, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 192;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2866, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 192;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 192;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 192;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2882, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 192 & 65535, 2883, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2884, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 193;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2890, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 193;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2896, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 2897, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 194;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 194;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 194;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2913, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 194;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 194;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 2924, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 194 & 65535, 2925, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 2926, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 195;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2932, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 195;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 195;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 195;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2948, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 195;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2954, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 195;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 2960, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 196;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 196;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 196;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2976, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 196;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2982, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 196;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2988, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 196;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 2994, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 196;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3000, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 196;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 196;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3011, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 196 & 65535, 3012, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3013, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 197;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 197;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 197;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3029, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 197;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 197;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3040, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 197;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3046, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3047, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 198;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3053, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 198 & 65535, 3054, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3055, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 199;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3061, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 200;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3067, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 200 & 65535, 3068, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3069, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 201;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3075, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 202;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3081, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 202;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3087, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 202 & 65535, 3088, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3089, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 203;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3095, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 203;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3101, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3102, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 204;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 204;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 204;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 204;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3123, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 204;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3129, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 204;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3135, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 204;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 204;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 204;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3151, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 204;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3157, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 204;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3163, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 204 & 65535, 3164, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3165, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 205;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3171, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3172, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 206;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3178, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 206 & 65535, 3179, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3180, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 207;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 207;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3191, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 207;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3197, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 207;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3203, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 207;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 207;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 207;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 207;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3224, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 208;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3230, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 208;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3236, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 208;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 208;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3247, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 208 & 65535, 3248, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3249, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 209;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 209;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3260, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 210;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 210;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3271, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 210 & 65535, 3272, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3273, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 211;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3279, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 211;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3285, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 211;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3291, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 212;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3297, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 212;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3303, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 212;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 212;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3314, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 212 & 65535, 3315, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3316, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 213;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3322, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3323, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 214;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 214;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3334, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 214;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 214;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3345, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 214;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3351, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 214 & 65535, 3352, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3353, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 215;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3359, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 216;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 216;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3370, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 216 & 65535, 3371, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3372, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 217;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3378, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 217;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3384, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 218;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 218;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 218;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3400, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 218 & 65535, 3401, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3402, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 219;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3408, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3409, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 220;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 220;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3420, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 220 & 65535, 3421, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3422, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 221;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3428, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 221;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3434, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 222;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 222;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 222;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3450, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 222;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3456, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 222;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3462, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 222;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3468, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 222 & 65535, 3469, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3470, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 223;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3476, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 224;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3482, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3483, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 225;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 225;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3494, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3495, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 226;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3501, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 227;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3507, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 228;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3513, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 229;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3519, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 230;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 230;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3530, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3531, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 231;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 231;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3542, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 232;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3548, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3549, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 233;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3555, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3556, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 234;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 234;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 234;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3572, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3573, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 235;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3579, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 235;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3585, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 236;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3591, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 237;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3597, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 238;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3603, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 238;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3609, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 239;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3615, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 240;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3621, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 241;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3627, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 241;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3633, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 241;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3639, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 242;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3645, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3646, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 243;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3652, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3653, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 244;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3659, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3660, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 245;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3666, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3667, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 246;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3673, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 246;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3679, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3680, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 247;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3686, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 248;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3692, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 249;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3698, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 250;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3704, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 250;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3710, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 250;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 250;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3721, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3722, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 251;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 251;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3733, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 251;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3739, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3740, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 252;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3746, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 252;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3752, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 253;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 253;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3763, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3764, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 254;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3770, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 255;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3776, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 256;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3782, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 256;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3788, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 256;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 256;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 256;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 256;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3809, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 256 & 65535, 3810, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3811, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 257;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3817, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3818, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 258;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3824, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 258 & 65535, 3825, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3826, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 259;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3832, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 259;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3838, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 260;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 260;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 260;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3854, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 260;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 260;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3865, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 260;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 260;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 260;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 260;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3886, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 260 & 65535, 3887, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3888, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 261;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 261;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 3899, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 262;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 262;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 262;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 262;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 262;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3925, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 262;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 262;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 262;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3941, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 262 & 65535, 3942, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3943, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 263;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 263;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3954, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3955, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 264;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3961, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 264;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3967, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 264;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3973, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 264;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 264;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3984, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 264;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 3990, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 264 & 65535, 3991, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 3992, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 265;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 3998, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 3999, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 266;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4040, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 266;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4056, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 266;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 266;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4067, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 266 & 65535, 4068, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4069, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 267;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4075, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 267;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4081, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 267;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4087, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 267;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4093, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 267;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 267;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4104, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 267;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4110, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 268;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 268;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 268;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4126, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 268 & 65535, 4127, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4128, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 269;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4134, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 269;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 269;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4145, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 269;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4151, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 269;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4157, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 269;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4163, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 269;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 269;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4174, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4175, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 270;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 270;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4186, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 270;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 270;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 270;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 270;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4207, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 270;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 270;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 270;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4223, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 270 & 65535, 4224, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4225, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 271;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 271;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 271;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 271;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4246, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 272;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 272;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 272;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4262, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 272;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4268, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 272 & 65535, 4269, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4270, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 273;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4276, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 274;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 274;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4287, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 274 & 65535, 4288, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4289, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 275;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4295, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 276;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 276;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 276;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 276;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4316, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 276 & 65535, 4317, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4318, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 277;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4324, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4325, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 278;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 278;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 278;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 278;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 278;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4351, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 278;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4357, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 278;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 278;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4368, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 278 & 65535, 4369, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4370, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 279;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4376, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 279;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 279;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 279;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4392, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4393, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 280;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 280;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 280;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4409, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 280;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 280;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4420, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 280;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 280;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 280;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4436, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 280 & 65535, 4437, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4438, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 281;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4444, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4445, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 282;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4451, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 282;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4457, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 282;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 282;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4468, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 282 & 65535, 4469, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4470, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 283;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4476, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4477, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 284;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4483, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 284;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 284;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 284;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 284;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4504, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 284 & 65535, 4505, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4506, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 285;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4512, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 286;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4518, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 286 & 65535, 4519, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4520, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 287;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 287;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 287;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4536, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 287;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 287;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4547, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 288;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4553, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 289;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 289;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4564, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 289;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4570, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4571, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 290;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4577, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 291;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4583, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 291;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4589, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 292;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 292;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4600, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 293;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4606, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4607, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 294;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4613, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 295;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4619, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 295;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4625, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 295;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4631, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4632, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 296;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4638, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 297;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 297;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4649, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4650, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 298;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4656, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4657, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 299;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 299;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4668, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 300;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4674, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 300;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4680, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4681, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 301;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4687, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4688, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 302;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4694, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 303;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4700, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 304;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4706, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 305;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 305;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 305;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4722, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 305;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4728, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 305;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4734, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4735, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 306;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 306;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4746, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 306;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4752, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 306;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4758, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4759, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 307;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4765, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 307;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4771, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4772, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 308;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4778, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 309;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 309;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4789, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 310;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4795, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 311;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4801, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 311;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 311;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4812, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4813, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 312;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4819, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 312;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4825, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4826, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 313;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 313;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 313;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4842, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 313;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4848, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 313;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4854, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 314;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4860, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 315;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4866, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4867, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 316;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4873, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 317;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 317;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 317;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4889, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4890, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 318;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 4896, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 319;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4902, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4903, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 320;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 320;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 320;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 320;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4924, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 320 & 65535, 4925, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4926, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 321;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4932, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4933, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 322;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 322;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 322;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 322;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 322;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 322;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4964, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 322;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 4970, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 322 & 65535, 4971, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 4972, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 323;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4978, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 323;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 323;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4989, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 4990, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 4996, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5002, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5013, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5019, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 324;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 324;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 324;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5055, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 324;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5061, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 324 & 65535, 5062, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5063, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 325;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5069, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5070, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 326;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5076, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 326;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5082, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 326 & 65535, 5083, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5084, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 327;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5090, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 327;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 327;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5101, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 327;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 327;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5112, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 327;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5118, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 327;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5124, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 327;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 327;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 327;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5140, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5141, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 328;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5147, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 328;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5153, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 328;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5159, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 328;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 328;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5170, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 328;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5176, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 328 & 65535, 5177, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5178, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 329;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5184, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 329;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5190, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5191, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 330;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5197, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 330;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 330;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 330;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5213, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 330;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5219, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 330 & 65535, 5220, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5221, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 331;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5227, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 332;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 332;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5238, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 332;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5244, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 332;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5250, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 332 & 65535, 5251, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5252, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 333;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5258, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5259, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 334;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5265, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 334 & 65535, 5266, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5267, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 335;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5273, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 335;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5279, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 336;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5285, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 336 & 65535, 5286, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5287, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 337;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 337;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 337;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 337;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5308, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 337;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 337;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5319, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 337;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5325, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5326, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 338;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 338;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 338;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5342, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 338 & 65535, 5343, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5344, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 339;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 339;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5355, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5356, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 340;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 340;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5367, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 340 & 65535, 5368, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5369, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 341;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5375, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5376, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 342;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 342;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5387, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 342 & 65535, 5388, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5389, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 343;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5395, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 343;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5401, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 344;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 344;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5412, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 344;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 344;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 344;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5428, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 344 & 65535, 5429, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5430, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 345;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5436, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5437, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 346;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 346;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5448, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 346 & 65535, 5449, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5450, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 347;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5456, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5457, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 348;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5463, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 348 & 65535, 5464, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5465, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 349;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5471, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 349;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5477, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5478, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 350;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5484, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 350 & 65535, 5485, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5486, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 351;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 351;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5497, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5498, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 352;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 352;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 352;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5514, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5515, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 353;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5521, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 353;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5527, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 353;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 353;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5538, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 354;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5544, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 354;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5550, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 354;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5556, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5557, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 355;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5563, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5564, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 356;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 356;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5575, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 356;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 356;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 356;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 356;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 356;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 356;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 356;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5611, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5612, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 357;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5618, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5619, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 358;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5625, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 358;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5631, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 359;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5637, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 360;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5643, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5644, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 361;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5650, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5651, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 362;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 362;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5662, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 362;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5668, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 363;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5674, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5675, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 364;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5681, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 364;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5687, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5688, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 365;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5694, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5695, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 366;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 366;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 366;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5711, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 366;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 366;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5722, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5723, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 367;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5729, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5730, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 368;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5736, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 369;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5742, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 369;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5748, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 370;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5754, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 370;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5760, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5761, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 371;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5767, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5768, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 372;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 372;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 372;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5784, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5785, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 373;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 373;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5796, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 373;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5802, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5803, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 374;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5809, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 375;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5815, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 376;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 376;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 376;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5831, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5832, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 377;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5838, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 377;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5844, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 378;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 378;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5855, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5856, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 379;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5862, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 380;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 5868, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 381;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 381;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5879, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5880, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 382;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5886, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5887, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 383;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 383;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5898, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5899, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 384;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 384;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5910, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 384;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5916, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 384;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 5922, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 384 & 65535, 5923, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 5924, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 385;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 385;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5935, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 385;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5941, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 5942, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5948, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 386;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5979, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 5985, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6001, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6012, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6018, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 386;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 386;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6029, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 386 & 65535, 6030, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6031, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 387;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6037, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 387;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6043, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 388;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 388;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 388;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 388;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 388;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 388;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 388;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 388;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 388;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6089, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 388;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6095, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 388;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 388;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6106, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 388;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6112, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 388 & 65535, 6113, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6114, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 389;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 389;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6125, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 390;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6131, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 390;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 390;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 390;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6147, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 390 & 65535, 6148, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6149, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 391;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6155, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 392;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6161, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 392;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 392;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 392;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 392;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 392;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6187, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 392 & 65535, 6188, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6189, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 393;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6195, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 393;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6201, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6202, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 394;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 394;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 394;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6218, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 394;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 394;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 394;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6234, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 394 & 65535, 6235, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6236, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 395;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6242, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6248, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 396;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 396;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6274, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6285, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6291, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 396;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 396;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 396;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6317, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 396;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6323, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 396 & 65535, 6324, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6325, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 397;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6331, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 397;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6337, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6338, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 398;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6344, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 398 & 65535, 6345, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6346, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 399;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6352, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6353, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 400;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6359, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 400 & 65535, 6360, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6361, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 401;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 401;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6372, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 401;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6378, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6379, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 402;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 402;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6390, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 402 & 65535, 6391, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6392, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 403;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6398, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 403;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6404, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 403;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6410, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 404;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 404;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6421, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 404 & 65535, 6422, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6423, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 405;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6429, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6430, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 406;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 406;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 406;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6446, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 406 & 65535, 6447, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6448, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 407;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 407;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6459, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 408;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 408;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 408;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 408;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6480, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 408;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6486, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 408;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6492, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 408 & 65535, 6493, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6494, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 409;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6500, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 410;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6506, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 410 & 65535, 6507, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6508, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 411;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6514, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6515, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 412;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6521, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 412;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6527, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 412 & 65535, 6528, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6529, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 413;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6535, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 414;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6541, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 414;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 414;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 414;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 414;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 414;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 6567, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 414 & 65535, 6568, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 6569, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 415;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6575, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 416;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6581, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6582, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 417;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6588, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 418;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6594, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 419;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6600, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 420;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 420;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 420;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6616, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 421;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6622, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 421;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6628, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6629, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 422;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 422;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6640, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 422;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6646, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 422;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6652, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6653, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 423;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 423;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6664, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 424;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6670, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 425;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6676, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 425;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6682, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6683, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 426;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 426;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 426;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 426;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6704, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6705, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 427;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 427;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6716, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 427;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6722, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 427;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 427;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6733, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 427;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6739, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 427;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6745, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6746, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 428;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 428;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6757, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 428;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6763, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 428;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6769, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 429;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6775, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 430;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6781, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6782, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 431;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6788, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 431;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6794, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 431;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6800, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 432;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 432;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6811, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6812, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 433;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6818, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 434;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6824, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 434;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6830, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 434;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6836, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 435;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6842, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 436;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6848, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 437;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6854, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 437;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6860, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 438;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6866, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 439;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6872, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 439;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6878, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6879, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 440;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6885, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 440;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6891, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 441;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6897, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 441;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 441;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6908, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 442;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6914, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 442;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 442;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6925, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6926, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 443;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6932, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 443;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6938, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 443;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 6944, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 444;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 444;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6955, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 444;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 444;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6966, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 444;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 444;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6977, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 444;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 444;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6988, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 6989, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 445;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 6995, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 445;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 445;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7006, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7007, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 446;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7013, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 446;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7019, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7020, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 447;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7026, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7027, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 448;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7033, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 448 & 65535, 7034, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7035, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 449;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7041, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 449;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7047, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 450;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 450;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 450;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7063, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 450;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 450;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7074, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 450 & 65535, 7075, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7076, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 451;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 451;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 451;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7092, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 452;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 452;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 452;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7108, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 452 & 65535, 7109, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7110, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 453;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 453;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7121, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 454;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7127, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 454;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7133, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 454 & 65535, 7134, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7135, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 455;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7141, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 455;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 455;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7152, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 455;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7158, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 455;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7164, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7165, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 456;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7171, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 456;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7177, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 456 & 65535, 7178, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7179, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 457;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7185, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 458;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 458;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 458;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7201, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 458;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7207, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 458;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7213, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 458;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 458;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7224, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 458 & 65535, 7225, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7226, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 459;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7232, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 460;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 460;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 460;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7248, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 460 & 65535, 7249, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7250, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 461;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7256, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7257, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 462;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7263, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 462;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 462;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 462;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 462;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7284, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 462;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 462;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7295, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 462;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7301, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 462 & 65535, 7302, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7303, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 463;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7309, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 464;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7315, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 464;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7321, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 464 & 65535, 7322, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7323, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 465;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7329, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7330, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 466;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 466;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7341, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 466 & 65535, 7342, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7343, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 467;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 467;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7354, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7355, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 468;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7361, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 468;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7367, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 468;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7373, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 468 & 65535, 7374, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7375, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 469;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7381, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 470;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7387, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 470 & 65535, 7388, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7389, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 471;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7395, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 471;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 471;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7406, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 471;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 471;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7417, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 471;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7423, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 471;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7429, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7430, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 472;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7436, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 472 & 65535, 7437, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7438, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 473;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7444, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 473;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7450, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 473;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7456, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7457, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 474;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 474;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 474;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7473, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 474 & 65535, 7474, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7475, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 475;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 475;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7486, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 476;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 476;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7497, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 476 & 65535, 7498, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7499, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 477;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7505, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 478;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7511, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 478 & 65535, 7512, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7513, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 479;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 479;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7524, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7525, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 480;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 480;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7536, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 480;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7542, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7543, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 481;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7549, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7550, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 482;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7556, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7557, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 483;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7563, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 484;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7569, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 485;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7575, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 486;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7581, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7582, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 487;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7588, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 487;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 487;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 487;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7604, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 488;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7610, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 488;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7616, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 489;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7622, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7623, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 490;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7629, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 490;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 490;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7640, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 490;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7646, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 490;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 490;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7657, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7658, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 491;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7664, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 491;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7670, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 492;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7676, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 493;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7682, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7683, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 494;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7689, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 494;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 494;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7700, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 495;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7706, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 496;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 496;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7717, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 496;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7723, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 496;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7729, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 496;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7735, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7736, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 497;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7742, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7743, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 498;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7749, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 499;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 499;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7760, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 500;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 500;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 500;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7776, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 501;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7782, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 501;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7788, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7789, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 502;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 502;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7800, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 503;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7806, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7807, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 504;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7813, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7814, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 505;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7820, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7821, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 506;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7827, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 506;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7833, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 507;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7839, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 508;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7845, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 509;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7851, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7852, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 510;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 510;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7863, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 511;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7869, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 511;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7875, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 511;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7881, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 511;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 511;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7892, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7893, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 512;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 512;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 512;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 512;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7914, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 512;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 512;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7925, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 512 & 65535, 7926, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7927, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 513;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7933, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 513;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 513;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7944, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 514;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7950, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 514 & 65535, 7951, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7952, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 515;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 7958, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 516;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 516;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 7969, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 516 & 65535, 7970, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 7971, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 517;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7977, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 7978, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 518;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 518;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 518;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 7994, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 518;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8000, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 518 & 65535, 8001, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8002, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 519;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8008, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 520;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8014, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 520;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8020, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 520;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 520;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 520;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 520;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8041, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 520;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 520;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 520;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 520;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8062, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 520;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8068, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 520;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 520;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8079, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 520;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 520;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 520;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8095, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 520 & 65535, 8096, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8097, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 521;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8103, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 522;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 522;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8114, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 522 & 65535, 8115, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8116, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 523;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8122, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8123, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8129, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8140, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8171, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8177, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8183, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8209, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 524;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 524;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8220, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 524 & 65535, 8221, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8222, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 525;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8228, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 526;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8234, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 526 & 65535, 8235, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8236, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 527;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 527;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 527;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 527;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8257, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8258, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 528;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8264, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 528 & 65535, 8265, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8266, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 529;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8272, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 529;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 529;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 529;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8288, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 530;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8294, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 530 & 65535, 8295, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8296, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 531;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8302, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 532;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8308, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 532;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8314, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 532;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8320, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 532 & 65535, 8321, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8322, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 533;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8328, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 534;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8334, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 534 & 65535, 8335, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8336, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 535;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8342, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 536;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 536;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 536;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8358, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 536 & 65535, 8359, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8360, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 537;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8366, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 538;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 538;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 538;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 538;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 538;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 538;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 538;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 538;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 538;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8412, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 538;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8418, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 538 & 65535, 8419, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8420, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 539;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 539;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8431, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 540;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8437, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 540;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8443, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 540 & 65535, 8444, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8445, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 541;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8451, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8452, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 542;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8458, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 542;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 542;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8469, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 542;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8475, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 542 & 65535, 8476, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8477, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 543;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 543;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8488, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8489, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 544;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 544;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 544;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8505, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 545;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8511, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 545;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8517, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8518, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 546;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8524, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 546;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8530, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8531, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 547;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8537, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8538, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 548;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8544, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 548;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8550, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 548;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 548;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8561, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 549;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8567, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 550;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8573, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 551;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8579, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 552;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8585, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8586, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 553;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8592, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 553;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8598, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 554;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 554;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8609, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8610, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 555;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 555;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8621, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 555;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 555;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8632, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 555;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8638, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 555;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8644, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8645, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 556;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8651, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 556;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8657, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 557;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8663, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 557;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8669, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 557;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8675, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 557;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8681, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8682, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 558;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 558;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8693, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 559;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8699, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8700, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 560;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8706, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 561;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 561;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8717, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8718, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 562;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8724, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8725, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 563;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8731, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 563;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8737, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 564;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 564;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8748, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 564;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 564;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8759, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 564;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8765, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8766, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 565;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 565;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8777, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 566;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8783, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8784, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 567;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 567;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8795, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 568;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8801, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 569;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8807, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8808, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 570;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8814, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 570;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8820, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8821, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 571;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8827, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8828, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 572;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8834, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 573;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 573;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8845, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8846, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 574;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 574;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8857, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 574;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8863, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 574;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8869, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 8870, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 575;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8876, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 575;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 575;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8887, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 575;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8893, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 575;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8899, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 576;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 576;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 576;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 576;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8920, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 576 & 65535, 8921, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8922, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 577;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 8928, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 578;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 578;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8939, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 578;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8945, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 578;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 578;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 578;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8961, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 578;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8967, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 578;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 8973, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 578 & 65535, 8974, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 8975, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 579;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8981, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 579;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 579;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 8992, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 579;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 579;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 579;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9008, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 579;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9014, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9015, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 580;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9021, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 580 & 65535, 9022, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9023, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 581;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9029, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 582;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9035, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 582;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 582;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9046, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 582;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 582;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9057, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 582;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 582;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 582;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9073, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 582 & 65535, 9074, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9075, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 583;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9081, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9082, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 584;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 584;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9093, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 584;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 584;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9104, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 584;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 584;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9115, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 584 & 65535, 9116, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9117, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 585;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 585;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9128, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9129, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 586;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 586;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 586;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9145, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 586;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9151, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 586 & 65535, 9152, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9153, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 587;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 587;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9164, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 588;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 588;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9175, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 588 & 65535, 9176, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9177, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 589;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9183, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 589;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9189, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 590;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 590;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9200, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 590 & 65535, 9201, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9202, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 591;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9208, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 591;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9214, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 592;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 592;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 592;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 592;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 592;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9240, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 592;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9246, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 592;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 592;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 592;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9262, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 592;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9268, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 592;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9274, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 592 & 65535, 9275, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9276, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 593;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 593;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9287, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 594;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9293, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 594 & 65535, 9294, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9295, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 595;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9301, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 595;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 595;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9312, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9313, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 596;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 596;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9324, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 596 & 65535, 9325, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9326, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 597;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 597;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9337, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 597;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9343, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9344, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 598;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 598;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 598;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9360, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 598 & 65535, 9361, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9362, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 599;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9368, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9369, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 600;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 600;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 600;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9385, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 600 & 65535, 9386, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9387, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 601;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 601;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9398, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 601;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 601;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9409, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 602;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9415, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 602 & 65535, 9416, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9417, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 603;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9423, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 604;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9429, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 604 & 65535, 9430, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9431, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 605;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9437, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 606;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 606;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 606;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 606;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9458, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 606 & 65535, 9459, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9460, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 607;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9466, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 607;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 607;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9477, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 608;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9483, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 608;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9489, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9490, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 609;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9496, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9497, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 610;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9503, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9504, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 611;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9510, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 611;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 611;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 611;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9526, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 612;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9532, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 612;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 612;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 612;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9548, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 613;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9554, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 614;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9560, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 615;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9566, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 616;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9572, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9573, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 617;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9579, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 617;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 617;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9590, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 618;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9596, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 618;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9602, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9603, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 619;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9609, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 620;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9615, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9616, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 621;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 621;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9627, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 622;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9633, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9634, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 623;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 623;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9645, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9646, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 624;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 624;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9657, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 624;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9663, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9664, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 625;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9670, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 626;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9676, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 627;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 627;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9687, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9688, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 628;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 628;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 628;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9704, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9705, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 629;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9711, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 630;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9717, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 631;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9723, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9724, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 632;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9730, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9731, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 633;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9737, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9738, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 634;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9744, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 635;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9750, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 636;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9756, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 637;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9762, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9763, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 638;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9769, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 638;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9775, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 639;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9781, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 640;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 640;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 640;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 640;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 640;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9807, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 640 & 65535, 9808, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9809, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 641;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9815, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9816, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 642;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9822, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 642;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9828, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 642 & 65535, 9829, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9830, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 643;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9836, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9837, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 644;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9843, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 644;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9849, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 644;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9855, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 644;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9861, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 644;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9867, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 644;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 644;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9878, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 644;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9884, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 644 & 65535, 9885, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9886, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 645;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9892, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 645;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9898, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9899, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 646;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9905, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 646;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 646;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 646;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9921, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 646 & 65535, 9922, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9923, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 647;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 647;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9934, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 648;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 648;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9945, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 648;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9951, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 648 & 65535, 9952, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9953, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 649;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 9959, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 650;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 650;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9970, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 650 & 65535, 9971, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9972, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 651;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9978, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 651;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9984, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 651;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 9990, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 9991, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 652;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 9997, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 652 & 65535, 9998, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 9999, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 653;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 653;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10010, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10011, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 654;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 654;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 654;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10027, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 654 & 65535, 10028, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10029, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 655;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 655;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10040, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10041, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 656;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 656;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10052, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 656 & 65535, 10053, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10054, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 657;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10060, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 658;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10066, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 658;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 658;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10077, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 658 & 65535, 10078, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10079, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 659;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10085, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 660;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 660;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10096, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 660;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 660;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 660;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 660;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10117, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 660;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10123, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 660;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10129, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 660 & 65535, 10130, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10131, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 661;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10137, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10138, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 662;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10144, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 662 & 65535, 10145, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10146, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 663;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10152, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10153, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10184, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 664;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 664;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10215, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 664;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10221, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 664 & 65535, 10222, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10223, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 665;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10229, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 666;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 666;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10240, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 666;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 666;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 666;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10256, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 666 & 65535, 10257, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10258, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 667;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 667;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10269, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10270, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 668;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10276, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 668 & 65535, 10277, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10278, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 669;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10284, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 670;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10290, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 670 & 65535, 10291, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10292, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 671;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10298, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10299, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 672;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10305, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 672;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10311, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 672;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10317, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10318, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 673;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10324, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 673;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10330, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 674;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 674;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10341, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 674;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10347, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 675;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 675;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10358, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 676;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10364, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10365, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 677;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 677;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 677;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10381, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 677;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10387, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10388, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 678;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10394, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10395, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 679;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10401, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10402, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 680;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10408, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 681;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10414, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 682;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10420, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 683;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10426, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 684;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10432, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 684;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10438, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 685;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10444, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 685;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10450, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10451, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 686;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 686;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10462, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 686;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 686;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10473, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 687;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10479, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 687;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10485, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 688;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10491, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10492, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 689;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10498, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 690;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 690;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10509, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 690;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10515, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 690;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10521, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 690;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10527, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10528, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 691;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10534, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 692;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10540, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10541, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 693;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10547, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 693;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10553, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 694;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10559, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 695;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10565, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10566, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 696;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10572, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 697;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10578, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10579, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 698;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10585, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10586, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 699;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 699;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10597, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 700;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 700;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10608, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10609, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 701;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 701;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10620, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 701;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10626, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 701;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10632, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 701;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10638, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 702;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 702;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 702;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 702;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10659, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 702;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10665, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 703;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10671, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 703;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10677, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 704;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 704;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10688, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 704;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 704;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 704;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10704, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 704;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10710, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 704 & 65535, 10711, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10712, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 705;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10718, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 705;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 705;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10729, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10730, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 706;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 706;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10741, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 706 & 65535, 10742, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10743, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 707;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10749, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 707;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10755, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10756, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 708;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10762, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 708 & 65535, 10763, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10764, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 709;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10770, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 709;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10776, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 710;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 710;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10787, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 710;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 710;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 710;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 710;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10808, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 710;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 710;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 710;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 710;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10829, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 710;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 710;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 710;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10845, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 710;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10851, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 710 & 65535, 10852, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10853, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 711;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 711;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10864, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 711;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 711;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10875, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 711;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10881, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 711;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 711;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 711;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10897, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 10898, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 712;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 712;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 10909, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 712 & 65535, 10910, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 10911, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 713;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10917, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 713;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 10923, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10929, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10945, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 10966, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11007, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11018, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 714;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11024, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 714;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11035, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 714 & 65535, 11036, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11037, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 715;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 715;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 715;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 715;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11058, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11059, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 716;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11065, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 716 & 65535, 11066, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11067, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 717;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11073, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 717;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11079, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11085, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11101, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11122, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11138, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11144, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11160, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 718;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11166, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 718;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 718;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11177, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 718 & 65535, 11178, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11179, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 719;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11185, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 719;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11191, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 719;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11197, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 719;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11203, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 720;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11209, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 720 & 65535, 11210, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11211, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 721;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 721;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11222, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11223, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 722;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11229, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 722;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 722;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 722;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11245, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 722;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 722;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11256, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 722 & 65535, 11257, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11258, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 723;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11264, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11265, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 724;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11271, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 724;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 724;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11282, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 724 & 65535, 11283, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11284, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 725;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11290, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 726;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11296, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 726;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11302, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 726 & 65535, 11303, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11304, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 727;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11310, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11311, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 728;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11317, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 728 & 65535, 11318, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11319, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 729;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11325, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 729;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11331, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11332, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 730;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 730;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11343, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 730;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11349, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 730;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 730;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11360, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 730;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 730;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11371, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 730;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11377, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 730 & 65535, 11378, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11379, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 731;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11385, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 731;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11391, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 732;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 732;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11402, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 732;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11408, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 732 & 65535, 11409, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11410, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 733;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11416, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11417, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 734;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 734;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11428, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 734;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11434, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 734 & 65535, 11435, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11436, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 735;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11442, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11443, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 736;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11449, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11450, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 737;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11456, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11457, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 738;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11463, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 738;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11469, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 738;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11475, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11476, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 739;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11482, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11483, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 740;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11489, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 741;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 741;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11500, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11501, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 742;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 742;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11512, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 743;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11518, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 744;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11524, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 744;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 744;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 744;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11540, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 745;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11546, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11547, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 746;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11553, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 747;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 747;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 747;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11569, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 747;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11575, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11576, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 748;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11582, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 749;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11588, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11589, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 750;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11595, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11596, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 751;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11602, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11603, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 752;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11609, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 752;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11615, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 752;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11621, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 752;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 752;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11632, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11633, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 753;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11639, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11640, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 754;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11646, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11647, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 755;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11653, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11654, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 756;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 756;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11665, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 756;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11671, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 757;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11677, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 758;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11683, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11684, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 759;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11690, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 759;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11696, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 760;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11702, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11703, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 761;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 761;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11714, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 761;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11720, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 761;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 761;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11731, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11732, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 762;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11738, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 762;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11744, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11745, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 763;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11751, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 764;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 764;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 764;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11767, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11768, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 765;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11774, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11775, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 766;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11781, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11782, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 767;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 767;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 767;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 767;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 767;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11808, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 11809, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 768;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11815, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 768;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 768;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 768;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11831, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 768 & 65535, 11832, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11833, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 769;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11839, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 769;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11845, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 769;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11851, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 769;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 769;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11862, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 769;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 769;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11873, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 769;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11879, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 769;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11885, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 770;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 770;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11896, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 770;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11902, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 770 & 65535, 11903, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11904, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 771;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11910, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 771;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11916, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 772;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 772;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 772;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11932, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 772 & 65535, 11933, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11934, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 773;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11940, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 774;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11946, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 774;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 774;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 774;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11962, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 774;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 774;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 11973, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 774;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 774;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 774;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 11989, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 774 & 65535, 11990, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 11991, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 775;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 11997, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 776;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12003, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 776 & 65535, 12004, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12005, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 777;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12011, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 778;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12017, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 778 & 65535, 12018, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12019, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 779;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12025, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 779;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12031, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 779;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12037, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 779;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 779;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12048, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 780;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 780;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 780;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 780;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 780;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 780;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 780;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 780;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12089, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 780;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12095, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 780 & 65535, 12096, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12097, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 781;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12103, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 781;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12109, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12110, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 782;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 782;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12121, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 782 & 65535, 12122, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12123, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 783;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 783;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 783;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12139, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12140, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 784;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 784;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 784;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 784;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12161, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 784;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12167, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 784 & 65535, 12168, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12169, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 785;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12175, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 786;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 786;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 786;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 786;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 786;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12201, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 786;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 786;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 786;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 786;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12222, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 786;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12228, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 786;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12234, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 786;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12240, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 786;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 786;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 786;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12256, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 786 & 65535, 12257, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12258, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 787;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 787;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12269, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 788;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 788;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 788;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12285, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 788 & 65535, 12286, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12287, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 789;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12293, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 789;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12299, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 789;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12305, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 789;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12311, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 790;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 790;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12322, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 790 & 65535, 12323, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12324, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 791;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12330, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 791;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 791;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12341, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 791;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12347, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 792;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 792;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12358, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 792 & 65535, 12359, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12360, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 793;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 793;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12371, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12372, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 794;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 794;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 794;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 794;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12393, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 794;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 794;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 794;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 794;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 794;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 794;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12424, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 794;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 794;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12435, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 794;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12441, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 794;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12447, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 794 & 65535, 12448, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12449, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 795;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12455, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 796;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12461, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 796 & 65535, 12462, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12463, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 797;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 797;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12474, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12475, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 798;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 798;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 798;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12491, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 798;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12497, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 798;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12503, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 798 & 65535, 12504, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12505, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 799;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12511, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 799;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12517, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 800;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 800;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12528, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 800;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12534, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 801;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12540, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 801;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12546, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12547, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 802;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12553, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 802;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12559, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12560, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 803;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 803;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12571, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12572, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 804;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 804;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12583, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 805;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 805;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12594, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 805;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 805;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12605, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12606, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 806;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12612, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 807;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12618, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 808;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12624, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12625, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 809;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12631, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 810;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12637, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 810;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12643, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 811;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12649, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 812;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12655, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12656, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 813;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12662, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 813;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12668, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 814;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 814;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 814;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 814;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12689, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 814;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12695, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12696, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 815;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 815;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12707, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 815;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12713, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 815;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12719, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 815;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12725, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 815;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12731, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 815;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12737, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 816;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12743, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 817;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12749, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 817;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12755, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12756, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 818;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12762, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12763, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 819;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12769, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 820;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12775, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 820;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12781, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 821;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12787, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 822;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12793, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 822;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12799, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 823;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12805, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 823;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12811, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12812, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 824;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 824;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12823, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 825;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12829, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 826;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 826;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12840, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 827;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12846, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 828;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12852, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12853, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 829;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12859, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12860, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 830;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12866, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 830;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12872, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12873, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 831;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12879, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 831;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12885, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 831;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12891, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 832;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 832;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12902, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 832;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12908, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 832 & 65535, 12909, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12910, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 833;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 833;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12921, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 834;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12927, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 834 & 65535, 12928, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12929, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 835;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12935, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 835;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12941, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 836;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12947, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 836 & 65535, 12948, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12949, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 837;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 12955, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 838;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 838;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12966, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 838;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 838;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 12977, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 838 & 65535, 12978, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 12979, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 839;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 839;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 839;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 12995, "downsample_verilog.data_out_valid");
  my_assert(top->data_in_ready, 1 & 1, 12996, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 840;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 840;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 840;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 840;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 840;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 13022, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 840 & 65535, 13023, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 13024, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 841;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 13030, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 842;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 13036, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 842 & 65535, 13037, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 13038, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 843;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 13044, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 844;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 844;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 13055, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 844;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 844;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 844;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 844;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 13076, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 844;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 844;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 844;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 844;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 1 & 1, 13097, "downsample_verilog.data_out_valid");
  my_assert(top->data_out_data, 844 & 65535, 13098, "downsample_verilog.data_out_data");
  my_assert(top->data_in_ready, 1 & 1, 13099, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 845;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 13105, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 845;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 845;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 13116, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 845;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 845;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_in_ready, 1 & 1, 13127, "downsample_verilog.data_in_ready");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 846;
  top->data_out_ready = 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  my_assert(top->data_out_valid, 0 & 1, 13133, "downsample_verilog.data_out_valid");
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 846;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 846;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 0;
  top->data_in_data = 846;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->data_in_valid = 1;
  top->data_in_data = 846;
  top->data_out_ready = 0;
  top->eval();
  main_time++;
  #if VM_TRACE
  tracer->dump(main_time);
  #endif
  top->eval();
  top->CLK ^= 1;
  top->eval();
  main_time++;
  #if VM_TRACE
  #endif
  top->eval();