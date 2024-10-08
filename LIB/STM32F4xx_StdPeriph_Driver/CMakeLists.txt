set(sources
    src/misc.c
    src/stm32f4xx_adc.c
    src/stm32f4xx_can.c
    src/stm32f4xx_cec.c
    src/stm32f4xx_crc.c
    src/stm32f4xx_cryp.c
    src/stm32f4xx_cryp_aes.c
    src/stm32f4xx_cryp_des.c
    src/stm32f4xx_cryp_tdes.c
    src/stm32f4xx_dac.c
    src/stm32f4xx_dbgmcu.c
    src/stm32f4xx_dcmi.c
    src/stm32f4xx_dma.c
    src/stm32f4xx_dma2d.c
    src/stm32f4xx_dsi.c
    src/stm32f4xx_exti.c
    src/stm32f4xx_flash.c
    src/stm32f4xx_flash_ramfunc.c
    src/stm32f4xx_fmpi2c.c
    src/stm32f4xx_gpio.c
    src/stm32f4xx_hash.c
    src/stm32f4xx_hash_md5.c
    src/stm32f4xx_hash_sha1.c
    src/stm32f4xx_i2c.c
    src/stm32f4xx_iwdg.c
    src/stm32f4xx_lptim.c
    src/stm32f4xx_ltdc.c
    src/stm32f4xx_pwr.c
    src/stm32f4xx_qspi.c
    src/stm32f4xx_rcc.c
    src/stm32f4xx_rng.c
    src/stm32f4xx_rtc.c
    src/stm32f4xx_sai.c
    src/stm32f4xx_sdio.c
    src/stm32f4xx_spdifrx.c
    src/stm32f4xx_spi.c
    src/stm32f4xx_syscfg.c
    src/stm32f4xx_tim.c
    src/stm32f4xx_usart.c
    src/stm32f4xx_wwdg.c
)

add_library(stm32f4xx ${sources})

# add include directories for StdPeriph library and CMSIS
target_include_directories(stm32f4xx PUBLIC inc)
target_include_directories(stm32f4xx PUBLIC ../CMSIS/include)
target_include_directories(stm32f4xx PUBLIC ../Device/STM32F4xx/Include)

target_compile_definitions(stm32f4xx PUBLIC HSE_VALUE=${HSE_VALUE})

# additional compiler options: use size-optimized version of library in release build, use -O0 in debug build
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(additional_flags -O0)
else()
  set(additional_flags -Os)
endif()

target_compile_options(stm32f4xx PRIVATE ${additional_flags})