#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <algorithm>

#include "../include/request.hpp"
#include "../include/color.hpp"
#include "../include/parse.hpp"
#include "../include/socket.hpp"

using namespace std;

Request::Request(int socket_id) {
    socket_desc = socket_id;
    username = "";
    password = "";
    isGlobal = true;
    transferEndFlag = "done\n";
}

void Request::handle_request(){

    // uncomment after proper implementation
    while(true){
        string command;
        cout << CYAN << "Enter Command(login | register | exit): " << RESET;
        getline(cin, command);
        transform(command.begin(), command.end(), command.begin(), ::tolower);

        trim(command);

        if(command == "login"){
            // login the user and get the information
            if(login_user())
                break;
            
        } else if(command == "register"){
            // register the user and get information
            if(register_user())
                break;

        } else if(command == "exit"){
            close(socket_desc);
            return;
            
        } else {
             cout << RED << "Invalid Input!.\n" << RESET;
             continue;
        }
        close(socket_desc);
        connectToServer();
    }
    
    print_help_message();

    while(true){
        string command;
        cout << CYAN << "Enter Command(enter 'help' for help dialog): " << RESET;
        getline(cin, command, '\n');
        transform(command.begin(), command.end(), command.begin(), ::tolower);
        
        vector<string> tokens = ftp_tokenizer(command, ' ');

        // only shared repo works for now uncomment the code when private repo also starts working

        if(tokens.size() > 1 && tokens[1] == "-g")
            isGlobal = true;
        else
            isGlobal = false;

        ftpRequest = "login " + username + " " + password + "\n";

        if(tokens.empty())
            continue;

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

            string client_command;
            cout << CYAN << "Enter Client Command: " << RESET;
            getline(cin, client_command);

            system(client_command.c_str());
            continue;
        } else if(tokens[0] == "help"){

            print_help_message();
            continue;
        } else {
            cout << RED << "Invalid Command" << RESET << endl;
            continue;
        }

        close(socket_desc);
        connectToServer();
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

void Request::connectToServer(){
    socket_desc = connect();
    if(socket_desc == -1){
        cerr << "Unable to Reconnect to server\n";
    }
}