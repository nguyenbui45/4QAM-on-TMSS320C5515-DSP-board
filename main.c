#include "AIC_func.h"
#include "sinetab.h"
#include "utilities.h"
#include "usbstk5515.h"
#include "usbstk5515_i2c.h"
#define THRESHOLD 200



void main( void )
{
// Declare variables:

    // variables use for looping purpose
    Int8 j = 0;
    Int16 i = 0;
    Int16 id = 0;
    Int8 sample;
    // variables receive input signal
    Int16 mes1, mes2;

    // variables use for storing sinals
    Int8 I, Q;
    Int16 modulated_signal;
    static Int16 message_bin[3200], *pmes = message_bin;
    static Int16 carrier_bin[1600], *pcar = carrier_bin;
    static Int16 modulated_sig_bin[1600], *pmod = modulated_sig_bin;
    Int8 logFlag = 0;
    // Initialize BSL
    USBSTK5515_init( );
    USBSTK5515_I2C_init();
    SYS_EXBUSSEL = 0x6100;

    // Configure AIC3204:
    AIC_init();
    // Configure OSD9616:

    for ( i = 0 ; i < 10 ; i++ )
    {
        id = 0;
        for ( j = 0 ; j < 12000 ; j++ )
        {
            for ( sample = 0 ; sample < samplesPerPeriod ; sample++ )
            {
                // Read Analog Audio

                while((Rcv & I2S0_IR) == 0); // Wait for interrupt pending flag
                mes1 = I2S0_W0_MSW_R; // 16 bit left  channel received 1st audio data.
                //USBSTK5515_waitusec(3000);

                while((Rcv & I2S0_IR) == 0); // Wait for interrupt pending flag
                mes2 = I2S0_W0_MSW_R; // 16 bit left channel received 2nd audio data.

                // Convert message to I,Q component:
                if ((mes1 <= -THRESHOLD) && (mes2 <= -THRESHOLD))
                {
                    I = -1;
                    Q = -1;
                }
                else if ((mes1 <= -THRESHOLD) && (mes2 > THRESHOLD))
                {
                    I = -1;
                    Q = 1;
                }
                else if ((mes1 > THRESHOLD) && (mes2 <= -THRESHOLD))
                {
                    I = 1;
                    Q = -1;
                }
                else if ((mes1 > THRESHOLD) && (mes2 > THRESHOLD))
                {
                    I = 1;
                    Q = 1;
                }
                else
                {
                    I = 0;
                    Q = 0;
                }
                // Modulate signal
                modulated_signal = I*cosinetable[sample] - Q*sinetable[sample]; // I*cos(2*pi*fc*t) - Q*sin(2*pi*fc*t)
                // Write the modulated signals to left channel:

                while((Xmit  & I2S0_IR) == 0);

               //  Wait for interrupt pending flag
                I2S0_W0_MSW_W = modulated_signal;
                // Write the modulated signal to 16 bit left channel.
                I2S0_W0_LSW_W = 0;
                I2S0_W1_MSW_W = modulated_signal;
                I2S0_W1_LSW_W = 0;



                // Log the data:
                if ((sample ==0) && (j == 8000) && (i ==9) )  //j=8 i=9
                {
                    logFlag = 1;
                }


                if (logFlag == 1)
                {

                    message_bin[2*id] = mes1;
                    message_bin[2*id+1] = mes2;
                    carrier_bin[id] = sinetable[sample];
                    modulated_sig_bin[id] = modulated_signal;
                    id = id + 1;

                    if (id == 1600) //1600
                    {
                        logFlag = 0;
                        ExportFile("C:\\Users\\COMPUTER\\workspace_v8\\QU_AM\\modulated.bin",1600,(Int16*) pmod );
                        ExportFile("C:\\Users\\COMPUTER\\workspace_v8\\QU_AM\\message.bin", 3200,(Int16*) pmes );
                        ExportFile("C:\\Users\\COMPUTER\\workspace_v8\\QU_AM\\carrier.bin", 1600,(Int16*) pcar );
                    }
                }
            }
        }
    }



    /* Disable I2S */
    I2S0_CR = 0x00;

}

