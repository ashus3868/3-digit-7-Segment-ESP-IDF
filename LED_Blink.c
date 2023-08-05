#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

const int seven_seg_pins[7] = {GPIO_NUM_33,
                               GPIO_NUM_25,
                               GPIO_NUM_26,
                               GPIO_NUM_27,
                               GPIO_NUM_4,
                               GPIO_NUM_2,
                               GPIO_NUM_5};
const int digit_select[3] = {GPIO_NUM_32,
                             GPIO_NUM_21,
                             GPIO_NUM_19};
const int numbers[10][7] = {{0, 0, 0, 0, 0, 0, 1},  // 0
                            {1, 0, 0, 1, 1, 1, 1},  // 1
                            {0, 0, 1, 0, 0, 1, 0},  // 2
                            {0, 0, 0, 0, 1, 1, 0},  // 3
                            {1, 0, 0, 1, 1, 0, 0},  // 4
                            {0, 1, 0, 0, 1, 0, 0},  // 5
                            {0, 1, 0, 0, 0, 0, 0},  // 6
                            {0, 0, 0, 1, 1, 1, 1},  // 7
                            {0, 0, 0, 0, 0, 0, 0},  // 8
                            {0, 0, 0, 1, 1, 0, 0}}; // 9

int count = 0;
char number[3] = "000";

void digit_display()
{
    
    for (int j = 0; j < 3; j++)
    {
        int c = number[j] - '0';
        // printf("%d %d ", j, c);
        // gpio_set_level(digit_select[j],state);
        if (j == 0)
        {
            gpio_set_level(digit_select[0], 1);
            gpio_set_level(digit_select[1], 0);
            gpio_set_level(digit_select[2], 0);
        }
        else if (j == 1)
        {
            gpio_set_level(digit_select[0], 0);
            gpio_set_level(digit_select[1], 1);
            gpio_set_level(digit_select[2], 0);
        }
        else if (j == 2)
        {
            gpio_set_level(digit_select[0], 0);
            gpio_set_level(digit_select[1], 0);
            gpio_set_level(digit_select[2], 1);
        }

        for (int i = 0; i < 7; i++)
        {
            gpio_set_level(seven_seg_pins[i], numbers[c][i]);
        }
        vTaskDelay(1);
    }
}
void app_main(void)
{
    for (int x = 0; x < 10; x++)
    {

        if (x >= 7)
        {
            gpio_set_direction(digit_select[x - 7], GPIO_MODE_OUTPUT);
        }
        else
        {
            gpio_set_direction(seven_seg_pins[x], GPIO_MODE_OUTPUT);
        }
    }

    gpio_set_direction(GPIO_NUM_23, GPIO_MODE_INPUT);

    while (1)
    {
        if (gpio_get_level(GPIO_NUM_23))
        {
            count += 1;
            if (count < 10)
            {
                // sprintf(number, "00%d", count);
                number[0] = '0';
                number[1] = '0';
                number[2] = count + '0';
            }
            else if ((count >= 10) && (count <= 99))
            {

                // sprintf(number, "0%d", count);
                number[0] = '0';
                number[1] = (count / 10) + '0';
                number[2] = (count % 10) + '0';
            }
            else if ((count >= 100) && (count <= 999))
            {

                // sprintf(number, "%d", count);
                number[0] = (count / 100) + '0';
                number[1] = ((count % 100) / 10) + '0';
                number[2] = (count % 10) + '0';
            }

            else
            {
                count = 0;
                // sprintf(number, "000");
                number[0] = '0';
                number[1] = '0';
                number[2] = '0';
            }
        }
        for (size_t i = 0; i < 12; i++)
        {
            digit_display();
        }
    }
}

// #include <stdio.h>
// #include "driver/gpio.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// const int seven_seg_pins[7] = {GPIO_NUM_22, GPIO_NUM_21, GPIO_NUM_19, GPIO_NUM_18, GPIO_NUM_5, GPIO_NUM_4, GPIO_NUM_2};
// const int numbers[10][7] = {{0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 1, 0},
// {0, 0, 0, 0, 1, 1, 0}, {1, 0, 0, 1, 1, 0, 0}, {0, 1, 0, 0, 1, 0, 0}, {0, 1, 0, 0, 0, 0, 0},
// {0, 0, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0}};

// int count = 0;

// void app_main(void)
// {
//     for (int x = 0; x < 7; x++)
//     {
//         gpio_set_direction(seven_seg_pins[x], GPIO_MODE_OUTPUT);
//     }

//     gpio_set_direction(GPIO_NUM_23, GPIO_MODE_INPUT);

//     while (1)
//     {
//         if (gpio_get_level(GPIO_NUM_23))
//         {
//             if (count < 9)
//             {
//                 count += 1;
//             }
//             else
//             {
//                 count = 0;
//             }
//         }
//         else
//         {
//         }

//         for (int i = 0; i < 7; i++)
//         {
//             gpio_set_level(seven_seg_pins[i], numbers[count][i]);
//         }
//         vTaskDelay(30);
//     }
// }
