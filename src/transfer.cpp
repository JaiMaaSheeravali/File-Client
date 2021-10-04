#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/request.hpp"
#include "../include/color.hpp"

using namespace std;

int Request::get_file(){
    string filename;

    cout << CYAN << "Enter filename to fetch from server: " << RESET;
    cin >> filename;
    
    ftpRequest += "download ";

    if(isGlobal)
        ftpRequest += "-g ";
    
    ftpRequest += filename + "\n";
    ftpRequest += transferEndFlag;

    buffer = new char[ftpRequest.size()+1];
    buffer[ftpRequest.size()] = '\0';

    strcpy(buffer, ftpRequest.c_str());

    cout << buffer << endl;

    bytes_left = ftpRequest.size()+1;

    sendDataToServer();

    char *result = recvDataFromServer();

    ofstream file(filename, std::ios::out);
    file.write(result, strlen(result));


    cout << GREEN << "Successfully received '" << filename << "' from Server.\n" << RESET;

    return 0;
}

int Request::send_file(){
    string filename;

    // Get input from the user:
    cout << CYAN << "Enter filename to upload: " << RESET;
    cin >> filename;

    //open file in binary mode, get pointer at the end of the file (ios::ate)
    std::ifstream file(filename, std::ios::in|std::ios::ate); 

    //retrieve get pointer position
    int file_size = file.tellg();

    ftpRequest += "upload ";

    if(isGlobal)
        ftpRequest += "-g ";
    
    ftpRequest += to_string(file_size) + " " + filename + "\n";
    ftpRequest += transferEndFlag;

    buffer = new char[ftpRequest.size()+1];
    memset(buffer, '\0', ftpRequest.size()+1);

    strcpy(buffer, ftpRequest.c_str());

    cout << buffer << endl;

    bytes_left = ftpRequest.size()+1;

    sendDataToServer();

    cout << "Request Sent\n";

    cout << file_size << endl;

    file.seekg (0, std::ios::beg);
    buffer = new char[file_size];
    char *temp = buffer;
    file.read(buffer, file_size);
    file.close();

    bytes_left = file_size;

    cout << "File Read\n";
    
    sendDataToServer();


    delete[] temp;

    cout << GREEN << "Successfully sent '" << filename << "' to Server.\n" << RESET;
    
    return 0;
}

int Request::sendDataToServer(){

    while (bytes_left > 0)
    {
        // perform non blocking io on the socket file descriptor
        if ((bytes_sent = send(socket_desc, buffer, bytes_left, 0)) == -1)
        {
            perror("failed file transfer");
            // send(NACK)
            return -1;
        }
        // std::cout << "bytes sent yet: " << bytes_sent << std::endl;
        buffer += bytes_sent;
        bytes_left -= bytes_sent;
    }

    // send(ACK)
    return 1;
}


char* Request::recvDataFromServer(){
    int file_size = 0;

    if (recv(socket_desc, &file_size, sizeof(int), 0) < 0){
        cerr << RED << "Couldn't receive\n" << RESET;
    }
    //file_size = ntohl(file_size);
    cout << "File Size " << file_size << endl;

    char *buffer = new char[file_size];
    char *result = buffer;
    bytes_left = file_size;
    bytes_sent = 0;

    while (bytes_left > 0)
    {
        // perform non blocking io on the socket file descriptor
        if (((bytes_sent = recv(socket_desc, buffer, bytes_left, 0)) == -1))
        {
            cerr << "failed data transfer";
            // send(NACK)
            return result;
        }
        // std::cout << "bytes received yet: " << bytes_sent << std::endl;
        buffer += bytes_sent;
        bytes_left -= bytes_sent;
    }

    return result;
}