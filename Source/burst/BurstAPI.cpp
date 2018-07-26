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

#include "BurstAPI.h"
#include <boost/crc.hpp>


BurstAPI::BurstAPI(String hostUrl) : host(hostUrl)
{
}

BurstAPI::~BurstAPI()
{
}

var BurstAPI::GetJSON(String urlStr)
{
	String url = urlStr;
	String json = URL(url).readEntireTextStream(true);
	var jsonStructure;
	Result r = JSON::parse(json, jsonStructure);
	return jsonStructure;
}

void BurstAPI::SetAccount(String accountID)
{
	var jsonStructure = rsConvert(accountID);
	reedSolomon = jsonStructure["accountRS"].toString();
	this->accountID = accountID;
}

void BurstAPI::SetAccountRS(String reedSolomonIn)
{
	reedSolomon = reedSolomonIn;
	if (reedSolomon.startsWith("BURST-") == false)
		reedSolomon = ("BURST-") + reedSolomon;

	var jsonStructure = GetAccount();
	accountID = jsonStructure["account"].toString();
}

void BurstAPI::SetSecretPhrase(String passphrase)
{
	secretPhrase = passphrase;
	
	// get the public key
	MemoryBlock pubKey;
	crypto.getPublicKey(MemoryBlock(secretPhrase.toUTF8(), secretPhrase.getNumBytesAsUTF8()), pubKey);
	pubKey_64HEX = String::toHexString(pubKey.getData(), pubKey.getSize()).removeCharacters(" ");
	
	// get the RS
	// take SHA256 of pubKey
	SHA256 shapub(pubKey);
	MemoryBlock shapubMem = shapub.getRawData();
	String srt = String::toHexString(shapubMem.getData(), shapubMem.getSize()).removeCharacters(" ");

	MemoryBlock shapubMemSwapped(shapubMem.getData(), 8);
	BigInteger bi;
	bi.loadFromMemoryBlock(shapubMemSwapped);
	accountID = bi.toString(10, 1);
	SetAccount(accountID);
}

var BurstAPI::GetAccount()
{
	return GetJSON(host + "burst?requestType=getAccount&account=" + reedSolomon);
}
var BurstAPI::GetAccountId()
{
	return GetJSON(host + "burst?requestType=getAccountId&publicKey=" + pubKey_64HEX);
}

var BurstAPI::GetAccountTransactionIds(String reedSolomonIn)
{
	return GetJSON(host + "burst?requestType=getAccountTransactionIds&account=" + (reedSolomonIn.isNotEmpty() ? reedSolomonIn : reedSolomon));
}

var BurstAPI::GetBalance()
{
	return GetJSON(host + "burst?requestType=getBalance&account=" + reedSolomon);
}

var BurstAPI::GetTransaction(String transaction)
{
	return GetJSON(host + "burst?requestType=getTransaction&transaction=" + transaction);
}

var BurstAPI::SendMoneyMulti(StringArray recipients, StringArray amountsNQT, String feeNQT, String deadlineMinutes)
{
	StringArray recipientStrArray;
	for (int i = 0; i < jmin<int>(recipients.size(), amountsNQT.size(), 64); i++) // up to 64 recipients
	{
		recipientStrArray.add(recipients[i] + ":" + amountsNQT[i]);
	}
	
	String recipientStr = recipientStrArray.joinIntoString(";");
	
	String url(host + "burst?requestType=sendMoneyMulti&publicKey=" + pubKey_64HEX + "&recipients=" + recipientStr + "&feeNQT=" + feeNQT + "&deadline=" + deadlineMinutes);
	var unsignedTX = GetJSON(url);
	String unsignedTransactionBytesStr = unsignedTX["unsignedTransactionBytes"].toString();

	// sign and broadcast tx bytes
	return SignAndBroadcast(unsignedTransactionBytesStr);
}

var BurstAPI::SendMoneyMultiSame(StringArray recipients, String amountNQT, String feeNQT, String deadlineMinutes)
{
	String recipientStr = recipients.joinIntoString(";");
	//String url(host + "burst?requestType=sendMoneyMultiSame&secretPhrase=" + URL::addEscapeChars(secretPhrase, false, true) + "&recipients=" + recipientStr + "&amountNQT=" + amountNQT + "&feeNQT=" + feeNQT + "&deadline=" + deadlineMinutes);
	String url(host + "burst?requestType=sendMoneyMultiSame&publicKey=" + pubKey_64HEX + "&recipients=" + recipientStr + "&amountNQT=" + amountNQT + "&feeNQT=" + feeNQT + "&deadline=" + deadlineMinutes);
	var unsignedTX = GetJSON(url);
	String unsignedTransactionBytesStr = unsignedTX["unsignedTransactionBytes"].toString();

	// sign and broadcast tx bytes
	return SignAndBroadcast(unsignedTransactionBytesStr);
}

var BurstAPI::SendMoney(String recipient, String amountNQT, String feeNQT, String deadlineMinutes)
{
	// make the url and send the data
	String url(host + "burst?requestType=sendMoney&publicKey=" + pubKey_64HEX + "&recipient=" + recipient + "&amountNQT=" + amountNQT + "&feeNQT=" + feeNQT + "&deadline=" + deadlineMinutes);
	var unsignedTX = GetJSON(url); // transactionJSON without a signature
	String unsignedTransactionBytesStr = unsignedTX["unsignedTransactionBytes"].toString();

	// sign and broadcast tx bytes
	return SignAndBroadcast(unsignedTransactionBytesStr);
}

var BurstAPI::SignAndBroadcast(String unsignedTransactionBytesStr)
{
	if (secretPhrase.isEmpty())
		return var::null;

	MemoryBlock unsignedTransactionBytes;
	unsignedTransactionBytes.loadFromHexString(unsignedTransactionBytesStr);

	if (unsignedTransactionBytes.getSize() > 0)// && transactionJSON["senderPublicKey"].toString().isNotEmpty())
	{
		// get the prepared but unsigned bytes, and sign it locally with the pass phrase
		// can test with signTransaction https://burstwiki.org/wiki/The_Burst_API#Sign_Transaction
		MemoryBlock signature = crypto.sign(unsignedTransactionBytes, MemoryBlock(secretPhrase.toUTF8(), secretPhrase.getNumBytesAsUTF8()));
		MemoryBlock signedTransactionBytes(unsignedTransactionBytes);
		signedTransactionBytes.copyFrom(signature.getData(), 32 * 3, signature.getSize());
		String transactionBytesHex = String::toHexString(signedTransactionBytes.getData(), signedTransactionBytes.getSize()).removeCharacters(" ");

		// for debug
	//	URL signUrl(host + "burst?requestType=signTransaction&unsignedTransactionBytes=" + unsignedTransactionBytesStr + "&secretPhrase=" + secretPhraseEscapeChars);
	//	String signUrlRes = signUrl.readEntireTextStream(true);
	//	String transactionBytes; // the final transactionBytes. unsignedTransactionBytesStr + transactionBytesHex

		// send the signed transaction, POST only.
		URL url(host + "burst");
		String post("requestType=broadcastTransaction" + (transactionBytesHex.isNotEmpty() ? "&transactionBytes=" + transactionBytesHex : ""));
			// + (transactionJSON["senderPublicKey"].toString().isNotEmpty() ? "&transactionJSON=" + JSON::toString(transactionJSON, true).removeCharacters(" ") : ""));
		
		URL postURL = url.withPOSTData(MemoryBlock(post.toUTF8(), post.getNumBytesAsUTF8()));
		String json = postURL.readEntireTextStream(true);
		var resultTX;
		Result r = JSON::parse(json, resultTX);

		return resultTX;
	}
	return var::null;
}

var BurstAPI::longConvert(String id)
{
	return GetJSON(host + "burst?requestType=longConvert&id=" + id);
}

var BurstAPI::rsConvert(String account)
{
	return GetJSON(host + "burst?requestType=rsConvert&account=" + account);
}

bool BurstAPI::ScrapeAccountTransactions(Array<MemoryBlock> &attachmentDatas, Array<String> &timecodes, String downloadTransactionID, CheckThreadShouldExit_ptr CheckThreadShouldExit, const void* context)
{
	downloadTransactionID = downloadTransactionID.toUpperCase();
	if (downloadTransactionID.containsAnyOf("ABCDEFGHIJKLMNOPQRSTUVWXYZ")) // a reed solomon or numerical?
	{
		String converted(downloadTransactionID.replace(PREFIX_CB_RS "-", ""));
		if (converted.startsWith("BURST-") == false)
			converted = "BURST-" + converted;
		downloadTransactionID = rsConvert(converted)["account"];
	}
	float progress = 0.f;

	bool cancel = CheckThreadShouldExit(context, progress);

	// get transaction with downloadTransactionID
	// read sender address
	var baseTransactionContents = GetTransaction(downloadTransactionID);
	String reedSolomonIn = baseTransactionContents["senderRS"];
	
	// track the probable max or min timestamp of adjacent messages.
	// the range of all messages is always within 32767 minutes, the max deadline.
	// we use this to limit the search range and limit cpu and io usage
	const String timestamp = baseTransactionContents["timestamp"];
	const uint64 tsBase = timestamp.getLargeIntValue();
	uint64 extendedSearchTimestampMax = 0;
	uint64 extendedSearchTimestampMin = 0xFFFFFFFFFFFFFFFF;
	if (tsBase - (SEARCH_RANGE_MINUTES * 60) < extendedSearchTimestampMin)
		extendedSearchTimestampMin = tsBase - (SEARCH_RANGE_MINUTES * 60);
	if (tsBase + (SEARCH_RANGE_MINUTES * 60) > extendedSearchTimestampMax)
		extendedSearchTimestampMax = tsBase + (SEARCH_RANGE_MINUTES * 60);
	
	StringArray txidArray;
	var recipientsArray;
	StringArray timeStamps;
	progress += 0.01;
	if (reedSolomonIn.isNotEmpty() && !CheckThreadShouldExit(context, progress))
	{
		// get all transactions from this account
		const var transactions = GetAccountTransactionIds(reedSolomonIn);
		Array<String> allTransactionsToCheckPre;
		Array<String> allTransactionsToCheckPost;
		float numProgress = 1.f;
		if (transactions["transactionIds"].isArray())
		{
			numProgress = transactions["transactionIds"].size();
			bool copyFromHere = false;
			for (int i = 0; i < transactions["transactionIds"].size(); i++)
			{
				if (downloadTransactionID.compare(transactions["transactionIds"][i]) == 0)
					copyFromHere = true;
				
				if (copyFromHere)
					allTransactionsToCheckPost.add(transactions["transactionIds"][i]);
				else allTransactionsToCheckPre.insert(0, transactions["transactionIds"][i]); // reverse insert				
			}
		}

		unsigned int matchThisCRC = 0;
		bool stopLookingPost = false;
		bool stopLookingPre = false;
		int idxPre = 0;
		int idxPost = 0;
		// check each transaction in front and back, and see if its a multi out same. and within time range
		// store each mtx that matches the CRC of the given tx id
		// and stop looking untill there is a multi out same with a different crc
		while ((!stopLookingPost || !stopLookingPre) && !CheckThreadShouldExit(context, progress))
		{
			progress = (idxPre + idxPost) / numProgress;
			bool timeRange = false;
			String txid;
			if (!stopLookingPost)
				txid = allTransactionsToCheckPost[idxPost];
			else if (!stopLookingPre)
				txid = allTransactionsToCheckPre[idxPre];
			
			if (txid.isNotEmpty())
			{
				const var jsonStructure = GetTransaction(txid);
				const String timestamp = jsonStructure["timestamp"];
				const uint64 ts = timestamp.getLargeIntValue();

				if (ts >= extendedSearchTimestampMin && ts <= extendedSearchTimestampMax)
				{	// get Multi Same {"version.MultiSameOutCreation":1,"recipients":["9223372036854775807","1"]}
					const var attachmentVAR = jsonStructure["attachment"];
					const var multiSameOutCreationVAR = attachmentVAR["version.MultiSameOutCreation"].toString();
					if ((int)multiSameOutCreationVAR == 1)
					{
						var	v = attachmentVAR["recipients"];
						// Check total CRC here so we can stop getting transaction details when it stops matching
						if (v.isArray())
						{
							juce::BigInteger bigInt; // convert string to 64 bit blob
							bigInt.parseString(v[0].toString(), 10);
							MemoryBlock header = bigInt.toMemoryBlock();

							int length = 0;
							unsigned int crc16 = 0;
							memcpy(&length, header.getData(), sizeof(int));
							memcpy(&crc16, &((int*)header.getData())[1], sizeof(int));
							unsigned int crc16_full = (crc16 & 0xFFFF0000) >> 16;

							if (idxPost == 0) // first one, the transaction we pointed to
								matchThisCRC = crc16_full;

							if (matchThisCRC == crc16_full)
							{
								// collect all probale data that matches the crc. still 1:65535 chance its not part of the set
								txidArray.add(txid);
								recipientsArray.append(v);
								// narrow the range down from min and max 32767 minutes of the origin tx
								if (ts - (SEARCH_RANGE_MINUTES * 60) > extendedSearchTimestampMin) // if 32767 min before Minimum is higher than our current minimum
									extendedSearchTimestampMin = ts - (SEARCH_RANGE_MINUTES * 60);
								if (ts + (SEARCH_RANGE_MINUTES * 60) < extendedSearchTimestampMax) // if 32767 min after Maximum is lower
									extendedSearchTimestampMax = ts + (SEARCH_RANGE_MINUTES * 60);

								timeStamps.add(timestamp);
							}
						}
					}
					const var multiOutCreationVAR = attachmentVAR["version.MultiOutCreation"].toString();
					if ((int)multiOutCreationVAR == 1)
					{
						var	v = attachmentVAR["recipients"];
						// Check total CRC here so we can stop getting transaction details when it stops matching
						if (v.isArray())
						{
							juce::BigInteger bigInt; // convert string to 64 bit blob
							bigInt.parseString(v[0][0].toString(), 10);
							MemoryBlock header = bigInt.toMemoryBlock();

							int length = 0;
							unsigned int crc16 = 0;
							memcpy(&length, header.getData(), sizeof(int));
							memcpy(&crc16, &((int*)header.getData())[1], sizeof(int));
							unsigned int crc16_full = (crc16 & 0xFFFF0000) >> 16;

							if (idxPost == 0) // first one, the transaction we pointed to
								matchThisCRC = crc16_full;

							if (matchThisCRC == crc16_full)
							{
								// collect all probale data that matches the crc. still 1:65535 chance its not part of the set
								txidArray.add(txid);

								// filter out the amounts. and remove the last TX
								var onlyAddresses;
								for (int a = 0; a < v.size() - 1; a++)
									onlyAddresses.append(v[a][0]);

								recipientsArray.append(onlyAddresses);
								// narrow the range down from min and max 32767 minutes of the origin tx
								if (ts - (SEARCH_RANGE_MINUTES * 60) > extendedSearchTimestampMin) // if 32767 min before Minimum is higher than our current minimum
									extendedSearchTimestampMin = ts - (SEARCH_RANGE_MINUTES * 60);
								if (ts + (SEARCH_RANGE_MINUTES * 60) < extendedSearchTimestampMax) // if 32767 min after Maximum is lower
									extendedSearchTimestampMax = ts + (SEARCH_RANGE_MINUTES * 60);

								timeStamps.add(timestamp);
							}
						}
					}
				}
				else // exeeded the time range. stop searching
				{
					timeRange = true;
				}
			}

			if (!stopLookingPost)
				idxPost++;
			else idxPre++;
			
			if (!stopLookingPost)
				stopLookingPost = idxPost >= allTransactionsToCheckPost.size();
			
			if (!stopLookingPre) 
				stopLookingPre = idxPre >= allTransactionsToCheckPre.size();

			if (timeRange)
			{
				if (!stopLookingPost)
					stopLookingPost = true;
				else stopLookingPre = true;
			}
		}
	}
	
	float progressPart2 = (1. - progress) / 2;
	float progressPart3 = (1. - progress) / 2;

	// sort and get data from recipients. reconstruct the data
	// we only collect 1 payload here but multiple payloads with different CRCs will be splitted also
	Array<unsigned int> attachmentCRCs;
	if (recipientsArray.isArray() && !CheckThreadShouldExit(context, progress))
	{
		int totalMultiOuts = recipientsArray.getArray()->size();
		Array<int> totalReadData;
		for (int i = 0; i < totalMultiOuts && !CheckThreadShouldExit(context, progress + ((progressPart2 / totalMultiOuts) * i)); i++)
		{
			int dataSize = 0;
			unsigned int crc16_full_match = 0;
			MemoryBlock data = GetAttachmentData(recipientsArray[i], dataSize, crc16_full_match);

			int attachmentIndex = attachmentCRCs.indexOf(crc16_full_match);
			int neededBytes = dataSize + data.getSize();
			if (attachmentIndex < 0)
			{ // new attachment
				attachmentDatas.add(MemoryBlock(data.getData(), data.getSize()));
				attachmentDatas.getReference(attachmentDatas.size() - 1).ensureSize(neededBytes, true);
				timecodes.add(timeStamps[i]);
				attachmentCRCs.addIfNotAlreadyThere(crc16_full_match);
				totalReadData.add(data.getSize());
			}
			else
			{
				totalReadData.getReference(attachmentIndex) += data.getSize();
				// determine the position to insert the data
				if (neededBytes > (int)attachmentDatas.getReference(attachmentIndex).getSize()) // check if we need to add more space
				{	// add the data in front of the data we already got
					int addedSize = (neededBytes)-attachmentDatas.getReference(attachmentIndex).getSize();
					data.ensureSize(addedSize, true);
					attachmentDatas.getReference(attachmentIndex).insert(data.getData(), data.getSize(), 0);
				}
				else
				{
					const int desitnationPos = attachmentDatas.getReference(attachmentIndex).getSize() - (neededBytes);
					attachmentDatas.getReference(attachmentIndex).copyFrom(data.getData(), desitnationPos, data.getSize());
				}
			}
		}

		for (int i = attachmentDatas.size() - 1; i >= 0 && !CheckThreadShouldExit(context, progress + progressPart2 + ((progressPart3 / attachmentDatas.size()) * ((attachmentDatas.size() - 1) - i))); i--)
		{ // check 16 bit crc for combined data. and if expected data size matches
			int attachmentSize = attachmentDatas[i].getSize();
			// unzip
			MemoryInputStream srcStream(attachmentDatas.getReference(i), false);
			juce::MemoryBlock mb;
			GZIPDecompressorInputStream dezipper(&srcStream, false, GZIPDecompressorInputStream::gzipFormat);
			dezipper.readIntoMemoryBlock(mb);
			attachmentDatas.getReference(i) = mb;			

			// check the 16 bits crc of the unzipped data
			boost::crc_16_type crcProcessor;
			crcProcessor.process_bytes(attachmentDatas[i].getData(), attachmentDatas[i].getSize());
			int crc16_full = crcProcessor.checksum();
			int crc16_expected = attachmentCRCs[i];
			int trd = totalReadData[i];
			
			if (trd < attachmentSize || // smaller than. bcz its possible a previous upload got aborted and we had double data
				crc16_expected != crc16_full)
			{
				attachmentDatas.remove(i);
			}
		}
	}
	if (CheckThreadShouldExit(context, 1.f))
	{
		attachmentDatas.clear();
		timecodes.clear();
	}
	return !CheckThreadShouldExit(context, 1.f);
}

/**********************************************************************************************
64 bits per address, 0.00000001 BURST burned
HEADER = datasize 32 bits + crc 16 + crcfull 16
PAYLOAD multiple of 8 bytes
**********************************************************************************************/
Array<StringArray> BurstAPI::SetAttachmentData(MemoryBlock data)
{ // convert arbitraty data to numerical burst addresses
	boost::crc_16_type crcProcessor;
	crcProcessor.process_bytes(data.getData(), data.getSize());
	int crc16_full = crcProcessor.checksum();

	// compress the data
	MemoryOutputStream destStream(0);
	juce::GZIPCompressorOutputStream zipper(&destStream, 9, false, juce::GZIPCompressorOutputStream::windowBitsGZIP);
	zipper.write(data.getData(), data.getSize());
	zipper.flush();
	data = destStream.getMemoryBlock();

	// zero padding
	juce::MemoryBlock paddedData = data;
	unsigned int original_len = paddedData.getSize();
	
	if (original_len % 8 > 0) // resize to multiple of 8 bytes
		paddedData.ensureSize(original_len + (8 - (original_len % 8)), true);
	uint64 header = 0;
	char *headerPtr = (char*)&header;
	
	Array<Array<uint64>> array64;
	Array<uint64> sa;
	unsigned int remaining_len = original_len;
	MemoryBlock partCRC;

	// first is always only 64 addresses. muli out
	// 1 header
	// payload
	// donation address
	for (unsigned int i = 0; i < paddedData.getSize(); i += 8)
	{
		// PAYLOAD
		uint64 address = 0;
		paddedData.copyTo(&address, i, sizeof(uint64));
		
		bool alreadyHasAddress = sa.contains(address);
		if (!alreadyHasAddress)
		{
			sa.add(address);
			partCRC.append(&address, sizeof(uint64));
		}

		const int s1 = array64.size(); // num multi outs
		const int s2 = sa.size(); // num addresses
		
		if (alreadyHasAddress ||
			(s1 != 0 && s2 >= (128 - 1)) ||	// multi out same
			(s1 == 0 && s2 >= (64 - 2)) ||	// multi out - fee
			(i + 8) == paddedData.getSize())
		{
			// HEADER
			// new multi out header for each 128 rows
			boost::crc_16_type crcProcessor;
			crcProcessor.process_bytes(partCRC.getData(), partCRC.getSize());
			int crc16 = crcProcessor.checksum();
			partCRC.reset();
			headerPtr[0] = (remaining_len & 0x000000FF); // <- repurpose?
			headerPtr[1] = (remaining_len & 0x0000FF00) >> 8;
			headerPtr[2] = (remaining_len & 0x00FF0000) >> 16;
			headerPtr[3] = (remaining_len & 0xFF000000) >> 24;	// 32 bit to store the length, might wanna repurpose the first byte. then max size would be 16777215 bytes (16.7 MB)
			headerPtr[4] = (crc16 & 0x000000FF);
			headerPtr[5] = (crc16 & 0x0000FF00) >> 8;
			headerPtr[6] = (crc16_full & 0x000000FF);
			headerPtr[7] = (crc16_full & 0x0000FF00) >> 8;
			
			remaining_len -= jmin<int>(sa.size() * 8, remaining_len); // subtract the bytes. which gives us an ID for searching the next multiout
			sa.insert(0, header);

			if (array64.size() == 0)
			{ // add the fee at the end of the first batch
				// If you change this or any other fee related code. then please consider buying me a beer : BURST-72X9-E6F3-YSM2-CLQUD
				sa.add(11955599475299484583);
			}

			// add 1 full new multi out with unique addresses
			array64.add(sa);
			
			sa.clear();
			if (alreadyHasAddress)
			{
				sa.add(address);
				partCRC.append(&address, sizeof(uint64));
			}
		}
	}

	// convert to array of multiouts with each a string arrays of addresses
	Array<StringArray> addressList;
	for (int mtx = 0; mtx < array64.size(); mtx++)
	{
		StringArray addresses;
		for (int address = 0; address < array64[mtx].size(); address++)
		{
			addresses.add(String(array64[mtx][address]));
		}
		addressList.add(addresses);
	}
	return addressList;
}

MemoryBlock BurstAPI::GetAttachmentData(var jsonStructure, int &length_match, unsigned int &crc16_full_match) // length_match to 0 get data without sequence check
{ // convert the numerical burst addresses from a multi out to arbitrary data
	MemoryBlock attachmentData;
	var recipientsVAR = jsonStructure;
	if (recipientsVAR.isArray())
	{
		if (recipientsVAR.size() > 0)
		{
			juce::BigInteger bigInt; // TODO drop the use of BigInteger. but String only returns signed version of int 64 (max size should be 2^64)
			bigInt.parseString(recipientsVAR[0].toString(), 10);
			MemoryBlock header = bigInt.toMemoryBlock();

			int length = 0;
			unsigned int crc16 = 0;
			memcpy(&length, header.getData(), sizeof(int));
			memcpy(&crc16, &((int*)header.getData())[1], sizeof(int));
			unsigned int crc16_full = (crc16 & 0xFFFF0000) >> 16;
			crc16 &= 0x0000FFFF;

			if (length < 0xFFFFFFFF && // 1000 * 1000
				length > 0 && (length == length_match || length_match == 0) && (crc16_full == crc16_full_match || length_match == 0))
			{
				if (length_match == 0)
					crc16_full_match = crc16_full;

				for (int i = 1; i < recipientsVAR.size(); i++)
				{
					juce::BigInteger bigInt;
					bigInt.parseString(recipientsVAR[i].toString(), 10);
					MemoryBlock part = bigInt.toMemoryBlock();
					part.ensureSize(8, true);
					attachmentData.append(part.getData(), 8);
				}

				length_match = jmax<int>(length - attachmentData.getSize(), 0);

				// check crc for this mulitout part
				boost::crc_16_type crcProcessor; 
				crcProcessor.process_bytes(attachmentData.getData(), attachmentData.getSize()); // incl any padded zeroes
				unsigned int crc16_check = crcProcessor.checksum();

				if ((crc16) != crc16_check)
					attachmentData.reset();
				else if (length_match <= 0)
				{ // end of the data stream, check if we need to cut any padded zeroes
					attachmentData.setSize(length, true); // remove zero padded bytes only at the end, when length is shorter than the data we got
				}
			}
			else attachmentData.reset();
		}
	}
	return attachmentData;
}

BurstAPI::Balance BurstAPI::GetBalance(var jsonStructure)
{
	Balance bal;
	bal.unconfirmedBalanceNQT = jsonStructure["unconfirmedBalanceNQT"].toString();
	bal.guaranteedBalanceNQT = jsonStructure["guaranteedBalanceNQT"].toString();
	bal.effectiveBalanceNXT = jsonStructure["effectiveBalanceNXT"].toString();
	bal.forgedBalanceNQT = jsonStructure["forgedBalanceNQT"].toString();
	bal.balanceNQT = jsonStructure["balanceNQT"].toString();
	bal.requestProcessingTime = jsonStructure["requestProcessingTime"].toString();

	return bal;
}


/*

MemoryBlock BurstAPI::TestAccountTransactions(StringArray txids, Array<StringArray> recipientsArray)
{
Array<MemoryBlock> attachmentDatas;
// sort and get data from recipients. reconstruct the data
// we only collect 1 payload here but multiple payloads with different CRCs will be splitted also
Array<unsigned int> attachmentCRCs;
//if (recipientsArray.isArray())
int foundMismatch = 0;
{
int totalMultiOuts = recipientsArray.size();
Array<int> totalReadData;
for (int i = 0; i < totalMultiOuts; i++)
{
int dataSize = 0;
unsigned int crc16_full_match = 0;
MemoryBlock data = GetAttachmentData(recipientsArray[i], dataSize, crc16_full_match);

if (txids[i].isNotEmpty())
{
var txContents = GetTransaction(txids[i]);
const var attachmentVAR = txContents["attachment"];
const var multiSameOutCreationVAR = attachmentVAR["version.MultiSameOutCreation"].toString();
if ((int)multiSameOutCreationVAR == 1)
{
var	v = attachmentVAR["recipients"];
if (v.isArray())
{
foundMismatch += (recipientsArray[i].size() != v.size() ? 1 : 0);

for (int j = 0; j < jmin<int>(recipientsArray[i].size(), v.size()); j++)
{
String value1 = recipientsArray[i][j];
String value2 = v[j].toString();
// compare the arrays
if (value1.compare(value2) != 0)
{
// something is wrong..
foundMismatch++;
}
}
}
}
}
int attachmentIndex = attachmentCRCs.indexOf(crc16_full_match);
int neededBytes = dataSize + data.getSize();
if (attachmentIndex < 0)
{ // new attachment
attachmentDatas.add(MemoryBlock(data.getData(), data.getSize()));
attachmentDatas.getReference(attachmentDatas.size() - 1).ensureSize(neededBytes, true);

attachmentCRCs.addIfNotAlreadyThere(crc16_full_match);
totalReadData.add(data.getSize());
}
else
{
totalReadData.getReference(attachmentIndex) += data.getSize();
// determine the position to insert the data
if (neededBytes > (int)attachmentDatas.getReference(attachmentIndex).getSize()) // check if we need to add more space
{	// add the data in front of the data we already got
int addedSize = (neededBytes)-attachmentDatas.getReference(attachmentIndex).getSize();
data.ensureSize(addedSize, true);
attachmentDatas.getReference(attachmentIndex).insert(data.getData(), data.getSize(), 0);
}
else
{
const int desitnationPos = attachmentDatas.getReference(attachmentIndex).getSize() - (neededBytes);
attachmentDatas.getReference(attachmentIndex).copyFrom(data.getData(), desitnationPos, data.getSize());
}
}
}

for (int i = attachmentDatas.size() - 1; i >= 0; i--)
{ // check 16 bit crc for combined data. and if expected data size matches
int attachmentSize = attachmentDatas[i].getSize();
// unzip
MemoryInputStream srcStream(attachmentDatas.getReference(i), false);
juce::MemoryBlock mb;
GZIPDecompressorInputStream dezipper(&srcStream, false, GZIPDecompressorInputStream::gzipFormat);
dezipper.readIntoMemoryBlock(mb);
attachmentDatas.getReference(i) = mb;

// check the 16 bits crc of the unzipped data
boost::crc_16_type crcProcessor;
crcProcessor.process_bytes(attachmentDatas[i].getData(), attachmentDatas[i].getSize());
int crc16_full = crcProcessor.checksum();
int crc16_expected = attachmentCRCs[i];
int trd = totalReadData[i];

if (trd < attachmentSize || // smaller than. bcz its possible a previous upload got aborted and we had double data
crc16_expected != crc16_full)
{
attachmentDatas.remove(i);
}
}
}
if (attachmentDatas.size() > 0)
return attachmentDatas.getFirst();
else return MemoryBlock();
}

*/
/*
PHP prep work
https://stackoverflow.com/questions/14018508/how-to-calculate-crc16-in-php

This seems to work, tested with several values against this website for CRC-16-CCITT
Note that it uses PHP strings as direct byte buffers, because it's PHP's closest equivalent to byte[]

<?php

class CRC16 {
private static $CRC16_Table = array
(   0x0000, 0x2110, 0x4220, 0x6330, 0x8440, 0xa550, 0xc660, 0xe770,
0x0881, 0x2991, 0x4aa1, 0x6bb1, 0x8cc1, 0xadd1, 0xcee1, 0xeff1,
0x3112, 0x1002, 0x7332, 0x5222, 0xb552, 0x9442, 0xf772, 0xd662,
0x3993, 0x1883, 0x7bb3, 0x5aa3, 0xbdd3, 0x9cc3, 0xfff3, 0xdee3,
0x6224, 0x4334, 0x2004, 0x0114, 0xe664, 0xc774, 0xa444, 0x8554,
0x6aa5, 0x4bb5, 0x2885, 0x0995, 0xeee5, 0xcff5, 0xacc5, 0x8dd5,
0x5336, 0x7226, 0x1116, 0x3006, 0xd776, 0xf666, 0x9556, 0xb446,
0x5bb7, 0x7aa7, 0x1997, 0x3887, 0xdff7, 0xfee7, 0x9dd7, 0xbcc7,
0xc448, 0xe558, 0x8668, 0xa778, 0x4008, 0x6118, 0x0228, 0x2338,
0xccc9, 0xedd9, 0x8ee9, 0xaff9, 0x4889, 0x6999, 0x0aa9, 0x2bb9,
0xf55a, 0xd44a, 0xb77a, 0x966a, 0x711a, 0x500a, 0x333a, 0x122a,
0xfddb, 0xdccb, 0xbffb, 0x9eeb, 0x799b, 0x588b, 0x3bbb, 0x1aab,
0xa66c, 0x877c, 0xe44c, 0xc55c, 0x222c, 0x033c, 0x600c, 0x411c,
0xaeed, 0x8ffd, 0xeccd, 0xcddd, 0x2aad, 0x0bbd, 0x688d, 0x499d,
0x977e, 0xb66e, 0xd55e, 0xf44e, 0x133e, 0x322e, 0x511e, 0x700e,
0x9fff, 0xbeef, 0xdddf, 0xfccf, 0x1bbf, 0x3aaf, 0x599f, 0x788f,
0x8891, 0xa981, 0xcab1, 0xeba1, 0x0cd1, 0x2dc1, 0x4ef1, 0x6fe1,
0x8010, 0xa100, 0xc230, 0xe320, 0x0450, 0x2540, 0x4670, 0x6760,
0xb983, 0x9893, 0xfba3, 0xdab3, 0x3dc3, 0x1cd3, 0x7fe3, 0x5ef3,
0xb102, 0x9012, 0xf322, 0xd232, 0x3542, 0x1452, 0x7762, 0x5672,
0xeab5, 0xcba5, 0xa895, 0x8985, 0x6ef5, 0x4fe5, 0x2cd5, 0x0dc5,
0xe234, 0xc324, 0xa014, 0x8104, 0x6674, 0x4764, 0x2454, 0x0544,
0xdba7, 0xfab7, 0x9987, 0xb897, 0x5fe7, 0x7ef7, 0x1dc7, 0x3cd7,
0xd326, 0xf236, 0x9106, 0xb016, 0x5766, 0x7676, 0x1546, 0x3456,
0x4cd9, 0x6dc9, 0x0ef9, 0x2fe9, 0xc899, 0xe989, 0x8ab9, 0xaba9,
0x4458, 0x6548, 0x0678, 0x2768, 0xc018, 0xe108, 0x8238, 0xa328,
0x7dcb, 0x5cdb, 0x3feb, 0x1efb, 0xf98b, 0xd89b, 0xbbab, 0x9abb,
0x754a, 0x545a, 0x376a, 0x167a, 0xf10a, 0xd01a, 0xb32a, 0x923a,
0x2efd, 0x0fed, 0x6cdd, 0x4dcd, 0xaabd, 0x8bad, 0xe89d, 0xc98d,
0x267c, 0x076c, 0x645c, 0x454c, 0xa23c, 0x832c, 0xe01c, 0xc10c,
0x1fef, 0x3eff, 0x5dcf, 0x7cdf, 0x9baf, 0xbabf, 0xd98f, 0xf89f,
0x176e, 0x367e, 0x554e, 0x745e, 0x932e, 0xb23e, 0xd10e, 0xf01e
);

public static function calculate( $buffer ) {
$length = strlen($buffer);

$crc = 0;
$i = 0;
while( $length-- ) {
$crc = (( $crc >> 8) & 0xff) ^ (self::$CRC16_Table[(ord($buffer[$i++]) ^ $crc) & 0xFF]);
}

return (($crc & 0xFFFF) ^ 0x8000) - 0x8000;
}
}

echo CRC16::calculate( "\x74\x65\x73\x74" );

---------------------------------------------------------



<?php
function crc16($data)
{
$crc = 0xFFFF;
for ($i = 0; $i < strlen($data); $i++)
{
$x = (($crc >> 8) ^ ord($data[$i])) & 0xFF;
$x ^= $x >> 4;
$crc = (($crc << 8) ^ ($x << 12) ^ ($x << 5) ^ $x) & 0xFFFF;
}
return $crc;
}
?>

*/