/************************************************************************/
/*						����ģʽ��ֱ��ת��bufferevent�е�����	��			*/
/************************************************************************/
#ifndef _BUFFPARSER_H_
#define _BUFFPARSER_H_
#include "CommonDefine.h"
class bufferevent;
class BuffParserPush
{
public:
	BuffParserPush(bufferevent *pBev, Int netId);
	virtual ~BuffParserPush();

public:
	virtual bool onRead();

	virtual bool sendData(char * data, int len);

private:
};

#endif