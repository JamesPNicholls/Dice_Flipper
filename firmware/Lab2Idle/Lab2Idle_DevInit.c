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
   // TURN ON ePWM1,3,4
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1    // LK
  // SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 0;
   SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;  // ePWM3    // LK
   //SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;  // ePWM4    // LK
   //------------------------------------------------

//  GPIO-00 - PIN FUNCTION = --Spare--
   //   ePWM1A  J1PIN 1
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;		// 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv      // LK
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;		// 1=OUTput,  0=INput                       // LK
//	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;	// uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO0 = 1;		// uncomment if --> Set High initially      // LK
//--------------------------------------------------------------------------------------
//  GPIO-01 - PIN FUNCTION = --Spare--
	//   ePWM1B  J1PIN 2
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;		// 0=GPIO,  1=EPWM1B,  2=EMU0,  3=COMP1OUT  // LK
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;		// 1=OUTput,  0=INput 			    // LK
//	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;	// uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO1 = 1;		// uncomment if --> Set High initially      // LK
////--------------------------------------------------------------------------------------
////  GPIO-02 - PIN FUNCTION = --Spare--
//	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;		// 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
//	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;		// 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;	// uncomment if --> Set Low initially
////	GpioDataRegs.GPASET.bit.GPIO2 = 1;		// uncomment if --> Set High initially
////--------------------------------------------------------------------------------------
////  GPIO-03 - PIN FUNCTION = --Spare--
//	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;		// 0=GPIO,  1=EPWM2B,  2=Resv,  3=COMP2OUT
//	GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;		// 1=OUTput,  0=INput
////	GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;	// uncomment if --> Set Low initially
////	GpioDataRegs.GPASET.bit.GPIO3 = 1;		// uncomment if --> Set High initially
////--------------------------------------------------------------------------------------


//  GPIO-04 - PIN FUNCTION = --Spare--
	//   ePWM3A  J1PIN 5
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;		// 0=GPIO,  1=EPWM3A, 2=Resv, 	3=Resv      // LK
	GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;		// 1=OUTput,  0=INput                       // LK
//	GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;	// uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO4 = 1;		// uncomment if --> Set High initially      // LK
////--------------------------------------------------------------------------------------
//  GPIO-05 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;		// 0=GPIO,  1=EPWM3B,  2=Resv,  3=ECAP1
	GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;		// 1=OUTput,  0=INput 
	GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO5 = 1;		// uncomment if --> Set High initially
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;
//
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0; //Enable the pull up to drive the output pin
 	GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;		// 1=OUTput,  0=INput                       // LK
	GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO6 = 1;		// uncomment if --> Set High initially      // LK
//--------------------------------------------------------------------------------------

/*************PWM Enable Stuff************************/
  SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;  // Enable TBCLK
//--------------------------------------------------------------------------------------
// Initialization 
//--------------------------------------------------------------------------------------
// ePWM1A/1B config for 50Hz output
    EPwm1Regs.TBPRD = 38000;          // freq = (60M/7) / 85714 = 50Hz
    EPwm1Regs.CMPA.half.CMPA = 0;    // 0% duty cycle initially
    EPwm1Regs.CMPB = 0;              // 0% duty cycle initially
    EPwm1Regs.TBPHS.half.TBPHS = 0;  // Set Phase register to zero
    EPwm1Regs.TBCTR = 0;             // clear TB counter
    EPwm1Regs.TBCTL.bit.CTRMODE = 00;
    EPwm1Regs.TBCTL.bit.PHSEN = 0;  // Phase loading disabled
    EPwm1Regs.TBCTL.bit.PRDLD = 0;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 3;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0; // TBCLK = SYSCLK
    EPwm1Regs.TBCTL.bit.CLKDIV = 5; //div 14
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 1; // 1 = immediate? 0 = "shadow"
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = 1;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 0;  // load on CTR = Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = 0;  // load on CTR = Zero
    EPwm1Regs.AQCTLA.bit.ZRO = 2;        // 2 = SET
    EPwm1Regs.AQCTLA.bit.CAU = 1;        // 1 = CLEAR
    EPwm1Regs.AQCTLB.bit.ZRO = 2;        // 2 = SET
    EPwm1Regs.AQCTLB.bit.CBU = 1;        // 1 = CLEAR
  

//
// ePWM3A config for 50Hz output
    EPwm3Regs.TBPRD = 38000;          // freq = (60M/7) / 85714 = 50Hz
    EPwm3Regs.CMPA.half.CMPA = 0;    // 0% duty cycle initially
    EPwm3Regs.CMPB = 0;              // 0% duty cycle initially
    EPwm3Regs.TBPHS.half.TBPHS = 0;  // Set Phase register to zero
    EPwm3Regs.TBCTR = 0;             // clear TB counter
    EPwm3Regs.TBCTL.bit.CTRMODE = 00;
    EPwm3Regs.TBCTL.bit.PHSEN = 0;  // Phase loading disabled
    EPwm3Regs.TBCTL.bit.PRDLD = 0;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = 3;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0; // TBCLK = SYSCLK
    EPwm3Regs.TBCTL.bit.CLKDIV = 5; //div 14
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = 1; // 1 = immediate? 0 = "shadow"
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = 1;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = 0;  // load on CTR = Zero
    EPwm3Regs.CMPCTL.bit.LOADBMODE = 0;  // load on CTR = Zero
    EPwm3Regs.AQCTLA.bit.ZRO = 2;        // 2 = SET
    EPwm3Regs.AQCTLA.bit.CAU = 1;        // 1 = CLEAR
    EPwm3Regs.AQCTLB.bit.ZRO = 2;        // 2 = SET
    EPwm3Regs.AQCTLB.bit.CBU = 1;        // 1 = CLEAR
  

    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;  // Enable TBCLK  
//
// ePWM4A config for 50Hz output
    EPwm4Regs.TBPRD = 38000;          // freq = (60M/7) / 85714 = 50Hz
    EPwm4Regs.CMPA.half.CMPA = 0;    // 0% duty cycle initially
    EPwm4Regs.CMPB = 0;              // 0% duty cycle initially
    EPwm4Regs.TBPHS.half.TBPHS = 0;  // Set Phase register to zero
    EPwm4Regs.TBCTR = 0;             // clear TB counter
    EPwm4Regs.TBCTL.bit.CTRMODE = 00;
    EPwm4Regs.TBCTL.bit.PHSEN = 0;  // Phase loading disabled
    EPwm4Regs.TBCTL.bit.PRDLD = 0;
    EPwm4Regs.TBCTL.bit.SYNCOSEL = 3;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0; // TBCLK = SYSCLK
    EPwm4Regs.TBCTL.bit.CLKDIV = 5; //div 14
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = 1; // 1 = immediate? 0 = "shadow"
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = 1;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = 0;  // load on CTR = Zero
    EPwm4Regs.CMPCTL.bit.LOADBMODE = 0;  // load on CTR = Zero
    EPwm4Regs.AQCTLA.bit.ZRO = 2;        // 2 = SET
    EPwm4Regs.AQCTLA.bit.CAU = 1;        // 1 = CLEAR
    EPwm4Regs.AQCTLB.bit.ZRO = 2;        // 2 = SET
    EPwm4Regs.AQCTLB.bit.CBU = 1;        // 1 = CLEAR
  
//
//--------------------------------------------------------------------------------------
// Run Time
//--------------------------------------------------------------------------------------
  //Set initial angles
  EPwm1Regs.CMPA.half.CMPA = 2800;
  EPwm3Regs.CMPA.half.CMPA = 2800;
//
/*************PWM STUFF*******************************/

/*************SCI-A Enable Stuff**********************/
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

    // Pull-up Resistor Enable
    // PU needed to assert high values
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;

    // Configure for Asynch Input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;

    SciaRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol

    SciaRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE

    SciaRegs.SCICTL2.all = 0x0000;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1; //Enable unterrupt flag for the Hwi

    // Baud Rate settings, currently configure for baud rate of 9600, see Onenote for explanation
    SysCtrlRegs.LOSPCP.bit.LSPCLK = SYSCLKOUT_DIV6;

    SciaRegs.SCIHBAUD = 0x00;
    SciaRegs.SCILBAUD = 0x82;

    SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset

    // Initialize FIFOs for the Tx/Rx
    SciaRegs.SCIFFTX.all = 0x8000;







EDIS; //disallow access to protected registers
}
