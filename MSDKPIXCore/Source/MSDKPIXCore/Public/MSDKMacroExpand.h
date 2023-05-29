/*!
 * @Module MSDK
 *
 * @Header  MSDKMacroExpand.h
 * @Author  developer
 * @Date 2018/4/2
 * @Abstract
 * 宏展开声明,将 struct 结构体里面的数据展开成自动解析 json 和 自动解析 jni 的函数
 *
 * @Copyright
 * Copyright © company. All rights reserved.
 */

#ifndef MSDK_MACRO_EXPAND_H
#define MSDK_MACRO_EXPAND_H

#include "MSDKMacros.h"

#ifdef ANDROID
#include "jni.h"
#endif

NS_MSDK_BEGIN

#ifdef ANDROID //Android 才需要 JNI 到 struct 的互转
// Java 到 struct 的代码模板
#define JNI_2_STRUCT_FUNC_BEGIN(clazzName)                                  \
public:                                                                     \
    template<typename JObject>                                              \
    void jni2Struct(JObject& obj, jobject src, char const* cn = clazzName) {

#define CONVERTER_JNI_2_STRUCT_OPTIONAL(M)                                 \
             obj.convert(#M, M, src, cn);

// 设置别名
#define CONVERTER_JNI_2_STRUCT_ALIAS(M, A_NAME)    CONVERTER_JNI_2_STRUCT_OPTIONAL(M)
			//obj.convert(A_NAME,M, src, cn);

// call father jni2Struct add by yuanchengsu
#define CONVERTER_JNI_2_STRUCT_BASE(M)  M::jni2Struct(obj,src,cn);

#define JNI_2_STRUCT_FUNC_END() }


// struct 到 JNI 的代码模板
#define STRUCT_2_JNI_FUNC_BEGIN(clazzName)                                  \
    template <class CLASS>                                                  \
    void struct2JNI(CLASS& obj, const char *root, char const* cn = clazzName) const {                   \

#define CONVERTER_STRUCT_2_JNI_OPTIONAL(M)                                  \
        obj.convert(#M, M, cn);

#define CONVERTER_STRUCT_2_JNI_ALIAS(M, A_NAME)  CONVERTER_STRUCT_2_JNI_OPTIONAL(M)
		//obj.convert(A_NAME, M, cn);

//call father struct2JNI add by yuanchengsu
#define CONVERTER_STRUCT_2_JNI_BASE(M)  M::struct2JNI(obj,root,cn);

#define STRUCT_2_JNI_FUNC_END() }
#endif

	// json 到 struct 的代码模板
#define JSON_2_STRUCT_FUNC_BEGIN()                                          \
public:                                                                     \
    template<typename Doc>                                                  \
    void json2Struct(Doc& obj) {

#define CONVERTER_JSON_2_STRUCT_OPTIONAL(M)                                 \
             obj[#M].convert(M);

// 设置别名
#define CONVERTER_JSON_2_STRUCT_ALIAS(M, A_NAME)                            \
            obj[A_NAME].convert(M);

// call father json2Struct by yuanchengsu
#define CONVERTER_JSON_2_STRUCT_BASE(M) M::json2Struct(obj);

// struct 到 json 的代码模板
#define STRUCT_2_JSON_FUNC_BEGIN()                                          \
    template <class CLASS>                                                  \
    void struct2Json(CLASS& obj, const char *root) const {

#define CONVERTER_STRUCT_2_JSON_OPTIONAL(M)                                 \
             obj.convert(#M,M);

// 设置别名
#define CONVERTER_STRUCT_2_JSON_ALIAS(M, A_NAME)                            \
            obj.convert(A_NAME,M);                                          \

// call father struct2Json by yuanchengsu
#define CONVERTER_STRUCT_2_JSON_BASE(M) M::struct2Json(obj,root);

#define STRUCT_AND_JSON_FUNC_END() }


	// 兼容层转换代码
#define RET_AND_INNER_FUNC_BEGIN()                                          \
    template <class Doc, class TypeRet>                                     \
    void innerRetConvert(Doc& doc, const TypeRet &typeRet) {

#define CONVERTER_RET_AND_INNER_OPTIONAL(M)                                 \
             doc.convert(M, typeRet.M);

	// 设置别名
#define CONVERTER_RET_AND_INNER_ALIAS(M, A_NAME) CONVERTER_RET_AND_INNER_OPTIONAL(M)

//call father innerRetConvert by yuanchengsu
#define CONVERTER_RET_AND_INNER_BASE(M) M::innerRetConvert(doc,typeRet);

#define RET_AND_INNER_FUNC_END() }


#define ARG_SEQ                                                             \
         _29,_28,_27,_26,_25,_24,_23,_22,_21,_20,                           \
         _19,_18,_17,_16,_15,_14,_13,_12,_11,_10,                           \
          _9, _8, _7, _6, _5, _4, _3, _2, _1

#define ARG_N(ACTION, \
         _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
        _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
        _21, _22, _23, _24, _25, _26, _27, _28, _29, NUMBER, ...) ACTION##NUMBER

#define WRAP_LEVEL_ONE(ACT, LIST, ...) ARG_N(LEVEL_ONE, __VA_ARGS__, LIST)(ACT, __VA_ARGS__)
#define WRAP_LEVEL_TWO(ACT, LIST, ...) ARG_N(LEVEL_TWO, __VA_ARGS__, LIST)(ACT, __VA_ARGS__)

#define LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_##ACT##M
#define LEVEL_ONE_1(ACT, M)        LEVEL_ONE_DEF(ACT, M)
#define LEVEL_ONE_2(ACT, M, ...)    LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_1(ACT, __VA_ARGS__)
#define LEVEL_ONE_3(ACT, M, ...)    LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_2(ACT, __VA_ARGS__)
#define LEVEL_ONE_4(ACT, M, ...)    LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_3(ACT, __VA_ARGS__)
#define LEVEL_ONE_5(ACT, M, ...)    LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_4(ACT, __VA_ARGS__)
#define LEVEL_ONE_6(ACT, M, ...)    LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_5(ACT, __VA_ARGS__)
#define LEVEL_ONE_7(ACT, M, ...)    LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_6(ACT, __VA_ARGS__)
#define LEVEL_ONE_8(ACT, M, ...)    LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_7(ACT, __VA_ARGS__)
#define LEVEL_ONE_9(ACT, M, ...)    LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_8(ACT, __VA_ARGS__)
#define LEVEL_ONE_10(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_9(ACT, __VA_ARGS__)
#define LEVEL_ONE_11(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_10(ACT, __VA_ARGS__)
#define LEVEL_ONE_12(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_11(ACT, __VA_ARGS__)
#define LEVEL_ONE_13(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_12(ACT, __VA_ARGS__)
#define LEVEL_ONE_14(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_13(ACT, __VA_ARGS__)
#define LEVEL_ONE_15(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_14(ACT, __VA_ARGS__)
#define LEVEL_ONE_16(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_15(ACT, __VA_ARGS__)
#define LEVEL_ONE_17(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_16(ACT, __VA_ARGS__)
#define LEVEL_ONE_18(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_17(ACT, __VA_ARGS__)
#define LEVEL_ONE_19(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_18(ACT, __VA_ARGS__)
#define LEVEL_ONE_20(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_19(ACT, __VA_ARGS__)
#define LEVEL_ONE_21(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_20(ACT, __VA_ARGS__)
#define LEVEL_ONE_22(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_21(ACT, __VA_ARGS__)
#define LEVEL_ONE_23(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_22(ACT, __VA_ARGS__)
#define LEVEL_ONE_24(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_23(ACT, __VA_ARGS__)
#define LEVEL_ONE_25(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_24(ACT, __VA_ARGS__)
#define LEVEL_ONE_26(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_25(ACT, __VA_ARGS__)
#define LEVEL_ONE_27(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_26(ACT, __VA_ARGS__)
#define LEVEL_ONE_28(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_27(ACT, __VA_ARGS__)
#define LEVEL_ONE_29(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_28(ACT, __VA_ARGS__)
#define LEVEL_ONE_30(ACT, M, ...)   LEVEL_ONE_DEF(ACT, M)      LEVEL_ONE_29(ACT, __VA_ARGS__)

#define LEVEL_TWO_DEF(ACT, M)     CONVERTER_##ACT(M)
#define LEVEL_TWO_1(ACT, M)       LEVEL_TWO_DEF(ACT, M)
#define LEVEL_TWO_2(ACT, M, ...)   LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_1(ACT, __VA_ARGS__)
#define LEVEL_TWO_3(ACT, M, ...)   LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_2(ACT, __VA_ARGS__)
#define LEVEL_TWO_4(ACT, M, ...)   LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_3(ACT, __VA_ARGS__)
#define LEVEL_TWO_5(ACT, M, ...)   LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_4(ACT, __VA_ARGS__)
#define LEVEL_TWO_6(ACT, M, ...)   LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_5(ACT, __VA_ARGS__)
#define LEVEL_TWO_7(ACT, M, ...)   LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_6(ACT, __VA_ARGS__)
#define LEVEL_TWO_8(ACT, M, ...)   LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_7(ACT, __VA_ARGS__)
#define LEVEL_TWO_9(ACT, M, ...)   LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_8(ACT, __VA_ARGS__)
#define LEVEL_TWO_10(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_9(ACT, __VA_ARGS__)
#define LEVEL_TWO_11(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_10(ACT, __VA_ARGS__)
#define LEVEL_TWO_12(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_11(ACT, __VA_ARGS__)
#define LEVEL_TWO_13(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_12(ACT, __VA_ARGS__)
#define LEVEL_TWO_14(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_13(ACT, __VA_ARGS__)
#define LEVEL_TWO_15(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_14(ACT, __VA_ARGS__)
#define LEVEL_TWO_16(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_15(ACT, __VA_ARGS__)
#define LEVEL_TWO_17(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_16(ACT, __VA_ARGS__)
#define LEVEL_TWO_18(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_17(ACT, __VA_ARGS__)
#define LEVEL_TWO_19(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_18(ACT, __VA_ARGS__)
#define LEVEL_TWO_20(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_19(ACT, __VA_ARGS__)
#define LEVEL_TWO_21(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_20(ACT, __VA_ARGS__)
#define LEVEL_TWO_22(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_21(ACT, __VA_ARGS__)
#define LEVEL_TWO_23(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_22(ACT, __VA_ARGS__)
#define LEVEL_TWO_24(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_23(ACT, __VA_ARGS__)
#define LEVEL_TWO_25(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_24(ACT, __VA_ARGS__)
#define LEVEL_TWO_26(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_25(ACT, __VA_ARGS__)
#define LEVEL_TWO_27(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_26(ACT, __VA_ARGS__)
#define LEVEL_TWO_28(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_27(ACT, __VA_ARGS__)
#define LEVEL_TWO_29(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_28(ACT, __VA_ARGS__)
#define LEVEL_TWO_30(ACT, M, ...)  LEVEL_TWO_DEF(ACT, M)     LEVEL_TWO_29(ACT, __VA_ARGS__)

//  struct to string
#define LEVEL_ONE_STRUCT_2_JNI_O(...)     WRAP_LEVEL_TWO(STRUCT_2_JNI_OPTIONAL, ARG_SEQ, __VA_ARGS__)
#define LEVEL_ONE_STRUCT_2_JNI_A(M, A)    CONVERTER_STRUCT_2_JNI_ALIAS(M,A)
#define LEVEL_ONE_STRUCT_2_JSON_O(...)    WRAP_LEVEL_TWO(STRUCT_2_JSON_OPTIONAL, ARG_SEQ, __VA_ARGS__)
#define LEVEL_ONE_STRUCT_2_JSON_A(M, A)   CONVERTER_STRUCT_2_JSON_ALIAS(M,A)
#define LEVEL_ONE_RET_AND_INNER_O(...)    WRAP_LEVEL_TWO(RET_AND_INNER_OPTIONAL, ARG_SEQ, __VA_ARGS__)
#define LEVEL_ONE_RET_AND_INNER_A(M, A)   CONVERTER_RET_AND_INNER_ALIAS(M,A)




// string to struct
#define LEVEL_ONE_JNI_2_STRUCT_O(...)    WRAP_LEVEL_TWO(JNI_2_STRUCT_OPTIONAL, ARG_SEQ, __VA_ARGS__)
#define LEVEL_ONE_JNI_2_STRUCT_A(M, A)   CONVERTER_JNI_2_STRUCT_ALIAS(M,A)
#define LEVEL_ONE_JSON_2_STRUCT_O(...)   WRAP_LEVEL_TWO(JSON_2_STRUCT_OPTIONAL, ARG_SEQ, __VA_ARGS__)
#define LEVEL_ONE_JSON_2_STRUCT_A(M, A)  CONVERTER_JSON_2_STRUCT_ALIAS(M,A)

// fix inherit by yuanchengsu
#define LEVEL_ONE_STRUCT_2_JSON_B(...)    WRAP_LEVEL_TWO(STRUCT_2_JSON_BASE, ARG_SEQ, __VA_ARGS__)
#define LEVEL_ONE_RET_AND_INNER_B(...)    WRAP_LEVEL_TWO(RET_AND_INNER_BASE, ARG_SEQ, __VA_ARGS__)
#define LEVEL_ONE_JSON_2_STRUCT_B(...)    WRAP_LEVEL_TWO(JSON_2_STRUCT_BASE, ARG_SEQ, __VA_ARGS__)

#define LEVEL_ONE_JNI_2_STRUCT_B(...)     WRAP_LEVEL_TWO(JNI_2_STRUCT_BASE, ARG_SEQ, __VA_ARGS__)
#define LEVEL_ONE_STRUCT_2_JNI_B(...)     WRAP_LEVEL_TWO(STRUCT_2_JNI_BASE, ARG_SEQ, __VA_ARGS__)

#ifdef ANDROID

#define AutoParser(clazzName, ...)                                               \
    JNI_2_STRUCT_FUNC_BEGIN(clazzName)                                           \
    WRAP_LEVEL_ONE(JNI_2_STRUCT_, ARG_SEQ, __VA_ARGS__)                          \
    JNI_2_STRUCT_FUNC_END()                                                      \
                                                                                 \
    STRUCT_2_JNI_FUNC_BEGIN(clazzName)                                           \
    WRAP_LEVEL_ONE(STRUCT_2_JNI_, ARG_SEQ, __VA_ARGS__)                          \
    STRUCT_2_JNI_FUNC_END()                                                      \
                                                                                 \
    JSON_2_STRUCT_FUNC_BEGIN()                                                   \
    WRAP_LEVEL_ONE(JSON_2_STRUCT_, ARG_SEQ, __VA_ARGS__)                         \
    STRUCT_AND_JSON_FUNC_END()                                                   \
                                                                                 \
    STRUCT_2_JSON_FUNC_BEGIN()                                                   \
    WRAP_LEVEL_ONE(STRUCT_2_JSON_, ARG_SEQ, __VA_ARGS__)                         \
    STRUCT_AND_JSON_FUNC_END()                                                   \
                                                                                 \
    RET_AND_INNER_FUNC_BEGIN()                                                   \
    WRAP_LEVEL_ONE(RET_AND_INNER_, ARG_SEQ, __VA_ARGS__)                         \
    RET_AND_INNER_FUNC_END()
#elif defined(__APPLE__)

#define AutoParser(clazzName, ...)                                               \
    JSON_2_STRUCT_FUNC_BEGIN()                                                   \
    WRAP_LEVEL_ONE(JSON_2_STRUCT_, ARG_SEQ, __VA_ARGS__)                         \
    STRUCT_AND_JSON_FUNC_END()                                                   \
                                                                                 \
    STRUCT_2_JSON_FUNC_BEGIN()                                                   \
    WRAP_LEVEL_ONE(STRUCT_2_JSON_, ARG_SEQ, __VA_ARGS__)                         \
    STRUCT_AND_JSON_FUNC_END()                                                   \
                                                                                 \
    RET_AND_INNER_FUNC_BEGIN()                                                   \
    WRAP_LEVEL_ONE(RET_AND_INNER_, ARG_SEQ, __VA_ARGS__)                         \
    RET_AND_INNER_FUNC_END()

#else

#define AutoParser(clazzName, ...) ;

#endif
NS_MSDK_END
#endif //MSDK_MACRO_EXPAND_H

