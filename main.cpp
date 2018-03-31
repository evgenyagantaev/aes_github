// This main file for 2v version of generator
#define DEBUG                   // includes debug activities in the compiler job




#include "main.h"

double abs(double value);

//--------------------------- macro definitions---------------------------------
#define BLUETOOTH_SILENCE_PERIOD 300 // seconds

//--------------------------end macro definitions-------------------------------
#define SETNAME
#define THEMPERATURE2

// global flags ---------------------------------------------------
int test_current_flag = 0;
int measure_and_save_flag = 0;
int get_voltage_flag = 0;
int start_plot_output_flag = 0;
int start_slowly_plot_output_flag = 0;
int short_plot_output_flag = 0;
int voltage_and_temperature_flag = 0;
int measure_voltage_temperature_flag = 0;
int voltage_temperature_current_flag = 0;
int sleep_flag = 0;

int full_line_received_flag = 0;


//----------------------------global constants----------------------------------
const double CURRENT_COEFFICIENT = 7.136;
char VERSION[] = "013-015-059";
char NAME[] = "accu_tester061";

const uint16_t crctable[256] =
{
    0x0000, 0xAC9A, 0xF5AE, 0x5934, 0x47C6, 0xEB5C, 0xB268, 0x1EF2,
    0x8F8C, 0x2316, 0x7A22, 0xD6B8, 0xC84A, 0x64D0, 0x3DE4, 0x917E,
    0xB382, 0x1F18, 0x462C, 0xEAB6, 0xF444, 0x58DE, 0x01EA, 0xAD70,
    0x3C0E, 0x9094, 0xC9A0, 0x653A, 0x7BC8, 0xD752, 0x8E66, 0x22FC,
    0xCB9E, 0x6704, 0x3E30, 0x92AA, 0x8C58, 0x20C2, 0x79F6, 0xD56C,
    0x4412, 0xE888, 0xB1BC, 0x1D26, 0x03D4, 0xAF4E, 0xF67A, 0x5AE0,
    0x781C, 0xD486, 0x8DB2, 0x2128, 0x3FDA, 0x9340, 0xCA74, 0x66EE,
    0xF790, 0x5B0A, 0x023E, 0xAEA4, 0xB056, 0x1CCC, 0x45F8, 0xE962,
    0x3BA6, 0x973C, 0xCE08, 0x6292, 0x7C60, 0xD0FA, 0x89CE, 0x2554,
    0xB42A, 0x18B0, 0x4184, 0xED1E, 0xF3EC, 0x5F76, 0x0642, 0xAAD8,
    0x8824, 0x24BE, 0x7D8A, 0xD110, 0xCFE2, 0x6378, 0x3A4C, 0x96D6,
    0x07A8, 0xAB32, 0xF206, 0x5E9C, 0x406E, 0xECF4, 0xB5C0, 0x195A,
    0xF038, 0x5CA2, 0x0596, 0xA90C, 0xB7FE, 0x1B64, 0x4250, 0xEECA,
    0x7FB4, 0xD32E, 0x8A1A, 0x2680, 0x3872, 0x94E8, 0xCDDC, 0x6146,
    0x43BA, 0xEF20, 0xB614, 0x1A8E, 0x047C, 0xA8E6, 0xF1D2, 0x5D48,
    0xCC36, 0x60AC, 0x3998, 0x9502, 0x8BF0, 0x276A, 0x7E5E, 0xD2C4,
    0x774C, 0xDBD6, 0x82E2, 0x2E78, 0x308A, 0x9C10, 0xC524, 0x69BE,
    0xF8C0, 0x545A, 0x0D6E, 0xA1F4, 0xBF06, 0x139C, 0x4AA8, 0xE632,
    0xC4CE, 0x6854, 0x3160, 0x9DFA, 0x8308, 0x2F92, 0x76A6, 0xDA3C,
    0x4B42, 0xE7D8, 0xBEEC, 0x1276, 0x0C84, 0xA01E, 0xF92A, 0x55B0,
    0xBCD2, 0x1048, 0x497C, 0xE5E6, 0xFB14, 0x578E, 0x0EBA, 0xA220,
    0x335E, 0x9FC4, 0xC6F0, 0x6A6A, 0x7498, 0xD802, 0x8136, 0x2DAC,
    0x0F50, 0xA3CA, 0xFAFE, 0x5664, 0x4896, 0xE40C, 0xBD38, 0x11A2,
    0x80DC, 0x2C46, 0x7572, 0xD9E8, 0xC71A, 0x6B80, 0x32B4, 0x9E2E,
    0x4CEA, 0xE070, 0xB944, 0x15DE, 0x0B2C, 0xA7B6, 0xFE82, 0x5218,
    0xC366, 0x6FFC, 0x36C8, 0x9A52, 0x84A0, 0x283A, 0x710E, 0xDD94,
    0xFF68, 0x53F2, 0x0AC6, 0xA65C, 0xB8AE, 0x1434, 0x4D00, 0xE19A,
    0x70E4, 0xDC7E, 0x854A, 0x29D0, 0x3722, 0x9BB8, 0xC28C, 0x6E16,
    0x8774, 0x2BEE, 0x72DA, 0xDE40, 0xC0B2, 0x6C28, 0x351C, 0x9986,
    0x08F8, 0xA462, 0xFD56, 0x51CC, 0x4F3E, 0xE3A4, 0xBA90, 0x160A,
    0x34F6, 0x986C, 0xC158, 0x6DC2, 0x7330, 0xDFAA, 0x869E, 0x2A04,
    0xBB7A, 0x17E0, 0x4ED4, 0xE24E, 0xFCBC, 0x5026, 0x0912, 0xA588
};


//--------------------------end global constants--------------------------------

//----------------------------global variables----------------------------------
// class-container of common global variables
#include "clsCommon.cpp"
// global object, which contains all variables needed for inter-module
// communications
clsCommon common;

long timer3_counter = 0;

#define BUFFER_LENGTH 20000
#define CURRENT_BUF_LENGTH 4000

int counter = 0;
uint32_t data_buffer[BUFFER_LENGTH];
uint16_t current_buffer[CURRENT_BUF_LENGTH];


int data_buffer_index = 0;
int current_buffer_index = 0;
int frequency_buffer_index = 0;

char current_input[4];
char frequency_input[7];

// buffer for input symbols
#define INPUTBUFFERLENGTH 128
char input_buffer[INPUTBUFFERLENGTH];
int input_buffer_index = 0;

int ack_waiting_flag = 0;

// text buffer for output via uart
//char sampleTxtBuffer[16];



// global flag; when set, signals that output through uart with dma in process
volatile int uartOutputInProcess;
uint16_t adc1Buffer[ADC1BUFFERLEN];
volatile int adc1BufferHead = 0;
// cyclic buffer for ecg samples which feed a 50 Hz filter
uint16_t filterBuffer[ADC1BUFFERLEN];
// global variable "uint16_t filterBufferHead" is an index which points to the 
// current position for writing a new sample in the buffer 
uint16_t filterBufferHead;

// cpu tick counters for profiling purposes
volatile portTickType tickCounter0, tickCounter1, tickCounter2, tickCounter3;
volatile portTickType interval0 = 0, interval1 = 0;
volatile portTickType profTick0, profTick1, profTick2, profTick3;
volatile portTickType profInterval0 = 0, profInterval1 = 0;

// cpu tick counters for timer interrupt control
volatile portTickType timerTickCounter0 = 0, timerTickCounter1 = 0;
volatile portTickType timerInterval = 0;

// cpu tick counters for timeouts
volatile portTickType timeoutInCounter, timeoutOutCounter;
volatile portTickType timeoutInterval = 0;
// timeout flag
int timeoutFlag;

// timer 3 update isr blocking flag
// set by timer 3 isr and clear by ad7792SpiReadDataTask
// if not clear, we get isr bypass
int timer3IsrBypass = 0;
// flag which signals that normal timer3 isr sequence was interrupted
int timer3SeqInterrupted = 1;

// extra sample
uint16_t extraSample0, extraSample1;
int extraSampleCounter = 0;

// vector of coefficients for polynomial approximation
//double a[4];
double a[2];
// vector of constatnt terms of a linear system
//double v[4];
double v[2];
// vector of samples which we want to approximate
//uint16_t y[4] = {20000, 20000, 20200, 20000};
uint16_t y[4];
// vector of points of approximation curve
double yy[4];

uint8_t adResponce;

// adc conversion result
volatile uint16_t Conv;

// adc fault flag
int adcFault = 0;
int adcAbnormal = 0;

// flag which signals that we have to suspend qrs detection procedure
// set when we just detected an r-pick
int qrsSuspend = 0;
// marker which marks a moment when we have found a new r-pick
int qrsSuspendMarker = 0;

//test mode flag
int testFlag=0; 

// flag which signals to timer2 interrupt procedure that measurements on
int measure_on = 0;
int measurement_counter = 0;

char message[128];
char voltage_message[21];
char temperature_message[21];
char temperature2_message[21];
char test_voltage_message[21];
char Il_message[21];
char Ih_message[21];
char test_Il_message[21];
char test_Ih_message[21];
char test_temperature_message[21];
char test_temperature2_message[21];

#define FREQ_LENGTH 11
double frequencies[] = {0.1, 0.2, 0.5, 1.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0, 200.0};
double f_setting = 10.0;
double working_frequency = 10.0; // frequency in Hertc

int samples_in_one_pulse = 1000;
double duration = 0.2;  // duration in seconds

long bluetooth_silence = 0;

//--------------------------end global variables--------------------------------

//--------------------------function prototypes--------------------------------

void measure_voltage_temperature();
void measure_highlow_current();
void readAds8320(void);
void readAds8320_2(void);
void readAd7691(void);
void uart1_receive_interrupt_service(char r);
void measure_and_save();

//--------------------------end function prototypes--------------------------------


//---------------------------classes includes-----------------------------------



#include "clsGPIO.cpp"
clsGPIO gpio;
#include "LEDclass.cpp"
clsLED led;
#include "clsThermometer.cpp"
clsThermometer thermometer;

#include "UARTclass.cpp"
clsUART uart;

#include "clsTimer2.cpp"
clsTimer2 timer2;


#include "clsTimer3.cpp"
clsTimer3 timer3;

#include "clsSpi1.cpp"
clsSpi1 spi1;
#include "clsSpi2.cpp"
clsSpi2 spi2;

#include "ADC1class.cpp"
clsADC1 adc1;



//#include "DAC1class.cpp"
//clsDAC1 dac1;

//#include "clsDacPower.cpp"
//clsDacPower dacPower;

#include "clsWatchdog.cpp"
clsWatchdog watchdog;

#include "clsCrcCalculator.cpp"
clsCrcCalculator crcCalculator;


//-------------------------interrupt services------------------------------------

void uart1_receive_interrupt_service()
{
    
    int i;
    int wrong_command = 0;
    
    if((strstr(input_buffer, "UCAST:") == input_buffer))
    {
        //cut prompt
        if(input_buffer_index >= 27)
        {
            // save PAN coordinator eid
            for(i=0; i<16; i++)
                uart.coord_eid[i] = input_buffer[i+6];
            // shift input buffer
            for(i=26; i<=input_buffer_index; i++)
                input_buffer[i-26] = input_buffer[i];
            
            // parse input string
            
            // 1. check GETU, GETUT, GETUTI
            if(strstr(input_buffer, "GETUTI") == input_buffer)
            {
                voltage_temperature_current_flag = 1;
            }
            else if(strstr(input_buffer, "GETUT") == input_buffer)
            {
                voltage_and_temperature_flag = 1;
            }
            else if(strstr(input_buffer, "GETU") == input_buffer)
            {
                get_voltage_flag = 1;
            }
            else if(strstr(input_buffer, "TEST") == input_buffer)
            {
                test_current_flag = 1;
            }
            else if(strstr(input_buffer, "SETFREQUENCY") == input_buffer)
            {
                char ch;
                if((sscanf(input_buffer, "SETFREQUENCY %lf%c", &(f_setting), &ch) == 2) && (ch == '\r'))
                {
                    // correct frequency settings
                    if(f_setting > 200)
                        f_setting = 200;
                    if(f_setting < 0.1)
                        f_setting = 0.1;
                    
                    // print echo
                    //uart.transmitMessage("frequency = ");
                    //uart.transmitMessage(input_buffer);
                    //uart.transmitMessage("\r\n");
                    sprintf(message, "frequency = %s", input_buffer);
                    uart.transmitMessage(message);
                    
                    // correct frequency (snap to frequency grid)
                    double min_difference = abs(f_setting - frequencies[0]);
                    int min_index = 0;
                    
                    for(int i = 1; i < FREQ_LENGTH; i++)
                    {
                        if(min_difference > abs(f_setting - frequencies[i]))
                        {
                            min_difference = abs(f_setting - frequencies[i]);
                            min_index = i;
                        }
                    }
                    
                    working_frequency = frequencies[min_index];
                    // adjust duration
                    if(min_index <= 3)
                        duration = 10;
                    else if(min_index >= 6)
                        duration = 1;
                    else
                        duration = 5;
                    
                    // calculate number of pulses
                    common.number_of_pulses = (int)(duration*working_frequency);
                    //samples_in_one_pulse = (int)( 1000 / working_frequency );
                }
                else // something wrong
                {
                    wrong_command = 1;
                }
            }
            else if(strstr(input_buffer, "SETCURRENT") == input_buffer)
            {
                char ch;
                if((sscanf(input_buffer, "SETCURRENT %d%c", &(common.i_setting), &ch) == 2) && (ch == '\r'))
                {
                    // correct current settings
                    if(common.i_setting > 255)
                        common.i_setting = 255;
                    if(common.i_setting < 1)
                        common.i_setting = 1;
                    
                    // print echo
                    //uart.transmitMessage("current = ");
                    //uart.transmitMessage(input_buffer);
                    //uart.transmitMessage("\r\n");
                    sprintf(message, "current = %s", input_buffer);
                    uart.transmitMessage(message);
                    
                    // transform gpios
                    uint8_t I_raw = (uint8_t)(common.i_setting);
                    uint8_t I_final = 0;
                    // 0 - 5, 1 - 4, 2 - 6, 3 - 7, 4 - 0, 5 - 1, 6 - 2, 7 - 3
                   
                    I_final = I_raw >> 4;    // 4 - 0, 5 - 1, 6 - 2, 7 - 3
                    I_final = I_final | ((I_raw & 0x01)<<5);      // 0 - 5
                    I_final = I_final | (((I_raw>>1) & 0x01)<<4); // 1 - 4
                    I_final = I_final | (((I_raw>>2) & 0x01)<<6); // 2 - 6
                    I_final = I_final | (((I_raw>>3) & 0x01)<<7); // 3 - 7
                    
                    common.resistors_gpios = (uint16_t)I_final;
                }
                else // something wrong
                {
                    wrong_command = 1;
                }
            }
            else if(strstr(input_buffer, "STARTTEST") == input_buffer)
            {
                measure_and_save_flag = 1;
                ////////////////////////////
                //working_frequency = 10.0;
                //common.i_setting = 32;
                //duration = 1;
                common.number_of_pulses = (int)(duration*working_frequency);
                //samples_in_one_pulse = (int)( 1000 / working_frequency );
            }
            else if(strstr(input_buffer, "GETTESTDATASLOW") == input_buffer)
            {
                start_slowly_plot_output_flag = 1;
            }
            else if(strstr(input_buffer, "GETTESTDATAFAST") == input_buffer)
            {
                start_plot_output_flag = 1;
            }
            else if(strstr(input_buffer, "GETVERSION") == input_buffer)
            {
                sprintf(message, "version = %s", VERSION);
                uart.transmitMessage(message);
            }
            else if(strstr(input_buffer, "SLEEP") == input_buffer)
            {
                sleep_flag = 1;
                uart.transmitMessage("SLEEPING");
            }
            else if(strstr(input_buffer, "WAKEUP") >= input_buffer)
            {
                uart.transmitMessage("AWAKENED");
                sleep_flag = 0;
                timer3.startTimer();
            }
            else // nothing of known
            {
                wrong_command = 1;
            }
            
            if(wrong_command)
            {
                //char wrong_command_mesage[INPUTBUFFERLENGTH + 32];
                //sprintf(wrong_command_mesage, "WRONG COMMAND %s\r\n", input_buffer);
                //uart.transmitMessage(wrong_command_mesage);
            }
        
        }
    
    }// end if((strstr(input_buffer, "UCAST:") == input_buffer))
    
    // initialize input string
    input_buffer_index = 0;
    // drop flag
    full_line_received_flag = 0;
    
}// end uart1_receive_interrupt_service()

void measure_current(int descriptor)
{
    uint16_t adc2Data;
    
    ADC_SoftwareStartConv(ADC2);
    while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));
    adc2Data = ADC_GetConversionValue(ADC2);
    
    if(descriptor != 0) // proizvodim izmerenie v konce impulsa
    {
        current_buffer[current_buffer_index] = (uint16_t)(adc2Data*CURRENT_COEFFICIENT);
        //current_buffer[current_buffer_index] = initial_current;
        /*
        if(initial_current <= adc2Data)
            current_buffer[current_buffer_index] = (uint16_t)((adc2Data - initial_current)*CURRENT_COEFFICIENT);
        else
            current_buffer[current_buffer_index] = 0;
        */
        current_buffer_index++;
    }
}

void test_current() // TEST
{
    // test: 3 sec
    // total impulses 1
    
    char test_current_message[64];
    
    // drop flag
    test_current_flag = 0;
    // stop low speed timer
    timer3.stopTimer();
    
    measure_voltage_temperature();
    strcpy(test_voltage_message, voltage_message);
    strcpy(test_temperature_message, temperature_message);
    strcpy(test_temperature2_message, temperature2_message);
    
    uart.transmitMessage("TEST CURRENT");
    //turn on current sensor (pa3 high)
    GPIOA->BSRRL=GPIO_Pin_3; 
    led.LED_Off();
    
    // turn current on
    gpio.high();
    
    // delay
    volatile long i = 0;
    for(i=0; i<50000000; i++);
    
    // measure current
    uint16_t adc2Data;
    ADC_SoftwareStartConv(ADC2);
    while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));
    adc2Data = ADC_GetConversionValue(ADC2);
    uint16_t current = (uint16_t)(adc2Data*CURRENT_COEFFICIENT);
    // turn current off
    gpio.low();
    
    // print current value
    current = current*5/5;
    sprintf(test_current_message, "I = %d", current);
    uart.transmitMessage(test_current_message);
    
    // turn off current sensor (pa3 low)
    GPIOA->BSRRH=GPIO_Pin_3;  
   
    // start low speed timer
    timer3.startTimer();
}

void measure_and_save() // STARTTEST
{
    // test: 10 sec 10 Hz 2000 KHz
    // total impulses 100
    // 200 measurements in every impulse
    
    int i;
    char message[64];
    
    data_buffer_index = 0;
    current_buffer_index = 0;
    // stop low speed timer
    timer3.stopTimer();
    
    measure_voltage_temperature();
    //measure_highlow_current();
    strcpy(test_voltage_message, voltage_message);
    strcpy(test_temperature_message, temperature_message);
    strcpy(test_temperature2_message, temperature2_message);
    //strcpy(test_Il_message, Il_message);
    //strcpy(test_Ih_message, Ih_message);
    
    uart.transmitMessage("START TEST");
    // set pa0
    GPIOA->BSRRL=GPIO_Pin_0; 
    led.LED_Off();
    //uart.transmitMessage(voltage_message);
    //uart.transmitMessage("\r\n");
    //uart.transmitMessage(temperature_message);
    //uart.transmitMessage("\r\n");
    sprintf(message, "current = %d", common.i_setting);
    uart.transmitMessage(message);
    sprintf(message, "frequency = %f", working_frequency);
    uart.transmitMessage(message);
    
    //turn on current sensor (pa3 high)
    GPIOA->BSRRL=GPIO_Pin_3; 
    // delay 0.5 sec
    for(volatile long i=0; i<4000000; i++);
    
    // start high speed timer
    timer2.startTimer();
    
    
    // loop on impulses
    for(i=0; i<common.number_of_pulses; i++)
    {
        // measure current
        measure_current(0);
        //high semyperiod =====================
       
        // start impulse
        gpio.high();
        // start measurements
        measurement_counter = 0;
        measure_on = 1;
        // wait for end of measurements
        while(measure_on);
        // stop high speed timer
        //timer2.stopTimer();
        // measure current
        measure_current(1);
        // stop impulse
        gpio.low();
        //low semyperiod =====================
        // start high speed timer
        //timer2.startTimer();
        // start measurements
        measurement_counter = 0;
        measure_on = 1;
        // wait for end of measurements
        while(measure_on);
        
    }
    
    // stop high speed timer
    timer2.stopTimer();
    
    // turn off current sensor (pa3 low)
    GPIOA->BSRRH=GPIO_Pin_3;  
    
    measure_and_save_flag = 0;
    // reset pa0
    GPIOA->BSRRH=GPIO_Pin_0; 
    uart.transmitMessage("FINISH TEST");
    
    // start low speed timer
    timer3.startTimer();
}

void readAds8320(void)
{
   uint32_t ads8320Data = 0;
   uint8_t byteBuffer;
   
   GPIOA->BSRRH=GPIO_Pin_8;  //CS pin low (start spi communication)
   
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   SPI1->DR=0x55;
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   while ((SPI1->SR & SPI_I2S_FLAG_RXNE) == RESET);
   byteBuffer=SPI1->DR;
   // apply 00000011 mask (0x03); 5 clocks and first zero dout
   byteBuffer &= 0x03;
   ads8320Data |= (uint32_t)byteBuffer;
   ads8320Data <<= 8;
   
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   SPI1->DR=0x55;
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   while ((SPI1->SR & SPI_I2S_FLAG_RXNE) == RESET);
   byteBuffer=SPI1->DR;
   ads8320Data |= (uint32_t)byteBuffer;
   ads8320Data <<= 8;
   
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   SPI1->DR=0x55;
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   while ((SPI1->SR & SPI_I2S_FLAG_RXNE) == RESET);
   byteBuffer=SPI1->DR;
   ads8320Data |= (uint32_t)byteBuffer;
   ads8320Data >>= 2;  // 2 "extra" clocks
   
   common.ads8320Data = ads8320Data;
   
   GPIOA->BSRRL=GPIO_Pin_8;  //CS pin high (stop spi communication)
}

void readAds8320_2(void)
{
   uint32_t ads8320Data = 0;
   uint8_t byteBuffer;
   
   GPIOB->BSRRH=GPIO_Pin_10;  //CS pin low (start spi communication)
   
   while ((SPI2->SR & SPI_I2S_FLAG_TXE) == RESET );
   SPI2->DR=0x55;
   while ((SPI2->SR & SPI_I2S_FLAG_TXE) == RESET );
   while ((SPI2->SR & SPI_I2S_FLAG_RXNE) == RESET);
   byteBuffer=SPI2->DR;
   // apply 00000011 mask (0x03); 5 clocks and first zero dout
   byteBuffer &= 0x03;
   ads8320Data |= (uint32_t)byteBuffer;
   ads8320Data <<= 8;
   
   while ((SPI2->SR & SPI_I2S_FLAG_TXE) == RESET );
   SPI2->DR=0x55;
   while ((SPI2->SR & SPI_I2S_FLAG_TXE) == RESET );
   while ((SPI2->SR & SPI_I2S_FLAG_RXNE) == RESET);
   byteBuffer=SPI2->DR;
   ads8320Data |= (uint32_t)byteBuffer;
   ads8320Data <<= 8;
   
   while ((SPI2->SR & SPI_I2S_FLAG_TXE) == RESET );
   SPI2->DR=0x55;
   while ((SPI2->SR & SPI_I2S_FLAG_TXE) == RESET );
   while ((SPI2->SR & SPI_I2S_FLAG_RXNE) == RESET);
   byteBuffer=SPI2->DR;
   ads8320Data |= (uint32_t)byteBuffer;
   ads8320Data >>= 2;  // 2 "extra" clocks
   
   common.ads8320Data_2 = ads8320Data;
   
   GPIOB->BSRRL=GPIO_Pin_10;  //CS pin high (stop spi communication)
}

void readAd7691(void)
{
   int32_t ad7691Data = 0;
   uint8_t byteBuffer = 0;
   
   GPIOA->BSRRL=GPIO_Pin_8;  //CNV pin high (start analog to digit conversion)
   GPIOA->BSRRH=GPIO_Pin_8;  //CNV pin low (initiate busy indicator)
   
   while((GPIOA->IDR & GPIO_Pin_6) != (uint32_t)Bit_RESET); // wait for an end of conversion
   
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   SPI1->DR=0x55;
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   while ((SPI1->SR & SPI_I2S_FLAG_RXNE) == RESET);
   byteBuffer=SPI1->DR;
   // apply mask 0x7f
   //byteBuffer &= (uint8_t)0x7f;
   ad7691Data |= (uint32_t)byteBuffer;
   ad7691Data <<= 8;
   
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   SPI1->DR=0x55;
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   while ((SPI1->SR & SPI_I2S_FLAG_RXNE) == RESET);
   byteBuffer=SPI1->DR;
   ad7691Data |= (uint32_t)byteBuffer;
   ad7691Data <<= 8;
   
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   SPI1->DR=0x55;
   while ((SPI1->SR & SPI_I2S_FLAG_TXE) == RESET );
   while ((SPI1->SR & SPI_I2S_FLAG_RXNE) == RESET);
   byteBuffer=SPI1->DR;
   ad7691Data |= (uint32_t)byteBuffer;
   
   ad7691Data <<= 8;   // проверяем знак
   if(ad7691Data < 0)
       ad7691Data = 0;
   else // положительное число
   {
       ad7691Data >>= 8;
       ad7691Data >>= 5;  // 5 "extra" clocks
   }
   
   common.ad7691Data = ad7691Data;
   
}


void measure_voltage_temperature()
{
    int i;
    double voltage = 0;
    float temperature1;
    
#ifdef THEMPERATURE2
    float temperature2;
#endif
    
    measure_voltage_temperature_flag = 0;

    // led off
    //led.LED_Off();
    
    // get data from external adc
    for(i=0;i<100;i++)
    {
        readAds8320();
        voltage += (double)common.ads8320Data;
    }
    voltage /= 100.0;
    //debug*****
    //voltage = (double)common.ad7691Data;
    //debug*****
    voltage = voltage/1000.0*38.0*1.81;
    // voltage data output
    //debug
    //printf("%d\r\n", common.ads8320Data);
    sprintf(voltage_message, "U = %7.1f", voltage);
    //uart.transmitMessage(voltage_message);
    //uart.transmitMessage("\r\n");
    //printf("%s\r\n", voltage_message);
    
    //get temperature
    // set pins pa9 and pa10
    GPIOA->BSRRL=GPIO_Pin_9; 
    GPIOA->BSRRL=GPIO_Pin_10; 
    temperature1 = thermometer.readThemperature(1);
#ifdef THEMPERATURE2
    temperature2 = thermometer.readThemperature(2);
#endif
    // reset pins pa9 and pa10
    GPIOA->BSRRH=GPIO_Pin_9; 
    GPIOA->BSRRH=GPIO_Pin_10; 
    // temperature data output
    //debug
    //printf("%d\r\n", common.ads8320Data);
    sprintf(temperature_message, "T = %7.1f", temperature1);
#ifdef THEMPERATURE2
    sprintf(temperature2_message, "O = %7.1f", temperature2);
#else
    sprintf(temperature2_message, "O = -----");
#endif
    //uart.transmitMessage(temperature_message);
    //uart.transmitMessage("\r\n");
    //printf("%s\r\n", temperature_message);
    //*/
    
       
}

void measure_highlow_current()
{
    int i;
    double current = 0;
    
    //turn on current sensor (pa3 high)
    GPIOA->BSRRL=GPIO_Pin_3; 
    // delay 0.5 sec
    for(volatile long i=0; i<4000000; i++);
    // get data from external adc
    for(i=0;i<400;i++)
    {
        readAds8320_2();
        current += (double)common.ads8320Data_2;
    }
    // turn off current sensor (pa3 low)
    GPIOA->BSRRH=GPIO_Pin_3;  
    
    current /= 400.0;
    current = 20.0 - current * (80.0 / 65535.0); 
    sprintf(Il_message, "Il = %7.1f", current);
    sprintf(Ih_message, "Ih = %7.1f", current);
}

void plot_output(int output_slowly)
{
    int j, k;
    uint16_t aux;
    
    //char message[64];
    char voltage_message[64];
    char current_message[128];
    
    // stop low speed timer
    timer3.stopTimer();
    
    uart.transmitMessage("START DATA");
    sprintf(message, "version = %s", VERSION);
    uart.transmitMessage(message);
    sprintf(message, "current = %d", common.i_setting);
    uart.transmitMessage(message);

    sprintf(message, "frequency = %f", working_frequency);
    uart.transmitMessage(message);

    sprintf(message, "number of samples = %d", samples_in_one_pulse);
    uart.transmitMessage(message);

    uart.transmitMessage(test_voltage_message);
    uart.transmitMessage(test_temperature_message);

    uart.transmitMessage(test_temperature2_message);
    uart.transmitMessage(test_Il_message);
    uart.transmitMessage(test_Ih_message);
   
    uart.transmitMessage("START LOG");

    //*
    for(k=0; k<common.number_of_pulses*2; k++)
    {
        if(k%2 == 0)
        {
            //aux = current_buffer[k/2];
            aux = current_buffer[k/2]*5/5;
            sprintf(current_message, "I = %d **************************************** %04d", aux, k);
            uart.transmitMessage(current_message);
        }
        else
        {
            sprintf(current_message, "I = %d **************************************** %04d", 0, k);
            uart.transmitMessage(current_message);
        }
        
        for(j=0; j<samples_in_one_pulse; j++)
        {
            sprintf(voltage_message, "%7.1f", (double)(data_buffer[k*samples_in_one_pulse + j])/1000.0*38.0*1.81);
            uart.transmitMessage(voltage_message);
            //uart.transmitMessage("");
            //printf("%s", voltage_message);
            if(output_slowly)
            {
                for(int j=0; j<5; j++) // 25 msec
                {
                    for(volatile long i=0; i<13100; i++);
                    for(volatile long i=0; i<13100; i++);
                    for(volatile long i=0; i<13100; i++);
                    for(volatile long i=0; i<13100; i++);
                    for(volatile long i=0; i<13100; i++);
                }
            }
        }
        
        
    }
    //*/
    
    uart.transmitMessage("FINISH LOG");
    uart.transmitMessage("FINISH DATA");
    
    /*
    for(j=0; j<(CURRENT_BUF_LENGTH/divisor); j++)
    {
        sprintf(current_message, "%05d", current_buffer[j]);
        uart.transmitMessage(current_message);
        uart.transmitMessage("\r\n");
        for(volatile long i=0; i<13100; i++);
        for(volatile long i=0; i<13100; i++);
        for(volatile long i=0; i<13100; i++);
    }
    */
    
    start_plot_output_flag = 0;
    short_plot_output_flag = 0;
    start_slowly_plot_output_flag = 0;
    
    // start low speed timer
    timer3.startTimer();
}


void high_high_plot_output()
{
}


void get_voltage()  // GETU
{
    get_voltage_flag = 0;
    
    measure_voltage_temperature();
    
    uart.transmitMessage(voltage_message);
    //uart.transmitMessage("");
   
}


void get_voltage_and_temperature()  // GETUT
{
    voltage_and_temperature_flag = 0;
    
    measure_voltage_temperature();
    
    
    uart.transmitMessage(voltage_message);
    uart.transmitMessage("; ");
    
    uart.transmitMessage(temperature_message);
    //uart.transmitMessage("");
}

void get_voltage_temperature_current()  // GETUTI
{
    voltage_temperature_current_flag = 0;
    
    measure_voltage_temperature();
    measure_highlow_current();
    
    uart.transmitMessage("START GETUTI");
    
    uart.transmitMessage(voltage_message);
    //uart.transmitMessage("");
    uart.transmitMessage(temperature_message);
    //uart.transmitMessage("");
    uart.transmitMessage(temperature2_message);
    //uart.transmitMessage("");
    uart.transmitMessage(Il_message);
    uart.transmitMessage(Ih_message);
    
    uart.transmitMessage("FINISH GETUTI");
}
    


//-----------------------end tasks definitions----------------------------------


// SOME NOTABENES

// timeout with increment of counter: 13100 -> 1 milisecond (120 MHz)
//for(volatile long i=0; i<13100; i++);
// timeout with increment of counter: 129 -> 1 microsecond (120 MHz)
//for(volatile long i=0; i<129; i++);

//timing control <<<<<<<<<<<<<<<<<<<<<
//GPIOD->BSRRL = GPIO_Pin_5;   //pd5 high
//GPIOD->BSRRH = GPIO_Pin_5;   //pd5 low
//timing control >>>>>>>>>>>>>>>>>>>>>






//-----------------------------------------------------------------------------
//*****************************************************************************
//                              MAIN
//*****************************************************************************
//-----------------------------------------------------------------------------


int main()
{
 
    // configure zigbee module
    // disassociate with any pan
    //uart.transmit_zigbee_command("AT+DASSL\r\n");
    //for(volatile long i=0; i<1310000; i++);  // 100 msec
    // join pan eda0 in 11 channel
    //uart.transmit_zigbee_command("AT+JPAN:11,EDA0\r\n");
    //for(volatile long i=0; i<1310000; i++);  // 100 msec
    
    // power on analog circuit
    //GPIOB->BSRRH=GPIO_Pin_8;
   
  
   //timer3.startTimer();
   //timer2.startTimer();
   
   // pause before go to sleep (5 seconds)
   //for(volatile long i=0; i<5000; i++)
   //{
       //for(volatile long j=0; j<13100; j++);
   //}
   
   // turn analog circuit on
   GPIOB->BSRRH=GPIO_Pin_8;  // to 0
   //turn on current sensor (pa3 high)
    GPIOA->BSRRL=GPIO_Pin_3; 
   // no sleep here
   sleep_flag = 0;
   
   
   
   double voltage = 0;
   
   led.LED_Off();
   // wait for a voltage ******************************************
   while(voltage < 10000.0)
   {
       readAds8320();
       voltage = common.ads8320Data;
       voltage = voltage/1000.0*38.0*1.81*6.86;
   }
   led.LED_On();
   
   // pause 2 sec
   for(volatile int j=0; j<20; j++)
       for(volatile long i=0; i<1310000; i++);  // 100 msec
   
   led.LED_Off();
   
   // start converting and saving data *********************************
   samples_in_one_pulse = 10000;
   measure_on = 1;
   timer2.setPeriod(100);   // 100 uSec
   timer2.init_timer();
   timer2.startTimer();
   
   // wait for end of measurements
   while(measure_on);
   
   // wait for a get log command and output plot
   while(1)
   {
       if(start_plot_output_flag)
           high_high_plot_output();
   }
   
   
   while(1)
   {
       if(full_line_received_flag)
           uart1_receive_interrupt_service();
       if(measure_voltage_temperature_flag)
           measure_voltage_temperature();
       if(voltage_temperature_current_flag)
           get_voltage_temperature_current();
       if(voltage_and_temperature_flag)
           get_voltage_and_temperature();
       if(measure_and_save_flag)
           measure_and_save();
       if(test_current_flag)
           test_current();
       if(get_voltage_flag)
           get_voltage();
       if(start_plot_output_flag)
           plot_output(0);
       if(start_slowly_plot_output_flag)
           plot_output(1);
       if(sleep_flag)
       {
            timer3.stopTimer();
            for(volatile long i=0; i<8000000; i++);
            led.LED_Off();
            // podgotovka ko snu
            //*
            //GPIOA->BSRRH=GPIO_Pin_9;  // termodatchik
            //GPIOA->BSRRH=GPIO_Pin_10;  // termodatchik
            GPIOB->BSRRL=GPIO_Pin_8;  // to 1
            //*/
            
            //uart.transmitMessage("SLEEPING\r\n");
            __WFI();
            
            
            // probuzhdenie
            //*
            //GPIOA->BSRRL=GPIO_Pin_9;  // termodatchik
            //GPIOA->BSRRL=GPIO_Pin_10;  // termodatchik
            GPIOB->BSRRH=GPIO_Pin_8;  // to 0
            
            for(volatile long i=0; i<40000000; i++);
            //*/
            
            sleep_flag = 0;
            //timer3.startTimer();
            //uart.transmitMessage("AWAKEN\r\n");
            led.LED_On();
       }
       
       /*
       if(bluetooth_silence >= BLUETOOTH_SILENCE_PERIOD)
       {
           bluetooth_silence = 0;
           uart.transmitMessage("bluetooth reset");
           
           gpio.bluetooth_reset();
       }
       */
   }
   
  
}


// auxiliary functions
double abs(double value)
{
    if(value >= 0.0)
        return value;
    else
        return -value;
}
