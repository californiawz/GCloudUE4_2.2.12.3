/*!
 * @Module MSDK
 *
 * @Header  MSDKJsonReader.h
 * @Author  developer
 * @Date 2018/4/3
 * @Abstract
 * json 转成 struct 的实现声明
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_JSON_READER_H
#define MSDK_JSON_READER_H

#include <sstream>
#include "MSDKMacros.h"
#include "MSDKCompatLayer.h"

NS_MSDK_BEGIN
#ifndef JSON_READER_DOCUMENT
#define JSON_READER_DOCUMENT void
#define JSON_READER_VALUE void
#define JSON_READER_ITERATOR void
#endif

class MSDK_EXPORT MSDKJsonReader
{
private:
    JSON_READER_DOCUMENT *document;
    const JSON_READER_VALUE *value;
    mutable JSON_READER_ITERATOR *iterator;
    const MSDKJsonReader *mParent;
    const char *mKey;
    int mIndex;
    bool isDebugLogOn;

    void init(const char* jsonStr);

public: // convert

    MSDKJsonReader(const std::string &str)
    {
        init(str.c_str());
    }

    MSDKJsonReader(const JSON_READER_VALUE *val, const MSDKJsonReader *parent, const char *key);

    MSDKJsonReader(const JSON_READER_VALUE *val, const MSDKJsonReader *parent, int index);

    ~MSDKJsonReader();

    void convert(char const *&val);

    void convert(std::string &val)
    {
        String tmp;
        convert(tmp);
        val = std::string(tmp.c_str());
    }

    void convert(String &val);

    void convert(bool &val);

    void convert(double &val);

    void convert(float &val);

    void convert(int &val);

    void convert(int64_t &value);

    void convert(unsigned char const *&val);

    size_t size();

    MSDKJsonReader operator[](const char *key);

    MSDKJsonReader operator[](size_t index);

    MSDKJsonReader begin();

    MSDKJsonReader next();

    operator bool() const;

    template<class T, class U>
    T toString(U a) const
    {
        //只有convert用到toString，convert没被调用 stream 使用有风险
        return "";
//        std::stringstream ss;
//        T ret;
//        ss << a;
//        ss >> ret;
//        return ret;
    };


    const std::string key() const
    {
        if (mKey)
        {
            return mKey;
        }
        else
        {
            char tempChars[32] = {0};
            int chars_written = snprintf(tempChars, sizeof(tempChars), "%d", mIndex);
            return std::string(tempChars, chars_written);
        }
    }

    template<typename TYPE>
    void convert(std::vector<TYPE> &val)
    {
        size_t s = this->size();
        val.resize(s);
        for (size_t i = 0; i < s; ++i)
        {
            (*this)[i].convert(val[i]);         // operator[](size_t)
        }
    }

    template<typename TYPE>
    void convert(Vector<TYPE> &val)
    {
        int s = (int) this->size();
        val.resize(s);
        for (int i = 0; i < s; ++i)
        {
            (*this)[i].convert(val[i]);         // operator[](size_t)
        }
    }

    template<typename TYPE>
    void convert(std::map<std::string, TYPE> &val)
    {
        for (MSDKJsonReader d = this->begin(); d; d = d.next())
        {
            TYPE _t;
            d.convert(_t);
            val[d.key()] = _t;
        }
    }

    // 不能注视掉函数，当前是public文件
    template<typename KEY_TYPE, typename TYPE>
    void convert(std::map<KEY_TYPE, TYPE> &val)
    {
//        for (MSDKJsonReader d = this->begin(); d; d = d.next())
//        {
//            TYPE _t;
//            d.convert(_t);
//
//            std::string key = d.key();
//            KEY_TYPE _k = toString<KEY_TYPE, std::string>(key);
//            val[_k] = _t;
//        }
    }

	template<typename TYPE>
	void convert(TYPE &val)
	{
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
#else
		val.json2Struct(*this);
#endif // MSDK_PLATFORM_WINDOWS
	}
};
NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

using MSDKJsonReader = MSDK::MSDKJsonReader;

NS_MSDK_SPACE_NO_STL_END

#endif //MSDK_JSON_READER_H
