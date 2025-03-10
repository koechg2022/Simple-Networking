




#include "../headers/included"
#include "string_functions"
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include "networking"











namespace networking {

    static bool clean_on_except = true;

    namespace {

        #if defined(crap_os)
            bool is_init = false;
        #else
            const bool is_init = true;
        #endif

        bool is_init_secure = false;

        const std::string ip6_regex_pattern = std::string("^(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}") + 
            std::string("|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}") +
            std::string("|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}") +
            std::string("){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:)") + 
            std::string("{1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6}") + 
            std::string(")|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}") + 
            std::string("|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}") + 
            std::string("(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1") + 
            std::string("{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))$");
    }
    
    
    namespace network_address_families {

        #if defined(crap_os)
            const std::string rel_adapter = "Wi-Fi 3";
        #else
            
            #if defined(mac_os)
                const std::string rel_adapter = "en0";
            #else
                const std::string rel_adapter = "enp0s8";
            #endif
        #endif

        const std::string unspec_address_family = "Unspecific Address family";
        const std::string ip_version4_address_family = "IP Version 4 family";
        const std::string ip_version6_address_family = "IP Version 6 family";

        #if defined(unix_os)
            
            #if defined(mac_os)
                const std::string link_layer_address_family = "Link-layer Interface Address family";
            #else
                const std::string netlink_address_family = "Netlink Address family";
                const std::string packet_address_family = "Packet Address family";
            #endif
        #else
            
            const std::string netbios_address_family = "NetBIOS Address family";
            const std::string irda_address_family = "IrDa Address family";
            const std::string bluetooth_address_family = "Bluetooth Address family";

        #endif

        const std::string unrecognized_address_family = "Unrecognized Address family";

    }
}

std::set<std::string> networking::network_address_families::get_address_families() {
    std::set<std::string> the_answer;
    the_answer.insert(unspec_address_family);
    the_answer.insert(unrecognized_address_family);
    the_answer.insert(ip_version4_address_family);
    the_answer.insert(ip_version6_address_family);
    #if defined(unix_os)
        #if defined(mac_os)
            the_answer.insert(link_layer_address_family);
        #else
            the_answer.insert(netlink_address_family);
            the_answer.insert(packet_address_family);
        #endif
    #else
        the_answer.insert(netbios_address_family);
        the_answer.insert(irda_address_family);
        the_answer.insert(bluetooth_address_family);
    #endif
    return the_answer;
}

std::string networking::network_address_families::resolve_address_family_to_string(socket_family_type the_family) {
    std::string the_answer = unrecognized_address_family;
    switch(the_family) {

        case (AF_UNSPEC) : {
            the_answer = network_address_families::unspec_address_family;
            break;
        }

        case (AF_INET) : {
            the_answer = network_address_families::ip_version4_address_family;
            break;
        }

        case (AF_INET6) : {
            the_answer = network_address_families::ip_version6_address_family;
            break;
        }

        #if defined(unix_os)
            
            #if defined(mac_os)

                case (AF_LINK) : {
                    the_answer = network_address_families::link_layer_address_family;
                    break;
                }
            
            #else

                case (AF_NETLINK) : {
                    the_answer = network_address_families::netlink_address_family;
                    break;
                }

                case (AF_PACKET) : {
                    the_answer = network_address_families::packet_address_family;
                    break;
                }

            #endif

        #else

            case (AF_NETBIOS) : {
                the_answer = network_address_families::netbios_address_family;
                break;
            }

            case (AF_IRDA) : {
                the_answer = network_address_families::irda_address_family;
                break;
            }

            case (AF_BTH) : {
                the_answer = network_address_families::bluetooth_address_family;
                break;
            }
            
        #endif

        default : {
            the_answer = network_address_families::unrecognized_address_family;
            break;
        }
    }
    return the_answer;
}

networking::exceptions::base_exception::base_exception(const std::string name, const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) {
    this->except_name = name;
    this->message = msg;
    this->file = file_name;
    this->line = except_line;
    this->func = function;
    if (print) {
        std::fprintf(stderr, "\"%s\" Thrown:\n%s:%s:line, %d:\n%s\n", this->except_name.c_str(), this->file.c_str(), this->func.c_str(), this->line, this->message.c_str());
    }
}

networking::exceptions::base_exception::~base_exception() throw() {}

const std::string networking::exceptions::base_exception::msg() const {
    return "\"" + this->except_name + "\" Thrown:\n" + this->file + ":" + this->func + "line, " + std::to_string(this->line) + "\n" + this->message.c_str() + "\n";
}

const std::string networking::exceptions::base_exception::exception_type() const {
    return this->except_name;
}


networking::exceptions::unexpected_exception::unexpected_exception(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("unexpected_exception", msg, print, file_name, except_line, function) {}

networking::exceptions::memory_exception::memory_exception(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("memory_exception", msg, print, file_name, except_line, function) {}

networking::exceptions::initialize_network_failure::initialize_network_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("initialize_network_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::getaddrinfo_failure::getaddrinfo_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("getaddrinfo_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::getifaddrs_failure::getifaddrs_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("getifaddrs_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::create_socket_failure::create_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("create_socket_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::bind_socket_failure::bind_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("bind_socket_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::listen_socket_failure::listen_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("listen_socket_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::select_failure::select_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("select_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::getnameinfo_failure::getnameinfo_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("getnameinfo_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::connect_failure::connect_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("connect_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::certificate_or_key_error::certificate_or_key_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception("certificate_or_key_error", msg, print, file_name, except_line, function) {}
        
networking::exceptions::secure_sockets_layer_error::secure_sockets_layer_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
    networking::exceptions::base_exception("secure_sockets_layer_error", msg, print, file_name, except_line, function) {}

networking::exceptions::certificate_error::certificate_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
    networking::exceptions::base_exception("certificate_error", msg, print, file_name, except_line, function) {}

networking::exceptions::accept_failure::accept_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
    networking::exceptions::base_exception("accept_failure", msg, print, file_name, except_line, function) {}

networking::exceptions::create_context_failure::create_context_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
    networking::exceptions::base_exception("accept_failure", msg, print, file_name, except_line, function) {}


bool networking::initialize_network() {
    #if defined(crap_os)
        if (not is_init) {
            WSADATA d;
            // std::printf("Initializing network...\n");
            if (WSAStartup(MAKEWORD(2, 2), &d)) {
                return false;
            }
            is_init = true;
            // std::printf("Network is initialized...\n");
        }
    #endif
    return is_init;
}

bool networking::initialize_secure_network() {
    if (not is_init_secure) {
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
        is_init_secure = true;
    }
    return is_init_secure;
}

bool networking::uninitialize_network() {
    #if defined(crap_os)
        if (is_init) {
            // std::printf("Uninitializing network...\n");
            if (WSACleanup()) {
                return is_init;
            }
            is_init = false;
            // std::printf("Network is uninitialized...\n");
        }
    #endif
    return is_init is false;
}

bool networking::uninitialize_secure_network() {
    if (is_init_secure) {
        OPENSSL_cleanup();
        is_init_secure = false;
    }
    return not is_init_secure;
}


std::vector<std::string> networking::resolve_hostname(const std::string hostname, const std::string port, const bool name) {
    
    bool was_init = is_init;

    if (not was_init) {
        if (not initialize_network()) {
            (clean_on_except) ? uninitialize_network() : true;
            throw exceptions::initialize_network_failure("Failed to initialize. ", true, __FILE__, __LINE__ - 2, "resolve_host_name");
        }
    }
    // To get here, the network was successfully initialized.
    std::vector<std::string> the_answer;
    struct addrinfo hints, *current, *all_addresses;
    char buffer[buffer_size];
    std::memset(&hints, 0, sizeof(hints));
    std::memset(&buffer, 0, buffer_size);
    hints.ai_flags = AI_ALL;

    if (getaddrinfo(hostname.c_str(), port.c_str(), &hints, &all_addresses)) {
        (clean_on_except and not was_init) ? uninitialize_network() : true;
        throw exceptions::getaddrinfo_failure("Failed to get address information for host " + hostname, true, __FILE__, __LINE__ - 2, "resolve_hostname");
    }

    for (current = all_addresses; current NOT null; current = current->ai_next) {

        if (not getnameinfo(current->ai_addr, current->ai_addrlen, buffer, buffer_size, 0, 0, NI_NUMERICHOST | AI_ALL)) {
            the_answer.push_back(std::string(buffer));
        }

        if (name) {
            if (not getnameinfo(current->ai_addr, current->ai_addrlen, buffer, buffer_size, 0, 0, NI_NAMEREQD | AI_ALL)) {
                the_answer.push_back(std::string(buffer));
            }
        }
    }

    freeaddrinfo(all_addresses);

    if (not was_init) {
        if (not uninitialize_network()) {
            throw exceptions::initialize_network_failure("Failed to uninitialize network", true, __FILE__, __LINE__ - 1, "resolve_hostname");
        }
    }
    return the_answer;
}

std::map<std::string, std::map<std::string, std::vector<std::string> > > networking::this_machine_adapters(const bool names) {
    bool was_init = is_init;
    
    if (not was_init) {

        if (not initialize_network()) {
            (clean_on_except) ? uninitialize_network() : true;
            throw exceptions::initialize_network_failure("Failed to initialize. ", true, __FILE__, __LINE__ - 2, __FUNCTION__);
        }
    }
    
    std::map<std::string, std::map<std::string, std::vector<std::string> > > the_answer;

    ifaddrs_adapter_type all_adapters;
    #if defined(crap_os)

        all_adapters = NULL;
        DWORD memory_size = 20000;
        int this_line;
        
        while (not all_adapters) {
            
            all_adapters = (ifaddrs_adapter_type) malloc(memory_size);
            this_line = __LINE__ - 1;

            if (not all_adapters) {
                (clean_on_except) ? uninitialize_network() : true;
                throw exceptions::memory_exception("Failed to aquire " + std::to_string(memory_size) + " bytes of memory", true, __FILE__, this_line, __FUNCTION__);
            }

            int resp = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, all_adapters, &memory_size);
            this_line = __LINE__ - 1;

            if (resp is ERROR_BUFFER_OVERFLOW) {
                ifaddrs_free_adapters(all_adapters);
            }

            else if (resp is ERROR_SUCCESS) {
                break;
            }

            else {
                (clean_on_except) ? uninitialize_network() : true;
                ifaddrs_free_adapters(all_adapters);
                throw exceptions::unexpected_exception("An unexpected exception occured while trying to retrieve this machine's network adapter information", true, __FILE__, this_line, __FUNCTION__);
            }

        }
        std::printf("Done with the creation of the pointer for all_adapters.\n");

    #else

        if (getifaddrs(&all_adapters)) {
            (clean_on_except) ? uninitialize_network() : true;
            throw exceptions::getifaddrs_failure("Failed to retrieve adater information", true, __FILE__, __LINE__ - 2, __FUNCTION__);
        }

    #endif

    ifaddrs_adapter_type this_adapter;
    ifaddrs_address_type this_address;
    char buffer[buffer_size];
    std::string adapter_name, address_family, address_name;
    std::memset(buffer, 0, buffer_size);
    for (this_adapter = all_adapters; this_adapter; this_adapter = ifaddrs_get_next_adapter(this_adapter)) {
        // std::printf("Retrieving adapter_name\n");
        adapter_name = ifaddrs_get_adapter_name(this_adapter);
        // std::printf("Retrieved adapter name ('%s')\n", adapter_name.c_str());

        for (this_address = ifaddrs_pull_adapter_address(this_adapter); this_address; this_address = ifaddrs_get_next_address(this_address)) {
            // std::printf("\tRetrieving address family\n");
            address_family = network_address_families::resolve_address_family_to_string(ifaddrs_get_address_family(this_address));
            // std::printf("\tRetrieved address_family ('%s')\n\n", address_family.c_str());
            // now to pull the address
            string_functions::same_char(*buffer, 0, false) ? (void*) 0 : std::memset(buffer, 0, buffer_size);

            switch (getnameinfo(ifaddrs_get_address_sockaddr(this_address), ifaddrs_get_address_sockaddrlen(this_address), buffer, buffer_size, 0, 0, NI_NUMERICHOST)) {

                case 0 : {

                    address_name = std::string(buffer);
                    if (address_name.empty()) {
                        continue;
                    }
                    else if (not the_answer.count(adapter_name)) {

                        std::map<std::string, std::vector<std::string> > new_map;
                        std::vector<std::string> new_list;
                        new_list.push_back(address_name);
                        new_map.insert(std::make_pair(address_family, new_list));

                        the_answer.insert(std::make_pair(adapter_name, new_map));
                    }

                    else if (not the_answer[adapter_name].count(address_family)) {

                        std::vector<std::string> new_list;
                        new_list.push_back(address_name);

                        the_answer[adapter_name].insert(std::make_pair(address_family, new_list));
                    }

                    else {
                        the_answer[adapter_name][address_family].push_back(address_name);
                    }
                }


            }

            if (names) {

                string_functions::same_char(*buffer, 0, false) ? (void*) 0 : std::memset(buffer, 0, buffer_size);

                switch (getnameinfo(ifaddrs_get_address_sockaddr(this_address), ifaddrs_get_address_sockaddrlen(this_address), buffer, buffer_size, 0, 0, NI_NAMEREQD)) {

                    case 0 : {

                        address_name = std::string(buffer);
                        if (address_name.empty()) {
                            continue;
                        }
                        else if (not the_answer.count(adapter_name)) {

                            std::map<std::string, std::vector<std::string> > new_map;
                            std::vector<std::string> new_list;
                            new_list.push_back(adapter_name);
                            new_map.insert(std::make_pair(address_family, new_list));

                            the_answer.insert(std::make_pair(adapter_name, new_map));
                        }

                        else if (not the_answer[adapter_name].count(address_family)) {

                            std::vector<std::string> new_list;
                            new_list.push_back(address_name);

                            the_answer[adapter_name].insert(std::make_pair(address_family, new_list));
                        }
                        
                        else {
                            the_answer[adapter_name][address_family].push_back(address_name);
                        }
                    }
                }

            }


        }

    }
    
    ifaddrs_free_adapters(all_adapters);
    return the_answer;

}

bool networking::socket_is_connected(const socket_type the_socket) {
    // int error = 0;
    // socklen_t len = sizeof(error);
    int retval = 0;

    #ifdef _WIN32
        u_long mode = 1;  // 1 to enable non-blocking socket
        ioctlsocket(the_socket, FIONBIO, &mode);
    #else
        int flags = fcntl(the_socket, F_GETFL, 0);
        fcntl(the_socket, F_SETFL, flags | O_NONBLOCK);
    #endif

    char buffer[1];
    retval = recv(the_socket, buffer, 1, MSG_PEEK);

    if (retval == 0) {
        return false;  // Connection closed
    } else if (retval < 0) {
        #if defined(crap_os)
            int error = 0;
            error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK) {
                return false;  // Error occurred
            }
        #else
            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                return false;  // Error occurred
            }
        #endif
    }

    return true;  // Connection is still alive
}

bool networking::is_ipstring(const std::string the_ip, const bool ip4) {
    if (ip4) {
        std::istringstream ss(the_ip);
        std::string octet;
        int count = 0;

        while (std::getline(ss, octet, '.')) {
            if (++count > 4 || octet.empty() || octet.size() > 3) return false;
            for (char c : octet) {
                if (!std::isdigit(c)) return false;
            }
            int num = std::stoi(octet);
            if (num < 0 || num > 255 || (octet.size() > 1 && octet[0] == '0')) return false;
        }

        return count == 4 && ss.eof();
    }

    const std::regex ipv6_regex(ip6_regex_pattern);
    
    return std::regex_match(the_ip, ipv6_regex);
}

bool networking::network_structures::connected_host::client_name::operator<(const client_name& other) const {
    return this->hostname < other.hostname and this->portvalue < other.portvalue;
}

bool networking::network_structures::connected_host::client::operator<(const client& other) const {
    return this->connected_socket < other.connected_socket;
}

networking::network_structures::connected_host::client::operator bool() const {
    return valid_socket(this->connected_socket);
}

bool networking::network_structures::connected_host::server::operator<(const server& other) const {
    return this->hostname < other.hostname and 
        this->portvalue < other.portvalue;
}

networking::network_structures::connected_host::server::operator bool() const {
    return valid_socket(this->connect_socket);
}

/***********************************************************************************************/



bool networking::network_structures::host::create_context_(bool server_) {
    
    if (not is_init) {
        this->was_init = false;
        initialize_network();
    }

    if (not is_init_secure) {
        this->was_init_secure = false;
        initialize_secure_network();
    }

    if (this->secure_ and not valid_context(this->context)) {
        this->context = SSL_CTX_new((server_) ? TLS_server_method() : TLS_client_method());
    }
    return valid_context(this->context);
}

bool networking::network_structures::host::create_address() {

    if (not this->address_information) {

        if (this->host_name.empty()) {
            std::map<std::string, std::map<std::string, std::vector<std::string> > > adapters = this_machine_adapters();

            for (auto adapter = adapters.begin(); adapter != adapters.end(); adapter++) {

                if (not string_functions::same_string(adapter->first, network_address_families::rel_adapter)) {
                    continue;
                }

                for (auto family = adapter->second.begin(); family != adapter->second.end(); family++)  {
                    if (not string_functions::same_string(network_address_families::ip_version4_address_family, family->first) and not 
                        string_functions::same_string(network_address_families::ip_version6_address_family, family->first)) {
                        continue;
                    }
                    
                    for (auto address = family->second.begin(); address != family->second.end(); address++) {
                        if (address->empty()) {
                            continue;
                        }

                        this->host_name = *address;
                        goto end;
                    }
                }

                
                if (not this->host_name.empty()) {
                    break;
                }
            }
        }

        end:
        if (this->port_value.empty()) {
            this->port_value = DEFAULT_PORT;
        }

        struct addrinfo hints;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = (this->tcp) ? SOCK_STREAM : SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE;
        if (getaddrinfo(this->host_name.c_str(), this->port_value.c_str(), &hints, &this->address_information)) {
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::getaddrinfo_failure("Failed to retrieve address information for \"" + this->host_name + "\"", true, __FILE_NAME__, __LINE__ - 2, __FUNCTION__);
        }

    }
    return this->address_information != nullptr;
}

bool networking::network_structures::host::create_socket() {
    if (not valid_socket(this->connect_socket)) {
        if (not this->create_address()) {
            throw exceptions::getaddrinfo_failure("Failed to retrieve address information", true, __FILE_NAME__, __LINE__ - 1, __FUNCTION__);
        }
        this->connect_socket = socket(this->address_information->ai_family, this->address_information->ai_socktype, this->address_information->ai_protocol);
        #if defined(unix_os)
            int reuse = 1;
        #else
            char reuse = 1;
        #endif
        if (setsockopt(this->connect_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))) {
            throw exceptions::create_socket_failure("Failed to set connection socket to reuse", true, __FILE__, __LINE__ - 1, __FUNCTION__);
        }
    }
    return valid_socket(this->connect_socket);
}

networking::network_structures::host::host() {
    
    this->connect_socket = invalid_socket;
    this->address_information = 0;
    this->host_name = DEFAULT_HOST;
    this->cert_file = this->key_file = "";
    this->port_value = DEFAULT_PORT;
    this->tcp = true;
    this->was_init = is_init;
    this->timeout = {0, 200};
    this->secure_ = false;
    this->was_init_secure = is_init_secure;
    this->context = invalid_context;
}

networking::network_structures::host::host(const std::string hostname, const std::string port, bool use_tcp, bool secure, struct timeval select_timeout, const std::string cert_file, const std::string key_file) {
    this->connect_socket = invalid_socket;
    this->address_information = 0;
    this->host_name = hostname;
    this->port_value = port;
    this->tcp = use_tcp;
    this->was_init = is_init;
    this->timeout = select_timeout;
    this->secure_ = secure;
    this->was_init_secure = is_init_secure;
    this->context = invalid_context;
    this->cert_file = cert_file;
    this->key_file = key_file;
}

networking::network_structures::host::host(const networking::network_structures::host& other) {
    if (this != &other) {
        this->close_host();
        this->connect_socket = other.connect_socket;
        this->address_information = 0;
        this->host_name = other.host_name;
        this->port_value = other.port_value;
        this->cert_file = other.cert_file;
        this->key_file = other.key_file;
        this->tcp = other.tcp;
        this->was_init = other.was_init;
        this->timeout = other.timeout;
        this->secure_ = other.secure_;
        this->was_init_secure = other.was_init_secure;
        this->context = other.context;
    }
}

networking::network_structures::host::~host() {
    this->close_host();
}

networking::network_structures::host& networking::network_structures::host::operator=(const networking::network_structures::host& other) {
    if (this != &other) {
        this->connect_socket = other.connect_socket;
        this->address_information = 0;
        this->host_name = other.host_name;
        this->port_value = other.port_value;
        this->tcp = other.tcp;
        this->was_init = other.was_init;
        this->timeout = other.timeout;
        this->secure_ = other.secure_;
        this->was_init_secure = other.was_init_secure;
        this->context = other.context;
    }
    return *this;
}

networking::network_structures::host::operator bool() const {
    return (this->secure_) ? valid_context(this->context) : valid_socket(this->connect_socket);
}

bool networking::network_structures::host::secure() const {
    return this->secure_;
}

networking::network_structures::host& networking::network_structures::host::secure(const bool new_flag) {
    if ((this->secure_ and not valid_context(this->context)) or (not this->secure_ and not valid_socket(this->connect_socket))) {
        this->secure_ = new_flag;
    }
    return *this;
}

networking::network_structures::host& networking::network_structures::host::hostname(const std::string new_host) {
    if ((this->secure_ and not valid_context(this->context)) or (not this->secure_ and not valid_socket(this->connect_socket))) {
        this->host_name = new_host;
    }
    return *this;
}

std::string networking::network_structures::host::hostname() const {
    return this->host_name;
}

socket_type networking::network_structures::host::connection_socket() const {
    return this->connect_socket;
}

bool networking::network_structures::host::close_host() {
    
    if (this->address_information) {
        freeaddrinfo(this->address_information);
        this->address_information = null;
    }

    if (valid_context(this->context)) {
        SSL_CTX_free(this->context);
        this->context = invalid_context;
    }

    if (not this->was_init_secure){
        uninitialize_secure_network();
        this->was_init_secure = false;
    }

    if (not this->was_init) {
        uninitialize_network();
        this->was_init = false;
    }

    this->key_file = this->cert_file = this->host_name = this->port_value = "";
    return not this->address_information and 
            not valid_context(this->context) and 
                not this->was_init and 
                    not this->was_init_secure;
}