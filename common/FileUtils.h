#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

#include <vector>
#include "CommonDefine.h"

/************************************************************************
 �ļ�������ʽΪc��File*                          
 �ļ�ʹ�÷�ʽ: 
				r(��), w(д), a(׷��), t(�ı���Ĭ��), b(������), +(����д)
				 r��a��ͷ�ļ�������ڣ�w�������򴴽�                                                                      
 ��д������                                                                      
          �ַ���д��fgetc��fputc	�ַ�����д��fgets��fputs 
			 ���ݿ��д��fread��fwrite ��ʽ����д��fscanf��fprinf(���̣�
 �ƶ��ļ�ָ����            
          rewind���ļ��ף�
			 fseek(file*, offset, startPos) startPos: SEEK_SET(��) SEEKCUR(��ǰ) SEEK_END(β)
************************************************************************/
namespace FileUtils
{
	std::string getCurrPath();

	void writeFile(const char * path, const char *info, bool isAppend = true, bool isEnter = true);
	void readFile(const char * path, char *info, int size);

	void getFiles(std::string path, std::vector<std::string>& files, const char * existStr = NULL);
}



#endif