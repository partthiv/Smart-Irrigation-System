#define bit(x) (1 << x)

void lcd_init(void);
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay(void);

void lcd_init()
{
    cmd(0x38); // Initialize LCD in 8-bit mode, 2-line display, 5x7
    cmd(0x0E); // Display on, cursor blinking
    cmd(0x01); // Clear display
    cmd(0x06); // Entry mode, increment cursor
    cmd(0x0C); // Display on, cursor off
    cmd(0x80); // Set cursor position to first line, first column
}

void cmd(unsigned char a)
{
    IO1CLR = 0xFF070000; // Clear data lines and control lines
    IO1SET = (a << 24); // Send command to data lines
    IO1CLR = bit(16); // RS (command register)
    IO1CLR = bit(17); // RW (write mode)
    IO1SET = bit(18); // EN (enable high)
    lcd_delay(); // Short delay
    IO1CLR = bit(18); // EN (enable low)
}

void dat(unsigned char b)
{
    IO1CLR = 0xFF070000; // Clear data lines and control lines
    IO1SET = (b << 24); // Send data to data lines
    IO1SET = bit(16); // RS (data register)
    IO1CLR = bit(17); // RW (write mode)
    IO1SET = bit(18); // EN (enable high)
    lcd_delay(); // Short delay
    IO1CLR = bit(18); // EN (enable low)
}

void show(unsigned char *s)
{
    while (*s) { 
        dat(*s++); // Send each character of the string to the LCD
    }
}

void lcd_delay()
{
    unsigned int i;
    for (i = 0; i < 3000; i++); // Simple delay loop
}
