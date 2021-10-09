#include<iostream>
#include<string>
#include <cstring>

#include "../include/color.hpp"
#include "../include/request.hpp"

using namespace std;

int Request::login_user(){
    string user, pass;
    cout << CYAN << "Enter your username: " << endl;
    cin >> user;
    cout << CYAN << "Enter your password: " << endl;
    cin >> pass;
    username = user;
    password = pass;

    ftpRequest = "login " + username + " " + password + "\n";
    ftpRequest += transferEndFlag;

    buffer = new char[ftpRequest.size()+1];
    memset(buffer, '\0', ftpRequest.size()+1);

    strcpy(buffer, ftpRequest.c_str());
    bytes_left = ftpRequest.size()+1;
    sendDataToServer();

    return 1;
}

int Request::register_user(){
    string user, pass;
    cout << CYAN << "Enter the username to register: " << endl;
    cin >> user;
    cout << CYAN << "Enter your password: " << endl;
    cin >> pass;
    return 0;
}