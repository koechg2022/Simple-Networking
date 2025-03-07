




#include "../headers/included"
#include "string_functions"
#include "networking"











namespace networking {


    namespace {

        #if defined(crap_os)
            bool is_init = false;
        #else
            const bool is_init = true;
        #endif

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



networking::network_structures::host::host() {
    this->connect_socket = invalid_socket;
    this->hostname = "";
    this->portvalue = DEFAULT_PORT;
    this->timeout = {0, 100000};
    this->tcp = true;
    this->was_init = is_init;
    initialize_network();
    this->del_on_except = true;
    this->secure_ = this->initialized_secure = this->certificates = false;
    this->context = null;
    this->secure_socket = null;
    this->certificates = false;
    this->certificate = null;
    this->connect_address = 0;
}

networking::network_structures::host::host(const std::string host_name, const std::string port, bool use_tcp, long wait_sec, int wait_msec, bool will_del, bool secure) {
    this->connect_socket = invalid_socket;
    this->hostname = host_name;
    this->portvalue = port;
    this->timeout = {wait_sec, wait_msec};
    this->tcp = use_tcp;
    this->was_init = is_init;
    initialize_network();
    this->del_on_except = will_del;
    this->secure_ = secure;
    this->initialized_secure = this->certificates = false;
    this->context = null;
    this->secure_socket = null;
    this->certificates = false;
    this->certificate = null;
    this->connect_address = 0;
}

networking::network_structures::host::~host() {
    if (this->connect_address) {
        freeaddrinfo(this->connect_address);
        this->connect_address = null;
    }

    if (this->secure_socket) {
        SSL_shutdown(this->secure_socket);
    }

    if (valid_socket(this->connect_socket)) {
        close_socket(this->connect_socket);
    }

    if (this->secure_socket) {
        SSL_free(secure_socket);
        SSL_CTX_free(this->context);
    }

    if (not this->certificate) {
        X509_free(this->certificate);
        this->certificate = null;
    }

    if (not was_init) {
        uninitialize_network();
    }
}

networking::network_structures::host::host(const network_structures::host& other) {
    if (this != &other) {
        this->connect_socket = other.connect_socket;
        this->hostname = other.hostname;
        this->portvalue = other.portvalue;
        this->connect_address = other.connect_address;
        this->timeout = other.timeout;
        this->tcp = other.tcp;
        this->was_init = other.was_init;
        this->del_on_except = other.del_on_except;

        // secure stuff
        this->secure_ = other.secure_;
        this->initialized_secure = other.initialized_secure;
        this->context = other.context;
        this->secure_socket = other.secure_socket;
        this->certificates = other.certificates;
        this->certificate = other.certificate;
    }
}

networking::network_structures::host& networking::network_structures::host::operator=(networking::network_structures::host& other) {
    if (this != &other) {
        this->connect_socket = other.connect_socket;
        this->hostname = other.hostname;
        this->portvalue = other.portvalue;
        this->connect_address = other.connect_address;
        this->timeout = other.timeout;
        this->tcp = other.tcp;
        this->was_init = other.was_init;
        this->del_on_except = other.del_on_except;
        this->secure_ = other.secure_;

        this->initialized_secure = other.initialized_secure;
        this->context = other.context;
        this->secure_socket = other.secure_socket;
        this->certificates = other.certificates;
        this->certificate = other.certificate;
    }
    return *this;
}

networking::network_structures::host& networking::network_structures::host::operator=(const networking::network_structures::host& other) {
    if (this != &other) {
        this->connect_socket = other.connect_socket;
        this->hostname = other.hostname;
        this->portvalue = other.portvalue;
        this->connect_address = other.connect_address;
        this->timeout = other.timeout;
        this->tcp = other.tcp;
        this->was_init = other.was_init;
        this->del_on_except = other.del_on_except;
        this->secure_ = other.secure_;

        this->initialized_secure = other.initialized_secure;
        this->context = other.context;
        this->secure_socket = other.secure_socket;
        this->certificates = other.certificates;
        this->certificate = other.certificate;
    }
    return *this;
}


bool networking::network_structures::host::host_name(const std::string new_host) {
    if (valid_socket(this->connect_socket) and connect_address and ((this->secure_) ? (this->context and this->secure_socket) : true)) {
        return false;
    }
    this->hostname = new_host;
    return string_functions::same_string(new_host, this->hostname);
}


std::string networking::network_structures::host::host_name() const {
    return this->hostname;
}

    
bool networking::network_structures::host::port_value(const std::string new_port) {
    if (valid_socket(this->connect_socket) and connect_address and ((this->secure_) ? (this->context and this->secure_socket) : true)) {
        return false;
    }
    this->portvalue = new_port;
    return string_functions::same_string(this->portvalue, new_port);
}


std::string networking::network_structures::host::port_value() const {
    return this->portvalue;
}


bool networking::network_structures::host::create_address() {
    
    if (not this->connect_address) {
        struct addrinfo hints;
        
        if (this->hostname.empty()) {
            
            std::map<std::string, std::map<std::string, std::vector<std::string> > > adapters = this_machine_adapters();

            for (auto adapter = adapters.begin(); adapter != adapters.end(); adapter++) {
                
                if (not string_functions::same_string(adapter->first, network_address_families::rel_adapter)) {
                    continue;
                }
                
                for (auto family = adapter->second.begin(); family != adapter->second.end(); family++) {
                    if (not string_functions::same_string(network_address_families::ip_version4_address_family, family->first) and not string_functions::same_string(network_address_families::ip_version6_address_family, family->first)) {
                        continue;
                    }

                    for (auto address = family->second.begin(); address != family->second.end(); address++) {
                        if (address->empty()) {
                            continue;
                        }
                        this->hostname = *address;
                        break;
                    }

                    if (not this->hostname.empty()) {
                        break;
                    }
                }

                if (not this->hostname.empty()) {
                    break;
                }
            }
        }

        if (this->portvalue.empty()) {
            this->portvalue = DEFAULT_PORT;
        }

        std::memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = (this->tcp) ? SOCK_STREAM : SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE;
        // std::printf("The host is '%s'\n", this->hostname.c_str());
        if (getaddrinfo(this->hostname.c_str(), this->portvalue.c_str(), &hints, &this->connect_address)) {
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::getaddrinfo_failure("Failed to retrieve address information for local machine", true, __FILE__, __LINE__ - 2, __FUNCTION__);
        }
    }
    return this->connect_address;
}


bool networking::network_structures::host::create_socket() {

    this->create_address();
    if (not valid_socket(this->connect_socket)) {
        this->connect_socket = socket(this->connect_address->ai_family, this->connect_address->ai_socktype, this->connect_address->ai_protocol);
        if (not valid_socket(this->connect_socket)) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::create_socket_failure("Failed to create connection socket for host " + this->hostname + ". Error number " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 4, __FUNCTION__);
        }
        // std::printf("Created the connection socket...\n");
        #if defined(unix_os)
            int reuse = 1;
        #else
            char reuse = 1;
        #endif
        // std::printf("setting socket options...\n");
        if (setsockopt(this->connect_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))) {
            std::fprintf(stderr, "Failed to set reusable socket.\n");
        }
    }
    return this->connect_socket;
}


bool networking::network_structures::host::initialize_secure() {
    if (this->secure_ and not this->initialized_secure) {
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
        this->initialized_secure = true;
    }
    return (this->secure_) ? this->initialized_secure : not this->initialized_secure;
}


bool networking::network_structures::host::create_context() {
    
    if (this->secure_ and not this->initialize_secure()) {
        return false;
    }

    if (this->secure_ and not this->context) {
        this->context = SSL_CTX_new(TLS_client_method());
    }
    return (this->secure_) ? valid_context(this->context) : not valid_context(this->context);
}


bool networking::network_structures::host::create_secure_socket() {
    if (this->secure_ and not this->initialize_secure()) {
        return false;
    }

    if (this->secure_ and not this->create_context()) {
        return false;
    }

    if (this->secure_ and not this->secure_socket) {
        this->secure_socket = SSL_new(this->context);
    }
    return this->secure_socket;
}


void networking::network_structures::host::update_timeout(long sec, int m_sec) {
    this->timeout = {sec, m_sec};
}


bool networking::network_structures::host::will_delete_on_except() const {
    return this->del_on_except;
}


void networking::network_structures::host::will_delete_on_except(const bool new_flag) {
    this->del_on_except = new_flag;
}


socket_type networking::network_structures::host::get_connection_socket() const {
    return this->connect_socket;
}


secure_socket_type networking::network_structures::host::get_secure_connection_socket() const {
    return this->secure_socket;
}

bool networking::network_structures::host::secure_host() {
    return this->secure_;
}
    



/***********************************************************************************************/





bool networking::network_structures::tcp_server::create_certificates() {
    if (this->secure_ and not this->certificates) {
        this->initialize_secure();
        this->create_context();
        if (not SSL_CTX_use_certificate_file(this->context, this->cert_pem_file.c_str(), SSL_FILETYPE_PEM) or not SSL_CTX_use_PrivateKey_file(this->context, this->key_pem_file.c_str(), SSL_FILETYPE_PEM)) {
            (not this->was_init) ? uninitialize_network() : true;
            char err_buf[256]; unsigned long err = ERR_get_error(); ERR_error_string_n(err, err_buf, sizeof(err_buf));
            throw exceptions::certificate_or_key_error("Failed to create the certificate or private key for this server. Error '" + std::string(err_buf) + "'", true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }
        this->certificates = true;
    }
    return this->certificates;
}

bool networking::network_structures::tcp_server::disconnect_client(networking::network_structures::connected_host::client& client) {
    
    if (client.secure_socket != invalid_secure_socket) {
        SSL_shutdown(client.secure_socket);
    }

    if (valid_socket(client.connected_socket)) {

        close_socket(client.connected_socket);
        client.connected_socket = invalid_socket;
    }

    if (client.secure_socket != invalid_secure_socket) {
        SSL_free(client.secure_socket);
        client.secure_socket = invalid_secure_socket;
    }

    if (not client.hostname.empty()) {
        client.hostname = "";
    }

    if (not client.portvalue.empty()) {
        client.portvalue = "";
    }

    client.address_info = empty_sockaddr();

    if (this->clients.contains(client.connected_socket)) {
        this->clients.erase(client.connected_socket);
        this->max_socket = invalid_socket;
        this->max_secure_socket = invalid_secure_socket;
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
            this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : this->max_secure_socket;
        }
    }
    
    
    return not valid_socket(client.connected_socket) and 
            not valid_secure_socket(client.secure_socket) and
                not this->clients.contains(client.connected_socket) and
                #if defined(mac_os)
                    client.address_info.ss_len == 0 and 
                #endif
                        client.address_info.ss_family == 0 and 
                            client.hostname.empty() and 
                                client.portvalue.empty();
}

bool networking::network_structures::tcp_server::bind_socket() {
    if (not this->bound) {
        if (this->secure_) {
            this->initialize_secure();
            this->create_certificates();
        }
        this->create_address();
        this->create_socket();
        
        if (bind(this->connect_socket, this->connect_address->ai_addr, this->connect_address->ai_addrlen)) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (this->was_init) ? uninitialize_network() : true;
            throw exceptions::bind_socket_failure("Failed to bind the connecting socket", true, __FILE__, __LINE__- 3, __FUNCTION__);
        }
        this->bound = true;
    }
    return this->bound;
}

bool networking::network_structures::tcp_server::start_listening() {
    if (not this->listening) {
        
        if (this->secure_) {
            this->initialize_secure();
            this->create_certificates();
        }

        this->create_address();
        this->create_socket();
        this->bind_socket();

        if (listen(this->connect_socket, this->listen_lim)) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (this->was_init) ? uninitialize_network() : true;
            throw exceptions::listen_socket_failure("Failed to start listening on the connection socket", true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }
        this->listening = true;
    }
    return this->listening;
}

networking::network_structures::tcp_server::tcp_server(const std::string host, const std::string port, int listen_limit, long seconds_wait, int micro_sec_wait, bool will_del, bool secure) :
    networking::network_structures::host::host(host, port, true, seconds_wait, micro_sec_wait, will_del, secure) {
    this->listen_lim = listen_limit;
    this->listening = this->bound = false;
    this->max_socket = invalid_socket;
    this->max_secure_socket = null;
}

networking::network_structures::tcp_server::~tcp_server() {
    this->close_server();
}

networking::network_structures::tcp_server::tcp_server(const networking::network_structures::tcp_server& other) {
    if (this != &other) {

        // For the host stuff:
        this->connect_socket = other.connect_socket;
        this->hostname = other.hostname;
        this->portvalue = other.portvalue;
        this->connect_address = other.connect_address;
        this->timeout = other.timeout;
        this->tcp = other.tcp;
        this->was_init = other.was_init;
        this->del_on_except = other.del_on_except;

        // secure stuff
        this->secure_ = other.secure_;
        this->initialized_secure = other.initialized_secure;
        this->context = other.context;
        this->secure_socket = other.secure_socket;
        this->certificates = other.certificates;


        // For the tcp_server
        this->listen_lim = other.listen_lim;
        this->listening = other.listening;
        this->bound = other.bound;
        this->max_socket = other.max_socket;
        this->max_secure_socket = other.max_secure_socket;
        this->clients = other.clients;
    }
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::operator=(networking::network_structures::tcp_server& other) {
    if (this != &other) {
        // For the host stuff:
        this->connect_socket = other.connect_socket;
        this->hostname = other.hostname;
        this->portvalue = other.portvalue;
        this->connect_address = other.connect_address;
        this->timeout = other.timeout;
        this->tcp = other.tcp;
        this->was_init = other.was_init;
        this->del_on_except = other.del_on_except;

        // secure stuff
        this->secure_ = other.secure_;
        this->initialized_secure = other.initialized_secure;
        this->context = other.context;
        this->secure_socket = other.secure_socket;
        this->certificates = other.certificates;


        // For the tcp_server
        this->listen_lim = other.listen_lim;
        this->listening = other.listening;
        this->bound = other.bound;
        this->max_socket = other.max_socket;
        this->max_secure_socket = other.max_secure_socket;
        this->clients = other.clients;
    }
    return *this;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::operator=(const networking::network_structures::tcp_server& other) {
    if (this != &other) {
        // For the host stuff:
        this->connect_socket = other.connect_socket;
        this->hostname = other.hostname;
        this->portvalue = other.portvalue;
        this->connect_address = other.connect_address;
        this->timeout = other.timeout;
        this->tcp = other.tcp;
        this->was_init = other.was_init;
        this->del_on_except = other.del_on_except;

        // secure stuff
        this->secure_ = other.secure_;
        this->initialized_secure = other.initialized_secure;
        this->context = other.context;
        this->secure_socket = other.secure_socket;
        this->certificates = other.certificates;


        // For the tcp_server
        this->listen_lim = other.listen_lim;
        this->listening = other.listening;
        this->bound = other.bound;
        this->max_socket = other.max_socket;
        this->max_secure_socket = other.max_secure_socket;
        this->clients = other.clients;
    }
    return *this;
}

networking::network_structures::tcp_server::operator bool() const {
    return this->running();
}

bool networking::network_structures::tcp_server::new_connection(bool accept_new) {
    fd_set ready;
    FD_ZERO(&ready);
    FD_SET(this->connect_socket, &ready);

    if (select(this->connect_socket + 1, &ready, 0, 0, (this->timeout.tv_usec is -1) ? 0 : &this->timeout) < 0) {
        (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
        (not this->was_init) ? uninitialize_network() : true;
        throw exceptions::select_failure("Failed to select for the actively listening socket for new connections. Error number " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
    }

    if (accept_new) {
        const unsigned long old = this->clients.size();
        if (FD_ISSET(this->connect_socket, &ready)) {
            network_structures::connected_host::client new_client;
            new_client.connected_socket = accept(this->connect_socket, (struct sockaddr*) &new_client.address_info, &new_client.address_size);

            if (not valid_socket(new_client.connected_socket)) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::create_socket_failure("Failed to create a connection to the new client. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
            }

            char address[buffer_size], service[buffer_size];
            std::memset(address, 0, buffer_size);
            std::memset(service, 0, buffer_size);

            if (getnameinfo((struct sockaddr*) &new_client.address_info, new_client.address_size, address, buffer_size, service, buffer_size, NI_NUMERICHOST)) {
                new_client.hostname = "Unspecified hostname";
                new_client.portvalue = "Unspecified port";
            }
            else {
                new_client.hostname = std::string(address);
                new_client.portvalue = std::string(service);
            }

            this->max_socket = (new_client.connected_socket > this->max_socket) ? new_client.connected_socket : this->max_socket;

            if (this->secure_) {
                new_client.secure_socket = SSL_new(this->context);
                if (not valid_secure_socket(new_client.secure_socket)) {
                    (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                    (not this->was_init) ? uninitialize_network() : true;
                    throw exceptions::secure_sockets_layer_error("Failed to create a secure connection with the new client", true, __FILE__, __LINE__ - 4, __FUNCTION__);
                }

                SSL_set_fd(new_client.secure_socket, new_client.connected_socket);
                if (SSL_accept(new_client.secure_socket) <= 0) {
                    this->disconnect_client(new_client);
                    (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                    (not this->was_init) ? uninitialize_network() : true;
                    char err_buf[256]; unsigned long err = ERR_get_error(); ERR_error_string_n(err, err_buf, sizeof(err_buf));
                    throw exceptions::accept_failure("Failed to accept a secure connection to client. Error : " + std::string(err_buf), true, __FILE__, __LINE__ - 5, __FUNCTION__);
                }
                this->max_secure_socket = (new_client.secure_socket > this->max_secure_socket) ? new_client.secure_socket : this->max_secure_socket;
            }
            this->clients.insert({new_client.connected_socket, new_client});
        }
        return this->clients.size() > old;
    }
    return FD_ISSET(this->connect_socket, &ready);
}

networking::network_structures::connected_host::client networking::network_structures::tcp_server::new_client() {
    
    
    if (not *this) {
        return (network_structures::connected_host::client) {};
    }

    fd_set ready;
    FD_ZERO(&ready);
    FD_SET(this->connect_socket, &ready);

    if (select(this->connect_socket + 1, &ready, 0, 0, (this->timeout.tv_usec is -1) ? 0 : &this->timeout) < 0) {
        (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
        (not this->was_init) ? uninitialize_network() : true;
        throw exceptions::select_failure("Failed to select for the actively listening socket for new connections. Error number " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
    }

    network_structures::connected_host::client the_answer;
    
    if (FD_ISSET(this->connect_socket, &ready)) {
        network_structures::connected_host::client new_client;
        new_client.connected_socket = accept(this->connect_socket, (struct sockaddr*) &new_client.address_info, &new_client.address_size);

        if (not valid_socket(new_client.connected_socket)) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::create_socket_failure("Failed to create a connection to the new client. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }

        char address[buffer_size], service[buffer_size];
        std::memset(address, 0, buffer_size);
        std::memset(service, 0, buffer_size);

        if (getnameinfo((struct sockaddr*) &new_client.address_info, new_client.address_size, address, buffer_size, service, buffer_size, NI_NUMERICHOST)) {
            new_client.hostname = "Unspecified hostname";
            new_client.portvalue = "Unspecified port";
        }
        else {
            new_client.hostname = std::string(address);
            new_client.portvalue = std::string(service);
        }

        this->max_socket = (new_client.connected_socket > this->max_socket) ? new_client.connected_socket : this->max_socket;

        if (this->secure_) {
            new_client.secure_socket = SSL_new(this->context);
            if (not valid_secure_socket(new_client.secure_socket)) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::secure_sockets_layer_error("Failed to create a secure connection with the new client", true, __FILE__, __LINE__ - 4, __FUNCTION__);
            }

            SSL_set_fd(new_client.secure_socket, new_client.connected_socket);
            if (SSL_accept(new_client.secure_socket) <= 0) {
                this->disconnect_client(new_client);
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (not this->was_init) ? uninitialize_network() : true;
                char err_buf[256]; unsigned long err = ERR_get_error(); ERR_error_string_n(err, err_buf, sizeof(err_buf));
                throw exceptions::accept_failure("Failed to accept a secure connection to client. Error : " + std::string(err_buf), true, __FILE__, __LINE__ - 5, __FUNCTION__);
            }
            this->max_secure_socket = (new_client.secure_socket > this->max_secure_socket) ? new_client.secure_socket : this->max_secure_socket;
        }
        this->clients.insert({new_client.connected_socket, new_client});
        return new_client;
    }
    
    return the_answer;
}

bool networking::network_structures::tcp_server::close_connection(const socket_type to_close) {
    bool the_answer = false;
    for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
        if (to_close == client->first) {
            // This is the client to be removed
            // std::printf("Closing secure socket...\n");
            (this->secure_) ? SSL_shutdown(client->second.secure_socket) : 0;
            // std::printf("Closing connection socket...\n");
            (socket_is_connected(client->first)) ? close_socket(client->first) : 0;
            // std::printf("Freeing secure socket...\n");
            (this->secure_) ? SSL_free(client->second.secure_socket) : (void) 0;
            // std::printf("Removing client from database...\n");
            this->clients.erase(client->first);
            the_answer = true;
            goto other;
        }
    }

    other:
    this->max_socket = invalid_socket;
    for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
        this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
        this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : this->max_secure_socket;
    }
    return the_answer;
}

bool networking::network_structures::tcp_server::close_connection(const std::string hostname, const std::string portvalue) {
    bool the_answer = false;
    for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
        if (string_functions::same_string(client->second.hostname, hostname) and string_functions::same_string(client->second.portvalue, portvalue)) {
            // This is the client to be removed
            // std::printf("Closing secure socket...\n");
            (this->secure_) ? SSL_shutdown(client->second.secure_socket) : 0;
            // std::printf("Closing connection socket...\n");
            (socket_is_connected(client->first)) ? close_socket(client->first) : 0;
            // std::printf("Freeing secure socket...\n");
            (this->secure_) ? SSL_free(client->second.secure_socket) : (void) 0;
            // std::printf("Removing client from database...\n");
            this->clients.erase(client->first);
            the_answer = true;
            goto other;
        }
    }

    other:
    this->max_socket = invalid_socket;
    for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
        this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
        this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : this->max_secure_socket;
    }
    return the_answer;
}

bool networking::network_structures::tcp_server::close_server() {
    for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
        this->disconnect_client(client->second);
    }

    this->listen_lim = 0;
    this->listening = this->bound = false;
    this->max_secure_socket = null;
    this->max_socket = invalid_socket;
    if (this->connect_address) {
        freeaddrinfo(this->connect_address);
        this->connect_address = null;
    }

    if (this->secure_socket) {
        SSL_shutdown(this->secure_socket);
        this->secure_socket = invalid_secure_socket;
    }

    if (valid_socket(this->connect_socket)) {
        close_socket(this->connect_socket);
        this->connect_socket = invalid_socket;
    }

    if (this->secure_socket) {
        SSL_free(secure_socket);
        SSL_CTX_free(this->context);
        this->context = invalid_context;
    }

    if (not this->certificate) {
        X509_free(this->certificate);
        this->certificate = null;
    }

    if (not this->was_init) {
        uninitialize_network();
        this->was_init = true;
    }
    return this->clients.empty() and 
                not this->listen_lim and 
                    not valid_secure_socket(this->max_secure_socket) and
                        not valid_socket(this->max_socket);
}

bool networking::network_structures::tcp_server::update_limit(const int listening_limit) {
    if (not this->listening) {
        this->listen_lim = listening_limit;
    }
    return this->listen_lim == listening_limit;
}

int networking::network_structures::tcp_server::listening_limit() const {
    return this->listen_lim;
}

bool networking::network_structures::tcp_server::start() {

    if (not this->running()) {

        if (this->secure_ and not this->initialize_secure()) {
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::initialize_network_failure("Failed to initialize secure network functions and algorithms", true, __FILE__, __LINE__ - 2, __FUNCTION__);
        }
        
        if (this->secure_ and not this->create_context()) {
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::create_context_failure("Failed to create the secure network context", true, __FILE__, __LINE__ - 2, __FUNCTION__);
        }

        if (this->secure_ and not this->create_certificates()) {
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::certificate_or_key_error("Failed to create the certificates and/or errors for the secure connection", true, __FILE__, __LINE__ - 2, __FUNCTION__);
        }

        if (not this->create_address()) {
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::getaddrinfo_failure("Failed to get the address information for the connection.", true, __FILE__, __LINE__ - 2, __FUNCTION__);
        }

        if (not this->create_socket()) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (this->was_init) ? uninitialize_network() : true;
            throw exceptions::create_socket_failure("Failed to create the connection socket for incomming clients to be received on.", true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }

        if (not this->bind_socket()) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (this->was_init) ? uninitialize_network() : true;
            throw exceptions::bind_socket_failure("Failed to bind the connection socket. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }

        if (not this->start_listening()) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (this->was_init) ? uninitialize_network() : true;
            throw exceptions::listen_socket_failure("Failed to start the server listening.", true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }
        
        this->listening = true;
    }

    return this->listening;
}

bool networking::network_structures::tcp_server::running() const {
    return this->bound and this->listening and ((this->secure_ and valid_secure_socket(this->secure_socket)) or (not this->secure_ and valid_socket(this->connect_socket)));
}

std::set<networking::network_structures::connected_host::client> networking::network_structures::tcp_server::get_clients() {
    std::set<network_structures::connected_host::client> the_answer;
    if (not this->listening or this->clients.empty()) {
        return the_answer;
    }
    
    fd_set ready;
    FD_ZERO(&ready);
    for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
        FD_SET(client->first, &ready);
    }

    if (select(this->max_socket + 1, &ready, 0, 0, (this->timeout.tv_usec is -1) ? 0 : &this->timeout) < 0) {
        (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
        (not this->was_init) ? uninitialize_network() : true;
        throw exceptions::select_failure("Failed to select any of the connections that are ready with information. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
    }

    this->max_socket = invalid_socket;
    this->max_secure_socket = invalid_secure_socket;
    for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
        this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
        this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : client->second.secure_socket;
        if (FD_ISSET(client->first, &ready)) {
            the_answer.insert(client->second);
        }
    }
    return the_answer;
}

std::set<networking::network_structures::connected_host::client> networking::network_structures::tcp_server::get_all_clients() {
    
    std::set<network_structures::connected_host::client> the_answer;

    for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
        the_answer.insert(client->second);
    }

    return the_answer;
}

socket_type networking::network_structures::tcp_server::get_max_socket() const {
    return this->max_socket;
}

secure_socket_type networking::network_structures::tcp_server::get_max_secure_socket() const {
    return this->max_secure_socket;
}


/***********************************************************************************************/


networking::network_structures::tcp_client::tcp_client() : networking::network_structures::host() {
    this->connected = false;
    this->bytes = -1;
}


networking::network_structures::tcp_client::tcp_client(const std::string remote_host, const std::string connect_port, const long wait_sec, const int wait_msec, bool will_del, bool secure) :
networking::network_structures::host(remote_host, connect_port, true, wait_sec, wait_msec, will_del, secure) {
    this->connected = false;
    this->bytes = -1;
}


networking::network_structures::tcp_client::~tcp_client() {
    this->disconnect();
}


networking::network_structures::tcp_client::operator bool() {
    return this->connected;
}


bool networking::network_structures::tcp_client::connect_client() {
    if (this->connected) {
        return this->connected;
    }
    if (this->secure_) {
        this->initialize_secure();
        this->create_context();
    }

    this->create_address();
    this->create_socket();

    if (connect(this->connect_socket, this->connect_address->ai_addr, this->connect_address->ai_addrlen)) {
        (this->del_on_except) ? this->disconnect() : true;
        (not this->was_init) ? uninitialize_network() : true;
        throw exceptions::connect_failure("Failed to connect to remote machine. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
    }
    // std::printf("Connected.\n");
    
    if (this->secure_) {
        this->create_secure_socket();
        if (not valid_secure_socket(this->secure_socket)) {
            (this->del_on_except) ? this->disconnect() : true;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::create_socket_failure("Failed to create the secure connection socket. ", true, __FILE__, __LINE__ - 4, __FUNCTION__);
        }
        
        if (not SSL_set_tlsext_host_name(this->secure_socket, this->hostname.c_str())) {
            (this->del_on_except) ? this->disconnect() : true;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::unexpected_exception("Failed to set the TLS host name", true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }

        SSL_set_fd(this->secure_socket, this->connect_socket);
        if (SSL_connect(this->secure_socket) == -1) {
            (this->del_on_except) ? this->disconnect() : true;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::select_failure("Failed to set the secure socket connection over the open connection", true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }

        this->certificate = SSL_get_peer_certificate(this->secure_socket);
        if (not this->certificate) {
            (this->del_on_except) ? this->disconnect() : true;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::certificate_error("Failed to get the peer certificate", true, __FILE__, __LINE__ - 4, __FUNCTION__);
        }
        this->connected = true;
    }
    else {
        this->connected = valid_socket(this->connect_socket);
    }
    return this->connected;
}


bool networking::network_structures::tcp_client::disconnect() {
    if (valid_secure_socket(this->secure_socket)) {
        SSL_shutdown(this->secure_socket);
        close_socket(this->connect_socket);
        SSL_free(this->secure_socket);
        SSL_CTX_free(this->context);
        this->secure_socket = invalid_secure_socket;
        this->connect_socket = invalid_socket;
        this->context = invalid_context;
        (this->certificate) ? X509_free(this->certificate) : (void) 0;
        this->certificate = null;
        this->connected = false;
    }
    else {
        if (valid_socket(this->connect_socket)) {
            close_socket(this->connect_socket);
            this->connect_socket = invalid_socket;
            this->connected = false;
        }
    }
    this->bytes = -1;
    return this->connected;
}


networking::network_structures::connected_host::server networking::network_structures::tcp_client::get_server_connection() const {
    return {this->hostname, 
                this->portvalue, 
                        this->context, 
                        this->secure_socket, 
                            this->connect_socket, 
                                    this->connect_address};
}


bool networking::network_structures::tcp_client::server_has_message() {
    fd_set ready;
    FD_ZERO(&ready);
    FD_SET(this->connect_socket, &ready);

    if (select(this->connect_socket + 1, &ready, 0, 0, (this->timeout.tv_usec is -1) ? 0 : &this->timeout) < 0) {
        throw exceptions::select_failure("Failed to select for active sockets", true, __FILE__, __LINE__ - 1, __FUNCTION__);
    }
    return FD_ISSET(this->connect_socket, &ready);
}