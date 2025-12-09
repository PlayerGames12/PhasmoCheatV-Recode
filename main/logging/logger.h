#pragma once
#include <mutex>
#include <sstream>
#include <fstream>
#include <windows.h>
#pragma warning(disable: 4005)
#define LOG_INFO(...)
#include "../Includes.h"
using namespace PhasmoCheatV::Globals;
namespace PhasmoCheatV
{
    class Logger
    {
    public:
        enum class Level : uint8_t
        {
            Call,
            Debug,
            Info,
            Warning,
            Error,
            Hooks
        };
        explicit Logger(Level minLevel = Level::Call);
        ~Logger();
        template <typename T>
        void Log(const Level level, const T& message)
        {
            std::ostringstream ss;
            ss << message;
            ActualLog(level, ss.str());
        }
        template <typename T, typename... Args>
        void Log(const Level level, const T& first, const Args&... args)
        {
            std::ostringstream ss;
            ss << first;
            ((ss << " " << args), ...);
            ActualLog(level, ss.str());
        }
        void ActualLog(Level level, std::string_view message);
    private:
        const Level MinLevel;
        bool ConsoleExists;
        HANDLE HConsole;
        std::mutex LogMutex;
        std::ofstream FileOut;
        std::string LogFilePath;
        static constexpr std::string_view LevelToString(Level level);
        static constexpr WORD LevelToColor(Level level);
        static std::string GetTimestamp();
        bool InitializeLogDirectory();
    };
    extern Logger* logger;
}
#define LOG_CALL(...) \
    if (PhasmoCheatV::logger && IsCalledLogs) \
        PhasmoCheatV::logger->Log(PhasmoCheatV::Logger::Level::Call, __VA_ARGS__)
#define LOG_DEBUG(...) \
    if (PhasmoCheatV::logger && IsDebugging && IsCalledLogs) \
        PhasmoCheatV::logger->Log(PhasmoCheatV::Logger::Level::Debug, __VA_ARGS__)
#define LOG_INFO(...) \
    if (PhasmoCheatV::logger && IsDebugging) \
        PhasmoCheatV::logger->Log(PhasmoCheatV::Logger::Level::Info, __VA_ARGS__)
#define LOG_HOOKS(...) \
    if (PhasmoCheatV::logger && IsDebugging) \
        PhasmoCheatV::logger->Log(PhasmoCheatV::Logger::Level::Hooks, __VA_ARGS__)
#define LOG_WARN(...) \
    if (PhasmoCheatV::logger && IsDebugging) \
        PhasmoCheatV::logger->Log(PhasmoCheatV::Logger::Level::Warning, __VA_ARGS__)
#define LOG_ERROR(...) \
    if (PhasmoCheatV::logger) \
        PhasmoCheatV::logger->Log(PhasmoCheatV::Logger::Level::Error, __VA_ARGS__)
#define LOG_CALL_UPDATE(...) \
    if (PhasmoCheatV::logger && IsDebugging && IsUpdateCalledLogs) \
        PhasmoCheatV::logger->Log(PhasmoCheatV::Logger::Level::Call, __VA_ARGS__)