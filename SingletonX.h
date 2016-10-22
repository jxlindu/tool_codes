#ifndef __SINGLETONX_H__
#define __SINGLETONX_H__

#include <pthread.h>

template <class T>
class SingletonX
{
    public:
	static T& getInstance()
	{
	    if(NULL == m_pInstance)
	    {
		pthread_mutex_lock(&m_mutex);

		if(NULL == m_pInstance)
		{
		    T* temp = new T();
		    m_pInstance = temp;
		}

		pthread_mutex_unlock(&m_mutex);
	    }

	    return *m_pInstance;
	}

	static void deleteInstance()
	{
	    if(NULL == m_pInstance)
	    {
		pthread_mutex_lock(&m_mutex);

		if(NULL == m_pInstance)
		{
		    delete m_pInstance;
		    m_pInstance = NULL;
		}

		pthread_mutex_unlock(&m_mutex);
	    }
	}

    protected:
	SingletonX() {}
	~SingletonX() {}

    private:
	SingletonX(const Singleton&);
	SingletonX& operator = (const Singleton&);

    private:
	static T* m_pInstance;
	static pthread_mutex_t m_mutex;
};

template<class T> T* SingletonX<T>::m_pInstance = NULL;
template<class T> pthread_mutex_t SingletonX<T>::m_mutex;

#endif // __SINGLETONX_H__
