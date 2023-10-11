#include "tx_unit.h"

void TxUnit::TxUnit_THREAD(){
    int count=0;
    while(true)
    {
        wait();
        if(reset->read())
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
            if(load->read())
            {
                buf=data_in.read();
                buf_empty->write(false);
            }

            //Transimitting data
            if(enable->read())
            {
                //first bit start
                if(count==0)
                {   
                    //if buf is not empty
                    if(!buf_empty->read())  
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
                    //read the first bit
                    txd->write();
                }
           
            }
        }
    }
        
}
    