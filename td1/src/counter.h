#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <systemc.h>
#include "helper_fct.h"

SC_MODULE(counter){
    //IN OUT
    sc_in<double> period;
    sc_in<bool> reset, up_down, load;
    sc_in<int> data_in;
    sc_out<int> Q;

    SC_CTOR(counter) : period("period"),
                        reset ("reset"),
                        up_down ("up_down"),
                        load ("load"),
                        data_in ("data_in"),
                        Q ("Q"){
                            DISPLAY("thread registration");
                            SC_THREAD(counter_thread);
                        }

void counter_thread();

};
#endif