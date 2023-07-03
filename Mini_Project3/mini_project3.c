/******************************************************************************
 *
 * File Name: mini_project3.c
 *
 * Description: Control a fan depending on the current temperature
 *
 * Author: Clara Isaac
 *
 * Date: 3/10/2022
 *
 *******************************************************************************/

#include "lcd.h"
#include "dc_motor.h"
#include "lm35_sensor.h"
#include "adc.h"

int main(void)
{
	uint8 temp;

	/* Create configuration structure for ADC driver */
	ADC_ConfigType ADC_Config = {INTERNAL_2_56_V, F_CPU_8};

	LCD_init(); /* initialize LCD driver */
	DcMotor_Init(); /* initialize DC motor driver */
	ADC_init(&ADC_Config); /* initialize ADC driver */

	/* Display this string "Fan is " only once on LCD at the first row 4th column */
	LCD_moveCursor(0,3);
	LCD_displayString("Fan is ");
	/* Display this string "Temp =      C " only once on LCD at the second row 4th column */
	LCD_moveCursor(1,3);
	LCD_displayString("Temp =     C");

	while(1)
	{
		temp = LM35_getTemperature();

		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,10);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

		if(temp >= 120)
		{
			DcMotor_Rotate(CLOCKWISE, 100); /* rotate the motor 100% of its speed */
			LCD_moveCursor(0,10);
			LCD_displayString("ON "); /* Display on the LCD ON (as fan is ON) */
		}
		else if(temp >= 90)
		{
			DcMotor_Rotate(CLOCKWISE, 75); /* rotate the motor 75% of its speed */
			LCD_moveCursor(0,10);
			LCD_displayString("ON "); /* Display on the LCD ON (as fan is ON) */
		}
		else if(temp >= 60)
		{
			DcMotor_Rotate(CLOCKWISE, 50); /* rotate the motor 50% of its speed */
			LCD_moveCursor(0,10);
			LCD_displayString("ON "); /* Display on the LCD ON (as fan is ON) */
		}
		else if(temp >= 30)
		{
			DcMotor_Rotate(CLOCKWISE, 25); /* rotate the motor 25% of its speed */
			LCD_moveCursor(0,10);
			LCD_displayString("ON "); /* Display on the LCD ON (as fan is ON) */
		}
		else
		{
			DcMotor_Rotate(STOP, 0); /* stop the motor */
			LCD_moveCursor(0,10);
			LCD_displayString("OFF"); /* Display on the LCD OFF (as fan is OFF) */
		}
	}

}
