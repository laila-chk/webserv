#include "conf.hpp"
#include "parsing.hpp"
#include <algorithm>

void servers_count(int &i, int &j, std::string path)
{
  std::string buff;
  std::ifstream file(path);
  std::string word;

  while (getline(file, buff))
  {
//      std::cout << buff  << "    is bf" << std::endl;
    std::stringstream  buffer(buff);
     buffer.erase(0, buffer.find_first_not_of('\t'));
      getline(buffer, word, ' ');
      word.erase(std::remove_if(word.begin(), word.end(), isspace), word.end());
      std::cout << word << "    is word" << std::endl;
      if(!word.compare("server"))
        i++;
      else if(!word.compare("location"))
        j++;
  }

  std::cout << "total servrers: " << i << " and tot locations is : " << j << std::endl;

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
  servers_count(i, j, path);

  std::cout << "total servrers: " << i << " and tot locations is : " << j << std::endl;
}

