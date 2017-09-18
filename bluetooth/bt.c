#include "bluetooth.h"

#include <libopencm3/stm32/iwdg.h>

#include <btstack_chipset_cc256x.h>
#include <btstack_memory.h>
#include <btstack_run_loop_embedded.h>
#include <hci.h>

static const hci_transport_config_uart_t config = {
    .type = HCI_TRANSPORT_CONFIG_UART,
    .baudrate_init = 115200,
    .baudrate_main = 460800,
    .flowcontrol = 1,
    .device_name = NULL,
};

void bluetooth_setup(void) {
    iwdg_reset();

    btstack_memory_init();
    btstack_run_loop_init(btstack_run_loop_embedded_get_instance());

    hci_init(hci_transport_h4_instance(btstack_uart_block_embedded_instance()), &config);
    hci_set_link_key_db(btstack_link_key_db_memory_instance());
    hci_set_chipset(btstack_chipset_cc256x_instance());

    gap_discoverable_control(1);

    hci_power_control(HCI_POWER_ON);
}

void bluetooth_poll(void) {
    btstack_run_loop_embedded_execute_once();
}
