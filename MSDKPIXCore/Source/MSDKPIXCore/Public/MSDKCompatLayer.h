/*!
 * @Module MSDK
 *
 * @Header  MSDKCompatLayer.h
 * @Author  developer
 * @Date 2018/6/20
 * @Abstract
 * 解决跨 STL 运行库导致的兼容问题声明
 * 更多 NDK 运行时信息查看：https://developer.android.com/ndk/guides/cpp-support?hl=zh-cn
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_COMPAT_LAYER_H
#define MSDK_COMPAT_LAYER_H

#include <sstream>
#include "MSDKMacros.h"
#include "MSDKMacroExpand.h"

#if MSDK_ENGINE_UE4_PLATFORM_WINDOWS
#define strncpy(deestination,source,sourceLen) \
    do { \
        strncpy_s(deestination, sourceLen+1, source, sourceLen); \
    } while (0)
#define strncat(deestination,source,sourceLen) \
    do {\
        strncat_s(deestination, sourceLen+1, source, sourceLen); \
    } while (0)
#endif



NS_MSDK_BEGIN


		class String
		{
		private:
			char *data;
			unsigned long len;
		public:
			String() : len(0)
			{
				data = SAFE_MALLOC(1, char);
				data[0] = '\0';
			}

			String(const std::string &str)
			{
				len = str.size();
				data = SAFE_MALLOC(len + 1, char);
				strncpy(data, str.c_str(), len);
				data[len] = '\0';
			}

			String(const char *strPtr)
			{
				if (strPtr == NULL)
				{
					len = 0;
					data = SAFE_MALLOC(1, char);
					data[0] = '\0';
					return;
				}

				len = (unsigned long)strlen(strPtr);
#if MSDK_PLATFORM_WINDOWS
				char temp_buff[10] = { 0 };
		_snprintf_s(temp_buff, sizeof(temp_buff), sizeof(temp_buff), "%ld", len);
#endif
				data = SAFE_MALLOC(len + 1, char);
				strncpy(data, strPtr, len);
				data[len] = '\0';
			}

			String(const String &str)
			{
				len = (unsigned int)str.size();
				data = SAFE_MALLOC(len + 1, char);
				strncpy(data, str.c_str(), len);
				data[len] = '\0';
			}

			// 析构函数
			~String()
			{
				SAFE_FREE(data);
				len = 0;
			}

			// 重载+
			String operator+(const String &str) const
			{
				String newStr;
				SAFE_FREE(newStr.data);
				newStr.len = len + (unsigned int)str.size();
				newStr.data = SAFE_MALLOC(newStr.len + 1, char);
				strncpy(newStr.data, data, len);
				strncat(newStr.data, str.data, str.length());
				newStr.data[newStr.len] = '\0';

				return newStr;
			}

			// 重载=
			String &operator=(const String &str)
			{
				if (this == &str)
				{
					return *this;
				}

				SAFE_FREE(data);
				len = str.len;
				data = SAFE_MALLOC(len + 1, char);
				strncpy(data, str.c_str(), len);
				data[len] = '\0';

				return *this;
			}

			// 重载=
			String &operator=(const char *strPtr)
			{
				if (strPtr == NULL)
				{
					len = 0;
					data = SAFE_MALLOC(1, char);
					data[0] = '\0';
					return *this;
				}
				SAFE_FREE(data);
				len = (unsigned long)strlen(strPtr);
#if MSDK_PLATFORM_WINDOWS
				char temp_buff[10] = { 0 };
		_snprintf_s(temp_buff, sizeof(temp_buff), sizeof(temp_buff), "%ld", len);
#endif
				data = SAFE_MALLOC(len + 1, char);
				strncpy(data, strPtr, len);
				data[len] = '\0';

				return *this;
			}

			// 重载=
			String &operator=(const std::string &str)
			{
				SAFE_FREE(data);
				len = str.length();
				data = SAFE_MALLOC(len + 1, char);
				strncpy(data, str.c_str(), len);
				data[len] = '\0';

				return *this;
			}

			// 重载+=
			String &operator+=(const String &str)
			{
				len += str.len;
				char *new_data = SAFE_MALLOC(len + 1, char);
				strncpy(new_data, data, len);
				strncat(new_data, str.data, str.size());
				SAFE_FREE(data);
				data = new_data;
				data[len] = '\0';

				return *this;
			}

			// 重载==
			inline bool operator==(const String &str) const
			{
				if (len != str.len)
				{
					return false;
				}
				return strcmp(data, str.data) == 0;
			}

			// 获取长度
			inline size_t size() const
			{
				return len;
			}

			inline size_t length() const
			{
				return len;
			}

			const std::string toString() const
			{
				if (data)
				{
					return data;
				}

				return "";
			}

			operator std::string() const {
				return toString();
			}

			bool empty() const
			{
				return size() <= 0;
			}

			// 获取C字符串
			inline const char *c_str() const
			{
				return data;
			}

		};

		class KVPair
		{
		public:
			String key;
			String value;

		AutoParser("", O(key, value));

		};

// 重新定义vector
		template<typename T, unsigned int SPARE_CAPACITY = 16>
		class Vector
		{
		public:
			//声明默认构造函数，是为了防止 windows 自动生成默认构造函数
			Vector() : vectorSize(0), vectorCapacity((unsigned int)SPARE_CAPACITY), objects(NULL)
			{
				objects = SAFE_MALLOC(SPARE_CAPACITY, T);
				for (unsigned int k = 0; k < vectorCapacity; k++)
				{
                    T t = objects[k];
                    objects[k] = t;
				}
			}
			//将构造函数声明为explicit ,是为了抑制由构造函数定义的隐式转换
			explicit Vector(unsigned long initSize) : vectorSize(0), vectorCapacity(
					(unsigned int)initSize + SPARE_CAPACITY), objects(NULL)
			{
				objects = SAFE_MALLOC(initSize + SPARE_CAPACITY, T);

			}

			Vector(const Vector &rhs) : objects(NULL)
			{
				vectorSize = rhs.vectorSize;
				vectorCapacity = rhs.vectorCapacity;

				objects = SAFE_MALLOC(vectorCapacity, T);
				for (unsigned int k = 0; k < vectorSize; k++)
				{
					objects[k] = rhs.objects[k];
				}
			}

			~Vector()
			{
				for (unsigned int i = 0; i < vectorSize; i++)
				{
					objects[i].~T();
				}
				SAFE_FREE(objects);
			}

			const Vector &operator=(const Vector &rhs)
			{
				if (this != &rhs)
				{
					for (unsigned int i = 0; i < vectorSize; i++)
					{
						objects[i].~T();
					}
					SAFE_FREE(objects);
					vectorSize = rhs.vectorSize;
					vectorCapacity = rhs.vectorCapacity;

					objects = SAFE_MALLOC(vectorCapacity, T);
					for (unsigned int k = 0; k < vectorSize; k++)
					{
						objects[k] = rhs.objects[k];
					}
				}

				return *this;
			}

			const Vector &operator=(const typename std::vector<T> &rhs)
			{
				if (!rhs.empty())
				{
					for (unsigned int i = 0; i < vectorSize; i++)
					{
						objects[i].~T();
					}
					SAFE_FREE(objects);
					vectorSize = rhs.size();
					vectorCapacity = rhs.capacity();

					objects = SAFE_MALLOC(vectorCapacity, T);
					for (unsigned int k = 0; k < vectorSize; k++)
					{
						objects[k] = rhs[k];
					}
				}

				return *this;
			}

			// 如果index错误，直接返回0的数据
			T &operator[](int index)
			{
				if (index < 0 || (unsigned int)index >= vectorSize)
				{
					return objects[0];
				}
				return objects[index];
			}

			const T &operator[](int index) const
			{
				return objects[index];
			}

			//检测是否需要扩容
			void reserve()
			{
				reserve(vectorSize);
			}

			// 扩容数据
			void reserve(unsigned int newSize)
			{
				if (vectorCapacity > newSize)
				{
					return;
				}
				unsigned int newCapacity = newSize * 2 + 1;
				T *oldArr = objects;

				objects = SAFE_MALLOC(newCapacity, T);
				for (unsigned int k = 0; k < vectorSize; k++)
				{
					objects[k] = oldArr[k];
				}
				for (unsigned int k = vectorSize; k < newSize; k++)
				{
                    T t = objects[k];
                    objects[k] = t;
				}
				vectorCapacity = newCapacity;
				for (unsigned int i = 0; i < vectorSize; i++)
				{
					oldArr[i].~T();
				}
				SAFE_FREE(oldArr);  // 删除原来的数据
			}

			unsigned int size() const
			{
				return vectorSize;
			}

			unsigned int capacity() const
			{
				return vectorCapacity;
			}

			bool empty() const
			{
				return vectorSize == 0;
			}

			bool find(const T &t) const
			{
				for (unsigned int i = 0; i < vectorSize; i++)
				{
					if (objects[i] == t)
					{
						return true;
					}
				}

				return false;
			}

			void resize(unsigned int newSize)
			{
				reserve(newSize);
				vectorSize = newSize;
			}

			void push_back(const T &obj)
			{
				reserve();  // 检测容器大小
				objects[vectorSize++] = obj;
			}

			void pop_back()
			{
				objects[vectorSize].~T();
				vectorSize--;
			}

			const T &back() const
			{
				return objects[vectorSize - 1];
			}

			//MARK: 这里的返回值不应带const的，但是删掉const会改变abi，慎重处理
			const T *begin()
			{
				return &objects[0];
			}

			T *end()
			{
				return &objects[vectorSize];
			}

			bool clear()
			{
				for (unsigned int i = 0; i < vectorSize; i++)
				{
					objects[i].~T();
				}
				vectorSize = 0;
				SAFE_FREE(objects);
				objects = SAFE_MALLOC(SPARE_CAPACITY, T);
				vectorCapacity = SPARE_CAPACITY;

				return true;
			}

			const T *begin() const
			{
				return &objects[0];
			}
			const T *end() const
			{
				return &objects[vectorSize];
			}

			std::string toString()
			{
				// 该函数当前未被使用到
				return "";
//		std::stringstream out;
//		out << "Vector length:" << size() << ",capacity：" << capacity() << std::endl;
//		for (int i = 0; i < vectorSize; i++)
//		{
//			out << "objects[" << i << "]:" << objects[i] << std::endl;
//		}
//		return out.str();
			}

			typedef const T *const_iterator;
			typedef T *iterator;
		private:
			unsigned int vectorSize;
			unsigned int vectorCapacity;
			T *objects;
		};

		class MSDK_EXPORT MSDKRetAdapter
		{
		public:

			void convert(bool &val, const bool &innerVal);

			void convert(double &val, const double &innerVal);

			void convert(float &val, const float &innerVal);

			void convert(int &val, const int &innerVal);

			//    void convert(long &val, const long &innerVal);

			void convert(int64_t &val, const int64_t &innerVal);

			void convert(std::string &val, const String &innerVal)
			{
				val = innerVal.c_str();
			}

			void convert(String &innerVal, const std::string &val)
			{
				innerVal = val;
			}

			void convert(String &innerVal, const String &val) {
				innerVal = val;
			}

			void convert(Vector<KVPair> &innerVal, const Vector<KVPair> &val) {
				innerVal.clear();
				Vector<KVPair>::const_iterator it;
				for (it = val.begin(); it != val.end(); ++it) {
					innerVal.push_back(*it);
				}
			}

			void convert(std::map<std::string, std::string> &val, const Vector<KVPair> &innerVal)
			{
				for (unsigned int i = 0; i < innerVal.size(); i++)
				{
					val.insert(std::make_pair(innerVal[i].key.c_str(), innerVal[i].value.c_str()));
				}
			}

			template<typename OutTypeRet, typename InnerTypeRet>
			void convert(std::vector<OutTypeRet> &val, const Vector<InnerTypeRet> &innerVal)
			{
				size_t s = innerVal.size();
				val.resize(s);
				for (unsigned int i = 0; i < s; ++i)
				{
					convert(val[i], innerVal[i]);        // operator[](size_t)
				}
			}

			template<typename OutTypeRet, typename InnerTypeRet>
			void convert(OutTypeRet &outTypeRet, const InnerTypeRet &innerTypeRet)
			{
#if MSDK_PLATFORM_WINDOWS || MSDK_ENGINE_UE4_SIMULATE_LOGIN
				//outTypeRet.innerRetConvert(*this, innerTypeRet);
#else
				outTypeRet.innerRetConvert(*this, innerTypeRet);
#endif
			};
		};

		class MSDK_EXPORT MSDKCompatManager
		{
		public:
			template<typename OutTypeRet, typename InnerTypeRet>
			static bool compatConvert(OutTypeRet &outTypeRet, const InnerTypeRet &innerTypeRet)
			{
				MSDKRetAdapter ret;
				ret.convert(outTypeRet, innerTypeRet);
				return true;
			}
		};

NS_MSDK_END

NS_MSDK_SPACE_NO_STL_BEGIN

			typedef MSDK::MSDKRetAdapter MSDKRetAdapter;
			typedef MSDK::MSDKCompatManager MSDKCompatManager;

			using String = MSDK::String;
			using KVPair = MSDK::KVPair;
			using MSDKRetAdapter = MSDK::MSDKRetAdapter;
			using MSDKCompatManager = MSDK::MSDKCompatManager;

			template<typename T, unsigned int SPARE_CAPACITY = 16>
			using Vector = MSDK::Vector<T, SPARE_CAPACITY>;

			class MSDK_EXPORT StringMap
			{
			public:

				StringMap();
				StringMap(const StringMap &rhs);

				MSDK_EXPORT_UE StringMap(const std::map<std::string, std::string> &map);

				String &operator[](String key);

				const String &operator[](String key) const;

				operator std::map<std::string, std::string>() const;

				operator Vector<KVPair>() const;

				unsigned int size() const;

				void insert(KVPair pair);

				void insert(std::pair<std::string, std::string> pair);

				KVPair *begin();

				KVPair *end();

				const KVPair *begin() const;

				const KVPair *end() const;

				typedef const KVPair *const_iterator;
				typedef KVPair *iterator;

			AutoParser("", O(table));
			private:
				Vector<KVPair> table;
			};

NS_MSDK_SPACE_NO_STL_END

#endif //MSDK_COMPAT_LAYER_H
