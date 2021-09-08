#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../include/list.hpp"
#include "../include/rename.hpp"
#include "../include/delete.hpp"
#include "../include/transfer.hpp"

using namespace std;
#define PORT 2400
#define IP_ADDRESS "127.0.0.1"


int getUserInput(int socket_desc){

    while(true){
        char command[200];
        memset(command, '\0', sizeof(command));
        cout << "Enter Command(upload | download | list | delete | rename | exit): ";
        cin >> command;

        if(send(socket_desc, command, sizeof(command), 0) < 0){
            cout << "Unable to send command\n";
            return -1;
        }

        if(strcmp(command, "upload") == 0){
            string filename;

            // Get input from the user:
            cout << "Enter filename to upload: ";
            cin >> filename;

            sendfile(socket_desc, filename);
        
        } else if(strcmp(command, "download") == 0){
            string filename;

            cout << "Enter filename to fetch from server: ";
            cin >> filename;

            getfile(socket_desc, filename);

        } else if(strcmp(command, "list") == 0){

            getfilelist(socket_desc);
        } else if(strcmp(command, "delete") == 0){
            string filename;

            delete_file(socket_desc, filename);
        } else if(strcmp(command, "rename") == 0){
            string original_filename, new_filename;

            renamefile(socket_desc, original_filename, new_filename);
        } else if(strcmp(command, "exit") == 0){
            
            break;
        } else {
            cout << "Invalid Command" << endl;
        }
    }
    return 0;
}

int connect(){
    int socket_desc;
    struct sockaddr_in server_addr;
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        cout << "Unable to create socket\n";
        return -1;
    }
    
    cout << "Socket created successfully\n";
    
    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    
    // Send connection request to server:
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        cout << "Unable to connect\n";
        return -1;
    }
    cout << "Connected with server successfully\n";
    
    getUserInput(socket_desc);
    
    // Close the socket:
    close(socket_desc);
    return 0;
}