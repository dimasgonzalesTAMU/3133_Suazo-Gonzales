#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

void parseStatus (std::string newline)
{
   std::string substr = "Name:";
   if(newline.find(substr) != std::string::npos)
   {
     printf("%s\n", newline.c_str());
   }

   substr = "State:";
   if(newline.find(substr) != std::string::npos)
   {
     printf("%s\n", newline.c_str());
   }

   substr = "Pid:";
   if(newline.find(substr) != std::string::npos  && newline.find("TracerPid") == std::string::npos)
   {
     printf("%s\n", newline.c_str());
   }

   substr = "ctxt_switches:";
   if(newline.find(substr) != std::string::npos)
   {
     printf("%s\n", newline.c_str());
   }

   substr = "Cpus_allowed";
   if(newline.find(substr) != std::string::npos)
   {
     printf("%s\n", newline.c_str());
   }

   substr = "Uid";
   if(newline.find(substr) != std::string::npos)
   {
     printf("\tReal|Effective|Saved Set|File System\n");
     printf("%s\n", newline.c_str());
   }

   substr = "Gid";
   if(newline.find(substr) != std::string::npos)
   {
     printf("\tReal|Effective|Saved Set|File System\n");
     printf("%s\n", newline.c_str());
   }

   substr = "FDSize:";
   if(newline.find(substr) != std::string::npos)
   {
     printf("------------------\n");
     printf("File Handles\n");
     printf("%s\n", newline.c_str());
     printf("------------------\n");
   }

   substr = "Threads:";
   if(newline.find(substr) != std::string::npos)
   {
     printf("Thread Info\n");
     printf("%s\n", newline.c_str());
   }

   substr = "Groups:";
   if(newline.find(substr) != std::string::npos)
   {
     printf("Group IDs\n");
     printf("%s\n", newline.c_str());
   }
}

void parseAutogroup(std::string newline)
{
  printf("Priority Niceness\n");
  printf("\t%s\n", newline.c_str());
}

void parseStat(std::ifstream &statFile)
{
    std::string str;
    for (int i = 0; i < 40; i++)
    {
      statFile >> str;
      switch (i) {
        case 13:
          printf("Utime: %s\n", str.c_str());
          break;
        case 14:
          printf("Stime: %s\n", str.c_str());
          break;
        case 15:
          printf("Cutime: %s\n", str.c_str());
          break;
        case 16:
          printf("Cstime: %s\n", str.c_str());
          break;
        case 18:
          printf("Priority Number: %s\n", str.c_str());
          break;
        case 19:
          printf("Nice Number: %s\n", str.c_str());
          break;
        case 24:
          printf("StartCode: %s\n", str.c_str());
          break;
        case 25:
          printf("EndCode: %s\n", str.c_str());
          break;
        case 27:
          printf("Esp: %s\n", str.c_str());
          break;
        case 28:
          printf("Eip: %s\n", str.c_str());
          break;
        case 39:
          printf("CPU Last Executed On: %s\n", str.c_str());
          break;
      }
    }
}

void parseMap(std::ifstream &mapFile)
{
    std::ofstream myfile;
    myfile.open ("maps.txt");
    myfile << "address           perms offset  dev   inode\t\t\t\t\tpathname\n";
    std::string str;
    while(std::getline(mapFile, str))
    {
      myfile << str << std::endl;
    }
    myfile.close();
}

void procManager(std::ifstream fileStream, int functionSelector)
{
    try
    {
        if (fileStream.good())
        {
          std::string str;
          while(std::getline(fileStream, str)){
            parseStatus(str);
          }
        }
        else
        {
            printf("Crap file is no good\n");
        }
    }
    catch(...)
    {
        printf("You had an error during read\n" );
    }

}




/*Global Options*/
std::string strPID = "";
void getOption(int argc, char *argv[ ])
{
    char option;

    //Specifying the expected options
    while ((option = getopt(argc, argv, "p:")) != -1)
    {
        switch (option) {
              case 'p' :
                  strPID = optarg;
                  break;
              case '?':
                  if (optarg == "p")
                    fprintf (stderr, "Option -%c requires an argument.\n", optarg);
                  else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n",  optarg);
              default:
                  abort ();
          }
    }
}

int main (int argc, char *argv[ ])
{
    getOption(argc, argv);

    try
    {
        if(strPID == "")
        {
            throw "Please enter a valid PID";
        }

        std::string filePath = "/proc/" + strPID + "/status";
        std::ifstream statusFile(filePath.c_str(), std::ifstream::in);
        if (statusFile.good())
        {
          std::string str;
          while(std::getline(statusFile, str))
          {
            parseStatus(str);
          }
        }
        else{
            throw "Status File fail during read";
        }

        std::string filePath3 = "/proc/" + strPID + "/stat";
        std::ifstream statFile(filePath3.c_str(), std::ifstream::in);
        if (statFile.good()) {
            parseStat(statFile);
        }
        else{
            throw "Stat File fail during read";
        }

        std::string filePath5 = "/proc/" + strPID + "/maps";
        std::ifstream mapFile(filePath5.c_str(), std::ifstream::in);
        if (statFile.good()) {
            parseMap(mapFile);
        }
        else{
            throw "Maps File fail during read";
        }
    }
    catch(char const* error)
    {
        printf("%s\n", error);
    }
    catch(...)
    {
        printf("You had an unknown error\n" );
    }

    return 0;

}
