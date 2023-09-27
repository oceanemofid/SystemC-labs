#include <df_display.h>


void df_display::df_display_thread(){
    int cpt;
    double val;
    while(cpt < N){
        val = result->read();
        DISPLAY("DF_DISPLAY : " << val);
        cpt++;
    }
}