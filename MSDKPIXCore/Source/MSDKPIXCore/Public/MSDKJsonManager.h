/*!
 * @Module MSDK
 *
 * @Header  MSDKJsonManager.h
 * @Author  developer
 * @Date 2018/4/3
 * @Abstract
 * Json 和 struct 互转的接口声明
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef ANDROID_JSON_MANAGER_H
#define ANDROID_JSON_MANAGER_H

#include "MSDKMacros.h"
#include "MSDKJsonReader.h"
#include "MSDKJsonWriter.h"
#include "MSDKMacroExpand.h"

NS_MSDK_BEGIN
#ifndef JSON_MANAGER_DOCUMENT
#define JSON_MANAGER_DOCUMENT void
#endif

class MSDK_EXPORT MSDKJsonManager
{
public:
	/*!
	 *
	 * @param str  需要被解析的 Json 文件
	 * @param type Json 属性对应的 struct 结构体
	 * @return 默认返回 true
	 */
	template<typename TYPE>
	static bool LoadJson(const std::string &str, TYPE &type)
	{
		if (str.empty()) return false;
		MSDKJsonReader reader(str);
		if (reader)
		{
			reader.convert(type);
			return true;
		}
		else
		{
			return false;
		}
	}


	/*!
	 *
	 * @param type 填充数值的 struct 结构体
	 * @param root 需要解析的根节点字符串
	 * @return 返回 Json 字符串
	 */
	template<typename TYPE>
	static std::string ToJson(const TYPE &type, const std::string &root = "")
	{
		MSDKJsonWriter writer;
		writer.convert(root.c_str(), type);
		return std::string(writer.GetJsonString().c_str());
	}

private:
	JSON_MANAGER_DOCUMENT *mDocument;

public:
	MSDKJsonManager(std::string json = "");

	~MSDKJsonManager();

	/**
	 * @param type (5 == Type::kStringType)
	 */
	void PutIfAbsent(const char *key, const char *val, int type = 5);

	/**
	 * @param type (5 == Type::kStringType)
	 */
	void PutIfAbsent(const char *key, const std::string &val, int type = 5);

	/**
 * @param type (5 == Type::kStringType)
 */
	void PutIfAbsent(const char *key, const String &val, int type = 5);

	//如果不存在就插入，如果存在就修改
	void PutIfAbsent(const char *key, const bool val);

	void PutIfAbsent(const char *key, const double val);

	void PutIfAbsent(const char *key, const float val);

	void PutIfAbsent(const char *key, const int val);

	void PutIfAbsent(const char *key, const int64_t value);

	operator bool() const;

	operator std::string() const;
};
NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

using MSDKJsonManager = MSDK::MSDKJsonManager;

NS_MSDK_SPACE_NO_STL_END

#endif //ANDROID_JSON_MANAGER_H
