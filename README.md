# iosnetmon

Net traffic monitor for iOS (Need Jailbreak)

```txt
  ifname     mtu    baudrate    ipackets    opackets      ibytes      obytes     imcasts     omcasts     ierrors     oerrors  collisions     iqdrops    in(?B/s)   out(?B/s)
     lo0   16384           0     6347175     6347175      2.26GB      2.26GB         785           0           0           0           0           0      3.12KB      3.12KB
    EHC4       0           0           0           0          0B          0B           0           0           0           0           0           0          0B          0B
 pdp_ip0    1500    52428800           0           0          0B          0B           0           0           0           0           0           0          0B          0B
 pdp_ip1    1500    52428800           0           0          0B          0B           0           0           0           0           0           0          0B          0B
 pdp_ip2    1500    52428800           0           0          0B          0B           0           0           0           0           0           0          0B          0B
 pdp_ip3    1500    52428800           0           0          0B          0B           0           0           0           0           0           0          0B          0B
 pdp_ip4    1500    52428800           0           0          0B          0B           0           0           0           0           0           0          0B          0B
     ap1    1500    10000000           0           0          0B          0B           0           0           0           0           0           0          0B          0B
     en0    1500   273780000     2661187     2298721    725.11MB    559.44MB     2258406           0           0          73           0           0        120B          0B
   awdl0    1484    10000000           0          22          0B      2.77KB           0           0           0           0           0           0          0B          0B
     en1    1500           0           0           0          0B          0B           0           0           0           0           0           0          0B          0B
     en2    1500   100000000      322135       34826     74.80MB     14.80MB      322130           0           0       10986           0           0          0B          0B
   utun0    2000           0           0           2          0B        240B           0           0           0           0           0           0          0B          0B
```

## field

```c
struct if_data {
	/* generic interface information */
	u_char          ifi_type;       /* ethernet, tokenring, etc */
	u_char          ifi_typelen;    /* Length of frame type id */
	u_char          ifi_physical;   /* e.g., AUI, Thinnet, 10base-T, etc */
	u_char          ifi_addrlen;    /* media address length */
	u_char          ifi_hdrlen;     /* media header length */
	u_char          ifi_recvquota;  /* polling quota for receive intrs */
	u_char          ifi_xmitquota;  /* polling quota for xmit intrs */
	u_char          ifi_unused1;    /* for future use */
	u_int32_t       ifi_mtu;        /* maximum transmission unit */
	u_int32_t       ifi_metric;     /* routing metric (external only) */
	u_int32_t       ifi_baudrate;   /* linespeed */
	/* volatile statistics */
	u_int32_t       ifi_ipackets;   /* packets received on interface */
	u_int32_t       ifi_ierrors;    /* input errors on interface */
	u_int32_t       ifi_opackets;   /* packets sent on interface */
	u_int32_t       ifi_oerrors;    /* output errors on interface */
	u_int32_t       ifi_collisions; /* collisions on csma interfaces */
	u_int32_t       ifi_ibytes;     /* total number of octets received */
	u_int32_t       ifi_obytes;     /* total number of octets sent */
	u_int32_t       ifi_imcasts;    /* packets received via multicast */
	u_int32_t       ifi_omcasts;    /* packets sent via multicast */
	u_int32_t       ifi_iqdrops;    /* dropped on input, this interface */
	u_int32_t       ifi_noproto;    /* destined for unsupported protocol */
	u_int32_t       ifi_recvtiming; /* usec spent receiving when timing */
	u_int32_t       ifi_xmittiming; /* usec spent xmitting when timing */
	struct IF_DATA_TIMEVAL ifi_lastchange;  /* time of last administrative change */
	u_int32_t       ifi_unused2;    /* used to be the default_proto */
	u_int32_t       ifi_hwassist;   /* HW offload capabilities */
	u_int32_t       ifi_reserved1;  /* for future use */
	u_int32_t       ifi_reserved2;  /* for future use */
};
```


