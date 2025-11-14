#pragma once
#include <cstdint>
#include <Windows.h>

#ifdef _WIN32
#include <Windows.h>
#endif

typedef void(*Il2CppMethodPointer)();

struct Il2CppType;
struct Il2CppClass;
struct Il2CppObject;
struct MethodInfo;
struct FieldInfo;
typedef uintptr_t il2cpp_array_size_t;

typedef void (*InvokerMethod)(Il2CppMethodPointer, const MethodInfo*, void*, void**, void*);

struct MethodInfo
{
    Il2CppMethodPointer methodPointer;
    Il2CppMethodPointer virtualMethodPointer;
    InvokerMethod invoker_method;
    const char* name;
    Il2CppClass* klass;
    const Il2CppType* return_type;
    const Il2CppType** parameters;
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t bitflags;
};

typedef struct Il2CppDomain Il2CppDomain;
typedef struct Il2CppAssembly Il2CppAssembly;
typedef struct Il2CppImage Il2CppImage;
typedef struct Il2CppString Il2CppString;

extern "C" {
    typedef Il2CppDomain* (*t_il2cpp_domain_get)(); 
    typedef void (*t_il2cpp_thread_attach)(Il2CppDomain*);
    typedef Il2CppAssembly* (*t_il2cpp_domain_assembly_open)(Il2CppDomain*, const char*);
    typedef Il2CppImage* (*t_il2cpp_assembly_get_image)(Il2CppAssembly*);
    typedef Il2CppClass* (*t_il2cpp_class_from_name)(Il2CppImage*, const char* namespaze, const char* name);
    typedef Il2CppObject* (*t_il2cpp_object_new)(Il2CppClass*);
    typedef Il2CppString* (*t_il2cpp_string_new)(const char*);
    typedef Il2CppString* (*t_il2cpp_string_new_utf16)(const wchar_t* str, int len);
    typedef const MethodInfo* (*t_il2cpp_class_get_method_from_name)(Il2CppClass*, const char* name, int argsCount);
    typedef void (*t_il2cpp_runtime_invoke)(const MethodInfo*, void*, void**, void*);
    typedef const char* (*t_il2cpp_type_get_name)(const Il2CppType*);
    typedef const Il2CppType* (*t_il2cpp_class_get_type)(Il2CppClass* klass);
    typedef Il2CppObject* (*t_il2cpp_type_get_object)(const Il2CppType* type);
    typedef Il2CppClass* (*t_il2cpp_object_get_class)(Il2CppObject* obj);
    typedef FieldInfo* (*t_il2cpp_class_get_field_from_name)(Il2CppClass* klass, const char* name);
    typedef void (*t_il2cpp_field_set_value)(Il2CppObject* obj, FieldInfo* field, void* value);

    bool il2cpp_initialize();
    Il2CppDomain* il2cpp_domain_get();
    void il2cpp_thread_attach(Il2CppDomain* domain);
    const Il2CppType* il2cpp_class_get_type(Il2CppClass* klass);
    Il2CppObject* il2cpp_type_get_object(const Il2CppType* type);
    const MethodInfo* il2cpp_class_get_method_from_name_wrap(Il2CppClass* klass, const char* name, int args);
    void il2cpp_runtime_invoke_wrap(const MethodInfo* method, void* obj, void** params, void* exc);
    Il2CppClass* il2cpp_get_class(const char* assemblyName, const char* namespaze, const char* name);
    Il2CppObject* il2cpp_object_new_from_class(Il2CppClass* klass);
    Il2CppObject* CreateIl2CppObject(const char* assemblyName, const char* namespaze, const char* name);
    Il2CppString* il2cpp_string_new_wrap(const char* str);
    Il2CppString* il2cpp_string_new_utf16_wrap(const wchar_t* str, int len);
    Il2CppClass* il2cpp_object_get_class_wrap(Il2CppObject* obj);
    FieldInfo* il2cpp_class_get_field_from_name_wrap(Il2CppClass* klass, const char* name);
    void il2cpp_field_set_value_wrap(Il2CppObject* obj, FieldInfo* field, void* value);

    Il2CppMethodPointer il2cpp_get_method_pointer(const char* assemblyName, const char* namespaze, const char* className, const char* methodName, int argsCount);
}