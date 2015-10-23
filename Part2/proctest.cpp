#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

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
   if(newline.find(substr) != std::string::npos)
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
     printf("---------GUID---------\n");

     printf("\tReal|Effective|Saved Set|File System\n");
     printf("%s\n", newline.c_str());
     printf("---------GUID---------\n");
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



int main ()
{
    char filePath[50] = "/proc/2964/status";
    std::ifstream statusFile(filePath, std::ifstream::in);
    try
    {
        if (statusFile.good())
        {
          std::string str;
          while(std::getline(statusFile, str)){
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

    char filePath2[50] = "/proc/2964/autogroup";
    std::ifstream autoFile(filePath2, std::ifstream::in);
    try
    {
        if (autoFile.good())
        {
          std::string str;
          while(std::getline(autoFile, str)){
            parseAutogroup(str);
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

    char filePath3[50] = "/proc/2964/stat";
    std::ifstream statFile(filePath3, std::ifstream::in);
    try
    {
        if (statFile.good())
        {
          std::string str;
          for (int i = 0; i < 29; i++)
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
            }
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



    return 0;

}
