#ifndef __SOCKETAPI_H__
#define __SOCKETAPI_H__

#if defined(_WINDOWS)
#include <WinSock2.h>
#elif defined(_LINUX)
typedef		int		SOCKET;
#define     INVALID_SOCKET   -1
#define		SOCKET_ERROR	 -1
#endif

namespace SocketAPI 
{
	/** ����socke���� **/
	bool setSockOpt(SOCKET socket, int level, int optname, const void * optval, unsigned int optlen);

	/** �ر�socket **/
	bool closeSocket (SOCKET s);

	/** �Ƿ������ **/
	bool setNonblocking (SOCKET s, bool onff = true); 
	
	/** �˳���ʽ **/
	bool setLinger (SOCKET s, bool onff , unsigned int lingerTime = 0); 

	/** �رպ��Ƿ����� **/
	bool setReuseAddr (SOCKET s, bool onff);

	/** ����buff��С **/
	bool setSendBuffSize (SOCKET s, unsigned int size);

	/** ����buff��С **/
	bool setRecvBuffSize (SOCKET s, unsigned int size);
}






#endif