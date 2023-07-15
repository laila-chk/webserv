#include "conf.hpp"

void ft_perr(std::string msg)
{
  std::cout << msg << std::endl;
  exit(1);
}

int main(int ac, char **av)
{

  if (ac != 2)
    ft_perr("Error: Bad argument\n");
  class conf config;
  getConf(av[1], config) ;
  std::cout << "pub is: " <<  config.pub << std::endl;
}

