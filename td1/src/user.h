#ifndef _USER_H_
#define _USER_H_

#include <systemc.h>
#include "helper_fct.h"

SC_MODULE(user){
    sc_out<double> period;
    sc_out<bool> reset, up_down, load;
    sc_out<int> data_in;

    SC_CTOR(user) : period("period"),
                        reset ("reset"),
                        up_down ("up_down"),
                        load ("load"),
                        data_in ("data_in")
                        {SC_THREAD(user_thread);}

    void user_thread();
};

#endif