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

//includes:
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>

#include <Headers/F2802x_device.h>

//function prototypes:
extern void DeviceInit(void);

//declare global variables:
volatile Bool isrFlag = FALSE; //flag used by idle function
volatile UInt tickCount = 0; //counter incremented by timer interrupt

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
       GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
   }
}
