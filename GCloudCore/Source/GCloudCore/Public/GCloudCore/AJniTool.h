/*
 * JniTool.h
 *
 *  Created on: 2011-10-20
 *      Author: vforkkcai
 */
#ifndef ABase_JNITOOL_H_
#define ABase_JNITOOL_H_
#if defined(ANDROID)

#include <jni.h>
#include <string>


namespace ABase
{
    
    class JniTool
    {
    public:
        static bool ConvertJByteArrayToString(JNIEnv * aEnv, jbyteArray aArray, std::string& rBuf)
        {
            if (aEnv)
            {
                jbyte *jpbuf;
                jsize bufLen;
                jpbuf = aEnv->GetByteArrayElements(aArray, 0);
                bufLen = aEnv->GetArrayLength(aArray);
                
                if (jpbuf)
                {
                    rBuf.clear();
                    rBuf.assign((char*) jpbuf, bufLen);
                    
                    aEnv->ReleaseByteArrayElements(aArray, jpbuf, 0);
                }
                
                return true;
            }
            return false;
        }
        
        static bool ConvertJStringToString(JNIEnv * aEnv, jstring astring, std::string& rstring)
        {
            if (aEnv && astring)
            {
                jchar* lpszString = (jchar*) aEnv->GetStringUTFChars(astring, 0);
                
                if (lpszString)
                {
                    rstring.assign((char*) lpszString);
                    aEnv->ReleaseStringUTFChars(astring, (const char*) lpszString);
                    return true;
                }
            }
            return false;
        }
        
        static jbyteArray GetJByteArray(JNIEnv * aEnv, const std::string& aString)
        {
            if (aEnv)
            {
                jbyteArray jarray = aEnv->NewByteArray(aString.size());
                aEnv->SetByteArrayRegion(jarray, 0, aString.size(), (const jbyte*) aString.c_str());
                
                return jarray;
            }
            return 0;
        }
        
        static jobject NewIntegerObject(JNIEnv* pEnv, int value)
        {
            jclass cls;
            cls = pEnv->FindClass("java/lang/Integer");
            jmethodID md = pEnv->GetMethodID(cls, "<init>", "(I)V");
            jobject jobj = pEnv->NewObject(cls, md, value);
            pEnv->DeleteLocalRef(cls);
            return jobj;
        }
        
        static bool ConvertIntegerToJInt(JNIEnv* pEnv, jobject jobjThis, jint& rValue)
        {
            if (jobjThis)
            {
                jclass jcls = pEnv->GetObjectClass(jobjThis);
                if (jcls)
                {
                    jmethodID jmid = pEnv->GetMethodID(jcls, "intValue", "()I");
                    pEnv->DeleteLocalRef(jcls);
                    if (jmid)
                    {
                        rValue = pEnv->CallIntMethod(jobjThis, jmid);
                        return true;
                    }
                }
            }
            return false;
        }
        
        static jobject GetMapValue(JNIEnv* pEnv, jobject jobjMap, const char* pchKey)
        {
            if (jobjMap)
            {
                jstring jstrKey = pEnv->NewStringUTF(pchKey);
                jclass jclassMap = pEnv->GetObjectClass(jobjMap);
                if (jobjMap && jstrKey)
                {
                    jmethodID jmidMapGet = pEnv->GetMethodID(jclassMap, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
                    pEnv->DeleteLocalRef(jclassMap);
                    if (jmidMapGet)
                    {
                        jobject ret = pEnv->CallObjectMethod(jobjMap, jmidMapGet, jstrKey);
                        pEnv->DeleteLocalRef(jstrKey);
                        return ret;
                    }
                }
            }
            return 0;
        }



        static jstring ConvertStringToJString(JNIEnv* env, const char* pStr)
        {
            if (pStr == NULL)
            {
                pStr = "";
            }
            int        strLen    = strlen((char *)pStr);
            jclass     jstrObj   = env->FindClass("java/lang/String");
            jmethodID  methodId  = env->GetMethodID(jstrObj, "<init>", "([BLjava/lang/String;)V");
            jbyteArray byteArray = env->NewByteArray(strLen);
            jstring    encode    = env->NewStringUTF("utf-8");

            env->SetByteArrayRegion( byteArray, 0, strLen, (jbyte*)pStr);

            jstring ret = (jstring)env->NewObject(jstrObj, methodId, byteArray, encode);

            env->DeleteLocalRef(jstrObj);
            env->DeleteLocalRef(byteArray);
            env->DeleteLocalRef(encode);

            return ret;
        }
    };
    
}
#endif /* JNITOOL_H_ */

#endif


