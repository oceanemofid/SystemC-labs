#ifndef _DF_ADDER_H_
#define _DF_ADDER_H_

#include <systemc.h>
#include "helper_fct.h"


SC_MODULE(df_adder){
    //IN OUT
    sc_fifo_in<double> const_value, feedback;
    sc_fifo_out<double> added_value;

    //CONSTRUCTOR
    SC_CTOR(df_adder) : const_value ("const_value"),
                            feedback("feedback"),
                            added_value("added_value")
    {
        //REGISTRATING THREAD  
        SC_THREAD(df_adder_thread);
    }

//PROCESS
void df_adder_thread();

};
#endif