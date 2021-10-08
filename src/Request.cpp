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
        // cout << CYAN << "Enter Command(login | register | exit): " << RESET;
        // cin >> command;

        // trim(command);

        // if(command == "login"){
        //     // get login information and check it

        //     //break;
        // } else if(command == "register"){
        //     // register the user and get information

        //     //break;
        // } else if(command == "exit"){
        //     return;

        // } else {
        //     cout << RED << "Invalid Input!.\n" << RESET;
        // }
    // }
    
    print_help_message();

    while(true){
        cout << CYAN << "Enter Command(enter 'help' for help dialog): " << RESET;
        cin >> command;

        vector<string> tokens = ftp_tokenizer(command, ' ');

        // only shared repo works for now uncomment the code when private repo also starts working

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
        } else if(tokens[0] == "client"){

            cout << CYAN << "Enter Client Command: " << RESET;
            cin >> command;

            system(command.c_str());
            continue;
        } else if(tokens[0] == "help"){

            print_help_message();
            continue;
        } else {
            cout << RED << "Invalid Command" << RESET << endl;
        }
        break;
    }

    close(socket_desc);
    return;
}

void Request::print_help_message() {
    cout << YELLOW;
    cout << "Following commands are supported by the server:\n";
    cout << "client: Can be used to run a command locally without exiting\n";
    cout << "exit: Used to exit the client\n";
    cout << "help: displays this help dialog\n";
    cout << "\n";
    cout << "Following commands also support optional -g flag to access shared repo on Server:\n";
    cout << "list, download, upload, rename, delete\n\n";
    cout << "e.g:- 'list' will list files in private repo and 'list -g' will list files in shared repo\n";
    cout << "\n" << RESET;
}