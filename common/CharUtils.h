/****************************************************************************/
/*		    �ַ�������ת��,��ʽ���ַ��������뼯ת��������                     */
/****************************************************************************/

#ifndef __CHAR_UTILS_H__
#define __CHAR_UTILS_H__
#include <string>
#include "CommonDefine.h"
using namespace std;

namespace CharUtils
{
	/** �ַ���ת��Ϊ���� **/
	int strToInt(const char * value);
	int strToInt(const string & value);
	unsigned int strToUInt(const char * value, int radix = 10);
	unsigned int strToUInt(const string & value, int radix = 10);
	long long strToLLong(const char * value);
	long long strToLLong(const string & value);
	unsigned long long strToULLong(const char * value, int radix = 10);
	unsigned long long strToULLong(const string & value, int radix = 10);
	float strToFloat(const char * value);
	float strToFloat(const string & value);
	double strToDouble(const char * value);
	double strToDouble(const string & value);

	/** ����ת��Ϊ�ַ��� **/
	string intToStr(int val);
	string uintToStr(unsigned int val);
	string floatToStr(float val);
	string uLLongToStr(unsigned long long val);

	/** �ַ�����ʽ�� **/
	void sprintfA(char *buffer, int size, const char *format, ...);
	void sprintfAW( wchar_t *buffer , int size , const wchar_t *format , ... );
	string format(const char* format, ...);

	/** �ַ����Ƚ� **/
	//���ִ�Сд
	int strcmpA(const char * p1, const char * p2);
	//�����ִ�Сд
	int strcmpnA(const char * p1, const char * p2);
}

#endif