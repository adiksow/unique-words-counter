///////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @file      main.cpp
 * @author    Andrii Dubyk
 * @date      Jun 05, 2023
 * @brief     Main of unique words counter application.
 *
 * @copyright Copyright (c) 2023 Andrii Dubyk, All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <thread>
#include <exception>
#include <cmath>
#include <algorithm>
#include <functional>

#include "app_context.h"

constexpr char DELIM = ' ';

constexpr const char *usageHelp()
{
    return "Invalid arguments\n"
           "Usage : ./uwc <input_file> [-c chunk_size_in_bytes]\n"
           "Example : ./uwc input_file.txt -c 1000000\n";
}

bool parseCmdOptions(const std::vector<std::string> &args, AppContext &context)
{
    bool ret = false;

    if (!args.size())
    {
        std::cout << usageHelp();
        return ret;
    }

    try
    {
        for (size_t i = 0; i < args.size(); i++)
        {
            if (args[i] == "-c")
            {
                const std::string val = args[++i];
                if (!std::all_of(val.begin(), val.end(), ::isdigit))
                {
                    std::cout << usageHelp();
                    return ret;
                }
                context.setChunkSize(std::stoull(val));
            }
            else
            {
                context.setInputFilePath(args[i]);
            }
        }

        ret = true;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << "\n";
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Out of range: " << e.what() << "\n";
    }

    return ret;
}

int countUniqueWords(const AppContext &context)
{
    // Open the text file
    std::ifstream ifs(context.getInputFilePath(), std::ios::binary);

    if (!ifs)
    {
        std::cout << "Error opening file!\n";
        return -1;
    }

    // Determine the size of the file
    ifs.seekg(0, std::ios::end);
    size_t fileSize = ifs.tellg();
    std::cout << "File size : " << fileSize << " bytes (" << static_cast<long double>(fileSize / std::pow(10, 6)) << " MB)\n";
    ifs.seekg(0, std::ios::beg);

    // Calculate the number of chunks based on the file size and chunk size
    unsigned long chunkSize = context.getChunkSize();
    size_t numChunks = (fileSize + chunkSize - 1) / chunkSize;
    std::cout << "Number of chunks : " << numChunks << "\n";

    // Vector to store the unique word sets for each chunk
    std::vector<std::unordered_set<std::string>> uniqueWordSets(numChunks);
    // Threads to process each chunk
    std::vector<std::thread> threads;

    // Function to process a file chunk and count unique words
    const auto processChunkHandler = [](const std::string &chunk, std::unordered_set<std::string> &uniqueWords)
    {
        std::string word;
        std::stringstream ss(chunk);

        while (ss >> word)
        {
            uniqueWords.insert(word);
        }
    };

    for (size_t i = 0; i < numChunks && !ifs.eof(); ++i)
    {
        // Read the chunk from the file
        std::string chunk(chunkSize, '\0');
        ifs.read(chunk.data(), chunkSize);

        if (ifs.gcount() < chunkSize)
        {
            chunk.resize(ifs.gcount());
        }

        if (chunk.back() != DELIM)
        {
            // Read until next ' '
            char temp;
            while (ifs.get(temp))
            {
                chunk.push_back(temp);
                if (temp == DELIM)
                {
                    break;
                }
            }
        }

        // Start thread to process the chunk
        threads.emplace_back(processChunkHandler, std::move(chunk), std::ref(uniqueWordSets[i]));
    }

    // Wait for all threads to finish
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    // Merge the unique word sets into a single set
    std::unordered_set<std::string> uniqueWords;
    for (const auto &uniqueWordSet : uniqueWordSets)
    {
        uniqueWords.insert(uniqueWordSet.begin(), uniqueWordSet.end());
    }

    // Close the file
    ifs.close();

    // Print the number of unique words
    std::cout << "Number of unique words: " << uniqueWords.size() << "\n";

    return uniqueWords.size();
}

int main(int argc, char *argv[])
{
    AppContext context{};

    bool ret = parseCmdOptions({argv + 1, argv + argc}, context);
    if (!ret)
    {
        std::cout << "Failed to parse cmd options!\n";
        return -1;
    }

    ret = context.initialize();
    if (!ret)
    {
        std::cout << "Failed to initialize application context using provided configuration!\n";
        return -1;
    }

    ret = countUniqueWords(context) >= 0 ? true : false;
    if (!ret)
    {
        std::cout << "Program execution failed!\n";
        return -1;
    }

    return 0;
}