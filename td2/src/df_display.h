#ifndef _DF_DISPLAY_H_
#define _DF_DISPLAY_H_

#include <systemc.h>
#include "helper_fct.h"


SC_MODULE(df_display){
    //IN OUT
    sc_fifo_in<double> result;
    int N;
    
    SC_HAS_PROCESS(df_display);

    df_display(sc_module_name name, int N) : sc_module(name), result("result"),N(N)
    {
                SC_THREAD(df_display_thread);
    }

void df_display_thread();

};
#endif