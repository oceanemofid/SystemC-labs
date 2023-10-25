
#include "benches.h"
#include "clk_unit.h"
#include "tx_unit.h"
#include "rx_unit.h"
#include "mini_uart.h"
#include "testbench.h"

void test_mini_uart()
{
	//sc_set_time_resolution(1,SC_NS);
    sc_signal<bool> clk;
	sc_signal<bool> reset, irq_rx, irq_tx, txd_rxd;
	sc_signal_resolved ce, rd, wr;
	sc_signal_rv<2> addr;
	sc_signal_rv<8> data;

    // Deaclare MiniUart
    MiniUart MiniUart_inst("MiniUart");
		MiniUart_inst.sys_clk(clk);
		MiniUart_inst.reset(reset);
		MiniUart_inst.ce(ce);
		MiniUart_inst.rd(rd);
		MiniUart_inst.wr(wr);
		MiniUart_inst.addr(addr);
		MiniUart_inst.data_in(data);
		MiniUart_inst.data_out(data);
		MiniUart_inst.irq_rx(irq_rx);
		MiniUart_inst.irq_tx(irq_tx);
		MiniUart_inst.rxd(txd_rxd);
		MiniUart_inst.txd(txd_rxd);

   // Declare TestBench
	TestBench TestBench_inst("TestBench_inst");
		TestBench_inst.sys_clk(clk);
		TestBench_inst.reset(reset);
		TestBench_inst.ce(ce);
		TestBench_inst.rd(rd);
		TestBench_inst.wr(wr);
		//TestBench_inst.rxd_txd(txd_rxd);
		TestBench_inst.addr(addr);
		TestBench_inst.data_in(data);
		TestBench_inst.data_out(data);
		TestBench_inst.irq_rx(irq_rx);
		TestBench_inst.irq_tx(irq_tx);
        //TestBench_inst.Miniuart_inst(Miniuart_inst);
    
	// Trace
	sc_trace_file *tf = sc_create_vcd_trace_file("wave_miniuart");
	sc_write_comment(tf, " Mini Uart Simulation ");

	sc_trace(tf,clk, "clk");
	sc_trace(tf,reset,"reset");
	sc_trace(tf,ce,"ce");
	sc_trace(tf,rd,"rd");
	sc_trace(tf,wr,"wr");
	sc_trace(tf,addr,"addr");
	sc_trace(tf,data,"data");
	sc_trace(tf,irq_rx,"irq_rx");
	sc_trace(tf,irq_tx,"irq_tx");
	sc_trace(tf,txd_rxd,"txd_rxd");

    // Run simulation
	sc_start(10, SC_MS);
    // Close Trace
	sc_close_vcd_trace_file(tf);
}
