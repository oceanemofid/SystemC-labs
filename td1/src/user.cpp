#include <user.h>

void user::user_thread(){
    DISPLAY("Set period = 10ns");
    period->write(10);

    DISPLAY("Reset, duration = 15ns");
    reset->write(true);
    wait(15, SC_NS);
    reset->write(false);

    DISPLAY("Countdown, duration = 100ns")
    up_down->write(false);
    wait(100, SC_NS);
    up_down->write(true);

    DISPLAY("Load value 3, duration = 100ns")
    load->write(true);
    data_in->write(3);
    wait(20, SC_NS);
    load->write(false);

    DISPLAY("Countdown, duration = 100ns")
    up_down->write(false);
    wait(100, SC_NS);
    up_down->write(true);

    DISPLAY("Countup, duration = 140ns")
    up_down->write(true);
    wait(140, SC_NS);
    up_down->write(false);

    DISPLAY("Change period = 30ns");
    period->write(30);

}