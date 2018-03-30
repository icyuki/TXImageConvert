/*******************************************************************************
* �ļ���    ImageConvert.cpp
* ˵����    ImageConvert��
*          �Ѳ��������򿪵�ͼƬת�������ͼƬ��
*          Ŀǰֻ֧��ת��png��ʽ��
*          pngת��ԭ��ÿ���ֽ���key�����Ȼ��ߵ�4λ������������ȷ���ֽ�ֵ��
*          keyֵ�ҵ�0x8���ֽڵ�ֵ�����λ����png�ļ�ͷ����ȷֵ��0x00
* ���ߣ�    icyuki
* �޸ģ�
* �������ڣ�2018/03/30
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
    // ԴͼƬ���� 
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

    // ���ļ� 
    std::ifstream fin(strInFile, std::ios::binary | std::ios::in | std::ios::_Nocreate);
    std::ofstream fout(strOutFile, std::ios::binary | std::ios::trunc);
    if (fin.fail() || fin.eof() || fout.fail())
    {
        return false;
    }

    // �Աȵ�һ���ֽڣ��������ȷ�ľͲ���ת�� 
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

    // ȡxor��key 
    fin.seekg(0x08);
    char k = fin.peek();

    // ���ļ�ͷ����ʼ�����ֽ���򡢸ߵ�4λ���� 
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

    // ��ȡ��׺����תСд 
    std::string strSuffix = strFile.substr(iOffset, strFile.length()-iOffset);
    std::transform(strSuffix.begin(), strSuffix.end(), strSuffix.begin(), tolower);

    if (strSuffix == ".png")
    {
        return IMAGE_TYPE_PNG;
    }

    return IMAGE_TYPE_NONE;
}
