#include "conf.hpp"

void getConf(char *str, class conf& config)
{
  std::cout << "getConf called" << std::endl << str  << std::endl;
  config.pub = "get" ;
}
