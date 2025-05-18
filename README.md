# **<div align="center"><h2>Simple-Networking</h2></div>**
***

***

***

**<div align = "center"><h1>!!DOCUMENTATION UNDER CONSTRUCTION!!</h1></div>**
----
----

***

***

***


*This is an outline of a simple implementation to connect remote machines with a TCP or a UDP connection (UDP hasn't been set up yet)*

**The code works on all three systems (Linux, MacOS, and Windows). The library works, but there is still more to come.**




*<h4>Table of Content:</h4>*

* [About the Program](#about-the-program)
* [How to use Simple-Networking](#how-to-use-simple-networking)
* [Library Features](#library-features)




***

***

***

# **<div align="center"><h3>About the Program</h3></div>**
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


# **<div align="center"><h3>Compiling the tests</h3></div>**
---


<span style = "color:red">**• Note**</span><br>
    
* Regarding the commands to run the the cmake file and the corresponding makefiles.
    
    ‣ MacOS - I used Homebrew to install 
        openssl and that was it. Beautiful, 
        simple and easy to set up.
    
    ‣ LinuxOS - I used the linux package 
        manager. Again, beautiful, simple 
        and easy to set up.
    
    ‣ Windows - Ya windows is not an 
        easy system to develop on. I 
        initially tried using choco, 
        but the cmake could never find 
        the openssl library on the machine, 
        even after I set the environment 
        variable for OpenSSL. In the end, 
        I just used MSYS2 to install Openssl. 
        It worked and I was even 
        able to use powershell to run the cmake file.

* The secure connection has been tested and it works great. 
To run the secure connection, be sure to be situated in the 
build directory (if it doesn't exist, create it in the same directory 
where the `CMakeLists.txt` file exists then enter into it) 
and execute the file in the objects directory with the 
appropriate command. Again this is for the secure tcp client/server tests programs.



The program itself has been written in `C++23`, though should work in `C++17+`.
The library can be used in most other networking programs as long as it's compiled in the proper manner. 
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
functions and methods implemented in the `libraries` directory. So during compilation, the header 
files in the `headers` directory must be linked to their counterparts in the `libraries` directory.

In the CMakeLists.txt file, this line:
    `include_directories(${CMAKE_SOURCE_DIR}/headers)`

tells the compiler to look at the files in the `headers` directory whenever an include statement 
is called. Then the next code snippet in the `CMakeLists.txt` file, the line,
    
    # Gather library sources
    file(GLOB LIB_SOURCES
        "${CMAKE_SOURCE_DIR}/libraries/*.c++"
        "${CMAKE_SOURCE_DIR}/libraries/*.cpp"
        "${CMAKE_SOURCE_DIR}/libraries/*.cc"
        "${CMAKE_SOURCE_DIR}/libraries/*.cxx"
    )



Is used to gather all the files that will be linked to the test executable. The test executable is created when the `make` command is executed and the executable object files are placed within the `objects` directory.
















This library works well, but to run it, OpenSSL will need to be installed on the system. In this code package here, I created a testing program that will run the networking code. It demonstrates how the code is structured and how to use the coding library. The tests are located in the `tests` directory.

When any program is being compiled and you wish to include the networking library in it, be sure to link all the files in the
    `headers` & `libraries` directory.

The CMakeLists.txt file works well on unix systems and on windows systems too. Furthermore, the CMakeLists.txt file has been confirmed to work on MSYS2.

In order to run the cmake file, I've been running the commands (these commands are also in the cmake file at the top):

*<span style="color:green">Unix</span>:*

    `Unix : cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`
    `make`

*<span style="color:blue">Windows</span>:*
    
    Powershell:
        cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        cmake --build build

    MSYS2:
        cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DOPENSSL_ROOT_DIR=/mingw64
        cmake --build buid




# **<h3>Library Features</h3>**
---

* All the functions, objects, and features that this library hold are located within the `networking` namespace.

* Create networking exceptions specific to this networking library.
    * All networking exceptions are located within the namespace exceptions.
    * All exceptions are children of the `base_exception` type. So any of them can be caught as a `base_exception`:
            
        `catch (networking::exceptions::base_exception& except)`
    * More im

* Implement networking functions that are useful for handling networking programs ✅
    *