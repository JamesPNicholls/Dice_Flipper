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

void SCIA_AutobaudLock(void);
void SendACK(void);
inline Uint16 SCIA_GetACK();
inline void SCIA_Flush(void);
void SCI_SendWord(Uint16 word);

//declare global variables:
volatile Bool isrFlag = FALSE; //flag used by idle function
volatile UInt tickCount = 0; //counter incremented by timer interrupt

Uint16 ReceivedChar;
char *msg;
Uint16 checksum;
Uint16 return_ack;

/* ======== main ======== */
Int main()
    {
    System_printf("Enter main()\n"); //use ROV->SysMin to view the characters in the circular buffer

    //initialization:
    DeviceInit(); //initialize processor
    //SCIA_AutobaudLock();
    //jump to RTOS (does not return):
    BIOS_start();
    return(0);
}

/* ======== myTickFxn ======== */
//Timer tick function that increments a counter and sets the isrFlag
//Entered times per second if PLL and Timer set up correctly
Void myTickFxn(UArg arg)
{
    tickCount++; //increment the tick counter
    if(tickCount % 1 == 0) {
        isrFlag = TRUE; //tell idle thread to do something 20 times per second
    }
}

Void mySwiFxn(Void)
{

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
       return_ack = SCIA_GetACK();
   }

   if(SciaRegs.SCIRXST.bit.RXRDY == 1)
   {
       GpioDataRegs.GPASET.bit.GPIO19 = 1;
   }
   else
   {
       GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;
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

inline Uint16 SCIA_GetACK()
{
    Uint16 wordData;

    while(SciaRegs.SCIRXST.bit.RXRDY != 1) { }

    wordData =  (Uint16)SciaRegs.SCIRXBUF.bit.RXDT;
    if(wordData != ACK)
    {
        return(1);
    }

    return(0);
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

//
// SCIA_AutobaudLock - Perform autobaud lock with the host.
//                     Note that if autobaud never occurs
//                     the program will hang in this routine as there
//                     is no timeout mechanism included.
//
void SCIA_AutobaudLock(void)
{
    Uint16 byteData;

    //
    // Must prime baud register with >= 1
    //
    SciaRegs.SCILBAUD  = 1;

    //
    // Prepare for autobaud detection
    // Set the CDC bit to enable autobaud detection
    // and clear the ABD bit
    //
    SciaRegs.SCIFFCT.bit.CDC = 1;
    SciaRegs.SCIFFCT.bit.ABDCLR = 1;

    //
    // Wait until we correctly read an
    // 'A' or 'a' and lock
    //
    while(SciaRegs.SCIFFCT.bit.ABD != 1) {}

    //
    // After autobaud lock, clear the ABD and CDC bits
    //
    SciaRegs.SCIFFCT.bit.ABDCLR = 1;
    SciaRegs.SCIFFCT.bit.CDC = 0;

    while(SciaRegs.SCIRXST.bit.RXRDY != 1) { }
    byteData = SciaRegs.SCIRXBUF.bit.RXDT;
    SciaRegs.SCITXBUF = byteData;

    return;
}
