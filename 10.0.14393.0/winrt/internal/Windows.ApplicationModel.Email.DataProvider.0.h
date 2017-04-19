// C++ for the Windows Runtime v1.0.170406.8
// Copyright (c) 2017 Microsoft Corporation. All rights reserved.

#pragma once


WINRT_EXPORT namespace winrt {

namespace ABI::Windows::ApplicationModel::Email::DataProvider {

struct IEmailDataProviderConnection;
struct IEmailDataProviderTriggerDetails;
struct IEmailMailboxCreateFolderRequest;
struct IEmailMailboxCreateFolderRequestEventArgs;
struct IEmailMailboxDeleteFolderRequest;
struct IEmailMailboxDeleteFolderRequestEventArgs;
struct IEmailMailboxDownloadAttachmentRequest;
struct IEmailMailboxDownloadAttachmentRequestEventArgs;
struct IEmailMailboxDownloadMessageRequest;
struct IEmailMailboxDownloadMessageRequestEventArgs;
struct IEmailMailboxEmptyFolderRequest;
struct IEmailMailboxEmptyFolderRequestEventArgs;
struct IEmailMailboxForwardMeetingRequest;
struct IEmailMailboxForwardMeetingRequestEventArgs;
struct IEmailMailboxGetAutoReplySettingsRequest;
struct IEmailMailboxGetAutoReplySettingsRequestEventArgs;
struct IEmailMailboxMoveFolderRequest;
struct IEmailMailboxMoveFolderRequestEventArgs;
struct IEmailMailboxProposeNewTimeForMeetingRequest;
struct IEmailMailboxProposeNewTimeForMeetingRequestEventArgs;
struct IEmailMailboxResolveRecipientsRequest;
struct IEmailMailboxResolveRecipientsRequestEventArgs;
struct IEmailMailboxServerSearchReadBatchRequest;
struct IEmailMailboxServerSearchReadBatchRequestEventArgs;
struct IEmailMailboxSetAutoReplySettingsRequest;
struct IEmailMailboxSetAutoReplySettingsRequestEventArgs;
struct IEmailMailboxSyncManagerSyncRequest;
struct IEmailMailboxSyncManagerSyncRequestEventArgs;
struct IEmailMailboxUpdateMeetingResponseRequest;
struct IEmailMailboxUpdateMeetingResponseRequestEventArgs;
struct IEmailMailboxValidateCertificatesRequest;
struct IEmailMailboxValidateCertificatesRequestEventArgs;
struct EmailDataProviderConnection;
struct EmailDataProviderTriggerDetails;
struct EmailMailboxCreateFolderRequest;
struct EmailMailboxCreateFolderRequestEventArgs;
struct EmailMailboxDeleteFolderRequest;
struct EmailMailboxDeleteFolderRequestEventArgs;
struct EmailMailboxDownloadAttachmentRequest;
struct EmailMailboxDownloadAttachmentRequestEventArgs;
struct EmailMailboxDownloadMessageRequest;
struct EmailMailboxDownloadMessageRequestEventArgs;
struct EmailMailboxEmptyFolderRequest;
struct EmailMailboxEmptyFolderRequestEventArgs;
struct EmailMailboxForwardMeetingRequest;
struct EmailMailboxForwardMeetingRequestEventArgs;
struct EmailMailboxGetAutoReplySettingsRequest;
struct EmailMailboxGetAutoReplySettingsRequestEventArgs;
struct EmailMailboxMoveFolderRequest;
struct EmailMailboxMoveFolderRequestEventArgs;
struct EmailMailboxProposeNewTimeForMeetingRequest;
struct EmailMailboxProposeNewTimeForMeetingRequestEventArgs;
struct EmailMailboxResolveRecipientsRequest;
struct EmailMailboxResolveRecipientsRequestEventArgs;
struct EmailMailboxServerSearchReadBatchRequest;
struct EmailMailboxServerSearchReadBatchRequestEventArgs;
struct EmailMailboxSetAutoReplySettingsRequest;
struct EmailMailboxSetAutoReplySettingsRequestEventArgs;
struct EmailMailboxSyncManagerSyncRequest;
struct EmailMailboxSyncManagerSyncRequestEventArgs;
struct EmailMailboxUpdateMeetingResponseRequest;
struct EmailMailboxUpdateMeetingResponseRequestEventArgs;
struct EmailMailboxValidateCertificatesRequest;
struct EmailMailboxValidateCertificatesRequestEventArgs;

}

namespace Windows::ApplicationModel::Email::DataProvider {

struct IEmailDataProviderConnection;
struct IEmailDataProviderTriggerDetails;
struct IEmailMailboxCreateFolderRequest;
struct IEmailMailboxCreateFolderRequestEventArgs;
struct IEmailMailboxDeleteFolderRequest;
struct IEmailMailboxDeleteFolderRequestEventArgs;
struct IEmailMailboxDownloadAttachmentRequest;
struct IEmailMailboxDownloadAttachmentRequestEventArgs;
struct IEmailMailboxDownloadMessageRequest;
struct IEmailMailboxDownloadMessageRequestEventArgs;
struct IEmailMailboxEmptyFolderRequest;
struct IEmailMailboxEmptyFolderRequestEventArgs;
struct IEmailMailboxForwardMeetingRequest;
struct IEmailMailboxForwardMeetingRequestEventArgs;
struct IEmailMailboxGetAutoReplySettingsRequest;
struct IEmailMailboxGetAutoReplySettingsRequestEventArgs;
struct IEmailMailboxMoveFolderRequest;
struct IEmailMailboxMoveFolderRequestEventArgs;
struct IEmailMailboxProposeNewTimeForMeetingRequest;
struct IEmailMailboxProposeNewTimeForMeetingRequestEventArgs;
struct IEmailMailboxResolveRecipientsRequest;
struct IEmailMailboxResolveRecipientsRequestEventArgs;
struct IEmailMailboxServerSearchReadBatchRequest;
struct IEmailMailboxServerSearchReadBatchRequestEventArgs;
struct IEmailMailboxSetAutoReplySettingsRequest;
struct IEmailMailboxSetAutoReplySettingsRequestEventArgs;
struct IEmailMailboxSyncManagerSyncRequest;
struct IEmailMailboxSyncManagerSyncRequestEventArgs;
struct IEmailMailboxUpdateMeetingResponseRequest;
struct IEmailMailboxUpdateMeetingResponseRequestEventArgs;
struct IEmailMailboxValidateCertificatesRequest;
struct IEmailMailboxValidateCertificatesRequestEventArgs;
struct EmailDataProviderConnection;
struct EmailDataProviderTriggerDetails;
struct EmailMailboxCreateFolderRequest;
struct EmailMailboxCreateFolderRequestEventArgs;
struct EmailMailboxDeleteFolderRequest;
struct EmailMailboxDeleteFolderRequestEventArgs;
struct EmailMailboxDownloadAttachmentRequest;
struct EmailMailboxDownloadAttachmentRequestEventArgs;
struct EmailMailboxDownloadMessageRequest;
struct EmailMailboxDownloadMessageRequestEventArgs;
struct EmailMailboxEmptyFolderRequest;
struct EmailMailboxEmptyFolderRequestEventArgs;
struct EmailMailboxForwardMeetingRequest;
struct EmailMailboxForwardMeetingRequestEventArgs;
struct EmailMailboxGetAutoReplySettingsRequest;
struct EmailMailboxGetAutoReplySettingsRequestEventArgs;
struct EmailMailboxMoveFolderRequest;
struct EmailMailboxMoveFolderRequestEventArgs;
struct EmailMailboxProposeNewTimeForMeetingRequest;
struct EmailMailboxProposeNewTimeForMeetingRequestEventArgs;
struct EmailMailboxResolveRecipientsRequest;
struct EmailMailboxResolveRecipientsRequestEventArgs;
struct EmailMailboxServerSearchReadBatchRequest;
struct EmailMailboxServerSearchReadBatchRequestEventArgs;
struct EmailMailboxSetAutoReplySettingsRequest;
struct EmailMailboxSetAutoReplySettingsRequestEventArgs;
struct EmailMailboxSyncManagerSyncRequest;
struct EmailMailboxSyncManagerSyncRequestEventArgs;
struct EmailMailboxUpdateMeetingResponseRequest;
struct EmailMailboxUpdateMeetingResponseRequestEventArgs;
struct EmailMailboxValidateCertificatesRequest;
struct EmailMailboxValidateCertificatesRequestEventArgs;

}

namespace Windows::ApplicationModel::Email::DataProvider {

template <typename T> struct impl_IEmailDataProviderConnection;
template <typename T> struct impl_IEmailDataProviderTriggerDetails;
template <typename T> struct impl_IEmailMailboxCreateFolderRequest;
template <typename T> struct impl_IEmailMailboxCreateFolderRequestEventArgs;
template <typename T> struct impl_IEmailMailboxDeleteFolderRequest;
template <typename T> struct impl_IEmailMailboxDeleteFolderRequestEventArgs;
template <typename T> struct impl_IEmailMailboxDownloadAttachmentRequest;
template <typename T> struct impl_IEmailMailboxDownloadAttachmentRequestEventArgs;
template <typename T> struct impl_IEmailMailboxDownloadMessageRequest;
template <typename T> struct impl_IEmailMailboxDownloadMessageRequestEventArgs;
template <typename T> struct impl_IEmailMailboxEmptyFolderRequest;
template <typename T> struct impl_IEmailMailboxEmptyFolderRequestEventArgs;
template <typename T> struct impl_IEmailMailboxForwardMeetingRequest;
template <typename T> struct impl_IEmailMailboxForwardMeetingRequestEventArgs;
template <typename T> struct impl_IEmailMailboxGetAutoReplySettingsRequest;
template <typename T> struct impl_IEmailMailboxGetAutoReplySettingsRequestEventArgs;
template <typename T> struct impl_IEmailMailboxMoveFolderRequest;
template <typename T> struct impl_IEmailMailboxMoveFolderRequestEventArgs;
template <typename T> struct impl_IEmailMailboxProposeNewTimeForMeetingRequest;
template <typename T> struct impl_IEmailMailboxProposeNewTimeForMeetingRequestEventArgs;
template <typename T> struct impl_IEmailMailboxResolveRecipientsRequest;
template <typename T> struct impl_IEmailMailboxResolveRecipientsRequestEventArgs;
template <typename T> struct impl_IEmailMailboxServerSearchReadBatchRequest;
template <typename T> struct impl_IEmailMailboxServerSearchReadBatchRequestEventArgs;
template <typename T> struct impl_IEmailMailboxSetAutoReplySettingsRequest;
template <typename T> struct impl_IEmailMailboxSetAutoReplySettingsRequestEventArgs;
template <typename T> struct impl_IEmailMailboxSyncManagerSyncRequest;
template <typename T> struct impl_IEmailMailboxSyncManagerSyncRequestEventArgs;
template <typename T> struct impl_IEmailMailboxUpdateMeetingResponseRequest;
template <typename T> struct impl_IEmailMailboxUpdateMeetingResponseRequestEventArgs;
template <typename T> struct impl_IEmailMailboxValidateCertificatesRequest;
template <typename T> struct impl_IEmailMailboxValidateCertificatesRequestEventArgs;

}

}
