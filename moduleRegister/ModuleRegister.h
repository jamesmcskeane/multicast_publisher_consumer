#ifndef Included_MODULE_REGISTER_H
#define Included_MODULE_REGISTER_H
#include <map>
#include <iostream>

//  Singileton, we only ever want one ModuleRegister so the object will
//  only ever return a reference to the original instance.

class ModuleRegister
{
    //  Simple template will tahe object and add it to the register map
    //  and return the module when called
    public:
    static ModuleRegister& getInstance()
    {
        static ModuleRegister mModuleRegister;
        return mModuleRegister;
    }

    template <class T>
    void Register (T *module)
    {
        m_modules [T::ModuleID] = module;
    }

    template <class T>
    T *Module ()
    {
        return reinterpret_cast <T *> (m_modules [T::ModuleID]);
    }

    private:
    ModuleRegister(){};
    ModuleRegister(ModuleRegister const&);
    void operator=(ModuleRegister const&);
    std::map <int, void*> m_modules;
};

#endif

