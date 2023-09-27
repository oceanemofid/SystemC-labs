#ifndef _DF_FORK_H_
#define _DF_FORK_H_

#include <systemc.h>
#include "helper_fct.h"


SC_MODULE(df_fork){
    //IN OUT
    sc_fifo_in<double> added_value;
    sc_fifo_out<double> result, feedback;

    SC_CTOR(df_fork) :  added_value("added_value"),
                        result ("result"),
                        feedback("feedback")
    {
        SC_THREAD(df_fork_thread);
    }

void df_fork_thread();

};
#endif