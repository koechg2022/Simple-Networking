




#include "../headers/included"
#include "string_functions"
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



bool networking::network_structures::host::create_connection_address() {
    
    if (not this->connect_address_) {
        if (not is_init) {
            initialize_network();
            this->was_init_ = false;
        }
        if (this->host_.empty()) {
            throw exceptions::getaddrinfo_failure("Cannot retrieve address information without a hostname specified", true, __FILE__, __LINE__ - 1, __FUNCTION__);
        }
        if (this->port_.empty()) {
            throw exceptions::getaddrinfo_failure("Cannot retrieve address information without a port", true, __FILE__, __LINE__ - 1, __FUNCTION__);
        }

        
        // Setting up to call getaddrinfo
        struct addrinfo hints;
        std::memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC; //(is_ipstring(this->host_)) ? AF_INET : (is_ipstring(this->host_, false)) ? AF_INET6 : AF_UNSPEC;
        hints.ai_socktype = (this->tcp_) ? SOCK_STREAM : SOCK_DGRAM;
        hints.ai_flags = (this->serving_) ? AI_PASSIVE : 0;

        // Ready to call getaddrinfo
        
        int status = getaddrinfo(this->host_.c_str(), this->port_.c_str(), &hints, &this->connect_address_);
        
        if (status) {
            throw exceptions::getaddrinfo_failure("Failed to retrieve address information for host \"" + this->host_ + "\". Error " + std::string(get_socket_error_string(status)), true, __FILE__, __LINE__ - 1, __FUNCTION__);
        }
        
    }
    return this->connect_address_;
}

bool networking::network_structures::host::create_connection_socket() {

    if (not valid_socket(this->connect_socket_)) {
        
        this->create_connection_address();
        
        this->connect_socket_ = socket(this->connect_address_->ai_family, 
                                this->connect_address_->ai_socktype, 
                                    this->connect_address_->ai_protocol);
        if (not valid_socket(this->connect_socket_)) {
            throw exceptions::create_socket_failure("Failed to create socket for host \"" + 
                        this->host_ + "\". Error " + std::string(get_socket_error_string(socket_error)), 
                                true, __FILE__, 
                                    __LINE__ - 1, __FUNCTION__);
        }
    }

    return valid_socket(this->connect_socket_);
}

bool networking::network_structures::host::close_host() {

    if (valid_socket(this->connect_socket_)) {
        close_socket(this->connect_socket_);  // Close the socket
        this->connect_socket_ = invalid_socket;  // Mark socket as invalid
    }

    if (not this->was_init_) {
        uninitialize_network();
    }

    if (this->connect_address_) {
        freeaddrinfo(this->connect_address_);
        this->connect_address_ = 0;
    }

    return not this->connect_address_ && !valid_socket(this->connect_socket_);
}

networking::network_structures::host::host() {
    this->host_ = this->port_ = "";
    this->connect_socket_ = invalid_socket;
    this->tcp_ = true;
    this->serving_ = true;
    this->was_init_ = is_init;
    this->connect_address_ = 0;
}

networking::network_structures::host::host(const std::string host_address, const std::string port, const bool use_tcp, const bool serving) {
    this->host_ = host_address;
    this->port_ = port;
    this->connect_socket_ = invalid_socket;
    this->tcp_ = use_tcp;
    this->serving_ = serving;
    this->was_init_ = is_init;
    this->connect_address_ = 0;
}

networking::network_structures::host::host(const networking::network_structures::host& other) {

    this->host_ = other.host_;
    this->port_ = other.port_;
    this->tcp_ = other.tcp_;
    this->serving_ = other.serving_;
    this->was_init_ = other.was_init_;
    this->connect_address_ = 0;

    if (other.connect_address_) {
        if (this->host_.empty() or this->port_.empty()) {
            int line_ = __LINE__ - 1;
            std::string message = "Cannot retrieve address information. Missing ";
            if (this->host_.empty() and not this->port_.empty()) {
                line_ = __LINE__ - 1;
                message = message + "hostname";
            }
            else if (not this->host_.empty() and this->port_.empty()) {
                line_ = __LINE__ - 1;
                message = message + "port";
            }
            else {
                message = message + "hostname and port";
            }
            throw exceptions::getaddrinfo_failure(message, true, __FILE__, line_, __FUNCTION__);
        }
        this->create_connection_address();
    }

}

networking::network_structures::host::~host() {
    this->close_host();
}

networking::network_structures::host& networking::network_structures::host::operator=(const networking::network_structures::host& other) {
    if (this != &other) {
        this->close_host();
        this->host_ = other.host_;
        this->port_ = other.port_;
        this->tcp_ = other.tcp_;
        this->serving_ = other.serving_;
        this->was_init_ = other.was_init_;

        if (other.connect_address_) {
            if (this->host_.empty() or this->port_.empty()) {
                int line_ = __LINE__ - 1;
                std::string message = "Cannot retrieve address information. Missing ";
                if (this->host_.empty() and not this->port_.empty()) {
                    line_ = __LINE__ - 1;
                    message = message + "hostname";
                }
                else if (not this->host_.empty() and this->port_.empty()) {
                    line_ = __LINE__ - 1;
                    message = message + "port";
                }
                else {
                    message = message + "hostname and port";
                }
                throw exceptions::getaddrinfo_failure(message, true, __FILE__, line_, __FUNCTION__);
            }
            this->create_connection_address();
        }
    }
    return *this;
}

socket_type networking::network_structures::host::get_socket() const {
    return this->connect_socket_;
}

bool networking::network_structures::host::retrieve_hostname(const std::set<std::string> adapter_name_options, const std::set<std::string> family_name_options) {

    if (this->host_.empty()) {
        std::map<std::string, std::map<std::string, std::vector<std::string > > > adapters = this_machine_adapters();
        std::string adapter_name = "", adapter_family = "";
        
        for (const std::string& name : adapter_name_options) {
            if (string_functions::contains(adapters, name)) {
                adapter_name = name;
                break;
            }
        }

        // std::cout << "adapter_name is now : " << adapter_name << std::endl;

        if (not adapter_name.empty()) {
            for (const std::string& name : family_name_options) {
                if (string_functions::contains(adapters[adapter_name], name)) {
                    adapter_family = name;
                    break;
                }
            }
        }

        // std::cout << "adapter_family is now " << adapter_family << std::endl;

        if (not adapter_family.empty()) {
            for (const std::string& name : adapters[adapter_name][adapter_family]) {
                if (name.empty()) {
                    continue;
                }
                this->host_ = name;
                break;
            }
        }

        if (this->host_.empty()) {
            this->host_ = DEFAULT_HOST;
        }

    }

    return not this->host_.empty();
}

std::string networking::network_structures::host::hostname() const {
    return this->host_;
}

networking::network_structures::host& networking::network_structures::host::hostname(const std::string new_host) {
    if (not valid_socket(this->connect_socket_)) {
        this->host_ = new_host;
    }
    return *this;
}

std::string networking::network_structures::host::port() const {
    return this->port_;
}

networking::network_structures::host& networking::network_structures::host::port(const std::string new_port) {
    if (not valid_socket(this->connect_socket_)) {
        this->port_ = new_port;
    }
    return *this;
}