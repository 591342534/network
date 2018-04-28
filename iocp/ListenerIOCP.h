/************************************************************************/
/*                     WinSock������ ����IOCP����ģ��					*/
/************************************************************************/

#ifndef _LISTENERIOCP_H_
#define _LISTENERIOCP_H_

#if defined(_WINDOWS)

#include <winsock2.h>
#include <MSWSock.h>
#include <list>
#include "Pool.h"
#include "PoolObj.h"
#include "Mutex.h"
#include "Listener.h"
#include "NetDefine.h"
#include "RingQueue.h"
#include "BuffParserUtil.h"
#include "RingBuffer.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

/** ͬʱͶ�ݵ�AcceptEx��������� */
#define MAX_POST_ACCEPT		3

enum IOType
{
	IOInvalid,		 //��Ч����
	IOAccept,		 //Ͷ�� AccepteEx �������
	IORead,			 //Ͷ�� WSARecv �������
	IOWrite,		 //Ͷ�� �������� �������
	IOWriteCompleted //Ͷ�� WSASend �������
};

//=======================
//		io�ص�����
//=======================
struct IOContext
{
	OVERLAPPED overLapped;
	SOCKET socket;
	WSABUF wsabuf;
	char buff[MAX_BUFFER_LEN];
	int len;
	IOType type;
	RingBuffer ringBuff;
	DWORD dwFlags;
	DWORD dwBytes;


	IOContext()
	{
		wsabuf.buf = buff;
		ringBuff.initSize(MAX_BUFFER_LEN);
		clear();
	};

	~IOContext(){clear();};

	void resetBuff()
	{
		ZeroMemory(&buff, MAX_BUFFER_LEN);
		ZeroMemory(&overLapped, sizeof(overLapped));
		wsabuf.len = MAX_BUFFER_LEN;
	}

	void clear()
	{
		ZeroMemory(&buff, MAX_BUFFER_LEN);
		ZeroMemory(&overLapped, sizeof(overLapped));
		wsabuf.len = MAX_BUFFER_LEN;
		type = IOInvalid;
		socket = INVALID_SOCKET;
		len = 0;
		ringBuff.clear();
		dwFlags = 0;
		dwBytes = 0;
	}
};

//=====================================
//		ÿ����ɶ˿ڶ�Ӧ��socket
//=====================================
struct SocketContext : public PoolObj
{
	SOCKET socket;
	SOCKADDR_IN clientAddr;
	int netId;
	char ip[20];
	int port;
	bool isNetmessage;
	IOContext readIO;
	IOContext writeIO;
	bool isClosed;
	bool isSend;

	SocketContext()
	{
		socket = INVALID_SOCKET;
		clear();
	};
	~SocketContext(){clear();};

	void initByPool(){clear();};
	void releaseByPool(){clear();};

	void setSocket(SOCKET val)
	{
		socket = val;
		readIO.socket = val;
		writeIO.socket = val;
	}
	void clear()
	{
		if (socket != INVALID_SOCKET )
		{
			CancelIo((HANDLE)socket);
			closesocket(socket);
			socket = INVALID_SOCKET;
		}
		memset(ip, 0 , 20);
		port = 0;
		netId = -1;
		isNetmessage = true;
		ZeroMemory(&clientAddr, sizeof(clientAddr));
		readIO.clear();
		writeIO.clear();
		readIO.type = IORead;
		writeIO.type = IOWrite;
		isClosed = false;
		isSend = false;
	}
};

class ListenerIOCP;
class NetMessage;
struct ThreadParam
{
	ListenerIOCP * pNetServer;
	int threadId;
};

class ListenerIOCP: public Listener
{
public:
	ListenerIOCP();
	~ListenerIOCP();

public:
	virtual bool init();

	virtual void listen();

	virtual bool shutDown();

	virtual bool disconnectByNetId(int netId);

	virtual void disconnectAll();

	virtual char * getLocalIp();

	void dispose();

public:
	bool getNetData(NetData & netData);

	void sendData(int netId, char * data, int len);

protected:
	/** �Ͽ�socket���� **/
	bool disconnectSocket(SocketContext * pSocketContext);

private:
	/**
	 *	�������������Ϣ
	 */
	bool startup();
	bool LoadSocketLib();
	void unLoadSocketLib(){WSACleanup();};
	bool createCompletionPort();
	bool setupListenSocket();
	bool setupFunctionPtr();
	bool initBaseData();
	bool setupIOWorkers();

	/**
	 *	����IO�����߳�
	 */
	static DWORD WINAPI workerThread(LPVOID lpParam);

	/**
	 *	����io��Ϣ
	 */
	bool processIOMessage(SocketContext * pSocketContext, IOContext * pIOContext);
	bool onAccept( SocketContext * pSocketContext, IOContext * pIOContext);
	bool onRead( SocketContext * pSocketContext);
	bool onWrite( SocketContext * pSocketContext);
	bool onWriteCompleted( SocketContext * pSocketContext);

	/**
	 *	Ͷ��io��Ϣ
	 */
	bool postAccept(IOContext * pIOContext);
	bool postRead(SocketContext * pSocketContext);
	bool postWrite(SocketContext * pSocketContext);
	bool postWriteCompleted(SocketContext * pSocketContext);

	/**
	 *	SocketContext���ɾ��
	 */
	SocketContext* newSocketContext();
	void freeSockeContext(SocketContext * pSocketContext);

	/**
	 *	IOContext���ɾ��
	 */
	IOContext* newIOContext(SocketContext * pSocketContext);
	void freeIOContext(SocketContext * pSocketContext, IOContext * pIOSocket);

	/**
	 * ���socket��io����
	 */
	SocketContext * getSocketContext(int netId);
	IOContext * getIOContext();

	/**
	 *	��ô���������
	 */
	int getProcessorsNum();

	/**
	 *	���ش�����Ϣ
	 */
	char * getErrorInfo();

private:
	HANDLE _shutDownEvent;			//�ر��¼����
	HANDLE _ioCompletionPort;		//��ɶ˿ھ��
	HANDLE* _pWorkThread;			//�����߳̾��ָ��
	int _threadNum;
	SocketContext * _pListenSocket;	//����socket
	list<IOContext *> _pIOList;       //����io

	MyLock _socketContextLock;
	MyLock _ioContextLock;
	
	list<SocketContext *> _listSocketContext;
	SocketContext * _arrSocketContext[MAX_CONNECT_NUM];
	int _currNetId;
	Pool<SocketContext> _socketContextPool;

	//������Ϣ����
	RingQueue<NetMessage> _netMessageQueue; 
	Pool<NetMessage> _netMessagePool;

	RingQueue<NetMessage> _opQueue;
	NetMessage * _netMsgCache;

	LPFN_ACCEPTEX _lpfnAcceptEx;
	LPFN_GETACCEPTEXSOCKADDRS _lpfnGetAcceptExSockAddrs;

	BuffParserUtil _buffIOCP;

	char * _errorStr;
};

#endif

#endif