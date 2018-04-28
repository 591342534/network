/************************************************************************/
/*								  �ͻ���������							*/
/************************************************************************/
#ifndef _NETSERVER_H_
#define _NETSERVER_H_

#include "CommonDefine.h"
#include "NetDefine.h"
#include "log.h"
#include "Thread.h"

class Connector;
class NetClient : public Thread
{
public:
	NetClient();
	virtual ~NetClient();

public:
	/**
	 *	��ʼ��������
	 */
	bool init();

	/**
	 *	�Ͽ�����
	 */
	bool disconnect();

	/**
	 *	�Ƿ�������
	 */
	bool isConnecting();

	/**
	 *	��������
	 */
	bool reconnect();

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

public:
	/**
	 *	�������ȡ���ݣ� �������ݷ���true����false
	 */
	bool getNetData(NetData & netData);

	/** �������� **/
	void sendData(char * data, int len);

protected:
	void onExit();
	void run();

private:
	Connector * _connector;
	Log * _log;
	bool _isInit;
	char _ip[32];
	UInt _port;
	ReceiveModel _rModel;

private:


};

#endif