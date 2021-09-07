#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>

using namespace std;


int getfilelist(int socket_desc){

    // while(true){
    //     int filename_size = 0;

    //     // Receive client's message:
    //     if (recv(socket_desc, &filename_size, sizeof(int), 0) < 0){
    //         cout << "Couldn't receive\n";
    //         return -1;
    //     }
    //     char file_name[filename_size+1];
    //     memset(file_name, '\0', sizeof(file_name));

    //     if(recv(socket_desc, file_name, sizeof(file_name), 0) < 0){
    //         cout << "Couldn't receive\n";
    //         return -1;
    //     }

    //     if(strcmp(file_name, "$end-transmission$"))
    //         break;
        
    //     cout << file_name << "\n";
    // }
    return 0;
}