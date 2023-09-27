#include <df_fork.h>

void df_fork::df_fork_thread(){
    for (;;)
    {
        double val = added_value->read();
        feedback->write(val);
        result->write(val);
        DISPLAY("df_fork forking with value : " << val);
        wait(10, SC_NS);
    }
}