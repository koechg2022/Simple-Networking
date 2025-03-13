




#include "../headers/included"
#include "networking"
#include "string_functions"
#include <filesystem>



/***********************************************************************************************/


/************************************ Networking Info funcs ************************************/


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


/***********************************************************************************************/



//                                             *



/************************************ Networking Exceptions ************************************/

networking::exceptions::base_exception::base_exception(const std::string name, const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) {
    this->except_name = name;
    this->message = msg;
    this->file = file_name;
    this->line = except_line;
    this->func = function;
    this->print_ = print;
    // if (print) {
    //     std::fprintf(stderr, "\"%s\" Thrown:\n%s:%s:line, %d:\n%s\n", this->except_name.c_str(), this->file.c_str(), this->func.c_str(), this->line, this->message.c_str());
    // }
}


networking::exceptions::base_exception::~base_exception() throw() {
    if (this->print_) {
        std::fprintf(stderr, "\"%s\" Thrown:\n%s:%s:line, %d:\n%s\n", this->except_name.c_str(), this->file.c_str(), this->func.c_str(), this->line, this->message.c_str());
    }
}

const std::string networking::exceptions::base_exception::msg() const {
    return "\"" + this->except_name + "\" Thrown:\n" + this->file + ":" + this->func + "line, " + std::to_string(this->line) + "\n" + this->message.c_str() + "\n";
}

const std::string networking::exceptions::base_exception::exception_type() const {
    return this->except_name;
}


networking::exceptions::unexpected_exception::unexpected_exception(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::unexpected_exception_type, msg, print, file_name, except_line, function) {}

networking::exceptions::memory_exception::memory_exception(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::memory_exception_type, msg, print, file_name, except_line, function) {}

networking::exceptions::initialize_network_failure::initialize_network_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::initialize_network_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::getaddrinfo_failure::getaddrinfo_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::getaddrinfo_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::getifaddrs_failure::getifaddrs_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::getifaddrs_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::create_socket_failure::create_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::create_socket_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::bind_socket_failure::bind_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::bind_socket_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::listen_socket_failure::listen_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::listen_socket_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::select_failure::select_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::select_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::getnameinfo_failure::getnameinfo_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::getnameinfo_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::connect_failure::connect_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::connect_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::certificate_or_key_error::certificate_or_key_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
    networking::exceptions::base_exception(networking::exceptions::certificate_or_key_error_type, msg, print, file_name, except_line, function) {}
        
networking::exceptions::secure_sockets_layer_error::secure_sockets_layer_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
    networking::exceptions::base_exception(networking::exceptions::secure_sockets_layer_error_type, msg, print, file_name, except_line, function) {}

networking::exceptions::certificate_error::certificate_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
    networking::exceptions::base_exception(networking::exceptions::certificate_error_type, msg, print, file_name, except_line, function) {}

networking::exceptions::accept_failure::accept_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
    networking::exceptions::base_exception(networking::exceptions::accept_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::create_context_failure::create_context_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
    networking::exceptions::base_exception(networking::exceptions::create_context_failure_type, msg, print, file_name, except_line, function) {}

networking::exceptions::socket_information_failure::socket_information_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
    networking::exceptions::base_exception(networking::exceptions::socket_information_failure_type, msg, print, file_name, except_line, function) {}


/***********************************************************************************************/



//                                             *



/************************************ Networking Functions ************************************/


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
    if (not networking::is_init_secure) {
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
        networking::is_init_secure = true;
    }
    return networking::is_init_secure;
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
    if (networking::is_init_secure) {
        OPENSSL_cleanup();
        networking::is_init_secure = false;
    }
    return not networking::is_init_secure;
}

std::vector<std::string> networking::resolve_hostname(const std::string hostname, const std::string port, const bool name) {
    
    bool was_init = is_init;

    if (not was_init) {
        if (not initialize_network()) {
            (networking::clean_on_except) ? uninitialize_network() : true;
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
        (networking::clean_on_except and not was_init) ? uninitialize_network() : true;
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
            (networking::clean_on_except) ? uninitialize_network() : true;
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
                (networking::clean_on_except) ? uninitialize_network() : true;
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
                (networking::clean_on_except) ? uninitialize_network() : true;
                ifaddrs_free_adapters(all_adapters);
                throw exceptions::unexpected_exception("An unexpected exception occured while trying to retrieve this machine's network adapter information", true, __FILE__, this_line, __FUNCTION__);
            }

        }

    #else

        if (getifaddrs(&all_adapters)) {
            (networking::clean_on_except) ? uninitialize_network() : true;
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

bool networking::socket_is_connected(const socket_type the_socket, const bool throw_except) {

    if (not valid_socket(the_socket)) {
        return false;
    }

    bool was_blocking = networking::socket_is_blocking(the_socket, throw_except);
    
    int retval = 0;

    #if defined(crap_os)
        u_long mode = 1;  // 1 to enable non-blocking socket
        ioctlsocket(the_socket, FIONBIO, &mode);
    #else
        int flags = fcntl(the_socket, F_GETFL, 0);
        fcntl(the_socket, F_SETFL, flags | O_NONBLOCK);
    #endif

    char buffer[1];
    int line_ = __LINE__ + 1;
    retval = recv(the_socket, buffer, 1, MSG_PEEK);

    if (not retval) {
        return false;  // Connection closed
    } 
    else if (retval < 0) {
        #if defined(crap_os)
            int error = 0;
            error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK) {
                if (was_blocking) {
                    networking::set_blocking(the_socket, false);
                }
                if (throw_except) {
                    std::string message = "Failed to retrieve socket connection information.";
                    throw networking::exceptions::socket_information_failure(message, true, __FILE__, line_, __FUNCTION__);
                }
                return false;  // Error occurred
            }
        #else
            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                if (was_blocking) {
                    networking::set_blocking(the_socket, false);
                }
                if (throw_except) {
                    std::string message = "Failed to retrieve socket connection information.";
                    throw networking::exceptions::socket_information_failure(message, true, __FILE__, line_, __FUNCTION__);
                }
                return false;  // Error occurred
            }
        #endif
    }

    if (was_blocking) {
        networking::set_blocking(the_socket, throw_except);
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

bool networking::socket_is_blocking(socket_type the_socket, const bool throw_except) {

    if (not valid_socket(the_socket)) {
        return false;
    }

    #if defined(crap_os)
        unsigned long mode = 0;
        if (not ioctlsocket(the_socket, FIONBIO, &mode)) {
            return mode == 0;
        }
    #else
        int flags = fcntl(the_socket, F_GETFL, 0);
        if (flags != -1) {
            return not (flags & O_NONBLOCK);
        }
    #endif
    if (throw_except) {
        throw networking::exceptions::socket_information_failure("Failed to retrieve socket information");
    }
    return false;
}

bool networking::set_non_blocking(socket_type the_socket, const bool throw_except) {

    if (not valid_socket(the_socket)) {
        return false;
    }

    if (not networking::socket_is_blocking(the_socket, throw_except)) {
        return true;
    }

    int line_;
    std::string message;

    #if defined(crap_os)
        unsigned long mode = 1; // to enable non-blocking mode
        line_ = __LINE__ + 1;
        if (ioctlsocket(the_socket, FIONBIO, &mode)) {
            message = "Failed to set the socket to non-blocking mode. Error " + 
                        std::to_string(socket_error) + " : " + 
                            std::string(get_socket_error_string(socket_error));
            if (throw_except) {
                throw networking::exceptions::socket_information_failure(message, true, __FILE__, line_, __FUNCTION__);
            }
            return false;
        }
    #else
        // Set the socket to non-blocking
        line_ = __LINE__ + 1;
        int flags = fcntl(the_socket, F_GETFL, 0);
        if (flags == -1) {
            message = "Failed to get socket flags on this Unix system. Error " + 
                    std::to_string(socket_error) + " : " +
                        std::string(get_socket_error_string(socket_error));
            if (throw_except) {
                throw networking::exceptions::socket_information_failure(message, true, __FILE__, line_, __FUNCTION__);
            }
            return false;
        }
        line_ = __LINE__ - 1;
        if (fcntl(the_socket, F_SETFL, flags | O_NONBLOCK) == -1) {
            message = "Failed to set the socket to non-blocking mode. Error " + 
                    std::to_string(socket_error) + " : " + 
                        std::string(get_socket_error_string(socket_error));
            if (throw_except) {
                throw networking::exceptions::socket_information_failure(message, true, __FILE__, line_, __FUNCTION__);
            }
            return false;
        }
    #endif

    return true;
}

bool networking::set_blocking(socket_type the_socket, const bool throw_except) {

    if (not valid_socket(the_socket)) {
        return false;
    }

    if (not socket_is_connected(the_socket)) {
        return false;
    }

    std::string message;
    int line_;

    #if defined(crap_os)
        unsigned long mode = 0; // set blocking
        line_ = __LINE__ + 1;
        if (ioctlsocket(the_socket ,FIONBIO, &mode)) {
            message = "Failed to set socket to blocking mode. Error " + 
                    std::to_string(socket_error) + " : " + 
                        std::string(get_socket_error_string(socket_error));
            if (throw_except) {
                throw networking::exceptions::socket_information_failure(message, true, __FILE__, line_, __FUNCTION__);
            }
            return false;
        }
    #else
        int flags = fcntl(the_socket, F_GETFL, 0);
        line_ = __LINE__ + 1;
        if (flags == -1) {
            message = "Failed to get socket flags. Error " + 
                std::to_string(socket_error) + " : " + 
                    std::string(get_socket_error_string(socket_error));
            if (throw_except) {
                throw networking::exceptions::socket_information_failure(message, true, __FILE__, line_, __FUNCTION__);
            }
            return false;
        }

        if (fcntl(the_socket, F_SETFL, flags & ~O_NONBLOCK) == -1) {
            message = "Failed to set socket to blocking mode. Error " + 
                std::to_string(socket_error) + " : " +
                    std::string(get_socket_error_string(socket_error));
            if (throw_except) {
                throw networking::exceptions::socket_information_failure(message, true, __FILE__, line_, __FUNCTION__);
            }
            return false;
        }
    #endif

    return true;
}

/***********************************************************************************************/



//                                             *



/***************************************** structures ******************************************/


bool networking::network_structures::connected_host::client_name::operator<(const client_name& other) const {
    return this->hostname < other.hostname and this->portvalue < other.portvalue;
}

bool networking::network_structures::connected_host::client_name::operator==(const networking::network_structures::connected_host::client_name& other) const {
    return string_functions::same_string(this->hostname, other.hostname) and string_functions::same_string(this->portvalue, other.portvalue);
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



//                                             *



/******** Host protected methods ********/


bool networking::network_structures::host::tcp() const {
    return this->tcp_;
}

networking::network_structures::host& networking::network_structures::host::tcp(const bool yes) {
    if (not this->main_socket_connected()) {
        this->tcp_ = yes;
    }
    return *this;
}

bool networking::network_structures::host::serve() const {
    return this->serving_;
}

networking::network_structures::host& networking::network_structures::host::serve(const bool yes) {
    if (not this->main_socket_connected()) {
        this->serving_ = yes;
    }
    return *this;
}

void networking::network_structures::host::next_address() {
    this->active_address_ = (this->active_address_) ? this->active_address_->ai_next : this->active_address_;
}

void networking::network_structures::host::reset_address() {
    this->active_address_ = this->connect_address_;
}

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
        this->reset_address();
    }
    return this->connect_address_;
}

bool networking::network_structures::host::create_connection_socket() {

    if (not valid_socket(this->connect_socket_)) {
        
        
        this->create_connection_address();
        
        
        if (not this->active_address_) {
            this->active_address_ = this->connect_address_;
        }
        
        std::string message = "Failed to create a valid socket for host \"" + this->host_ + "\"";
        int line_ = __LINE__ + 2;
        for (; this->active_address_; this->next_address()) {
            this->connect_socket_ = socket(this->active_address_->ai_family, this->active_address_->ai_socktype, this->active_address_->ai_protocol);
            if (valid_socket(this->connect_socket_)) {
                break;
            }
        }
        if (not this->active_address_) {
            line_ = line_ - 1;
            message = message + ". No more addresses to use for a socket connection";
        }
        
        if (not valid_socket(this->connect_socket_)) {
            throw exceptions::create_socket_failure(message + ". Error : " + std::string(get_socket_error_string(socket_error)), 
                                true, __FILE__, 
                                    line_, __FUNCTION__);
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
        this->connect_address_ = this->active_address_ = 0;
    }
    this->tcp_ = this->serving_ = this->print_except_ = true;

    return not this->connect_address_ && !valid_socket(this->connect_socket_);
}

bool networking::network_structures::host::main_socket_connected() const {
    return networking::socket_is_connected(this->connect_socket_);
}
/****** Host protected methods end ******/




//                *




/********** Host public methods **********/


// Default constructor
networking::network_structures::host::host() {
    // this->host_ = this->port_ = "";
    // this->connect_socket_ = invalid_socket;
    // this->tcp_ = true;
    // this->serving_ = true;
    // this->was_init_ = is_init;
    // this->connect_address_ = 0;
    // this->active_address_ = this->connect_address_;
}

// Parameter constructor
networking::network_structures::host::host(const std::string host_address, const std::string port, const bool use_tcp, const bool serving) {
    this->host_ = host_address;
    this->port_ = port;
    this->connect_socket_ = invalid_socket;
    this->tcp_ = use_tcp;
    this->serving_ = serving;
    this->was_init_ = is_init;
    this->connect_address_ = 0;
    this->active_address_ = this->connect_address_;
    this->print_except_ = true;
}

// Copy constructor
networking::network_structures::host::host(const networking::network_structures::host& other) {

    // Remove resources and close sockets for current host (nothing changes if no resources are set)
    // this->close_host();

    // Set new values from other.
    
    this->was_init_ = other.was_init_;
    this->hostname(other.host_).port(other.port_).tcp(other.tcp_).serve(other.serving_);
    this->connect_address_ = 0;
    this->print_except_ = other.print_except_;

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
            throw exceptions::getaddrinfo_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }
        this->create_connection_address();
    }

}

// Move constructor 
networking::network_structures::host::host(networking::network_structures::host&& other) noexcept{

    this->host_ = std::move(other.host_);
    this->port_ = std::move(other.port_);
    this->was_init_ = other.was_init_;
    this->tcp_ = other.tcp_;
    this->serving_ = other.serving_;
    this->connect_socket_ = other.connect_socket_;
    this->connect_address_ = other.connect_address_;
    other.connect_address_ = 0;
    this->print_except_ = other.print_except_;

    // Set other to default values as defined in default constructor
    other.connect_socket_ = invalid_socket;
    other.host_ = other.port_ = "";
    other.tcp_ = other.serving_ = true;
    other.print_except_ = true;
    other.was_init_ = is_init; // set to networking namespace's tracker of network is initialized (for windows)
}

// Destructor
networking::network_structures::host::~host() {
    this->close_host();
}

// Copy asignment operator
networking::network_structures::host& networking::network_structures::host::operator=(const networking::network_structures::host& other) {
    if (this != &other) {
        this->close_host();
        
        // Assignment of values
        this->host_ = other.host_;
        this->port_ = other.port_;
        this->tcp_ = other.tcp_;
        this->serving_ = other.serving_;
        this->was_init_ = other.was_init_;
        this->print_except_ = other.print_except_;

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
                throw exceptions::getaddrinfo_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
            }
            this->create_connection_address();
        }
    }
    return *this;
}

// Move assignment operator
networking::network_structures::host& networking::network_structures::host::operator=(networking::network_structures::host&& other) noexcept {
    if (this != &other) {
        this->close_host();

        this->host_ = std::move(other.host_);
        this->port_ = std::move(other.port_);
        this->tcp_ = other.tcp_;
        this->serving_ = other.serving_;
        this->was_init_ = other.was_init_;
        this->connect_socket_ = other.connect_socket_;
        this->connect_address_ = other.connect_address_;
        other.connect_address_ = 0;
        this->print_except_ = other.print_except_;

        // Set other to default values as defined in default constructor
        other.connect_socket_ = invalid_socket;
        other.host_ = other.port_ = "";
        other.tcp_ = other.serving_ = other.print_except_ = true;
        other.was_init_ = is_init; // set to networking namespace's tracker of network is initialized (for windows)
    }

    return *this;
}

// get_socket()
socket_type networking::network_structures::host::get_socket() const {
    return this->connect_socket_;
}

// hostname()
std::string networking::network_structures::host::hostname() const {
    return this->host_;
}

// hostname(const std::string new_host)
networking::network_structures::host& networking::network_structures::host::hostname(const std::string new_host) {
    if (not valid_socket(this->connect_socket_)) {
        this->host_ = new_host;
    }
    return *this;
}

// port()
std::string networking::network_structures::host::port() const {
    return this->port_;
}

// port(const std::string new_port)
networking::network_structures::host& networking::network_structures::host::port(const std::string new_port) {
    if (not valid_socket(this->connect_socket_)) {
        this->port_ = new_port;
    }
    return *this;
}

// retrieve_hostname()
networking::network_structures::host& networking::network_structures::host::retrieve_hostname(const std::set<std::string> adapter_name_options, const std::set<std::string> family_name_options) {

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

    return *this;
}


// blocking()
bool networking::network_structures::host::blocking() const {
    if (valid_socket(this->connect_socket_)) {
        if (networking::socket_is_connected(this->connect_socket_)) {
            return networking::socket_is_blocking(this->connect_socket_, false);
        }
    }
    return false;
}

// blocking(const bool block)
networking::network_structures::host& networking::network_structures::host::blocking(const bool block) {
    if (valid_socket(this->connect_socket_)) {
        if (networking::socket_is_connected(this->connect_socket_)) {
            bool blocking = networking::socket_is_blocking(this->connect_socket_, false);
            if (block and not blocking) {
                // set the socket to blocking
                
                networking::set_blocking(this->connect_socket_, false);
            }

            else if (not block and blocking) {
                // set the socket to non-blocking
                
                networking::set_non_blocking(this->connect_socket_, false);
            }
        }
    }
    return *this;
}

networking::network_structures::host& networking::network_structures::host::print_on_exceptions(const bool print) {
    this->print_except_ = print;
    return *this;
}

bool networking::network_structures::host::print_on_exceptions() const {
    return this->print_except_;
}

/******** Host public methods end ********/

/***********************************************************************************************/
/***************************************** TCP Server *****************************************/




/********* TCP Server private methods *********/



bool networking::network_structures::tcp_server::create_context() {
    if (this->secure_ and not valid_context(this->context_)) {

        // Initialize network 
        if (not networking::is_init) {
            if (not networking::initialize_network()) {
                return false;
            }
            this->was_init_ = false;
        }

        // Initialize secure library
        if (not networking::is_init_secure) {
            if (not networking::initialize_secure_network()) {
                return false;
            }
            this->secure_was_init_ = false;
        }

        // Create the context
        this->context_ = SSL_CTX_new(TLS_server_method());
    }
    return this->context_;
}

bool networking::network_structures::tcp_server::set_cert_and_key() {
    
    if (not this->certified_) {
        
        std::string message;
        const int count = 3;
        char msg[count * buffer_size];
        int line_;
        
        if (this->cert_file_.empty() or this->key_file_.empty()) {
            line_ = __LINE__ - 1;
            
            message = "No certificate or key file specified. Cannot " + 
                ((this->cert_file_.empty() and this->key_file_.empty()) ? 
                        std::string("create certificate and cannot create private key") : 
                        (this->cert_file_.empty()) ? 
                            std::string("create certificate") : 
                            std::string("create private key"));
            throw networking::exceptions::certificate_or_key_error(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        // There is a certificate file and there is a key file for both variables.
        // But do the files exist
        bool cert_exists_ = std::filesystem::exists(std::filesystem::path(this->cert_file_).lexically_normal());
        bool key_exists_ = std::filesystem::exists(std::filesystem::path(this->key_file_).lexically_normal());
        if (not cert_exists_ or not key_exists_) {
            line_ = __LINE__ - 1;
            // We have a problem
            message = (not cert_exists_) ? "Certification file \"" + this->cert_file_ + "\"" : "";
            
            if (message.empty()) {
                message = "Key file \"" + this->key_file_ + "\"";
            }
            else {
                message = message + "\nAnd key file \"" + this->key_file_ + "\"";
            }
            message = message + " not found.";
            throw networking::exceptions::certificate_or_key_error(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        // The certificate (proof of identity to client) exists.
        // The public key (used by the client to encrypt data) exists.
        if (not SSL_CTX_use_certificate_file(this->context_, this->cert_file_.c_str(), SSL_FILETYPE_PEM) or not SSL_CTX_use_PrivateKey_file(this->context_, this->key_file_.c_str(), SSL_FILETYPE_PEM)) {
            line_ = __LINE__ - 1;
            ERR_error_string_n(ERR_get_error(), msg, count * buffer_size);
            message = "Failed to create certificate and or key. Error \"" + std::string(msg) + "\"";
            throw networking::exceptions::certificate_or_key_error(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        this->certified_ = true;
    }
    
    return this->certified_;
}

/****** TCP Server private methods end ********/


//                *


/********* TCP Server public methods *********/


// Default Constructor
networking::network_structures::tcp_server::tcp_server() : 
    networking::network_structures::host::host("", DEFAULT_PORT, true, true) {
    // this->secure_ = this->certified_ = false;
    // this->max_socket_ = invalid_socket;
    // this->max_secure_ = invalid_secure_socket;
    // this->context_ = invalid_context;
    // this->key_file_ = this->cert_file_ = "";
    // this->secure_was_init_ = networking::is_init_secure;
    // this->block_clients_ = true;
    // this->listening_ = false;
}

// Parameter Constructor
networking::network_structures::tcp_server::tcp_server(const std::string hostname, const std::string port, const bool secure_server, const std::string key, const std::string cert) : 
    networking::network_structures::host::host(hostname, port, true, true) {
    this->secure_ = secure_server;
    this->max_socket_ = invalid_socket;
    this->max_secure_ = invalid_secure_socket;
    this->context_ = invalid_context;
    this->key_file_ = key;
    this->cert_file_ = cert;
    this->secure_was_init_ = networking::is_init_secure;
    this->block_clients_ = true;
    this->certified_ = false;
    this->listening_ = false;
    this->print_except_ = true;
}

// Copy Constructor
networking::network_structures::tcp_server::tcp_server(const networking::network_structures::tcp_server& other) :
    networking::network_structures::host(other) {
    
    if (this != &other) {

        // Set new values from other.
        this->secure_ = other.secure_;
        this->max_secure_ = other.max_secure_;
        this->max_socket_ = other.max_socket_;
        this->context_ = other.context_;
        this->key_file_ = other.key_file_;
        this->cert_file_ = other.cert_file_;
        this->secure_was_init_ = other.secure_was_init_;
        this->block_clients_ = other.block_clients_;
        this->certified_ = other.certified_;
        this->listening_ = other.listening_;
        this->print_except_ = other.print_except_;
        
        this->clients_ = other.clients_;
    }
    
}

// Move Constructor
networking::network_structures::tcp_server::tcp_server(networking::network_structures::tcp_server&& other) noexcept : 
networking::network_structures::host::host(std::move(other)) {
    
    if (this != &other) {
        
        // Set new values from other
        this->secure_ = other.secure_;
        this->max_secure_ = other.max_secure_;
        other.max_secure_ = invalid_secure_socket;
        this->max_socket_ = other.max_socket_;
        other.max_socket_ = invalid_socket;
        this->context_ = other.context_;
        other.context_ = invalid_context;
        this->key_file_ = std::move(other.key_file_);
        this->cert_file_ = std::move(other.cert_file_);
        this->clients_ = std::move(other.clients_);
        this->secure_was_init_ = other.secure_was_init_;
        this->block_clients_ = other.block_clients_;
        this->certified_ = other.certified_;
        this->listening_ = other.listening_;
        this->print_except_ = other.print_except_;

        // Set other to default values as defined in default constructor
        other.secure_ = false;
        other.certified_ = false;
        other.block_clients_ = true;
        other.key_file_.clear();
        other.cert_file_.clear();
        other.listening_ = false;

        // In question
        other.clients_.clear();
        other.secure_was_init_ = networking::is_init_secure;
    }
}

// Destructor
networking::network_structures::tcp_server::~tcp_server() {
    this->close_server();
}

// Copy assignment 
networking::network_structures::tcp_server& networking::network_structures::tcp_server::operator=(const networking::network_structures::tcp_server& other) {
    if (this != &other) {
        this->close_server();

        // Set new values from other.
        this->secure_ = other.secure_;
        this->max_secure_ = other.max_secure_;
        this->max_socket_ = other.max_socket_;
        this->context_ = other.context_;
        this->key_file_ = other.key_file_;
        this->cert_file_ = other.cert_file_;
        this->secure_was_init_ = other.secure_was_init_;
        this->block_clients_ = other.block_clients_;
        this->certified_ = other.certified_;
        this->listening_ = other.listening_;
        this->print_except_ = other.print_except_;
        
        this->clients_ = other.clients_;
    }
    return *this;
}

// Move assigment
networking::network_structures::tcp_server& networking::network_structures::tcp_server::operator=(networking::network_structures::tcp_server&& other) noexcept {
    if (this != &other) {
        this->close_server();
        
        // Set new values from other
        this->secure_ = other.secure_;
        this->max_secure_ = other.max_secure_;
        other.max_secure_ = invalid_secure_socket;
        this->max_socket_ = other.max_socket_;
        other.max_socket_ = invalid_socket;
        this->context_ = other.context_;
        other.context_ = invalid_context;
        this->key_file_ = std::move(other.key_file_);
        this->cert_file_ = std::move(other.cert_file_);
        this->clients_ = std::move(other.clients_);
        this->secure_was_init_ = other.secure_was_init_;
        this->block_clients_ = other.block_clients_;
        this->certified_ = other.certified_;
        this->listening_ = other.listening_;
        this->print_except_ = other.print_except_;

        // Set other to default values as defined in default constructor
        other.secure_ = false;
        other.certified_ = false;
        other.listening_ = false;
        other.block_clients_ = true;
        other.print_except_ = true;
        other.key_file_.clear();
        other.cert_file_.clear();

        // In question
        other.clients_.clear();
        other.secure_was_init_ = networking::is_init_secure;

    }
    return *this;
}

// operator bool() const
networking::network_structures::tcp_server::operator bool() const {
    return (this->secure_) ? (valid_context(this->context_) and this->listening_) : this->listening_;
}

// secure()
bool networking::network_structures::tcp_server::secure() const {
    return this->secure_;
}

// secure(const bool set_secure)
networking::network_structures::tcp_server& networking::network_structures::tcp_server::secure(const bool set_secure) {
    if (not *this) {
        this->secure_ = set_secure;
    }
    return *this;
}

// key();
std::string networking::network_structures::tcp_server::key() const {
    return this->key_file_;
}

// key(const std::string new_key)
networking::network_structures::tcp_server& networking::network_structures::tcp_server::key(const std::string new_key) {
    if (not *this) {
        this->key_file_ = new_key;
    }
    return *this;
}

// cert()
std::string networking::network_structures::tcp_server::cert() const {
    return this->cert_file_;
}

// cert(const std::string new_cert)
networking::network_structures::tcp_server& networking::network_structures::tcp_server::cert(const std::string new_cert) {
    if (not *this) {
        this->cert_file_ = new_cert;
    }
    return *this;
}

// client_has_data(client&, struct timeval)
bool networking::network_structures::tcp_server::client_has_data(networking::network_structures::connected_host::client& client, struct timeval timeout) {
    
    if (not networking::socket_is_connected(client.connected_socket)) {
        return false;
    }

    fd_set ready;
    FD_ZERO(&ready);
    FD_SET(client.connected_socket, &ready);

    if (select(client.connected_socket + 1, &ready, 0, 0, &timeout) < 0) {
        throw exceptions::select_failure("Failed to select for client's connection socket. Error " + std::to_string(socket_error) + " : " + std::string(get_socket_error_string(socket_error)), true, __FILE__, __LINE__ - 1, __FUNCTION__);
    }

    return FD_ISSET(client.connected_socket, &ready);
}

// disconnect_client(const client& client, const bool update_max)
networking::network_structures::tcp_server& networking::network_structures::tcp_server::disconnect_client(const networking::network_structures::connected_host::client& client, const bool update_max) {
    networking::network_structures::connected_host::client_name name = {client.hostname, client.portvalue};
    return this->disconnect_client(name, update_max);
}

// disconnect_client(const client_name& client_name, const bool update_max)
networking::network_structures::tcp_server& networking::network_structures::tcp_server::disconnect_client(const networking::network_structures::connected_host::client_name& client_name, const bool update_max) {
    /*  
    Not secure:
        1.) Close the connection socket
        2.) Remove client from clients map. -
        3.) Update max_socket. -

    Secure:
        1.) SSL_shutdown of client's secure socket.
        2.) close client's non-secure socket.
        3.) SSL free client's secure socket.
        4.) Remove client from clients map. -
        5.) Update max socket (non-secure) and max secure socket -
    */ 

    
    // Lookup should be O(1) - unordered_map.
    if (this->clients_.contains(client_name)) {
        
        network_structures::connected_host::client client = this->clients_[client_name];
        
        // For whether or not to update the max sockets
        bool non_secure, yes_secure;
        if (update_max) {
            non_secure = (this->max_socket_ == client.connected_socket);
            yes_secure = (this->max_secure_ == client.secure_socket);
        }
        
        // Close connection (secure or non-secure)
        (this->secure_) ? SSL_shutdown(client.secure_socket) : 0;
        close_socket(client.connected_socket);
        (this->secure_) ? SSL_free(client.secure_socket) : (void) 0;

        // Connection is undone


        // Update internal management now.
        // First remove client
        this->clients_.erase(client_name);

        if (update_max) {
            
            // Now update max(es). Crap OS deals with unsigned ints, and unix deals with regular ints.
            // Work around it to set each to the first client's socket.
            
            this->max_socket_ = (non_secure) ? this->clients_.begin()->second.connected_socket : this->max_socket_;

            this->max_secure_ = (yes_secure) ? this->clients_.begin()->second.secure_socket : this->max_secure_;
            

            if (not this->clients_.empty()) {
                if (non_secure) {
                    // Update max non-secure socket
                    for (auto& this_client : this->clients_) {
                        this->max_socket_ = (this_client.second.connected_socket > this->max_socket_) ? this_client.second.connected_socket : this->max_socket_;
                    }
                }

            
                if (yes_secure) {
                    // Update max secure socket
                    for (auto& this_client : this->clients_) {
                        this->max_secure_ = (this_client.second.secure_socket > this->max_secure_) ? this_client.second.secure_socket : this->max_secure_;
                    }
                }
            }
        }

    }

    return *this;
    
}

// disconnect_client(const std::string name, const std::string port, const bool update_max)
networking::network_structures::tcp_server& networking::network_structures::tcp_server::disconnect_client(const std::string name, const std::string port, const bool update_max) {
    // const networking::network_structures::connected_host::client_name names = {name, port};
    return this->disconnect_client((const networking::network_structures::connected_host::client_name) {name, port}, update_max);
}

// new_client(struct timeval timeout)
networking::network_structures::connected_host::client networking::network_structures::tcp_server::new_client(struct timeval timeout) {
    

    if (not *this) {
        int line_ = __LINE__ - 1;
        std::string message = "Server is not listening...";
        throw networking::exceptions::listen_socket_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
    }
    networking::network_structures::connected_host::client the_answer;
    fd_set ready;
    FD_ZERO(&ready);
    FD_SET(this->connect_socket_, &ready);

    if (select(this->connect_socket_ + 1, &ready, 0, 0, &timeout) < 0) {
        throw networking::exceptions::select_failure("Failed to select for server's actively listening socket. Error " + std::to_string(socket_error) + " : " + std::string(get_socket_error_string(socket_error)), true, __FILE__, __LINE__ - 1, __FUNCTION__);
    }

    if (FD_ISSET(this->connect_socket_, &ready)) {
        // There is a new connection request
        int line_;
        the_answer.address_size = sizeof(the_answer.address_info);

        line_ = __LINE__ + 1;
        the_answer.connected_socket = accept(this->connect_socket_, (struct sockaddr*) &the_answer.address_info, &the_answer.address_size);
        the_answer.connection_time = misc_functions::get_current_time();

        if (not valid_socket(the_answer.connected_socket)) {
            throw networking::exceptions::accept_failure("Failed to accept a new incomming connection. Error " + std::to_string(socket_error) + std::string(get_socket_error_string(socket_error)), true, __FILE__, line_, __FUNCTION__);
        }

        // The connection has been made
        char address_buffer[buffer_size], port_buffer[buffer_size];
        std::memset(address_buffer, 0, buffer_size); std::memset(port_buffer, 0, buffer_size);
        
        line_ = __LINE__ + 1;
        if (getnameinfo((struct sockaddr*) &the_answer.address_info, the_answer.address_size, address_buffer, buffer_size, port_buffer, buffer_size, NI_NUMERICHOST | NI_NUMERICSERV)) {
            
            if (getnameinfo((struct sockaddr*) &the_answer.address_info, the_answer.address_size, address_buffer, buffer_size, port_buffer, buffer_size, NI_NAMEREQD | AI_ALL)) {
                throw networking::exceptions::getnameinfo_failure("Failed to retrieve client's name and or client's port number. All is necessary information. Error " + std::to_string(socket_error) + " : " + std::string(get_socket_error_string(socket_error)), true, __FILE__, line_, __FUNCTION__);
            }
            the_answer.hostname = std::string(address_buffer);
            the_answer.portvalue = std::string(port_buffer);
        }
        else {
            the_answer.hostname = std::string(address_buffer);
            the_answer.portvalue = std::string(port_buffer);
        }

        // Have the hostname and portvalues
        // Now for the secure connection
        if (this->secure_) {
            std::string message;
            const int space = 3 * buffer_size;
            char buffer[space];

            ERR_clear_error();
            line_ = __LINE__ + 1;
            the_answer.secure_socket = SSL_new(this->context_);
            
            if (not valid_secure_socket(the_answer.secure_socket)) {
                ERR_error_string_n(ERR_get_error(), buffer, space);
                message = "Failed to create a secure socket for communication with \"" + 
                            the_answer.hostname + "\" : " + std::string(buffer);
                throw networking::exceptions::secure_sockets_layer_error(message, this->print_except_, __FILE__, line_, __FUNCTION__);
            }

            ERR_clear_error();
            line_ = __LINE__ + 1;
            if (not SSL_set_fd(the_answer.secure_socket, the_answer.connected_socket)) {
                SSL_shutdown(the_answer.secure_socket);
                close_socket(the_answer.connected_socket);
                SSL_free(the_answer.secure_socket);
                ERR_error_string_n(ERR_get_error(), buffer, space);
                message = "Failed to set the connection socket as the TLS/SSL endpoint. Error - " + std::string(buffer);
                throw networking::exceptions::secure_sockets_layer_error(message, this->print_except_, __FILE__, line_, __FUNCTION__);
            }

            // int secure_accept = SSL_accept(the_answer.secure_socket);

            ERR_clear_error();
            line_ = __LINE__ + 1;
            if (SSL_accept(the_answer.secure_socket) != 1) {
                
                SSL_shutdown(the_answer.secure_socket);
                close_socket(the_answer.connected_socket);
                SSL_free(the_answer.secure_socket);
                ERR_error_string_n(ERR_get_error(), buffer, space);
                message = "Failed to accept new secure TLS/SSL connection. Error - " + std::string(buffer);
                throw networking::exceptions::secure_sockets_layer_error(message, this->print_except_, __FILE__, line_, __FUNCTION__);
            }

            this->max_secure_ = (the_answer.secure_socket > this->max_secure_) ? the_answer.secure_socket : this->max_secure_;
        }

        this->max_socket_ = (the_answer.connected_socket > this->max_socket_) ? the_answer.connected_socket : this->max_socket_;

    }

    return the_answer;
}

// clients_with_data()
std::vector<networking::network_structures::connected_host::client> networking::network_structures::tcp_server::clients_with_data() {
    
    std::vector<networking::network_structures::connected_host::client> the_answer;
    

    std::vector<networking::network_structures::connected_host::client_name> to_remove;
    
    if (this->clients_.size() < FD_SETSIZE) {
        // Use select because there is a managable amout of sockets to deal with.
        
        fd_set ready;
        FD_ZERO(&ready);
        for (const auto& client : this->clients_) {
            if (not networking::socket_is_connected(client.second.connected_socket)) {
                to_remove.emplace_back(client.first);
                continue;
            }
            
            // client is still connected
            FD_SET(client.second.connected_socket, &ready);
        }

        // ready has all the clients that have data to be read
        for (const auto& client : this->clients_) {
            if (FD_ISSET(client.second.connected_socket, &ready)) {
                the_answer.emplace_back(client.second);
            }
        }
    }

    else {
        // There are a lot of clients connected. Best to use poll
        int ready;
        std::vector<pollfd> check_polls;
        std::unordered_map<socket_type, networking::network_structures::connected_host::client_name> to_check;

        for (const auto& client : this->clients_) {
            if (not networking::socket_is_connected(client.second.connected_socket)) {
                to_remove.emplace_back(client.first);
                continue;
            }
            pollfd this_poll = {client.second.connected_socket, POLLIN, 0};
            check_polls.emplace_back(this_poll);
            to_check.insert({client.second.connected_socket, client.first});
        }

        #if defined(crap_os)
            int line_ = __LINE__ + 1;
            ready = WSAPoll(check_polls.data(), check_polls.size(), 0);
        #else
            int line_ = __LINE__ + 1;
            ready = poll(check_polls.data(), check_polls.size(), 0);
        #endif

        if (ready < 0) {
            std::string message = "Failed to select for ready socket with poll(). Error " + 
                            std::to_string(socket_error) + 
                                " : " + std::string(get_socket_error_string(socket_error));
            throw networking::exceptions::select_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        for (const auto& sock : check_polls) {
            
            // Does the socket have data to read?
            if (sock.revents & POLLIN) {
                the_answer.emplace_back(this->clients_[to_check[sock.fd]]);
            }
        }
        
    }

    for (const auto& remove : to_remove) {
        this->clients_.erase(remove);
    }

    return the_answer;
}

// all_clients()
std::vector<networking::network_structures::connected_host::client> networking::network_structures::tcp_server::all_clients() {
    std::vector<networking::network_structures::connected_host::client> the_answer;
    for (const auto& client : this->clients_) {
        the_answer.emplace_back(client.second);
    }

    return the_answer;
}

// update()
networking::network_structures::tcp_server& networking::network_structures::tcp_server::update(const bool reuse) {
    
    std::vector<networking::network_structures::connected_host::client> to_remove;
    int line_ = reuse;
    std::string message;
    #if defined(unix_os)
        int set_ = reuse;
    #else
        char set_ = 0;
    #endif

    // Set the listening socket to reuse or non-reuse, depending on reuse parameter
    if (setsockopt(this->connect_socket_, SOL_SOCKET, SO_REUSEADDR, &set_, sizeof(set_)) < 0) {
        line_ = __LINE__ - 1;
        message = "Failed to set connection socket address to " + 
                ((reuse) ? std::string("reuse") : std::string("non-reuse")) + 
                    "Error " + std::to_string(socket_error) + " : " +
                        std::string(get_socket_error_string(socket_error));
        throw networking::exceptions::socket_information_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
    }


    for (const auto& client : this->clients_) {
        if (not networking::socket_is_connected(client.second.connected_socket, false)) {
            to_remove.emplace_back(client.second);
            continue;
        }

        if (this->secure_ and not valid_secure_socket(client.second.secure_socket)) {
            to_remove.emplace_back(client.second);
            continue;
        }
    }


    for (const auto& client : to_remove) {
        (this->secure_ and valid_secure_socket(client.secure_socket)) ? SSL_shutdown(client.secure_socket) : 0;
        (valid_socket(client.connected_socket)) ? close_socket(client.connected_socket) : 0;
        (this->secure_ and valid_secure_socket(client.secure_socket)) ? SSL_free(client.secure_socket) : (void) 0;
        this->clients_.erase({client.hostname, client.portvalue});
    }

    this->max_socket_ = (this->clients_.empty()) ? invalid_socket : this->clients_.begin()->second.connected_socket;
    this->max_secure_ = (this->secure_ and this->clients_.empty()) ? invalid_secure_socket : this->clients_.begin()->second.secure_socket;

    for (const auto& client : this->clients_) {
        this->max_socket_ = (client.second.connected_socket > this->max_socket_) ? client.second.connected_socket : this->max_socket_;
        this->max_secure_ = (client.second.secure_socket > this->max_secure_) ? client.second.secure_socket : this->max_secure_;
    }

    return *this;
}

// run(bool reuse)
networking::network_structures::tcp_server& networking::network_structures::tcp_server::run(const int listen_limit, const bool reuse, const bool block) {

    if (not *this) {
        std::string message;
        int line_;
        const int count = 3;
        char msg[count * buffer_size];
        if (listen_limit <= 0) {
            line_ = __LINE__ - 1;
            message = "Illegal listen_limit. Cannot have a listening limit less than 1. The listening socket needs to be able to listen to at least one client.";
            throw networking::exceptions::listen_socket_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        if (not networking::is_init) {
            if (not networking::initialize_network()) {
                line_ = __LINE__ - 1;
                message = "Failed to initialize network... Windows really sucks. Error " + 
                    std::to_string(socket_error) + 
                        " : " + std::string(get_socket_error_string(socket_error));
                throw networking::exceptions::initialize_network_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
            }
        }

        if (this->secure_) {
            ERR_clear_error();
        }
        
        if (this->secure_ and not networking::is_init_secure) {
            if (not networking::initialize_secure_network()) {
                line_ = __LINE__ - 1;
                ERR_error_string_n(ERR_get_error(), msg, count * buffer_size);
                message = "Failed to initialize secure network. Error \"" + std::string(msg) + "\"";
                throw networking::exceptions::initialize_network_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
            }
            this->secure_was_init_ = false;
        }

        if (this->secure_ and not valid_context(this->context_)) {
            
            if (not this->create_context()) {
                line_ = __LINE__ - 1;
                ERR_error_string_n(ERR_get_error(), msg, count * buffer_size);
                message = "Failed to create server context. Error \"" + std::string(msg) + "\"";
                throw networking::exceptions::create_context_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
            }
            // The context exists now
        }

        // std::cout << "Reached right before certificate check" << std::endl;
        if (this->secure_ and not this->certified_) {
            if (not this->set_cert_and_key()) {
                line_ = __LINE__ - 1;
                ERR_error_string_n(ERR_get_error(), msg, count * buffer_size);
                message = "Failed to create certificate and private key for communication with clients. Error \"" +
                    std::string(msg) + "\"";
                throw networking::exceptions::certificate_or_key_error(message, this->print_except_, __FILE__, line_, __FUNCTION__);
            }
            // Certified.
        }


        // Presteps for the secure are done.
        // Now for connection socket.

        if (not this->create_connection_address()) {
            line_ = __LINE__ - 1;
            message = "Failed to retrieve connection address information. Error " +
                std::to_string(socket_error) + " : " + std::string(get_socket_error_string(socket_error));
            throw networking::exceptions::getaddrinfo_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        // std::cout << "Successfully created connection address" << std::endl;
        // addrinfo pointer points to actual data.
        if (not this->create_connection_socket()) {
            line_ = __LINE__ - 1;
            message = "Failed to create listening socket for server \"" + 
                    this->host_ + "\" on port \"" + this->port_ + "\". Error " + 
                        std::to_string(socket_error) + " : " +
                            std::string(get_socket_error_string(socket_error));
            throw networking::exceptions::create_socket_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        // Redundant check
        if (not valid_socket(this->connect_socket_)) {
            line_ = __LINE__ - 1;
            message = "Failed to create listening socket for server \"" + 
                    this->host_ + "\" on port \"" + this->port_ + "\". Error " + 
                        std::to_string(socket_error) + " : " +
                            std::string(get_socket_error_string(socket_error));
            throw networking::exceptions::create_socket_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        // std::cout << "Successfully created connection socket " << std::endl;
        // Settings for the listening socket.
        // Setting the listening socket to reuse or not
        #if defined(unix_os)
            int sock_setting = reuse;
        #else
            char sock_setting = reuse;
        #endif
        
        if (setsockopt(this->connect_socket_, SOL_SOCKET, SO_REUSEADDR, &sock_setting, sizeof(sock_setting)) < 0) {
            line_ = __LINE__ - 1;
            message = "Failed to set the listening socket to " + std::string((reuse) ? "Reuse" : "Non-reuse") + ". Error " +
                    std::to_string(socket_error) + " : " + std::string(get_socket_error_string(socket_error));
            throw networking::exceptions::socket_information_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        // Iterated through all the address options and created a listening socket with the address
        // in this->active_address_

        // Now bind the socket
        if (bind(this->connect_socket_, this->active_address_->ai_addr, this->active_address_->ai_addrlen)) {
            line_ = __LINE__ - 1;
            message = "Failed to bind the listening socket for server \"" +
                this->host_ + "\" on port \"" + this->port_ + "\". Error " +
                    std::to_string(socket_error) + " : " +
                        std::string(get_socket_error_string(socket_error));
            throw networking::exceptions::bind_socket_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }

        // Socket is bound. Now start listening.
        if (listen(this->connect_socket_, listen_limit) < 0) {
            line_ = __LINE__ - 1;
            message = "Failed to start listening on new socket created for server \"" +
                this->host_ + "\" on port \"" + this->port_ + "\". Error " +
                    std::to_string(socket_error) + " : " +
                        std::string(get_socket_error_string(socket_error));
            throw networking::exceptions::listen_socket_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
        }
        this->listening_ = true;

        // Socket is now listening.
        // Also secure connection is listening.
        this->block_clients_ = block;
    }
    return *this;
}

// close_server()
networking::network_structures::tcp_server& networking::network_structures::tcp_server::close_server() {
    
    // First disconnect all clients
    for (auto client : this->clients_) {
        this->disconnect_client(client.first, false); // Save on execution time
    }

    // CLose the main non-secure connection
    this->close_host();
    
    // Close the secore connection
    (this->secure_ and this->context_) ? SSL_CTX_free(this->context_) : (void) 0;
    (not this->secure_was_init_) ? networking::uninitialize_secure_network() : true;
    this->listening_ = false;
    // std::cout << "Calling close_server()" << std::endl;
    return *this;
}

// block_clients(const bool block)
networking::network_structures::tcp_server& networking::network_structures::tcp_server::block_clients(const bool block) {
    

    if (this->block_clients_ != block) {
        std::string message;
        int line_;
        for (const auto& client : this->clients_) {
            if (not ((block) ? networking::set_blocking(client.second.connected_socket) : networking::set_non_blocking(client.second.connected_socket))) {
                line_ = __LINE__ - 1;
                message = "Failed to set client \"" + client.first.hostname + "\" to " + std::string((block) ? "blocking." : "non-blocking.");
                throw networking::exceptions::socket_information_failure(message, this->print_except_, __FILE__, line_, __FUNCTION__);
            }
        }
        this->block_clients_ = block;
    }
    
    return *this;
}


bool networking::network_structures::tcp_server::block_clients() const {
    return this->block_clients_;
}


networking::network_structures::tcp_server& networking::network_structures::tcp_server::blocking(const bool block) {
    networking::network_structures::host::blocking(block);
    return *this;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::print_exceptions(const bool print_except) {
    this->print_except_ = print_except;
    return *this;
}

/***** TCP Server public methods end *********/



/************************************* TCP Server END *****************************************/
/***********************************************************************************************/