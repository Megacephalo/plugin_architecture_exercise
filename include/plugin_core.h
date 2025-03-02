#ifndef _PLUGIN_CORE_H_
#define _PLUGIN_CORE_H_

#include <string>
#include <dlfcn.h>
#include <memory>

struct PluginInfo {
    std::string name;
    std::string version;
    std::string description;
    std::string author;
    std::string license;
    std::string url;
    void* handle; // WIP
};

// functor of custom deleter for the dynamic library handle
struct DLCloseDeleter {
    void operator() (void* handle) const {
        if (handle != nullptr)  dlclose(handle);
    }
};

typedef std::unique_ptr<void, DLCloseDeleter> DLibHandle;

#endif // _PLUGIN_CORE_H_