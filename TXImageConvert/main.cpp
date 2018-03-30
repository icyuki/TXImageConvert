#include "FileList.h"
#include "ImageConvert.h"

#include <direct.h>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    char* szPath = _getcwd(NULL, 0);
    std::string strPath(szPath);
    free(szPath);

    ImageConvert imageConvert;
    FileList fileList;
    std::fstream f;
    fileList.SearchDir(strPath);
    std::vector<std::string> vecFile = fileList.FilterFile(".png");
    
    for (auto& strFile : vecFile)
    {
        std::cout << strFile << "......";
        if (imageConvert.Convert(strFile, "tempfile", true))
        {
            remove(strFile.c_str());
            rename("tempfile", strFile.c_str());
            std::cout << "ok" << std::endl;
        }
        else
        {
            std::cout << "skip" << std::endl;
        }
    }
    remove("tempfile");

    return 0;
}