#include "../include/initParameters.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>

std::vector<std::string> extractParametreAndValue(char* argument)
{
    std::string parametre = "";
    std::string value = "";
    bool foundEqual = false;

    for (int j=2; j<std::strlen(argument); j++)
    {
        if (argument[j]!='=')
        {
            if (!foundEqual){parametre += argument[j];}
            else {value += argument[j];}
        }
        else
        {
            foundEqual = true;
        }
    }

    return std::vector<std::string> {parametre, value};
}

bool initParameters(int argc, char* argv[], int &mapSizeX, int &mapSizeY)
{
    std::vector<std::string> parametres = {"help", "mazeSizeX", "mazeSizeY"};

    for (int i=1; i<argc; i++)
    {
        if (argv[i][0] != '-'){}

        if (argv[i][0] == '-' && argv[i][1] != '-'){}

        if (argv[i][0] == '-' && argv[i][1] == '-')
        {
            std::vector<std::string> argument = extractParametreAndValue(argv[i]);

            if (argument[0] == parametres[0])
            {
                std::cout << "Usable parameters:" << std::endl;

                for (int j=0; j<parametres.size(); j++)
                {
                    std::cout << "--" << parametres[j] << " ";
                }

                std::cout << std::endl;

                return true;
            }

            if (argument[0] == parametres[1])
            {
                char valueInChars[argument[1].size()];
                for (int j=0; j<argument[1].size(); j++)
                {
                    valueInChars[j] = argument[1][j];
                }

                mapSizeX = std::atoi(valueInChars);

                if (mapSizeX<=0 || mapSizeX%2==0)
                {
                    std::cerr << "Parameter \"" << parametres[1] << "\" must be odd and positive integer" << std::endl;
                    return true;
                }
            }

            if (argument[0] == parametres[2])
            {
                char valueInChars[argument[1].size()];
                for (int j=0; j<argument[1].size(); j++)
                {
                    valueInChars[j] = argument[1][j];
                }

                mapSizeY = std::atoi(valueInChars);

                if (mapSizeX<=0 || mapSizeX%2==0)
                {
                    std::cerr << "Parameter \"" << parametres[2] << "\" must be odd and positive integer" << std::endl;
                    return true;
                }
            }
        }
    }

    return false;
}
