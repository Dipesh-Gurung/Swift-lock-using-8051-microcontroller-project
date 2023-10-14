#include <reg52.h>
#include <String.h>

sbit keypad_row1 = P2^0;
sbit keypad_row2 = P2^1;
sbit keypad_row3 = P2^2;
sbit keypad_row4 = P2^3;
sbit keypad_col1 = P3^0;
sbit keypad_col2 = P3^1;
sbit keypad_col3 = P3^2;
sbit led = P3^4;



sbit RS = P3^5;
sbit RW = P3^6;
sbit EN = P3^7;


void lcd_display(unsigned char *call);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
unsigned char correct_password[] = {"1234"};
unsigned char entered_password[5];
char keypad_init();
void check_password();
void delay(unsigned int);

void main()
{
    lcd_command(0x0F); 
    lcd_command(0x38);  
    lcd_command(0x01); 
		led=0;



    while (1)
    {
			
        unsigned int i = 0;
        lcd_command(0x80); 
        lcd_display("ENTER PASSWORD");
        delay(1000);
        lcd_command(0xc0);
        while (correct_password[i] != '\0')
        {
						entered_password[i] = keypad_init();
            delay(1000);
            i++;
        }
        check_password();
    }
}
void delay(unsigned int j)
{
    int a, b;
    for (a = 0; a < j; a++)
    {
        for (b = 0; b < 10; b++)
            ;
    }
}
void lcd_command(unsigned char A)
{
    P1 = A;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(1000);
    EN = 0;
}


void lcd_data(unsigned char i)
{
    P1 = i;
    RS = 1;
    RW = 0;
    EN = 1;
    delay(1000);
    EN = 0;
}
void lcd_display(unsigned char *call)
{
    int k;
    for (k = 0; call[k] != '\0'; k++)
    {
        lcd_data(call[k]);
    }
    delay(10000);
}
char keypad_init()
{
    int x = 0;
    char entered_key;
    
    while (x == 0)
    {
        // Assign values for the first row
        keypad_row1 = 0;
        keypad_row2 = 1;
        keypad_row3 = 1;
        keypad_row4 = 1;

        if (keypad_col1 == 0)
        {
            entered_key = '1';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        if (keypad_col2 == 0)
        {
            entered_key = '2';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        if (keypad_col3 == 0)
        {
            entered_key = '3';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        keypad_row1 = 1;
        keypad_row2 = 0;
        keypad_row3 = 1;
        keypad_row4 = 1;
        if (keypad_col1 == 0)
        {
            entered_key = '4';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        if (keypad_col2 == 0)
        {
            entered_key = '5';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        if (keypad_col3 == 0)
        {
            entered_key = '6';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        keypad_row1 = 1;
        keypad_row2 = 1;
        keypad_row3 = 0;
        keypad_row4 = 1;

        if (keypad_col1 == 0)
        {
            entered_key = '7';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        if (keypad_col2 == 0)
        {
            entered_key = '8';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        if (keypad_col3 == 0)
        {
            entered_key = '9';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        keypad_row1 = 1;
        keypad_row2 = 1;
        keypad_row3 = 1;
        keypad_row4 = 0;

        if (keypad_col1 == 0)
        {
            entered_key = '*';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        if (keypad_col2 == 0)
        {
            entered_key = '0';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
        if (keypad_col3 == 0)
        {
            entered_key = '#';
            lcd_data(entered_key);
            delay(1000);
            x = 1;
        }
    }
    
    return entered_key;
}

void check_password() {
    if (strcmp(entered_password, correct_password) == 0) {
        delay(1000);
        lcd_command(0x01);
        lcd_command(0x81);
        lcd_display("CORRECT");
        delay(1000);

        led = 1;  
        delay(10000);
        led = 0;
        lcd_command(0xc1);
        lcd_display("ACCESS GRANTED");
        delay(10000);
        led = 0;
        lcd_command(0x01);
    } else {
        lcd_command(0x01);
        lcd_command(0x80);
        lcd_display("ACCESS DENIED");
        delay(1000);
        lcd_command(0x01);
    }
}
