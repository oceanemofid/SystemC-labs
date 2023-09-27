/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for SystemC course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file main.c
 * @author Fabrice Muller
 * @date 02 Nov. 2021
 * @brief Empty main program for SystemC
 *
 * @see https://github.com/fmuller-pns/systemc-vscode-project-template.git
 */

#include <systemc.h>
#include "counter.h"
#include "user.h"
#include "helper_fct.h"

int sc_main(int argc, char* argv[]) {
	sc_signal<double> period;
    sc_signal<bool> reset, up_down, load;
    sc_signal<int> data_in, Q;

	/* Elaboration step */
	DISPLAY("ELABORATION");
	counter counter_inst("counter inst");
	counter_inst.period(period);
	counter_inst.reset(reset);
	counter_inst.up_down(up_down);
	counter_inst.load(load);
	counter_inst.data_in(data_in);
	counter_inst.Q(Q);

	user user_inst("user inst");
	user_inst.period(period);
	user_inst.reset(reset);
	user_inst.up_down(up_down);
	user_inst.load(load);
	user_inst.data_in(data_in);

	sc_trace_file *tf = sc_create_vcd_trace_file("wave");
	sc_write_comment(tf,"TD1");
	sc_trace(tf, period, "period");
	sc_trace(tf, reset, "reset");	
	sc_trace(tf, up_down, "up_down");	
	sc_trace(tf, load, "load");	
	sc_trace(tf, data_in, "data_in");
	sc_trace(tf, Q, "Q");
	

	/* Simulation step */
	DISPLAY("START SIMULATION");
    sc_start(450,SC_NS);
	sc_close_vcd_trace_file(tf);
	/* End of Simulation */
	DISPLAY("END OF SIMULATION");
				
	return 0;
}


