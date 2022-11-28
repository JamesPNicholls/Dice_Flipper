// James Nicholls
// Lab 10
// Forever Alone Pong

#include "msp.h"
#include "lcd.h"
#include "adc.h"
#include "paddle.h"

//Analog Channels for Joy X & Y
#define JOY_Y_ACHAN 9
#define JOY_X_ACHAN 15

//Const used in msDelay fnc
#define CYCLE_2_MILISECONDS 3333// CYCLE_2_MILISECONDS = 1ms/3Mhz, where 3Mhertz is the base cycle for the device
#define DEBOUNCE_DELAY 10 // 10 ms

//S1 & S2 Port Mapping
#define S1_BP 0x02      // J4.33 > P5.1
#define S2_BP 0x20      // J4.32 > P3.5

//Joy X & Y Port mapping
#define JOY_X_PORT BIT0 // J1.02 > P6.0
#define JOY_Y_PORT BIT4 // J3.26 > P4.4

#define OFF 0x0         //a zero is useful

//Stuff for joy2lcd_draw()
#define ANA_2_LCD_SCALE_FACTOR 129// 2^14(adc resolution) / 127(pixels on the lcd screen)

int current_colour = BLACK;//current draw colour for the etch-e-sketch, default to BLACK
int colour_array[] = {BLACK, WHITE, RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA};
int* p_colour_array = &colour_array[0];


//int x_Current_Position = X_START_POS;


//it would be easier just to use a global int to just store the index value, but I'm too lazy to change it atm.

//Prototypes

void msDelay(unsigned int ms);
void prepSwitchwInterrupt(void);
void prepJoyPorts(void);


/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    //Prep the LCD to communicate via SPI
    lcdInit();

    //Prepare interrupts for S1 and S2
    prepSwitchwInterrupt();

    //Prepare inputs for Joy X/Y
    prepJoyPorts();
    adcInit(JOY_X_ACHAN);
    adcInit(JOY_Y_ACHAN);


    struct object_Params str_object_params, *ptr_object_params; //pretty sure i need malloc for this
    ptr_object_params = &str_object_params;// pointer to struct because multiple function modify the values

    //initialising parameters
    str_object_params.ball_x_pos =                  BALL_START_POS_X;
    str_object_params.ball_y_pos =                  BALL_START_POS_Y;
    str_object_params.x_Paddle_Current_Position =   X_START_POS_PAD;
    str_object_params.brick_x_corner =              BRICK_X_START;
    str_object_params.brick_y_corner =              BRICK_Y_START;
    str_object_params.x_accel =                     X_ACCEL_START;
    str_object_params.y_accel =                     Y_ACCEL_START;
    str_object_params.score   =                     START_SCORE;

    drawBrick(ptr_object_params, DRAW);
    while(1)//loop forever for the ADC polling and to catch the interrupts
    {
        paddleDirection(adcSample(), ptr_object_params);
        drawBall(ptr_object_params);
        detectBrick(ptr_object_params);
    }//0xBADC0C0A
}


/************************************
 PORT5_IRQHandler:  S1 Interrupt Handler
                    Clears LCD screen to WHITE

 Arguments:         none
 Return:            none
 ************************************/
void PORT5_IRQHandler(void)
{
    //Hold to debounce
    msDelay(DEBOUNCE_DELAY);
    //Clear the flag
    P5->IFG = OFF;
    if((P5->IN & S1_BP) == 0)//check to see if switch is still pressed
    {
        lcdClear(WHITE);
    }
}//void PORT5_IRQHandler(void)

/************************************
 PORT3_IRQHandler:  S2 interrupt handler
                    Cycles through available colours in colour_array[], assigns it to 'current_colour'

 Arguments:         none
 Return:            none
 ************************************/
void PORT3_IRQHandler(void)
{
    //Hold to debounce
    msDelay(DEBOUNCE_DELAY);
    //Clear the flag
    P3->IFG = OFF;
    if((P3->IN & S2_BP) == 0)//check to see if switch is still pressed
    {
        if(current_colour == MAGENTA)//checks if current_colour is the last element in colour_array[]
        {
            current_colour = BLACK;
            p_colour_array = &colour_array[0];//set the pointer back to the first element of the array
        }
        else
        {
            p_colour_array++;//iterate through the colour array
            current_colour = *p_colour_array;

        }
    }
}//void PORT3_IRQHandler(void)

/************************************
 prepSwitchwInterrupt:  Prepares ports S1 and S2 on the boosterpack

 Arguments:             none
 Return:                none
 ************************************/
void prepSwitchwInterrupt(void)
{
    //Prepare Switch Interrupts
    //Pre Clearing the interrupt flag
    P3->IFG = OFF;
    P5->IFG = OFF;

    //--S2
    //Configure P3 for input, with no Pull UP/down resistor needed
    P3->DIR &= ~S2_BP;
    P3->REN &=  S2_BP;
    P3->OUT |=  S2_BP;

    //P5 Interrupt Enable for falling edge
    P3->IE  |= S2_BP;
    P3->IES |= S2_BP;

    //--S1
    //Configure P5 for input, with no Pull UP/down resistor needed
    P5->DIR &= ~S1_BP;
    P5->REN &=  S1_BP;
    P5->OUT |=  S1_BP;

    //P6 Interrupt Enable for falling edge
    P5->IE  |= S1_BP;
    P5->IES |= S1_BP;

    NVIC_EnableIRQ(PORT3_IRQn); //Handler for S2
    NVIC_EnableIRQ(PORT5_IRQn); //Handler for S1
    __enable_interrupts();      //"I'm Global"

}//void prepSwitchwInterrupt();

/************************************
 prepJoyPorts:  Prepares ports for Joy Y and Joy X on the booster pack

 Arguments:     none
 Return:        none
 ************************************/
void prepJoyPorts(void)
{
    //set port 4.4 for Joy Y analog input
    P4->SEL0 |= JOY_Y_PORT;
    P4->SEL1 |= JOY_Y_PORT;

    //set port 6.0 for Joy X analog input
    P6->SEL0 |= JOY_X_PORT;
    P6->SEL1 |= JOY_X_PORT;
}//void prepJoyPorts(void)

/************************************
 msDelay:   wait for a specific amount of time(ms)

 Arguments: ms - time in milliseconds to wait

 Return:    none
 ************************************/
void msDelay(unsigned int ms)
{
    while (ms > 0)
    {
       __delay_cycles(CYCLE_2_MILISECONDS);
        ms--;
    }
    return;
}//void msDelay()
//0xBADC0C0A
