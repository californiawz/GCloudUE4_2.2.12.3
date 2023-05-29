#if defined(ANDROID)
#ifndef _ABase_JVM_H
#define _ABase_JVM_H

#include <stddef.h>
#include <string.h>
#include <string>
#include "jni.h"
#include "AJniTool.h"
#include "ACritical.h"
#ifndef LOG
#define LOG
#	include <android/log.h>
#	define _TAG     	"ABase"
#	define LOG_D(...) __android_log_print(ANDROID_LOG_DEBUG, 	_TAG, __VA_ARGS__);
#	define LOG_I(...) __android_log_print(ANDROID_LOG_INFO, 	_TAG, __VA_ARGS__);
#	define LOG_W(...) __android_log_print(ANDROID_LOG_WARN,		_TAG, __VA_ARGS__);
#	define LOG_E(...) __android_log_print(ANDROID_LOG_ERROR,	_TAG, __VA_ARGS__);
#	define LOG_F(...) __android_log_print(ANDROID_LOG_FATAL,	_TAG, __VA_ARGS__);
#endif

#include "ABasePal.h"

class EXPORT_CLASS ABaseJVM
{
private:
    static ABaseJVM *m_instance;
    JavaVM    *m_jvm;
    jobject   m_obj;
    jobject   m_mainAtv;
    jobject   m_mainContext;
    jobject m_network_tool;
    jclass  m_network_tool_clazz;
    jclass m_cuploadtask_clazz;
    jclass m_security_store_clazz;
    jclass m_string_clazz;
    jclass m_tasksystem_clazz;
    char 	  *m_tombDir;
    
protected:
    ABaseJVM();
    
public:
    static ABaseJVM *GetInstance();
    JavaVM *GetJVM();
    void SetMainAtv(jobject atv);
    void SetMainContext(jobject context);
    void SetObj(jobject thiz);
    void SetCUploadTaskClass(jclass clazz);
    void SetSecurityStoreClass(jclass clazz);
    void SetStringClass(jclass clazz);
    void SetTaskSystemClass(jclass clazz);


    jclass GetCUploadTaskClass();
    jclass GetSecurityStoreClass();
    jclass GetStringClass();
    jclass GetTaskSytemClass();
    jobject GetObj();
    jobject GetMainAtv();
    jobject GetMainContext();
    //    void SetTombDir(char *tombDir);
    //	char *GetTombDir();
    bool Init(JavaVM *jvm);
public:
    static jstring StrToJstring(JNIEnv* env, const char* pStr);
    static std::string Jstring2Str(JNIEnv *env,jstring jstr);
    
    static jbyteArray StrToJbytearray(JNIEnv* env, const char* pStr, int len)
    {
        jbyteArray dst = env->NewByteArray(len);
        jbyte *dstMem = env->GetByteArrayElements(dst, 0);
        memcpy(dstMem, pStr, len);
        env->SetByteArrayRegion(dst, 0,len, dstMem);
        return dst;
    }
    
    
    static std::string Jbytearray2Str(JNIEnv* env, jbyteArray array)
    {
        char*   rtn   =   NULL;
        jsize alen  =   env->GetArrayLength(array);
        jbyte *ba   =   env->GetByteArrayElements(array, JNI_FALSE);
        if(alen > 0)
        {
            rtn   =   new char[alen + 1];
            memcpy(rtn,ba,alen);
            rtn[alen]=0;
        }
        env->ReleaseByteArrayElements(array,ba,0);
        env->DeleteLocalRef(array);
        std::string stemp;
        if(NULL != rtn)
        {
            stemp.assign(rtn, alen);
            delete []rtn;
            return   stemp;
        }
        else return "";
    }

};

class ABaseEnv
{
public:
    ABaseEnv();
    ~ABaseEnv();
    
    JNIEnv* GetEnv();
private:
    JNIEnv* m_env;
    JavaVM* m_jvm;
    bool m_attached;
};


#endif
#endif

