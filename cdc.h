#ifndef _CDC
#define _CDC

#ifdef __APPLE__
#define cdc_path_separator '/'

#ifdef __cplusplus
	#define DL_EXTERN extern "C"
#else
	#define DL_EXTERN extern
#endif
#elif defined(WIN32)
#define cdc_path_separator '\\'

#ifdef __cplusplus
	#define DL_EXTERN extern "C" __declspec(dllexport)
#else
	#define DL_EXTERN extern __declspec(dllexport)
#endif
#endif

typedef void* cdc_dynamic_lib_handle; 
#ifdef __cplusplus
extern "C"{
#endif

//returns current work directory
char* cdc_get_current_directory();
//returns path to the current running executable
char* cdc_get_executable_directory();
//opens dynamic library, reqires path to library without file extension (will be added automaticly)
cdc_dynamic_lib_handle cdc_open_dynamic_lib(char* path_to_dl);
//extracts pointer to symbol at dynamic library
void* cdc_get_dynamic_lib_member(cdc_dynamic_lib_handle dl_handle, char* member_name);
//close dynamic library
void cdc_close_dynamic_lib(cdc_dynamic_lib_handle dl_handle);

#ifdef __cplusplus
}
#endif

#endif
