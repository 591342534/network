/************************************************************************/
/*                           �ض������                                 */
/************************************************************************/

#ifndef _POOL_OBJ_H_
#define _POOL_OBJ_H_

class PoolObj
{
public:
	PoolObj() : _poolId(-1){};
	virtual ~PoolObj(){};

public:
	/**
	 *	�˷���Ϊ�ڲ�������pooId�ᾭ���ı�
	 */
	inline int getPoolId() const {return _poolId;}
	inline void setPoolId( const int poolId) {_poolId = poolId;}

	/**
	 *	����ӳ��д�����ɾ��ʱ�򴥷�
	 */
	virtual void initByPool() = 0;
	virtual void releaseByPool() = 0;

private:
	int _poolId;
};


#endif