#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/request.hpp"
#include "../include/color.hpp"
#include "../include/parse.hpp"

using namespace std;

int Request::rename_file(){
    string original_filename, new_filename;

    cout << CYAN << "Enter current name of file: " << RESET;
    getline(cin, original_filename);
    trim(original_filename);

    cout << CYAN << "Enter updated name of file: " << RESET;
    getline(cin, new_filename);
    trim(new_filename);

    //send_data(original_filename.c_str(), original_filename.size());
    //send_data(new_filename.c_str(), new_filename.size());

    ftpRequest += "rename ";

    if(isGlobal){
        ftpRequest += "-g ";
    }

    ftpRequest += original_filename + " " + new_filename + "\n";
    ftpRequest += transferEndFlag;

    buffer = new char[ftpRequest.size()+1];
    buffer[ftpRequest.size()] = '\0';
    strcpy(buffer, ftpRequest.c_str());

    bytes_left = ftpRequest.size()+1;

    sendDataToServer();

    char ack = recvAck();

    if(ack == '0')
        cout << GREEN << "Successfully renamed '" << original_filename << "' to '" << new_filename << "'.\n" << RESET;
    else if(ack == '1')
        cout << RED << "Server Error Renaming '" << original_filename << "' to '"<< new_filename << "'!\n" << RESET;
    else if(ack == '2')
        cout << RED << "Rename Error: File " << original_filename << " doesn't exist on server!\n" << RESET;
    else if(ack == '3')
        cout << RED << "Rename Error: File " << new_filename << " already exist on server can't overwrite!\n" << RESET;

    return 0;
}


int Request::delete_file(){
    string filename;

    cout << CYAN << "Enter filename to delete: " << RESET;
    getline(cin, filename);
    trim(filename);

    //send_data(filename.c_str(), filename.size());

    ftpRequest += "delete ";

    if(isGlobal){
        ftpRequest += "-g ";
    }

    ftpRequest += filename + "\n";
    ftpRequest += transferEndFlag;

    buffer = new char[ftpRequest.size()+1];
    buffer[ftpRequest.size()] = '\0';
    strcpy(buffer, ftpRequest.c_str());

    bytes_left = ftpRequest.size()+1;

    sendDataToServer();

    char ack = recvAck();

    if(ack == '0')
        cout << GREEN << "Successfully deleted '" << filename << "' from server.\n" << RESET;
    else if(ack == '1')
        cout << RED << "Server Error Deleting '" << filename << "'!\n" << RESET;
    else if(ack == '2')
        cout << RED << "Delete Error: File '" << filename << "' doesn't exist on server!\n" << RESET;

    return 0;
}

int Request::get_file_list(){

    ftpRequest += "list";
    if(isGlobal)
        ftpRequest += " -g";

    ftpRequest += "\n" + transferEndFlag;

    buffer = new char[ftpRequest.size()+1];
    buffer[ftpRequest.size()] = '\0';
    strcpy(buffer, ftpRequest.c_str());

    bytes_left = ftpRequest.size()+1;

    sendDataToServer();

    char* fileList = recvDataFromServer();

    cout << YELLOW;
    cout << fileList << endl;
    cout << RESET;

    delete[] fileList;
    return 0;
}