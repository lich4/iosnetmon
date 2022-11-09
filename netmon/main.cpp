#include <dlfcn.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

int (*_system)(const char* cmd) = 0;

template<typename F>
static int enum_net_if(const F& lambda) {
    int ret = -1;
    ifaddrs* interfaces = 0;
    ifaddrs* temp_addr = 0;
    if (0 == getifaddrs(&interfaces)) {
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if (temp_addr->ifa_addr != 0) {
                lambda(temp_addr->ifa_name, temp_addr->ifa_addr->sa_family, temp_addr);
            }
            temp_addr = temp_addr->ifa_next;
        }
        freeifaddrs(interfaces);
    }
    return ret;
}

static std::string int_to_unit(uint64_t v) {
    std::stringstream stream;
    if (v < 1024) {
        return std::to_string(v) + "B";
    } else if (v < 1024 * 1024) {
        double vv = (double)v / (1024);
        stream << std::fixed << std::setprecision(2) << vv;
        return stream.str() + "KB";
    } else if (v < 1024 * 1024 * 1024) {
        double vv = (double)v / (1024 * 1024);
        stream << std::fixed << std::setprecision(2) << vv;
        return stream.str() + "MB";
    } else {
        double vv = (double)v / (1024 * 1024 * 1024);
        stream << std::fixed << std::setprecision(2) << vv;
        return stream.str() + "GB";
    }
}

struct in_out_byte {
    uint32_t ibyte;
    uint32_t obyte;
};

static std::unordered_map<std::string, in_out_byte> last_data;

static void print_netif_info() {
    std::cout <<
        std::setw(8) << "ifname" << std::setw(8) <<  "mtu" << std::setw(12) << "baudrate" <<
        std::setw(12) << "ipackets" << std::setw(12) << "opackets" <<
        std::setw(12) << "ibytes" << std::setw(12) << "obytes" <<
        std::setw(12) << "imcasts" << std::setw(12) << "omcasts" <<
        std::setw(12) << "ierrors" << std::setw(12) << "oerrors" <<
        std::setw(12) << "collisions" << std::setw(12) << "iqdrops" <<
        std::setw(12) << "in(?B/s)" << std::setw(12) << "out(?B/s)" <<
    std::endl;
    enum_net_if([](const char* ifname, int family, ifaddrs* addr) {
        if (family != AF_LINK || !addr->ifa_data) {
            return;
        }
        if_data* d = (if_data*)addr->ifa_data;
        if (last_data.find(ifname) == last_data.end()) {
            last_data[ifname] = {d->ifi_ibytes, d->ifi_obytes};
        }
        std::cout <<
            std::setw(8) << ifname << std::setw(8) << d->ifi_mtu << std::setw(12) << d->ifi_baudrate <<
            std::setw(12) << d->ifi_ipackets << std::setw(12) << d->ifi_opackets <<
            std::setw(12) << int_to_unit(d->ifi_ibytes) << std::setw(12) << int_to_unit(d->ifi_obytes) <<
            std::setw(12) << d->ifi_imcasts << std::setw(12) << d->ifi_omcasts <<
            std::setw(12) << d->ifi_ierrors << std::setw(12) << d->ifi_oerrors <<
            std::setw(12) << d->ifi_collisions << std::setw(12) << d->ifi_iqdrops <<
            std::setw(12) << int_to_unit(d->ifi_ibytes - last_data[ifname].ibyte) << std::setw(12) << int_to_unit(d->ifi_obytes - last_data[ifname].obyte) <<
        std::endl;
        last_data[ifname] = {d->ifi_ibytes, d->ifi_obytes};
    });
}

int main (int argc, const char * argv[]) {
    _system = (__typeof(_system))dlsym(RTLD_DEFAULT, "system");
    for (int i = 0; i < 1000; i++) {
        _system("clear");
        print_netif_info();
        sleep(1);
    }
	return 0;
}

