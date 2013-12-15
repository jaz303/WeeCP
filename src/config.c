#include "weecp/weecp.h"

#include <string.h>

static wcp_iface_t *iface_head = 0;
static wcp_iface_t *iface_tail = 0;

void wcp_iface_init(wcp_iface_t *iface, const char *name) {

    size_t ix = 0;
    while (ix < (WCP_IFACE_NAME_LEN-1) && name[ix]) {
        iface->name[ix] = name[ix];
        ix++;
    }
    iface->name[ix] = 0;

    iface->hwaddr = 0x00;
    iface->ipaddr = 0x00;

}

wcp_iface_t* wcp_iface_register(wcp_iface_t *iface) {
    if (iface_head == 0) {
        iface_head = iface_tail = iface;
    } else {
        iface_tail->next = iface;
        iface_tail = iface;
    }
    iface->next = 0;
}

void wcp_iface_set_hw_addr(wcp_iface_t *iface, uint8_t *hwaddr) {

}

void wcp_iface_set_ipv4_addr(wcp_iface_t *iface, uint32_t ipaddr) {
    iface->ipaddr = ipaddr;
}
