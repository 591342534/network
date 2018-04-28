/****************************************************************************/
/*								�߳���										*/
/****************************************************************************/

#ifndef __THREAD_H__
#define __THREAD_H__


#if defined(_WINDOWS)
typedef unsigned int TID;
typedef void * HANDLE;
#elif defined(_LINUX)
typedef pthread_t TID;
#endif


class Thread
{
public:
	enum ThreadStatus
	{
		READY,
		STARTING,
		RUNNING,
		EXITING,
		EXIT
	};

public:
	Thread();
	virtual ~Thread();

public:
	/** �߳̿�ʼ **/
	void start();


protected:
	/** �߳��˳� **/
	void exit ( void * retval = 0);

	/** �߳̿�ʼ���� **/
	virtual void run() = 0;

	void waitForExit();

	/** �߳��˳�֮����� **/
	virtual void onExit(){};


public:
	inline TID getTID() { return m_TID; };

	inline ThreadStatus getStatus() { return m_Status;};

	inline void setStatus( ThreadStatus status ){ m_Status = status;};

#if defined(_WINDOWS)
	inline HANDLE getHandle(){return m_hThread;};
#endif


private:

	TID m_TID;

	ThreadStatus m_Status;

#if defined(_WINDOWS)
	HANDLE m_hThread;
#endif

private:
#if defined(_WINDOWS)
	friend unsigned int __stdcall MyThreadProcess ( void * d );
#elif defined(_LINUX)
	friend void * MyThreadProcess ( void * d );
#endif

};

extern unsigned int g_QuitThreadCount;

#if defined(_WINDOWS)
unsigned int __stdcall MyThreadProcess ( void * d );
#elif defined(_LINUX)
void * MyThreadProcess ( void * d );
#endif

#endif
