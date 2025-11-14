#include "hooking.h"

using namespace PhasmoCheatV;

Hooking::Hooking()
{
    hooking = this;
}

Hooking::~Hooking()
{
    if (renderer && renderer->Window)
        SetWindowLongPtr(renderer->Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(OriginalWndproc));

    hooking = nullptr;
}

void Hooking::AddHook(const std::string& name, PVOID* original, PVOID hook)
{
    hooks_.emplace_back(name, original, hook);
}

void Hooking::ApplyHooks() const
{
    LOG_HOOKS("Detour begin");

    if (DetourTransactionBegin() != NO_ERROR)
        throw std::runtime_error("Detour begin fail");

    if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
        throw std::runtime_error("Detour thread fail");

    for (auto& h : hooks_)
    {
        LOG_HOOKS("Attach: " + std::get<0>(h));
        auto e = DetourAttach(std::get<1>(h), std::get<2>(h));
        if (e != NO_ERROR)
            LOG_ERROR("Attach fail: " + std::get<0>(h) + " err=" + std::to_string(e));
    }

    if (DetourTransactionCommit() != NO_ERROR)
        throw std::runtime_error("Detour commit fail");

    LOG_HOOKS("Detour commit");
}

void Hooking::RemoveHooks() const
{
    LOG_HOOKS("Detour remove begin");

    if (hooks_.empty())
    {
        LOG_HOOKS("No hooks");
        return;
    }

    if (DetourTransactionBegin() != NO_ERROR)
        return;

    if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
    {
        DetourTransactionAbort();
        return;
    }

    for (auto& h : hooks_)
    {
        LOG_HOOKS("Detach: " + std::get<0>(h));
        auto e = DetourDetach(std::get<1>(h), std::get<2>(h));
        if (e != NO_ERROR)
            LOG_ERROR("Detach fail: " + std::get<0>(h) + " err=" + std::to_string(e));
    }

    if (DetourTransactionCommit() != NO_ERROR)
        LOG_ERROR("Detour remove commit fail");

    LOG_HOOKS("Detour remove done");
}
