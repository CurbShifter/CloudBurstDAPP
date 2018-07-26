//
//  Crypto.h
//  Burstcoin

/*
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

#ifndef _CRYPTO_BURST
#define _CRYPTO_BURST

#include "../JuceLibraryCode/JuceHeader.h"

class Crypto
{
public:
	Crypto() {};
	~Crypto() {};

	void getPublicKey(MemoryBlock passPhrase, MemoryBlock &publicKey);
	void getPrivateKey(MemoryBlock passPhrase, MemoryBlock &privateKey);

	MemoryBlock sign(MemoryBlock data, MemoryBlock passPhrase);
	bool verify(MemoryBlock signature, MemoryBlock pubKey, MemoryBlock data);
};
#endif