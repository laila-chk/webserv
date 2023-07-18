#include <iostream>


class locations
{
	std::string root;
  std::string pattern;
	std::string err_page;
  int client_max_body_size;
};

class servers
{
	locations *location;
  std::string  port;
  std::string   host;
  std::string   server_name;
  int client_max_body_size;

};
