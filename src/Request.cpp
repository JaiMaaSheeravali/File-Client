#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>

#include "../include/request.hpp"
#include "../include/color.hpp"

using namespace std;

void Request::handle_request(){

    while(true){
        char command[200];
        memset(command, '\0', sizeof(command));
        cout << CYAN << "Enter Command(upload | download | list | delete | rename | exit): " << RESET;
        cin >> command;

        if(send(socket_desc, command, sizeof(command), 0) < 0){
            cout << RED << "Unable to send command\n" << RESET;
            return;
        }

        if(strcmp(command, "upload") == 0){

            send_file();
        } else if(strcmp(command, "download") == 0){
            

            get_file();
        } else if(strcmp(command, "list") == 0){

            get_file_list();
        } else if(strcmp(command, "delete") == 0){
            

            delete_file();
        } else if(strcmp(command, "rename") == 0){
            
            rename_file();
        } else if(strcmp(command, "exit") == 0){
            
            break;
        } else {
            cout << RED << "Invalid Command" << RESET << endl;
        }
    }

    close(socket_desc);
    return;
}