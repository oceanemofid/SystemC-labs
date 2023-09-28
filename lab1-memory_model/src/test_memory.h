#ifndef TEST_MEMORY_H
#define TEST_MEMORY_H
#include <systemc.h>
#include "rtl_memory.h"



SC_MODULE(test_memory){

    //predefine
    static const int ADDR_SIZE=6;
    static const int WORD_SIZE=8;
    static const int MEM_SIZE=100;

    RTL_memory<ADDR_SIZE,WORD_SIZE,MEM_SIZE> RTL_memory_inst;
    sc_clock clk;
    sc_signal<bool> enable;
    sc_signal<bool> rd_we;
    sc_signal<sc_uint< ADDR_SIZE>> addr;
    sc_signal<sc_lv< WORD_SIZE>> data_in;
    sc_signal<sc_lv< WORD_SIZE>> data_out;

    sc_trace_file *tf;

    //constructeur
    SC_CTOR(test_memory): RTL_memory_inst("RTL_memory_inst"),
                          clk("clock",1,SC_MS),
                          enable("enbale"),
                          rd_we("rd_we"),
                          addr("addr"),
                          data_in("data_in"),
                          data_out("data_out")
        {

        //port map of RTL_memory
        RTL_memory_inst.enable(enable);
        RTL_memory_inst.rd_we(rd_we);
        RTL_memory_inst.clk(clk);
        RTL_memory_inst.addr(sc_uint<ADDR_SIZE> addresse_file("wave");
            sc_write_comment(tf,"Simulation of RTL memory");
            sc_trace(tf,clk,"clk");
            sc_trace(tf,enable,"enable");
            sc_trace(tf,rd_we,"rd_we");
            sc_trace(tf,addr,"addr");
            sc_trace(tf,data_in,"data_in");
            sc_trace(tf,data_out,"data_out"); 

        void test_thread()
        {
           //test1 write
            write_data(addr, rd_we, enable, data_in, 0x01, 11);

            //write3
            write_data(addr, rd_we, enable, data_in, 0x03, 12);


            //test1 read
            read_data(addr, rd_we, enable, data_out, 0x01);
            
            //test2 read
            read_data(addr, rd_we, enable, data_out, 0x02);

            //test3 read
            read_data(addr, rd_we, enable, data_out, 0x03);


        }
        
    };

    void read_data(sc_uint<ADDR_SIZE> addr, sc_signal<bool> rd_we, sc_signal<bool> enable, sc_lv<WORD_SIZE> data_out, sc_uint<ADDR_SIZE> address){
            addr.write(address);
            enable.write(true);
            rd_we.write(true);
            data_out.read();
            wait(5,SC_MS);
        }
        void write_data(sc_uint<ADDR_SIZE> addr, sc_signal<bool> rd_we, sc_signal<bool> enable, sc_lv<WORD_SIZE> data_in, sc_uint<ADDR_SIZE> address, sc_lv<WORD_SIZE> value){
            addr.write(address);
            enable.write(true);
            rd_we.write(false);
            data_in.write(value);
            wait(5,SC_MS);
        }
};

#endif
