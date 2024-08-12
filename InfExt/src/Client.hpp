#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <Minhook.h>
#include <array>                // IWYU pragma: keep
#include <consoleapi.h>
#include <cstring>    // IWYU pragma: keep
#include <fstream>    // IWYU pragma: keep
#include <functional> // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <map> // IWYU pragma: keep
#include <psapi.h>
#include <sstream> // IWYU pragma: keep
#include <string>  // IWYU pragma: keep
#include <tchar.h>
#include <unordered_map> // IWYU pragma: keep
#include <variant>       // IWYU pragma: keep
#include <windows.h>
#include <mutex>

std::mutex consoleMutex;
std::condition_variable cv;
std::atomic<bool> stopThread(false);
std::thread mainThread;
HANDLE hMutex = NULL;

#endif
