#ifndef util_hpp
#define util_hpp

#include <iostream>
#include <memory>

#define FMT_HEADER_ONLY
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <fstream>
#include <cassert>
#include <string>
#include <rapidjson/document.h>

using namespace rapidjson;

namespace mgl
{
    class Config
    {
    public:
        // * static create and delete functions       
        static Config* instance();
        static void release();
        
    private:
        
        // * private constructo and destructor
        Config();
        ~Config();
        
    public:

        // * return the logger config json document
        inline Document &getLoggerConifg() { return m_loggerConifg; }
        // * return the game config json document
        inline Document &getGameConifg() { return m_gameConfig; }
        
        // * fequetly used varibles
        inline int getWidth() { return m_gameConfig["width"].GetInt(); }
        inline int getHeight() { return m_gameConfig["height"].GetInt(); }
        
    private:
        
        // * private read file function
        std::string getFile(std::string t_filename);
        
    private:
        
        // * static instance
        static Config* s_instance;
        
        // * logger config document
        Document m_loggerConifg;
        // * game config document
        Document m_gameConfig;
    };

    // * config macros
    #define CONFIG() mgl::Config::instance()
    #define LOGGER_CONFIG() mgl::Config::instance()->getLoggerConifg()
    #define GAME_CONFIG() mgl::Config::instance()->getGameConifg()

    class Logger
    {
    public:
        
        // * singleton instance and releace functions
        static Logger* instance();
        static void release();
        
    private:
        
        // * logger constructor
        Logger();
        
    public:
        
        // * client logger functions
        template<typename... Args>
        inline void trace(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_clientFileLogger->trace(fmt, std::forward<Args>(args)...);
            m_clientConsoleLogger->trace(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void debug(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_clientFileLogger->debug(fmt, std::forward<Args>(args)...);
            m_clientConsoleLogger->debug(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void info(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_clientFileLogger->info(fmt, std::forward<Args>(args)...);
            m_clientConsoleLogger->info(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void warn(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_clientFileLogger->warn(fmt, std::forward<Args>(args)...);
            m_clientConsoleLogger->warn(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void error(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_clientFileLogger->error(fmt, std::forward<Args>(args)...);
            m_clientConsoleLogger->error(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void critical(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_clientFileLogger->critical(fmt, std::forward<Args>(args)...);
            m_clientConsoleLogger->critical(fmt, std::forward<Args>(args)...);
        }
        
        // * core logger functions
        template<typename... Args>
        inline void coreTrace(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_coreFileLogger->trace(fmt, std::forward<Args>(args)...);
            m_coreConsoleLogger->trace(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void coreDebug(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_coreFileLogger->debug(fmt, std::forward<Args>(args)...);
            m_coreConsoleLogger->debug(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void coreInfo(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_coreFileLogger->info(fmt, std::forward<Args>(args)...);
            m_coreConsoleLogger->info(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void coreWarn(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_coreFileLogger->warn(fmt, std::forward<Args>(args)...);
            m_coreConsoleLogger->warn(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void coreError(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_coreFileLogger->error(fmt, std::forward<Args>(args)...);
            m_coreConsoleLogger->error(fmt, std::forward<Args>(args)...);
        }
        
        template<typename... Args>
        inline void coreCritical(fmt::format_string<Args...> fmt, Args &&...args)
        {
            m_coreFileLogger->critical(fmt, std::forward<Args>(args)...);
            m_coreConsoleLogger->critical(fmt, std::forward<Args>(args)...);
        }
        
    private:
        
        // * class instance
        static Logger* s_instance;
        
        // * loggers
        std::shared_ptr<spdlog::logger> m_coreFileLogger;
        std::shared_ptr<spdlog::logger> m_clientFileLogger;
        std::shared_ptr<spdlog::logger> m_coreConsoleLogger;
        std::shared_ptr<spdlog::logger> m_clientConsoleLogger;
    };

    // * core logger macros
    #define CORE_TRACE(...) mgl::Logger::instance()->coreTrace(__VA_ARGS__)
    #define CORE_DEBUG(...) mgl::Logger::instance()->coreDebug(__VA_ARGS__)
    #define CORE_INFO(...) mgl::Logger::instance()->coreInfo(__VA_ARGS__)
    #define CORE_WARN(...) mgl::Logger::instance()->coreWarn(__VA_ARGS__)
    #define CORE_ERROR(...) mgl::Logger::instance()->coreError(__VA_ARGS__)
    #define CORE_CRITICAL(...) mgl::Logger::instance()->coreCritical(__VA_ARGS__)

    // * client logger macros
    #define APP_TRACE(...) mgl::Logger::instance()->trace(__VA_ARGS__)
    #define APP_DEBUG(...) mgl::Logger::instance()->debug(__VA_ARGS__)
    #define APP_INFO(...) mgl::Logger::instance()->info(__VA_ARGS__)
    #define APP_WARN(...) mgl::Logger::instance()->warn(__VA_ARGS__)
    #define APP_ERROR(...) mgl::Logger::instance()->error(__VA_ARGS__)
    #define APP_CRITICAL(...) mgl::Logger::instance()->critical(__VA_ARGS__)
    
}

#endif