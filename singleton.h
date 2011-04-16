#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
    class Singleton
{
public:
    static T* instance() {
    if(!m_pInstance) m_pInstance = new T;
    return m_pInstance;
    }
protected:
    Singleton();
    ~Singleton();
private:
    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);
    static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance=NULL;

#endif // SINGLETON_H
