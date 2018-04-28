/************************************************************************/
/*								  ������������							*/
/************************************************************************/
#ifndef _NETSERVER_H_
#define _NETSERVER_H_

#include "CommonDefine.h"
#include "NetDefine.h"
#include "log.h"
#include "Thread.h"

class Listener;
class NetServer : public Thread
{
public:
	NetServer();
	virtual ~NetServer();

public:
	/**
	 *	��ʼ��������
	 */
	bool init();

	/**
	 *	�ط�
	 */
	bool shutDown();

	/**
	 *	��������IP��ַ
	 */
	void setIP( const String &strIP );
	void setIP( const char * strIP );
	const char * getIP();

	/**
	 *	���ü����˿�
	 */
	void setPort( const UInt port ) { _port = port; }
	int getPort() { return _port; }

	/**
	 *	�Ͽ�ĳһ������id����
	 */
	virtual bool disconnectByNetId(int netId);

	/**
	 *	�Ͽ����пͻ�������
	 */
	virtual void disconnectAll();

	/**
	 *	��ñ���ip
	 */
	virtual char * getLocalIp();

public:
	/**
	 *	�������ȡ���ݣ� �������ݷ���true����false
	 */
	bool getNetData(NetData & netData);

	/** �������� **/
	void sendData(int netId, char * data, int len);

protected:
	void onExit();
	void run();
private:
	Listener * _listener;
	Log * _log;
	bool _isInit;
	char _ip[32];
	UInt _port;
	ReceiveModel _rModel;

private:


};

#endif