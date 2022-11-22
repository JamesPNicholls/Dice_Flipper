// Filename:            Servo.c
//
// Description:	        This program controls multiple Buck converters with independent frequencies
//                      that then control the individual servo motors
//                      Note that all four ePWM modules are configured as masters and no synchronization is used
//
// Version:             1.0
//
// Target:              TMS320F28027
//
// Author:              Laurel Kinahan
//
// Date:                21/Nov/2022
//
//============================================================================
//============================================================================

#include "Peripheral_Headers/F2802x_Device.h"

void servo_init(int servos) {
  EALLOW; // Edit protected reg's
  
  SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;  // Enable TBCLK
//--------------------------------------------------------------------------------------
// Initialization 
//--------------------------------------------------------------------------------------
// ePWM1A config for 10kHz output
  EPwm1Regs.TBPRD = 6000;         // freq = 60M/6000 = 10kHz
  EPwm1Regs.CMPA.half.CMPA = 0;   // 0% duty cycle initially
  EPwm1Regs.CMPB = 0;             // 0% duty cycle initially
  EPwm1Regs.TBPHS.half.TBPHS = 0; // Set phase register to zero
  EPwm1Regs.TBCTR = 0;            // Clear TB Counter
  EPwm1Regs.TBCTL.bit.CTRMODE = 00; // Count_up Asymmetric mode
  EPwm1Regs.TBCTL.bit.PHSEN = 0;  // Phase loading disabled
  EPwm1Regs.TBCTL.bit.PRDLD = 0;
  EPwm1Regs.TBCTL.bit.SYNCOSEL = 3;
  EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;  // TBCLK=SYSCLK
  EPwm1Regs.TBCTL.bit.CLKDIV = 0;
  EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0; // load on CTR=Zero
  EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0; // load on CTR=Zero
  EPwm1Regs.AQCTLA.bit.ZRO = 2;     // 2 = SET
  EPwm1Regs.AQCTLA.bit.CAU = 1;     // 1 = CLEAR
  EPwm1Regs.AQCTLB.bit.ZRO = 2;     // 2 = SET
  EPwm1Regs.AQCTLB.bit.CAU = 1;     // 1 = CLEAR
  
  GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1; // 1=EPWM1A
  GpioCtrlRegs.GPAPUD.bit.GPIO0 =1;   // Diable pull-up on GPIO0
  
//
// ePWM2A config for 10kHz output
  EPwm2Regs.TBPRD = 6000;         // freq = 60M/6000 = 10kHz
  EPwm2Regs.CMPA.half.CMPA = 0;   // 0% duty cycle initially
  EPwm2Regs.CMPB = 0;             // 0% duty cycle initially
  EPwm2Regs.TBPHS.half.TBPHS = 0; // Set phase register to zero
  EPwm2Regs.TBCTR = 0;            // Clear TB Counter
  EPwm2Regs.TBCTL.bit.CTRMODE = 00; // Count_up Asymmetric mode
  EPwm2Regs.TBCTL.bit.PHSEN = 0;  // Phase loading disabled
  EPwm2Regs.TBCTL.bit.PRDLD = 0;
  EPwm2Regs.TBCTL.bit.SYNCOSEL = 3;
  EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;  // TBCLK=SYSCLK
  EPwm2Regs.TBCTL.bit.CLKDIV = 0;
  EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0; // load on CTR=Zero
  EPwm2Regs.CMPCTL.bit.SHDWBMODE = 0; // load on CTR=Zero
  EPwm2Regs.AQCTLA.bit.ZRO = 2;     // 2 = SET
  EPwm2Regs.AQCTLA.bit.CAU = 1;     // 1 = CLEAR
  EPwm2Regs.AQCTLB.bit.ZRO = 2;     // 2 = SET
  EPwm2Regs.AQCTLB.bit.CAU = 1;     // 1 = CLEAR
  
  GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1; // 1=EPWM2A
  GpioCtrlRegs.GPAPUD.bit.GPIO2 =1;   // Diable pull-up on GPIO2
  
//
// ePWM3A config for 10kHz output
  EPwm3Regs.TBPRD = 6000;         // freq = 60M/6000 = 10kHz
  EPwm3Regs.CMPA.half.CMPA = 0;   // 0% duty cycle initially
  EPwm3Regs.CMPB = 0;             // 0% duty cycle initially
  EPwm3Regs.TBPHS.half.TBPHS = 0; // Set phase register to zero
  EPwm3Regs.TBCTR = 0;            // Clear TB Counter
  EPwm3Regs.TBCTL.bit.CTRMODE = 00; // Count_up Asymmetric mode
  EPwm3Regs.TBCTL.bit.PHSEN = 0;  // Phase loading disabled
  EPwm3Regs.TBCTL.bit.PRDLD = 0;
  EPwm3Regs.TBCTL.bit.SYNCOSEL = 3;
  EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0;  // TBCLK=SYSCLK
  EPwm3Regs.TBCTL.bit.CLKDIV = 0;
  EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0; // load on CTR=Zero
  EPwm3Regs.CMPCTL.bit.SHDWBMODE = 0; // load on CTR=Zero
  EPwm3Regs.AQCTLA.bit.ZRO = 2;     // 2 = SET
  EPwm3Regs.AQCTLA.bit.CAU = 1;     // 1 = CLEAR
  EPwm3Regs.AQCTLB.bit.ZRO = 2;     // 2 = SET
  EPwm3Regs.AQCTLB.bit.CAU = 1;     // 1 = CLEAR
  
  GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1; // 1=EPWM3A
  GpioCtrlRegs.GPAPUD.bit.GPIO4 =1;   // Diable pull-up on GPIO4
  
//
// ePWM4A config for 10kHz output
  EPwm4Regs.TBPRD = 6000;         // freq = 60M/6000 = 10kHz
  EPwm4Regs.CMPA.half.CMPA = 0;   // 0% duty cycle initially
  EPwm4Regs.CMPB = 0;             // 0% duty cycle initially
  EPwm4Regs.TBPHS.half.TBPHS = 0; // Set phase register to zero
  EPwm4Regs.TBCTR = 0;            // Clear TB Counter
  EPwm4Regs.TBCTL.bit.CTRMODE = 00; // Count_up Asymmetric mode
  EPwm4Regs.TBCTL.bit.PHSEN = 0;  // Phase loading disabled
  EPwm4Regs.TBCTL.bit.PRDLD = 0;
  EPwm4Regs.TBCTL.bit.SYNCOSEL = 3;
  EPwm4Regs.TBCTL.bit.HSPCLKDIV = 0;  // TBCLK=SYSCLK
  EPwm4Regs.TBCTL.bit.CLKDIV = 0;
  EPwm4Regs.CMPCTL.bit.SHDWAMODE = 0; // load on CTR=Zero
  EPwm4Regs.CMPCTL.bit.SHDWBMODE = 0; // load on CTR=Zero
  EPwm4Regs.AQCTLA.bit.ZRO = 2;     // 2 = SET
  EPwm4Regs.AQCTLA.bit.CAU = 1;     // 1 = CLEAR
  EPwm4Regs.AQCTLB.bit.ZRO = 2;     // 2 = SET
  EPwm4Regs.AQCTLB.bit.CAU = 1;     // 1 = CLEAR
  
  GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1; // 1=EPWM4A
  GpioCtrlRegs.GPAPUD.bit.GPIO6 =1;   // Diable pull-up on GPIO6
  
//
//--------------------------------------------------------------------------------------
// Run Time
//--------------------------------------------------------------------------------------
EPwm1Regs.CMPA.half.CMPA = 4500;
EPwm2Regs.CMPA.half.CMPA = 4500;
EPwm3Regs.CMPA.half.CMPA = 4500;
EPwm4Regs.CMPA.half.CMPA = 4500;
//
