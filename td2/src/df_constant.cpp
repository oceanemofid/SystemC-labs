#include "helper_fct.h"
#include <df_constant.h>

void df_constant::df_constant_thread(){
    for(;;){
        wait(1, SC_MS);
        const_value->write(cst);
        DISPLAY("df_constant : send value = " << cst);
    }
}