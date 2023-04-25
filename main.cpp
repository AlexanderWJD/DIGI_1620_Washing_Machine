/* 
ELEC1620 Digital Electronics and Microcontrollers UNIT 4 Project
 Washing Machine Interface

 Alex Desborough 201539640 ll21awjd@leeds.ac.uk
*/
 
#include "mbed.h"


void init_buttons(); // initialise buttons
void init_leds(); // initialise leds

void function_1(); //On/Off Function
float function_2(); //Read Force Sensor
void function_3();
void function_4();
void function_5();
void function_6();




// SETUP GPIO
DigitalIn On_Off(PC_10);                    // declare global variable 'On_Off';                    as Digital input pin [PC_10]; used to switch on/off themachine
DigitalOut led_1(PC_0);                    // declare global variable 'led_1';                    as Digital output pin [PH_1]; used to toggle an LED [Indicator]
DigitalOut led_2(PC_1);                    // declare global variable 'led_2';                    as Digital output pin [PH_1]; used to toggle an LED [Indicator]

AnalogIn Force_Sensor_Pin(PA_1);            // declare global variable 'Force_Sensor_Pin';          as Analogue Input Pin [PA_1]; used to measure Sensor [Force sensor]


DigitalOut motor_clockwise(PC_8);
DigitalOut motor_anticlockwise(PC_9);

DigitalIn button2(PC_11);
DigitalIn button3(PD_2);

// SETUP software variables
float Force_Sensor_Pin_Value = 0.0;         // declare global variable 'Force_Sensor_Pin_Value';    as floating point number; to store the value from the force sensor
bool On_Off_Status = true;

int motor_run = 0;

BufferedSerial pc(USBTX, USBRX, 115200);        //establish serial communications between PC and NUCLEO



int main(){
    
    while (1) {
        
        function_1(); // (standby mode)
        function_2(); // (main power on function)
        function_3(); // (turn off sequence)
        ThisThread::sleep_for(5s);
    }

    /*while(1){
        Force_Sensor_Pin_Value = Force_Sensor_Pin.read()*1000;
        
        printf("Force Sensor Value = %d \n", static_cast<int>(Force_Sensor_Pin_Value)); //for some reason this won't work with %f so it has to be converted
                                                                                        //to int then printed as %d
        thread_sleep_for(500);
        }*/


}

        

void function_1(){
    // Standby function constantly checking On_Off button for a press (normally low, pulled high on press) 
    
    // while true (no press) serial print 
    init_leds();
    led_1 = 1;
    
    while (On_Off_Status) {
        On_Off_Status = !On_Off.read();
        printf("function_1 Standby Mode\t On_Off_Status variable = %d \t On_Off pin read = %d \n", On_Off_Status, static_cast<bool>(On_Off.read()));
        thread_sleep_for(50);
    } 

    //action to be taken when On/Off button pressed
    led_1 = 0;
    led_2 = 1; 
    thread_sleep_for(500);
    On_Off_Status = !On_Off.read();
    
}

float function_2(){
    // while loop to detect force sensor reading
    
    
    while (On_Off_Status) {
        thread_sleep_for(50);
        On_Off_Status = !On_Off.read();

    // Read Force Sensor
        Force_Sensor_Pin_Value = Force_Sensor_Pin.read()*1000;
        printf("function_2 \t On_Off_Status variable = %d \t Force Sensor Value = %d \n", On_Off_Status, static_cast<int>(Force_Sensor_Pin_Value));
        }

    led_1 = 0;
    led_2 = 0;
    
    thread_sleep_for(500);
    On_Off_Status = !On_Off.read();
    return 0;
}

void function_3(){
    // Empty Funtion
    while (On_Off_Status) {
        On_Off_Status = !On_Off.read();

        printf("function_3 \n");
        thread_sleep_for(50);
    }
    led_1 = 1;
    led_2 = 1;
    thread_sleep_for(500);
    On_Off_Status = !On_Off.read();       
}

void function_4(){
    // Empty Funtion
    while (!button2.read() || !button3.read()) {
    printf("function_3 \t On_Off_Status variable = %d \t loopy \n", On_Off_Status);
    thread_sleep_for(50);
    }
    
    if (button2.read()) {
    motor_clockwise.write(1);
    motor_anticlockwise.write(0); 
    }

    else if (button3.read()) {
    motor_clockwise.write(0);
    motor_anticlockwise.write(1);
    }

    else {
    motor_clockwise.write(0);
    motor_anticlockwise.write(0);
    }
}

void function_5(){
    // Empty Funtion
}

void function_6(){
    // Empty Funtion
}

void init_buttons(){
    On_Off.mode(PullNone);  //turn off internal pull up / pull down resistors
    button2.mode(PullNone);
    button3.mode(PullNone);
}

void init_leds(){
    led_1 = 0;
    led_2 = 0;
}