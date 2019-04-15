/*
 * CCommonThread.h
 *
 *  Created on: 2010-9-29
 *      Author: hbs
 */

#ifndef CCOMMONTHREAD_H_
#define CCOMMONTHREAD_H_

#include <pthread.h>
#include <unistd.h>
#include "ctypedef.h"

//!线程接口
struct ICommonThread
{
	//!线程接口体
	virtual void ThreadProc() = 0;
};
//!线程定义
typedef void* (*ThreadBody)(void *);

//!线程辅助类
class CCommonThread: public ICommonThread
{
private:
	//!线程体
        ICommonThread *target;
	ThreadBody m_vTarget;
	//!当前线程的线程ID
	pthread_t tid;

	//!线程的状态
	int threadStatus;
	//!线程属性
	pthread_attr_t attr;
	//!线程优先级
	sched_param param;
	void *m_pParam;
	//!获取执行方法的指针
	static void* run0(void* pVoid);
	//!内部执行方法
	void* run1();
	//!等待线程直至退出
	void join();
	//!等待线程退出或者超时
	void join(unsigned long millisTime);
protected:
	volatile bool  bRun;//!<运行标志
public:
	//!等待线程直至退出
	void stop();
	//!等待线程退出或者超时
	void stop(unsigned long millisTime);
    //!停止线程
	void asyncStop();
	//!等待线程停止
	void waitAsyn();

	//线程的状态－新建
#define  THREAD_STATUS_NEW  0
	//线程的状态－正在运行
#define  THREAD_STATUS_RUNNING  1
	//线程的状态－运行结束
#define  THREAD_STATUS_EXIT  -1
	//!构造函数
	CCommonThread();
	//!构造函数
	CCommonThread(ICommonThread *iTarget);
	//!构造函数
	CCommonThread(ThreadBody vTarget,void *pParam);
	//!析构
	~CCommonThread();
	//!判断运行状态
	bool isRun(){return bRun;}
	//!线程的运行实体
	void ThreadProc();
	//!开始执行线程
	bool start(int iStackSize = 0);
	//!获取线程状态
        int getState();

};

#endif /* CCOMMONTHREAD_H_ */
