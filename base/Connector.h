/************************************************************************/
/*								����������								*/
/************************************************************************/
#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_
#include "CommonDefine.h"
#include "NetDefine.h"


class Log;
class Connector
{
public:
	Connector();
	virtual ~Connector();

public:
	/**
	 *	��ʼ��
	 */
	virtual bool init() = 0;

	/**
	 *	������������
	 */
	virtual bool connect() = 0;

	/**
	 *	��������
	 */
	virtual bool reconnect() = 0;

	/**
	 *	�Ͽ�����
	 */
	virtual void disconnect() = 0;

	/**
	 *	��������IP��ַ
	 */
	void setIP( const String &strIP ) { strncpy(_ip, strIP.c_str(), strIP.length()); }
	void setIP( const char * strIP ) { strncpy(_ip, strIP, strlen(strIP)); }
	const char * getIP() { return _ip; }

	/**
	 *	���ü����˿�
	 */
	void setPort( const int &port ) { _port = port; };

	/**
	 *	���ý���ģ��
	 */
	void setReceiveModel( ReceiveModel val ) { _rModel = val; };
	ReceiveModel getReceiveModel() { return _rModel; };

	/**
	 *	�Ƿ�������
	 */
	bool isConnecting() { return _isConncet; };

	/**
	 *	ж��
	 */
	virtual void dispose() = 0;

public:
	/**
	 *	�������ȡ���ݣ� �������ݷ���true����false
	 */
	virtual bool getNetData(NetData & netData) = 0;

	/**
	 *	��������
	 */
	virtual void sendData(char * data, int len) = 0;
protected:
	Log * _log;
	bool _isInit;
	bool _isConncet;
	bool _reconnect;
	char _ip[32];
	UInt _port;
	ReceiveModel _rModel;

};


#endif