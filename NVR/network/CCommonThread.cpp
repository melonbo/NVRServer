/*
 * CCommonThread.cpp
 *
 *  Created on: 2010-9-29
 *      Author: hbs
 */
//http://hi.baidu.com/hetaoos/blog/item/de864d34f16b1a48241f1464.html
#include "CCommonThread.h"
#include <assert.h>
#include <stdio.h>
#include <limits.h>
/*!
 *
 * @param pVoid
 */
void* CCommonThread::run0(void* pVoid) {
	CCommonThread* p = (CCommonThread*) pVoid;
	p->run1();
	return p;
}
/*!
 *
 */
void* CCommonThread::run1() {
	threadStatus = THREAD_STATUS_RUNNING;
	tid = pthread_self();
	ThreadProc();
	threadStatus = THREAD_STATUS_EXIT;
	tid = 0;
	pthread_exit(NULL);

	return NULL;
}
/*!
 *
 */
void CCommonThread::ThreadProc() {
	if (target != NULL) {
		(*target).ThreadProc();
	}
}
/*!
 *
 */
CCommonThread::CCommonThread() {
	tid = 0;
	bRun = false;
	m_vTarget = NULL;
	target = 0;
	m_pParam = NULL;
	//设置线程栈
	threadStatus = THREAD_STATUS_NEW;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 1024 * 1024);//PTHREAD_STACK_MIN);
}
/*!
 *
 * @param iTarget
 */
CCommonThread::CCommonThread(ICommonThread *iTarget) {
	target = iTarget;
	tid = 0;
	bRun = false;
	m_vTarget = NULL;
	m_pParam = NULL;
	//设置线程栈
	threadStatus = THREAD_STATUS_NEW;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 1024 * 1024);//PTHREAD_STACK_MIN);
}
/*!
 *
 * @param vTarget
 * @param pParam
 */
CCommonThread::CCommonThread(ThreadBody vTarget,void *pParam) {
	target = 0;
	tid = 0;
	bRun = false;
	m_vTarget = vTarget;
	m_pParam = pParam;
	//设置线程栈
	threadStatus = THREAD_STATUS_NEW;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 1024 * 1024);//PTHREAD_STACK_MIN);
}
/*!
 *
 */
CCommonThread::~CCommonThread() {
	pthread_attr_destroy(&attr);
}
/*!
 *
 * @param iStackSize
 * @return
 */
bool CCommonThread::start(int iStackSize) {
	assert(bRun == false);
	bRun = true;
	if (iStackSize > 0) {
//                printf(" CCommonThread::start iStackSize:%d\n", iStackSize);
		assert(pthread_attr_setstacksize(&attr, iStackSize) == 0);//PTHREAD_STACK_MIN);
	}
	if (target != NULL) {
		return pthread_create(&tid, &attr, run0, this) == 0;
	}
        printf("ssssssssss\n");
	//创建线程
	if ( m_vTarget != NULL ){
		return pthread_create(&tid, &attr, m_vTarget, m_pParam) == 0;
	}
        printf("wwwwwwwwwwwwwww\n");
	assert(0);
	return false;
}
//等待线程直至退出
void CCommonThread::stop() {
	//停止线程
	assert(bRun == true);
	bRun = false;
	join();
}
/*!
 *
 */
void CCommonThread::asyncStop() {
	//异步停止
	assert(bRun == true);
	bRun = false;
}
/*!
 *
 */
void CCommonThread::waitAsyn() {
	//等待停止
	join();
}

//等待线程退出或者超时
void CCommonThread::stop(unsigned long millisTime) {
	//等待时间停止
	assert(bRun == true);
	bRun = false;
	join(millisTime);
}
/*!
 *
 * @return
 */
int CCommonThread::getState() {
	//获得线程状态
	return threadStatus;
}
/*!
 *
 */
void CCommonThread::join() {
	//等待停止
	if (tid > 0) {
		pthread_join(tid, NULL);
	}
}
/*!
 *
 * @param millisTime
 */
void CCommonThread::join(unsigned long millisTime) {
	//等待时长停止
	if (tid == 0) {
		return;
	}
	if (millisTime == 0) {
		join();
	} else {
		unsigned long k = 0;
		while (threadStatus != THREAD_STATUS_EXIT && k <= millisTime) {
			usleep(100);
			k++;
		}
	}
}



