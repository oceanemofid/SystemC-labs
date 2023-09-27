#ifndef _DF_CONSTANT_H_
#define _DF_CONSTANT_H_

#include <systemc.h>
#include "helper_fct.h"


SC_MODULE(df_constant){
    //DECLARATION
    sc_fifo_out<double> const_value;
    const double cst;

    //DATA

    //Ajouter de la macro pour utiliser le constructeur systemc
    SC_HAS_PROCESS(df_constant);

    //CONSTRUCTOR
    df_constant(sc_module_name name, const double c) : sc_module(name), const_value("const_value"),cst(c)
    {
        //REGISTRATING THREAD                                                        
        SC_THREAD(df_constant_thread);
    }

    //PROCESS
    void df_constant_thread();

};
#endif