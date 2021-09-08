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

int recv_data(int socket_desc, const char* filename){
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


char* recv_string(int socket_desc){
    int file_size = 0;

    if (recv(socket_desc, &file_size, sizeof(int), 0) < 0){
        cout << "Couldn't receive\n";
    }
    cout << "Size of file: " << file_size << "\n";

    char *buffer = new char[file_size];

    if(recv(socket_desc, buffer, file_size, 0) < 0){
        cout << "Couldn't receive\n";
        return buffer;
    }
    return buffer;
}

int getfile(int socket_desc, string &filename){

    senddata(socket_desc, filename.c_str(), filename.size());

    recv_data(socket_desc, filename.c_str());

    return 0;
}

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