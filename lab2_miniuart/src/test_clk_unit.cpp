#include <systemc.h>
#include "clk_unit.h"
#include "helper_fct.h"

void test_clk_unit() {
	// Declare signal
	sc_clock clk("clk",25,SC_NS);	// 40MHz
	sc_signal<bool> sys_clk;
	sc_signal<bool> reset;
	sc_signal<bool> en_tx;
	sc_signal<bool> en_rx;
	
	// Declare ClkUnit
	ClkUnit ClkUnit_inst("ClkUnit");
			ClkUnit_inst.sys_clk(clk);
			ClkUnit_inst.reset(reset);
			ClkUnit_inst.en_tx(en_tx);
			ClkUnit_inst.en_rx(en_rx);
		

	// Trace
	sc_trace_file *tf = sc_create_vcd_trace_file("wave_clkunit");
	sc_write_comment(tf, "Simulation of Clk Unit");
	tf->set_time_unit(1, SC_NS);
	sc_trace(tf,clk,"clk");
	sc_trace(tf,reset,"reset");
	sc_trace(tf,en_tx,"en_tx");
	sc_trace(tf,en_rx,"en_rx");

	

	cout << "simulation ..."  << endl;

	for (int i=0; i<5; i++) {
		sc_start(1, SC_MS);
		cout << ".";
	}
	cout << endl;

	// CLose Trace
	sc_close_vcd_trace_file(tf);

	//end of simulation
	DISPLAY("END OF SIMULATION");

}
