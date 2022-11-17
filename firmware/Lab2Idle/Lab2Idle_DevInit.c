// Filename:            Lab2Idle_DeviceInit.c
//
// Description:	        Initialization code
//
// Version:             1.0
//
// Target:              TMS320F28027
//
// Author:              David Romalo
//
// Date:                11Oct2022

#include <Headers/F2802x_device.h>
#define SYSCLKOUT_DIV6   0b011

// SCI stuff from here
//https://github.com/AdrianoRuseler/LAUNCHXL-F28379D/blob/master/C2000Ware/examples/dual/F2837xD_sci_flash_kernels/cpu01/SCI_GetFunction.c

void DeviceInit(void)
{
//initialize GPIO:
EALLOW; //allow access to protected registers

    //configure D2 (right-most blue LED)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; //set pin as gpio
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; //set gpio as output
    GpioDataRegs.GPASET.bit.GPIO0 = 1; //initialize output value to "1"

    //configure D4 (second-from-right blue LED)
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0; //set pin as gpio
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1; //set gpio as output
    GpioDataRegs.GPASET.bit.GPIO1 = 1; //initialize output value to "1"

    //configure D3 (second-from-left blue LED)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0; //set pin as gpio
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1; //set gpio as output
    GpioDataRegs.GPASET.bit.GPIO2 = 1; //initialize output value to "1"

    //configure D5 (left-most blue LED)
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0; //set pin as gpio
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1; //set gpio as output
    GpioDataRegs.GPASET.bit.GPIO3 = 1; //initialize output value to "1"

/*************Pins for debugging********************/
//  GPIO-00 - PIN FUNCTION = --Spare--
//  GPIO-05 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;		// 0=GPIO,  1=EPWM3B,  2=Resv,  3=ECAP1
	GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;		// 1=OUTput,  0=INput
	GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO5 = 1;		// uncomment if --> Set High initially

    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0; //Enable the pull up to drive the output pin


/*************SCI-A Enable Stuff********************8*/
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

    // Reset the SCI regs
    SciaRegs.SCICTL1.bit.SWRESET = 0;
    SciaRegs.SCICTL1.bit.SWRESET = 1;

    // Mux settings for first
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;

    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;

    GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO29 = 1;

    SciaRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol

    SciaRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE

    SciaRegs.SCICTL2.all = 0x0000;


    // Baud Rate settings, currently configure for baud rate of 9600, see Onenote for explanation
    SysCtrlRegs.LOSPCP.bit.LSPCLK = SYSCLKOUT_DIV6;
    SciaRegs.SCIHBAUD = 0x00;
    SciaRegs.SCILBAUD = 0x82;

    SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset



    // Pull-up Resistor Enable
    // PU needed to assert high values
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;

    // Configure for Asynch Input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;


    // Initialize FIFOs for the Tx/Rx
    SciaRegs.SCIFFTX.all = 0x8000;


EDIS; //disallow access to protected registers
}
