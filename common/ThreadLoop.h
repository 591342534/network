/************************************************************************/
/*                           ѭ�������߳���				                */
/************************************************************************/

#ifndef _DB_THREADLOOP_H_
#define _DB_THREADLOOP_H_

#include "Thread.h"
#include "CommonDefine.h"

class ThreadLoop : public Thread
{
public:
	ThreadLoop();
	virtual ~ThreadLoop();

protected:
	virtual void run() final;

	/** ��һ�ο�ʼ���� **/
	virtual bool onStartRunning(){ return true; };

	/** 
	 * �߳�������ѭ�����ú���
	 * t : ����ʱ��
	 * ����ֵΪfalse���˳��߳�
	 */
	virtual bool onTick(unsigned int t) = 0;

	/**
	 * ÿ�ε���tick���
	 */
	virtual unsigned int getTickTime() { return FRAME_RATE;};

private:
	unsigned int _lastTime;
};
#endif