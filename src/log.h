/*
 * Copyright (C) 2020 Kandao Technology Co.,Ltd.
 *
 * This software is the property of Kandao Technology Co.,Ltd.
 * Use or redistribution of this software without written permission
 * from Kandao Technology Co.,Ltd is prohibited.
 *
 * @project  Kandao OS
 * @version  1.0
 * @author   Xing Dongfeng
 * @created  Fri Jul 28 2020
 */
#ifndef __BASE_LOG_H__
#define __BASE_LOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#if defined(KDVER_WIN32) || defined(KDVER_IOS) || defined(KDVER_MAC) || defined(KDVER_ANDROID) || defined(KDVER_LINUX)
#else
#if defined(unix)        || defined(__unix)      || defined(__unix__) \
|| defined(linux)       || defined(__linux)     || defined(__linux__) \
    || defined(sun)         || defined(__sun) \
    || defined(BSD)         || defined(__OpenBSD__) || defined(__NetBSD__) \
    || defined(__FreeBSD__) || defined (__DragonFly__) \
    || defined(sgi)         || defined(__sgi) \
    || defined(__CYGWIN__)
#define KDVER_LINUX
#elif defined(__MACOSX__) || defined(__APPLE__)
#if defined(TARGET_OS_IPHONE)
#define KDVER_IOS
#else
#define KDVER_MAC
#endif
#elif defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) \
|| defined(WIN64)    || defined(_WIN64) || defined(__WIN64__) || defined(_WINDOWS)
#define KDVER_WIN32
#else
#endif
#endif

#ifdef KDVER_WIN32
#if defined(_WIN64) || defined(_M_X64) || defined(_M_IA64) || defined(_M_AMD64)
#define KDVER_64BIT
#else
#endif
#else
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#define KDVER_64BIT
#else
#endif
#endif


#ifdef KDVER_WIN32
#if defined(KDEXP_UTL)
#define KDLOG_VAR         __declspec(dllexport)
#define KDLOG_API(type)   __declspec(dllexport) type __cdecl
#define KDLOG_CLS         __declspec(dllexport)
#elif defined(KDIMP_UTL)
#define KDLOG_VAR         __declspec(dllimport)
#define KDLOG_API(type)   __declspec(dllimport) type __cdecl
#define KDLOG_CLS         __declspec(dllimport)
#else
#define KDLOG_VAR
#define KDLOG_API(type)   type __cdecl
#define KDLOG_CLS
#endif
#else /* !WIN32 */
#if (defined(__GNUC__) || defined(__SUNPRO_CC) || defined (__SUNPRO_C)) && defined(GOAPI_VISIBILITY)
#define KDLOG_VAR         __attribute__((visibility("default")))
#define KDLOG_API(type)   __attribute__((visibility("default"))) type
#define KDLOG_CLS         __attribute__((visibility("default")))
#else
#define KDLOG_VAR
#define KDLOG_API(type) type
#define KDLOG_CLS
#endif
#endif


/*------------------------------------------include-------------------------------------------------------*/
typedef enum _LogLevel {
    LOG_VERBOSE = 0,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
} eLogLevel;


/*------------------------------------------Macro--------------------------------------------------------*/
/*
NOTE: You must specify the current module name ('module') before using it. eg:
    static const char *module = "log";
*/
#define KDLOG_DECLARE_MODULE_NAME(tag) static const char *module = #tag;
#define LOGV(format, ...) logV((char *)module, format, ##__VA_ARGS__)
#define LOGD(format, ...) logD((char *)module, format, ##__VA_ARGS__)
#define LOGI(format, ...) logI((char *)module, format, ##__VA_ARGS__)
#define LOGW(format, ...) logW((char *)module, format, ##__VA_ARGS__)
#define LOGE(format, ...) logE((char *)module, format, ##__VA_ARGS__)

/*------------------------------------------Func--------------------------------------------------------*/
/**
 * @brief log info output to console
 * 
 */
KDLOG_API(void) kdlog_output_to_console();

/**
 * @brief Set log info output to file
 * 
 * @param directory The directory of the log file that will to save
 * @param pattern The file name of the log file that will to save. 
 *                note: pattern contain "%d" to indicate a file index.
 * @param nFiles The maximum number of stored log file.
 * @param maxSize The maximum number of bytes the per log file.
 */
KDLOG_API(void) kdlog_output_to_file(const char *directory, const char *pattern, int nFiles, unsigned int maxSize);

/**
 * @brief finish
 * 
 */
KDLOG_API(void) kdlog_finish();
/**
 * @brief Specifying a log Level
 * 
 * @param level LogLevel
 */
KDLOG_API(void) kdlog_set_level(eLogLevel level);

///**
// * @brief Enable all modules
// *
// */
//KDLOG_API(void) kdlog_enable_all_modules();

///**
// * @brief Disable all modules
// *
// */
//KDLOG_API(void) kdlog_disable_all_modules();

///**
// * @brief Enable specifying module
// *
// * @param module
// */
//KDLOG_API(void) kdlog_enable_module(const char *module);

///**
// * @brief Disable specifying module
// *
// * @param module
// */
//KDLOG_API(void) kdlog_disable_module(const char *module);

KDLOG_API(void) logV(const char* module, const char* fmt, ...);
KDLOG_API(void) logD(const char* module, const char* fmt, ...);
KDLOG_API(void) logI(const char* module, const char* fmt, ...);
KDLOG_API(void) logW(const char* module, const char* fmt, ...);
KDLOG_API(void) logE(const char* module, const char* fmt, ...);


/*------------------------------------------end--------------------------------------------------------*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __BASE_LOG_H__ */
