#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/transfer.hpp"


using namespace std;

int sendfile(int socket_desc, string &filename){

    senddata(socket_desc, filename.c_str(), filename.size());

    //open file in binary mode, get pointer at the end of the file (ios::ate)
    ifstream file (filename, ios::in|ios::binary|ios::ate); 

    //retrieve get pointer position
    int file_size = file.tellg();

    //position get pointer at the begining of the file                                   
    file.seekg (0, ios::beg);                                   
    char buffer[file_size];                                          
    file.read (buffer, file_size);                                   
    file.close();                                               

    senddata(socket_desc, buffer, file_size);
    
    return 0;
}