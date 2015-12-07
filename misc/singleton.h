#ifndef SINGLETON
#define SINGLETON

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




