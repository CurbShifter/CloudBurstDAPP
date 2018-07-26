/*
CloudBurst DAPP
Copyright (C) 2018  CurbShifter

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BURSTAPI_H_INCLUDED
#define BURSTAPI_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "./crypto/Crypto.hpp"

// Search range should be 32767 as absolute max. but 1 day should be enough
#define SEARCH_RANGE_MINUTES (24*60)
#define PREFIX_CB_RS "CLOUD"
#define PERCENT_FEE 1

typedef bool(*CheckThreadShouldExit_ptr)(const void* context, float progress);

class BurstAPI
{
public:
	struct Balance
	{
		String unconfirmedBalanceNQT;
		String guaranteedBalanceNQT;
		String effectiveBalanceNXT;
		String forgedBalanceNQT;
		String balanceNQT;
		String requestProcessingTime;
	};
	
	BurstAPI(String hostUrl = "https://wallet.dev.burst-test.net:8125/"); // default on testnet
	~BurstAPI();

	StringArray toReedSolomonEncoding(MemoryBlock mb);
	MemoryBlock fromReedSolomonEncoding(StringArray encoded_strings);

	Array<StringArray> SetAttachmentData(MemoryBlock data);
	MemoryBlock GetAttachmentData(var jsonStructure, int &length_match, unsigned int &crc16_full_match);

	void SetHost(String hostUrl) { host = hostUrl; };

	void SetAccountRS(String reedSolomonIn);
	void SetAccount(String accountID);
	void SetSecretPhrase(String passphrase);
	
	var GetAccount();
	var GetAccountId();
	var GetAccountTransactionIds(String reedSolomonIn = String::empty);
	var GetBalance();

	var GetTransaction(String transaction);
	var SendMoneyMulti(StringArray recipients, StringArray amountsNQT, String feeNQT, String deadlineMinutes);
	var SendMoneyMultiSame(StringArray recipients, String amountNQT, String feeNQT, String deadlineMinutes);
	var SendMoney(String recipient, String amountNQT, String feeNQT, String deadlineMinutes);
	var SignAndBroadcast(String unsignedTransactionBytesStr);

	var longConvert(String id);
	var rsConvert(String account);

	Balance GetBalance(var jsonStructure);
	bool ScrapeAccountTransactions(Array<MemoryBlock> &results, Array<String> &timecodes, String downloadTransactionID, CheckThreadShouldExit_ptr CheckThreadShouldExit, const void* context);
	juce::var GetJSON(String urlStr);

	String getReedSolomon() { return reedSolomon; };

//	MemoryBlock TestAccountTransactions(StringArray txids, Array<StringArray> attachmentDatas);
//	void TestTransaction();
private:
	Crypto crypto;

	String host;
	String accountID;
	String reedSolomon;
	String secretPhrase;
	String pubKey_64HEX;
};

#endif
