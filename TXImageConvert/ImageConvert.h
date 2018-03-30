/*******************************************************************************
 * �ļ���    ImageConvert.h
 * ˵����    ImageConvert��
 *          �Ѳ��������򿪵�ͼƬת�������ͼƬ��
 *          Ŀǰֻ֧��ת��png��ʽ��
 *          pngת��ԭ��ÿ���ֽ���key�����Ȼ��ߵ�4λ������������ȷ���ֽ�ֵ��
 *          keyֵ�ҵ�0x8���ֽڵ�ֵ�����λ����png�ļ�ͷ����ȷֵ��0x00
 * ���ߣ�    icyuki
 * �޸ģ�    
 * �������ڣ�2018/03/28
 ******************************************************************************/

#ifndef __IMAGE_CONVERT_H__
#define __IMAGE_CONVERT_H__

#include <map>
#include <string>
#include <vector>

class ImageConvert
{
public:
    ImageConvert();
    ~ImageConvert();

public:
    //************************************
    // ת��ͼƬ�ļ�
    // Returns:   bool ת��ɹ�����true
    // Qualifier:
    // Parameter: const std::string & strInFile
    // Parameter: const std::string & strOutFile
    // Parameter: bool bSkipNormal ��true����������ͼƬ��ת�룬����false
    //************************************
    bool Convert(const std::string& strInFile,
                 const std::string& strOutFile,
                 bool bSkipNormal);

private:
    enum ImageType
    {
        IMAGE_TYPE_NONE,
        IMAGE_TYPE_PNG,
    };

    typedef std::map<ImageType, char> MapFileHead;

private:
    ImageType GetImageType(const std::string& strFile);

private:
    MapFileHead m_mapFileHead;
};

#endif
