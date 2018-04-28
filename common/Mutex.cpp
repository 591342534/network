#include "Mutex.h"

#if defined(_WINDOWS)
#include <windows.h>
MyLock::MyLock()
{
	m_Lock = new CRITICAL_SECTION();
	InitializeCriticalSection((CRITICAL_SECTION *)m_Lock);
}

MyLock::~MyLock()
{
	DeleteCriticalSection((CRITICAL_SECTION *)m_Lock);
	delete m_Lock;
}

void MyLock::Lock()
{
	EnterCriticalSection((CRITICAL_SECTION*)m_Lock);
}
void MyLock::Unlock()
{
	LeaveCriticalSection((CRITICAL_SECTION*)m_Lock);
}


#elif defined(_LINUX)
#include <pthread.h>

MyLock::MyLock()
{
	m_Lock = new pthread_mutex_t();
	//pthread_mutexattr_t attr;
	//pthread_mutexattr_init(&attr);
	//Ĭ�� ͬһ�߳̿��ظ�����������һ���ͷ���
	//pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);// Ƕ���� ͬһ�߳̿��ظ�����������ͬ�������ſ��ͷ���
	//pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK_NP);// ������ ͬһ�̲߳����ظ����������ϵ���ֻ���ɱ��߳̽���
	//pthread_mutex_init( (pthread_mutex_t*)m_Lock, &attr );
	pthread_mutex_init((pthread_mutex_t*)m_Lock, NULL);
	pthread_mutexattr_destroy( &attr );
}

MyLock::~MyLock()
{
	pthread_mutex_destroy( (pthread_mutex_t*)m_Lock );
	delete (pthread_mutex_t*)m_Lock;
}
void MyLock::Lock()
{
	pthread_mutex_lock((pthread_mutex_t*)m_Lock);
};
void MyLock::Unlock()
{
	pthread_mutex_unlock((pthread_mutex_t*)m_Lock);
}
#endif