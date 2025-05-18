
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

* Create networking exceptions specific to this networking library.
    * All networking exceptions are located within the namespace exceptions.
    * All exceptions are children of the `base_exception` type. So any of them can be caught as a `base_exception` reference:
            
        `catch (networking::exceptions::base_exception& except)`
    
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










* Implement networking functions that are useful for handling networking programs ✅
    *





# <div align = "center">**<h3><u>How to use Simple-Networking</u></h3>**</div>

<div align="center"><h3>UNDER CONSTRUCTION</h3></div>