#include "cdc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef __APPLE__
    	#include <mach-o/dyld.h>
#endif
#ifdef unix
    #include <unistd.h>
    #include <dlfcn.h>
#endif
#if defined(WIN32)
    #include <Windows.h>
#endif
#if defined(linux)
    #include <linux/limits.h>
#endif

//returns current work directory
char* cdc_get_current_directory(){
#ifdef unix
    size_t buffer_size = 64;
    char* buf = (char*)malloc(buffer_size);
    while(getcwd(buf, buffer_size) == NULL){
        buffer_size += 64;
        buf = (char*)realloc(buf, buffer_size);
    }
    return buf;
#endif
#ifdef WIN32
    size_t buffer_size = GetCurrentDirectory(0, NULL);
    char* buf = (char*)malloc(buffer_size);
    GetCurrentDirectory(buffer_size, buf);
    return buf;
#endif
}

//returns path to the current running executable
char* cdc_get_executable_directory() {
#ifdef __APPLE__
    uint32_t buffer_size = 64;
    char* buf = (char*)malloc(buffer_size);
    while (_NSGetExecutablePath(buf, &buffer_size) == -1) {
        buffer_size += 64;
        buf = (char*)realloc(buf, buffer_size);
    }
#endif
#if defined(WIN32)
    size_t buffer_size = 0;
    char* buf = (char*)malloc(buffer_size);
    do {
        buffer_size += 64;
        buf = (char*)realloc(buf, buffer_size);
        GetModuleFileName(NULL, buf, buffer_size);
    } while (GetLastError() == ERROR_INSUFFICIENT_BUFFER);
#endif

#if defined(linux)
    char* buf = (char*)malloc(PATH_MAX);
    readlink("/proc/self/exe", buf, PATH_MAX);
#endif
    char* last_symbol = strrchr(buf, cdc_path_separator);
    if (last_symbol == NULL) {
        return buf;
    }
    size_t result_length = last_symbol - buf + 1;
    char* result = (char*)malloc(result_length);
    result = memcpy(result, buf, result_length);
    result[result_length - 1] = '\0';
    free(buf);
    return result;
}

//opens dynamic library, reqires path to library without file extension (will be added automaticly), if path_to_dl equals to "" returns handler to C standart lib
cdc_dynamic_lib_handle cdc_open_dynamic_lib(char* path_to_dl) {
    size_t new_str_len = strlen(path_to_dl);
#ifdef __APPLE__
    new_str_len += 6;
    char* extension = ".dylib";
#elif defined(WIN32)
    new_str_len += 4;
    char* extension = ".dll";
#elif defined(linux)
    new_str_len += 3;
    char* extension = ".so";
#endif
    char* real_path = 0;
    if (strlen(path_to_dl) != 0) {
        real_path = (char*)malloc(new_str_len + 1);
        real_path = memcpy(real_path, path_to_dl, strlen(path_to_dl) + 1);
        real_path = strcat(real_path, extension);
    }
#ifdef unix
    void* handler = dlopen(real_path, RTLD_NOW);
#elif defined(WIN32)
    HINSTANCE handler;
    if (real_path == 0) {
        handler = GetModuleHandle("ucrtbase.dll");
        if (handler == 0) {
            handler = GetModuleHandle("ucrtbased.dll");
        }
    }
    else {
        handler = LoadLibrary(real_path);
    }
#endif
    if(real_path != 0){
        free(real_path);
    }
    return (cdc_dynamic_lib_handle)(handler);
}

cdc_dynamic_lib_handle cdc_get_current_module(){
#ifdef unix
    void* handler = dlopen(0, RTLD_NOW);
#elif defined(WIN32)
    HINSTANCE handler;
    handler = GetModuleHandle(NULL);
#endif
    return (cdc_dynamic_lib_handle)(handler);
}

//extracts pointer to symbol at dynamic library
void* cdc_get_dynamic_lib_member(cdc_dynamic_lib_handle dl_handle, char* member_name){
#ifdef unix
    return dlsym(dl_handle, member_name);
#elif defined(__CYGWIN__) || defined(WIN32)
    return GetProcAddress(dl_handle, member_name);
#endif
}

//close dynamic library
void cdc_close_dynamic_lib(cdc_dynamic_lib_handle dl_handle){
#ifdef unix_
    dlclose(dl_handle);
#elif defined(WIN32) || defined(__CYGWIN__)
    FreeLibrary(dl_handle);
#endif
}

void cdc_set_cursor(int x, int y){
#ifdef unix
    printf("\033[%d;%dH", y, x);
#elif defined(WIN32)
    COORD coords;
    coords.X = x;
    coords.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
#endif
}

void cdc_clear_console(){
#ifdef unix
    printf("\033[H\033[J");
#elif defined(WIN32)
    HWND hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 }; 
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hConsole,        
        (TCHAR)' ',     
        dwConSize,       
        coordScreen,     
        &cCharsWritten)) 
    {
        return;
    }

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    if (!FillConsoleOutputAttribute(hConsole, 
        csbi.wAttributes,
        dwConSize,        
        coordScreen,      
        &cCharsWritten)) 
    {
        return;
    }

    SetConsoleCursorPosition(hConsole, coordScreen);
#endif
}

