#include <cstring>

#include "pc_recoder.hpp"
#include "quit.hpp"

#include "../help_strings.hpp"

int main(int argc, char** argv)
{
    char local_ip_1[16];
    char local_port_1[6];
    char remote_ip_1[16];
    char remote_port_1[6];

    char local_ip_2[16];
    char local_port_2[6];
    char remote_ip_2[16];
    char remote_port_2[6];

    if (argc != 11)
    {
        std::cout << strrchr(argv[0], '/')+1 << " [kodo redundancy factor 1] [local ip 1] [remote ip 1] [local port 1] [remote port 1] [kodo redundancy factor 2] [local ip 2] [remote ip 2] [local port 2] [remote port 2]" << std::endl;

        std::cout << std::endl
                  << "The recoder has two sets of options, one for each node it is connected to" << std::endl
                  << "[kodo redundancy factor]    " KODO_REDUNDANCY_FACTOR_HELP_STRING << std::endl
                  << "[local ip]                  " LOCAL_IP_HELP_STRING << std::endl
                  << "[remote ip]                 " REMOTE_IP_HELP_STRING << std::endl
                  << "[local port]                " LOCAL_PORT_HELP_STRING << std::endl
                  << "[remote port]               " REMOTE_PORT_HELP_STRING << std::endl
                  << std::endl;

        return 1;
    }

    strncpy(local_ip_1, argv[2], 16);
    strncpy(remote_ip_1, argv[3], 16);
    strncpy(local_port_1, argv[4], 6);
    strncpy(remote_port_1, argv[5], 6);
    strncpy(local_ip_2, argv[7], 16);
    strncpy(remote_ip_2, argv[8], 16);
    strncpy(local_port_2, argv[9], 6);
    strncpy(remote_port_2, argv[10], 6);

    recoder r(local_ip_1, local_port_1, remote_ip_1, remote_port_1,
              local_ip_2, local_port_2, remote_ip_2, remote_port_2);

    // redundancy is applied on the receiving udp stack ->
    //  redundancy for link 2 is applied on the link 1 receiving stack.
    double redundancy2 = atoi(argv[1])/100.0;
    double redundancy1 = atoi(argv[6])/100.0;
    r.udp1->parse({ {"kodo::tx_redundancy", redundancy1} });
    r.udp2->parse({ {"kodo::tx_redundancy", redundancy2} });

    wait_for_quit();

    return 0;
}
