/*
 *	File: unnamedsemaphorelite.hpp
 *
 *	Created on: 14 Dec 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file semaphore for interprocess usage
 *  This semaphore implemets only 2 functions wait() and post()
 *
 */
#ifndef UNNAMEDSEMAPHORELITE_HPP
#define UNNAMEDSEMAPHORELITE_HPP

#ifdef WIN32
#include <windows.h>
#else
#include <semaphore.h>
#define SHARING_TYPE	0/* 0 means semaphores is shared between threads in same process */
#endif

namespace decent_tools
{

#ifndef TYPE_SEMA_defined
#define TYPE_SEMA_defined
#ifdef WIN32
typedef HANDLE TYPE_SEMA;
#else
typedef sem_t TYPE_SEMA;
#endif
#endif  // #ifndef TYPE_SEMA_defined

class UnnamedSemaphoreLite
{
public:
    UnnamedSemaphoreLite()
    {
#ifdef WIN32
        m_Semaphore = CreateSemaphore( 0, (LONG)0, (LONG)100, 0 );
#else
        sem_init( &m_Semaphore, SHARING_TYPE, 0 );
#endif
    }

    ~UnnamedSemaphoreLite()
    {
#ifdef WIN32
        CloseHandle( m_Semaphore );
#else
        sem_destroy( &m_Semaphore );
#endif
    }

    void post()
    {
#ifdef WIN32
        ReleaseSemaphore( m_Semaphore, 1, 0  );
#else
        sem_post( &m_Semaphore );
#endif
    }

    void wait()
    {
#ifdef WIN32
        WaitForSingleObject( m_Semaphore, INFINITE );
#else
        sem_wait( &m_Semaphore );
#endif
    }

private:
    TYPE_SEMA m_Semaphore;
};

}

#endif // UNNAMEDSEMAPHORELITE_HPP
