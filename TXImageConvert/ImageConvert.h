/*******************************************************************************
 * 文件：    ImageConvert.h
 * 说明：    ImageConvert类
 *          把不能正常打开的图片转码成正常图片。
 *          目前只支持转码png格式。
 *          png转码原理：每个字节与key做异或，然后高低4位互换，就是正确的字节值。
 *          key值找第0x8个字节的值，这个位置在png文件头中正确值是0x00
 * 作者：    icyuki
 * 修改：    
 * 创建日期：2018/03/28
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
    // 转码图片文件
    // Returns:   bool 转码成功返回true
    // Qualifier:
    // Parameter: const std::string & strInFile
    // Parameter: const std::string & strOutFile
    // Parameter: bool bSkipNormal 填true则遇到正常图片不转码，返回false
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
