#include<iostream>
#include<string>
#include <cstring>

#include "../include/color.hpp"
#include "../include/request.hpp"
#include "../include/parse.hpp"

using namespace std;

int Request::login_user(){
    cout << CYAN << "Enter your username: " << RESET;
    getline(cin, username);
    trim(username);
    cout << CYAN << "Enter your password: " << RESET;
    getline(cin, password);
    trim(password);

    ftpRequest = "login " + username + " " + password + "\n";
    ftpRequest += transferEndFlag;

    buffer = new char[ftpRequest.size()+1];
    memset(buffer, '\0', ftpRequest.size()+1);

    strcpy(buffer, ftpRequest.c_str());
    bytes_left = ftpRequest.size()+1;
    sendDataToServer();

    char ack = recvAck();

    if(ack == '0'){
        cout << GREEN << "Successfully logged in to Server!\n" << RESET;
    } else if(ack == '1') {
        cout << RED << "Login Failed! Please check you username and password.\n" << RESET;
        return 0; 
    }

    return 1;
}

int Request::register_user(){
    cout << CYAN << "Enter your username: " << RESET;
    getline(cin, username);
    trim(username);
    cout << CYAN << "Enter your password: " << RESET;
    getline(cin, password);
    trim(password);

    ftpRequest = "register " + username + " " + password + "\n";
    ftpRequest += transferEndFlag;

    buffer = new char[ftpRequest.size()+1];
    memset(buffer, '\0', ftpRequest.size()+1);

    strcpy(buffer, ftpRequest.c_str());
    bytes_left = ftpRequest.size()+1;
    sendDataToServer();

    char ack = recvAck();

    if(ack == '0'){
        cout << GREEN << "Successfully Registered to Server!\n" << RESET;
    } else if(ack == '1') {
        cout << RED << "Register Failed! Please check you username and password.\n" << RESET; 
        return 0;
    } else if(ack == '2'){
        cout << GREEN << "User already exists logging in to existing account instead.\n" << RESET;
    } else if(ack == '3'){
        cout << RED << "Username: " + username << " already exists on server! Retry with another username or login instead.\n" << RESET;
        return 0;
    }

    return 1;
}