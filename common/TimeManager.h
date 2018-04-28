#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__

#include "CommonDefine.h"
#include "Singleton.h"
#ifdef __LINUX__
#include <sys/utsname.h>
#include <sys/time.h>
#endif

struct TimeStruct
{
	UInt year;
	UInt month;
	UInt day;
	UInt hour;
	UInt minute;
	UInt second;
	UInt week;

	TimeStruct()
	{
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		minute = 0;
		second = 0;
		week = 0;
	};
};

class TimeManager : EXTEND_SINGLETON(TimeManager)
{
public:
	TimeManager();
	~TimeManager();

public:
	Bool init();

	/** ����һ�ε�ǰ����ʱ�䣬�����أ����룩 **/
	UInt currentTime();

	/** ֱ�ӷ����ϴμ���ĵ�ǰʱ�� **/
	UInt currentSavedTime() { return _currTime; };

	/** ����������ʱ�� (����1970.1.1 ������ **/
	UInt serverStartTime(){ return _serverStartTime; };

	/** ����ǰ��ϵͳʱ���ʽ����ʱ��������� **/
	void setTime();

	/** �õ���׼ʱ�� (����1970.1.1 ������ **/
	Time_t getANSITime( );

	/** �õ���׼ʱ��TimeStruct **/
	TimeStruct getANSITimeStruct();

public:
	/** ȡ������ʱ��ʱ��ġ��ꡢ�¡��ա�ʱ���֡��롢���ڵ�ֵ�� **/
	UInt getYear() { return _tm.tm_year + 1900; }	//[1900, ~]
	UInt getMonth() { return _tm.tm_mon + 1; }		//[1, 12]
	UInt getDay() { return _tm.tm_mday; }			//[1, 31]
	UInt getHour() { return _tm.tm_hour; }			//[0, 23]
	UInt getMinute() { return _tm.tm_min; }			//[0, 59]
	UInt getSecond() { return _tm.tm_sec; }			//[0, 59]
	UInt getWeek() { return _tm.tm_wday ? _tm.tm_wday : 7; }	//[1, 7]

public:
	/** �Ƿ����� **/
	static Bool isLeapYear( UInt year ) { return (year % 400 == 0) ?  true : ((year % 4 == 0) && (year % 100 != 0)); }
	/** ĳ��ʱ�䵱������ **/
	static UInt secToMonthDay(Time_t t);

	/** ʱ���ת���� **/
	static TimeStruct sec2ts(Time_t t);
	/** ʱ���ת���ڼ� **/
	static UInt sec2week(Time_t t);
	/** ������ת���ڼ� **/
	static UInt ymd2week(UInt y, UInt m, UInt d);
	/** ����תʱ��� **/
	static Time_t ts2sec(TimeStruct &ts);
	
	/** ��ý��쿪ʼ���� **/
	static Time_t getTodayTime();
	/** ���������ڿ�ʼ���� **/
	static Time_t getWeekTime();
	/** �������¿�ʼ���� **/
	static Time_t getMonthTime();

	/** ʱ����Ƿ����ڽ��� **/
	static Bool isSecInToday(Time_t t);
	/** ʱ����Ƿ����ڱ��� **/
	static Bool isSecInWeek(Time_t t);
	/** ʱ����Ƿ����ڱ��� **/
	static Bool isSecInMonth(Time_t t);

	/** ��ʱ�䣨�ꡢ�¡��ա�Сʱ���֣�ת����һ��UINT����ʾ,Ĭ�ϲ���Ϊ��ǰʱ��
		���磺0,507,211,233 ��ʾ "2005.07.21 12:33" **/
	static UInt time2uint(Time_t t = 0);
	static Time_t uint2time(UInt t);
	static TimeStruct uint2timestruct(UInt t);

private:
	static void setTMByANSITime(Time_t &t, tm &tm);
	static Time_t getANSITimeByTM(tm &tm);
	static tm ts2tm(TimeStruct &t);
	static TimeStruct tm2ts(tm &tm);
	
private:
	UInt	_startTime ;
	UInt	_serverStartTime;//���ʱ�� ����1970.1.1
	UInt	_currTime ;
	Time_t	_setTime ;
	tm		_tm ;
#ifdef __LINUX__
	struct timeval _tvStart, _tvEnd;
	struct timezone _tz;
#endif
};









#endif