# CloudBurst DAPP
Decentralized cloud storage application to upload &amp; download files from the [Burstcoin blockchain](http://burst-coin.org/).

![CloudBurst](https://raw.githubusercontent.com/CurbShifter/CloudBurst/master/img/cloudburst-logo-big.png?token=AnETEP84qUYfqymITDikzpW3CKLif3Reks5bXSTYwA%3D%3D)

Decentralized file storage
-
Storing data on a blockchain through transactions to arbitrary addresses is a proven concept that is useful for trust-less data storage and time stamping purposes. This DAPP is designed to make this process user friendly and applicable.

----------
DISCLAIMER
-
**Any data uploaded through this program will be publicly visible for anyone and will exist forever on the Burstcoin blockchain. Uploaded data is linked to your Burst account and cannot be removed !**

* The program is released under GPL v3 License, provided "AS IS" without warranty of any kind.
* The account holder holds sole responsibility for any contents that is uploaded.
* The storage of any personal data is not recommended ! This DAPP is designed for business usage.
* Use a separate wallet with limited funds to upload data.

----------

Usage 
-
1. [Download](https://github.com/CurbShifter/CloudBurstDAPP/releases) and start the app. (unzip the package on Windows or load the .dmg for OSX)
2. Select or enter the wallet server address in top of the interface. Using a local wallet is highly recommended `http://127.0.0.1:8125/`
3. Select 'Upload' or 'Download' in the top left;

## Download ##
Downloading files is free. Just enter a CLOUD ID, for example `CLOUD-739F-XKNL-D4ZT-7GT3Q` and click the large download button. CloudBurst will then reconstruct the data and will ask you to select a location to save the file. 

The timestamp (local to user) of the last upload confirmation and the uploaded message will be displayed below the download button.

![download screen](https://raw.githubusercontent.com/CurbShifter/CloudBurstDAPP/master/img/cloudburst-download-screen.png?token=AnETEGjR0VrrwljFDBPdifZhwPrb4WDUks5bWOT1wA%3D%3D)

## Upload ##
Select a file (1 MB max) and/or enter a message. Then select your upload parameters in the area below. To speed up the upload confirmation you can stack transactions and increase slot priority. But note that the costs will increase because the slots in the block will get more expensive. (When the Burstcoin network is very busy this becomes a necessity).

The confirmation time estimate and total cost in BURST is shown on the right side. It will update each time you change a value. The confirm time should stay well below 24 hours to ensure the upload is valid. This is also the 'deadline' used for all transactions.

Enter the secret pass phrase for your account and click 'Upload'. The program shows the total costs and asks for confirmation. Once all data is send a dialog is shown with your CLOUD ID that you use to retrieve the file/message. Be sure to make a note of it !

NOTE: The 'remember' toggle switch will save your pass phrase on your computer. Consider it being saved as plain text ! Never use it with your main wallet.

![upload screen](https://raw.githubusercontent.com/CurbShifter/CloudBurstDAPP/master/img/cloudburst-upload-screen.png?token=AnETEIWLFQAFvdN6iHg09UQKV2FBKfdGks5bWOIswA%3D%3D)

Cost
-
The costs for uploading are the transaction fees containing the data on the burst network with a 1% added DAPP fee. For each 8 bytes of data that is stored 1 planck needs to be burned (0.00000001 BURST) to register the data on the ledger. 

There is no need to compress your file to lowers the cost. Because maximum gzip compression is automatically applied, which saves time, space and money. This project is designed to support its own development through the fee structure. The modest 1% DAPP fee is send to this address: `BURST-72X9-E6F3-YSM2-CLQUD`

Security
-
All transactions in this DAPP are signed locally, your secret pass phrase will not leave your computer. The code is open sourced so it can be audited for trust-less business deployment.

----------
Command line
-
CloudBurst can be called from the command line with the arguments below. Note that only one instance of the app can run at the same time. If one instance is already running, it will catch and process any command line requests.

	-output [PATH_OF_TEXT_FILE]					a log file for this job

		-upload [PATH_OF_UPLOAD_FILE]				the main payload
			-msg [MESSAGE_WITHIN_QUOTES]			optional message
			-priority [1-1020]				numerical same as UI
			-stack [1-1020]					numerical same as UI
			-maxCostNQT [PLANCKS]				safe guard to prevent expensive uploads. will be noted in the log file if triggered

		-download [CLOUD_ID]					optionally use a tx numerical id
			-folder [PATH_OF_DOWNLOAD_FOLDER]		the filename will be saved in 'output'

		-quit							will close the app after its done

Upload and download examples:
	
	-output "c:/consoleoutput.txt" -upload "c:/test.pdf" -msg "hello world !" -priority 5 -stack 10 -maxCostNQT 1000000000
	-output "c:/consoleoutput.txt" -download CLOUD-739F-XKNL-D4ZT-7GT3Q -folder "c:/foo" -quit


Building
-
The msvc2013 / xcode projects are included. You will need to download and include these libraries;

    Juce https://www.juce.com
    boost++ https://www.boost.org/

	sha256 by Brad Conte https://github.com/B-Con/crypto-algorithms
	CURVE25519 Modified by mko, by Matthijs van Duin, based on work by Daniel J Bernstein

Inquiries
-
Implementations as background service can be discussed. You can reach me through the CloudBurst discord server [https://discord.gg/KsFf3jb](https://discord.gg/KsFf3jb "https://discord.gg/KsFf3jb")

----------

Released under GPL v3 License - Copyright (c) 2018 CurbShifter

Big thanks to @nixops and @MrPilotMan !

