#ifndef SINGLETON
#define SINGLETON

#include <qobject.h>

template<class T> class SingletonPtr;

template<class T> class SingletonDestroyer {
    T * p_instance;
public:
    SingletonDestroyer() : p_instance(0) {}
    ~SingletonDestroyer() { delete p_instance; }
    void initialize(T * p) { p_instance = p; }
};

template<class T> class SingletonPtr {
    static T * p_instance;
    static SingletonDestroyer<T> destroyer;
protected:
    SingletonPtr() { }
    SingletonPtr(const SingletonPtr &);
    SingletonPtr & operator=(SingletonPtr &);
    virtual ~SingletonPtr() { }
    friend class SingletonDestroyer<T>;
public:
    static T & obj() {
        if(!p_instance)
            destroyer.initialize((p_instance = new T()));
        return *p_instance;
    }

    static T & linked_obj_with_init(QObject * parent) {
        if(!p_instance)
            p_instance = new T(parent);
        return *p_instance;
    }
};

template<class T> T * SingletonPtr<T>::p_instance = 0;
template<class T> SingletonDestroyer<T> SingletonPtr<T>::destroyer;

template<class T> class Singleton {
public:
    static T & obj() {
        static T obj;
        return obj;
    }

    virtual ~Singleton() {}
protected:
    Singleton() {}
    Singleton(const Singleton &);
    Singleton & operator=(const Singleton &);
};

#endif // SINGLETON




