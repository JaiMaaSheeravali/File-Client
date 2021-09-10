#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/request.hpp"

using namespace std;

int Request::rename_file(){
    string original_filename, new_filename;

    cout << "Enter current name of file: ";
    cin >> original_filename;

    cout << "Enter updated name of file: ";
    cin >> new_filename;

    send_data(original_filename.c_str(), original_filename.size());
    send_data(new_filename.c_str(), new_filename.size());
    
    return 0;
}


int Request::delete_file(){
    string filename;

    cout << "Enter filename to delete: ";
    cin >> filename;

    send_data(filename.c_str(), filename.size());
    return 0;
}

int Request::get_file_list(){

    cout << recv_string() << endl;
    return 0;
}