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
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

//Swi handle defined in .cfg file:

//Interupt handles
extern const Swi_Handle Swi0; // Assign Motor Position
extern const Hwi_Handle hwi0; // Get UART input
extern const Task_Handle Tsk0; // Handler for the PID scaling
//Semaphore handle defined in .cfg file:
extern const Semaphore_Handle mySem;

#include <Headers/F2802x_device.h>

//function prototypes:
extern void DeviceInit(void);

//Sends 0x2d to the pi
void SendACK(void);
inline void SCIA_Flush(void);

Uint16 pid_x();
Uint16 pid_y();
void pixel_to_motor(Uint16 x, Uint16 y);

//declare global variables:
volatile Bool isrFlag = FALSE; //flag used by idle function
volatile UInt tickCount = 0; //counter incremented by timer interrupt



// Ball parameters
Uint16 x_ball_pos_old = 0;
Uint16 y_ball_pos_old = 0;

Uint16 x_ball_pos_new = 0;
Uint16 y_ball_pos_new = 0;

Uint16 x_ball_set = 50;
Uint16 y_ball_set = 50;
Uint16 x_serv_set = 2800;
Uint16 y_serv_set = 2800;

// Limits for PID Parameters
Uint16 x_max = 50;
Uint16 y_max = 50;
int16 x_min = -50;
int16 y_min = -50;

// PID consts
float32 kpX = 12.5;
float32 kiX = 0;
float32 kdX = 200;

float32 kpY = 12.5;
float32 kiY = 0;
float32 kdY = 200;


float32 outsum_x = 0;
float32 outsum_y = 0;

// Consts used to convert the angle to PWM
Uint16 pwm_mult = 4;
Uint16 pwm_offset_x = 2125;
Uint16 pwm_offset_y = 2375;

// Range for the system to not trigger PID
Uint16 dead_band_rad = 5;

//True to use the PID tuning
//False to use x/y_ball_pos_new
bool PID = true;
bool debug = true;
//https://github.com/br3ttb/Arduino-PID-Library/blob/master/PID_v1.cpp maybe steal this?

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


//Scale
Void myTskFxn(Void)
{

    while(true)
    {
        Semaphore_pend(mySem, BIOS_WAIT_FOREVER); //wait for semaphore to be posted
        GpioDataRegs.GPASET.bit.GPIO5 = 1;
    }


}

Void mySwiFxn(Void)
{

    Uint16 x, y, diff_x, diff_y;

    if(PID)
    {
        x = pid_x();
        y = pid_y();
        diff_x = abs(x_ball_pos_new - x_ball_set);
        diff_y = abs(y_ball_pos_new - y_ball_set);

        // Scaling P value
        kpX = diff_x;
        kpY = diff_y;

        if(diff_x < dead_band_rad)
        {
            x = 50;
        }

        if(diff_y < dead_band_rad)
        {
            y = 50;
        }

        pixel_to_motor(x, y);
    }
    else
    {
        pixel_to_motor(x_ball_pos_new, y_ball_pos_new);
    }

    Semaphore_post(mySem); // Let the tsk thread run to manage the PID constants
}

Void myHwi(Void)
{


    Swi_post(Swi0); // Post the Swi to assign the values to motors
    Uint16 rx_data = SciaRegs.SCIRXBUF.bit.RXDT;

    //Values received are from 0 to 100
    //0 to 100 uses 7 bits, with the 8th for X/!Y control
    if(rx_data & 0x80) // if MSB = 1 store x_pos
    {
        x_ball_pos_new = rx_data & 0x7f; // mask out the flag bit
    }
    else // if the MSB is 0 store y pos
    {
        y_ball_pos_new = rx_data;
    }
    SendACK(); //Send ack to request the next value
    GpioDataRegs.GPASET.bit.GPIO5 = 1;
    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack


}

Uint16 pid_x()
{
    // Store the current x_pos
    float32 input_x = x_ball_pos_new;
    float32 error_x = x_ball_set - input_x; //error comes later
    float32 dInput_x = (input_x - x_ball_pos_old); //Find the delta
    outsum_x += kiX*error_x;

    outsum_x -= kpX * dInput_x;
    if(outsum_x > x_max) outsum_x = x_max;
    if(outsum_x < x_min) outsum_x = x_min;


    float32 output_x = kpX*error_x;
    if(output_x > x_max) output_x = x_max;
    if(output_x < x_min) output_x = x_min;

    output_x += outsum_x - kdX*dInput_x;
    if(output_x > x_max) output_x = x_max;
    if(output_x < x_min) output_x = x_min;

    x_ball_pos_old = x_ball_pos_new;
    return (100-(50 + output_x));
}
Uint16 pid_y()
{
    // Store the current x_pos
    float32 input_y = y_ball_pos_new;
    float32 error_y = y_ball_set - input_y; //error comes later
    float32 dInput_y = (input_y - y_ball_pos_old); //Find the delta
    outsum_y += kiY*error_y;

    outsum_y -= kpY * dInput_y;
    if(outsum_y > y_max) outsum_y = y_max;
    if(outsum_y < y_min) outsum_y = y_min;


    float32 output_y = kpY*error_y;
    if(output_y > y_max) output_y = y_max;
    if(output_y < y_min) output_y = y_min;

    output_y += outsum_y - kdY*dInput_y;
    if(output_y > y_max) output_y = y_max;
    if(output_y < y_min) output_y = y_min;

    y_ball_pos_old = y_ball_pos_new;
    return (100-(50 + output_y));
}


void pixel_to_motor( Uint16 x_pos, Uint16 y_pos)
{
    //pixel/deg
    EPwm1Regs.CMPA.half.CMPA = (y_pos)*22/5 + pwm_offset_y;
    EPwm3Regs.CMPA.half.CMPA = (100-x_pos)*22/5 + pwm_offset_x;
}

/***************PID********************/

// Sends an 8bit Ack out to the Pi
void SendACK(void)
{
    while(!SciaRegs.SCICTL2.bit.TXRDY)
    {
    }

    SciaRegs.SCITXBUF = ACK;
    SCIA_Flush();
}

//Wait for the Tx buffer to clear
inline void SCIA_Flush(void)
{
    while(!SciaRegs.SCICTL2.bit.TXEMPTY)
    {
    }
}
