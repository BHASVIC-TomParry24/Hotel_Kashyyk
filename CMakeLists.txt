cmake_minimum_required(VERSION 3.29)
project(Hotel_Kashyyk C)

set(CMAKE_C_STANDARD 11)

add_executable(Hotel_Kashyyk main.c
        checkIn.c
        bookTable.c
        checkOut.c
        read.c
        writeFile.c)
