#include "conf.hpp"
#include "parsing.hpp"
#include <algorithm>

void ft_perr(std::string msg)
{
  std::cout << msg << std::endl;
  exit(1);
}

void servers_count(int &i, int &j, std::string path)
{
  std::string buff;
  std::ifstream file(path);
  std::string word;

  while (getline(file, buff))
  {
    buff.erase(std::remove_if(buff.begin(), buff.end(), isspace), buff.end());
    std::stringstream  buffer(buff);

    if ((!buff.compare(0, 6,"server") && buff.length() > 6) || (!buff.compare(0, 8,"location") && buff.length() > 8))
      ft_perr("Error, bad syntax!");
    
    if(!buff.compare("server"))
      i++;
    else if(!buff.compare("location"))
      j++;
  }
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
  servers_count(i, j, path);

  std::cout << "total servrers: " << i << " and tot locations is : " << j << std::endl;
}

