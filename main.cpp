#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <libloaderapi.h>

using namespace std;

void get_proc_id(const char* window_title, DWORD &process_id)
{
    GetWindowThreadProcessId(FindWindow(NULL, window_title), &process_id);

}

void errordump(const char* error_title, const char* error_message)
{
    MessageBox(0, error_message, error_title, 0);
    exit(-1);
}

bool file_exists(string file_name)
{
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) == 0);
}

int main()
{
    DWORD proc_id = NULL; 
    char dll_path[MAX_PATH];
    const char* dll_name = "";
    const char* window_title = "";

    if (!file_exists(dll_name))
    {
        error("file_exists", "shi aint exists buddy");
    }

    if (!GetFullPathName(dll_name, MAX_PATH, dll_path, nullptr))
    {
        error("GetFullPathName", "fail to get full path N00b lmao");
    }

    get_proc_id(window_title, proc_id);
    if (proc_id == NULL)
    {
        error("get_proc_id", "fail to get process id idiotaa");
    }

    HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc_id);
    if (!h_process)
    {
        error("OpenProcess", "fail to open a handle to process piska")
    }

    void* allocated_memory = VirtualAllocEx(h_process, nullptr, MAX_PATH, MEM_COMMIT, PAGE_READWRITE);
    if (!allocated_memory)
    {
        error("VirtualAllocEx", "fail to allocate memory skibidfi")
    }

    if (!WriteProcessMemory(h_process, dll_path, MAX_PATH, nullptr))
    {
        error("WriteProcessMemory", "fail to write process memory nuh uh duke dennis")
    }

    HANDLE h_thread = CreateRemoteThread(h_process, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocated_memory, NULL, nullptr);
    if (!h_thread)
    {
        error("CreateRemoteThread", "fail to create remote thread gyatt level 30");
    }

    CloseHandle(h_process);
    VirtualFreeEx(h_process, allocated_memory, NULL, MEM_RELEASE);
    MessageBox(0, "inject success bi...", "success", ;0)

}