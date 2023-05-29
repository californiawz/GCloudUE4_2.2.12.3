///*
/*!
 * @Header MSDKSensitivityDelegate.h
 * @Author lamarzhang(张庆贺)
 * @Version 1.0.0
 * @Date 2020/7/30
 * @Abstract 文件功能的声明
 *
 * @Module iTOP
 *
 * Copyright © 2020 company. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MSDKSensitivityDelegate <NSObject>

- (NSString *)getIDFA:(bool)enableAppTracking;

@end

NS_ASSUME_NONNULL_END
