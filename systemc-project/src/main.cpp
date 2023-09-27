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

int sc_main(int argc, char* argv[]) {

	/* Elaboration step */
	DISPLAY("ELABORATION");



	/* Simulation step */
	DISPLAY("START SIMULATION");

	sc_start();

	/* End of Simulation */
	DISPLAY("END OF SIMULATION");
				
	return 0;
}


