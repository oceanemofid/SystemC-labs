#include <systemc.h>
#include "tx_unit.h"
#include "rx_unit.h"
#include "clk_unit.h"
#include "benches.h"

void test_rx_unit() {
	// Declare signals and clocks
	sc_clock clk("clk", 25, SC_NS);
	sc_signal<bool> reset, en_tx, en_rx, load, reg_empty, buf_empty, txd_rxd;//(relation between txd_rxd);
	sc_signal<bool> read, data_rdy, output_err, frame_err;
	sc_signal<sc_lv<8>> data_in, data_out;

	// Declare ClkUnit
	ClkUnit ClkUnit_inst("ClkUnit");
	ClkUnit_inst.sys_clk(clk);
	ClkUnit_inst.reset(reset);
	ClkUnit_inst.en_tx(en_tx);
	ClkUnit_inst.en_rx(en_rx);

	// Declare TxUnit
	TxUnit TxUnit_inst("TxUnit");
	TxUnit_inst.sys_clk(clk);
	TxUnit_inst.reset(reset);
	TxUnit_inst.enable(en_tx);
	TxUnit_inst.load(load);
	TxUnit_inst.data_in(data_in);
	TxUnit_inst.reg_empty(reg_empty);
	TxUnit_inst.buf_empty(buf_empty);
	TxUnit_inst.txd(txd_rxd);


	// Declare RxUnit
	RxUnit RxUnit_inst("RxUnit");
	RxUnit_inst.sys_clk(clk);
	RxUnit_inst.reset(reset);
	RxUnit_inst.enable(en_rx);
	RxUnit_inst.read(read);
	RxUnit_inst.data_out(data_out);
	RxUnit_inst.frame_err(frame_err);
	RxUnit_inst.output_err(output_err);
	RxUnit_inst.data_rdy(data_rdy);
	RxUnit_inst.rxd(txd_rxd);

	//trace
	sc_trace_file* tf = sc_create_vcd_trace_file("wave_rxunit");
	sc_write_comment(tf, "Simulation of Rx Unit ...");

	// des signaux
	sc_trace(tf, clk, "clk");  
	sc_trace(tf, reset, "reset");
	sc_trace(tf, en_tx, "en_tx");
	sc_trace(tf, en_rx, "en_rx");
	sc_trace(tf, load, "load");
	sc_trace(tf, data_in, "data_in");
	sc_trace(tf, reg_empty, "reg_empty");
	sc_trace(tf, buf_empty, "buf_empty");
	sc_trace(tf, txd_rxd, "txd_rxd");
	sc_trace(tf, read, "read");
	sc_trace(tf, data_out, "data_out");
	sc_trace(tf, frame_err, "frame_err");
	sc_trace(tf, output_err, "output_err");
	sc_trace(tf, data_rdy, "data_rdy");


	DISPLAY("START SIMULATION");

	// Reset
	DISPLAY("----------Reset----------");
	load.write(false);
	read.write(false);
	reset.write(true);
	sc_start(1, SC_US);
	reset.write(false);
	sc_start(1, SC_US);


	// Load and send
	DISPLAY("----------Load and Send----------");
	data_in.write(0x69); 
	load.write(true);
	sc_start(100, SC_NS);
	load.write(false);
	//sc_start(800, SC_US);
	read.write(true);
	//sc_start(25, SC_NS);
	read.write(false);
	sc_start(1100, SC_US);


	DISPLAY("----------Load and Send----------");
	data_in.write(0xAA); 
	load.write(true);
	sc_start(100, SC_NS);
	load.write(false);
	sc_start(1100, SC_US);


	DISPLAY("----------Load and Send----------");
	data_in.write(0x56); 
	load.write(true);
	read.write(true);
	sc_start(100, SC_NS);
	read.write(false);
	load.write(false);
	sc_start(1100, SC_US);


	

	/*DISPLAY("----------Load and Send----------");
	data_in.write(0x30); 
	load.write(true);
	read.write(true);
	sc_start(100, SC_NS);
	read.write(false);
	load.write(false);
	sc_start(1100, SC_US);*/


	/* End of Simulation */
	DISPLAY("END OF SIMULATION");

	sc_close_vcd_trace_file(tf);
}