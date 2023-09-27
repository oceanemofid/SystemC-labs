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
#include "helper_fct.h"
#include "df_constant.h"
#include "df_adder.h"
#include "df_fork.h"
#include "df_display.h"

int sc_main(int argc, char* argv[]){
	sc_fifo <double> const_value_fifo("const_value");
	sc_fifo <double> feedback_fifo("feedback");
	sc_fifo <double> added_value_fifo("added_value");
	sc_fifo <double> result_fifo("result");
	/* Elaboration step */
	DISPLAY("ELABORATION");

	//Module instances
	df_constant df_constant_inst("df_constant_inst",5.2);
	df_constant_inst.const_value(const_value_fifo);

	df_adder df_adder_inst("df_adder_inst");
	df_adder_inst.const_value(const_value_fifo);
	df_adder_inst.feedback(feedback_fifo);
	df_adder_inst.added_value(added_value_fifo);

	df_fork df_fork_inst("df_fork_inst");
	df_fork_inst.added_value(added_value_fifo);
	df_fork_inst.feedback(feedback_fifo);
	df_fork_inst.result(result_fifo);
	//when we change 20 to 21 it has 37circles 21 + 16 maximale de fifo par default est 16
	//when the lien stop it was full and cant write again

	df_display df_display_inst("df_display_inst",20);
	df_display_inst.result(result_fifo);
	/* Simulation step */

	DISPLAY("START SIMULATION");
	feedback_fifo.write(3.2);
	sc_start(300,SC_MS);
	/* End of Simulation */
	DISPLAY("END OF SIMULATION");
	return 0;
}

