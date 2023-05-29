//
//  WXApiObject+WMPF.h
//  WeChatSDK
//
//  Created by abezheng(郑昱旋) on 2020/8/18.
//

#pragma mark - WMPF

/*! @brief 小程序 SDK 专用，在 sendAuthReq 的基础上添加了私有字段
 *
 *  tdiExtInfo 会在 SendTdiAuthResp 原样带回 SendTdiAuthReq 填写的内容
*/
@interface SendTdiAuthReq : SendAuthReq

@property (nonatomic, copy) NSString *tdiExtInfo;

@end

/*! @brief 小程序 SDK 专用，在 SendTdiAuthResp 的基础上添加了私有字段
 *
 *  当 auth scope 带有 snsapi_runtime_sdk 时，微信会通过 SendTdiAuthResp 带回 tdiAuthBuffer。
 *  tdiExtInfo 会原样带回 SendTdiAuthReq 填写的内容
 */
@interface SendTdiAuthResp : SendAuthResp

@property (nonatomic, copy) NSString *tdiExtInfo;
@property (nonatomic, nullable) NSData *tdiAuthBuffer;
@property (nonatomic, nullable) NSData *tdiAuthParams;

@end

/*! @brief 小程序 SDK 专用，用于跳转到微信执行 JSAPI
*/

@interface WXLaunchWxaRedirectingPageReq : BaseReq

@property (nonatomic, copy) NSString *ticket;

/** 剪切板传递数据
*/
@property (nonatomic, nullable) NSDictionary *extDict;

@end

@interface WXLaunchWxaRedirectingPageResp : BaseResp

@property (nonatomic, copy) NSString *ticket;

@end
