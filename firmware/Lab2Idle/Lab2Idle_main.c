// Filename:            Lab2Idle_main.c
//
// Description:         This file has a main, timer, and idle function for SYS/BIOS application.
//
// Target:              TMS320F28027
//
// Author:              DR
//
// Date:                Oct. 11, 2022

//defines:
#define xdc__strict //suppress typedef warnings
#define ACK 0x2D
//includes:
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>

#include <Headers/F2802x_device.h>

//function prototypes:
extern void DeviceInit(void);
void scia_msg(char * msg);
void scia_xmit(int a);

void SendACK(void);
inline void SCIA_Flush(void);
void SCI_SendWord(Uint16 word);

//declare global variables:
volatile Bool isrFlag = FALSE; //flag used by idle function
volatile UInt tickCount = 0; //counter incremented by timer interrupt

Uint16 ReceivedChar;
char *msg;
Uint16 checksum;

/* ======== main ======== */
Int main()
{ 
    System_printf("Enter main()\n"); //use ROV->SysMin to view the characters in the circular buffer

    //initialization:
    DeviceInit(); //initialize processor

    //jump to RTOS (does not return):
    BIOS_start();
    return(0);
}

/* ======== myTickFxn ======== */
//Timer tick function that increments a counter and sets the isrFlag
//Entered 100 times per second if PLL and Timer set up correctly
Void myTickFxn(UArg arg)
{
    tickCount++; //increment the tick counter
    if(tickCount % 5 == 0) {
        isrFlag = TRUE; //tell idle thread to do something 20 times per second
    }
}

/* ======== myIdleFxn ======== */
//Idle function that is called repeatedly from RTOS
Void myIdleFxn(Void)
{
   if(isrFlag == TRUE) {
       isrFlag = FALSE;
       //toggle blue LED:
       GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;

       SendACK();

   }
}

void SendACK(void)
{
    while(!SciaRegs.SCICTL2.bit.TXRDY)
    {
    }

    SciaRegs.SCITXBUF = ACK;
    SCIA_Flush();
}
inline void SCIA_Flush(void)
{
    while(!SciaRegs.SCICTL2.bit.TXEMPTY)
    {
    }
}

void SCI_SendWord(Uint16 word)
{
    SciaRegs.SCITXBUF = (word & 0xFF); //LSB
    checksum += word & 0xFF;
    SCIA_Flush();


    SciaRegs.SCITXBUF = (word>>8) & 0xFF; //MSB
    checksum += word>>8 & 0xFF;
    SCIA_Flush();

}
