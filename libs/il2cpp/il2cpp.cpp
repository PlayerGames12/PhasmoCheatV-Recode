#include "il2cpp.h"
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

static HMODULE g_gameAssembly = nullptr;

// function pointers
static t_il2cpp_domain_get p_il2cpp_domain_get = nullptr;
static t_il2cpp_thread_attach p_il2cpp_thread_attach = nullptr;
static t_il2cpp_domain_assembly_open p_il2cpp_domain_assembly_open = nullptr;
static t_il2cpp_assembly_get_image p_il2cpp_assembly_get_image = nullptr;
static t_il2cpp_class_from_name p_il2cpp_class_from_name = nullptr;
static t_il2cpp_object_new p_il2cpp_object_new = nullptr;
static t_il2cpp_class_get_method_from_name p_il2cpp_class_get_method_from_name = nullptr;
static t_il2cpp_runtime_invoke p_il2cpp_runtime_invoke = nullptr;
static t_il2cpp_string_new p_il2cpp_string_new = nullptr;
static t_il2cpp_class_get_type p_il2cpp_class_get_type = nullptr;
static t_il2cpp_type_get_object p_il2cpp_type_get_object = nullptr;

// новые указатели на функции
static t_il2cpp_object_get_class p_il2cpp_object_get_class = nullptr;
static t_il2cpp_class_get_field_from_name p_il2cpp_class_get_field_from_name = nullptr;
static t_il2cpp_field_set_value p_il2cpp_field_set_value = nullptr;

static bool ResolveSymbol(const char* name, FARPROC* out)
{
    if (!g_gameAssembly) return false;
    *out = GetProcAddress(g_gameAssembly, name);
    return *out != nullptr;
}

bool il2cpp_initialize()
{
    if (g_gameAssembly) return true;
    g_gameAssembly = GetModuleHandleA("GameAssembly.dll");
    if (!g_gameAssembly) return false;

    FARPROC proc = nullptr;
    ResolveSymbol("il2cpp_domain_get", &proc); p_il2cpp_domain_get = (t_il2cpp_domain_get)proc;
    ResolveSymbol("il2cpp_thread_attach", &proc); p_il2cpp_thread_attach = (t_il2cpp_thread_attach)proc;
    ResolveSymbol("il2cpp_domain_assembly_open", &proc); p_il2cpp_domain_assembly_open = (t_il2cpp_domain_assembly_open)proc;
    ResolveSymbol("il2cpp_assembly_get_image", &proc); p_il2cpp_assembly_get_image = (t_il2cpp_assembly_get_image)proc;
    ResolveSymbol("il2cpp_class_from_name", &proc); p_il2cpp_class_from_name = (t_il2cpp_class_from_name)proc;
    ResolveSymbol("il2cpp_object_new", &proc); p_il2cpp_object_new = (t_il2cpp_object_new)proc;
    ResolveSymbol("il2cpp_string_new", &proc); p_il2cpp_string_new = (t_il2cpp_string_new)proc;

    // основные функции
    ResolveSymbol("il2cpp_class_get_type", &proc); p_il2cpp_class_get_type = (t_il2cpp_class_get_type)proc;
    ResolveSymbol("il2cpp_type_get_object", &proc); p_il2cpp_type_get_object = (t_il2cpp_type_get_object)proc;
    ResolveSymbol("il2cpp_class_get_method_from_name", &proc); p_il2cpp_class_get_method_from_name = (t_il2cpp_class_get_method_from_name)proc;
    ResolveSymbol("il2cpp_runtime_invoke", &proc); p_il2cpp_runtime_invoke = (t_il2cpp_runtime_invoke)proc;

    // новые функции для работы с полями
    ResolveSymbol("il2cpp_object_get_class", &proc); p_il2cpp_object_get_class = (t_il2cpp_object_get_class)proc;
    ResolveSymbol("il2cpp_class_get_field_from_name", &proc); p_il2cpp_class_get_field_from_name = (t_il2cpp_class_get_field_from_name)proc;
    ResolveSymbol("il2cpp_field_set_value", &proc); p_il2cpp_field_set_value = (t_il2cpp_field_set_value)proc;

    return true;
}

// Обертки для основных функций
const Il2CppType* il2cpp_class_get_type(Il2CppClass* klass) {
    if (!p_il2cpp_class_get_type) return nullptr;
    return p_il2cpp_class_get_type(klass);
}

Il2CppObject* il2cpp_type_get_object(const Il2CppType* type) {
    if (!p_il2cpp_type_get_object) return nullptr;
    return p_il2cpp_type_get_object(type);
}

const MethodInfo* il2cpp_class_get_method_from_name_wrap(Il2CppClass* klass, const char* name, int args) {
    if (!p_il2cpp_class_get_method_from_name) return nullptr;
    return p_il2cpp_class_get_method_from_name(klass, name, args);
}

void il2cpp_runtime_invoke_wrap(const MethodInfo* method, void* obj, void** params, void* exc) {
    if (!p_il2cpp_runtime_invoke) return;
    p_il2cpp_runtime_invoke(method, obj, params, exc);
}

// Обертки для новых функций
Il2CppClass* il2cpp_object_get_class_wrap(Il2CppObject* obj) {
    if (!p_il2cpp_object_get_class) return nullptr;
    return p_il2cpp_object_get_class(obj);
}

FieldInfo* il2cpp_class_get_field_from_name_wrap(Il2CppClass* klass, const char* name) {
    if (!p_il2cpp_class_get_field_from_name) return nullptr;
    return p_il2cpp_class_get_field_from_name(klass, name);
}

void il2cpp_field_set_value_wrap(Il2CppObject* obj, FieldInfo* field, void* value) {
    if (!p_il2cpp_field_set_value) return;
    p_il2cpp_field_set_value(obj, field, value);
}

Il2CppDomain* il2cpp_domain_get()
{
    if (!p_il2cpp_domain_get) return nullptr;
    return p_il2cpp_domain_get();
}

void il2cpp_thread_attach(Il2CppDomain* domain)
{
    if (!p_il2cpp_thread_attach) return;
    p_il2cpp_thread_attach(domain);
}

Il2CppClass* il2cpp_get_class(const char* assemblyName, const char* namespaze, const char* name)
{
    if (!il2cpp_initialize()) return nullptr;
    Il2CppDomain* domain = il2cpp_domain_get();
    if (!domain) return nullptr;

    Il2CppAssembly* asmHandle = p_il2cpp_domain_assembly_open(domain, assemblyName);
    if (!asmHandle) return nullptr;

    Il2CppImage* image = p_il2cpp_assembly_get_image(asmHandle);
    if (!image) return nullptr;

    if (p_il2cpp_class_from_name)
    {
        return p_il2cpp_class_from_name(image, namespaze, name);
    }

    return nullptr;
}

Il2CppObject* il2cpp_object_new_from_class(Il2CppClass* klass)
{
    if (!klass) return nullptr;
    if (!p_il2cpp_object_new) return nullptr;
    return p_il2cpp_object_new(klass);
}

Il2CppString* il2cpp_string_new_wrap(const char* str)
{
    if (!p_il2cpp_string_new) return nullptr;
    return p_il2cpp_string_new(str);
}

Il2CppObject* CreateIl2CppObject(const char* assemblyName, const char* namespaze, const char* name)
{
    if (!il2cpp_initialize()) return nullptr;
    Il2CppDomain* domain = il2cpp_domain_get();
    if (!domain) return nullptr;

    // attach current thread
    il2cpp_thread_attach(domain);

    Il2CppClass* klass = il2cpp_get_class(assemblyName, namespaze, name);
    if (!klass)
    {
        std::cout << "[il2cpp] class not found: " << namespaze << "." << name << " in " << assemblyName << std::endl;
        return nullptr;
    }

    Il2CppObject* obj = il2cpp_object_new_from_class(klass);
    if (!obj)
    {
        std::cout << "[il2cpp] failed to allocate object." << std::endl;
        return nullptr;
    }

    // если есть ctor — попытаемся вызвать его (".ctor")
    if (p_il2cpp_class_get_method_from_name && p_il2cpp_runtime_invoke)
    {
        const MethodInfo* ctor = p_il2cpp_class_get_method_from_name(klass, ".ctor", 0);
        if (ctor)
        {
            p_il2cpp_runtime_invoke(ctor, obj, nullptr, nullptr);
        }
    }

    std::cout << "[il2cpp] created object: " << obj << std::endl;
    return obj;
}