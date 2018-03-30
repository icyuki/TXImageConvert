/*******************************************************************************
 * 文件：    FileList.cpp
 * 说明：    FileList类
 *           递归遍历指定文件夹并枚举指定后缀名的文件
 * 作者：    icyuki
 * 修改：    
 * 创建日期：2018/03/30
 ******************************************************************************/
#include "FileList.h"

#include <io.h>

FileList::FileList()
{
}

FileList::~FileList()
{
}

void FileList::SearchDir(const std::string& strPath)
{
    m_vecFile.clear();
    Search(strPath);
}

std::vector<std::string> FileList::FilterFile(const std::string& strSuffix)
{
    std::vector<std::string> vecFile;
    if (strSuffix.length() <= 0)
    {
        return vecFile;
    }

    size_t iLength = strSuffix.length();

    for (auto& strFile : m_vecFile)
    {
        if (strFile.substr(strFile.length() - iLength, iLength) == strSuffix)
        {
            vecFile.push_back(strFile);
        }
    }
    return vecFile;
}

void FileList::Search(const std::string& strPath)
{
    std::string strFind = strPath + "\\*";
    _finddata_t stFileData;

    intptr_t iFindHandle = _findfirst(strFind.c_str(), &stFileData);
    do
    {
        std::string strNewPath = strPath + "\\" + stFileData.name;
        if (stFileData.attrib & _A_SUBDIR)
        {
            if (strcmp(stFileData.name, ".") != 0 &&
                strcmp(stFileData.name, "..") != 0)
            {
                Search(strNewPath);
            }
        }
        else
        {
            m_vecFile.push_back(strNewPath);
        }
    } while (_findnext(iFindHandle, &stFileData) == 0);
    _findclose(iFindHandle);
}

