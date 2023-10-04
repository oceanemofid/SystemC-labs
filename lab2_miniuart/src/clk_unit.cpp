#include "clk_unit.h"

void ClkUnit::ClkUnit_THREAD()
{
    wait();
    if(reset.read())
    {
        count_tx=0;
        count_rx=0;
    }
    else
    {
        if(count_tx>=(40000000/9600))
        {
            en_tx.write(true);
            count_tx=0;
        }
        else
        {
            en_tx.write(false);
            count_tx++;
        }

        if(count_rx>=(40000000/153600))
        {
            en_rx.write(true);
            count_rx=0;
        }
        else
        {
            en_rx.write(false);
            count_rx++;
        }

    }
}