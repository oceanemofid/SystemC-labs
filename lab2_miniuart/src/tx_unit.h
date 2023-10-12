#ifndef TX_UNIT_H
#define TX_UNIT_H

#include <systemc.h>
#include "helper_fct.h"

#define wordsize 8

SC_MODULE(TxUnit) {
	// Port Declaration
	sc_in<bool> sys_clk;
	sc_in<bool> reset;
	sc_in<bool> enable;
	sc_in<bool> load;
    sc_in<sc_lv<wordsize>>data_in;
    sc_out<bool> reg_empty;
    sc_out<bool> buf_empty;
    sc_out<bool> txd;

	//Data member
	sc_lv<wordsize> reg;
    sc_lv<wordsize> buf;

	// Constructor
	SC_CTOR(TxUnit): sys_clk("sys_clk"),
					  reset("reset"),
					  enable("enable"),
					  load("load"),
                      data_in("data_in"),
                      reg_empty("reg_empty"),
                      buf_empty("buf_empty"),
                      txd("txd")
                      {
		
		SC_THREAD(TxUnit_THREAD);
		sensitive << sys_clk.pos();

	}

	// Processes
	void TxUnit_THREAD();
};

#endif
