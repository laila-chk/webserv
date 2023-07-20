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
  int   i = 0;
  bool inSer = false;
  bool inLoc = false;
  int j = 0;

  if (file.fail())
    ft_perr("Error: Bad file permissions or file doesn't exist!");
  while (getline(file, buff))
  {
    buff.erase(0, buff.find_first_not_of(" \t"));
     j = buff.length() - 1;
     while (j > 0 && (buff[j] == ' ' || buff[j] == '\t'))
       j--;
    buff.erase(j+1, buff.length());

   if (!inSer && (!buff.compare(0, 6,"server") && buff.length() > 6))
      ft_perr("Error: bad syntax!");

    if(!buff.compare("server") && !inSer)
    {
      srvs.push_back(servers());
      getline(file, buff);
      buff.erase(std::remove_if(buff.begin(), buff.end(), isspace), buff.end());
      if (buff.compare("{") != 0) 
        ft_perr("Error: Opening bracket is missing !");
      inSer = true;
      i++;
    }
    if(!buff.compare("server") && inSer)
      ft_perr("Error: Server can't exist within a context");

    if(inSer && (buff.compare(0, 8,"location")==0 && buff.length() == 8))
    {
      srvs[i-1].loc.push_back(locations());


      getline(file, buff);
      buff.erase(std::remove_if(buff.begin(), buff.end(), isspace), buff.end());
      // std::stringstream  buffer(buff);
      //
      if (buff.compare("{") != 0) 
        ft_perr("Error: Opening bracket is missing for location!");
      inLoc = true;
    }
    else if(inSer && (!buff.compare(0, 8,"location") && buff.length() != 8))
      ft_perr("Error: bad syntax!");
     if (inLoc && !buff.compare("}"))
       inLoc = false;

     else if (inSer && !buff.compare("}"))
       inSer = false;


  }
  // note that is may be possible to use inly inser and inloc instead of ser_bracket and loc_bracket
  if (inSer || inLoc)
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
