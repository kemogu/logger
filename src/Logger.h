/**
 * @file Logger.h
 * 
 * @brief
 * 
 * @date 20.04.2025
 * @author Kemal Oğuzhan Yeyit
 */

 #ifndef LOGGER_H
 #define LOGGER_H

 #include "LogLevel.h"
 #include <string>
 #include <queue>
 #include <fstream>
 #include <mutex>
 #include <condition_variable>
 #include <thread>
 #include <atomic>
 #include <sstream>

 namespace Logging {

    class Logger {
        public:
            /**
             * @brief Gets the singleton instance of the Logger.
             * @return Reference to the Logger instance.
             */
            static Logger& getInstance();
        
            /**
             * @brief Logs a message with the specified log level and source information.
             * @param level The log level (DEBUG, INFO, WARN, ERROR).
             * @param message The message to log.
             * @param file The source file name where the log call originated.
             * @param line The line number in the source file.
             */
            void log(LogLevel level, const std::string& message, const std::string& file, int line);
        
            /**
             * @brief Shuts down the logger, flushing all pending messages.
             *
             * This method stops the background logging thread and flushes any remaining log messages.
             */
            void shutdown();
        
            // Delete copy and move constructors and assignment operators.
            Logger(const Logger&) = delete;
            Logger(Logger&&) = delete;
            Logger& operator=(const Logger&) = delete;
            Logger& operator=(Logger&&) = delete;
        
        private:
            /**
             * @brief Constructs a new Logger instance.
             *
             * Initializes the output file and starts the background thread responsible for processing the log queue.
             */
            Logger();
        
            /**
             * @brief Destructor that ensures the logger is shut down properly.
             */
            ~Logger();
                
            /**
             * @brief Converts a LogLevel value to its corresponding string representation.
             * @param level The log level to convert.
             * @return A string corresponding to the log level.
             */
            std::string logLevelToString(LogLevel level);
        
            /**
             * @brief Processes the log messages queue in a background thread.
             *
             * This function continuously waits for log messages to appear in the queue and writes them to the output file and console.
             */
            void processQueue();
        
            /**
             * @brief Flushes any remaining messages in the queue to the output file.
             */
            void flushQueue();
        
            std::ofstream outputFile;               ///< The output file stream used for logging.
            std::queue<std::string> messageQueue;   ///< Queue storing the formatted log messages.
            std::mutex queueMutex;                  ///< Mutex to protect access to the queue.
            std::condition_variable condVar;        ///< Condition variable used to signal new messages.
            std::thread backgroundThread;           ///< Background thread that processes the message queue.
            std::atomic<bool> exitFlag;             ///< Flag indicating that the logger should shut down.
        };
 }



 #endif // LOGGER_H