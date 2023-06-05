#ifndef APP_CONTEXT_H_
#define APP_CONTEXT_H_

///////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @file      app_context.h
 * @author    Andrii Dubyk
 * @date      Jun 05, 2023
 * @brief     Application context - contains context variables and configuration processing.
 *
 * @copyright Copyright (c) 2023 Andrii Dubyk, All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

/**
 * @brief Class which stores common context varaibles for program execution/configuration.
 */
class AppContext
{
private:
    /* Path to input file for processing. */
    std::string filePath_;

    /* Chunk size (in bytes) for processing by single thread. */
    unsigned long chunkSize_;

    /* Indicates if application context is properly initialized. */
    bool isInitialized_;

public:
    AppContext() = default;
    AppContext(const AppContext &) = default;
    AppContext(AppContext &&) = default;
    AppContext &operator=(const AppContext &) = default;
    AppContext &operator=(AppContext &&) = default;
    ~AppContext() = default;

    bool initialize();

    const std::string &getInputFilePath() const { return filePath_; };
    unsigned long getChunkSize() const { return chunkSize_; };

    void setInputFilePath(const std::string &filePath) { filePath_ = filePath; };
    void setChunkSize(unsigned long chunkSize) { chunkSize_ = chunkSize; };
};

#endif // APP_CONTEXT_H_
