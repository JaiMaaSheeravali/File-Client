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
    send_data(filename.c_str(), filename.size());

    recv_data(filename.c_str());

    cout << GREEN << "Successfully received '" << filename << "' from Server.\n" << RESET;

    return 0;
}

int Request::send_file(){
    string filename;

    // Get input from the user:
    cout << CYAN << "Enter filename to upload: " << RESET;
    cin >> filename;

    send_data(filename.c_str(), filename.size());

    //open file in binary mode, get pointer at the end of the file (ios::ate)
    ifstream file (filename, ios::in|ios::binary|ios::ate); 

    //retrieve get pointer position
    int file_size = file.tellg();

    //position get pointer at the begining of the file                                   
    file.seekg (0, ios::beg);                                   
    char buffer[file_size];                                          
    file.read (buffer, file_size);                                   
    file.close();                                               

    send_data(buffer, file_size);

    cout << GREEN << "Successfully sent '" << filename << "' to Server.\n" << RESET;
    
    return 0;
}