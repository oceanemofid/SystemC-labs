
#ifndef _RTL_MEMORY_H_
#define _RTL_MEMORY_H_

#include <systemc.h>
#include "helper_fct.h"

template<int ADDR_SIZE=6,int WORD_SIZE=8,int MEM_SIZE=100>

SC_MODULE(RTL_memory)
{
    //port
    sc_in<bool> clk,enable,rd_we;
    sc_in<sc_uint< ADDR_SIZE>> addr;
    sc_in<sc_lv< WORD_SIZE>> data_in;
    sc_out<sc_lv< WORD_SIZE>> data_out;

    //Channel
    sc_lv<WORD_SIZE> buffer[MEM_SIZE];


        SC_CTOR(RTL_memory):clk("clk"),
                            enable("enbale"),
                            rd_we("rd_we"),
                            addr("addr"),
                            data_in("data_in"),
                            data_out("data_out")
   {
    SC_METHOD(process_memory);
    sensitive<<clk.neg();
   }

   void process_memory()
   {
        if(enable==true)
        {
            //true --> read mode , false --> write mode
            if(rd_we==true)
            {
            //read mode
                //judge if addr out of range
                if(addr->read()<MEM_SIZE)
                {
                    //if not , data out = le text de buffer in this addr
                    data_out->write(buffer[addr->read()]);
                    DISPLAY("read data "<<buffer[addr->read()]<<" from buffer addr"<<addr->read());
                }
                else
                     DISPLAY("out of range");
             
            }
            //write mode
            else 
            {
                if(addr->read()<MEM_SIZE)
                {
                    buffer[addr->read()]=data_in->read();
                    DISPLAY("write data "<<buffer[addr->read()]<<" in buffer addr"<<addr->read());
                }
                else
                    DISPLAY("out of range");
            }
        }
    
   }

        
};

#endif
