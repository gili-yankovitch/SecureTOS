//*****************************************************************************
//
//! @file ble_freertos.c
//!
//! @brief ARM Cordio BLE - Proximity Tag Example
//!
//! Purpose: This is a standard BLE Proximity Profile example.
//!
//! Printing takes place over the ITM at 1M Baud.
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2019, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 2.3.2 of the AmbiqSuite Development Package.
//
//*****************************************************************************

//*****************************************************************************
//
// This application has a large number of common include files. For
// convenience, we'll collect them all together in a single header and include
// that everywhere.
//
//*****************************************************************************
//#include "ap3_gpio.h"
//#include "variant.h"

typedef unsigned char bool;
#include <stdint.h>
#include <hal/am_hal_status.h>
#include <hal/am_hal_gpio.h>
#include "main.h"
#include "tasks_setup.h"

//*****************************************************************************
//
// Enable printing to the console.
//
//*****************************************************************************
void
enable_print_interface(void)
{
    //
    // Initialize a debug printing interface.
    //
    am_bsp_itm_printf_enable();
    am_bsp_uart_printf_enable();
}

static void ap3_init( void )
{
    // Set the clock frequency.
    //am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);

    // Set the default cache configuration
    //am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();

    // Configure the board for low power operation.
    am_bsp_low_power_init();

    // Configure the stimer
    am_hal_stimer_int_enable(AM_HAL_STIMER_INT_OVERFLOW);
    NVIC_EnableIRQ(STIMER_IRQn);
    am_hal_stimer_config(AM_HAL_STIMER_CFG_CLEAR | AM_HAL_STIMER_CFG_FREEZE);
    am_hal_stimer_config(AM_HAL_STIMER_HFRC_3MHZ);

    // Enable interruts master
    //am_hal_interrupt_master_enable();
}

extern am_hal_gpio_pincfg_t g_AM_HAL_GPIO_OUTPUT_WITH_READ_12;

//*****************************************************************************
//
// Main Function
//
//*****************************************************************************

extern const am_hal_gpio_pincfg_t g_AM_HAL_GPIO_ENABLE;

int
main(void)
{
	// ap3_err_t ret;

    //
    // Set the clock frequency
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);

    //
    // Set the default cache configuration
    //
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();

#ifndef NOFPU
    //
    // Enable the floating point module, and configure the core for lazy
    // stacking.
    //
    am_hal_sysctrl_fpu_enable();
    am_hal_sysctrl_fpu_stacking_enable(true);
#else
    am_hal_sysctrl_fpu_disable();
#endif

    //
    // Configure the board for low power.
    //
    am_bsp_low_power_init();

    // Turn on LED
    //padMode(19, AP3_PINCFG_OUTPUT, &ret);
    // AP3_PINCFG_OUTPUT

    // am_hal_rtc_osc_enable();
    //am_hal_gpio_pinconfig(20, g_AM_HAL_GPIO_ENABLE);
    // am_hal_gpio_pinconfig(21, g_AM_HAL_GPIO_ENBLE);
    // am_hal_gpio_pinconfig(48, g_AM_HAL_GPIO_ENABLE);
    // am_hal_gpio_pinconfig(49, g_AM_HAL_GPIO_ENBLE);

    // am_hal_stimer_config(AM_HAL_STIMER_HFRC_3MHZ);

    am_hal_gpio_pinconfig(19, g_AM_HAL_GPIO_OUTPUT_WITH_READ_12);
    am_hal_gpio_output_set(19);
    // am_hal_gpio_pinconfig(38, g_AM_HAL_GPIO_OUTPUT_WITH_READ_12);
    // am_hal_gpio_output_set(38);

    // Turn off unused Flash & SRAM

    //
    // Enable printing to the console.
    //
#ifdef AM_DEBUG_PRINTF
    am_bsp_uart_printf_enable();
#endif

	//ap3_init();

    //
    // Initialize plotting interface.
    //

    //
    // Run the application.
    //
    uprintf("Running tasks...\r\n");
    run_tasks();

    //
    // We shouldn't ever get here.
    //
    while (1)
    {
    }

}

