/*******************************************************************************
 * �ļ���    FileList.h
 * ˵����    FileList��
 *           �ݹ����ָ���ļ��в�ö��ָ����׺�����ļ�
 * ���ߣ�    icyuki
 * �޸ģ�    
 * �������ڣ�2018/03/30
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
    // �ݹ����ָ���ļ��� 
    // Returns:   void
    // Qualifier:
    // Parameter: const std::string & strPath
    //************************************
    void SearchDir(const std::string& strPath);

    //************************************
    // ɸѡ��ָ����׺�����ļ� 
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