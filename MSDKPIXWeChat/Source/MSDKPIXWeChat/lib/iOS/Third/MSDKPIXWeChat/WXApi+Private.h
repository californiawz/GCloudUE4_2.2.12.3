//
//  WXApi+Private.h
//  WeChatSDK
//
//  Created by Aizenzhang on 2018/6/1.
//

#import "WXApi.h"

extern const UInt32 kWXSendMsg2SpecialContactSupportVersion;

@interface WXApi (Private)

/*! @brief 尝试获取用户安装的微信的十六进制版本号
 *
 * @return 返回用户安装的微信的十六进制版本号。 在第三方应用收到微信返回的Resp时(通过SDK跳转微信，并由微信跳转回第三方应用)，SDK可从微信获得版本号并记录于NSUserDefaults。
 注意: 以下情况返回结果不准确
  1. 微信是旧版本微信(版本号及以下)，则返回0。 //TODO 待确定旧版本微信号
  2. 第三方应用和微信从未发生以上通信，则返回0。
  3. 当用户更新微信后再无发生以上通信，则接口返回的版本会小于用户的实际版本。
  4. 第三方应用将NSUserDefaults关于微信的版本号数据清除, 则返回0。
 */
+(UInt32) tryGetWechatVersion;

@end
