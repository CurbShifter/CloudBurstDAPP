# CloudBurst DAPP
Decentralized cloud storage - upload &amp; download files from the [Burstcoin blockchain](http://burst-coin.org/).

![CloudBurst](https://raw.githubusercontent.com/CurbShifter/CloudBurstDAPP/master/img/cloudburst-logo-big.png?token=AnETENqmTXeIYFuXkmbf40X41LlYzPhkks5bWOLhwA%3D%3D)

Decentralized file storage
-
Storing arbitrary data on blockchains is a known concept. This dapp is designed to make this process easy for anyone and is useful for trust-less data integrity and time stamping purposes.  

----------
IMPORTANT DISCLAIMER
-
**Any files or data you upload through this program will be publicly visible for anyone and will exist forever on the Burstcoin blockchain. Uploaded data cannot be removed !**

* You hold sole responsibility for the contents that is uploaded.
* Only upload data to which you own the rights. 
* No warranties or guarantees are given to any user of this software.
* Minimize risk by using a separate wallet with limited funds.

----------

Usage 
-
1. [Download](https://github.com/CurbShifter/CloudBurstDAPP/releases) and start the app. 
2. Select or enter the wallet server address in top of the interface. Using a local wallet is recommended `http://127.0.0.1:8125/`
3. Select upload or download from the top toolbar;

**Download** : Downloading is free. Just enter a CLOUD ID, for example `CLOUD-739F-XKNL-D4ZT-7GT3Q` and click the large download button. CloudBurst will search and reconstruct the file. You will then be asked to select a location to save the file if any. The timestamp of the upload confirmation (time local to user) and the uploaded message will be displayed below the download button.

![download screen](https://raw.githubusercontent.com/CurbShifter/CloudBurstDAPP/master/img/cloudburst-download-screen.png?token=AnETEGjR0VrrwljFDBPdifZhwPrb4WDUks5bWOT1wA%3D%3D)

**Upload** : Select a file (1 MB max) and/or enter a message. Then select your upload parameters in the area below. To speed up the upload confirmation you can stack transactions and increase slot priority. But note that the costs will increase because the slots in the block will get more expensive for each transaction.

The estimate of the confirmation time and total cost in BURST is show on the right. The confirm time should stay below 24 hours to ensure the upload is valid. This is also the deadline for all uploaded data transactions.
 
![upload screen](https://raw.githubusercontent.com/CurbShifter/CloudBurstDAPP/master/img/cloudburst-upload-screen.png?token=AnETEIWLFQAFvdN6iHg09UQKV2FBKfdGks5bWOIswA%3D%3D)

Costs
-
**The costs are the transaction fees containing the data with a 5% added dapp fee.**  For each 8 bytes of data that is stored 1 planck needs to be burned (0.00000001 BURST) to register the data and to ensure it is stored on the ledger. The program shows the total costs before you upload and asks for confirmation. There is no need to compress your file to lowers the cost. Maximum compression is automatically applied on upload.

The dapp fee is send to this address `BURST-72X9-E6F3-YSM2-CLQUD` to ensure further updates, features and the purchase of code signing certificates for both Windows and OSX to further improve ease and security.

Security
-
All transactions that are made with this dapp are signed locally. Which means your secret pass phrase will not leave your computer. 
Only download CloudBurst from [this location](https://github.com/CurbShifter/CloudBurstDAPP/releases). To ensure validity you should check if the hash of the application matches with the one noted at the download.

Support
-
If you need assistance or have questions, you can reach me at [https://discord.gg/KsFf3jb](https://discord.gg/KsFf3jb "https://discord.gg/KsFf3jb")
