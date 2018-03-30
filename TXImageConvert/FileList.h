/*******************************************************************************
 * 文件：    FileList.h
 * 说明：    FileList类
 *           递归遍历指定文件夹并枚举指定后缀名的文件
 * 作者：    icyuki
 * 修改：    
 * 创建日期：2018/03/30
 ******************************************************************************/
#ifndef __FILE_LIST_H__
#define __FILE_LIST_H__

#include <string>
#include <vector>

class FileList
{
public:
    FileList();
    ~FileList();

public:

    //************************************
    // 递归遍历指定文件夹 
    // Returns:   void
    // Qualifier:
    // Parameter: const std::string & strPath
    //************************************
    void SearchDir(const std::string& strPath);

    //************************************
    // 筛选出指定后缀名的文件 
    // Returns:   std::vector<std::string>
    // Qualifier:
    // Parameter: const std::string & strSuffix
    //************************************
    std::vector<std::string> FilterFile(const std::string& strSuffix);

private:
    void Search(const std::string& strPath);

private:
    std::vector<std::string> m_vecFile;
};

#endif