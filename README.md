
***

***

***

**<div align = "center"><h3>!!DOCUMENTATION UNDER CONSTRUCTION!!</h3></div>**
----
----

***

***

***


**<div align="center"><h1><u>Simple-Networking</u></h1></div>**


***

***

***



*This is an outline of a simple implementation to connect remote machines with a TCP or a UDP connection (UDP hasn't been set up yet)*

**The code works on all three systems (Linux, MacOS, and Windows). The library works, but there is still more to come.**




***<div align="center"><h4><u>Table of Content</u>:</h4></div>***

* [About the Program](#about-the-program)
* [Compiling the tests](#compiling-the-tests)
* [Library Features](#library-features)
* [How to use Simple-Networking](#how-to-use-simple-networking)




***

***

***

# **<div align="center"><h3><u>About the Program</u></h3></div>**
---


I wrote this program to gain experience with network programming. This project has lead to a lot of learning 
and I've come to see a whole new way to write code. I based a lot of what I did 
in this project of Lewis Van Winkle's wonderful book, [Hands-On Network Programming with C](https://codeplea.com/). If you're looking for a comprehensive, engaging, and easy to follow book on networking, I 
can't recommend this book enough.

Not only is the book a great resource for network programming, Lewis Van Winkle himself is great at explaining complex ideas in a simple way that makes sense, is easy to follow, and is easy to replicate and advance. He is also willing to engage with his readers. When I was reading his book, I was struggling with wrapping my mind around the secure networking sections (Chapter 9/10), I sent him an email. He responded within a few days and was kind, supportive, helpful, and just overall wonderful. In summary, wondeful book and wonderful author! 😊

This program is basically me implementing everything I learned in that book. I am still working on some of it, but I've implemented the bigger aspects of networking so far (with a `tcp_server` and a `tcp_client`).
What I'm still planning on adding:
    
* `DNS-Querying`.
* `Emailing` functions/objects.
* `https/https structures` (which allow for https communication).
* `udp_server` and `udp_client` for `UDP` communication.
 
***

***

***


# **<div align="center" style="font:sans-serif"><h3><u>Compiling the tests</u></h3></div>**
---


The program itself has been written in `C++23`, though should work in `C++17+`.
The library can be used in most other networking programs as long as it's compiled in the proper manner. 
The manner of compilation here can be applied to any other project this library is included in. 
The structure of the program is as follows:

    .
    ├── CMakeLists.txt
    ├── README.md
    ├── files // For testing purposes. Not required to run Simple-Networking
    │   ├── cert.pem
    │   └── key.pem
    ├── headers
    │   ├── include
    │   ├── included
    │   ├── misc_functions
    │   ├── networking
    │   └── string_functions
    ├── libraries
    │   ├── misc_functions.c++
    │   ├── networking.c++
    │   └── string_functions.c++
    ├── objects
    │   └── test_server
    └── tests
        └── test_server.c++


Within this structure, the all the files in the `headers` directory are C/C++ header files.
(I just like the look of them without a file type extension), and they hold the prototypes for 
functions and methods implemented in the `libraries` directory. The `include` file in the `headers` directory only serves as a header where all the basic macro definitions are defined that are used throughout the `libraries/*c++` files. During compilation, the header files in the `headers` directory must be linked to their counterparts in the `libraries` directory.

In the CMakeLists.txt file, this line:
    `include_directories(${CMAKE_SOURCE_DIR}/headers)`

tells the compiler to look at the files in the `headers` directory whenever an include statement 
is called. Then the next code snippet in the `CMakeLists.txt` file, this one,
    
    # Gather library sources
    file(GLOB LIB_SOURCES
        "${CMAKE_SOURCE_DIR}/libraries/*.c++"
        "${CMAKE_SOURCE_DIR}/libraries/*.cpp"
        "${CMAKE_SOURCE_DIR}/libraries/*.cc"
        "${CMAKE_SOURCE_DIR}/libraries/*.cxx"
    )



Is used to gather all the files that will be linked to the test executable. The test executable is created when the `make` command is executed and the executable object files are placed within the `objects` directory.

This library works well, but to run it, OpenSSL will need to be installed on the system. In this code package here, I created a testing program that will run the networking code. It demonstrates how the code is structured and how to use the coding library. To view these tests, take a look in the `tests` directory.

To compile this library as part of your own application, be sure to link all the files in the
`headers` & `libraries` directory. Also be sure to [OpenSSL](https://openssl-library.org/) installed 
and findable by your compiler during compilation time.

In this testing environment, I've installed [OpenSSL](https://openssl-library.org/) and I've made sure it's findable by the compiler being used for compilation.

If you want to ensure that the compiler can find where you have [OpenSSL](https://openssl-library.org/) installed, be sure to use use a good package manager for the installation of [OpenSSL](https://openssl-library.org/). 

* On mac, [Homebrew](https://brew.sh/)
* On linux (I used Ubuntu) - [Installing OpenSSL on Ubuntu](https://stackoverflow.com/questions/3016956/how-do-i-install-the-openssl-libraries-on-ubuntu)
*  On Windows, I wasn't able to find a good reference (Ya, windows is not nice...) This is what worked for me instead:
    
        1.) Open MSYS2
        
        2.) Upgrade the package installer:
                pacman -Syu
        
        3.) Install OpenSSl:
                pacman -S mingw-w64-x86_64-openssl
        
        4.) The packages should be installed now. Verify by checking if:
                Headers are in:
                    /mingw64/include

                Libraries are in:
                    /mingw64/lib
                
                DLLs are in:
                    /mingw64/bin
        
        5.) If you want to compile using powershell, you'll have to link the path to where the MSYS2 compiler is located and where the [OpenSSL](https://openssl-library.org/) compiler is installed (In step 3, the MSYS2 compiler was installed along with openssl).
                In my CMakeLists.txt file, I have the commented out line that links the [OpenSSL](https://openssl-library.org/) root directory location (this could be different on your machine). But I also linked the location where MSYS2 installed OPENSSL and the MSYS2 compiler (C:\mingw64\mingw64\bin) to the path variable in system environment.
            

Then in CMakeLists.txt, if you want the compiler to find the OpenSSL library, be sure to include these lines, no matter what system is being used:

    find_package(OpenSSL REQUIRED)
    target_link_libraries(your_target PRIVATE OpenSSL::SSL OpenSSL::Crypto)


The CMakeLists.txt file works well on unix systems and on windows systems too. Furthermore, the CMakeLists.txt file has been confirmed to work on MSYS2. 

In order to run the cmake file, I've been running the commands (these commands are also in the cmake file at the top):

#### *<span style="color:green"><u>Unix</u></span>:*

    Unix : cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    
    make

#### *<span style="color:blue"><u>Windows</u></span>:*
    
    Powershell:
        cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DOPENSSL_ROOT_DIR=/mingw64 // Not strictly necessary if directory was added to system path.
        
        cmake --build build

    MSYS2:
        cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DOPENSSL_ROOT_DIR=/mingw64 // This is still necessary even if OPENSSL is in the system variable path. It failed for me if I didn't have this linking.
        
        cmake --build buid


* The secure connection has been tested and it works great so far.
To run the secure connection, be sure to be situated in the 
build directory (if it doesn't exist, create it in the same directory 
where the `CMakeLists.txt` file exists then enter into it) and run the commands [above](#Unix).
Run the cmake command first, then once that's done, run the `make command` (`make` on [Unix](#Unix), and `cmake --build build` on [Windows](#Windows)). After the `make command` successfully finishes it's execution, the executables 
will have been created and placed into the `objects` directory. 
Again this is only to create the tests for the networking library that are included in this codebase.



# <div align = "center">**<h3><u>Library Features</u></h3>**</div>
---

* All the functions, objects, and features that this library hold are located within the `networking` namespace.
    
* Data types:
    
    * All the `primitive` networking data types are still available 
    (i.e ints for sockets on unix machines and SOCKETs for windows sockets), but their types have been abstracted away to allow for 
    cross platform code. Here's a list of the networking types and their abstracted away working type names:


| type/func        | Lin/Mac                | Win                        | abstraction                  |
|------------------|:----------------------:|:--------------------------:|:----------------------------:|
| adapter ptr      | `struct ifaddrs*`      | `PIP_ADAPTER_ADDRESSES`    | adapter_type                 |
| adapter name     | `std::string(the_adapter->ifa_name)` | `std::string(the_adapter->FriendlyName)` | get_adapter_name()           |
| next adapter     | `the_adapter->ifa_next`| `this_adapter->Next`       | get_next_adapter()           |
| addr from adapter| `the_adapter`          | `this_adapter->FirstUnicastAddress` | get_address_from_adapter()   |
| free adapters    | `freeifaddrs(the_adapters)` | `std::free(the_adapters)` | free_adapters()              |
| addr ptr         | `struct ifaddrs*`      | `PIP_ADAPTER_UNICAST_ADDRESS` | address_type                |
| next addr        | `NULL`                 | `this_address->Next`       | get_next_address()           |
| addr sockaddr    | `this_address->ifa_addr` | `this_address->Address.lpSockaddr` | get_address_sockaddr()     |
| addr sockaddr len| `sizeof(*this_address->ifa_addr)` | `this_address->Address.iSockaddrLength` | get_address_sockaddrlen()|
| addr family      | `this_address->ifa_addr->sa_family` | `this_address->Address.lpSockaddr->sa_family` | get_address_family()    |
| socket error     | `(errno)`              | `(WSAGetLastError())`      | socket_error()                |
| error string     | `gai_strerror(error_number)` | `gai_strerrorA(error_number)` | socket_error_string()    |
| socket type      | `int`                  | `SOCKET`                   | socket_type                   |
| socket family type | `unsigned short` (Linux),<br>`unsigned char` (Mac) | `int` | socket_family_type    |
| invalid socket   | `-1`                   | `INVALID_SOCKET`           | invalid_socket                |
| valid socket     | `(this_socket >= 0)`   | `(this_socket != invalid_socket)` | valid_socket()            |
| close socket     | `close(the_socket)`    | `closesocket(the_socket)`  | close_socket()                |


<br>
<br>
<br>

* Data types:

    * And for dealing with the OpenSSL. This was not necessary and is still not necessary to use, but I find
    these renames easier to follow along

| data type/function                  | Linux/macOS                      | Windows                       | abstracted type/macro           |
|-------------------------------------|:--------------------------------:|:-----------------------------:|:-------------------------------:|
| secure socket type pointer (OpenSSL)| `SSL*`                           | `SSL*`                        | secure_socket_type              |
| networking context pointer (OpenSSL)| `SSL_CTX*`                       | `SSL_CTX*`                    | context_type                    |
| certificate pointer (OpenSSL)       | `X509*`                          | `X509*`                       | certificate_type                |
| invalid secure socket               | `nullptr`                        | `nullptr`                     | invalid_secure_socket           |
| invalid context                     | `nullptr`                        | `nullptr`                     | invalid_context                 |
| invalid certificate                 | `nullptr`                        | `nullptr`                     | invalid_certificate             |
| valid secure socket                 | `(the_socket != invalid_secure_socket)` | `(the_socket != invalid_secure_socket)` | valid_secure_socket()     |
| valid context                       | `(the_context != invalid_context)`      | `(the_context != invalid_context)`      | valid_context()           |
| valid certificate                   | `(certificate != invalid_certificate)`  | `(certificate != invalid_certificate)`  | valid_certificate()       |


* A networking exceptions specific to this networking library.
    * All networking exceptions are located within the namespace exceptions.
    * All exceptions are children of the `base_exception` type. So any of them can be caught as a `base_exception` reference:
            
        ```
        catch (networking::exceptions::base_exception& except) {
            
            // To see the exception type
            std::cerr << except.type() << std::endl;
            
            // To see the message generated for the exception
            std::cerr << except.message() << std::endl;
            
            // To see the file where the exception was thrown from
            std::cerr << except.file() << std::endl;
            
            // To se the line where the exception was thrown from
            std::cerr << except.error_line() << std::endl;
            
            // To see the error number
            std::cerr << except.error_number() << std::endl;

            // To print the error message associated with this exception being thrown.
            except.print();
        }
        ```

* A `network_address_families` namespace used for retrieving address families.

    * There are two important aspects to the `network_address_families` namespace:

        
        * The Relevant adapter:
            * This is assigned at compilation time. 
            It's the adapter that is referenced most on the machine. I assigned them based off my machine, 
            but your machine could be different. Be sure to check the name of your adapter on your 
            machine and change this to match that name for smooth utilization of the networking structures.

            * To retrieve rel_adapter, you can use the `machine_adapters()` function to retrieve all 
            the adapters on your current machie, then change this value to match what you want to be the adapter 
            that is referenced most often on your machine.

            * `rel_adapter` is the default parameter for the following method (So be sure to either pass in a value for this method, or change rel_adapter to something that will be promising):
                * `networking::network_structures::host::retrieve_hostname(std::unordered_set<std::string> {rel_adapter})`

        
        | Platform            | rel_adapter value |
        |---------------------|:-----------------|
        | Windows (`crap_os`) | "Wi-Fi 3"        |
        | macOS (`mac_os`)    | "en0"            |
        | Linux (other Unix)  | "enp0s8"         |


        * The family constants:

        | Constant Name                  | Value                                 | Platform(s)                  |
        |--------------------------------|---------------------------------------|------------------------------|
        | unspec_address_family          | "Unspecified Address Family"          | All                          |
        | unrecognized_address_family    | "Unrecognized Address Family"         | All                          |
        | ip_version4_address_family     | "IP Version 4 Family"                 | All                          |
        | ip_version6_address_family     | "IP Version 6 Family"                 | All                          |
        | link_layer_address_family      | "Link-Layer Interface Address Family" | macOS (Unix)                 |
        | netlink_address_family         | "Netlink Address Family"              | Linux (Unix, not macOS)      |
        | packet_address_family          | "Packet Address Family"               | Linux (Unix, not macOS)      |
        | netbios_address_family         | "NetBIOS Address Family"              | Windows                      |
        | irda_address_family            | "IrDa Address Family"                 | Windows                      |
        | bluetooth_address_family       | "Bluetooth Address Family"            | Windows                      |

    * The other aspect of the `network_address_families` namespace are the two functions:
        
        * `get_addresses_families()` function which retrieves a `std::set<std::string>` of all the family constants that the Platform uses.
        
        * `resolve_address_to_string(const socket_type the_family)` Converts the `socket_family_type` 
        [See Library Features above](#library-features) into a `std::string` in the `family constants` above.



* Networking namespace functions:
<br>
<br>
<br>
<br>


###### <h3><div align = "center"><u>`network_initialized()`</u></div></h3>
* This is a function that is really only useful for windows systems. But it works on all platforms. 
Windows systems need to have their networking libraries initialized. This function 
simply checks if the network was initialized within the context of using this networking library 
during the current runtime session.

* Return type is a `bool`.

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>    


###### <h3><div align = "center"><u>`initialize_network()`</u></div></h3>
* Again this is really only useful on windows systems. It initializes the networking library and 
returns `true` within the context of the networking library namespace during the current runtime 
session, `false` if it was not initialized, or an exception.

* Return type is a `bool`.

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>


###### <h3><div align = "center"><u>`uninitialize_network()`</u></div></h3>
* Again really only useful on windows systems. It uninitializes the networking library and returns 
`true` if the network was successfully uninitialized within the context of the networking 
library namespace during the current runtime session, `false` if it 
was not or an exception is thrown.

* Return type is a `bool`.

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>


###### <h3><div align = "center"><u>`secure_network_initialized()`</u></div></h3>
* Check if the [OpenSSL](https://openssl-library.org/) library has been initialized within the 
context of the networking namespace during the current runtime session. 
Returns `true` if the library is initialized, `false` if it's not.

* Return type is a `bool`.

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>


###### <h3><div align = "center"><u>`initialize_secure_network()`</u></div></h3>
* This is to initialize the [OpenSSL](https://openssl-library.org/) secure networking 
library within the context of the networking library namespace during the 
current runtime session. There are currently no checks for whether or 
not the network was initialized though, so this will pretty 
much always initialize the library then return `true`.

* Return type is a `bool`.

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>


###### <h3><div align = "center"><u>`uninitialize_secure_network()` :</u></div></h3>
* Uninitialize the [OpenSSL](https://openssl-library.org/) secure networking library within the 
context of the networking library namespace during the current runtime session, so this will 
pretty much always uninitilize the library then return `true`.

* Return type is a `bool`.

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>

###### <h3><div align = "center"><u>`resolve_hostname(const std::string hostname, const std::stirng port = default_port, const bool name = false)`</u></div></h3>
    
* Parameters:
        
    | data type | parameter name | default value | Notes |
    |-----------|:--------------:|:-------------:|:---------------------------:|
    | const std::string | hostname | no default value, must be set when called.| This is the hostname 
    to be resolved into an IP address. This hostname's IP address(es) are what are returned.
    | const std::string | port | default_port (macro - #define "8080") | This is the port to use for 
    the DNS query. Not usually necessary to change it, but it can be changed if necessary.
    | const bool | name | false | The name flag is used to specify whether or not to use the `NI_NAMEREQD` macro in the call to retrieve the name information for the address. This is a flag because it can take a while to retrieve this data, for some reason, this is especially true on the windows system I've been using. |

* Returns a `std::unordered_set<std::string>` with all the IP addresses that were resolved for 
the `hostname` passed in.

* If the networking library fails to initilize, a `initialize_network_failure` 
exception is thrown.

* Namespace parent is `networking`.

<br>
<br>
<br>
<br>

###### <h3><div align = "center"><u>`networking::machine_adapters(const bool names = false)`</u></div></h3>
* Parameters:

| data type | parameter name | default value | Notes |
|-----------|:--------------:|:-------------:|:-----:|
|const bool |     names      |     false     | This is the same as [resolve_hostname](#-stdunordered_setstdstring-networkingresolve_hostnameconst-stdstring-hostname-const-stdstirng-port--default_port-const-bool-name--false-)'s names parameter. This specified whether or not to use the NI_NAMREQD with the getnameinfo function. It can take a while on windows machines, so it might not be worth using.

* Return type is a `std::unordered_map<std::string, std::unordered_map<std::string, std::set<std::string> > >`

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>


###### <h3><div align = "center"><u>`socket_is_blocking(const socket_type& the_socket)`</u></div></h3>
* This still hasn't been tested, but it's supposed to check if the socket is in a blocking state or not. 
If the socket is blocking, then `true` is returned, if it's not blocking or an error occured, `false` is returned.
* So be sure to always check if the socket passed in is still valid after using this function.

* Return type is `bool`

* Namespace parent is `networking`.

<br>
<br>
<br>
<br>


###### <h3><div align = "center"><u>`set_blocking(socket_type& the_socket, const bool block)`</u></div></h3>
* Set the socket passed in to blocking or non-blocking, depending on what `block` is. `true` to set the socket 
to blocking, `false` to set it to non-blocking.

* Return type is `bool`

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>


###### <h3><div align = "center"><u>`socket_connected(socket_type& the_socket)` :</u></div></h3>
* Honestly, this is a bad function. It's almost always unreliable and breaks sockets. Gonna get rid of it soon.

* Return type is `bool`

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>

###### <h3><div align = "center"><u>`send_message(networking::network_structures::host_connection host, const data* the_message, const bytes byte_count, const int flags = 0, const std::chrono::duration<int> timeout = std::chrono::seconds(10))`</h3></u></div>
* This function sends a message to the host that is specified with the `host` parameters.


* Return type is `networking::network_structures::host_report`

* Namespace parent is `networking`.
<br>
<br>
<br>
<br>

#### <h2><div align = "center"><u>`Networking::Networking Structures`</u></div></h2>

***Note** : These structures are implemened to be have their own comparison operations and they implement two different types of comparisions.

***Another Note** : Another very useful book I used to learn about `C++'s Standard Library` and it's algorithms is [Data Structuresa nd Algorithms in C++ Pocket Primer](https://bookshop.org/p/books/data-structures-and-algorithms-in-c-pocket-primer-lee-wittenberg/b26326e0c97bebf4?ean=9781683920847&next=t&), by Lee Wittenberg. This book showed me basic data structures defined within C++'s Standard library, and it also went over how the data structures are implemented. For example it showed how a [`std::set`](https://en.cppreference.com/w/cpp/container/set) is implemented using a [`Binary Search Tree`](https://www.cs.usfca.edu/~galles/visualization/BST.html), and how an [`std::unordered_set`](https://en.cppreference.com/w/cpp/container/unordered_set) is implemented using a [`hash table`](https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/). All the explanations in the book are short and easy to follow. This is good to learn about coding in C++, but also to learn about data structures & algorithms in general.
    
* # <h6>`Weak comparison` : Internal attributes are only compared if they are both defined.</h6>

* # <h6>`Strong comparison` : Internal attributes of the structures are always compared</h6>

##### <h2><div align = "center"><u><h3>networking::network_structures</h3></u></div></h2>

###### <h3><div align = "center"><u>client_id</u></div></h3>
* All the members of this struct are public.

* The `client_id` structure is used primarily as a map key in the `tcp_server` to keep track of all the connected clients. This structure consists of three different strings (All of which have to be set manually):
    * `hostname` 
    * `port`
    * `connection_time`

* 2 Constructors:
    * Default constructor:
        * `client_id()`
    
    * Parameter constructor:
        * `client_id(const std::string hname, const std::string hport, const std::string ctime_)`
            * `const std::string hname` : The hostname of the client structure being pointed to.
            * `const std::string hport` : The port this client structre being pointed to.
            * `const std::string ctime_` : The time when the client connected to this machine.
    
* Operator overrides:
    * `Operator<() const` : Allows for the `client_id` object to be used in an `std::set()`,
    `std::map()`, and their unordered_counterparts too.
        * Parameters:
            * `const client_id& other` : The other `client_id` to be compared with. This comparision has been implemented to compare all three internal strings. This comparison also [strongly compares](#strong-comparison--internal-attributes-of-the-structures-are-always-compared) the `hostname` of each `client_id`, and [weakly compares](#weak-comparison--internal-attributes-are-only-compared-if-they-are-both-defined) the `port` and `connection_time`.

    * `Operator==() const` : Used for comparisons between different `client_id` objects.
        * Parameters:
            * `const client_id& other` : The other `client_id` structure to be compared with. This comparison uses the `std::string_functions::same_string` function because it allows for string comparisons in a case independent manner. This comparison also [strongly compares](#strong-comparison--internal-attributes-of-the-structures-are-always-compared) the `hostname` of each `client_id`, and [weakly compares](#weak-comparison--internal-attributes-are-only-compared-if-they-are-both-defined) the `port` and `connection_time`.

        * Returns a `bool`.
        
    * `Operator bool() const` : This method is used to check if the `client_id` is defined or not.
        * To be defined, the `client_id` needs to have a hostname defined to it. The `port` and `connection_time` don't need to be defined.

        * Returns a `bool`.

    * `Operator=` : Assigns another `client_id` to the current `client_id`.
        * Parameters:
            * `const client_id& other` : The other `client_id` to assign to the current `client_id`.

        * Returns a `client_id` reference to the current `client_id` object.

###### <h3><div align = "center"><u>host_connection</u></div></h3>

* The `host_connection` is used as the base class for the `client_connection` & `server_connection` structs.

* The `host_connection` struct consists of three data types (Again all of which need to be set manually):
    * `host_information` of type `client_id`.
    * `connect_socket` of type `socket_type`.
    * `secure_connect_socket` of type `secure_socket_type`.

* 2 Constructors:
    * Default constructor:
        * `host_connection()`
    * Parameter constructor:
        * `host_connection(client_id client_, const socket_type sock_, secure_socket_type sec_sock)`
            * `client_` : The identifier for this `host_connection` structure.
            * `connect_socket` : The socket that is used for creating connection to the remote machine.
            *  `sec_sock` : The secure connection socket that is used to establish secure connections.

* Operator overrides:
    * `Operator<() const`: Used to compare a `host_connection` with another `host_connection`. This simply compares the `client_id` objects with each `host_connection`.
        * Parameters:
            `const host_connection& other` : The other `host_connection` to compare the current `host_connection` with.
        
        * Returns a `bool`.
    
    * `Operator==() const` : This [strongly compares](#strong-comparison--internal-attributes-of-the-structures-are-always-compared) the `host_connection` objects' `client_id`s and `connect_socket`s. It also [weakly compares](#weak-comparison--internal-attributes-are-only-compared-if-they-are-both-defined) the `host_connection`'s `secure_connect_socket`s.
        * Parameters:
            `const host_connection& other` : The other `host_connection` to compare this `host_connection` against.
        * This is a `virtual` method.

        * Returns a `bool`.

    * `Operator bool() const` : This operator checks that the `host_connection`'s `host_information` is true (utilizing the `client_id's operator bool()`), and if the `connect_socket` of this `host_connection` is valid or not. The `secure_connect_socket` is not checked in this operator.

        * Returns a `bool`.

    * `Operator=()` : The assignment operator. Performs a deep copy of all data attributes of `other`'s data attributes, to `this`'s data attributes (provided `this` is not `other`).

        * Returns a `host_connection` reference to the current `host_connection`.



###### <h3><div align = "center"><u>host_report</u></div></h3>

* A `host_report` is a struct that is the atomic type for host communication. It consists of the attributes:
    * `host` of type `host_connection` which holds the name of the host that either sent of received data.
    * `byte_count` of type `bytes` which holds the total number of bytes that were sent or received (depending on the context in which the `host_report` is being returned).
    * `success` of type `bool` which states if the send or receive was successful.

* 3 Constructors:
    * Default constructors:
        * `host_report`

    * Parameter constructor:
        * `host_report(const host_connection con_host, bytes total_bytes, const bool succeeded)`
            * TODO: Add explanations
        * `host_report(const std::string hname, const std::string hport, const std::string hctime, const socket_type conn_sock, secure_socket_type sec_sock)`
            * TODO: Add explanations

* Operator overrides:

    * `Operator==() const` : The comparison operator for this `host_report`. It compares this `host_report`'s `host`, `byte_count`, and `success` data fields, to the `other` `host_report`'s `host`, `byte_count`, and `success` fields.

        * Parameters:
            * `other` of type `const host_report&` : The other `host_report` to compare to the current `host_report` object.

        * Returns a `bool`.

    * `Operator bool() const` : The `bool` check for this `host_report`. It returns value of the `success` data field.

        * Returns a `bool`.

    * `Operator<() const` : The comparison operator that allows this `host_report` to be used in `std::set` and `std::map` and their `unordered` partner types.

        * Parameters:
            * `other` of type `const host_report&` : The other `host_report` to use for a comparison with the current `host_report`.

        * Returns a `bool`.

    * `Operator()=` : This is the assignment operator to change the values of this `host_report` to the values of `other`'s field values.

        * Parameters:
            * `other` of type `const host_report&` : The `host_report` whose values will be assigned to this `host_report`. If `other` is the same `host_report` as the `host_report` calling it, then nothing is changed.
        
        * Returns a reference to the current `host_report`.
    

###### <h3><div align = "center"><u>complete_report</u></div></h3>

* A `complete_report` is a 

###### <h3><div align = "center"><u>client_connection</u></div></h3>
###### <h3><div align = "center"><u>server_connection</u></div></h3>
###### <h3><div align = "center"><u>tcp_server</u></div></h3>
###### <h3><div align = "center"><u>tcp_client</u></div></h3>


# <div align = "center">**<h3><u>How to use Simple-Networking</u></h3>**</div>

<div align="center"><h3>UNDER CONSTRUCTION</h3></div>



# <div align = "center">**<h3><u>TO DO list</u></h3>**</div>

Complete
<ul>
    <li>Make all the functions and objects thread safe when in execution. ✅</li>
    <li>Make the structures utilize operation overloading, allowing for simplified code. ✅</li>
    <li>Make sure the code works on all operating systems. ✅</li>
    <li>Implement the code so it works with both secure and non-secure connections. ✅</li>

</ul>
In progress
<ul>
    <li>Make the tcp_client capable of timing out when establishing a connection. ✅ (BUT STILL NEEDS TO BE TESTED)</li>
    <li>Make the tcp_server and tcp_client capable of sending any data type across the network connection. ✅ (BUT STILL NEEDS TO BE TESTED)</li>
    <li>Investigate if there's a way to check if the windows networking library has already been implemented, and if the secure networking library has already been initialized or not.</li>
</ul>
Still to come
<ul>
    <li>Add javadoc comments to all methods and functions (In progress- Still documenting the tcp_client object's methods)</li>
    <li>Write http_server and http_client classes that utilize the tcp_server and tcp_client classes for establishing connections.</li>
</ul>