unsigned int adc(int no, int ch)
{
    unsigned int val;
    
    switch(no) {
        case 0:
            // Configure ADC0 with the selected channel
            AD0CR = 0x00200600 | (1 << ch); // Set ADC0 control register with channel selection
            AD0CR |= (1 << 24); // Start conversion
            while ((AD0GDR & (1 << 31)) == 0); // Wait for conversion to complete
            val = AD0GDR; // Read result from ADC0
            break;
        case 1:
            // Configure ADC1 with the selected channel
            AD1CR = 0x00200600 | (1 << ch); // Set ADC1 control register with channel selection
            AD1CR |= (1 << 24); // Start conversion
            while ((AD1GDR & (1 << 31)) == 0); // Wait for conversion to complete
            val = AD1GDR; // Read result from ADC1
            break;
        default:
            val = 0; // Handle invalid ADC number
            break;
    }
    
    // Extract the 10-bit ADC value from the result
    val = (val >> 6) & 0x03FF;
    return val;
}
