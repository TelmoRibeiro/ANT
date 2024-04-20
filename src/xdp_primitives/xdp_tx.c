#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/in.h>

/* @ telmo -
    TESTED:
    NOT TESTED:
        - Generic Mode
        - Native
        - Offloaded
    
    IDEA:
*/

// @ telmo - missing