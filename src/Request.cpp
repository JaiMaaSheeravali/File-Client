#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../include/request.hpp"
#include "../include/color.hpp"
#include "../include/parse.hpp"

using namespace std;

Request::Request(int socket_id) {
    socket_desc = socket_id;
    login = "testuser";
    password = "Pa$$w0rd";
    isGlobal = true;
    transferEndFlag = "done\n";
}

void Request::handle_request(){
    
    
    string command;

    // uncomment after proper implementation
    // while(true){
        cout << CYAN << "Enter Command(login | register | exit): " << RESET;
        cin >> command;

        trim(command);

        if(command == "login"){
            // get login information and check it

            break;
        } else if(command == "register"){
            // register the user and get information

            break;
        } else if(command == "exit"){
            return;

        } else {
            cout << RED << "Invalid Input!.\n" << RESET;
        }
    // }
    

    while(true){
        cout << CYAN << "Enter Command(upload | download | list | delete | rename | exit)(optional -g): " << RESET;
        cin >> command;

        vector<string> tokens = ftp_tokenizer(command, ' ');

        // if(tokens.size() > 1 && tokens[1] == "-g")
        //     isGlobal = true;
        // else
        //     isGlobal = false;

        ftpRequest = "login " + login + " " + password + "\n";

        if(tokens[0] == "upload"){

            send_file();
        } else if(tokens[0] == "download"){

            get_file();
        } else if(tokens[0] == "list"){

            get_file_list();
        } else if(tokens[0] == "delete"){

            delete_file();
        } else if(tokens[0] == "rename"){
            
            rename_file();
        } else if(tokens[0] == "exit"){
            
            break;
        } else {
            cout << RED << "Invalid Command" << RESET << endl;
        }
        break;
    }

    close(socket_desc);
    return;
}