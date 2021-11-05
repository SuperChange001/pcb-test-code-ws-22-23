#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

// Step 1:
// int main(){ 
//     // Enable UART so we can print status output
//     stdio_init_all();
    
//     while(1){
        
//         char input_char = getchar_timeout_us(10000);
//         if(input_char>=32 &&input_char<=126){
//             printf("%c",input_char);
//             // sleep_ms(1000);
//         }else{
//             // Uncomment the line below for testing
//             // printf("i dont know what you typed:%d.\n", input_char);
//         }

//     }
// }



// Step 2:
// we want to get a adc meaurement
// void adc_print_value(){
//     adc_init();
//     adc_gpio_init(27); // pin to the resistor
//     adc_select_input(1); // this channel is conneced to pin 27
//     uint16_t adc_value = adc_read(); // 12-bit, 0 to (2^12-1)
//     float voltage = adc_value*3.3/((1<<12)-1);
//     printf("adc read, int value: %d\n", adc_value);
//     printf("adc read, float value: %f\n", voltage);
// }

// int main(){ 
//     // Enable UART so we can print status output
//     stdio_init_all();
    
//     while(1){
        
//         char input_char = getchar_timeout_us(10000);
//         if(input_char>=32 &&input_char<=126){
//             if(input_char=='t'){
//                 adc_print_value();
//             }
//             // sleep_ms(1000);
//         }else{
//             // Uncomment the line below for testing
//             // printf("i dont know what you typed:%d.\n", input_char);
//         }

//     }
// }

// step3
// 10 times reading
// single conversion
// void adc_print_value(){
//     uint16_t buf[10];
//     adc_init();
//     adc_gpio_init(27); // pin to the resistor
//     adc_select_input(1); // this channel is conneced to pin 27

//     for(int i=0; i<10; i++){
//         buf[i] = adc_read(); // 12-bit, 0 to (2^12-1)
//     }

//     for(int i=0; i<10; i++){
//         float voltage = buf[i]*3.3/((1<<12)-1);
//         printf("adc read, int value: %d\t", buf[i]);
//         printf("float value: %f\n", voltage);
//     }
// }

// int main(){ 
//     // Enable UART so we can print status output
//     stdio_init_all();
    
//     while(1){
        
//         char input_char = getchar_timeout_us(10000);
//         if(input_char>=32 &&input_char<=126){
//             if(input_char=='t'){
//                 adc_print_value();
//             }
//             // sleep_ms(1000);
//         }else{
//             // Uncomment the line below for testing
//             // printf("i dont know what you typed:%d.\n", input_char);
//         }

//     }
// }

// Step 4: use continues conversion to get 10 measurements
// why 10 times? does 20 times help?
// #include "hardware_setup.h"
// void adc_measure_10_times(void){
//    uint16_t buffer[10];
//    const float conversion_factor = 3.3f / ((1 << 12)-1);

//    adc_init();            // initialize the adc
//    adc_gpio_init(27);     // set a GPIO Pin as analogue input function
//    adc_select_input(1);   // connect the gpio pin to the ADC input

//    // measure
//    adc_capture(buffer, 10);

//    // calculating
//    for(int i=0; i<10; i++){
//        float adc_float_voltage = buffer[i] * conversion_factor;
//        printf("Voltage: %04f\n", adc_float_voltage);
//    }

//    adc_run(false);
// }

// int main(){
//    stdio_init_all(); // minimum code for using USB debug function
//    while(1){
//        char input_char = getchar_timeout_us(10000);
//        if(input_char=='t'){
//            adc_measure_10_times();
//        }
//        else if(input_char>=32&&input_char<126){
//            printf("No mapping to command key: '%c'\n", input_char);
//        }else if(input_char!=0){
//            // do nothing
//        }
//    }
// }


//step5: Averaging
//void adc_measure_average(uint16_t times){
//    uint16_t buffer[200];
//    const float conversion_factor = 3.3f / (1 << 12);
//
//    adc_init();                 // initialize the adc
//    adc_gpio_init(27);     // set a GPIO Pin as analogue input function
//    adc_select_input(1);  // connect the gpio pin to the ADC input
//
//    // measure
//    adc_capture(buffer, times);
//
//    uint32_t sum = 0;
//    // calculating
//    for(int i=0; i<times; i++){
//        sum += buffer[i];
//    }
//
//    float adc_float_voltage = sum * conversion_factor/times;
//    printf("Voltage: %04f\n", adc_float_voltage);
//
//    adc_run(false);
//}
//
//int main(){
//    stdio_init_all(); // minimum code for using USB debug function
//    while(1){
//        char input_char = getchar_timeout_us(10000);
//        if(input_char=='t'){
//            adc_measure_average(10);
//        }
//        else if(input_char>=32&&input_char<126){
//            printf("No mapping to command key: '%c'\n", input_char);
//        }else if(input_char!=0){
//            // do nothing
//        }
//    }
//}


float adc_measure_calibrated(uint16_t times){
    uint16_t buffer[200];
    const float conversion_factor = 3.3f / (1 << 12);

    adc_init();                 // initialize the adc
    adc_gpio_init(27);     // set a GPIO Pin as analogue input function
    adc_select_input(1);  // connect the gpio pin to the ADC input

    // measure
    adc_capture(buffer, times);

    uint32_t sum = 0;
    // calculating
    for(int i=0; i<times; i++){
        sum += buffer[i];
    }

    float adc_float_voltage = sum * conversion_factor/times;
    float adc_float_voltage_calibrated = adc_float_voltage*1.01+0.2;
//    printf("Voltage: %04f\n", adc_float_voltage_calibrated);

    adc_run(false);
    return adc_float_voltage_calibrated;
}

int main(){
    stdio_init_all(); // minimum code for using USB debug function
    while(1){
        char input_char = getchar_timeout_us(10000);
        if(input_char=='t'){
            float adc_cal_voltage = adc_measure_calibrated(10);
            printf("Voltage: %04f\n", adc_cal_voltage);
        }
        else if(input_char>=32&&input_char<126){
            printf("No mapping to command key: '%c'\n", input_char);
        }else if(input_char!=0){
            // do nothing
        }
    }
}