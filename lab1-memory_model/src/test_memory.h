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
        RTL_memory_inst.clk(clk);
        RTL_memory_inst.enable(enable);
        RTL_memory_inst.rd_we(rd_we);
        RTL_memory_inst.addr(addr);
        RTL_memory_inst.data_in(data_in);
        RTL_memory_inst.data_out(data_out);

       //trace wave
        tf = sc_create_vcd_trace_file("wave"); 
        sc_write_comment(tf,"Simulation of RTL memory");
        sc_trace(tf,clk,"clk");
        sc_trace(tf,enable,"enable");
        sc_trace(tf,rd_we,"rd_we");
        sc_trace(tf,addr,"addr");
        sc_trace(tf,data_in,"data_in");
        sc_trace(tf,data_out,"data_out"); 

        SC_THREAD(test_thread);
        }

        //deconstructeur
        ~test_memory(){
            sc_close_vcd_trace_file(tf);
        }


        void write_data(int Addr, bool Enable, bool Rd_we, int data){
            addr.write(Addr);
            enable.write(Enable);
            rd_we.write(Rd_we);
            data_in.write(data);
            wait(5,SC_MS);
        }

         void read_data(int Addr, bool Enable, bool Rd_we){
            addr.write(Addr);
            enable.write(Enable);
            rd_we.write(Rd_we);
            wait(5,SC_MS);
        }


        void test_thread()
        {
           //test write
            write_data(0x01, true, false,50);
            write_data(0x02, true, false,51);
            write_data(0x03, true, false,52);

            //test read
            read_data(0x01, true, true);      
            read_data(0x02, true, true);
            read_data(0x03, true, true);

        }
        
    };
       
#endif
