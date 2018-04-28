#ifndef __NETDEFINE_H__
#define __NETDEFINE_H__

//�ֽ���
#define NET_BYTE_INT( i ) ((i&0xFF000000)>>24 | (i&0x00FF0000)>>8 | (i&0x0000FF00)<<8 | (i&0x000000FF)<<24)
#define NET_BYTE_SHORT( i ) ((i&0xFF00)>>8 | (i&0x00FF)<<8)

/** ����ģ�� **/
enum ReceiveModel
{
	ReceiveModel_Push, //ֱ������
	ReceiveModel_Pull, //�ֶ���ȡ
	ReceiveModel_Pack, //����
};

/** ����ģ�� **/
enum NetState
{
	NetState_Null,		//δ��ʼ��
	NetState_Connect,   //�µ�����
	NetState_Close,		//�ر�����
	NetState_Receive,   //��������
	NetState_Send,		//��������
	NetState_ReConnect, //��������
};

struct NetData
{
	int netId;
	NetState state;
	char * data;
	int len;

	NetData():netId(0), state(NetState_Null), data(0),len(0){};
};


/** Ĭ�϶˿� */
#define DEFAULT_PORT					12345    
/** Ĭ��IP��ַ */
#define DEFAULT_IP						"127.0.0.1"
//#define DEFAULT_IP					"192.168.229.200"
/** ���socket������ */
#define MAX_CONNECT_NUM					2000
/** ���listen��ɶ���(accept ֮ǰ�� */
#define MAX_LISTEN_NUM					2000
/** ���������� (1024*8) */
#define MAX_BUFFER_LEN					8192
/** �������ݰ����ֵ (1024) */
#define MAX_PACKET_SIZE					1024  
/** ����buff char������Сֵ */
#define BUFFER_ARR_SIZE_MIN				8
/** buffͷ���ⳤ�� */
#define BUFFER_HEAD_LEN					4  
/** Ĭ�Ͻ���ģ�ͷ�ʽ */
#define DEFAULT_REVEIVEMODEL			ReceiveModel_Pack    
/** netmessage�������ֵ���������� */
#define DEFAULT_NETMESSAGE_MAX_SERVER	10000
/** netmessage�������ֵ���������� */
#define DEFAULT_NETMESSAGE_MAX_CLIENT	1000


#endif