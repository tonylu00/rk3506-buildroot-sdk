/*
 * Copyright (c) 2022 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-08     Steven Liu   first implementation
 */

#include "rtdef.h"
#include "iomux.h"
#include "hal_base.h"

#ifdef RT_USING_PIN
/**
 * @brief  Config iomux for UART0
 */
RT_WEAK void uart0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_C6 |  // UART0_TX
                         GPIO_PIN_C7,   // UART0_RX
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for UART3
 */
RT_WEAK void uart3_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_B2,
                        RMIO_UART3_TX);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_B3,
                        RMIO_UART3_RX);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_D1,
                        RMIO_UART3_CTS_REN);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_B1,
                        RMIO_UART3_RTSN_DE);
}

/**
 * @brief  Config iomux for UART4
 */
RT_WEAK void uart4_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_C2,
                        RMIO_UART4_TX);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_C3,
                        RMIO_UART4_RX);
}

/**
 * @brief  Config iomux for UART5
 */
RT_WEAK void uart5_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_B2 |  // UART0_CTSN
                         GPIO_PIN_B3 |  // UART0_RX
                         GPIO_PIN_B4 |  // UART0_TX
                         GPIO_PIN_B5,   // UART0_RTSN
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for I2C0
 */
RT_WEAK void i2c0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B5,
                        RMIO_I2C0_SCL);

    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B6,
                        RMIO_I2C0_SDA);
}

/**
 * @brief  Config iomux for I2C2
 */
RT_WEAK void i2c2_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_A4,
                        RMIO_I2C2_SCL);

    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_A5,
                        RMIO_I2C2_SDA);
}

/**
 * @brief  Config iomux for RMII0
 */
void rmii0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_B0 |  // ETH_RMII_RXD0
                         GPIO_PIN_B1 |  // ETH_RMII_RXD1
                         GPIO_PIN_B2 |  // ETH_RMII_CLK
                         GPIO_PIN_B3 |  // ETH_RMII_TXD0
                         GPIO_PIN_B4 |  // ETH_RMII_TXD1
                         GPIO_PIN_B5 |  // ETH_RMII_TXEN
                         GPIO_PIN_B6 |  // ETH_RMII_MDC
                         GPIO_PIN_B7 |  // ETH_RMII_MDIO
                         GPIO_PIN_C0,   // ETH_RMII_CRSDV
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for RMII1
 */
void rmii1_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_A6 |  // ETH_RMII_RXD0
                         GPIO_PIN_A7 |  // ETH_RMII_RXD1
                         GPIO_PIN_B0 |  // ETH_RMII_CLK
                         GPIO_PIN_B1 |  // ETH_RMII_TXD0
                         GPIO_PIN_B2 |  // ETH_RMII_TXD1
                         GPIO_PIN_B3 |  // ETH_RMII_TXEN
                         GPIO_PIN_B4 |  // ETH_RMII_MDC
                         GPIO_PIN_B5 |  // ETH_RMII_MDIO
                         GPIO_PIN_B6,   // ETH_RMII_CRSDV
                         PIN_CONFIG_MUX_FUNC2);
}

/**
 * @brief  Config iomux for CAN0
 */
RT_WEAK void can0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_D2,   // CAN_TX
                        RMIO_CAN0_TX);

    HAL_PINCTRL_SetRMIO(GPIO_BANK1,
                        GPIO_PIN_D3,   // CAN_RX
                        RMIO_CAN0_RX);
}

/**
 * @brief  Config iomux for SDIO
 */
RT_WEAK void emmc_iomux_config(void)
{
    /* EMMC D0 ~ D7 & CMD & CLK*/
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_A0 |  /* CLK */
                         GPIO_PIN_A1 |  /* CMD */
                         GPIO_PIN_A2 |  /* D0 */
                         GPIO_PIN_A3 |  /* D1 */
                         GPIO_PIN_A4 |  /* D2 */
                         GPIO_PIN_A5,   /* D3 */
                         PIN_CONFIG_MUX_FUNC1);

    /* need an internal pull up or an external pull up */
    HAL_PINCTRL_SetParam(GPIO_BANK3,
                         GPIO_PIN_A2 |  /* D0 */
                         GPIO_PIN_A3 |  /* D1 */
                         GPIO_PIN_A4 |  /* D2 */
                         GPIO_PIN_A5,   /* D3 */
                         PIN_CONFIG_PUL_UP);
}

/**
 * @brief  Config iomux for LCDC
 */
RT_WEAK  void lcdc_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK1,
                         GPIO_PIN_A0 |  // VO_LCDC_DEN
                         GPIO_PIN_A1 |  // VO_LCDC_VSYNC
                         GPIO_PIN_A2 |  // VO_LCDC_HSYNC
                         GPIO_PIN_A3 |  // VO_LCDC_CLK
                         GPIO_PIN_D3 |  // VO_LCDC_D0
                         GPIO_PIN_D2 |  // VO_LCDC_D1
                         GPIO_PIN_D1 |  // VO_LCDC_D2
                         GPIO_PIN_D0 |  // VO_LCDC_D3
                         GPIO_PIN_C7 |  // VO_LCDC_D4
                         GPIO_PIN_C6 |  // VO_LCDC_D5
                         GPIO_PIN_C5 |  // VO_LCDC_D6
                         GPIO_PIN_C4 |  // VO_LCDC_D7
                         GPIO_PIN_C3 |  // VO_LCDC_D8
                         GPIO_PIN_C2 |  // VO_LCDC_D9
                         GPIO_PIN_C1 |  // VO_LCDC_D10
                         GPIO_PIN_C0 |  // VO_LCDC_D11
                         GPIO_PIN_B7 |  // VO_LCDC_D12
                         GPIO_PIN_B6 |  // VO_LCDC_D13
                         GPIO_PIN_B5 |  // VO_LCDC_D14
                         GPIO_PIN_B4 |  // VO_LCDC_D15
                         GPIO_PIN_B3 |  // VO_LCDC_D16
                         GPIO_PIN_B2 |  // VO_LCDC_D17
                         GPIO_PIN_B1 |  // VO_LCDC_D18
                         GPIO_PIN_B0 |  // VO_LCDC_D19
                         GPIO_PIN_A7 |  // VO_LCDC_D20
                         GPIO_PIN_A6 |  // VO_LCDC_D21
                         GPIO_PIN_A5 |  // VO_LCDC_D22
                         GPIO_PIN_A4,   // VO_LCDC_D23
                         PIN_CONFIG_MUX_FUNC1);

    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_A1 |  // power en
                         GPIO_PIN_A7,   // reset
                         PIN_CONFIG_MUX_FUNC0);
}

/**
 * @brief  Config iomux for PWM0
 */
RT_WEAK void pwm0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_A3,
                        RMIO_PWM0_CH2);
}

/**
 * @brief  Config iomux for DSM0
 */
RT_WEAK void dsm0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK1,
                         GPIO_PIN_D0 |  // ln
                         GPIO_PIN_D1 |  // lp
                         GPIO_PIN_C1 |  // rn
                         GPIO_PIN_C2,   // rp
                         PIN_CONFIG_MUX_FUNC4);
}

/**
 * @brief  Config iomux for PDM0
 */
RT_WEAK void pdm0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B3,
                        RMIO_PDMCLK0);
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_A7,
                        RMIO_PDMCLK1);
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B4,
                        RMIO_PDM_SDI0);
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B5,
                        RMIO_PDM_SDI1);
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B6,
                        RMIO_PDM_SDI2);
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_B6,
                        RMIO_PDM_SDI3);
}

/**
 * @brief  Config iomux for SAI0
 */
RT_WEAK void sai0_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_A0 |  // lrck
                         GPIO_PIN_A1 |  // sclk
                         GPIO_PIN_A3 |  // sdo0
                         GPIO_PIN_A4 |  // sdi0
                         GPIO_PIN_A5 |  // sdi1
                         GPIO_PIN_A6 |  // sdi2
                         GPIO_PIN_A7,   // sdi3
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for SAI1
 */
RT_WEAK void sai1_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK0,
                         GPIO_PIN_B1 |  // sclk
                         GPIO_PIN_B2 |  // lrck
                         GPIO_PIN_B3 |  // sdi0
                         GPIO_PIN_B4 |  // sdo0
                         GPIO_PIN_B5 |  // sdo1
                         GPIO_PIN_B6 |  // sdo2
                         GPIO_PIN_B7,   // sdo3
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for SAI2
 */
RT_WEAK void sai2_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK3,
                         GPIO_PIN_A7 |  // sclk
                         GPIO_PIN_B1 |  // lrck
                         GPIO_PIN_A6 |  // sdi0
                         GPIO_PIN_B0,   // sdo0
                         PIN_CONFIG_MUX_FUNC1);
}

/**
 * @brief  Config iomux for SAI3
 */
RT_WEAK void sai3_iomux_config(void)
{
    HAL_PINCTRL_SetIOMUX(GPIO_BANK2,
                         GPIO_PIN_B4 |  // sclk
                         GPIO_PIN_B5 |  // lrck
                         GPIO_PIN_B6 |  // sdi0
                         GPIO_PIN_B7,   // sdo0
                         PIN_CONFIG_MUX_FUNC3);
}

/**
 * @brief  Config iomux for SPDIFRX0
 */
RT_WEAK void spdifrx0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_C0,
                        RMIO_SPDIF_RX);
}

/**
 * @brief  Config iomux for SPDIFTX0
 */
RT_WEAK void spdiftx0_iomux_config(void)
{
    HAL_PINCTRL_SetRMIO(GPIO_BANK0,
                        GPIO_PIN_C1,
                        RMIO_SPDIF_TX);
}

/**
 * @brief  Config iomux for RK3506
 */
RT_WEAK void rt_hw_iomux_config(void)
{
#if defined(RT_USING_UART0)
    uart0_iomux_config();
#endif

#if defined(RT_USING_UART3)
    uart3_iomux_config();
#endif

#if defined(RT_USING_UART4)
    uart4_iomux_config();
#endif

#if defined(RT_USING_UART5)
    uart5_iomux_config();
#endif

#ifdef RT_USING_GMAC0
    rmii0_iomux_config();
#endif

#ifdef RT_USING_GMAC1
    rmii1_iomux_config();
#endif

#ifdef RT_USING_CAN0
    can0_iomux_config();
#endif

#ifdef RT_USING_ACDCDIG_DSM0
    dsm0_iomux_config();
#endif

#ifdef RT_USING_PDM0
    pdm0_iomux_config();
#endif

#ifdef RT_USING_SAI0
    sai0_iomux_config();
#endif

#ifdef RT_USING_SAI1
    sai1_iomux_config();
#endif

#ifdef RT_USING_SAI2
    sai2_iomux_config();
#endif

#ifdef RT_USING_SAI3
    sai3_iomux_config();
#endif

#ifdef RT_USING_SPDIFRX0
    spdifrx0_iomux_config();
#endif

#ifdef RT_USING_SPDIFTX0
    spdiftx0_iomux_config();
#endif

}
#endif
