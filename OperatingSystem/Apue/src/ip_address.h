#pragma once

#include "include/apue.h"
#include "include/inc.h"
#include <ifaddrs.h>    //  getifaddrs
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_ntop
#include <sys/socket.h>

NS_BEGIN(elloop);

class IpAddress {
public:

    static int run(int argc, char** argv) {
        ipTest();
        return 0;
    }

    static void ipTest() {

        auto sinAddr2Ipv4 = [] (struct in_addr inAddr) -> char* {
            char* cp = new char[INET_ADDRSTRLEN];
            // psln(INET_ADDRSTRLEN);
            char srcStr[INET_ADDRSTRLEN];
            memcpy(srcStr, &inAddr, sizeof(struct in_addr));
            ERR_IF(inet_ntop(AF_INET, srcStr, cp, INET_ADDRSTRLEN) == NULL, err_ret, "fail to ntop");
            return cp;
        };

        auto sinAddr2Ipv6 = [] (struct in6_addr inAddr) -> char* {
            char* cp = new char[INET6_ADDRSTRLEN];
            // psln(INET6_ADDRSTRLEN);
            char srcStr[INET6_ADDRSTRLEN];
            memcpy(srcStr, &inAddr, sizeof(struct in6_addr));
            ERR_IF(inet_ntop(AF_INET6, srcStr, cp, INET6_ADDRSTRLEN) == NULL, err_ret, "fail to ntop");
            return cp;
        };

        struct ifaddrs* interfaces(NULL);
        ERR_IF(getifaddrs(&interfaces) != 0, err_sys, "fail to getifaddrs");
        auto interface = interfaces;
        pv("%-15s%-15s%-18s\n", "ifa_name", "sa_family", "ip");
        pv("======================================\n");
        while (interface) {
            pv("%-15s", interface->ifa_name);
            pv("%-15s", interface->ifa_addr->sa_family == AF_INET ? "AF_INET" :
                    interface->ifa_addr->sa_family == AF_INET6 ? "AF_INET6" :
                    interface->ifa_addr->sa_family == AF_LINK ? "AF_LINK" : "Unknown");

            if (interface->ifa_addr->sa_family == AF_INET){
                // pln("find ipv4");
                struct in_addr inAddr = ((struct sockaddr_in*)interface->ifa_addr)->sin_addr;
                char* p = sinAddr2Ipv4(inAddr);
                pv("%-18s", p);
                // pv("sin_addr 2 ipv4: %s\n", p);
                delete [] p;
                // pv("sin_addr: %s\n", ((struct sockaddr_in *)interface->ifa_addr)->sin_addr);
            }

            //如果是IPV6地址
            else if (interface->ifa_addr->sa_family == AF_INET6){
                // pln("find ipv6");
                auto inAddr = ((struct sockaddr_in6*)interface->ifa_addr)->sin6_addr;
                auto p = sinAddr2Ipv6(inAddr);
                pv("%-8s", p);
                // pv("sin_addr 2 ipv6: %s\n", p);
                delete [] p;
                // pv("sin_addr: %s\n", ((struct sockaddr_in6 *)interface->ifa_addr)->sin6_addr);
            }
            cr;
            interface = interface->ifa_next;
        }
        freeifaddrs(interfaces);
    }

};

NS_END(elloop);

