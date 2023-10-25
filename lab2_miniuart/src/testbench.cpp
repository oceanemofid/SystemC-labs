#include <systemc.h>
#include "testbench.h"
#include "helper_fct.h"

// Processes

void TestBench::sysclk_method() 
{
	sys_clk->write(clock.read()); 
}

void TestBench::main_thread() 
{
	cpt_car = 0;
	mess = (char *)"Hello !\n";

	resetTest();
	wait(CLK_PERIOD * 5);

	DISPLAY(": Write Boot "<<mess[cpt_car]);
	//cout << sc_time_stamp() << ": " << "Write Boot " << mess[cpt_car] << endl;
	write(0x00, mess[cpt_car]);
}

void TestBench::tx_isr_thread() 
{
	while (true) {
		wait(irq_tx->posedge_event());
		DISPLAY("TX Interrupt");
		//cout << "TX Interrupt at time : " << sc_time_stamp() << endl;
		if (cpt_car < sizeof(mess)) {
			cpt_car += 1;
			DISPLAY(": Write "<<mess[cpt_car]);
			//cout << sc_time_stamp() << ": " << "Write " << mess[cpt_car] << endl;
			write(0x00, mess[cpt_car]);
		}
	}
}

void TestBench::rx_isr_thread() 
{
	sc_uint<8> value;
	while (true) 
	{
		wait(irq_rx->posedge_event());
		DISPLAY("RX Interrupt");
		//cout << "RX Interrupt at time : " << sc_time_stamp() << endl;
		read(0x00, value);
		DISPLAY(": Read " << char(value));
		//cout << sc_time_stamp() << ": " << "Read " << char(value) << endl;
	}
}

// Helper Functions

void TestBench::resetTest(void) 
{
    bus_mutex.lock();
	ce->write(SC_LOGIC_0);
	wr->write(SC_LOGIC_0);
	rd->write(SC_LOGIC_0);
	addr->write(0);
	data_out->write("ZZZZZZZZ");
	reset->write(true);
	wait(CLK_PERIOD * 20);
	reset->write(false);

	ce->write(SC_LOGIC_Z);
	wr->write(SC_LOGIC_Z);
	rd->write(SC_LOGIC_Z);
	bus_mutex.unlock();
}

void TestBench::write(unsigned int addr_, sc_uint<8> data_) {
	
	//bus_mutex.lock();
	DISPLAY("------------------write---------------- ");
	//cout << sc_time_stamp() << " : ------------------write---------------- " << endl;
	DISPLAY("data_in " << data_);
    //cout << "data_in = "<< data_ << endl;

	
	ce->write(SC_LOGIC_1);
	wr->write(SC_LOGIC_0);
	rd->write(SC_LOGIC_0);
	addr->write(addr_);

	data_out->write("ZZZZZZZZ");


	wait(CLK_PERIOD);

	wr->write(SC_LOGIC_1);
	data_out->write(data_);
	wait(CLK_PERIOD * 3);

	ce->write(SC_LOGIC_0);
	wr->write(SC_LOGIC_0);
	data_out->write("ZZZZZZZZ");
	wait(CLK_PERIOD);

	ce->write(SC_LOGIC_Z);
	wr->write(SC_LOGIC_Z);
	rd->write(SC_LOGIC_Z);

	//bus_mutex.unlock();
}

void TestBench::read(unsigned int addr_, sc_uint<8>& data_) {

	//bus_mutex.lock();
	DISPLAY("------------------read--------------- ");
    //cout << sc_time_stamp() << " : ------------------read---------------- " << endl;
	DISPLAY("data_in " << data_);
    //cout << "data_in = "<< data_ << endl;
	ce -> write(SC_LOGIC_1);
	//wr -> write(SC_LOGIC_0);
	//rd -> write(SC_LOGIC_0);
	addr->write(addr_);	
	//wait(CLK_PERIOD);

	rd -> write(SC_LOGIC_1);
	wait(CLK_PERIOD * 3);

	data_ = data_in->read();
	ce -> write(SC_LOGIC_0);
	rd -> write(SC_LOGIC_0);
	wait(CLK_PERIOD);

	ce -> write(SC_LOGIC_Z);
	wr -> write(SC_LOGIC_Z);
	rd -> write(SC_LOGIC_Z);
	//bus_mutex.unlock();


}
