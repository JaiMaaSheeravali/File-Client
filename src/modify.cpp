#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/request.hpp"
#include "../include/color.hpp"

using namespace std;

int Request::rename_file(){
    string original_filename, new_filename;

    cout << CYAN << "Enter current name of file: " << RESET;
    cin >> original_filename;

    cout << CYAN << "Enter updated name of file: " << RESET;
    cin >> new_filename;

    send_data(original_filename.c_str(), original_filename.size());
    send_data(new_filename.c_str(), new_filename.size());

    cout << GREEN << "Successfully renamed '" << original_filename << "' to '" << new_filename << "'.\n" << RESET;
    
    return 0;
}


int Request::delete_file(){
    string filename;

    cout << CYAN << "Enter filename to delete: " << RESET;
    cin >> filename;

    send_data(filename.c_str(), filename.size());

    cout << GREEN << "Successfully deleted '" << filename << "' from Server.\n" << RESET;
    return 0;
}

int Request::get_file_list(){
    cout << YELLOW;
    cout << recv_string() << endl;
    cout << RESET;
    return 0;
}