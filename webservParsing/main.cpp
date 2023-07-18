#include "conf.hpp"
#include "parsing.hpp"

void servers_count(int &i, int &j)
{
  :wq

}

void ft_perr(std::string msg)
{
  std::cout << msg << std::endl;
  exit(1);
}

int main(int ac, char **av)
{
  std::string path;

  if (ac >= 3)
    ft_perr("Error!\nusage: ./webserv [configuration file]\n");
  else if (ac == 1) 
    path = "default.conf";
  else if (ac == 2)
    path = av[1];

  int i = 0;
  int j = 0;
  servers_count(&i, &j, path);

}

