#include <lpc214x.h>
#include "LCD.h"
#include "ADC.h"

#define MOTOR_EN1 (1 << 10) // P0.10 for motor enable 1
#define MOTOR_EN2 (1 << 11) // P0.11 for motor enable 2
#define LED (1 << 12)       // P0.12 for LED

unsigned int val;
float moisture_percentage;
int int_part;
int frac_part;

int main()
{
    // Initialize LCD and ADC
    lcd_init(); // Initialize LCD
    ADC_Init(); // Initialize ADC

    // Set all pins of port 0 as output
    IODIR0 |= MOTOR_EN1 | MOTOR_EN2 | LED; 

    // Configure ADC (assuming AD0.6 is the desired ADC channel)
    PINSEL0 |= (1 << 12); // Select AD0.6 function for P0.6
    VPBDIV = 0x02; // Set the peripheral clock (pclk) to 1/2 of the CPU clock

    while (1)
    {
        // Read ADC value from channel 6
        val = ADC_Read(6); // Adjust channel as needed

        // Convert ADC value to moisture percentage (0-100%)
        moisture_percentage = (val / 1023.0f) * 100.0f;

        // Calculate integer and fractional parts
        int_part = (int)moisture_percentage;
        frac_part = (int)((moisture_percentage - int_part) * 10); // Using 10 for one decimal place

        // Display moisture percentage on LCD
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("Moisture: ");
        lcd_print_char((int_part / 10) + 48); // Display tens place of integer part
        lcd_print_char((int_part % 10) + 48); // Display units place of integer part
        lcd_print_char('.'); // Display decimal point
        lcd_print_char(frac_part + 48); // Display fractional part
        lcd_print("%"); // Display percentage symbol

        // Check if moisture is below 40%
        if (moisture_percentage < 40.0f)
        {
            IOSET0 = MOTOR_EN1 | LED; // Turn on LED and motor enable 1
            IOCLR0 = MOTOR_EN2; // Ensure motor enable 2 is off
        }
        else
        {
            IOCLR0 = LED | MOTOR_EN1 | MOTOR_EN2; // Turn off LED and stop motor
        }

        // Delay for a while (adjust as needed)
        for(volatile int i = 0; i < 1000000; i++);
    }
}
