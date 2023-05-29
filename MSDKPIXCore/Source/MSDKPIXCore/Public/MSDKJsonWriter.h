/*!
 * @Module MSDK
 *
 * @Header  MSDKJsonWriter.h
 * @Author  developer
 * @Date 2018/4/3
 * @Abstract
 * struct 转为 json 的实现声明
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_JSON_WRITER_H
#define MSDK_JSON_WRITER_H


#include <sstream>
#include "MSDKDefine.h"
#include "MSDKMacros.h"
#include "MSDKCompatLayer.h"

NS_MSDK_BEGIN

#ifndef JSON_WRITER_DOCUMENT
#define JSON_WRITER_DOCUMENT void
#define JSON_WRITER_STRING_BUFFER void
#define JSON_WRITER_WITH_STRING_BUFFER void
#endif

typedef enum RapidJsonType
{
	kJsonNullType = 0,      //!< null
	kJsonFalseType = 1,     //!< false
	kJsonTrueType = 2,      //!< true
	kJsonObjectType = 3,    //!< object
	kJsonArrayType = 4,     //!< array
	kJsonStringType = 5,    //!< string
	kJsonNumberType = 6     //!< number
} RapidJsonType;

class MSDK_EXPORT MSDKJsonWriter
{
private:
	JSON_WRITER_STRING_BUFFER *buffer;
	JSON_WRITER_WITH_STRING_BUFFER *writer;
	bool isDebugLogOn;

public:
	MSDKJsonWriter();

	~MSDKJsonWriter();

	void arrayBegin();

	void arrayEnd();

	void objectBegin();

	void objectEnd();


	String GetJsonString();

	void setKey(const char *key); // openssl defined set_key macro ...

	MSDKJsonWriter &convert(const char *key, const char *val, int type = kJsonStringType);

	MSDKJsonWriter &convert(const char *key, const std::string &val, int type = kJsonStringType)
	{
		return convertPRV(key, val.c_str(), type);
	}

	MSDKJsonWriter &convertPRV(const char *key, const char *val, int type = kJsonStringType);

	MSDKJsonWriter &convert(const char *key, const String &val, int type = kJsonStringType);

	MSDKJsonWriter &convert(const char *key, bool val);

	MSDKJsonWriter &convert(const char *key, double val);

	MSDKJsonWriter &convert(const char *key, float val);

	MSDKJsonWriter &convert(const char *key, int val);

	MSDKJsonWriter &convert(const char *key, int64_t val);

	MSDKJsonWriter &convert(const char *key, const unsigned char *val);

	MSDKJsonWriter &convert(const char *key, MethodName val);

	void merge(std::string &json1, const std::string &json2); // json merge 操作，存在项目 key 情况，json2 会覆盖 json 1 的值

	template<class T, class U>
	T toString(U a)
	{
        return "";
        // 只有convert用到toString，convert没被调用 stream 使用有风险
//		std::stringstream ss;
//		T ret;
//		ss << a;
//		ss >> ret;
//		return ret;
	};


	template<typename T>
	MSDKJsonWriter &convert(const char *key, const std::vector<T> &data)
	{
		setKey(key);

		this->arrayBegin();
		for (size_t i = 0; i < data.size(); ++i)
		{
			this->convert("", data[i]);
		}
		this->arrayEnd();
		return *this;
	}

	template<typename T>
	MSDKJsonWriter &convert(const char *key, const Vector<T> &data)
	{
		setKey(key);
		this->arrayBegin();
		for (int i = 0; i < data.size(); ++i)
		{
			this->convert("", data[i]);
		}
		this->arrayEnd();
		return *this;
	}

	template<typename T>
	MSDKJsonWriter &convert(const char *key, const std::set<T> &data)
	{
		setKey(key);
		this->arrayBegin();
		for (typename std::set<T>::const_iterator it = data.begin(); it != data.end(); ++it)
		{
			this->convert("", *it);
		}
		this->arrayEnd();
		return *this;
	}

	template<typename T>
	void convert(const char *key, const std::map<std::string, T> &data)
	{
		setKey(key);
		this->objectBegin();
		for (typename std::map<std::string, T>::const_iterator iter = data.begin();
			iter != data.end(); ++iter)
		{
			this->convert(iter->first.c_str(), iter->second);
		}
		this->objectEnd();
	}

    // 没被使用到，但不能注视掉函数，当前是public文件
	template<typename KEY, typename T>
	void convert(const char *key, const std::map<KEY, T> &data)
	{
//		setKey(key);
//		this->objectBegin();
//		for (typename std::map<KEY, T>::const_iterator iter = data.begin();
//			iter != data.end(); ++iter)
//		{
//			std::string _k = toString<std::string>(iter->first);
//			this->convert(_k.c_str(), iter->second);
//		}
//		this->objectEnd();
	}

	template<typename T>
	void convert(const char *key, const T &data)
	{
		setKey(key);
		this->objectBegin();
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
#else
		data.struct2Json(*this, key);
#endif
		this->objectEnd();
	}

	void StartJsonConvert();

	void EndJsonConvert();
};
NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

using MSDKJsonWriter = MSDK::MSDKJsonWriter;
typedef enum RapidJsonType
{
    kJsonNullType = MSDK::kJsonNullType,      //!< null
    kJsonFalseType = MSDK::kJsonFalseType,     //!< false
    kJsonTrueType = MSDK::kJsonTrueType,      //!< true
    kJsonObjectType = MSDK::kJsonObjectType,    //!< object
    kJsonArrayType = MSDK::kJsonArrayType,     //!< array
    kJsonStringType = MSDK::kJsonStringType,    //!< string
    kJsonNumberType = MSDK::kJsonNumberType     //!< number
} RapidJsonType;

NS_MSDK_SPACE_NO_STL_END

#endif //MSDK_JSON_WRITER_H
