



#include "networking.h++"









namespace networking {
    
    
    namespace network_address_families {

        std::set<std::string> get_address_families() {
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

        std::string resolve_address_family_to_string(socket_family_type the_family) {
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

    }

    namespace exceptions {

        base_exception::base_exception(const std::string name, const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) {
            this->except_name = name;
            this->message = msg;
            this->file = file_name;
            this->line = except_line;
            this->func = function;
            if (print) {
                std::fprintf(stderr, "\"%s\" Thrown:\n%s:%s:line, %d:\n%s\n", this->except_name.c_str(), this->file.c_str(), this->func.c_str(), this->line, this->message.c_str());
            }
        }

        base_exception::~base_exception() throw() {}

        const std::string base_exception::msg() const {
            return "\"" + this->except_name + "\" Thrown:\n" + this->file + ":" + this->func + "line, " + std::to_string(this->line) + "\n" + this->message.c_str() + "\n";
        }
        

        unexpected_exception::unexpected_exception(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("unexpected_exception", msg, print, file_name, except_line, function) {}

        memory_exception::memory_exception(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("memory_exception", msg, print, file_name, except_line, function) {}

        initialize_network_failure::initialize_network_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("initialize_network_failure", msg, print, file_name, except_line, function) {}

        getaddrinfo_failure::getaddrinfo_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("getaddrinfo_failure", msg, print, file_name, except_line, function) {}

        getifaddrs_failure::getifaddrs_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("getifaddrs_failure", msg, print, file_name, except_line, function) {}

        create_socket_failure::create_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("create_socket_failure", msg, print, file_name, except_line, function) {}

        bind_socket_failure::bind_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("bind_socket_failure", msg, print, file_name, except_line, function) {}

        listen_socket_failure::listen_socket_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("listen_socket_failure", msg, print, file_name, except_line, function) {}

        select_failure::select_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("select_failure", msg, print, file_name, except_line, function) {}

        getnameinfo_failure::getnameinfo_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("getnameinfo_failure", msg, print, file_name, except_line, function) {}

        connect_failure::connect_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("connect_failure", msg, print, file_name, except_line, function) {}

        certificate_or_key_error::certificate_or_key_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) : 
            base_exception("certificate_or_key_error", msg, print, file_name, except_line, function) {}
        
        secure_sockets_layer_error::secure_sockets_layer_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
            base_exception("secure_sockets_layer_error", msg, print, file_name, except_line, function) {}

        certificate_error::certificate_error(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
            base_exception("certificate_error", msg, print, file_name, except_line, function) {}

        accept_failure::accept_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
            base_exception("accept_failure", msg, print, file_name, except_line, function) {}

        create_context_failure::create_context_failure(const std::string msg, bool print, const std::string file_name, const int except_line, const std::string function) :
            base_exception("accept_failure", msg, print, file_name, except_line, function) {}

    }

    bool initialize_network() {
        #if defined(crap_os)
            if (not is_init) {
                WSADATA d;
                if (WSAStartup(MAKEWORD(2, 2), &d)) {
                    return false;
                }
                is_init = true;
            }
        #endif
        return is_init;
    }

    bool uninitialize_network() {
        #if defined(crap_os)
            if (!is_init) {
                if (WSACleanup()) {
                    return is_init;
                }
                is_init = false;
            }
        #endif
        return !is_init;
    }

    std::vector<std::string> resolve_hostname(const std::string hostname, const std::string port) {
        
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

            if (not getnameinfo(current->ai_addr, current->ai_addrlen, buffer, buffer_size, 0, 0, NI_NAMEREQD | AI_ALL)) {
                the_answer.push_back(std::string(buffer));
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

    std::map<std::string, std::map<std::string, std::vector<std::string> > > this_machine_adapters() {
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
            std::string this_line;
            
            while (not all_adapters) {
                
                all_adapters = (ifaddrs_adapter_type) malloc(memory_size);
                this_line = std::to_string(__LINE__ prev);

                if (not all_adapters) {
                    (clean_on_except) ? uninitialize_network() : true;
                    throw exceptions::memory_exception("Failed to aquire " + std::to_string(memory_size) + " bytes of memory", true, __FILE__, line, __FUNCTION__);
                }

                int resp = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAGS_INCLUDE_PREFIX, 0, all_adapters, &memory_size);
                this_line = std::to_string(__LINE__ prev);

                if (resp is ERROR_BUFFER_OVERFLOW) {
                    ifaddrs_free_adapters(all_adapters);
                }

                else if (resp is ERROR_SUCCESS) {
                    break;
                }

                else {
                    (clean_on_except) ? uninitialize_network() : true;
                    ifaddrs_free_adapters(all_adapters);
                    throw exceptions::unexpected_exception("An unexpected exception occured while trying to retrieve this machine's network adapter information", true, __FILE__, line, __FUNCTION__);
                }

            }

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

            adapter_name = ifaddrs_get_adapter_name(this_adapter);

            for (this_address = ifaddrs_pull_adapter_address(this_adapter); this_address; this_address = ifaddrs_get_next_address(this_address)) {

                address_family = network_address_families::resolve_address_family_to_string(ifaddrs_get_address_family(this_address));
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
        
        ifaddrs_free_adapters(all_adapters);
        return the_answer;

    }

    bool socket_is_connected(const int the_socket) {
        int error = 0;
        socklen_t len = sizeof(error);
        int retval = 0;

        #ifdef _WIN32
            u_long mode = 1;  // 1 to enable non-blocking socket
            ioctlsocket(sock, FIONBIO, &mode);
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

    bool is_ipstring(const std::string the_ip, const bool ip4) {
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

    bool network_structures::connected_host::client::operator<(const client& other) const {
        return this->connected_socket < other.connected_socket;
    }

    bool network_structures::connected_host::server::operator<(const server& other) const {
        return this->hostname < other.hostname and 
            this->portvalue < other.portvalue;
    }

    ////////////////////////host////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////



    network_structures::host::host() {
        this->connect_socket = invalid_socket;
        this->hostname = "";
        this->portvalue = DEFAULT_PORT;
        this->timeout = {0, 100000};
        this->tcp = true;
        this->was_init = is_init;
        if (not this->was_init) {
            initialize_network();
        }
        this->del_on_except = true;
        this->secure_ = this->initialized_secure = this->certificates = false;
        this->context = null;
        this->secure_socket = null;
        this->certificates = false;
    }


    network_structures::host::host(const std::string host_name, const std::string port, bool use_tcp, long wait_sec, int wait_msec, bool will_del, bool secure) {
        this->connect_socket = invalid_socket;
        this->hostname = host_name;
        this->portvalue = port;
        this->timeout = {wait_sec, wait_msec};
        this->tcp = use_tcp;
        this->was_init = is_init;
        if (not this->was_init) {
            initialize_network();
        }
        this->del_on_except = will_del;
        this->secure_ = secure;
        this->initialized_secure = this->certificates = false;
        this->context = null;
        this->secure_socket = null;
        this->certificates = false;
    }


    network_structures::host::~host() {
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

        if (not was_init) {
            uninitialize_network();
        }
    }


    bool network_structures::host::host_name(const std::string new_host) {
        if (valid_socket(this->connect_socket) and connect_address and ((this->secure_) ? (this->context and this->secure_socket) : true)) {
            return false;
        }
        this->hostname = new_host;
        return string_functions::same_string(new_host, this->hostname);
    }


    std::string network_structures::host::host_name() const {
        return this->hostname;
    }


    bool network_structures::host::port_value(const std::string new_port) {
        if (valid_socket(this->connect_socket) and connect_address and ((this->secure_) ? (this->context and this->secure_socket) : true)) {
            return false;
        }
        this->portvalue = new_port;
        return string_functions::same_string(this->portvalue, new_port);
    }

    
    std::string network_structures::host::port_value() const {
        return this->portvalue;
    }


    bool network_structures::host::create_address() {
        
        if (not this->connect_address) {
            struct addrinfo hints;
            
            if (this->hostname.empty()) {
                
                std::map<std::string, std::map<std::string, std::vector<std::string> > > adapters = this_machine_adapters();

                for (auto adapter = adapters.begin(); adapter != adapters.end(); adapter++) {
                    
                    if (not string_functions::same_string(adapter->first, rel_adapter)) {
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
            std::printf("The host is '%s'\n", this->hostname.c_str());
            if (getaddrinfo(this->hostname.c_str(), this->portvalue.c_str(), &hints, &this->connect_address)) {
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::getaddrinfo_failure("Failed to retrieve address information for local machine", true, __FILE__, __LINE__ - 2, __FUNCTION__);
            }
        }
        return this->connect_address;
    }


    bool network_structures::host::create_socket() {

        this->create_address();
        if (not valid_socket(this->connect_socket)) {
            this->connect_socket = socket(this->connect_address->ai_family, this->connect_address->ai_socktype, this->connect_address->ai_protocol);
            if (not valid_socket(this->connect_socket)) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::create_socket_failure("Failed to create connection socket for host " + this->hostname + ". Error number " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 4, __FUNCTION__);
            }
        }
        return this->connect_socket;
    }


    bool network_structures::host::initialize_secure() {
        if (this->secure_ and not this->initialized_secure) {
            SSL_library_init();
            OpenSSL_add_all_algorithms();
            SSL_load_error_strings();
            this->initialized_secure = true;
        }
        return (this->secure_) ? this->initialized_secure : not this->initialized_secure;
    }


    bool network_structures::host::create_context() {
        
        if (this->secure_ and not this->initialize_secure()) {
            return false;
        }

        if (this->secure_ and not this->context) {
            this->context = SSL_CTX_new(TLS_client_method());
        }
        return (this->secure_) ? valid_context(this->context) : not valid_context(this->context);
    }


    bool network_structures::host::create_secure_socket() {
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


    void network_structures::host::update_timeout(long sec, int m_sec) {
        this->timeout = {sec, m_sec};
    }


    bool network_structures::host::will_delete_on_except() const {
        return this->del_on_except;
    }


    void network_structures::host::will_delete_on_except(const bool new_flag) {
        this->del_on_except = new_flag;
    }


    socket_type network_structures::host::get_connection_socket() const {
        return this->connect_socket;
    }


    secure_socket_type network_structures::host::get_secure_connection_socket() const {
        return this->secure_socket;
    }


    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    //////////////////////host end//////////////////////


    /**************************************************/

    
    /////////////////////tcp_server/////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////



    
    bool network_structures::tcp_server::create_certificates() {
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

    bool network_structures::tcp_server::disconnect_client(network_structures::connected_host::client& client) {
        
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

        if (client.address_info.ss_family and client.address_info.ss_len) {
            client.address_info.ss_family = 0;
            client.address_info.ss_len = 0;
        }

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
                        client.address_info.ss_len == 0 and 
                            client.address_info.ss_family == 0 and 
                                client.hostname.empty() and 
                                    client.portvalue.empty();
    }

    bool network_structures::tcp_server::bind_socket() {
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

    bool network_structures::tcp_server::start_listening() {
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

    network_structures::tcp_server::tcp_server(const std::string host, const std::string port, int listen_limit, long seconds_wait, int micro_sec_wait, bool will_del, bool secure) :
        network_structures::host::host(host, port, true, seconds_wait, micro_sec_wait, will_del, secure) {
            this->listen_lim = listen_limit;
            this->listening = this->bound;
            this->max_socket = invalid_socket;
            this->max_secure_socket = null;
        }

    network_structures::tcp_server::~tcp_server() {
        this->close_server();
    }

    network_structures::tcp_server::operator bool() const {
        return this->listening;
    }

    bool network_structures::tcp_server::new_connection(bool accept_new) {
        fd_set ready;
        FD_ZERO(&ready);
        FD_SET(this->connect_socket, &ready);

        if (select(this->connect_socket + 1, &ready, 0, 0, &timeout) < 0) {
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

    network_structures::connected_host::client network_structures::tcp_server::new_client() {
        network_structures::connected_host::client the_answer;
        the_answer.connected_socket = invalid_socket;
        the_answer.hostname = the_answer.portvalue = "";
        the_answer.secure_socket = invalid_secure_socket;
        the_answer.address_info = {0, 0};
        the_answer.address_size = sizeof(the_answer.address_info);

        fd_set ready;
        FD_ZERO(&ready);
        FD_SET(this->connect_socket, &ready);

        if (select(this->connect_socket, &ready, 0, 0, &this->timeout) < 0) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::select_failure("Failed to select for the actively listneing socket for new connections. Error number " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 2, __FUNCTION__);
        }

        if (FD_ISSET(this->connect_socket, &ready)) {
            the_answer.connected_socket = accept(this->connect_socket, (struct sockaddr*) &the_answer.address_info, &the_answer.address_size);
            if (not valid_socket(the_answer.connected_socket)) {
                (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                (not this->was_init) ? uninitialize_network() : true;
                throw exceptions::create_socket_failure("Failed to create a new connection socket for the new incomming connection. Error number " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 4, __FUNCTION__);
            }
            
            char address[buffer_size], service[buffer_size];
            std::memset(address, 0, buffer_size);
            std::memset(service, 0, buffer_size);

            if (getnameinfo((struct sockaddr*) &the_answer.address_info, the_answer.address_size, address, buffer_size, service, buffer_size, 0)) {
                the_answer.hostname = "Unspecified hostname";
                the_answer.portvalue = "Unspecified port";
            }
            else {
                the_answer.hostname = std::string(address);
                the_answer.portvalue = std::string(service);
            }

            the_answer.connected_socket = (the_answer.connected_socket > this->max_socket) ? the_answer.connected_socket : this->max_socket;

            if (this->secure_) {
                the_answer.secure_socket = SSL_new(this->context);
                if (not valid_secure_socket(the_answer.secure_socket)) {
                    (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                    (not this->was_init) ? uninitialize_network() : true;
                    throw exceptions::secure_sockets_layer_error("Failed to create a secure connection with the new client", true, __FILE__, __LINE__ - 4, __FUNCTION__);
                }

                SSL_set_fd(the_answer.secure_socket, the_answer.connected_socket);
                if (SSL_accept(the_answer.secure_socket) <= 0) {
                    this->disconnect_client(the_answer);
                    (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
                    (not this->was_init) ? uninitialize_network() : true;
                    char err_buf[256]; unsigned long err = ERR_get_error(); ERR_error_string_n(err, err_buf, sizeof(err_buf));
                    throw exceptions::accept_failure("Failed to accept a secure connection to client. Error : " + std::string(err_buf), true, __FILE__, __LINE__ - 5, __FUNCTION__);
                }
                this->max_secure_socket = (the_answer.secure_socket > this->max_secure_socket) ? the_answer.secure_socket : this->max_secure_socket;
            }
            this->clients.insert({the_answer.connected_socket, the_answer});
        }
        return the_answer;
    }

    bool network_structures::tcp_server::close_connection(const socket_type to_close) {
        bool the_answer = false;
        if (this->clients.contains(to_close)) {
            this->max_socket = invalid_socket;
            for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
                if (to_close == client->first) {
                    // This is the client to be removed
                    SSL_shutdown(client->second.secure_socket);
                    close_socket(client->first);
                    SSL_free(client->second.secure_socket);
                    this->clients.erase(client->first);
                    the_answer = true;
                    continue;
                }
                this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
                this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : this->max_secure_socket;
            }

        }
        return the_answer;
    }

    bool network_structures::tcp_server::close_connection(const std::string hostname, const std::string portvalue) {
        bool the_answer = false;
        this->max_socket = invalid_socket;
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            if (string_functions::same_string(client->second.hostname, hostname) and string_functions::same_string(client->second.portvalue, portvalue)) {
                SSL_shutdown(client->second.secure_socket);
                close_socket(client->first);
                SSL_free(client->second.secure_socket);
                this->clients.erase(client->first);
                the_answer = true;
                continue;
            }
            this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
            this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : this->max_secure_socket;
        }
        return the_answer;
    }

    bool network_structures::tcp_server::close_server() {
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            this->disconnect_client(client->second);
        }

        this->listen_lim = 0;
        this->listening = this->bound = false;
        this->max_secure_socket = null;
        this->max_socket = invalid_socket;
        return this->clients.empty() and 
                    not this->listen_lim and 
                        not valid_secure_socket(this->max_secure_socket) and
                            not valid_socket(this->max_socket);
    }

    bool network_structures::tcp_server::update_limit(const int listening_limit) {
        if (not this->listening) {
            this->listen_lim = listening_limit;
        }
        return this->listen_lim == listening_limit;
    }

    int network_structures::tcp_server::listening_limit() const {
        return this->listen_lim;
    }

    bool network_structures::tcp_server::start() {

        if (not this->listening) {

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

    bool network_structures::tcp_server::running() const {
        return this->bound and this->listening and valid_socket(this->connect_socket);
    }

    std::set<network_structures::connected_host::client> network_structures::tcp_server::get_clients() {
        std::set<network_structures::connected_host::client> the_answer;
        if (not this->listening) {
            return the_answer;
        }
        
        fd_set ready;
        FD_ZERO(&ready);
        this->max_socket = invalid_socket;
        this->max_secure_socket = invalid_secure_socket;
        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            this->max_socket = (client->first > this->max_socket) ? client->first : this->max_socket;
            this->max_secure_socket = (client->second.secure_socket > this->max_secure_socket) ? client->second.secure_socket : client->second.secure_socket;
            FD_SET(client->first, &ready);
        }

        if (select(this->max_socket + 1, &ready, 0, 0, &this->timeout) < 0) {
            (this->del_on_except) ? freeaddrinfo(this->connect_address) : (void) 0;
            (not this->was_init) ? uninitialize_network() : true;
            throw exceptions::select_failure("Failed to select any of the connections that are ready with information. Error " + std::to_string(get_socket_error()), true, __FILE__, __LINE__ - 3, __FUNCTION__);
        }

        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            if (FD_ISSET(client->first, &ready)) {
                the_answer.insert(client->second);
            }
        }
        return the_answer;
    }

    std::set<network_structures::connected_host::client> network_structures::tcp_server::get_all_clients() {
        
        std::set<network_structures::connected_host::client> the_answer;

        for (auto client = this->clients.begin(); client != this->clients.end(); client++) {
            the_answer.insert(client->second);
        }

        return the_answer;
    }

    socket_type network_structures::tcp_server::get_max_socket() const {
        return this->max_socket;
    }

    secure_socket_type network_structures::tcp_server::get_max_secure_socket() const {
        return this->max_secure_socket;
    }

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ///////////////////tcp_server end///////////////////


    /**************************************************/

    
    /////////////////////tcp_client/////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////



    // Code goes here



    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ///////////////////tcp_client end///////////////////

}