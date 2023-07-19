#ifndef PARSING_HPP
#define  PARSING_HPP

#include <string>
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
  	std::string root;
    std::string pattern;
  	std::string err_page;
    int client_max_body_size;
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
