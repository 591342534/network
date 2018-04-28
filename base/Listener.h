/************************************************************************/
/*								���������								*/
/************************************************************************/
#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "CommonDefine.h"
#include "log.h"
#include "NetDefine.h"
#if defined(_LINUX)
#include <string.h>
#endif

class Listener
{
public:
	Listener();
	virtual ~Listener();

public:
	/**
	 *	��ʼ��
	 */
	virtual bool init() = 0;

	/**
	 *	��ʼ����
	 */
	virtual void listen() = 0;

	/**
	 *	�ر�
	 */
	virtual bool shutDown() = 0;

	/**
	 *	��������IP��ַ
	 */
	void setIP( const String &strIP ) { strncpy(_ip, strIP.c_str(), strIP.length()); }
	void setIP( const char * strIP ) { strncpy(_ip, strIP, strlen(strIP)); }
	const char * getIP() { return _ip; }

	/**
	 *	���ü����˿�
	 */
	void setPort( const UInt port ) { _port = port; }
	int getPort() { return _port; }

	/**
	 *	���ý���ģ��
	 */
	void setReceiveModel( ReceiveModel val ) { _rModel = val; };
	ReceiveModel getReceiveModel() { return _rModel; };

	/**
	 *	�Ͽ�ĳһ������id����
	 */
	virtual bool disconnectByNetId(int netId) = 0;

	/**
	 *	�Ͽ����пͻ�������
	 */
	virtual void disconnectAll() = 0;

	/**
	 *	��ñ���ip
	 */
	virtual char * getLocalIp() = 0;

	/**
	 *	ж��
	 */
	virtual void dispose();

public:
	/**
	 *	�������ȡ���ݣ� �������ݷ���true����false
	 */
	virtual bool getNetData(NetData & netData) = 0;

	/**
	 *	��������
	 */
	virtual void sendData(int netId, char * data, int len) = 0;

protected:
	Log * _log;
	bool _isInit;
	bool _closed;
	char _ip[32];
	UInt _port;
	ReceiveModel _rModel;
};

#endif