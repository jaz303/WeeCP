#ifndef WEECP_H
#define WEECP_H

/*
 * Ethernet address
 */

typedef struct wcp_eth_addr {
    uint8_t octet[6];
} wcp_eth_addr_t;

#define WCP_COPY_ETH_ADDR(dest, src) \
    WCP_SET_ETH_ADDR6(dest, src.octet[0], src.octet[1], src.octet[2], src.octet[3], src.octet[4], src.octet[5])

#define WCP_ETH_ADDR_CMP(addr1, addr2) \
    0
    
#define WCP_SET_ETH_ADDR3(addr, n1, n2, n3) \
    WCP_SET_ETH_ADDR6(addr, n1 >> 8, n1, n2 >> 8, n2, n3 >> 8, n3)

#define WCP_SET_ETH_ADDR6(addr, o1, o2, o3, o4, o5, o6) \
    (addr).octet[0] = (o1); \
    (addr).octet[1] = (o2); \
    (addr).octet[2] = (o3); \
    (addr).octet[3] = (o4); \
    (addr).octet[4] = (o5); \
    (addr).octet[5] = (o6)

/*
 * Interface
 */

#define WCP_IFACE_NAME_LEN 8

typedef struct wcp_iface wcp_iface_t;

struct wcp_iface {
    char            name[WCP_IFACE_NAME_LEN];
    wcp_eth_addr_t  hwaddr;
    uint32_t        ipaddr;
    wcp_iface_t     *next;
};

/*
 * ARP Result
 */

typedef struct wcp_arp_result {
    wcp_eth_addr_t      hwaddr;
    wcp_iface_t         *iface;
} wcp_arp_result_t;

/*
 * API
 */

/* Initialise ARP subsystem */
void arp_init();

/* ARP cache lookup */
int arp_lookup(uint32_t ipaddr, wcp_arp_result_t *result);

#endif