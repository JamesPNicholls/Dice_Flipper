#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

 

 

 

//Movement Definitions

#define START 0

#define STOP 1

#define LEFT 2

#define RIGHT 3

 

typedef unsigned char       Uint8;

 

void scib_init(void);

void scib_fifo_init(void);

void scib_xmit(int a);

void scib_msg(char *msg);

void scib_sonar(Uint16 a);

void scib_image_start();

void scib_image_stop();

void scib_word(Uint16 pixel); //Send a pixel over UART

void scib_rx();

void CustomInitScibGpio();

void init_motor_control(void);

void motor_control(Uint16 direction);

 

 

void main(void)
{
    InitSysCtrl();


    InitGpio(); //Initialize all GPIO pins as input synchronized to SYSCLOCK


   CustomInitScibGpio();


    init_motor_control();


    scib_fifo_init();   // Initialize the SCI FIFO

    scib_init();  // Initalize SCI for echoback

 

   DELAY_US(2000);

 

 

    for(;;)
    {
        //After Each Line check for Rx

        if (ScibRegs.SCIFFRX.bit.RXFFST)
        {

        scib_rx();
        }
    }
}

//Initialize pins communicating with PIC to control Servo Motors

void init_motor_control(void)
{
    EALLOW;


    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0x0; //set GPIO4 pins to GPIO

    GpioCtrlRegs.GPADIR.bit.GPIO4 = 0x1; //set GPIO0 as output


    //Set as outputs (1 output, 0 inputs)

    GpioCtrlRegs.GPADIR.bit.GPIO4= 1;

    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;

    

    //Set to stop by default

    GpioDataRegs.GPADAT.bit.GPIO4= 1;

    GpioDataRegs.GPADAT.bit.GPIO3 = 1;

 

    EDIS;
}

void CustomInitScibGpio()

{

   EALLOW;


/* Enable internal pull-up for the selected pins */

// Pull-ups can be enabled or disabled disabled by the user.  

// This will enable the pullups for the specified pins.

// Comment out other unwanted lines.

 

//  GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;     // Enable pull-up for GPIO9  (SCITXDB)

//  GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up for GPIO14 (SCITXDB)

GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up for GPIO18 (SCITXDB)

//  GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;    // Enable pull-up for GPIO22 (SCITXDB)

 


//  GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up for GPIO11 (SCIRXDB)

//  GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up for GPIO15 (SCIRXDB)

  GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up for GPIO19 (SCIRXDB)

// GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;    // Enable pull-up for GPIO23 (SCIRXDB)

 

/* Set qualification for selected pins to asynch only */

// This will select asynch (no qualification) for the selected pins.

// Comment out other unwanted lines.

 

//  GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  // Asynch input GPIO11 (SCIRXDB)

//  GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (SCIRXDB)

GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDB)

//    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO23 (SCIRXDB)

 

/* Configure SCI-B pins using GPIO regs*/

// This specifies which of the possible GPIO pins will be SCI functional pins.

// Comment out other unwanted lines.

 

//  GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;    // Configure GPIO9 for SCITXDB operation

//  GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2;   // Configure GPIO14 for SCITXDB operation

GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;   // Configure GPIO18 for SCITXDB operation

//  GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;   // Configure GPIO22 for SCITXDB operation


//  GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;   // Configure GPIO11 for SCIRXDB operation

//  GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;   // Configure GPIO15 for SCIRXDB operation

    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   // Configure GPIO19 for SCIRXDB operation

//  GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;   // Configure GPIO23 for SCIRXDB operation


    EDIS;

}

//Setup SCI

// Test 1,scib  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity

void scib_init()

{

//Reduce the increase the LSCLK by 2 to offset slower SYSCLK

//SYSCLOCK is 75MHz, LSPCLK = 37.5MHz

EALLOW;

SysCtrlRegs.LOSPCP.all = 0x0001;


EDIS;


    // Note: Clocks were turned on to the scib peripheral

    // in the InitSysCtrl() function

 

  ScibRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback

                                   // No parity,8 char bits,

                                   // async mode, idle-line protocol

ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,

                                   // Disable RX ERR, SLEEP, TXWAKE

ScibRegs.SCICTL2.all =0x0003; //Note: Why is the RX/Bk interrupt being enabled here?

ScibRegs.SCICTL2.bit.TXINTENA =1;

ScibRegs.SCICTL2.bit.RXBKINTENA =1;

#if (CPU_FRQ_150MHZ)

     ScibRegs.SCIHBAUD    =0x0000;  // 115200 baud @LSPCLK = 37.5MHz.

     ScibRegs.SCILBAUD    =0x0028;

//      ScibRegs.SCIHBAUD    =0x0000;  // 2343750 baud @LSPCLK = 37.5MHz.

//      ScibRegs.SCILBAUD    =0x0000;

#endif

#if (CPU_FRQ_100MHZ)

      ScibRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.

      ScibRegs.SCILBAUD    =0x0044;

#endif

ScibRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset

}

 

// Initalize the SCI FIFO

void scib_fifo_init()

{

    ScibRegs.SCIFFTX.all=0xE040;

    ScibRegs.SCIFFRX.all=0x204f;

    ScibRegs.SCIFFCT.all=0x0;

 

}

//Recieve from SCIB

void scib_rx()

{

//Rx data and status variables

Uint16 ReceivedChar;

Uint16 rxffst;


   // Wait for data in Rx register

    rxffst = ScibRegs.SCIFFRX.bit.RXFFST;

while(rxffst == 0) 

{

rxffst = ScibRegs.SCIFFRX.bit.RXFFST;

} // wait for XRDY =1 for empty state

   // Get character

   ReceivedChar = ScibRegs.SCIRXBUF.all;

   //Process Recieved Character

   if(ReceivedChar == 'u')

   {

   motor_control(START);

   }

   else if(ReceivedChar == 's')

   {

   motor_control(STOP);

   }

   else if(ReceivedChar == 'l')

   {

   motor_control(LEFT);

   }

   else if(ReceivedChar == 'r')

   {

   motor_control(RIGHT);

   }

}

void motor_control(Uint16 direction)

{

switch(direction)

{

case STOP :

EALLOW;

GpioDataRegs.GPADAT.bit.GPIO4 = 1;

GpioDataRegs.GPADAT.bit.GPIO3 = 1;

  EDIS;

break;

case START :

EALLOW;

GpioDataRegs.GPADAT.bit.GPIO4 = 0;

GpioDataRegs.GPADAT.bit.GPIO3 = 0;

  EDIS;

break;

case LEFT :

EALLOW;

GpioDataRegs.GPADAT.bit.GPIO4 = 1;

GpioDataRegs.GPADAT.bit.GPIO3 = 0;

  EDIS;

break;

case RIGHT :

EALLOW;

GpioDataRegs.GPADAT.bit.GPIO4 = 0;

DELAY_US(1000);

GpioDataRegs.GPADAT.bit.GPIO3 = 1;

  EDIS;

break;

default :

EALLOW;

GpioDataRegs.GPADAT.bit.GPIO4 = 1;

  GpioDataRegs.GPADAT.bit.GPIO3 = 1;

  EDIS;

}

}