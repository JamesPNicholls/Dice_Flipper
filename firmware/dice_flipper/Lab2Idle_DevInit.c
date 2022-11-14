// Filename:            Lab2Idle_DeviceInit.c
//
// Description:         Initialization code
//
// Version:             1.0
//
// Target:              TMS320F28027
//
// Author:              David Romalo
//
// Date:                11Oct2022

#include <Headers/F2802x_device.h>
#define SCICHAR_LENGTH_8 0x7
#define SYSCLKOUT_DIV6   0b011

void DeviceInit(void)
{
//initialize GPIO:
EALLOW; //allow access to protected registers

    //configure D10 (blue LED)
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0; //set pin as gpio
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1; //set gpio as output
    GpioDataRegs.GPASET.bit.GPIO31 = 1; //initialize output value to "1"

 
 /***Configure SCI Pins*****/
    //Reset and re-eable the SCI state machines
    SciaRegs.SCICTL1.bit.SWRESET = 0; // Active low to reset
    SciaRegs.SCICTL1.bit.SWRESET = 1; 

    // Mux setting
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;

    // Pull-up Resistor Enable
    // PU needed to asset high values
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
    
    // Configure for Asynch Input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; 

    // SCI Word Properties 
    SciaRegs.SCICCR.bit.STOPBITS = 0; // 1 stop bit
    // SciaRegs.SCICCR.bit.PARITY = 0 // not using parity atm
    SciaRegs.SCICCR.bit.PARITYENA = 0; // disable parity 
    SciaRegs.SCICCR.bit.LOOPBKENA = 0; //diable loopback
    SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0; // idle-line mode
    SciaRegs.SCICCR.bit.SCICHAR = SCICHAR_LENGTH_8; // 8 bit word length

    // Control Register
    SciaRegs.SCICTL1.bit.RXERRINTENA = 0; //disable RX error interrupt
    SciaRegs.SCICTL1.bit.TXWAKE = 0; // Disable the tx transmitter method
    SciaRegs.SCICTL1.bit.TXENA = 0; // Disable Tx Pin, set high when data is ready to be sent
    SciaRegs.SCICTL1.bit.RXENA = 0; // Disable Rx Pin, set high when data is ready to be heard
    
    SciaRegs.SCICTL2.bit.RXBKINTENA = 0; // Rx interrupt flag

    // Baud Rate settings, currently configure for baud rate of 9600, see Onenote for explanation 
    SysCtrlRegs.LOSPCP.bit.LSPCLK = SYSCLKOUT_DIV6;
    SciaRegs.SCIHBAUD = 0x05;
    SciaRegs.SCILBAUD = 0x15;    
    
    //FIFO Settings
    SciaRegs.SCIFFCT

    // Stuff needed for later
    SciaRegs.SCICTL1.bit.SWRESET = 0; // Active low to reset
    SciaRegs.SCICTL1.bit.TXENA = 0; // Disable Tx Pin, set high when data is ready to be sent
    SciaRegs.SCICTL1.bit.RXENA = 0; // Disable Rx Pin, set high when data is ready to be sent
    
    SciaRegs.SCICTL2.bit.TXRDY = 0; // Tx full
    SciaRegs.SCICTL2.bit.TXEMPTY = 0; // Tx empty
    SciaRegs.SCICTL2.bit.TXINTENA = 0; // Tx Interrupt flag

    // Rx control reg
    // Whole thing filled with flags and interrupts to control the Rx
    SciaRegs.SCIRXST.bit.RXRDY = 0;   // Tx empty
    SciaRegs.SCIRXST.bit.RXERROR = 0; // Tx Interrupt flag
    SciaRegs.SCIRXST.bit.BRKDT = 0;   // Tx Interrupt flag

    // Buffers that the Rx data is store in
    //SciaRegs.SCIRXBUF - required Rxrdy flag to be cleared to run
    //SciaRegs.SCIRXEMU

    //Tx buffer
    //SciaRegs.SCITXBUF 
    
    // Controls the FIFO for Rx/Tx
    //SciaRegs.SCIFFTX 
    //SciaRegs.SCIFFRX
EDIS; //disallow access to protected registers
}
