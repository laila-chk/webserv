#include "conf.hpp"
#include "parsing.hpp"

void ft_perr(std::string msg)
{
  std::cout << msg << std::endl;
  exit(1);
}

void contexts_count(std::vector<servers> &srvs, std::string path)
{
  std::string buff;
  std::ifstream file(path);
  std::string word;
  int   ob = 0;
  int   cb = 0;
  int   i = 0;

  while (getline(file, buff))
  {
    buff.erase(std::remove_if(buff.begin(), buff.end(), isspace), buff.end());
    std::stringstream  buffer(buff);

    if ((!buff.compare(0, 6,"server") && buff.length() > 6) || (!buff.compare(0, 8,"location") && buff.length() > 8))
      ft_perr("Error: bad syntax!");
    
    if(!buff.compare("server"))
    {
      srvs.push_back(servers());
      i++;
    }
    else if(!buff.compare("location"))
    {
      srvs[i-1].loc.push_back(locations());
    }
    else if (!buff.compare("{"))
      ob++;
    else if (!buff.compare("}"))
      cb++;
  }
  if (ob != cb)
    ft_perr("Error: missing Bracket!");
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

  std::vector<servers> servs;
  contexts_count(servs, path);
  
  std::cout << "The length of serv: " << servs.size() ;
  std::cout << "The length of locs: " << servs[0].loc.size() ;
  

}
