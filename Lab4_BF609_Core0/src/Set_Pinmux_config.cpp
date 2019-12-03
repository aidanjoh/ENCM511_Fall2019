/*
 * Set_Pinmux_config.c
 *
 *  Created on: Aug 7, 2018
 *      Author: smithmr
 */

/*
 **
 ** Source file generated on January 10, 2018 at 10:01:21.
 **
 ** Copyright (C) 2018 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 */

#if 1
/*
 **
 ** pinmux_config.c source file generated on March 8, 2013 at 16:41:46.
 **
 ** Copyright (C) 2000-2013 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 ** SPI0 (CLK, MISO, MOSI, SEL1)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** PD02, PD03, PD04, PD11
 */

#include <sys/platform.h>
#include <stdint.h>

#define SPI0_CLK_PORTD_MUX  ((uint16_t) ((uint16_t) 0<<8))
#define SPI0_MISO_PORTD_MUX  ((uint16_t) ((uint16_t) 0<<4))
#define SPI0_MOSI_PORTD_MUX  ((uint16_t) ((uint16_t) 0<<6))
#define SPI0_SEL1_PORTD_MUX  ((uint32_t) ((uint32_t) 0<<22))

#define SPI0_CLK_PORTD_FER  ((uint16_t) ((uint16_t) 1<<4))
#define SPI0_MISO_PORTD_FER  ((uint16_t) ((uint16_t) 1<<2))
#define SPI0_MOSI_PORTD_FER  ((uint16_t) ((uint16_t) 1<<3))
#define SPI0_SEL1_PORTD_FER  ((uint32_t) ((uint32_t) 1<<11))

#define SPI0_SEL4_PORTC_MUX  ((uint32_t) ((uint32_t) 0<<30))
#define SPI0_SEL4_PORTC_FER  ((uint32_t) ((uint32_t) 1<<15))

// int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX and FER Registers
 */
int32_t Smith_adi_initpinmux(void) {

#if 1
    /* PORTx_MUX registers */
    *pREG_PORTD_MUX = SPI0_CLK_PORTD_MUX | SPI0_MISO_PORTD_MUX
     | SPI0_MOSI_PORTD_MUX ; // | SPI0_SEL1_PORTD_MUX;

    /* PORTx_FER registers */
    *pREG_PORTD_FER = SPI0_CLK_PORTD_FER | SPI0_MISO_PORTD_FER
     | SPI0_MOSI_PORTD_FER ; // | SPI0_SEL1_PORTD_FER;

    /* PORTx_MUX registers */
    *pREG_PORTC_MUX = SPI0_SEL4_PORTC_MUX;

    /* PORTx_FER registers */
    *pREG_PORTC_FER = SPI0_SEL4_PORTC_FER;

    /* PORTx_MUX registers */
//   *pREG_PORTE_MUX = SPI0_SEL4_PORTC_MUX;

    /* PORTx_FER registers */
//    *pREG_PORTE_FER = SPI0_SEL4_PORTC_FER;
#endif
    return 0;
}

#else

#include <sys/platform.h>
#include <stdint.h>

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX Registers
 */
int32_t adi_initpinmux(void) {

    return 0;
}

#endif
