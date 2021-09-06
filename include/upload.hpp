#pragma once
#include <string>

int sendfile(int socket_desc, std::string &filename);