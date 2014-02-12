/*  
 * File:  Thread.h 
 * Author: Null 
 * 
 * 
 * �ڱ����ʱ��ǵü��ϲ�����-lpthread 
 *  
 */
#ifndef _THREAD_H
#define _THREAD_H

#ifndef WIN32
#include <pthread.h>
#include <unistd.h>
#else
#include "Win32Platform/thread_win32.h"
#endif
/* 
 * �߳�����ʵ���� 
 */
class Runnable
{
public:    
    //����ʵ��    
    virtual void run() = 0;
};
/* 
 * �߳��� 
 * 
 */
class Thread : public Runnable
{
private:      
    static int threadInitNumber; //�̳߳�ʼ�����    
    
    int curThreadInitNumber;//��ǰ�̳߳�ʼ�����  
    
    Runnable *target;//�߳���    
    
    pthread_t tid;//��ǰ�̵߳��߳�ID     
    
    int threadStatus;//�̵߳�״̬    
    
    pthread_attr_t attr;//�߳�����    
#ifndef WIN32  
    sched_param param; //�߳����ȼ�   
#endif
  
#ifndef WIN32
    static void* run0(void* pVoid); //��ȡִ�з�����ָ��   
#else
	static DWORD WINAPI run0(LPVOID lpParameter);
#endif
    
    void run1(); //�ڲ�ִ�з���    
    
    static int getNextThreadNum();//��ȡһ���߳����
    
public:    
    
    static const int THREAD_STATUS_NEW = 0;  //�̵߳�״̬���½�  
    
    static const int THREAD_STATUS_RUNNING = 1; //�̵߳�״̬����������   
    
    static const int THREAD_STATUS_EXIT = -1; //�̵߳�״̬�����н���   
    
    Thread();   //���캯�� 
    
    Thread(Runnable *iTarget); //���캯��    
    
    ~Thread(); //����    
    
    void run(); //�̵߳�����ʵ��   
    
    bool start();  //��ʼִ���߳�  
    
    int getState(); //��ȡ�߳�״̬   
    
    void join(); //�ȴ��߳�ֱ���˳�   
    
    void join(unsigned long millisTime);//�ȴ��߳��˳����߳�ʱ    
    
    bool operator ==(const Thread *otherThread); //�Ƚ������߳�ʱ����ͬ,ͨ�� curThreadInitNumber �ж�   
    
    pthread_t getThreadID(); //��ȡThis�߳�ID    
    
    static pthread_t getCurrentThreadID(); //��ȡ��ǰ�߳�ID   
    
    static bool isEquals(Thread *iTarget); //��ǰ�߳��Ƿ��ĳ���߳����,ͨ�� tid �ж�   
    
    void setThreadScope(bool isSystem);//�����̵߳�����:��/�ǰ�    
    
    bool getThreadScope();  //��ȡ�̵߳�����:��/�ǰ�  
    
    void setThreadPriority(int priority); //�����̵߳����ȼ�,1-99,����99Ϊʵʱ;�����Ϊ��ͨ   
    
    int getThreadPriority();//��ȡ�̵߳����ȼ� 
    
    void cancelThread();
};

#endif /* _THREAD_H */