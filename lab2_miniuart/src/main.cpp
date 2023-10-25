#include <systemc.h>
#include "benches.h"

#define TEST_CLK_UNIT 0
#define TEST_TX_UNIT 1
#define TEST_RX_UNIT 2
#define TEST_RTL_TESTBENCH 3
#define TEST_MINI_UART 4

// Change scenario:
//#define TEST TEST_CLK_UNIT
//#define TEST TEST_TX_UNIT
//#define TEST TEST_RX_UNIT
#define TEST TEST_MINI_UART

int sc_main(int argc, char* argv[]) {
	sc_set_time_resolution(1, SC_NS);

	#if TEST == TEST_CLK_UNIT
		test_clk_unit();
	#elif TEST == TEST_TX_UNIT
		test_tx_unit();
	#elif TEST == TEST_RX_UNIT
		test_rx_unit();
	#elif TEST == TEST_MINI_UART
		test_mini_uart();
	#endif

	return 0;
}
