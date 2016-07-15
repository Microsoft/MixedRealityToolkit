// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "Lobby2ResultCode.h"
#include "RakAssert.h"

using namespace RakNet;

static Lobby2ResultCodeDescription resultCodeDescriptions[L2RC_COUNT] =
{
	{L2RC_SUCCESS, "SUCCESS", "SUCCESS"},
	{L2RC_PROCESSING, "PROCESSING", "PROCESSING"},
	{L2RC_BUSY_EXCEEDED_PROCESSING_LIMIT, "BUSY_EXCEEDED_PROCESSING_LIMIT", "BUSY_EXCEEDED_PROCESSING_LIMIT"},
	{L2RC_INVALID_PARAMETERS, "INVALID_PARAMETERS", "INVALID_PARAMETERS"},
	{L2RC_GENERAL_ERROR, "GENERAL_ERROR", "GENERAL_ERROR"},
	{L2RC_UNSUPPORTED_PLATFORM, "UNSUPPORTED_PLATFORM", "UNSUPPORTED_PLATFORM"},
	{L2RC_OUT_OF_MEMORY, "OUT_OF_MEMORY", "OUT_OF_MEMORY"},
	{L2RC_NOT_IMPLEMENTED, "NOT_IMPLEMENTED", "NOT_IMPLEMENTED"},
	{L2RC_NOT_LOGGED_IN, "NOT_LOGGED_IN", "NOT_LOGGED_IN"},
	{L2RC_DATABASE_CONSTRAINT_FAILURE, "DATABASE_CONSTRAINT_FAILURE", "DATABASE_CONSTRAINT_FAILURE"},
	{L2RC_PROFANITY_FILTER_CHECK_FAILED, "PROFANITY_FILTER_CHECK_FAILED", "PROFANITY_FILTER_CHECK_FAILED"},
	{L2RC_REQUIRES_ADMIN, "REQUIRES_ADMIN", "REQUIRES_ADMIN"},
	{L2RC_REQUIRES_RANKING_PERMISSION, "REQUIRES_RANKING_PERMISSION", "REQUIRES_RANKING_PERMISSION"},
	{L2RC_UNKNOWN_USER, "UNKNOWN_USER", "UNKNOWN_USER"},
	{L2RC_HANDLE_IS_EMPTY, "HANDLE_IS_EMPTY", "HANDLE_IS_EMPTY"},
	{L2RC_HANDLE_CONTAINS_NON_PRINTABLE, "HANDLE_CONTAINS_NON_PRINTABLE", "HANDLE_CONTAINS_NON_PRINTABLE"},
	{L2RC_HANDLE_STARTS_WITH_SPACES, "HANDLE_STARTS_WITH_SPACES", "HANDLE_STARTS_WITH_SPACES"},
	{L2RC_HANDLE_ENDS_WITH_SPACES, "HANDLE_ENDS_WITH_SPACES", "HANDLE_ENDS_WITH_SPACES"},
	{L2RC_HANDLE_HAS_CONSECUTIVE_SPACES, "HANDLE_HAS_CONSECUTIVE_SPACES", "HANDLE_HAS_CONSECUTIVE_SPACES"},
	{L2RC_HANDLE_IS_TOO_SHORT, "HANDLE_IS_TOO_SHORT", "HANDLE_IS_TOO_SHORT"},
	{L2RC_HANDLE_IS_TOO_LONG, "HANDLE_IS_TOO_LONG", "HANDLE_IS_TOO_LONG"},
	{L2RC_BINARY_DATA_LENGTH_EXCEEDED, "BINARY_DATA_LENGTH_EXCEEDED", "BINARY_DATA_LENGTH_EXCEEDED"},
	{L2RC_BINARY_DATA_NULL_POINTER, "BINARY_DATA_NULL_POINTER", "BINARY_DATA_NULL_POINTER"},
	{L2RC_REQUIRED_TEXT_IS_EMPTY, "REQUIRED_TEXT_IS_EMPTY", "REQUIRED_TEXT_IS_EMPTY"},
	{L2RC_PASSWORD_IS_WRONG, "PASSWORD_IS_WRONG", "PASSWORD_IS_WRONG"},
	{L2RC_PASSWORD_IS_EMPTY, "PASSWORD_IS_EMPTY", "PASSWORD_IS_EMPTY"},
	{L2RC_PASSWORD_IS_TOO_SHORT, "PASSWORD_IS_TOO_SHORT", "PASSWORD_IS_TOO_SHORT"},
	{L2RC_PASSWORD_IS_TOO_LONG, "PASSWORD_IS_TOO_LONG", "PASSWORD_IS_TOO_LONG"},
	{L2RC_EMAIL_ADDRESS_IS_EMPTY, "EMAIL_ADDRESS_IS_EMPTY", "EMAIL_ADDRESS_IS_EMPTY"},
	{L2RC_EMAIL_ADDRESS_IS_INVALID, "EMAIL_ADDRESS_IS_INVALID", "EMAIL_ADDRESS_IS_INVALID"},
	{L2RC_System_CreateTitle_TITLE_ALREADY_IN_USE, "System_CreateTitle_TITLE_ALREADY_IN_USE", "System_CreateTitle_TITLE_ALREADY_IN_USE"},
	{L2RC_System_DestroyTitle_TITLE_NOT_IN_USE, "System_DestroyTitle_TITLE_NOT_IN_USE", "System_DestroyTitle_TITLE_NOT_IN_USE"},
	{L2RC_System_GetTitleBinaryData_TITLE_NOT_IN_USE, "System_GetTitleBinaryData_TITLE_NOT_IN_USE", "System_GetTitleBinaryData_TITLE_NOT_IN_USE"},
	{L2RC_System_GetTitleRequiredAge_TITLE_NOT_IN_USE, "System_GetTitleRequiredAge_TITLE_NOT_IN_USE", "System_GetTitleRequiredAge_TITLE_NOT_IN_USE"},
	{L2RC_System_RegisterProfanity_CANNOT_REGISTER_EMPTY_STRINGS, "System_RegisterProfanity_CANNOT_REGISTER_EMPTY_STRINGS", "System_RegisterProfanity_CANNOT_REGISTER_EMPTY_STRINGS"},
	{L2RC_System_BanUser_INVALID_DURATION, "System_BanUser_INVALID_DURATION", "System_BanUser_INVALID_DURATION"},
	{L2RC_System_BanUser_ALREADY_BANNED, "System_BanUser_ALREADY_BANNED", "System_BanUser_ALREADY_BANNED"},
	{L2RC_System_UnbanUser_NOT_BANNED, "System_UnbanUser_NOT_BANNED", "System_UnbanUser_NOT_BANNED"},
	{L2RC_System_DeleteAccount_INVALID_PASSWORD, "System_DeleteAccount_INVALID_PASSWORD", "System_DeleteAccount_INVALID_PASSWORD"},
	{L2RC_CDKey_Add_TITLE_NOT_IN_USE, "CDKey_Add_TITLE_NOT_IN_USE", "CDKey_Add_TITLE_NOT_IN_USE"},
	{L2RC_CDKey_GetStatus_TITLE_NOT_IN_USE, "CDKey_GetStatus_TITLE_NOT_IN_USE", "CDKey_GetStatus_TITLE_NOT_IN_USE"},
	{L2RC_CDKey_GetStatus_UNKNOWN_CD_KEY, "CDKey_GetStatus_UNKNOWN_CD_KEY", "CDKey_GetStatus_UNKNOWN_CD_KEY"},
	{L2RC_CDKey_Use_TITLE_NOT_IN_USE, "CDKey_Use_TITLE_NOT_IN_USE", "CDKey_Use_TITLE_NOT_IN_USE"},
	{L2RC_CDKey_Use_UNKNOWN_CD_KEY, "CDKey_Use_UNKNOWN_CD_KEY", "CDKey_Use_UNKNOWN_CD_KEY"},
	{L2RC_CDKey_Use_NOT_USABLE, "CDKey_Use_NOT_USABLE", "CDKey_Use_NOT_USABLE"},
	{L2RC_CDKey_Use_CD_KEY_ALREADY_USED, "CDKey_Use_CD_KEY_ALREADY_USED", "CDKey_Use_CD_KEY_ALREADY_USED"},
	{L2RC_CDKey_Use_CD_KEY_STOLEN, "CDKey_Use_CD_KEY_STOLEN", "CDKey_Use_CD_KEY_STOLEN"},
	{L2RC_CDKey_FlagStolen_TITLE_NOT_IN_USE, "CDKey_FlagStolen_TITLE_NOT_IN_USE", "CDKey_FlagStolen_TITLE_NOT_IN_USE"},
	{L2RC_CDKey_FlagStolen_UNKNOWN_CD_KEY, "CDKey_FlagStolen_UNKNOWN_CD_KEY", "CDKey_FlagStolen_UNKNOWN_CD_KEY"},
	{L2RC_Client_Login_HANDLE_NOT_IN_USE_OR_BAD_SECRET_KEY, "Client_Login_HANDLE_NOT_IN_USE_OR_BAD_SECRET_KEY", "Client_Login_HANDLE_NOT_IN_USE_OR_BAD_SECRET_KEY"},
	{L2RC_Client_Login_CANCELLED, "Client_Login_CANCELLED", "Client_Login_CANCELLED"},
	{L2RC_Client_Login_CABLE_NOT_CONNECTED, "Client_Login_CABLE_NOT_CONNECTED", "Client_Login_CABLE_NOT_CONNECTED"},
	{L2RC_Client_Login_NET_NOT_CONNECTED, "Client_Login_NET_NOT_CONNECTED", "Client_Login_NET_NOT_CONNECTED"},
	{L2RC_Client_Login_BANNED, "Client_Login_BANNED", "Client_Login_BANNED"},
	{L2RC_Client_Login_CDKEY_STOLEN, "Client_Login_CDKEY_STOLEN", "Client_Login_CDKEY_STOLEN"},
	{L2RC_Client_Login_EMAIL_ADDRESS_NOT_VALIDATED, "Client_Login_EMAIL_ADDRESS_NOT_VALIDATED", "Client_Login_EMAIL_ADDRESS_NOT_VALIDATED"},
	{L2RC_Client_Login_BAD_TITLE_OR_TITLE_SECRET_KEY, "Client_Login_BAD_TITLE_OR_TITLE_SECRET_KEY", "Client_Login_BAD_TITLE_OR_TITLE_SECRET_KEY"},
	{L2RC_Client_Login_CONTEXT_CREATION_FAILURE, "Client_Login_CONTEXT_CREATION_FAILURE", "Client_Login_CONTEXT_CREATION_FAILURE"},
	{L2RC_Client_RegisterAccount_HANDLE_ALREADY_IN_USE, "Client_RegisterAccount_HANDLE_ALREADY_IN_USE", "Client_RegisterAccount_HANDLE_ALREADY_IN_USE"},
	{L2RC_Client_RegisterAccount_REQUIRED_AGE_NOT_MET, "Client_RegisterAccount_REQUIRED_AGE_NOT_MET", "Client_RegisterAccount_REQUIRED_AGE_NOT_MET"},
	{L2RC_Client_RegisterAccount_INVALID_STATE, "Client_RegisterAccount_INVALID_STATE", "Client_RegisterAccount_INVALID_STATE"},
	{L2RC_Client_RegisterAccount_INVALID_COUNTRY, "Client_RegisterAccount_INVALID_COUNTRY", "Client_RegisterAccount_INVALID_COUNTRY"},
	{L2RC_Client_RegisterAccount_INVALID_RACE, "Client_RegisterAccount_INVALID_RACE", "Client_RegisterAccount_INVALID_RACE"},
	{L2RC_Client_RegisterAccount_REQUIRES_CD_KEY, "Client_RegisterAccount_REQUIRES_CD_KEY", "Client_RegisterAccount_REQUIRES_CD_KEY"},
	{L2RC_Client_RegisterAccount_REQUIRES_TITLE, "Client_RegisterAccount_REQUIRES_TITLE", "Client_RegisterAccount_REQUIRES_TITLE"},
	{L2RC_Client_RegisterAccount_CD_KEY_ALREADY_USED, "Client_RegisterAccount_CD_KEY_ALREADY_USED", "Client_RegisterAccount_CD_KEY_ALREADY_USED"},
	{L2RC_Client_RegisterAccount_CD_KEY_STOLEN, "Client_RegisterAccount_CD_KEY_STOLEN", "Client_RegisterAccount_CD_KEY_STOLEN"},
	{L2RC_Client_RegisterAccount_CD_KEY_NOT_USABLE, "Client_RegisterAccount_CD_KEY_NOT_USABLE", "Client_RegisterAccount_CD_KEY_NOT_USABLE"},
	{L2RC_Client_ValidateHandle_HANDLE_ALREADY_IN_USE, "Client_ValidateHandle_HANDLE_ALREADY_IN_USE", "Client_ValidateHandle_HANDLE_ALREADY_IN_USE"},
	{L2RC_Client_GetPasswordByPasswordRecoveryAnswer_BAD_ANSWER, "Client_GetPasswordByPasswordRecoveryAnswer_BAD_ANSWER", "Client_GetPasswordByPasswordRecoveryAnswer_BAD_ANSWER"},
	{L2RC_Client_ChangeHandle_NEW_HANDLE_ALREADY_IN_USE, "Client_ChangeHandle_NEW_HANDLE_ALREADY_IN_USE", "Client_ChangeHandle_NEW_HANDLE_ALREADY_IN_USE"},
	{L2RC_Client_ChangeHandle_HANDLE_NOT_CHANGED, "Client_ChangeHandle_HANDLE_NOT_CHANGED", "Client_ChangeHandle_HANDLE_NOT_CHANGED"},
	{L2RC_Client_ChangeHandle_INVALID_PASSWORD, "Client_ChangeHandle_INVALID_PASSWORD", "Client_ChangeHandle_INVALID_PASSWORD"},
	{L2RC_Client_UpdateAccount_REQUIRED_AGE_NOT_MET, "Client_UpdateAccount_REQUIRED_AGE_NOT_MET", "Client_UpdateAccount_REQUIRED_AGE_NOT_MET"},
	{L2RC_Client_StartIgnore_UNKNOWN_TARGET_HANDLE, "Client_StartIgnore_UNKNOWN_TARGET_HANDLE", "Client_StartIgnore_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Client_StartIgnore_CANNOT_PERFORM_ON_SELF, "Client_StartIgnore_CANNOT_PERFORM_ON_SELF", "Client_StartIgnore_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Client_StartIgnore_ALREADY_IGNORED, "Client_StartIgnore_ALREADY_IGNORED", "Client_StartIgnore_ALREADY_IGNORED"},
	{L2RC_Client_StopIgnore_UNKNOWN_TARGET_HANDLE, "Client_StopIgnore_UNKNOWN_TARGET_HANDLE", "Client_StopIgnore_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Client_StopIgnore_CANNOT_PERFORM_ON_SELF, "Client_StopIgnore_CANNOT_PERFORM_ON_SELF", "Client_StopIgnore_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Client_PerTitleIntegerStorage_TITLE_NOT_IN_USE, "Client_PerTitleIntegerStorage_TITLE_NOT_IN_USE", "Client_PerTitleIntegerStorage_TITLE_NOT_IN_USE"},
	{L2RC_Client_PerTitleIntegerStorage_ROW_EMPTY, "Client_PerTitleIntegerStorage_ROW_EMPTY", "Client_PerTitleIntegerStorage_ROW_EMPTY"},
	{L2RC_Client_PerTitleBinaryStorage_TITLE_NOT_IN_USE, "Client_PerTitleBinaryStorage_TITLE_NOT_IN_USE", "Client_PerTitleBinaryStorage_TITLE_NOT_IN_USE"},
	{L2RC_Client_PerTitleBinaryStorage_ROW_EMPTY, "Client_PerTitleBinaryStorage_ROW_EMPTY", "Client_PerTitleBinaryStorage_ROW_EMPTY"},
	{L2RC_Friends_SendInvite_UNKNOWN_TARGET_HANDLE, "Friends_SendInvite_UNKNOWN_TARGET_HANDLE", "Friends_SendInvite_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Friends_SendInvite_CANNOT_PERFORM_ON_SELF, "Friends_SendInvite_CANNOT_PERFORM_ON_SELF", "Friends_SendInvite_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Friends_SendInvite_ALREADY_SENT_INVITE, "Friends_SendInvite_ALREADY_SENT_INVITE", "Friends_SendInvite_ALREADY_SENT_INVITE"},
	{L2RC_Friends_SendInvite_ALREADY_FRIENDS, "Friends_SendInvite_ALREADY_FRIENDS", "Friends_SendInvite_ALREADY_FRIENDS"},
	{L2RC_Friends_AcceptInvite_UNKNOWN_TARGET_HANDLE, "Friends_AcceptInvite_UNKNOWN_TARGET_HANDLE", "Friends_AcceptInvite_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Friends_AcceptInvite_CANNOT_PERFORM_ON_SELF, "Friends_AcceptInvite_CANNOT_PERFORM_ON_SELF", "Friends_AcceptInvite_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Friends_AcceptInvite_NO_INVITE, "Friends_AcceptInvite_NO_INVITE", "Friends_AcceptInvite_NO_INVITE"},
	{L2RC_Friends_RejectInvite_UNKNOWN_TARGET_HANDLE, "Friends_RejectInvite_UNKNOWN_TARGET_HANDLE", "Friends_RejectInvite_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Friends_RejectInvite_CANNOT_PERFORM_ON_SELF, "Friends_RejectInvite_CANNOT_PERFORM_ON_SELF", "Friends_RejectInvite_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Friends_RejectInvite_NO_INVITE, "Friends_RejectInvite_NO_INVITE", "Friends_RejectInvite_NO_INVITE"},
	{L2RC_Friends_GetFriends_UNKNOWN_TARGET_HANDLE, "Friends_GetFriends_UNKNOWN_TARGET_HANDLE", "Friends_GetFriends_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Friends_Remove_UNKNOWN_TARGET_HANDLE, "Friends_Remove_UNKNOWN_TARGET_HANDLE", "Friends_Remove_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Friends_Remove_CANNOT_PERFORM_ON_SELF, "Friends_Remove_CANNOT_PERFORM_ON_SELF", "Friends_Remove_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Friends_Remove_NOT_FRIENDS, "Friends_Remove_NOT_FRIENDS", "Friends_Remove_NOT_FRIENDS"},
	{L2RC_BookmarkedUsers_Add_UNKNOWN_TARGET_HANDLE, "BookmarkedUsers_Add_UNKNOWN_TARGET_HANDLE", "BookmarkedUsers_Add_UNKNOWN_TARGET_HANDLE"},
	{L2RC_BookmarkedUsers_Add_CANNOT_PERFORM_ON_SELF, "BookmarkedUsers_Add_CANNOT_PERFORM_ON_SELF", "BookmarkedUsers_Add_CANNOT_PERFORM_ON_SELF"},
	{L2RC_BookmarkedUsers_Add_ALREADY_BOOKMARKED, "BookmarkedUsers_Add_ALREADY_BOOKMARKED", "BookmarkedUsers_Add_ALREADY_BOOKMARKED"},
	{L2RC_BookmarkedUsers_Remove_UNKNOWN_TARGET_HANDLE, "BookmarkedUsers_Remove_UNKNOWN_TARGET_HANDLE", "BookmarkedUsers_Remove_UNKNOWN_TARGET_HANDLE"},
	{L2RC_BookmarkedUsers_Remove_CANNOT_PERFORM_ON_SELF, "BookmarkedUsers_Remove_CANNOT_PERFORM_ON_SELF", "BookmarkedUsers_Remove_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Emails_Send_NO_RECIPIENTS, "Emails_Send_NO_RECIPIENTS", "Emails_Send_NO_RECIPIENTS"},
	{L2RC_Emails_Send_CANNOT_PERFORM_ON_SELF, "Emails_Send_CANNOT_PERFORM_ON_SELF", "Emails_Send_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Emails_Delete_UNKNOWN_EMAIL_ID, "Emails_Delete_UNKNOWN_EMAIL_ID", "Emails_Delete_UNKNOWN_EMAIL_ID"},
	{L2RC_Emails_Delete_ALREADY_DELETED, "Emails_Delete_ALREADY_DELETED,", "Emails_Delete_ALREADY_DELETED"},
	{L2RC_Emails_SetStatus_NOTHING_TO_DO, "Emails_SetStatus_NOTHING_TO_DO", "Emails_SetStatus_NOTHING_TO_DO"},
	{L2RC_Emails_SetStatus_UNKNOWN_EMAIL_ID, "Emails_SetStatus_UNKNOWN_EMAIL_ID", "Emails_SetStatus_UNKNOWN_EMAIL_ID"},
	{L2RC_Emails_SetStatus_WAS_DELETED, "Emails_SetStatus_WAS_DELETED", "Emails_SetStatus_WAS_DELETED"},
	{L2RC_Ranking_SubmitMatch_TITLE_NOT_IN_USE, "Ranking_SubmitMatch_TITLE_NOT_IN_USE", "Ranking_SubmitMatch_TITLE_NOT_IN_USE"},
	{L2RC_Ranking_SubmitMatch_NO_PARTICIPANTS, "Ranking_SubmitMatch_NO_PARTICIPANTS", "Ranking_SubmitMatch_NO_PARTICIPANTS"},
	{L2RC_Ranking_GetMatches_TITLE_NOT_IN_USE, "Ranking_GetMatches_TITLE_NOT_IN_USE", "Ranking_GetMatches_TITLE_NOT_IN_USE"},
	{L2RC_Ranking_GetMatchBinaryData_INVALID_MATCH_ID, "Ranking_GetMatchBinaryData_INVALID_MATCH_ID", "Ranking_GetMatchBinaryData_INVALID_MATCH_ID"},
	{L2RC_Ranking_GetTotalScore_TITLE_NOT_IN_USE, "Ranking_GetTotalScore_TITLE_NOT_IN_USE", "Ranking_GetTotalScore_TITLE_NOT_IN_USE"},
	{L2RC_Ranking_WipeScoresForPlayer_TITLE_NOT_IN_USE, "Ranking_WipeScoresForPlayer_TITLE_NOT_IN_USE", "Ranking_WipeScoresForPlayer_TITLE_NOT_IN_USE"},
	{L2RC_Ranking_WipeMatches_TITLE_NOT_IN_USE, "Ranking_WipeMatches_TITLE_NOT_IN_USE", "Ranking_WipeMatches_TITLE_NOT_IN_USE"},
	{L2RC_Ranking_UpdateRating_TITLE_NOT_IN_USE, "Ranking_UpdateRating_TITLE_NOT_IN_USE", "Ranking_UpdateRating_TITLE_NOT_IN_USE"},
	{L2RC_Ranking_UpdateRating_UNKNOWN_TARGET_HANDLE, "Ranking_UpdateRating_UNKNOWN_TARGET_HANDLE", "Ranking_UpdateRating_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Ranking_WipeRatings_TITLE_NOT_IN_USE, "Ranking_WipeRatings_TITLE_NOT_IN_USE", "Ranking_WipeRatings_TITLE_NOT_IN_USE"},
	{L2RC_Ranking_GetRating_TITLE_NOT_IN_USE, "Ranking_GetRating_TITLE_NOT_IN_USE", "Ranking_GetRating_TITLE_NOT_IN_USE"},
	{L2RC_Ranking_GetRating_UNKNOWN_TARGET_HANDLE, "Ranking_GetRating_UNKNOWN_TARGET_HANDLE", "Ranking_GetRating_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Ranking_GetRating_NO_RATING, "Ranking_GetRating_NO_RATING", "Ranking_GetRating_NO_RATING"},
	{L2RC_Clans_Create_CLAN_HANDLE_IN_USE, "Clans_Create_CLAN_HANDLE_IN_USE", "Clans_Create_CLAN_HANDLE_IN_USE"},
	{L2RC_Clans_Create_ALREADY_IN_A_CLAN, "Clans_Create_ALREADY_IN_A_CLAN", "Clans_Create_ALREADY_IN_A_CLAN"},
	{L2RC_Clans_SetProperties_UNKNOWN_CLAN, "Clans_SetProperties_UNKNOWN_CLAN", "Clans_SetProperties_UNKNOWN_CLAN"},
	{L2RC_Clans_SetProperties_MUST_BE_LEADER, "Clans_SetProperties_MUST_BE_LEADER", "Clans_SetProperties_MUST_BE_LEADER"},
	{L2RC_Clans_GetProperties_UNKNOWN_CLAN, "Clans_GetProperties_UNKNOWN_CLAN", "Clans_GetProperties_UNKNOWN_CLAN"},
	{L2RC_Clans_SetMyMemberProperties_UNKNOWN_CLAN, "Clans_SetMyMemberProperties_UNKNOWN_CLAN", "Clans_SetMyMemberProperties_UNKNOWN_CLAN"},
	{L2RC_Clans_SetMyMemberProperties_NOT_IN_CLAN, "Clans_SetMyMemberProperties_NOT_IN_CLAN", "Clans_SetMyMemberProperties_NOT_IN_CLAN"},
	{L2RC_Clans_GrantLeader_UNKNOWN_CLAN, "Clans_GrantLeader_UNKNOWN_CLAN", "Clans_GrantLeader_UNKNOWN_CLAN"},
	{L2RC_Clans_GrantLeader_NOT_IN_CLAN, "Clans_GrantLeader_NOT_IN_CLAN", "Clans_GrantLeader_NOT_IN_CLAN"},
	{L2RC_Clans_GrantLeader_UNKNOWN_TARGET_HANDLE, "Clans_GrantLeader_UNKNOWN_TARGET_HANDLE", "Clans_GrantLeader_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Clans_GrantLeader_MUST_BE_LEADER, "Clans_GrantLeader_MUST_BE_LEADER", "Clans_GrantLeader_MUST_BE_LEADER"},
	{L2RC_Clans_GrantLeader_CANNOT_PERFORM_ON_SELF, "Clans_GrantLeader_CANNOT_PERFORM_ON_SELF", "Clans_GrantLeader_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Clans_GrantLeader_TARGET_NOT_IN_CLAN, "Clans_GrantLeader_TARGET_NOT_IN_CLAN", "Clans_GrantLeader_TARGET_NOT_IN_CLAN"},
	{L2RC_Clans_SetSubleaderStatus_UNKNOWN_CLAN, "Clans_SetSubleaderStatus_UNKNOWN_CLAN", "Clans_SetSubleaderStatus_UNKNOWN_CLAN"},
	{L2RC_Clans_SetSubleaderStatus_NOT_IN_CLAN, "Clans_SetSubleaderStatus_NOT_IN_CLAN", "Clans_SetSubleaderStatus_NOT_IN_CLAN"},
	{L2RC_Clans_SetSubleaderStatus_UNKNOWN_TARGET_HANDLE, "Clans_SetSubleaderStatus_UNKNOWN_TARGET_HANDLE", "Clans_SetSubleaderStatus_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Clans_SetSubleaderStatus_MUST_BE_LEADER, "Clans_SetSubleaderStatus_MUST_BE_LEADER", "Clans_SetSubleaderStatus_MUST_BE_LEADER"},
	{L2RC_Clans_SetSubleaderStatus_TARGET_NOT_IN_CLAN, "Clans_SetSubleaderStatus_TARGET_NOT_IN_CLAN", "Clans_SetSubleaderStatus_TARGET_NOT_IN_CLAN"},
	{L2RC_Clans_SetSubleaderStatus_CANNOT_PERFORM_ON_SELF, "Clans_SetSubleaderStatus_CANNOT_PERFORM_ON_SELF", "Clans_SetSubleaderStatus_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Clans_SetMemberRank_UNKNOWN_CLAN, "Clans_SetMemberRank_UNKNOWN_CLAN", "Clans_SetMemberRank_UNKNOWN_CLAN"},
	{L2RC_Clans_SetMemberRank_NOT_IN_CLAN, "Clans_SetMemberRank_NOT_IN_CLAN", "Clans_SetMemberRank_NOT_IN_CLAN"},
	{L2RC_Clans_SetMemberRank_UNKNOWN_TARGET_HANDLE, "Clans_SetMemberRank_UNKNOWN_TARGET_HANDLE", "Clans_SetMemberRank_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Clans_SetMemberRank_MUST_BE_LEADER, "Clans_SetMemberRank_MUST_BE_LEADER", "Clans_SetMemberRank_MUST_BE_LEADER"},
	{L2RC_Clans_SetMemberRank_CANNOT_PERFORM_ON_SELF, "Clans_SetMemberRank_CANNOT_PERFORM_ON_SELF", "Clans_SetMemberRank_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Clans_SetMemberRank_TARGET_NOT_IN_CLAN, "Clans_SetMemberRank_TARGET_NOT_IN_CLAN", "Clans_SetMemberRank_TARGET_NOT_IN_CLAN"},
	{L2RC_Clans_GetMemberProperties_UNKNOWN_CLAN, "Clans_GetMemberProperties_UNKNOWN_CLAN", "Clans_GetMemberProperties_UNKNOWN_CLAN"},
	{L2RC_Clans_GetMemberProperties_UNKNOWN_TARGET_HANDLE, "Clans_GetMemberProperties_UNKNOWN_TARGET_HANDLE", "Clans_GetMemberProperties_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Clans_GetMemberProperties_TARGET_NOT_IN_CLAN, "Clans_GetMemberProperties_TARGET_NOT_IN_CLAN", "Clans_GetMemberProperties_TARGET_NOT_IN_CLAN"},
	{L2RC_Clans_ChangeHandle_UNKNOWN_CLAN, "Clans_ChangeHandle_UNKNOWN_CLAN", "Clans_ChangeHandle_UNKNOWN_CLAN"},
	{L2RC_Clans_ChangeHandle_NOT_IN_CLAN, "Clans_ChangeHandle_NOT_IN_CLAN", "Clans_ChangeHandle_NOT_IN_CLAN"},
	{L2RC_Clans_ChangeHandle_NEW_HANDLE_IN_USE, "Clans_ChangeHandle_NEW_HANDLE_IN_USE", "Clans_ChangeHandle_NEW_HANDLE_IN_USE"},
	{L2RC_Clans_ChangeHandle_MUST_BE_LEADER, "Clans_ChangeHandle_MUST_BE_LEADER", "Clans_ChangeHandle_MUST_BE_LEADER"},
	{L2RC_Clans_ChangeHandle_HANDLE_NOT_CHANGED, "Clans_ChangeHandle_HANDLE_NOT_CHANGED", "Clans_ChangeHandle_HANDLE_NOT_CHANGED"},
	{L2RC_Clans_Leave_UNKNOWN_CLAN, "Clans_Leave_UNKNOWN_CLAN", "Clans_Leave_UNKNOWN_CLAN"},
	{L2RC_Clans_Leave_NOT_IN_CLAN, "Clans_Leave_NOT_IN_CLAN", "Clans_Leave_NOT_IN_CLAN"},
	{L2RC_Clans_SendJoinInvitation_UNKNOWN_CLAN, "Clans_SendJoinInvitation_UNKNOWN_CLAN", "Clans_SendJoinInvitation_UNKNOWN_CLAN"},
	{L2RC_Clans_SendJoinInvitation_NOT_IN_CLAN, "Clans_SendJoinInvitation_NOT_IN_CLAN", "Clans_SendJoinInvitation_NOT_IN_CLAN"},
	{L2RC_Clans_SendJoinInvitation_UNKNOWN_TARGET_HANDLE, "Clans_SendJoinInvitation_UNKNOWN_TARGET_HANDLE", "Clans_SendJoinInvitation_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Clans_SendJoinInvitation_MUST_BE_LEADER_OR_SUBLEADER, "Clans_SendJoinInvitation_MUST_BE_LEADER_OR_SUBLEADER", "Clans_SendJoinInvitation_MUST_BE_LEADER_OR_SUBLEADER"},
	{L2RC_Clans_SendJoinInvitation_REQUEST_ALREADY_PENDING, "Clans_SendJoinInvitation_REQUEST_ALREADY_PENDING", "Clans_SendJoinInvitation_REQUEST_ALREADY_PENDING"},
	{L2RC_Clans_SendJoinInvitation_CANNOT_PERFORM_ON_SELF, "Clans_SendJoinInvitation_CANNOT_PERFORM_ON_SELF", "Clans_SendJoinInvitation_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Clans_SendJoinInvitation_TARGET_ALREADY_REQUESTED, "Clans_SendJoinInvitation_TARGET_ALREADY_REQUESTED", "Clans_SendJoinInvitation_TARGET_ALREADY_REQUESTED"},
	{L2RC_Clans_SendJoinInvitation_TARGET_IS_BANNED, "Clans_SendJoinInvitation_TARGET_IS_BANNED", "Clans_SendJoinInvitation_TARGET_IS_BANNED"},
	{L2RC_Clans_SendJoinInvitation_TARGET_ALREADY_IN_CLAN, "Clans_SendJoinInvitation_TARGET_ALREADY_IN_CLAN", "Clans_SendJoinInvitation_TARGET_ALREADY_IN_CLAN"},
	{L2RC_Clans_WithdrawJoinInvitation_UNKNOWN_CLAN, "Clans_WithdrawJoinInvitation_UNKNOWN_CLAN", "Clans_WithdrawJoinInvitation_UNKNOWN_CLAN"},
	{L2RC_Clans_WithdrawJoinInvitation_NO_SUCH_INVITATION_EXISTS, "Clans_WithdrawJoinInvitation_NO_SUCH_INVITATION_EXISTS", "Clans_WithdrawJoinInvitation_NO_SUCH_INVITATION_EXISTS"},
	{L2RC_Clans_WithdrawJoinInvitation_MUST_BE_LEADER_OR_SUBLEADER, "Clans_WithdrawJoinInvitation_MUST_BE_LEADER_OR_SUBLEADER", "Clans_WithdrawJoinInvitation_MUST_BE_LEADER_OR_SUBLEADER"},
	{L2RC_Clans_WithdrawJoinInvitation_UNKNOWN_TARGET_HANDLE, "Clans_WithdrawJoinInvitation_UNKNOWN_TARGET_HANDLE", "Clans_WithdrawJoinInvitation_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Clans_WithdrawJoinInvitation_CANNOT_PERFORM_ON_SELF, "Clans_WithdrawJoinInvitation_CANNOT_PERFORM_ON_SELF", "Clans_WithdrawJoinInvitation_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Clans_AcceptJoinInvitation_ALREADY_IN_CLAN, "Clans_AcceptJoinInvitation_ALREADY_IN_CLAN", "Clans_AcceptJoinInvitation_ALREADY_IN_CLAN"},
	{L2RC_Clans_AcceptJoinInvitation_ALREADY_IN_DIFFERENT_CLAN, "Clans_AcceptJoinInvitation_ALREADY_IN_DIFFERENT_CLAN", "Clans_AcceptJoinInvitation_ALREADY_IN_DIFFERENT_CLAN"},
	{L2RC_Clans_AcceptJoinInvitation_UNKNOWN_CLAN, "Clans_AcceptJoinInvitation_UNKNOWN_CLAN", "Clans_AcceptJoinInvitation_UNKNOWN_CLAN"},
	{L2RC_Clans_AcceptJoinInvitation_NOT_IN_CLAN, "Clans_AcceptJoinInvitation_NOT_IN_CLAN", "Clans_AcceptJoinInvitation_NOT_IN_CLAN"},
	{L2RC_Clans_AcceptJoinInvitation_NO_SUCH_INVITATION_EXISTS, "Clans_AcceptJoinInvitation_NO_SUCH_INVITATION_EXISTS", "Clans_AcceptJoinInvitation_NO_SUCH_INVITATION_EXISTS"},
	{L2RC_Clans_RejectJoinInvitation_UNKNOWN_CLAN, "Clans_RejectJoinInvitation_UNKNOWN_CLAN", "Clans_RejectJoinInvitation_UNKNOWN_CLAN"},
	{L2RC_Clans_RejectJoinInvitation_NO_SUCH_INVITATION_EXISTS, "Clans_RejectJoinInvitation_NO_SUCH_INVITATION_EXISTS", "Clans_RejectJoinInvitation_NO_SUCH_INVITATION_EXISTS"},
	{L2RC_Clans_DownloadInvitationList_UNKNOWN_CLAN, "Clans_DownloadInvitationList_UNKNOWN_CLAN", "Clans_DownloadInvitationList_UNKNOWN_CLAN"},
	{L2RC_Clans_SendJoinRequest_UNKNOWN_CLAN, "Clans_SendJoinRequest_UNKNOWN_CLAN", "Clans_SendJoinRequest_UNKNOWN_CLAN"},
	{L2RC_Clans_SendJoinRequest_REQUEST_ALREADY_PENDING, "Clans_SendJoinRequest_REQUEST_ALREADY_PENDING", "Clans_SendJoinRequest_REQUEST_ALREADY_PENDING"},
	{L2RC_Clans_SendJoinRequest_ALREADY_IN_CLAN, "Clans_SendJoinRequest_ALREADY_IN_CLAN", "Clans_SendJoinRequest_ALREADY_IN_CLAN"},
	{L2RC_Clans_SendJoinRequest_BANNED, "Clans_SendJoinRequest_BANNED", "Clans_SendJoinRequest_BANNED"},
	{L2RC_Clans_SendJoinRequest_ALREADY_INVITED, "Clans_SendJoinRequest_ALREADY_INVITED", "Clans_SendJoinRequest_ALREADY_INVITED"},
	{L2RC_Clans_WithdrawJoinRequest_UNKNOWN_CLAN, "Clans_WithdrawJoinRequest_UNKNOWN_CLAN", "Clans_WithdrawJoinRequest_UNKNOWN_CLAN"},
	{L2RC_Clans_WithdrawJoinRequest_ALREADY_IN_CLAN, "Clans_WithdrawJoinRequest_ALREADY_IN_CLAN", "Clans_WithdrawJoinRequest_ALREADY_IN_CLAN"},
	{L2RC_Clans_WithdrawJoinRequest_NO_SUCH_INVITATION_EXISTS, "Clans_WithdrawJoinRequest_NO_SUCH_INVITATION_EXISTS", "Clans_WithdrawJoinRequest_NO_SUCH_INVITATION_EXISTS"},
	{L2RC_Clans_AcceptJoinRequest_UNKNOWN_CLAN, "Clans_AcceptJoinRequest_UNKNOWN_CLAN", "Clans_AcceptJoinRequest_UNKNOWN_CLAN"},
	{L2RC_Clans_AcceptJoinRequest_NOT_IN_CLAN, "Clans_AcceptJoinRequest_NOT_IN_CLAN", "Clans_AcceptJoinRequest_NOT_IN_CLAN"},
	{L2RC_Clans_AcceptJoinRequest_MUST_BE_LEADER_OR_SUBLEADER, "Clans_AcceptJoinRequest_MUST_BE_LEADER_OR_SUBLEADER", "Clans_AcceptJoinRequest_MUST_BE_LEADER_OR_SUBLEADER"},
	{L2RC_Clans_AcceptJoinRequest_UNKNOWN_TARGET_HANDLE, "Clans_AcceptJoinRequest_UNKNOWN_TARGET_HANDLE", "Clans_AcceptJoinRequest_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Clans_AcceptJoinRequest_CANNOT_PERFORM_ON_SELF, "Clans_AcceptJoinRequest_CANNOT_PERFORM_ON_SELF", "Clans_AcceptJoinRequest_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Clans_AcceptJoinRequest_TARGET_ALREADY_IN_CLAN, "Clans_AcceptJoinRequest_TARGET_ALREADY_IN_CLAN", "Clans_AcceptJoinRequest_TARGET_ALREADY_IN_CLAN"},
	{L2RC_Clans_AcceptJoinRequest_TARGET_ALREADY_IN_DIFFERENT_CLAN, "Clans_AcceptJoinRequest_TARGET_ALREADY_IN_DIFFERENT_CLAN", "Clans_AcceptJoinRequest_TARGET_ALREADY_IN_DIFFERENT_CLAN"},
	{L2RC_Clans_AcceptJoinRequest_TARGET_IS_BANNED, "Clans_AcceptJoinRequest_TARGET_IS_BANNED", "Clans_AcceptJoinRequest_TARGET_IS_BANNED"},
	{L2RC_Clans_AcceptJoinRequest_REQUEST_NOT_PENDING, "Clans_AcceptJoinRequest_REQUEST_NOT_PENDING", "Clans_AcceptJoinRequest_REQUEST_NOT_PENDING"},
	{L2RC_Clans_RejectJoinRequest_UNKNOWN_CLAN, "Clans_RejectJoinRequest_UNKNOWN_CLAN", "Clans_RejectJoinRequest_UNKNOWN_CLAN"},
	{L2RC_Clans_RejectJoinRequest_NOT_IN_CLAN, "Clans_RejectJoinRequest_NOT_IN_CLAN", "Clans_RejectJoinRequest_NOT_IN_CLAN"},
	{L2RC_Clans_RejectJoinRequest_MUST_BE_LEADER_OR_SUBLEADER, "Clans_RejectJoinRequest_MUST_BE_LEADER_OR_SUBLEADER", "Clans_RejectJoinRequest_MUST_BE_LEADER_OR_SUBLEADER"},
	{L2RC_Clans_RejectJoinRequest_REQUESTING_USER_HANDLE_UNKNOWN, "Clans_RejectJoinRequest_REQUESTING_USER_HANDLE_UNKNOWN", "Clans_RejectJoinRequest_REQUESTING_USER_HANDLE_UNKNOWN"},
	{L2RC_Clans_RejectJoinRequest_NO_SUCH_INVITATION_EXISTS, "Clans_RejectJoinRequest_NO_SUCH_INVITATION_EXISTS", "Clans_RejectJoinRequest_NO_SUCH_INVITATION_EXISTS"},
	{L2RC_Clans_KickAndBlacklistUser_UNKNOWN_CLAN, "Clans_KickAndBlacklistUser_UNKNOWN_CLAN", "Clans_KickAndBlacklistUser_UNKNOWN_CLAN"},
	{L2RC_Clans_KickAndBlacklistUser_NOT_IN_CLAN, "Clans_KickAndBlacklistUser_NOT_IN_CLAN", "Clans_KickAndBlacklistUser_NOT_IN_CLAN"},
	{L2RC_Clans_KickAndBlacklistUser_UNKNOWN_TARGET_HANDLE, "Clans_KickAndBlacklistUser_UNKNOWN_TARGET_HANDLE", "Clans_KickAndBlacklistUser_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Clans_KickAndBlacklistUser_MUST_BE_LEADER_OR_SUBLEADER, "Clans_KickAndBlacklistUser_MUST_BE_LEADER_OR_SUBLEADER", "Clans_KickAndBlacklistUser_MUST_BE_LEADER_OR_SUBLEADER"},
	{L2RC_Clans_KickAndBlacklistUser_ALREADY_BLACKLISTED, "Clans_KickAndBlacklistUser_ALREADY_BLACKLISTED", "Clans_KickAndBlacklistUser_ALREADY_BLACKLISTED"},
	{L2RC_Clans_KickAndBlacklistUser_CANNOT_PERFORM_ON_SELF, "Clans_KickAndBlacklistUser_CANNOT_PERFORM_ON_SELF", "Clans_KickAndBlacklistUser_CANNOT_PERFORM_ON_SELF"},
	{L2RC_Clans_KickAndBlacklistUser_CANNOT_PERFORM_ON_LEADER, "Clans_KickAndBlacklistUser_CANNOT_PERFORM_ON_LEADER", "Clans_KickAndBlacklistUser_CANNOT_PERFORM_ON_LEADER"},
	{L2RC_Clans_UnblacklistUser_UNKNOWN_CLAN, "Clans_UnblacklistUser_UNKNOWN_CLAN", "Clans_UnblacklistUser_UNKNOWN_CLAN"},
	{L2RC_Clans_UnblacklistUser_NOT_IN_CLAN, "Clans_UnblacklistUser_NOT_IN_CLAN", "Clans_UnblacklistUser_NOT_IN_CLAN"},
	{L2RC_Clans_UnblacklistUser_UNKNOWN_TARGET_HANDLE, "Clans_UnblacklistUser_UNKNOWN_TARGET_HANDLE", "Clans_UnblacklistUser_UNKNOWN_TARGET_HANDLE"},
	{L2RC_Clans_UnblacklistUser_MUST_BE_LEADER_OR_SUBLEADER, "Clans_UnblacklistUser_MUST_BE_LEADER_OR_SUBLEADER", "Clans_UnblacklistUser_MUST_BE_LEADER_OR_SUBLEADER"},
	{L2RC_Clans_UnblacklistUser_NOT_BLACKLISTED, "Clans_UnblacklistUser_NOT_BLACKLISTED", "Clans_UnblacklistUser_NOT_BLACKLISTED"},
	{L2RC_Clans_GetBlacklist_UNKNOWN_CLAN, "Clans_GetBlacklist_UNKNOWN_CLAN", "Clans_GetBlacklist_UNKNOWN_CLAN"},
	{L2RC_Clans_GetMembers_UNKNOWN_CLAN, "Clans_GetMembers_UNKNOWN_CLAN", "Clans_GetMembers_UNKNOWN_CLAN"},
	{L2RC_Clans_CreateBoard_UNKNOWN_CLAN, "Clans_CreateBoard_UNKNOWN_CLAN", "Clans_CreateBoard_UNKNOWN_CLAN"},
	{L2RC_Clans_CreateBoard_NOT_IN_CLAN, "Clans_CreateBoard_NOT_IN_CLAN", "Clans_CreateBoard_NOT_IN_CLAN"},
	{L2RC_Clans_CreateBoard_MUST_BE_LEADER_OR_SUBLEADER, "Clans_CreateBoard_MUST_BE_LEADER_OR_SUBLEADER", "Clans_CreateBoard_MUST_BE_LEADER_OR_SUBLEADER"},
	{L2RC_Clans_CreateBoard_BOARD_ALREADY_EXISTS, "Clans_CreateBoard_BOARD_ALREADY_EXISTS", "Clans_CreateBoard_BOARD_ALREADY_EXISTS"},
	{L2RC_Clans_DestroyBoard_UNKNOWN_CLAN, "Clans_DestroyBoard_UNKNOWN_CLAN", "Clans_DestroyBoard_UNKNOWN_CLAN"},
	{L2RC_Clans_DestroyBoard_NOT_IN_CLAN, "Clans_DestroyBoard_NOT_IN_CLAN", "Clans_DestroyBoard_NOT_IN_CLAN"},
	{L2RC_Clans_DestroyBoard_MUST_BE_LEADER_OR_SUBLEADER, "Clans_DestroyBoard_MUST_BE_LEADER_OR_SUBLEADER", "Clans_DestroyBoard_MUST_BE_LEADER_OR_SUBLEADER"},
	{L2RC_Clans_DestroyBoard_BOARD_DOES_NOT_EXIST, "Clans_DestroyBoard_BOARD_DOES_NOT_EXIST", "Clans_DestroyBoard_BOARD_DOES_NOT_EXIST"},
	{L2RC_Clans_CreateNewTopic_UNKNOWN_CLAN, "Clans_CreateNewTopic_UNKNOWN_CLAN", "Clans_CreateNewTopic_UNKNOWN_CLAN"},
	{L2RC_Clans_CreateNewTopic_BOARD_DOES_NOT_EXIST, "Clans_CreateNewTopic_BOARD_DOES_NOT_EXIST", "Clans_CreateNewTopic_BOARD_DOES_NOT_EXIST"},
	{L2RC_Clans_CreateNewTopic_PERMISSION_DENIED, "Clans_CreateNewTopic_PERMISSION_DENIED", "Clans_CreateNewTopic_PERMISSION_DENIED"},
	{L2RC_Clans_ReplyToTopic_UNKNOWN_POST_ID, "Clans_ReplyToTopic_UNKNOWN_POST_ID", "Clans_ReplyToTopic_UNKNOWN_POST_ID"},
	{L2RC_Clans_ReplyToTopic_PERMISSION_DENIED, "Clans_ReplyToTopic_PERMISSION_DENIED", "Clans_ReplyToTopic_PERMISSION_DENIED"},
	{L2RC_Clans_RemovePost_UNKNOWN_POST_ID, "Clans_RemovePost_UNKNOWN_POST_ID", "Clans_RemovePost_UNKNOWN_POST_ID"},
	{L2RC_Clans_RemovePost_NOT_IN_CLAN, "Clans_RemovePost_NOT_IN_CLAN", "Clans_RemovePost_NOT_IN_CLAN"},
	{L2RC_Clans_RemovePost_MUST_BE_LEADER_OR_SUBLEADER, "Clans_RemovePost_MUST_BE_LEADER_OR_SUBLEADER", "Clans_RemovePost_MUST_BE_LEADER_OR_SUBLEADER"},
	{L2RC_Clans_GetBoards_UNKNOWN_CLAN, "Clans_GetBoards_UNKNOWN_CLAN", "Clans_GetBoards_UNKNOWN_CLAN"},
	{L2RC_Clans_GetTopics_UNKNOWN_CLAN, "Clans_GetTopics_UNKNOWN_CLAN", "Clans_GetTopics_UNKNOWN_CLAN"},
	{L2RC_Clans_GetTopics_BOARD_DOES_NOT_EXIST, "Clans_GetTopics_BOARD_DOES_NOT_EXIST", "Clans_GetTopics_BOARD_DOES_NOT_EXIST"},
	{L2RC_Clans_GetPosts_UNKNOWN_POST_ID, "Clans_GetPosts_UNKNOWN_POST_ID", "Clans_GetPosts_UNKNOWN_POST_ID"},
	{L2RC_Console_JoinLobby_LOBBY_FULL, "Console_JoinLobby_LOBBY_FULL", "Console_JoinLobby_LOBBY_FULL"},
	{L2RC_Console_JoinLobby_NO_SUCH_LOBBY, "Console_JoinLobby_NO_SUCH_LOBBY", "Console_JoinLobby_NO_SUCH_LOBBY"},
	{L2RC_Console_GetRoomDetails_NO_ROOMS_FOUND, "Console_GetRoomDetails_NO_ROOMS_FOUND", "Console_GetRoomDetails_NO_ROOMS_FOUND"},
	{L2RC_Console_SignIntoRoom_NO_USERS, "Console_SignIntoRoom_NO_USERS", "Console_SignIntoRoom_NO_USERS"},
	{L2RC_Console_SignIntoRoom_NO_SUCH_ROOM, "Console_SignIntoRoom_NO_SUCH_ROOM", "Console_SignIntoRoom_NO_SUCH_ROOM"},
	{L2RC_Console_SignIntoRoom_JOIN_ILLEGAL, "Console_SignIntoRoom_JOIN_ILLEGAL", "Console_SignIntoRoom_JOIN_ILLEGAL"},
	{L2RC_Console_SignIntoRoom_REMOTE_JOIN_FAILED, "Console_SignIntoRoom_REMOTE_JOIN_FAILED", "Console_SignIntoRoom_REMOTE_JOIN_FAILED"},
	{L2RC_Console_JoinRoom_ROOM_FULL, "Console_JoinRoom_ROOM_FULL", "Console_JoinRoom_ROOM_FULL"},
	{L2RC_Console_JoinRoom_WRONG_PASSWORD, "Console_JoinRoom_WRONG_PASSWORD", "Console_JoinRoom_WRONG_PASSWORD"},
	{L2RC_Console_JoinRoom_NO_SUCH_ROOM, "Console_JoinRoom_NO_SUCH_ROOM", "Console_JoinRoom_NO_SUCH_ROOM"},
	{L2RC_Console_JoinRoom_SERVER_ERROR_BLOCKED, "Console_JoinRoom_SERVER_ERROR_BLOCKED", "Console_JoinRoom_SERVER_ERROR_BLOCKED"},
	{L2RC_Console_JoinRoom_ALREADY_IN_ROOM, "Console_JoinRoom_ALREADY_IN_ROOM", "Console_JoinRoom_ALREADY_IN_ROOM"},
	{L2RC_Console_JoinRoom_CONNECTION_TIMEOUT, "Console_JoinRoom_CONNECTION_TIMEOUT", "Console_JoinRoom_CONNECTION_TIMEOUT"},
	{L2RC_Console_ModifyRoom_NO_SUCH_ROOM, "Console_ModifyRoom_NO_SUCH_ROOM", "Console_ModifyRoom_NO_SUCH_ROOM"},
	{L2RC_Console_ModifyRoom_MUST_BE_HOST, "Console_ModifyRoom_MUST_BE_HOST", "Console_ModifyRoom_MUST_BE_HOST"},
	{L2RC_Console_UpdateRoomParameters_ROOM_WAS_DELETED_WHILE_IN_PROGRESS, "Console_UpdateRoomParameters_ROOM_WAS_DELETED_WHILE_IN_PROGRESS", "Console_UpdateRoomParameters_ROOM_WAS_DELETED_WHILE_IN_PROGRESS"},
	{L2RC_Console_LeaveRoom_NO_SUCH_ROOM, "Console_LeaveRoom_NO_SUCH_ROOM", "Console_LeaveRoom_NO_SUCH_ROOM"},
	{L2RC_Console_LeaveRoom_ROOM_WAS_DELETED_WHILE_IN_PROGRESS, "Console_LeaveRoom_ROOM_WAS_DELETED_WHILE_IN_PROGRESS", "Console_LeaveRoom_ROOM_WAS_DELETED_WHILE_IN_PROGRESS"},
	{L2RC_Console_StartGame_NO_SUCH_ROOM, "Console_StartGame_NO_SUCH_ROOM", "Console_StartGame_NO_SUCH_ROOM"},
	{L2RC_Console_StartGame_MUST_BE_HOST, "Console_StartGame_MUST_BE_HOST", "Console_StartGame_MUST_BE_HOST"},
	{L2RC_Console_StartGame_ALREADY_STARTED, "Console_StartGame_ALREADY_STARTED", "Console_StartGame_ALREADY_STARTED"},
	{L2RC_Console_StartGame_ROOM_WAS_DELETED_WHILE_IN_PROGRESS, "Console_StartGame_ROOM_WAS_DELETED_WHILE_IN_PROGRESS", "Console_StartGame_ROOM_WAS_DELETED_WHILE_IN_PROGRESS"},
	{L2RC_Console_EndGame_NO_SUCH_ROOM, "Console_EndGame_NO_SUCH_ROOM", "Console_EndGame_NO_SUCH_ROOM"},
	{L2RC_Console_EndGame_MUST_BE_HOST, "Console_EndGame_MUST_BE_HOST", "Console_EndGame_MUST_BE_HOST"},
	{L2RC_Console_EndGame_NOT_STARTED, "Console_EndGame_NOT_STARTED", "Console_EndGame_NOT_STARTED"},
	{L2RC_Console_EndGame_ROOM_WAS_DELETED_WHILE_IN_PROGRESS, "Console_EndGame_ROOM_WAS_DELETED_WHILE_IN_PROGRESS", "Console_EndGame_ROOM_WAS_DELETED_WHILE_IN_PROGRESS"},
	{L2RC_Notification_Console_CableDisconnected, "Notification_Console_CableDisconnected", "Notification_Console_CableDisconnected"},
	{L2RC_Notification_ContextError_SignedOut, "Notification_ContextError_SignedOut", "Notification_ContextError_SignedOut"},
	{L2RC_Notification_ContextError_SystemError, "Notification_ContextError_SystemError", "Notification_ContextError_SystemError"},
};
const char *Lobby2ResultCodeDescription::ToEnglish(Lobby2ResultCode result)
{
	RakAssert(resultCodeDescriptions[result].resultCode==result);
	return resultCodeDescriptions[result].englishDesc;
}
const char *Lobby2ResultCodeDescription::ToEnum(Lobby2ResultCode result)
{
	RakAssert(resultCodeDescriptions[result].resultCode==result);
	return resultCodeDescriptions[result].enumDesc;
}
void Lobby2ResultCodeDescription::Validate(void)
{
	unsigned int i;
	for (i=0; i < L2RC_COUNT; i++)
	{
		RakAssert(resultCodeDescriptions[i].resultCode==(Lobby2ResultCode)i);
	}
}
