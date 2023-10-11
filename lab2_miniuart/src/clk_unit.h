#ifndef CLK_UNIT_H
#define CLK_UNIT_H

#include <systemc.h>
#include "helper_fct.h"

SC_MODULE(ClkUnit) {
	// Port Declaration
	sc_in<bool> sys_clk;
	sc_in<bool> reset;
	sc_out<bool> en_tx;
	sc_out<bool> en_rx;

	// Data Members
	int count_tx=0;
	int count_rx=0;

	const float cyc_tx=4160;
	const float cyc_rx=260;

	// Constructor
	SC_CTOR(ClkUnit): sys_clk("sys_clk"),
					  reset("reset"),
					  en_tx("en_tx"),
					  en_rx("en_rx"){
		
		SC_THREAD(ClkUnit_THREAD);
		sensitive << sys_clk.pos();
		DISPLAY("cyc_tx="<<cyc_tx);
		DISPLAY("cyc_rx="<<cyc_rx);

	}

	// Processes
	void ClkUnit_THREAD();
};

#endif
