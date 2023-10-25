#include "mini_uart.h"

void MiniUart::interfaceProcess_thread()
{
    while(1){
        
        //load et tx_data
        if((ce->read()=='0') || (ce->read()=='1' && wr->read()=='0'))
        {
            load.write(0);
            tx_data.write("00000000");
        }
        else if(ce->read() == '1' && wr->read() == '1')
        {
            if(addr->read()=="00")
            {
                load.write(1);
                tx_data = data_in->read();
            }
            else
            {
                load.write(0);
                tx_data.write("00000000");
            }
        }

        //read et data_out
        if((ce->read()=='0') || (ce->read()=='1' && rd->read()=='0'))
        {
            read.write(0);
            data_out->write("ZZZZZZZZ");
            //rx_data = "zzzzzzzz";
        }
        else if(ce->read() == '1' && rd->read() == '1')
        {
            switch(addr.read().to_uint())
            {
                case 0:
                    read.write(1);
                    data_out->write(rx_data);
                    //rx_data = rx_data;
                    break;
                case 1:
                    read.write(0);
                    data_out->write(ctrl_status_reg);
                    //rx_data = ctrl_status_reg;
                    break;
                case 2:
                case 3:
                    read.write(0);
                    data_out->write("ZZZZZZZZ");
                    //rx_data ="zzzzzzzz";
            }
        }
        wait(10,SC_NS);
    }
    
}

void MiniUart::combinational_thread(){
       while(1){
        if(buf_empty.read() && !reg_empty.read()){
                irq_tx->write(true);
            }else{
                irq_tx->write(false);
            }

            if(data_rdy.read()){
                irq_rx->write(true);
            }else{
                irq_rx->write(false);
            }

            ctrl_status_reg = buf_empty.read() << 2 | frame_err.read() << 1 | output_err.read();
            wait(10,SC_NS);
       }
}