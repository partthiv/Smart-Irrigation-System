#include <lpc214x.h> // LPC2148 Header file
#include <stdio.h>    // For sprintf function

#define MOISTURE_THRESHOLD 400

void adc_init(void);
unsigned int adc(int ch);
void lcd_init(void);
void lcd_display(const char *str);
void gpio_init(void);

int main(void) {
    unsigned int moisture_level;
    char moisture_str[16];

    // Initialize peripherals
    lcd_init();
    gpio_init();
    adc_init();

    while (1) {
        // Read moisture level from ADC
        moisture_level = adc(1); // Example: Channel 1

        // Display moisture level on LCD
        sprintf(moisture_str, "Moisture: %u", moisture_level);
        lcd_display(moisture_str);

        // Control motor based on moisture level
        if (moisture_level < MOISTURE_THRESHOLD) {
            IOSET0 = (1 << 10); // Set GPIO pin to turn on the motor
            lcd_display("LOW MOISTURE");
        } else {
            IOCLR0 = (1 << 10); // Clear GPIO pin to turn off the motor
            lcd_display("MOISTURE OK");
        }

        // Add a delay for stability (consider using a timer instead)
        for (volatile int i = 0; i < 50000; i++);
    }
}

void adc_init(void) {
    // Initialize ADC (example settings, verify with datasheet)
    PINSEL1 |= (1 << 14); // Select AD0.1 function
    AD0CR = 0x00200600; // Configure ADC (Example settings)
}

unsigned int adc(int ch) {
    unsigned int val;

    AD0CR = (AD0CR & ~(0xFF)) | (1 << ch); // Select channel
    AD0CR |= (1 << 24); // Start conversion
    while ((AD0GDR & (1 << 31)) == 0); // Wait for conversion to complete
    val = AD0GDR;
    val = (val >> 6) & 0x03FF; // Extract the 10-bit ADC value
    return val;
}

void gpio_init(void) {
    // Initialize GPIO (example for pin 10 as output)
    IO0DIR |= (1 << 10); // Set GPIO pin 10 as output
}
