#include "conf.hpp"
#include "parsing.hpp"

void ft_perr(std::string msg)
{
  std::cout << msg << std::endl;
  exit(1);
}

bool directive(std::string buff, std::vector<std::string> serv_dirs, servers &srv)
{
  if (!buff.compare("{"))
    return true;
  int j = 0;

  std::vector<std::string> words;
  for(size_t i = 0; i < buff.length(); i++)
  {
    if (buff[i] == ' ' || buff[i] == '\t' || buff[i] == ';')
    {
      words.push_back(buff.substr(j, i - j));
      while (buff[i] == ' ' || buff[i] == '\t' || buff[i] == ';')
        i++;
      j = i;
    }
  }

   for (int i = 0; i < 4; i++)
   {
    //std::cout << words[0]<< std::endl;
      if (!words[0].compare(serv_dirs[i]))
      {
       //get what class var to store in:
       
        if (!words[0].compare("server_name"))
          srv.server_name = words[1];
        else if (!words[0].compare("listen"))
          srv.port = words[1];
       return true;
      }
   }
  return false;
  //compare words[0] to all directives to check wether it is falid or nah
  //return (serv_dirs.size());
}

void  dirs(std::vector<std::string> &serv_dirs)
{
  // we cann later add location directives too, since they will be know by their indexs.
  serv_dirs.push_back("server_name");
  serv_dirs.push_back("listen");
  serv_dirs.push_back("error_page");
  serv_dirs.push_back("client_max_body_size");
//  serv_dirs.push_back("root");
//  ma3raftchi wach ghadrcha9li ndir chi root f serv wla la :3
}

void contexts_count(std::vector<servers> &srvs, std::string path)
{
  std::string buff;
  std::ifstream file(path);
  std::string word;
  std::vector<std::string> serv_dirs;
  int   i = 0;
  bool inSer = false;
  bool inLoc = false;
  int j = 0;

  dirs(serv_dirs);
  if (file.fail())
    ft_perr("Error: Bad file permissions, or file doesn't exist!");
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
    else if(!buff.compare("server") && inSer)
      ft_perr("Error: Server can't exist within a context");

    if(inSer && (buff.compare(0, 8,"location") == 0 && buff.length() == 8))
    {
      srvs[i-1].loc.push_back(locations());

      getline(file, buff);
      buff.erase(std::remove_if(buff.begin(), buff.end(), isspace), buff.end());
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

    else if (!directive(buff, serv_dirs, srvs[i-1]))
      ft_perr("Error: Uknown directive!");
  std::cout << "i is now = " << i << std::endl;
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

  std::cout << "The length of serv: " << servs.size() << std::endl;
  std::cout << "The length of locs: " << servs[0].loc.size() << std::endl;
  std::cout << "we have stored in serv " << servs[0].port << "." << std::endl;
  std::cout << "we have stored in serv " << servs[0].server_name <<"." << std::endl;


}
