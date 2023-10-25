#ifndef MINI_UART_H
#define MINI_UART_H

#include <iostream>
#include <systemc.h>
#include <cstdlib>
#include "clk_unit.h"
#include "tx_unit.h"
#include "rx_unit.h"


SC_MODULE(MiniUart)
{

    //Port Declaration
  
    sc_in<bool> sys_clk;
    sc_in<bool> reset;
    sc_in<sc_logic> ce,rd,wr;
    sc_in<sc_lv<2>> addr;
    sc_in<sc_lv<8>> data_in;
    sc_in<bool> rxd; 

    sc_out<bool> txd;
    sc_out<sc_lv<8>> data_out;
    sc_out<bool> irq_rx;
    sc_out<bool> irq_tx;

    // Channel Members
    sc_lv<8> ctrl_status_reg="00000000"; 

    sc_signal<bool> en_tx, load,reg_empty, buf_empty;
    sc_signal<bool> en_rx, read, data_rdy, output_err, frame_err;
    sc_signal<sc_lv<8>> tx_data, rx_data;

    //Sub-modules
    ClkUnit ClkUnit_inst;
    TxUnit  TxUnit_inst;
    RxUnit  RxUnit_inst;

    // Constructor
    SC_CTOR(MiniUart):    
                sys_clk("sys_clk"), 
                reset("reset"), 
                ce("ce"),
                rd("rd"), 
                wr("wr"),
                addr("addr"),
                data_in("data_in"),
                rxd("rxd"),txd("txd"), 
                data_out("data_out"),
                irq_rx("irq_rx"),
                irq_tx("irq_tx"), 
                ClkUnit_inst("ClkUnit_inst"), 
                TxUnit_inst("TxUnit_inst"), 
                RxUnit_inst("RxUnit_inst")
    {
        
		ClkUnit_inst.sys_clk(sys_clk);
		ClkUnit_inst.reset(reset);
		ClkUnit_inst.en_tx(en_tx);
		ClkUnit_inst.en_rx(en_rx);

		TxUnit_inst.sys_clk(sys_clk);
		TxUnit_inst.reset(reset);
		TxUnit_inst.enable(en_tx);
		TxUnit_inst.load(load);
		TxUnit_inst.data_in(tx_data);
		TxUnit_inst.reg_empty(reg_empty);
		TxUnit_inst.buf_empty(buf_empty);
		TxUnit_inst.txd(txd);

		RxUnit_inst.sys_clk(sys_clk);
		RxUnit_inst.reset(reset);
		RxUnit_inst.enable(en_rx);
		RxUnit_inst.read(read);
		RxUnit_inst.data_out(rx_data);
		RxUnit_inst.frame_err(frame_err);
		RxUnit_inst.output_err(output_err);
		RxUnit_inst.data_rdy(data_rdy);
		RxUnit_inst.rxd(rxd);

        SC_THREAD(interfaceProcess_thread);
            sensitive << ce << rd << wr << addr;
        SC_THREAD(combinational_thread);
            sensitive << output_err << frame_err << data_rdy << buf_empty << reg_empty;
    }

    //Processes
    void interfaceProcess_thread();
    void combinational_thread();

};

#endif