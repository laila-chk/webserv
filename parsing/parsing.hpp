#ifndef PARSING_HPP
#define  PARSING_HPP

#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include  <cctype> 
#include <vector>


class locations
{
  private:

  public:
    std::string pattern;
    std::string methods;
    std::string redir_path;
    std::string root;
    bool        autoindex;
    //pair string string cgi extension + path
    std::string err_page;
    locations();
    ~locations();
};

class servers
{
  private:

  public:
    //	locations *location;
    std::vector <locations> loc;
    std::string  port;
    std::string   host;
    std::string   server_name;
    int client_max_body_size;
    servers();
    ~servers();
};

#endif
