// Copyright (c) 2016
// Author: Chrono Law
#include <stdexcept>

#include <std.hpp>
using namespace std;

extern "C" {
#include <dlfcn.h>
}

class DlManager
{
public:
    DlManager(const char* name)
    {
        m_h = dlopen(name, RTLD_NOW);
        assert(m_h);
    }
    ~DlManager()
    {
        dlclose(m_h);
    }

    template<typename FuncType>
    FuncType load(const char* func_name)
    {
        FuncType pf = reinterpret_cast<FuncType>
            (dlsym(m_h, func_name));
        if (!pf)
        {
            throw std::runtime_error(dlerror());
        }
        return pf;
    }
private:
    typedef void* handle_t;
    handle_t m_h;
};

typedef int (*Func1)(int);
typedef int (*Func2)(int, int);

int main()
{
    cout << "dll version 1" << endl;

    DlManager dm("libtest.so");

    Func1 f1 = dm.load<Func1>("so_func1");
    Func2 f2 = dm.load<Func2>("so_func2");

    cout << f1(10) << endl;
    cout << f2(10, 20) << endl;

    cout << dm.load<Func1>("so_func1")(10) << endl;
    cout << dm.load<Func2>("so_func2")(10, 20) << endl;

}

