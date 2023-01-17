//
//  MedalliaMXOAPI.h
//  Medallia
//
//  Copyright © 2022 Medallia. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

#define ONE_API_DEPRECATED(__VA_ARGS__) __attribute__((deprecated(__VA_ARGS__)));

/*!
 @typedef MXOLogLevel
 @brief This is an enum which specifies the log level output which will be printed to console.
 @field MXOLogLevelNone This log level disables logging to console.
 @field MXOLogLevelAll  This log level prints everything to console.
 @field MXOLogLevelWebService This log level prints everything relating to web services (requests, responses etc.) only.
 @field MXOLogLevelFramework This log level prints framework events which occur whilst running the app.
 @field MXOLogLevelDebug This log level prints debug logs to console.
 */
typedef NS_ENUM(NSInteger, MXOLogLevel) {
    MXOLogLevelNone NS_SWIFT_NAME(None),
    MXOLogLevelAll NS_SWIFT_NAME(All),
    MXOLogLevelWebService NS_SWIFT_NAME(WebService),
    MXOLogLevelFramework NS_SWIFT_NAME(Framework),
    MXOLogLevelDebug NS_SWIFT_NAME(Debug)
};

/*!
 @typedef MXOTheme
 @brief This is an enum which specifies the theme used in design time.
 @field MXOThemeDefault Default theme in design time.
 @field MXOThemeInteractionStudio Interaction Studio theme in design time.
 */
typedef NS_ENUM(NSInteger, MXOTheme) {
    MXOThemeDefault NS_SWIFT_NAME(Default),
    MXOThemeInteractionStudio NS_SWIFT_NAME(InteractionStudio)
};

/*!
 @typedef MXOOpt
 @brief This is an enum which specifies the type used when opting in/out.
 @field Out Configure MXO SDK to opt out of all tracking, keychain tid storage, pasteboard tid storage, and/or city/country level tracking.
 @field In Configure MXO SDK to opt in for all tracking, keychain tid storage, pasteboard tid storage, and/or city/country level tracking.
*/
typedef NS_OPTIONS(NSUInteger, MXOOpt) {
    Out NS_SWIFT_NAME(out),
    In NS_SWIFT_NAME(in)
};

/*!
 @typedef MXOOptOptions
 @brief This is an enum which specifies the configurations used in design time.
 @field AllTracking Opt out/in from all tracking.
 @field KeychainTidStorage Opt out/in from keychain Tid storage.
 @field PasteboardTidStorage Opt out/in from pasteboard Tid storage.
 @field CityCountryDetection Opt out/in from city/country level tracking.
*/
typedef NS_OPTIONS(NSUInteger, MXOOptOptions) {
    AllTracking NS_SWIFT_NAME(allTracking)                      = 1,
    KeychainTidStorage NS_SWIFT_NAME(keychainTidStorage)        = 1 << 1,
    PasteboardTidStorage NS_SWIFT_NAME(pasteboardTidStorage)    = 1 << 2,
    CityCountryDetection NS_SWIFT_NAME(cityCountryDetection)    = 1 << 3,
};

/*!
 @brief This delegate can be used to retrieve interaction responses from automatically triggered interactions. 
 @discussion Using this delegate is optional. See the MXO SDK for iOS integration document for further details.
 */
    @protocol MXOInteractionResponseDelegate <NSObject>

@property (nonatomic, copy) NSString *mxoInteractionPath;

- (void)interaction:(NSString *)interactionPath didReceiveResponse:(NSDictionary *)response NS_SWIFT_NAME(interaction(_:didReceiveResponse:));

@end


@interface MedalliaMXO : NSObject

/*!
 @brief Initializes the framework.
 @param siteKey The MXO Engagement Hub space site key.
 @param touchPointURI The touchpoint URI path only without the protocol idetifier.
 @param apiKey The MXO Engagement Hub space API key.
 @param sharedSecret The MXO Engagement Hub space shared secret key.
 @param userId A User ID which has access to the current touchpoint. It is recommended to use an api user: api@<your-tenant.com>.
 @param adminMode Define whether the framework is initialized in Admin or User mode. Set YES to initialize in Admin mode. Otherwise set NO to initialize in User mode.
 @param hostName The MXO Engagement Hub server instance your space is hosted on. If you specify the host name without http or https, https will be used.
 @discussion Call the method in app delegate's didFinishLaunchingWithOptions.
 */
+ (void)startSessionWithSK:(NSString *)siteKey uri:(NSString *)touchPointURI apiKey:(NSString *)apiKey sharedSecret:(NSString *)sharedSecret userId:(NSString *)userId adminMode:(BOOL)adminMode hostName:(NSString *)hostName NS_SWIFT_NAME(startSessionWithSK(_:uri:apiKey:sharedSecret:userId:adminMode:hostName:));

/*!
 @brief Sends touchpoint properties to MXO via a PUT request for the interaction '/' (base touchpoint) and/or '/' with '*' (wildcard).
 @param properties A dictionary of properties. Keys and values should be NSString objects.
 */
+ (void)sendBaseTouchpointProperties:(NSDictionary *)properties NS_SWIFT_NAME(sendBaseTouchpointProperties(_:));

/*!
 @brief Sends properties for a given interaction path to MXO via a PUT request.
 @param interactionPath An interaction path.
 @param properties A dictionary of properties. Keys and values should be NSString objects.
 */
+ (void)sendProperties:(NSDictionary *)properties
    forInteractionPath:(NSString *)interactionPath NS_SWIFT_NAME(sendProperties(_:forInteractionPath:));

/*!
 @brief Sends an interaction request with properties for a given path to MXO via a POST request.
 @param properties A dictionary of properties. Keys and values should be NSString objects.
 @param interactionPath An interaction path.
 @discussion If no properties are provided, an interaction request will be sent without properties.
 */
+ (void)sendInteraction:(NSString *)interactionPath
         withProperties:(NSDictionary *)properties NS_SWIFT_NAME(sendInteraction(_:withProperties:));

/*!
 @brief Sends an interaction request with properties for a given path to MXO via a POST request.
 @param properties A dictionary of properties. Keys and values should be NSString objects.
 @param interactionPath An interaction path.
 @param block A completion block will be executed when the response is received. The processResponse: method can be called inside this block to handle the response object.
 @discussion If no properties are provided, an interaction request will be sent without properties.
 */
+ (void)sendInteraction:(NSString *)interactionPath
         withProperties:(NSDictionary *)properties
               andBlock:(void(^)(NSDictionary *response, NSError *error))block NS_SWIFT_NAME(sendInteraction(_:withProperties:andBlock:));

/*!
 @brief Sends an interaction request for a given path to MXO via a POST request.
 @param interactionPath An interaction path.
 */
+ (void)sendInteraction:(NSString *)interactionPath NS_SWIFT_NAME(sendInteraction(_:));

/*!
 @brief Sends an interaction request for a given path to MXO via a POST request.
 @param interactionPath An interaction path.
 @param block A completion block will be executed when the response is received. The processResponse: method can be called inside this block to handle the response object.
 */
+ (void)sendInteraction:(NSString *)interactionPath
              withBlock:(void(^)(NSDictionary *response, NSError *error))block NS_SWIFT_NAME(sendInteraction(_:withBlock:));

/*!
 @brief Sends a response code for a given interaction path via a PUT request.
 @param responseCode A response code.
 @param interactionPath An interaction path.
 */
+ (void)sendResponseCode:(NSString *)responseCode
      forInteractionPath:(NSString *)interactionPath NS_SWIFT_NAME(sendResponseCode(_:forInteractionPath:));

/*!
 @brief Retrieves a structure data from MXO for a given structure name.
 @param structureName A structure name.
 @param block A completion block containing the structure.
 */
+ (void)getStructureData:(NSString *)structureName
               withBlock:(void(^)(NSDictionary *response, NSError *error))block NS_SWIFT_NAME(getStructureData(_:withBlock:)) ONE_API_DEPRECATED("Please contact mxo-mobile-ios@medallia.com if you require access to this API");

/*!
 @brief Sends an '/one-click' interaction call to MXO passing the link URL, host, path and parameters as properties to enable link attribution tracking.
 @param link A NSURL instance.
 */
+ (void)sendInteractionForOutboundLink:(NSURL *)link NS_SWIFT_NAME(sendInteractionForOutboundLink(_:));

/**
 *  Disables automatic interaction detection.
 *
 *  @param disable YES, if automatic interaction detection should be disabled, 
 *  and NO otherwise.
 */
+ (void)disableAutomaticInteractionDetection:(BOOL)disable NS_SWIFT_NAME(disableAutomaticInteractionDetection(_:));

/**
 *  Disables automatic outbound link tracking.
 *
 *  @param disable YES, if automatic outbound link tracking should be disabled,
 *  and NO otherwise.
 */
+ (void)disableAutomaticOutboundLinkTracking:(BOOL)disable NS_SWIFT_NAME(disableAutomaticOutboundLinkTracking(_:));

/*!
 @brief Erases the user profile from the app user preferences.
 */
+ (void)clearUserProfile NS_SWIFT_NAME(clearUserProfile());

/*!
 @brief Returns the current framework version.
 */
+ (NSString *)frameworkVersion NS_SWIFT_NAME(frameworkVersion());

/*!
 @brief Sets the framework's log level.
 @param logValue Log level. Possible values are MXOLogLevelNone, MXOLogLevelAll, MXOLogLevelWebService, MXOLogLevelFramework.
 @discussion Set specific log level to see the framework outputs in the debug panel. By default, the log level is set to MXOLogLevelNone.
 */
+ (void)setLogLevel:(MXOLogLevel)logValue NS_SWIFT_NAME(setLogLevel(_:));

/*!
 @brief Sends the location object's latitude, longitude, horizontal accuracy and timestamp.
 @param location A CLLocation object.
 */
+ (void)updateLocation:(CLLocation *)location NS_SWIFT_NAME(updateLocation(_:));

/*!
 @brief Parses and sends URL parameters of a given URL to MXO
 @param url A NSURL object.
 */
+ (void)handleURL:(NSURL *)url NS_SWIFT_NAME(handleURL(_:));

/*!
 @brief Returns the MXO tid.
 */
+ (NSString *)getTid NS_SWIFT_NAME(getTid());

/*!
 @brief Enables or disables automatic identity transfer for incoming and outgoing links.
 @param disable Set YES to disable automatic identity transfer and NO otherwise.
 @discussion Enabled by default.
 */
+ (void)disableIdentityTransfer:(BOOL)disable NS_SWIFT_NAME(disableIdentityTransfer(_:));

/*!
 @brief Appends the MXO tid as parameter to a given URL.
 @param url A NSURL object.
 @return A NSURL object with the MXO tid.
 */
+ (NSURL *)getURLWithMxoTid:(NSURL *)url NS_SWIFT_NAME(getURLWithMxoTid(_:));

/*!
 @brief Allows the given links to participate in identity transfer.
 @param links A NSArray object containg NSURL or NSString objects.
 @discussion The given links can be NSURL objects or NSString objects representing URL patterns. NSString objects can include wildcard characters.
 */
+ (void)whitelistIdentityTransferLinks:(NSArray *)links;

/*!
 @brief Disallows the given links to participate in identity transfer.
 @param links A NSArray object containg NSURL or NSString objects.
 @discussion The given links can be NSURL objects or NSString objects representing URL patterns. NSString objects can include wildcard characters.
 */
+ (void)blacklistIdentityTransferLinks:(NSArray *)links;

/*!
 @brief Synchronizes the app's customer identity with their identity in Mobile Safari.
 */
+ (void)identitySync NS_SWIFT_NAME(identitySync());

/*!
 @brief Synchronizes the app's customer identity with their identity from a given URL.
 @param url A NSURL object.
 */
+ (void)identitySyncWithURL:(NSURL *)url NS_SWIFT_NAME(identitySyncWithURL(_:));

/*!
 @brief Handles a response received from MXO. All tracking and/or capture points will be parsed by the framework as usual. All optimization points, known by the framework, will be processed/displayed.
 @param response A NSDictionary instance.
 */
+ (void)processResponse:(NSDictionary *)response NS_SWIFT_NAME(processResponse(_:));

/*!
 @brief Register a given object to receive a response for an automatically triggered interaction call. 
 @param delegate An object conforming to MXOInteractionResponseDelegate protocol.
 @discussion If the object is deallocated, it will be automatically unregistered. If you want to unregister the object and use it for other needs, you can call removeInteractionResponseDelegate: method.
 */
+ (void)addInteractionResponseDelegate:(id <MXOInteractionResponseDelegate>)delegate NS_SWIFT_NAME(addInteractionResponseDelegate(_:));

/*!
 @brief Removes a given object from receiving a response for an automatically triggered interaction call.
 @param delegate An object you added by using addInteractionResponseDelegate: method.
 */
+ (void)removeInteractionResponseDelegate:(id)delegate NS_SWIFT_NAME(removeInteractionResponseDelegate(_:));

/*!
 @brief Configure MXO SDK to opt out/in from all tracking, or keychain tid storage, or pasteboard tid storage and/or city/country level tracking. By default, the MXO SDK is opted in for all settings.
 @param mxoOpt A MXOOpt enum that determines if the configurations are opted in or out. For a list of possible values, see the constants for the MXOOpt type.
 @param options An integer bit mask that determines which configurations to opt out/in. For a list of possible values, see the constants for the MXOOptOut type.
*/
+ (void)opt:(MXOOpt)mxoOpt forOptions:(MXOOptOptions)options NS_SWIFT_NAME(opt(_:forOptions:));

/*!
 @brief Sets the framework's UI theme.
 @param theme A MXOTheme enum. For a list of possible values, see the constants for the MXOTheme type.
 @discussion Set specific themes to update the framework's UI in design time. By default, the theme is set to kMXOThemeDefault.
 */
+ (void)setTheme:(MXOTheme)theme NS_SWIFT_NAME(setTheme(_:));

@end

///////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Interaction ID
///////////////////////////////////////////////////////////////////////////////////////////

@interface UIViewController (MXOInteracting)

/*!
 @property mxoInteractionPath
 @brief An interaction path.
 */
@property (nonatomic, copy) NSString *mxoInteractionPath;

/*!
 @property excludeInteractionPath
 @brief Excludes an interaction from being recognized by the framework
 @discussion Set it to YES to exclude the interaction from processing. Default is NO.
 */
@property (nonatomic, assign) BOOL excludeInteractionPath;

@end