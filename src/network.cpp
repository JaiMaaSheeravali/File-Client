#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/request.hpp"
#include "../include/color.hpp"

using namespace std;

int Request::send_data(const char *buffer, const int size){

    if(send(socket_desc, &size, sizeof(int), 0) < 0){
        cerr << RED << "Unable to send message size\n" << RESET;
        return -1;
    }
    if(send(socket_desc, buffer, size, 0) < 0){
        cerr << RED << "Unable to send message content\n" << RESET;
        return -1;
    }
    return 0;
}

int Request::recv_data(const char* filename){
    int file_size = 0;

    if (recv(socket_desc, &file_size, sizeof(int), 0) < 0){
        cerr << RED << "Couldn't receive\n" << RESET;
        return 0;
    }

    char buffer[file_size];

    if(recv(socket_desc, buffer, file_size, 0) < 0){
        cerr << RED << "Couldn't receive\n" << RESET;
        return 0;
    }
    ofstream file(filename, ios::out|ios::binary);
    file.write(buffer, file_size);

    return file_size;
}


char* Request::recv_string(){
    int file_size = 0;

    if (recv(socket_desc, &file_size, sizeof(int), 0) < 0){
        cerr << RED << "Couldn't receive\n" << RESET;
    }

    char *buffer = new char[file_size+1];
    buffer[file_size] = '\0';

    if(recv(socket_desc, buffer, file_size, 0) < 0){
        cerr << RED << "Couldn't receive\n" << RESET;
        return buffer;
    }
    return buffer;
}