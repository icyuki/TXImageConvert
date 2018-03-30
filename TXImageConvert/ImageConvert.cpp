/*******************************************************************************
* 文件：    ImageConvert.cpp
* 说明：    ImageConvert类
*          把不能正常打开的图片转码成正常图片。
*          目前只支持转码png格式。
*          png转码原理：每个字节与key做异或，然后高低4位互换，就是正确的字节值。
*          key值找第0x8个字节的值，这个位置在png文件头中正确值是0x00
* 作者：    icyuki
* 修改：
* 创建日期：2018/03/30
******************************************************************************/

#include "ImageConvert.h"

#include <algorithm>
#include <fstream>

ImageConvert::ImageConvert()
{
    m_mapFileHead[IMAGE_TYPE_PNG] = (char)0x89;
}


ImageConvert::~ImageConvert()
{
}

bool ImageConvert::Convert(const std::string& strInFile,
                           const std::string& strOutFile,
                           bool bSkipNormal)
{
    // 源图片类型 
    ImageType eType = GetImageType(strInFile);
    if (eType == IMAGE_TYPE_NONE)
    {
        return false;
    }

    MapFileHead::iterator it = m_mapFileHead.find(eType);
    if (it == m_mapFileHead.end())
    {
        return false;
    }

    // 打开文件 
    std::ifstream fin(strInFile, std::ios::binary | std::ios::in | std::ios::_Nocreate);
    std::ofstream fout(strOutFile, std::ios::binary | std::ios::trunc);
    if (fin.fail() || fin.eof() || fout.fail())
    {
        return false;
    }

    // 对比第一个字节，如果是正确的就不用转码 
    if (static_cast<char>(fin.peek()) == it->second)
    {
        if (bSkipNormal)
        {
            return false;
        }
        else
        {
            fout << fin.rdbuf();
            fin.close();
            fout.close();
            return true;
        }
    }

    // 取xor的key 
    fin.seekg(0x08);
    char k = fin.peek();

    // 从文件头部开始，逐字节异或、高低4位互换 
    fin.seekg(std::ios::beg);
    while (!fin.eof())
    {
        char c[1] = { 0 };
        fin.read(c, sizeof(char));
        c[0] ^= k;
        char h = (c[0] & 0xf0) >> 4;
        c[0] = (c[0] << 4) + h;
        fout.write(c, sizeof(char));
    }

    fin.close();
    fout.close();

    return true;
}

ImageConvert::ImageType ImageConvert::GetImageType(const std::string& strFile)
{
    if (strFile.empty())
    {
        return IMAGE_TYPE_NONE;
    }
 
    size_t iOffset = strFile.find_last_of(".");
    if (iOffset == std::string::npos || iOffset == strFile.length())
    {
        return IMAGE_TYPE_NONE;
    }

    // 读取后缀名并转小写 
    std::string strSuffix = strFile.substr(iOffset, strFile.length()-iOffset);
    std::transform(strSuffix.begin(), strSuffix.end(), strSuffix.begin(), tolower);

    if (strSuffix == ".png")
    {
        return IMAGE_TYPE_PNG;
    }

    return IMAGE_TYPE_NONE;
}
