/*
Copyright (c) 2019 SparkFun Electronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "variant.h"

const ap3_gpio_pad_t ap3_variant_pinmap[AP3_VARIANT_NUM_PINS] = {
    0,
    1,
    AP3_GPIO_PAD_UNUSED,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    AP3_GPIO_PAD_UNUSED,
    17,
    AP3_GPIO_PAD_UNUSED,
    AP3_GPIO_PAD_UNUSED,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    AP3_GPIO_PAD_UNUSED,
    AP3_GPIO_PAD_UNUSED,
    AP3_GPIO_PAD_UNUSED,
    33,
    AP3_GPIO_PAD_UNUSED,
    AP3_GPIO_PAD_UNUSED,
    36,
    37,
    38,
    39,
    40,
    AP3_GPIO_PAD_UNUSED,
    42,
    43,
    44,
    AP3_GPIO_PAD_UNUSED,
    46,
    47,
    48,
    49,
};

// Uart Definitions
Uart Serial(0, 49, 48);// declares a Uart object called Serial using instance 0 of Apollo3 UART peripherals with RX on pin 49 and TX on pin 48 (note, you specify *pins* not Apollo3 pads. This uses the variant's pin map to determine the Apollo3 pad)
