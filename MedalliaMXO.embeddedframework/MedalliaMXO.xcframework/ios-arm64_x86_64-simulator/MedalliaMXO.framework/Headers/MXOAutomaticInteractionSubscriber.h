//
//  MXOAutomaticInteractionSubscriber.h
//  MedalliaMXO
//
//  Copyright © 2023 Medallia. Use subject to licensing terms.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MXOInteractionResponse, MXOInteraction, MXOAutomaticInteractionSubscriberBuilder;

///////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Typedef
///////////////////////////////////////////////////////////////////////////////////////////

typedef void (^MXOAutomaticInteractionOnResponseBlock)(MXOInteractionResponse *response);
typedef void (^MXOAutomaticInteractionSubscriberBuilderBlock)(MXOAutomaticInteractionSubscriberBuilder *builder);

///////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - MXOAutomaticInteractionSubscriber
///////////////////////////////////////////////////////////////////////////////////////////

@interface MXOAutomaticInteractionSubscriber : NSObject

///////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Properties
///////////////////////////////////////////////////////////////////////////////////////////

@property (nonatomic, strong, readonly) MXOInteraction *interaction;

@property (nonatomic, copy, readonly, nullable) MXOAutomaticInteractionOnResponseBlock onResponse;

///////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Instance Methods
///////////////////////////////////////////////////////////////////////////////////////////

- (MXOAutomaticInteractionSubscriberBuilder *)builder;

- (instancetype)init NS_UNAVAILABLE;

///////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Class Methods
///////////////////////////////////////////////////////////////////////////////////////////

+ (instancetype)initWithBuilder:(MXOAutomaticInteractionSubscriberBuilderBlock)block NS_SWIFT_NAME(init(withBuilder:));

@end

///////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - MXOAutomaticInteractionSubscriberBuilder
///////////////////////////////////////////////////////////////////////////////////////////

@interface MXOAutomaticInteractionSubscriberBuilder : NSObject

@property (nonatomic, strong) MXOInteraction *interaction;

@property (nonatomic, copy, nullable) MXOAutomaticInteractionOnResponseBlock onResponse;

///////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Instance Methods
///////////////////////////////////////////////////////////////////////////////////////////

- (MXOAutomaticInteractionSubscriber *)build;

@end

NS_ASSUME_NONNULL_END