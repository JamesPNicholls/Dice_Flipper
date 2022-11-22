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

    // GPIO 
//  GPIO-00 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;		// 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;	// uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO0 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-01 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;		// 0=GPIO,  1=EPWM1B,  2=EMU0,  3=COMP1OUT
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;	// uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO1 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-02 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;		// 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;		// 1=OUTput,  0=INput
	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO2 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-03 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;		// 0=GPIO,  1=EPWM2B,  2=Resv,  3=COMP2OUT
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO3 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------


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


    /*******************PWM********************/
    // clkEnables
    SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
    SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
    SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 0;  // ePWM3
    SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;  // ePWM4
    
    // = = = = = = = = = = = = = = = = = = = = = = = =
    EPwm1Regs.TBPRD = 600; // Period = 601 TBCLK counts
    EPwm1Regs.CMPA.half.CMPA = 350; // Compare A = 350 TBCLK counts
    EPwm1Regs.CMPB = 200; // Compare B = 200 TBCLK counts
    EPwm1Regs.TBPHS.all = 0; // Set Phase register to zero
    EPwm1Regs.TBCTR = 0; // clear TB counter
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;
    EPwm1Regs.TBCTL.bit.PHSEN = 0; // Phase loading disabled
    EPwm1Regs.TBCTL.bit.PRDLD = 0;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 3;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0; // TBCLK = SYSCLK
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 0; // load on CTR = Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = 0; // load on CTR = Zero
    EPwm1Regs.AQCTLA.bit.ZRO = 2;
    EPwm1Regs.AQCTLA.bit.CAU = 1;
    EPwm1Regs.AQCTLB.bit.ZRO = 2;
    EPwm1Regs.AQCTLB.bit.CBU = 1;

    // Set the PWM perioid
    EPwm1Regs.CMPA.half.CMPA = 1000; // adjust duty for output EPWM1A
    EPwm1Regs.CMPB = 2000; // adjust duty for output EPWM1B

EDIS; //disallow access to protected registers
}
