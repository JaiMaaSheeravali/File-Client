#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/request.hpp"

using namespace std;

int Request::send_data(const char *buffer, const int size){

    if(send(socket_desc, &size, sizeof(int), 0) < 0){
        cout << "Unable to send message size\n";
        return -1;
    }
    if(send(socket_desc, buffer, size, 0) < 0){
        cout << "Unable to send message content\n";
        return -1;
    }
    return 0;
}

int Request::recv_data(const char* filename){
    int file_size = 0;

    if (recv(socket_desc, &file_size, sizeof(int), 0) < 0){
        cout << "Couldn't receive\n";
        return 0;
    }
    cout << "Size of file: " << file_size << "\n";

    char buffer[file_size];

    if(recv(socket_desc, buffer, file_size, 0) < 0){
        cout << "Couldn't receive\n";
        return 0;
    }
    ofstream file(filename, ios::out|ios::binary);
    file.write(buffer, file_size);

    return file_size;
}


char* Request::recv_string(){
    int file_size = 0;

    if (recv(socket_desc, &file_size, sizeof(int), 0) < 0){
        cout << "Couldn't receive\n";
    }
    cout << "Size of file: " << file_size << "\n";

    char *buffer = new char[file_size+1];
    buffer[file_size] = '\0';

    if(recv(socket_desc, buffer, file_size, 0) < 0){
        cout << "Couldn't receive\n";
        return buffer;
    }
    return buffer;
}