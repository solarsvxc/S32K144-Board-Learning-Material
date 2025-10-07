#include "S32K144.h"
#include "driver_include/driver_nvic.h"
#include "driver_include/driver_clock.h"
#include "driver_include/driver_gpio.h"
#include "driver_include/driver_port.h"

#define RX_PTC6 6
#define TX_PTC7 7

static ARM_DRIVER_GPIO *GPIOdrv = &Driver_GPIO0;

void init_UART(void)
{
    IP_PCC->PCCn[PCC_LPUART1_INDEX] &=~PCC_PCCn_CGC_MASK;
    
    /* Clock source SOSCDIV2_CLK 8Mhz = XTAL external oscilli */
    /* Enable Clock Gating */
    IP_PCC->PCCn[PCC_LPUART1_INDEX] = PCC_PCCn_PCS(0b1) | PCC_PCCn_CGC_MASK ;
    
    /** OSR = 15 ===> SBR almost equal to 52
     *  SBNS = 0b - One stop bit.
     *  RXEDGIE = 0b - Hardware interrupts from STAT[RXEDGIF] are disabled.
     *  LBKDIE  = 0b - Hardware interrupts from STAT[LBKDIF] flag are disabled (use polling).
     *  RESYNCDIS = 0b - Resynchronization during received data word is supported
     *  BOTHEDGE = 0b - Receiver samples input data using the rising edge of the baud rate clock
     *  MATCFG = 00b - Address Match Wakeup.
     *  RIDMAE = 0b - DMA request disabled.
     *  RDMAE = 0b - DMA request disabled.
     *  TDMAE = 0b - DMA request disabled.
     *  M10 = 0b - Receiver and transmitter use 7-bit to 9-bit data characters
     *  MAEN2 = 0b, MAEN1 = 0b - Normal operation.
     *  Baudrate 9600 
     * */
    IP_LPUART1->BAUD     =  LPUART_BAUD_SBR(0x34) | LPUART_BAUD_OSR(15); ;

    /** 
     * No parity bit, 8-bit data and 1 stop bit
     * Transmit enable and Receiver enable
     * PT = 0b - Even parity.
     * PE = 0b - No hardware parity generation or checking.
     * ILT = 0b - Idle character bit count starts after start bit.
     * WAKE = 0b - Configures RWU for idle-line wakeup.
     * M  = 0b - Receiver and transmitter use 8-bit data characters.
     * RSRC = 0b - Provided LOOPS is set, RSRC is cleared, selects internal loop back mode and the LPUART 
     *             does not use the RXD pin.
     * DOZEEN  = 0b - LPUART is enabled in Doze mode.
     * LOOPS  = 0b - Normal operation - RXD and TXD use separate pins.
     * IDLECFG = 000b - 1 idle character.
     * M7 = 0b - Receiver and transmitter use 8-bit to 10-bit data characters
     * MA2IE, MA1IE = 0b - MA2F interrupt disabled.
     * SBK = 0b - Normal transmitter operation.
     * RWU = 0b - Normal receiver operation.
     * RE = 1b - Receiver enabled.
     * TE = 1b - Transmitter enabled.
     * ILIE = 0b - Hardware interrupts from IDLE disabled; use polling.
     * RIE = 0b - Hardware interrupts from RDRF disabled; use polling.
     * TCIE = 0b - Hardware interrupts from TC disabled; use polling.
     * TIE = 0b - Hardware interrupts from TDRE disabled; use polling.
     * PEIE = 0b - PF interrupts disabled; use polling).
     * FEIE = 0b - FE interrupts disabled; use polling.
     * NEIE = 0b - NF interrupts disabled; use polling.
     * ORIE = 0b - OR interrupts disabled; use polling.
     * TXINV = 0b - Transmit data not inverted.
     * TXDIR = 0b - TXD pin is an input in single-wire mode
     * R9T8 : R9 is a read-only bit and T8 is a write-only bit, the value read is different from the value written */
    IP_LPUART1->CTRL    = LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK;
}

void send_char_LPUART1(char send )
{
    /* Waiting Data Register Empty */
	while(((IP_LPUART1->STAT & LPUART_STAT_TDRE_MASK) >> LPUART_STAT_TDRE_SHIFT) == 0);
    IP_LPUART1->DATA = send;
    // TDRE sẽ trả về 0 nếu data đang full, khi gửi xong thì TDRE sẽ trả về 1.
    // khi gửi xong nó sẽ dịch phải 23 tức là xóa bit 23 đó, ở lệnh tiếp theo điền data vào thanh ghi DATA thì nó lại trả về 0 
}

void send_string_LPUART1(char data_string[])
{
    uint32_t i = 0;

    while (data_string[i] != '\0' )
    {
        send_char_LPUART1(data_string[i]);
        i++;
    }
}

int main(void)
{
    init_SOSC_8MHz();
    init_SPLL_160Mhz();
    normal_SPLL_run_80MHz();
    init_UART();

    PCC_Enable(PCC_PORTC_INDEX);
    /* Alternative 2 is LPUART following IO signal table.xls */
    IP_PORTC->PCR[RX_PTC6] |= PORT_PCR_MUX(2);
    IP_PORTC->PCR[TX_PTC7] |= PORT_PCR_MUX(2);
    
    send_string_LPUART1("Hello Computer\n");
    
    while (1){
        send_char_LPUART1('p');
    }
}
