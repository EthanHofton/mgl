#include <mgl/mglpch.hpp>

namespace mgl
{
    Config *Config::s_instance = nullptr;
    Logger *Logger::s_instance = nullptr;
        
    Config *Config::instance()
    {
        if (s_instance == nullptr)
        {
            s_instance = new Config;
        }
        
        return s_instance;
    }
    
    void Config::release()
    {
        if (s_instance != nullptr)
        {
            delete s_instance;
            s_instance = nullptr;
        }
    }

    Config::Config()
    {
        // TODO: use user defined macro
        std::string loggerConfigFile = "config/loggerConfig.json";
        std::string gameConfigFile = "config/gameConfig.json";
        
        m_loggerConifg.Parse(readFile(loggerConfigFile).c_str());
        m_gameConfig.Parse(readFile(gameConfigFile).c_str());
    }

    Config::~Config()
    {
        spdlog::drop("CORE_CONSOLE");
        spdlog::drop("CORE");
        spdlog::drop("APP_CONSOLE");
        spdlog::drop("APP");
    }
    
    std::string readFile(std::string t_filename)
    {
        std::string line;
        std::string output;
        std::ifstream file(t_filename);
        
        assert(file.is_open());
        
        while (std::getline(file, line))
        {
            output.append(line);
        }
        
        return output;
    }

    std::string readFileWithNewline(std::string t_filename)
    {
        std::string line;
        std::string output;
        std::ifstream file(t_filename);
        
        assert(file.is_open());
        
        while (std::getline(file, line))
        {
            output.append(line + '\n');
        }
        
        return output;
    }

    Logger* Logger::instance()
    {
        if (s_instance == nullptr)
        {
            s_instance = new Logger();
        }
        
        return s_instance;
    }

    void Logger::release()
    {
        if (s_instance != nullptr)
        {
            delete s_instance;
            s_instance = nullptr;
        }
    }

    Logger::Logger()
    {
        // * set logging pattern
        spdlog::set_pattern(LOGGER_CONFIG()["format"].GetString());
        std::string path = "logs/";
        
        // * try create the file loggers (catch logger execption)
        try
        {
            m_coreFileLogger = spdlog::basic_logger_mt("CORE", path + "core.log");
            m_clientFileLogger = spdlog::basic_logger_mt("APP", path + "app.log");
        } catch (const spdlog::spdlog_ex &ex) {
            std::cout << "Logger init failed: " << ex.what() << std::endl;
        }
        
        // * create console loggers
        m_coreConsoleLogger = spdlog::stdout_color_mt("CORE_CONSOLE");
        m_clientConsoleLogger = spdlog::stdout_color_mt("APP_CONSOLE");
        
        // * set logger debug levels
        int loggerLevel = LOGGER_CONFIG()["level"].GetInt();
        m_coreConsoleLogger->set_level((spdlog::level::level_enum)loggerLevel);
        m_clientConsoleLogger->set_level((spdlog::level::level_enum)loggerLevel);
        m_coreFileLogger->set_level((spdlog::level::level_enum)loggerLevel);
        m_clientFileLogger->set_level((spdlog::level::level_enum)loggerLevel);
        
        // * log that the loggers were initalised
        coreInfo("loggers initalised");
    }


}