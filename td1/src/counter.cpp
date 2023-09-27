#include <counter.h>

void counter::counter_thread(){
    while(true){
        wait(sc_time(period->read(), SC_NS), reset->posedge_event());
        if(reset->read() == true){
            Q->write(0);
        }

        else if (load->read()== true){
            Q->write(data_in->read());
        }

        else{
            
            if(up_down->read() == true){
                Q->write((Q->read()+1)%10);
            }

            else{
                if(Q->read()==0){
                    Q->write(9);
                }
                else{
                    Q->write(Q->read()-1);
                }
            }

            DISPLAY("Q = " << Q -> read());

        }
        //DISPLAY("running counter thread");
    }
}