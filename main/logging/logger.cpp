#include "logger.h"
#include <ctime>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <cstdio>
#include "../Globals.h"

using namespace PhasmoCheatV::Globals;

namespace PhasmoCheatV
{
    Logger* logger = nullptr;

    constexpr std::string_view Logger::LevelToString(Level level)
    {
        switch (level)
        {
        case Level::Call: return "[Call]";
        case Level::Debug: return "[Debug]";
        case Level::Info: return "[Info]";
        case Level::Warning: return "[Warning]";
        case Level::Error: return "[Error]";
        case Level::Hooks: return "[Hooks]";
        default: return "[Unknown]";
        }
    }

    constexpr WORD Logger::LevelToColor(Level level)
    {
        switch (level)
        {
        case Level::Call:
            return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case Level::Debug:
            return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        case Level::Info:
            return FOREGROUND_GREEN | FOREGROUND_BLUE;
        case Level::Warning:
            return FOREGROUND_RED | FOREGROUND_GREEN;
        case Level::Error:
            return FOREGROUND_RED;
        case Level::Hooks:
            return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        default:
            return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
    }

    bool Logger::InitializeLogDirectory()
    {
        try
        {
            std::string dir = Utils::GetPhasmoCheatVDirectory() + "\\logs";
            if (!std::filesystem::exists(dir))
                std::filesystem::create_directories(dir);

            std::string lastPath = dir + "\\last-log.txt";
            std::string prevPath = dir + "\\prev-last-log.txt";

            if (std::filesystem::exists(lastPath))
            {
                if (std::filesystem::exists(prevPath))
                    std::filesystem::remove(prevPath);

                std::filesystem::rename(lastPath, prevPath);
            }

            auto now = std::time(nullptr);
            std::tm tmv;
            localtime_s(&tmv, &now);

            char ts[32];
            std::strftime(ts, sizeof(ts), "%Y-%m-%d_%H-%M-%S", &tmv);

            LogFilePath = dir + "\\log_" + ts + ".txt";
            FileOut.open(LogFilePath, std::ios::out | std::ios::app);
            FileOut.rdbuf()->pubsetbuf(nullptr, 0);

            std::filesystem::copy_file(LogFilePath, lastPath, std::filesystem::copy_options::overwrite_existing);

            return FileOut.is_open();
        }
        catch (...)
        {
            return false;
        }
    }

    Logger::Logger(Level minLevel)
        : MinLevel(minLevel), ConsoleExists(false), HConsole(nullptr)
    {
        if (!InitializeLogDirectory())
            throw std::runtime_error("Failed to initialize log directory");

        if (IsDebugging)
        {
            ConsoleExists = AllocConsole() != 0;
            if (ConsoleExists)
            {
                FILE* f;
                freopen_s(&f, "CONOUT$", "w", stdout);
                freopen_s(&f, "CONOUT$", "w", stderr);

                HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                if (HConsole && HConsole != INVALID_HANDLE_VALUE)
                {
                    DWORD mode;
                    if (GetConsoleMode(HConsole, &mode))
                    {
                        SetConsoleMode(HConsole, mode & ~ENABLE_QUICK_EDIT_MODE);
                        SetConsoleTitleA("PhasmoCheatV Console");
                        SetConsoleOutputCP(CP_UTF8);
                    }
                }
            }
        }
        logger = this;
    }

    Logger::~Logger()
    {
        if (FileOut.is_open())
            FileOut.close();
        if (ConsoleExists)
            FreeConsole();
        logger = nullptr;
    }

    std::string Logger::GetTimestamp()
    {
        char ts[32];
        auto now = std::time(nullptr);
        std::tm tmv;
        localtime_s(&tmv, &now);
        std::strftime(ts, sizeof(ts), "%H:%M:%S", &tmv);
        return ts;
    }

    void Logger::ActualLog(Level level, std::string_view msg)
    {
        if (level < MinLevel)
            return;
        if ((level == Level::Call || level == Level::Debug) && !IsCalledLogs)
            return;
        if ((level == Level::Info || level == Level::Warning) && !IsDebugging)
            return;

        std::string t = GetTimestamp();
        std::string s = std::string(LevelToString(level));

        {
            std::lock_guard lock(LogMutex);

            if (HConsole && HConsole != INVALID_HANDLE_VALUE)
            {
                SetConsoleTextAttribute(HConsole, LevelToColor(level));
                std::cout << s << " " << msg << std::endl;
                SetConsoleTextAttribute(HConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            if (FileOut.is_open() && FileOut.good())
            {
                FileOut << "[" << t << "] " << s << " " << msg << "\n";
                FileOut.flush();
            }
        }
    }
}
