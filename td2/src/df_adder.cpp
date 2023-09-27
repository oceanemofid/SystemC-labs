#include <df_adder.h>
#include "helper_fct.h"


void df_adder::df_adder_thread(){
    double val1, val2;
    for(;;){
        //Read 2 FIFO inputs
        val1 = const_value->read();
        val2 = feedback->read();

        wait(100, SC_NS);

        added_value->write(val1+val2);
        DISPLAY("df_adder:"<< val1 << " + " << val2 << " = " << val1+val2);
       
    }
}