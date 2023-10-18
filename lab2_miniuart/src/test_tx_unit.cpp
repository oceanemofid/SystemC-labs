#include <systemc.h>
#include "clk_unit.h"
#include "tx_unit.h"
#include "helper_fct.h"

void test_tx_unit() {
	// Declare signal
	sc_clock clk("clk",25,SC_NS);	// 40MHz
	sc_signal<bool> sys_clk;
	sc_signal<bool> reset;
	sc_signal<bool> en_tx;
	sc_signal<bool> en_rx;
    sc_signal<bool> load;
    sc_signal<sc_lv<wordsize>>data_in;
    sc_signal<bool> reg_empty;
    sc_signal<bool> buf_empty;
    sc_signal<bool> txd;
	
	// Declare ClkUnit
	ClkUnit ClkUnit_inst("ClkUnit");
			ClkUnit_inst.sys_clk(clk);
			ClkUnit_inst.reset(reset);
			ClkUnit_inst.en_tx(en_tx);
			ClkUnit_inst.en_rx(en_rx);
    
    // Declare TxUnit
    TxUnit  TxUnit_inst("TxUnit");
		    TxUnit_inst.sys_clk(clk);
		    TxUnit_inst.reset(reset);
		    TxUnit_inst.enable(en_tx);
		    TxUnit_inst.load(load);
            TxUnit_inst.data_in(data_in);
            TxUnit_inst.reg_empty(reg_empty);
            TxUnit_inst.buf_empty(buf_empty);
            TxUnit_inst.txd(txd);
		

	// Trace
	sc_trace_file *tf = sc_create_vcd_trace_file("wave_txunit");
	sc_write_comment(tf, "Simulation of Tx Unit");
	tf->set_time_unit(1, SC_NS);
	sc_trace(tf,clk,"clk");
	sc_trace(tf,reset,"reset");
	sc_trace(tf,en_tx,"en_tx");
    //sc_trace(tf,en_rx,"en_rx");
    sc_trace(tf,load,"load");
	sc_trace(tf,data_in,"data_in");
	sc_trace(tf,reg_empty,"reg_empty");
    sc_trace(tf,buf_empty,"buf_empty");
    sc_trace(tf,txd,"txd");

    
    //Reset
    DISPLAY("----------Reset----------");
    load.write(false);
    reset.write(true);
    sc_start(1,SC_US);
    reset.write(false);
    sc_start(1,SC_US);

    //Send data
    DISPLAY("----------Load and Send----------");
    data_in.write(0x69);
    load.write(true);
    sc_start(100,SC_NS);
    load.write(false);
    sc_start(1100,SC_US);

    //Send data
    DISPLAY("----------Load and Send----------");
    data_in.write(0x22);
    load.write(true);
    sc_start(100,SC_NS);
    load.write(false);
    sc_start(1100,SC_US);

	// CLose Trace
	sc_close_vcd_trace_file(tf);

	//end of simulation
	DISPLAY("END OF SIMULATION");

}