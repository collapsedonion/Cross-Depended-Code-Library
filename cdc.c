#include "cdc.h"
#include <stdlib.h>
#include <string.h>
#ifdef __APPLE__
	#include <unistd.h>
	#include <mach-o/dyld.h>
	#include <dlfcn.h>
#endif


//returns current work directory
char* cdc_get_current_directory(){
#ifdef __APPLE__
	size_t buffer_size = 64;
	char* buf = (char*)malloc(buffer_size);
	while(getcwd(buf, buffer_size) == NULL){
		buffer_size += 64;
		buf = (char*)realloc(buf, buffer_size);
	}
	return buf;
#endif
}

//returns path to the current running executable
char* cdc_get_executable_directory(){
#ifdef __APPLE__
	uint32_t buffer_size = 64;
	char* path = (char*)malloc(buffer_size);
	while(_NSGetExecutablePath(path, &buffer_size) == -1){
		buffer_size += 64;
		path = (char*)realloc(path, buffer_size);
	}	
	return path;
#endif
}

//opens dynamic library, reqires path to library without file extension (will be added automaticly)
cdc_dynamic_lib_handle cdc_open_dynamic_lib(char* path_to_dl){
	size_t new_str_len = strlen(path_to_dl);
#ifdef __APPLE__
	new_str_len += 6;
	char* extension = ".dylib";
#endif
	char* real_path = (char*)malloc(new_str_len + 1);
	real_path = memcpy(real_path, path_to_dl, strlen(path_to_dl));
	real_path = strcat(real_path, extension);

#ifdef __APPLE__
	void* handler = dlopen(real_path, RTLD_NOW);	
#endif	
	free(real_path);
	return (cdc_dynamic_lib_handle)(handler);
}

//extracts pointer to symbol at dynamic library
void* cdc_get_dynamic_lib_member(cdc_dynamic_lib_handle dl_handle, char* member_name){
#ifdef __APPLE__
	return dlsym(dl_handle, member_name);
#endif
}

//close dynamic library
void cdc_close_dynamic_lib(cdc_dynamic_lib_handle dl_handle){
#ifdef __APPLE__
	dlclose(dl_handle);
#endif
}


