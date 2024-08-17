#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <Minhook.h>
#include <consoleapi.h>
#include <cstring>
#include <mutex>
#include <psapi.h>
#include <tchar.h>
#include <windows.h>

std::mutex consoleMutex;
std::condition_variable cv;
std::atomic<bool> stopThread(false);
HANDLE hMutex = NULL;

#endif
