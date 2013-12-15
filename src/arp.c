#include "weecp/weecp.h"

#define ARP_TABLE_SIZE      32
#define ARP_ENTRY_SET       0x01

#define ARP_HTYPE_ETH       0x0001
#define ARP_PTYPE_IPV4      0x0800
#define ARP_HLEN            6
#define ARP_PLEN            4

#define ARP_REQUEST         0x0001
#define ARP_REPLY           0x0002

struct arp_entry {
    uint8_t         flags;
    uint32_t        paddr;
    wcp_eth_addr_t  haddr;
};

struct arp_entry arp_table[ARP_TABLE_SIZE];

struct __attribute__ ((__packed__)) arp_msg {
    uint16_t        htype;
    uint16_t        ptype;
    uint8_t         hlen;
    uint8_t         plen;
    uint16_t        oper;
    wcp_eth_addr_t  sha;
    uint32_t        spa;
    wcp_eth_addr_t  tha;
    uint32_t        tpa;
};

void arp_init() {
    memset(arp_table, 0, sizeof(struct arp_entry) * ARP_TABLE_SIZE);
}

int arp_lookup(uint32_t ipaddr, wcp_arp_result_t *result); {

    for (int = 0; i < ARP_TABLE_SIZE; ++i) {
        if (*arp_table[i].flags && ARP_TABLE_SET) && arp_table[i].paddr == ipaddr) {
            WCP_COPY_ETH_ADDR(&result->hwaddr, &arp_table[i].haddr);
            // TODO: fill in interface
            return 1;
        }
    }

    return 0;

}

static void foo(struct arp_msg *msg, wcp_iface_t *iface, uint32_t lookupaddr) {
    
    msg->htype = ARP_HTYPE_ETH;
    msg->ptype = ARP_PTYPE_IPV4;
    msg->hlen = ARP_HLEN;
    msg->plen = ARP_PLEN;
    msg->oper = ARP_REQUEST;

    WC_COPY_ETH_ADDR(&msg->sha, &iface->hwaddr);
    msg->spa = iface->ipaddr;

    // msg->tha ignored for requests
    msg->tpa = lookupaddr;

}

static handle_reply(struct arp_msg *msg) {

    int victim_ix = -1, empty_ix = -1;

    for (int i = 0; i < ARP_TABLE_SIZE; ++i) {
        if (arp_table[i].flags & ARP_ENTRY_SET) {
            if (arp_table[i].paddr == msg->tpa) {
                WCP_COPY_ETH_ADDR(&arp_table[i].haddr, &msg->tha);
                return;
            }
        } else if (empty_ix == -1) {
            empty_ix = i;
        }
    }

    int update_ix = (empty_ix < 0) ? victim_ix : empty_ix;

    arp_table[update_ix].paddr = msg->tpa;
    WCP_COPY_ETH_ADDR(&arp_table[update_ix].haddr, &msg->tha);

}