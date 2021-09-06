#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sys/socket.h>

using namespace std;

int senddata(int socket_desc, const char *buffer, const int size){

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

int recvdata(int socket_desc, char* buffer){
    int file_size = 0;

    if (recv(socket_desc, &file_size, sizeof(int), 0) < 0){
        cout << "Couldn't receive\n";
        return 0;
    }
    cout << "Size of file: " << file_size << "\n";

    buffer = new char[file_size];

    if(recv(socket_desc, buffer, file_size, 0) < 0){
        cout << "Couldn't receive\n";
        return 0;
    }
    
    return file_size;
}