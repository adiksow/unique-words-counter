///////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @file      app_context.cpp
 * @author    Andrii Dubyk
 * @date      Jun 05, 2023
 * @brief     Application context - contains context variables and configurations processing.
 *
 * @copyright Copyright (c) 2023 Andrii Dubyk, All rights reserved.
 */
/////////////////////////////////////////////////////////////////////////////////////////////

#include "app_context.h"

#include <iostream>
#include <filesystem>
#include <cmath>

bool AppContext::initialize()
{
    if (isInitialized_)
    {
        std::cout << "Application context has alredy been initialized!\n";
        return false;
    }

    if (!std::filesystem::exists(filePath_))
    {
        std::cout << "Input file \"" << filePath_ << "\" does not exist!\n";
        return false;
    }

    if (!chunkSize_)
    {
        // Use default chunk size in bytes (100MB)
        chunkSize_ = 100000000;
    }

    std::cout << "Input file : \"" << filePath_ << "\"\n"
              << "Chunk size : " << chunkSize_ << " bytes (" << static_cast<long double>(chunkSize_ / std::pow(10, 6)) << " MB)"
              << "\n";

    isInitialized_ = true;

    return isInitialized_;
}
