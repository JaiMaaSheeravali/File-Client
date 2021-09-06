#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sys/socket.h>

#include "./include/transfer.hpp"

using namespace std;

int getfile(int socket_desc, string &filename){

    int filename_size = filename.size();

    // Send the message to server:
    if(send(socket_desc, &filename_size, sizeof(int), 0) < 0){
        cout << "Unable to send message\n";
        return -1;
    }
    
    // Send the message to server:
    if(send(socket_desc, filename.c_str(), filename_size, 0) < 0){
        cout << "Unable to send message\n";
        return -1;
    }

    int file_size = 0;

    if (recv(socket_desc, &file_size, sizeof(int), 0) < 0){
        cout << "Couldn't receive\n";
        return -1;
    }
    cout << "Msg from client: " << file_size << "\n";

    char buffer[file_size];

    if(recv(socket_desc, buffer, file_size, 0) < 0){
        cout << "Couldn't receive\n";
        return -1;
    }

    ofstream file (filename, ios::out|ios::binary);

    file.write(buffer, file_size);

    return 0;
}