//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class OWSContact;
@class OWSLinkPreviewDraft;
@class OWSMessageSender;
@class OWSQuotedReplyModel;
@class OWSUnreadIndicator;
@class SDSAnyReadTransaction;
@class SDSAnyWriteTransaction;
@class SignalAttachment;
@class SignalServiceAddress;
@class StickerInfo;
@class TSContactThread;
@class TSGroupThread;
@class TSInteraction;
@class TSOutgoingMessage;
@class TSThread;
@class YapDatabaseReadTransaction;

@interface ThreadDynamicInteractions : NSObject

// Represents the "reverse index" of the focus message, if any.
// The "reverse index" is the distance of this interaction from
// the last interaction in the thread.  Therefore the last interaction
// will have a "reverse index" of zero.
//
// We use "reverse indices" because (among other uses) we use this to
// determine the initial load window size.
@property (nonatomic, nullable, readonly) NSNumber *focusMessagePosition;

@property (nonatomic, nullable, readonly) OWSUnreadIndicator *unreadIndicator;

- (void)clearUnreadIndicatorState;

@end

#pragma mark -

@interface ThreadUtil : NSObject

#pragma mark - Durable Message Enqueue

+ (TSOutgoingMessage *)enqueueMessageWithText:(NSString *)fullMessageText
                                     inThread:(TSThread *)thread
                             quotedReplyModel:(nullable OWSQuotedReplyModel *)quotedReplyModel
                             linkPreviewDraft:(nullable nullable OWSLinkPreviewDraft *)linkPreviewDraft
                                  transaction:(SDSAnyReadTransaction *)transaction;

+ (TSOutgoingMessage *)enqueueMessageWithText:(nullable NSString *)fullMessageText
                             mediaAttachments:(NSArray<SignalAttachment *> *)attachments
                                     inThread:(TSThread *)thread
                             quotedReplyModel:(nullable OWSQuotedReplyModel *)quotedReplyModel
                             linkPreviewDraft:(nullable nullable OWSLinkPreviewDraft *)linkPreviewDraft
                                  transaction:(SDSAnyReadTransaction *)transaction;

+ (nullable TSOutgoingMessage *)createUnsentMessageWithText:(nullable NSString *)fullMessageText
                                           mediaAttachments:(NSArray<SignalAttachment *> *)mediaAttachments
                                                   inThread:(TSThread *)thread
                                           quotedReplyModel:(nullable OWSQuotedReplyModel *)quotedReplyModel
                                           linkPreviewDraft:(nullable nullable OWSLinkPreviewDraft *)linkPreviewDraft
                                                transaction:(SDSAnyWriteTransaction *)transaction
                                                      error:(NSError **)error;

+ (TSOutgoingMessage *)enqueueMessageWithContactShare:(OWSContact *)contactShare inThread:(TSThread *)thread;
+ (void)enqueueLeaveGroupMessageInThread:(TSGroupThread *)thread;

+ (TSOutgoingMessage *)enqueueMessageWithInstalledSticker:(StickerInfo *)stickerInfo inThread:(TSThread *)thread;
+ (TSOutgoingMessage *)enqueueMessageWithUninstalledSticker:(StickerInfo *)stickerInfo
                                                stickerData:(NSData *)stickerData
                                                   inThread:(TSThread *)thread;

#pragma mark - Non-Durable Sending

// Used by SAE and "reply from lockscreen", otherwise we should use the durable `enqueue` counterpart
+ (TSOutgoingMessage *)sendMessageNonDurablyWithText:(NSString *)fullMessageText
                                            inThread:(TSThread *)thread
                                    quotedReplyModel:(nullable OWSQuotedReplyModel *)quotedReplyModel
                                         transaction:(SDSAnyReadTransaction *)transaction
                                       messageSender:(OWSMessageSender *)messageSender
                                          completion:(void (^)(NSError *_Nullable error))completion;

// Used by SAE, otherwise we should use the durable `enqueue` counterpart
+ (TSOutgoingMessage *)sendMessageNonDurablyWithText:(NSString *)fullMessageText
                                    mediaAttachments:(NSArray<SignalAttachment *> *)attachments
                                            inThread:(TSThread *)thread
                                    quotedReplyModel:(nullable OWSQuotedReplyModel *)quotedReplyModel
                                         transaction:(SDSAnyReadTransaction *)transaction
                                       messageSender:(OWSMessageSender *)messageSender
                                          completion:(void (^)(NSError *_Nullable error))completion;

// Used by SAE, otherwise we should use the durable `enqueue` counterpart
+ (TSOutgoingMessage *)sendMessageNonDurablyWithContactShare:(OWSContact *)contactShare
                                                    inThread:(TSThread *)thread
                                               messageSender:(OWSMessageSender *)messageSender
                                                  completion:(void (^)(NSError *_Nullable error))completion;

#pragma mark - dynamic interactions

// This method will create and/or remove any offers and indicators
// necessary for this thread.  This includes:
//
// * Block offers.
// * "Add to contacts" offers.
// * Unread indicators.
//
// Parameters:
//
// * hideUnreadMessagesIndicator: If YES, the "unread indicator" has
//   been cleared and should not be shown.
// * firstUnseenInteractionTimestamp: A snapshot of unseen message state
//   when we entered the conversation view.  See comments on
//   ThreadOffersAndIndicators.
// * maxRangeSize: Loading a lot of messages in conversation view is
//   slow and unwieldy.  This number represents the maximum current
//   size of the "load window" in that view. The unread indicator should
//   always be inserted within that window.
+ (ThreadDynamicInteractions *)ensureDynamicInteractionsForThread:(TSThread *)thread
                                      hideUnreadMessagesIndicator:(BOOL)hideUnreadMessagesIndicator
                                              lastUnreadIndicator:(nullable OWSUnreadIndicator *)lastUnreadIndicator
                                                   focusMessageId:(nullable NSString *)focusMessageId
                                                     maxRangeSize:(NSUInteger)maxRangeSize
                                                      transaction:(SDSAnyReadTransaction *)transaction;

// This method should be called right _before_ we send a message to a thread,
// since we want to auto-add any thread to the profile whitelist that was
// initiated by the local user.
//
// Returns YES IFF the thread was just added to the profile whitelist.
+ (BOOL)addThreadToProfileWhitelistIfEmptyThreadWithSneakyTransaction:(TSThread *)thread;

#pragma mark - Delete Content

+ (void)deleteAllContent;

#pragma mark - Find Content

+ (nullable TSInteraction *)findInteractionInThreadByTimestamp:(uint64_t)timestamp
                                                 authorAddress:(SignalServiceAddress *)authorAddress
                                                threadUniqueId:(NSString *)threadUniqueId
                                                   transaction:(SDSAnyReadTransaction *)transaction;

#pragma mark - Message Request

+ (BOOL)hasPendingMessageRequest:(TSThread *)thread transaction:(SDSAnyReadTransaction *)transaction;
+ (BOOL)existsOutgoingMessage:(TSThread *)thread transaction:(SDSAnyReadTransaction *)transaction;

@end

NS_ASSUME_NONNULL_END
