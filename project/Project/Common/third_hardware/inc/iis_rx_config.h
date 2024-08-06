#ifndef IIS_RX_CONFIG_H_
#define IIS_RX_CONFIG_H_

void iis_rx_open(void);
void iis_rx_start(void);
void iis_rx_stop(void);
void iis_tx_close(void);

uint32_t iis_rx_get_sclk_freq(void);
uint32_t iis_rx_dma_pointer(void);

#endif

