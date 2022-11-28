/*
 * paddle.c
 *
 *  Created on: Dec. 3, 2020
 *      Author: James
 */

#include "msp.h"
#include "lcd.h"
#include "adc.h"
#include "paddle.h"



#ifndef PADDLE_C_
#define PADDLE_C_



/************************************
 joy2lcd_draw:  Maps the x/y results from the ADC sample and draws a pixel at that  location

 Arguments:     x_result - adc sample from the Joystick X-axis
                y_result - adc sample from the Joystick Y-axis

 Return:        none
 ************************************/
void drawPaddle(int x_Position)
{
    //Draws current_colour to the current position of the joy stick
    uint8_t i;
    uint8_t paddle_end      = x_Position + (PAD_LENGTH/2);
    uint8_t paddle_start    = x_Position - (PAD_LENGTH/2);

    lcdSetPixel(paddle_start- 1, PAD_HEIGHT, WHITE);//clears the pixel in front of the paddle
    for( i =  paddle_start; i < paddle_end ; i++)
    {
        lcdSetPixel(i, PAD_HEIGHT, BLACK);
    }
    lcdSetPixel(paddle_end  + 1, PAD_HEIGHT, WHITE);//clears the pixel behind the paddle
}

void drawBall(struct object_Params *ptr_object_params)
{
    ptr_object_params->x_accel = ballAcceleration(ptr_object_params->x_accel , X, ptr_object_params );
    ptr_object_params->y_accel = ballAcceleration(ptr_object_params->y_accel , Y, ptr_object_params);

    //i tried drawing a bigger ball but it would slow the game down a lot
    lcdSetPixel( ptr_object_params->ball_x_pos, ptr_object_params->ball_y_pos, WHITE);
    lcdSetPixel( ptr_object_params->ball_x_pos += ptr_object_params->x_accel, ptr_object_params->ball_y_pos += ptr_object_params->y_accel, BLACK);


}

void paddleDirection(int adc_sample, struct object_Params *ptr_object_params)
{
    if(adcSample() > X_ACC_LEFT)
    {
        if(ptr_object_params->x_Paddle_Current_Position > (PAD_LENGTH/2))//checks to see if the paddle goes out of bounds
        {
            ptr_object_params->x_Paddle_Current_Position--;
        }
    }

    if(adcSample() < X_ACC_RIGHT)
    {
        if(ptr_object_params->x_Paddle_Current_Position < (LCD_MAX_X - (PAD_LENGTH/2)))//checks to see if the paddle goes out of bounds
        {
            ptr_object_params->x_Paddle_Current_Position++;
        }
    }
    drawPaddle(ptr_object_params->x_Paddle_Current_Position);
}

int ballAcceleration( int accel_in, char XY, struct object_Params *ptr_object_params)
{
    int accel_out = accel_in; // keeps the accel the same if no collision

    if(XY == X)//
    {
        //ball hitting left wall
        if(ptr_object_params->ball_x_pos >= LCD_MAX_X)
        {
            accel_out *= -1;
        }
        //hitting right wall
        if(ptr_object_params->ball_x_pos <= 0)
        {
            accel_out *= -1;
        }
        if(ptr_object_params->ball_y_pos == LCD_MAX_Y)
        {
            if(accel_out > 0)//lowers the x acceleration when the top wall is hit
            {
                accel_out = 1;
            }
            else
            {
                accel_out = -1;
            }
        }

        if(ptr_object_params->ball_y_pos == PAD_HEIGHT)//collision checks for the pad
        {
            if((ptr_object_params->ball_x_pos < (ptr_object_params->x_Paddle_Current_Position + (PAD_LENGTH/2))) && (ptr_object_params->ball_x_pos > ptr_object_params->x_Paddle_Current_Position)) //of the paddle
            {
                accel_out *= -1*(rand()%3+1);//gives the ball greater acceleration if hit on the edge, makes it a little random to make it harder
            }
            if((ptr_object_params->ball_x_pos > (ptr_object_params->x_Paddle_Current_Position - (PAD_LENGTH/2))) && (ptr_object_params->ball_x_pos < ptr_object_params->x_Paddle_Current_Position))// checks to see if the ball collides on the far right side of the paddle
            {
                accel_out *= -1*(rand()%3+1);
            }
        }
    }

    if(XY == Y)
    {
        if(ptr_object_params->ball_y_pos == PAD_HEIGHT)
        {
        //check if it hit the paddle
            if((ptr_object_params->ball_x_pos > (ptr_object_params->x_Paddle_Current_Position - (PAD_LENGTH/2))) && (ptr_object_params->ball_x_pos < (ptr_object_params->x_Paddle_Current_Position + (PAD_LENGTH/2))))
            {
                accel_out = 1;
            }
        }

        //ball hitting top wall
        if(ptr_object_params->ball_y_pos == LCD_MAX_Y)
        {
            accel_out = -1;
        }
        //hitting bottom wall
        if(ptr_object_params->ball_y_pos == 0)
        {
            //add a you died screen
            accel_out *= -1;
        }
    }
    return accel_out;
}

void detectBrick(struct object_Params *ptr_object_params)
{
    int ball_x      = ptr_object_params->ball_x_pos;
    int ball_y      = ptr_object_params->ball_y_pos;
    int brick_x     = ptr_object_params->brick_x_corner;
    int brick_y     = ptr_object_params->brick_y_corner;

    if((ball_x > brick_x) && (ball_x < (brick_x + BRICK_WIDTH)))//checks to see if the ball is within the horizontal space of the brick
    {
        if((ball_y > brick_y) && (ball_y < (brick_y + BRICK_HEIGHT)))//cheks to see if the ball is in the vertical space
        {
            drawBrick(ptr_object_params,ERASE);//kill the old brick
        }
    }


}

void drawBrick(struct object_Params *ptr_object_params, char erase)
{
    int index;
    int colour_array[] = {BLACK, RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA};//such colour, much wow

    //load the old start pos
    int cornerX = ptr_object_params->brick_x_corner;
    int cornerY = ptr_object_params->brick_y_corner;

    if(erase == ERASE)//erase the old brick
    {
        for(index = 0; index < BRICK_HEIGHT; index++)
        {
            lcdSetPixel(cornerX,               cornerY+index, WHITE);//draw two vert lines
            lcdSetPixel(cornerX + BRICK_WIDTH, cornerY+index, WHITE);
        }
        for(index = 0; index < BRICK_WIDTH; index++)
        {
            lcdSetPixel(cornerX + index, cornerY + BRICK_HEIGHT, WHITE);//draw two Horz lines
            lcdSetPixel(cornerX + index, cornerY,                WHITE);//
        }
    }

    //find a new start pos
    cornerX = rand()%BRICK_RAND_PARAM_X_MOD + BRICK_RAND_PARAM_X_OFFSET;
    cornerY = rand()%BRICK_RAND_PARAM_Y_MOD + BRICK_RAND_PARAM_Y_OFFSET;

    for(index = 0; index < BRICK_HEIGHT; index++)//draw a new brick with a new set start pos
    {
        lcdSetPixel(cornerX,               cornerY+index, colour_array[rand()%7]);//draw two vert lines
        lcdSetPixel(cornerX + BRICK_WIDTH, cornerY+index, colour_array[rand()%7]);
    }
    for(index = 0; index < BRICK_WIDTH; index++)
    {
        lcdSetPixel(cornerX + index, cornerY + BRICK_HEIGHT, colour_array[rand()%7]);//draw two Horz lines
        lcdSetPixel(cornerX + index, cornerY,                colour_array[rand()%7]);//
    }




    ptr_object_params->brick_x_corner = cornerX;
    ptr_object_params->brick_y_corner = cornerY;

}

void drawNumber(int score)//i tried to get a score counter working but I ran out of time
{
    int i;
    int j;
    int start_y = 120;
    int start_x = 120;
    for(i = numWid; i > 0 ; i--)
    {
        for(j = numHight; j > 0; j--)
        {
            if( (num0 >>((i*j-1))) & 0x1)
            {
                lcdSetPixel(start_x - i, start_y-j, BLACK);
            }
            else
                lcdSetPixel(start_x - i, start_y-j, WHITE);

        }
    }
}

#endif /* PADDLE_C_ */
