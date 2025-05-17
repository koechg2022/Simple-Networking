# Simple Networking


*This is an outline of a simple implementation to connect remote machines with a TCP or a UDP connection (UDP hasn't been set up yet)*

**The code works on all three systems (Linux, MacOS, and Windows). There will be more code added soon though.**

This program works well, but to run it, OpenSSL will need to be installed on the system. The CMakeLists.txt file works well on unix systems and on windows systems too. Furthermore, the CMakeLists.txt file has been confirmed to work on MSYS2.

In order to run the cmake file, I've been running the commands (these commands are also in the cmake file at the top):

*Unix:*

    `Unix : cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`
    `make`

*Windows:*
    
    Powershell:
        cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        cmake --build build

    MSYS2:
        cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DOPENSSL_ROOT_DIR=/mingw64
        cmake --build buid

***NOTE**
    Regarding the commands to run the the cmake file and the corresponding makefiles.
    
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


***Note**
The secure connection has been tested and it works great. To run the secure connection, be sure to be situated in the build directory (if it doesn't exist, create it in the same directory where the `CMakeLists.txt` file exists then enter into it) and execute the file in the objects directory with the appropriate command. Again this is for the secure tcp client/server tests programs.


*<h3>About the Program</h3>*

The program itself has been written in `C++23`, it should work in `C++17+` though.

