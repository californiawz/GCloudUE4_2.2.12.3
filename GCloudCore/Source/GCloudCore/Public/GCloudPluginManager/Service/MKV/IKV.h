//
// Created by junhui on 2022/4/6.
//

#ifndef ANDROID_IKV_H
#define ANDROID_IKV_H

#include "GCloudPluginManager/IPluginService.h"
#include "GCloudPluginManager/IPluginManager.h"

GCLOUD_PLUGIN_NAMESPACE

class IKV: public GCloud::Plugin::IPluginService{
    /**
     * multi process kv storage service.
     * this ability is provided by MSDK and integrates into gcloud by plug-in form
     * the plugin name is "KV", and the service name is "KV" too. some existed inner feature:
     *  1. Multi-process support
     *  2. Automatic encryption
     *  3. some common C++ APIs
     *
     * some important attentions:
     *  1. the KV plugin should be initialized before any use
     *  2. depends MMKV, which means the third party MMKV should be packaged too.
     *  3. within multi-process, init KV plugin first always.
     */
public:
    /**
     * check a key from kv service whether contains a key or not
     * @param key, key of value, must a valid string, end with '0'
     * @return true, if contains; false, if not contains
     */
    virtual bool Contains(const char* key) = 0;
    /**
     * for string type, the key and value must end with '0'
     * @param key key for the value
     * @param value value of the key
     * @return true, if the invoke is success, thus, the key and value has saved success
     *      otherwise, false will be returned.
     */
    virtual bool PutString(const char* key, const char* value) = 0;
    /**
     * for string type, get a string with the key
     * @param key key of the value
     * @return the length of value
     *
     *  attention, if the key is not exist, the return is -1,
     *   otherwise return the real length of value
     */
    virtual int GetString(const char* key, char* value, int len) = 0;
    /**
     * save int value for a key
     * @param key
     * @param value
     * @return true, if the invoke is success, otherwise false
     */
    virtual bool PutInt(const char* key, int value) = 0;
    /**
     * get a int value by a key. if the key is not exist, the default value will be return.
     * @param key the key for the value
     * @param defaultValue default value for the key is not exist
     * @return a int value
     */
    virtual int GetInt(const char* key, int defaultValue = 0) = 0;
    /**
     * save long value for a key
     * @param key
     * @param value
     * @return true if success, otherwise false
     */
    virtual bool PutLong(const char* key, long value) = 0;
    /**
     * get a long value for a key, if the key is not exist, default value will be return
     * @param key
     * @param defaultValue
     * @return the value for the key
     */
    virtual long GetLong(const char* key, long defaultValue = 0) = 0;
    /**
     * save a float value for a key
     * @param key, the key of value
     * @param value, the value of the key
     * @return true, if the invoke is success, otherwise false
     */
    virtual bool PutFloat(const char* key, float value) = 0;
    /**
     * get float value for a key. if the key is not exist, the default value will be return.
     * @param key
     * @param defaultValue
     * @return a float value of the key or default value.
     */
    virtual float GetFloat(const char* key, float defaultValue = 0.0) = 0;
    /**
     * save a boolean value for a key
     * @param key
     * @param value
     * @return true, if the invoke is success, otherwise false
     */
    virtual bool PutBoolean(const char* key, bool value) = 0;
    /**
     * get boolean value for a key. if the key is not exist, the default value will be return.
     * @param key
     * @param defaultValue
     * @return a boolean value of the key or default value.
     */
    virtual bool GetBoolean(const char* key, bool defaultValue = false) = 0;
};

GCLOUD_PLUGIN_NAMESPACE_END

#endif //ANDROID_IKV_H
