#ifndef PARSING_HPP
#define PARSING_HPP

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "include.hpp"

class locations {
  private:
  public:
    std::string pattern;
    std::vector<std::string> methods;
    std::string redir_path;
    std::string root;
    bool autoindex;
<<<<<<< HEAD
    std::vector<std::string> def_files;
=======
    std::string def_files;
    //Change from vec of pairs into map for easier handling + bonus
//    std::vector<std::pair<std::string, std::string> > cgi;
>>>>>>> origin/multiplex
    std::map<std::string, std::string> cgi;
    locations();
    locations(const locations & obj);
    ~locations();
};

// Change it from 'servers' to 'Config'
class Config {
  private:
  public:
    std::vector<locations> loc;
    std::string address;
    int         port;
    std::string server_name;
    int client_max_body_size;
    std::map<int, std::string> error_pages;
    Config();
    ~Config();
};

#endif
