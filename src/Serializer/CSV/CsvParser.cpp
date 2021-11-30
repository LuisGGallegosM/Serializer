
#include"CsvParser.h"
#include<fstream>

namespace serializer
{
namespace csv
{
    Object parse(const char* filename)
    {
        std::ifstream file(filename);
        Object output;
        std::vector<std::string> columnHeaders;
        std::vector<std::string> rowHeaders;

        std::string line;

        if (!file.is_open())
        {
            throw std::runtime_error("ERROR: cannot open file:"+std::string(filename) + ".\n");
        }

        std::getline(file,line);

        tokenize(line,',',columnHeaders);

        std::vector<std::string> tokens;
        int lineNum=0;
        while( std::getline(file,line) )
        {
            tokenize(line,',',tokens);
            if (tokens.size()!= columnHeaders.size()) 
                throw std::invalid_argument("Error: in line "+std::to_string(lineNum)+" , columns dont match.");

            Object obj;
            for(int i=0;i<tokens.size();i++)
            {
                obj[columnHeaders[i]]=tokens[i];
            }

            output[tokens[0]]=obj;
            lineNum++;
        }

        return output;
    }
    
}
}