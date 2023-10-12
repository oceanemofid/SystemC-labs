#include "tx_unit.h"
#include "helper_fct.h"

void TxUnit::TxUnit_THREAD(){
    int count=0;
    while(true)
    {
        wait();
        if(reset->read()==true)
        {
            count=0;
            reg="00000000";
            buf="00000000";

            //Stop transimitting data
            txd->write(1);
            reg_empty->write(true);
            buf_empty->write(true);
        }
        else
        {
            //Load data in buf
            if(load->read()==true)
            {
                buf=data_in.read();
                buf_empty->write(false);
            }

            //Transimitting data
            if(enable->read()==true)
            {
                //first bit start
                if(count==0)
                {   
                    //if buf is not empty
                    if(buf_empty->read()==false)  
                    {   
                        //start transimit
                        txd->write(0);
                        reg=buf;
                        reg_empty->write(false);
                        buf_empty->write(true);
                        DISPLAY("start transmission : "<<reg);
                        ++count;
                    }  
                    //if empty
                    else 
                    {
                        //stop transimit
                        txd->write(1);
                        reg_empty->write(true);
                    }                 
                }
                else if(count>=1 && count<=8)
                {
                    //read data bit by bit
                    txd->write(reg.to_uint() & 1);
                    reg=reg>>1;
                    DISPLAY(txd->read());
                    count++;
                }

                else if(count==9)
                {
                    //stop
                    txd->write(1);
                    reg_empty->write(true);
                    count=0;
                    DISPLAY(txd->read());
                }
            else
            {
                DISPLAY("ERROR");
                return;
            }
           
            }
        }
    }
        
}
    