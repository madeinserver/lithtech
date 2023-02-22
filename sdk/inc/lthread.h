
// This module defines the engine's threading classes.

#ifndef __LTHREAD_H__
#define __LTHREAD_H__

#ifndef __LTINTEGER_H__
#include "ltinteger.h"
#endif

#ifndef __ITHREAD_H__
#include "ithread.h"
#endif

#include "goodlinklist.h"

#ifdef _WIN32
#include <Windows.h>
#undef PostMessage
#else
#include <pthread.h>
#endif


// Thread priorities go from 0 to LTPRI_MAX.
#define LTPRI_LOWEST    ThreadLow
#define LTPRI_NORMAL    ThreadNormal
#define LTPRI_MAX       ThreadHigh


// How much data each LThreadMessage contains..
#define NUM_THREADMESSAGE_DATA  4

// Arbitrary.. hope we don't get a thread with this ID!
//#define LCS_INVALIDTHREADID	0xFECDAEDC


class LThread;

//
// CLASS: CSysSyncVar
//
class CSysSyncVar : public ISyncVar {
public:
    CSysSyncVar();
    ~CSysSyncVar();
    // implement this interface (see IThread.h)
    ESyncResult Begin();
    ESyncResult End();
    ESyncResult Wait();
protected:
#ifdef _WIN32
    HANDLE m_hMutex;
#else
    pthread_mutex_t	m_Mutex;
#endif
}; // CSysSyncVar

//
// CLASS: CSysSerialVar
//
class CSysSerialVar : public ISerialVar
{
public:
    CSysSerialVar();
    ~CSysSerialVar();
    // implement this interface (see IThread.h)
    ESyncResult Lock();
    ESyncResult Unlock();
protected:
    friend class CSysEventVar;

#ifdef _WIN32
    CRITICAL_SECTION m_CritSect;
#else
    pthread_mutex_t	m_Mutex;
    // attributes for mutex object
    pthread_mutexattr_t m_MutexAttr;
#endif
};

//
// CLASS: CSysThread
//
class CSysThread : public IThread
{
public:
    CSysThread();
    // implement the pure vitural interface defined in ithread.h
    virtual ESTDLTResults Run(EThreadPriority pri = ThreadNormal);
    virtual ESTDLTResults Wakeup();
    virtual ESTDLTResults Term(bool blocking = true); // avoid using this function if possible!
    virtual void          WaitForTerm();

protected:
    // these methods are not in IThread

#ifdef _WIN32
    bool    IsInThisThread() const;
#else
    pthread_t	m_ThreadID;
    pthread_cond_t	m_ThreadCond;
    pthread_mutex_t	m_ThreadMutex;
    pthread_mutex_t	m_WakeupMutex;
    uint32          m_WakeupCnt;

    bool	IsInThisThread() const { return pthread_self() == m_ThreadID; }
#endif

    bool    IsThreadActive() const;
    static  unsigned int __stdcall  ThreadLaunch(void* pWhichThread);
    virtual void                    ThreadRun() = 0;
    virtual ESTDLTResults           ThreadInit();
    virtual ESTDLTResults           ThreadTerm();
    virtual void                    Sleep();
protected:
    // not portable
    int     LTPriToWinPri(EThreadPriority pri);
    HANDLE  GetWinThreadHandle() { return m_hThread; }
    DWORD   GetWinThreadId() { return m_ThreadID; }
private:
    // data members
    CSysSerialVar m_Lock; // thread-safe access to m_LocalWakeup
    int m_LocalWakeup;
    HANDLE m_hThread;
    unsigned int m_ThreadID;
}; // CSysThread


// Used to synchronize access to things.
class LCriticalSection : public CSysSerialVar {
    typedef CSysSerialVar super;
public:

    LCriticalSection()
    {
    }

    // When you make a critical section, it might not be able to intialize.
    // You should check it with IsValid() before using it.
    bool        IsValid(); 

    // No two threads can enter a critical section at the same time so if two
    // call Enter at the same time, one will wait until the other one leaves.
    void        Enter();
    void        Leave();

#ifndef _WIN32
private:
    uint32      m_CS[6];    // CRITICAL_SECTION m_CS (CRITICAL_SECTIONs are 24 bytes)
#endif
};


// This class automatically enters and leaves the critical section in its constructor and destructor.
class CSAccess
{
public:
    CSAccess(LCriticalSection *pSection) {
        m_pSection = pSection;
        pSection->Enter();
    }

    ~CSAccess() {
        m_pSection->Leave();
    }

    LCriticalSection *m_pSection;
};



// This is what threads use to communicate between eachother.  They post
// messages into eachother's queues.
class LThreadMessage : public CGLLNode {
public:
    LThreadMessage();

    uint32      m_ID;
    LThread     *m_pSender; // Optional..
    
    union {
        void    *m_pData;
        uint32  m_dwData;
        uint16  m_wData[sizeof(uint32)/sizeof(uint16)];
        uint8   m_bData[sizeof(uint32)/sizeof(uint8)];
    } m_Data[NUM_THREADMESSAGE_DATA];
};



// A message queue.  Each thread has an incoming and outgoing list of messages.
class LThreadQueue {
public:
    
    LThreadQueue();
    ~LThreadQueue();

    LTRESULT    Init();
    void        Clear(); // Clear all the messages.
    
    // Post a message to the queue.
    LTRESULT    PostMessage(LThreadMessage &msg);

    // Tells how many messages we have.
    uint32      GetMessageCount();

    // PeekMessage gets the next message without removing it from the list.
    // GetMessage gets the next message and pops it off the list.
    // Both return LT_NOTFOUND if there are no messages.
    // If bWait is TRUE, it won't return until it gets a message.
    LTRESULT    GetMessage(LThreadMessage &msg, bool bWait=LTFALSE);
    LTRESULT    PeekMessage(LThreadMessage &msg);
    // Pops the top message off, and copies it into pMsg if it's non-NULL
    // Returns TRUE if a message was available
    bool        PopMessage(LThreadMessage *pMsg = NULL);

// If you access these messages, ALWAYS do it in a lock/unlock block.
public:
    LCriticalSection    m_MessageCS;

    // The message queue.. new messages are added at the end.
    CGLinkedList<LThreadMessage*>   m_Messages; 

    // Retrieve the msg wait handle (Should only be used by LThread)
    uint32 &GetMsgEvent() { return m_hMsgEvent; }
// Internal synching handles
private:
    uint32  m_hMsgEvent; // HANDLE - Message waiting
};


class LThread : public CSysThread {
    typedef CSysThread super;

// Functions for the caller or the thread to use.
public:

    LThread();
    virtual     ~LThread();

    LTRESULT    Start(const EThreadPriority& = ThreadNormal); // Start
    LTRESULT    Pause();                // Pause
    LTRESULT    Resume();               // Resume after pausing

    // This will terminate the thread.  bWait is currently ignored.
    // Note: this does NOT clear the incoming/outgoing queues, so it's a good idea
    // to read the contents of the outgoing queue after calling Terminate().
    LTRESULT    Terminate(bool bWait=TRUE);

    // Post a message to the thread.
    LTRESULT    PostMessage(LThreadMessage &msg) {return m_Incoming.PostMessage(msg);}


// Functions for the thread to use.
protected:

    virtual ESTDLTResults Term();  // Frees resources and stuff.

    // LThread calls this when its thread runs.  The default implementation
    // waits for a message to enter the incoming queue, calls ProcessMessage
    // and then pops the thread from the queue.
    // Note: this loop PEEKS at messages when calling ProcessMessage and actually
    virtual ESTDLTResults ThreadInit();
    virtual ESTDLTResults ThreadTerm();

    // removes the message from the queue AFTER ProcessMessage is called.
    virtual void    ThreadRun();

    // This is called by the default ThreadRun() when there's a new message.
    virtual void    ProcessMessage(LThreadMessage &msg);

    bool            ShouldTerminate();
    
public:
    
    // Message to the thread go in here.
    LThreadQueue    m_Incoming;

    // The thread posts status messages in here.
    LThreadQueue    m_Outgoing;


private:
    
#ifdef _WIN32
    // Internal Windows stuff.
    uint32          m_Handle;       // HANDLE m_Handle
    uint32          m_ThreadID;
    uint32          m_hStopEvent;   // HANDLE - Notification to shut down
#else
    pthread_t       m_ThreadID;
    bool            m_bRunning;
    bool            m_bTerminate;
#endif
};


#endif




