#include "base_headers.hpp"

#if not defined(_NETWORKING_HEADERS_)
    #define _NETWORKING_HEADERS_
    #if defined(crap_os)

        #if not defined(crap_os)
            #define crap_os
        #endif

        #if not defined(_INC_CONIO)
            #include <conio.h>
        #endif

        #if not defined(_WIN32_WINNT)
            #define <winsock2.h>
        #endif

        #if not defined(__IPHLPAPI_H__)
            #include <iphlpapi.h>
        #endif

        #if not defined(_WINDOWS_)
            #include <Windows.h>
        #endif

        #pragma comment(lib, "ws2_32.lib")
        #pragma comment(lib, "iphlpapi.lib")


        #define get_string(crap_string)\
            [&]() -> std::string {\
                const wchar_t* crap_str = crap_string;\
                std::string the_answer;\
                while(*crap_str) {\
                    the_answer.push_back(static_cast<char>(*crap_str));\
                }\
                return the_answer;\
            }()


        // For dealing with adapters
        #define ifaddrs_adapter_type PIP_ADAPTER_ADDRESSES
        #define ifaddrs_get_adapter_name(this_adapter) get_string(this_adapter->FriendlyName)
        #define ifaddrs_get_next_adapter(this_adapter) this_address->Next
        #define ifaddrs_pull_adapter_address(this_adapter) this_adapter->FirstUnicastAddress
        #define ifaddrs_free_adapters(these_adapters) std::free(these_adapters)


        // For dealing with addresses
        #define ifaddrs_address_type PIP_ADAPTER_UNICAST_ADDRESS
        #define ifaddrs_get_next_address(this_address) this_address->Next
        #define ifaddrs_get_address_sockaddr(this_address) this_address->Address.lpSockaddr
        #define ifaddrs_get_address_sockaddrlen(this_address) this_address->Address.iSockaddrLength
        #define ifaddrs_get_address_family(this_address) this_address->Address.lpSockaddr->sa_family



        // For dealing with sockets
        #define socket_error WSAGetLastError()
        #define socket_type SOCKET
        #define socket_family_type int
        #define invalid_socket INVALID_SOCKET
        #define valid_socket(this_socket) this_socket != INVALID_SOCKET
        #define close_socket(this_socket) closesocket(this_socket)
        #define sys_slash "\\"


    #else


        #if (defined(mac_os) and not defined(_SYS_IOCTL_H_)) or (defined(linux_os) and not defined(_SYS_IOCTL_H))
            #include <sys/ioctl.h>
        #endif

        #if (defined(mac_os) and not defined(_UNISTD_H_)) or (defined(linux_os) and not defined(_UNISTD_H))
            #include <unistd.h>
        #endif

        #if (defined(mac_os) and not defined(_IFADDRS_H_)) or (defined(linux_os) and not defined(_IFADDRS_H))
            #include <ifaddrs.h>
        #endif

        #if (defined(mac_os) and not defined(_SYS_SOCKET_H_)) or (defined(linux_os) and not defined(_SYS_SOCKET_H))
            #include <sys/socket.h>
        #endif

        #if (defined(mac_os) and not defined(_NETDB_H_)) or (defined(linux_os) and not defined(_NETDB_H))
            #include <netdb.h>
        #endif

        #if (defined(mac_os) and not defined(_LIBCPP_ERRNO_H)) or (defined(linux_os) and not defined(_ERRNO_H))
            #include <errno.h>
        #endif

        #if (defined(mac_os) and not defined(_ARPA_INET_H_)) or (defined(linux_os) and not defined(_ARPA_INET_H))
            #include <arpa/inet.h>
        #endif


        // For dealing with adapters
        #define ifaddrs_adapter_type struct ifaddrs*
        #define ifaddrs_get_adapter_name(this_adapter) std::string(this_adapter->ifa_name)
        #define ifaddrs_get_next_adapter(this_adapter) this_adapter->ifa_next
        #define ifaddrs_pull_adapter_address(this_adapter) this_adapter
        #define ifaddrs_free_adapters(these_adapters) freeifaddrs(these_adapters)
        
        
        // For dealing with addresses
        #define ifaddrs_address_type struct ifaddrs*
        #define ifaddrs_get_next_address(this_address) NULL
        #define ifaddrs_get_address_sockaddr(this_address) this_address->ifa_addr
        #define ifaddrs_get_address_sockaddrlen(this_address) sizeof(*this_address->ifa_addr)
        #define ifaddrs_get_address_family(this_address) this_address->ifa_addr->sa_family
        
        
        // For dealing with sockets
        #define socket_error errno
        #define socket_type int
        #if defined(mac_os)
            #define socket_family_type unsigned char
        #else
            #define socket_family_type unsigned short
        #endif
        #define invalid_socket -1
        #define valid_socket(this_socket) (this_socket >= 0)
        #define close_socket(this_socket) close(this_socket)
        #define sys_slash "/"

    #endif

    #define buffer_size 100
    #define kilo_byte 1024
    #define four_kilo_bytes 4096
    #define eight_kilo_bytes 8192



    #if not defined(AI_ALL)
        #define AI_ALL 0x0100
    #endif


    #define response_size 32768
    #define byte char

    #define DEFAULT_PORT "8080"

#endif


