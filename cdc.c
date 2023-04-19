#include "cdc.h"
#include <stdlib.h>
#ifdef __APPLE__
	#include <unistd.h>
	#include <mach-o/dyld.h>
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

