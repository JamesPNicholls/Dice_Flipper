/*
 * paddle.h
 *
 *  Created on: Dec. 3, 2020
 *      Author: James
 */

#ifndef PADDLE_H_
#define PADDLE_H_

#define PAD_HEIGHT 20 //paddle height is fixed on the y axis arbitrary
#define PAD_LENGTH 35 //length of the paddle, arbitrary, longer or shorter paddle speed or slowed the game

//used for the ADC sampling, voltages for left or right movement of the joystick
#define X_ACC_LEFT  12000
#define X_ACC_RIGHT  4000

//Starting Params for object_params
#define X_START_POS_PAD 63 // 128/2
#define BALL_START_POS_X 124
#define BALL_START_POS_Y 67
#define X_ACCEL_START 1
#define Y_ACCEL_START 1
#define BRICK_X_START 0
#define BRICK_Y_START 0
#define BRICK_WIDTH  30
#define BRICK_HEIGHT 10
#define START_SCORE   0

//these are experimental values to make the brick appear in the top half of the screen inbounds
#define BRICK_RAND_PARAM_X_MOD      85
#define BRICK_RAND_PARAM_X_OFFSET   5
#define BRICK_RAND_PARAM_Y_MOD      60
#define BRICK_RAND_PARAM_Y_OFFSET   50

//used for drawBrick
#define DRAW   0
#define ERASE  1

//used in draw score
#define num1 0b0010011000100010001
#define num2 0b01101001001001000111
#define num3 0b11100001111100011110
#define num4 0b10101010111100100010
#define num5 0b11111000011000011111
#define num6 0b11111000111110011111
#define num7 0b11110001001000100010
#define num8 0b01101001011010010110
#define num9 0b01101001111100011110
#define num0 0b01110100011000101110
#define numWid 4
#define numHight 5
//plan was to bitwise iteration to draw a 5x4 pixel grid, but ran out of time

//Used for ballAcceleration()
#define X 0
#define Y 1

#define ANA_2_LCD_SCALE_FACTOR 129// 2^14(adc resolution) / 127(pixels on the lcd screen)

struct object_Params{
    int x_accel;                    //ball x acceleration
    int y_accel;
    int x_Paddle_Current_Position;
    int ball_x_pos;
    int ball_y_pos;

    int brick_x_corner;
    int brick_y_corner;
    int score;
};
/************************************
 drawBrick:         draws the brick after each collision detection

 Arguments:         ptr_object_params - Pointer to the parameter struct
                    erase - decides on whethe to erase the brick first before redrawing
 Return:            none
 ************************************/
void drawBrick(struct object_Params *ptr_object_params, char erase);

/************************************
  detectBrick:      Determines if the ball collides with the brick
                    If yes it deletes the old brick, calls drawBrick() to delte the old one and make the new one

  Arguments:        ptr_object_params - Pointer to the parameter struct
  Return:           none
 *************************************/
void detectBrick(struct object_Params *ptr_object_params);

/************************************
  paddleDirection:  Takes the adc sample and moves the paddles center left or right based on the value.
                    Calls drawPaddle() to update the position

  Arguments:        adc_sample - takes the input from the x-axis on the joy stick
                    ptr_object_params - Pointer to the parameter struct
  Return:           none
 *************************************/
void paddleDirection(int adc_sample, struct object_Params *ptr_object_params);

/************************************
  drawBall: Draws a new ball on every frame, taking into account the balls current acceleration

  Arguments:ptr_object_params - Pointer to the parameter struct
  Return:
 *************************************/
void drawBall(struct object_Params *ptr_object_params);

/************************************
  drawPaddle:   draw the new paddle based on the center postion

  Arguments:    x_Position - current center of the paddle
  Return:       none
 *************************************/
void drawPaddle(int x_Position);//left = true, right = false

/************************************
  ballAcceleration: Checks for collisions with the walls or paddle and than modifies the acceleration based on wher the collision takes place.

  Arguments:        accel_in - current acceleration value
                    XY - modifying the X or Y acceleration
                    ptr_object_params - Pointer to the parameter struct
  Return:           new accleration value
 *************************************/
int ballAcceleration( int accel_in, char XY, struct object_Params *ptr_object_params);

/************************************
  drawScore:    increase the score when a brick collision is detected

  Arguments:    score - the input score

  Return:       none
 *************************************/
void drawScore(int score);

#endif /* PADDLE_H_ */
