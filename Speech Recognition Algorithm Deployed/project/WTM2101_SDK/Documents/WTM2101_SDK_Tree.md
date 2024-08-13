WTM2101_SDK文件结构目录:
    WTM2101_SDK
    ├── Common                                       公用文件
    │   ├── Examples                                     模块示例
    │   ├── Libraries                                    库文件
    │   │   ├── Device                                       设备相关
    │   │   ├── HAL_Driver                                   HAL驱动库
    │   │   ├── NMSIS                                        微控制器软件接口标准库
    │   │   ├── WTM2101_Lib                                  WTM2101基础库
    │   │   ├── WTM2101_NPU_Lib                              NPU库
    │   │   ├── WTM2101_StdPeriph_Lib                        外设驱动库
    │   │   └── WTM2101_Ucontext                             协程库
    │   ├── Middlewares                                  软件中间件
    │   └── Templates                                    模板示例
    ├── Documents                                    说明文档
    ├── Solutions                                    应用解决方案
    │   ├── double_dmic_by_i2s_send                      双PDM MIC采集I2S输出至耳机
    │   ├── i2s_full_duplex                              I2S DMA全双工方案
    │   └── STM32F429_jtag                               GPIO模拟jtag方案
    └── Utilities                                    实用工具
        └── RTT                                          SEGGER RTT工具


模块示例文件结构目录:
    Examples                                     模块示例
    ├── afc_example                                  AFC示例
    │   ├── afc_external                                 AFC外部时钟校准示例
    │   └── afc_internal                                 AFC内部获取参数校准示例
    ├── audio_example                                AUDIO示例
    │   ├── audio                                        PDM MIC采集FIFO模式RTT数据输出示例
    │   ├── audio_fifo_dma                               PDM MIC采集FIFO模式I2S单声道数据输出示例
    │   ├── audio_fifo_dma_analog                        内部PDM 模拟MIC采集FIFO模式I2S数据输出示例
    │   ├── audio_fifo_dma_lr                            PDM MIC采集FIFO模式I2S左右声道数据输出示例
    │   ├── audio_ram_dma                                PDM MIC采集RAM模式I2S数据输出示例
    │   └── audio_uart                                   PDM MIC采集RAM模式UART数据输出示例
    ├── ctx_example                                  协程示例
    │   └── ctx                                          双线程切换示例
    ├── dma_example                                  DMA示例
    │   ├── dma_multi_block_auto_reload                  DMA 多块传输自动重加载示例
    │   ├── dma_multi_block_linked_list                  DMA 多块传输链表模式示例
    │   └── dma_single_block                             DMA 单块传输示例
    ├── fft_example                                  FFT示例
    │   └── fft                                          FFT功能示例
    ├── gpio_example                                 GPIO示例
    │   ├── gpio                                         GPIO输出
    │   ├── gpio_interrupt                               GPIO按键中断
    │   └── io_expand_pcf8574                            PCF8574模块进行双向IO（输入输出）扩展
    ├── hal_example                                  HAL库示例
    │   ├── hal_audio                                    HAL库AUDIO基本功能示例
    │   ├── hal_clock                                    HAL库CLOCK基本功能示例
    │   └── hal_i2s                                      HAL库I2S基本功能示例
    ├── i2c_example                                  I2C示例
    │   ├── i2c                                          SHT20 温湿度传感器接入
    │   ├── i2c_dma                                      EEPROM DMA方式数据收发
    │   ├── i2c_int                                      I2C中断示例
    │   └── i2c_slave_dma                                I2C主从收发
    ├── i2s_example                                  I2S示例
    │   ├── i2s                                          I2S master FIFO中断方式发送
    │   ├── i2s_int                                      I2S1主发送I2S0从接收（中断方式接收）
    │   └── i2s_int_dma                                  I2S1主发送(DMA方式发送)I2S0从接收（中断方式接收）
    ├── pmu_example                                  PMU示例
    │   ├── audio_vad_rsm2                               RSM2模式下的AUDIO VAD唤醒
    │   ├── gpio_rsm                                     RSM模式下的GPIO唤醒
    │   ├── gpio_sbm                                     SBM模式下的GPIO唤醒
    │   ├── rtc_rsm                                      RSM模式下RTC唤醒
    │   └── wdt_rsm                                      RSM模式下WDT唤醒
    ├── pwm_example                                  PWM示例
    │   └── pwm                                          PWM功能示例
    ├── qspi_example                                 QSPI示例
    │   ├── qspi_flash_dma                               使用 QSPI（1/2line）接口读写板载外部 flash(DMA 的方式)
    │   ├── qspi_flash_mem_mapped                        momery mapped 模式直接读取外部 flash 数据
    │   └── qspi_flash_w25q64jv                          使用QSPI 接口读写w25q64jv flash
    ├── rtc_example                                  RTC示例
    │   └── rtc                                          RTC定时示例
    ├── spi_example                                  SPI示例
    │   ├── spi_dma_send_receive                         SPI master使用DMA方式与SPI slave进行数据收发
    │   ├── spi_fifo_master_send_receive                 SPI master使用FIFO方式与SPI slave进行数据收发
    │   ├── spi_fifo_slave_send_receive                  SPI slave使用FIFO方式与SPI master进行数据收发
    │   ├── spi_flash                                    SPI master对x3板子上的Flash（ZD25wq）进行读写擦测试
    │   ├── spi_int_master_send_slave_receive            SPI master使用中断方式与SPI slave进行数据收发
    │   └── spi_lcd                                      SPI master驱动SPI LCD显示屏MSP2202进行显示功能
    ├── timer_example                                TIMER示例
    │   └── timer_case                                   TIMER定时示例
    ├── uart_example                                 UART示例
    │   ├── uart_dma                                     UART DMA方式数据收发
    │   ├── uart_fifo                                    UART FIFO方式数据收发
    │   ├── uart_int                                     UART 中断方式数据收发
    │   └── uart_polling                                 UART 轮询方式数据收发
    └── wdt_example                                  WDT示例
        └── wdt_case                                     WDT喂狗示例
