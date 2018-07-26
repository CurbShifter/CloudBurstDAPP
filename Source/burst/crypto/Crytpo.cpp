//
//  Crytpo.cpp
//  Burstcoin
//
//  
//  based on .m version by Andy Prock

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

#include "Crypto.hpp"

extern "C" {
#include "curve25519_i64.h"
}
#include "sha256.h"

#define ECCKeyLength 32
#define ECCSignatureLength 64

void Crypto::getPublicKey(MemoryBlock passPhrase, MemoryBlock &publicKey)
{
	publicKey.ensureSize(ECCKeyLength, true);
	SHA256 sha(passPhrase.getData(), passPhrase.getSize());
	MemoryBlock hash = sha.getRawData();
	keygen25519((unsigned char *)publicKey.getData(), nullptr, (unsigned char *)hash.getData());
}

void Crypto::getPrivateKey(MemoryBlock passPhrase, MemoryBlock &privateKey)
{
	SHA256 sha(passPhrase.getData(), passPhrase.getSize());
	privateKey = sha.getRawData();
	
	if (privateKey.getSize() > 31)
	{
		((char*)privateKey.getData())[31] &= 0x7F;
		((char*)privateKey.getData())[31] |= 0x40;
		((char*)privateKey.getData())[0] &= 0xF8;
	}
}

// deterministic EC-KCDSA
MemoryBlock Crypto::sign(MemoryBlock data, MemoryBlock passPhrase)
{ 
	MemoryBlock P(ECCKeyLength, true);
	MemoryBlock s(ECCKeyLength, true);

	SHA256 sha1(passPhrase.getData(), passPhrase.getSize());
	MemoryBlock k = sha1.getRawData();
	keygen25519((unsigned char *)P.getData(), (unsigned char *)s.getData(), (unsigned char *)k.getData());

	SHA256 sha2(data.getData(), data.getSize());
	const MemoryBlock m = sha2.getRawData();

	SHA256_CTX ctx;
	sha256_init(&ctx);
	sha256_update(&ctx, (BYTE*)m.getData(), ECCKeyLength);
	sha256_update(&ctx, (BYTE*)s.getData(), ECCKeyLength);
	MemoryBlock x(ECCKeyLength, true);
	sha256_final(&ctx, (BYTE*)x.getData());

	MemoryBlock Y(ECCKeyLength, true);
	keygen25519((unsigned char *)Y.getData(), nullptr, (unsigned char *)x.getData());

	SHA256_CTX ctx2;
	sha256_init(&ctx2);
	sha256_update(&ctx2, (BYTE*)m.getData(), ECCKeyLength);
	sha256_update(&ctx2, (BYTE*)Y.getData(), ECCKeyLength);
	MemoryBlock h(ECCKeyLength, true);
	sha256_final(&ctx2, (BYTE*)h.getData());

	MemoryBlock v(ECCKeyLength, true);
	bool success = sign25519((unsigned char *)v.getData(), (unsigned char *)h.getData(), (unsigned char *)x.getData(), (unsigned char *)s.getData()) > 0;

	MemoryBlock signature;
	signature.append(v.getData(), ECCKeyLength);
	signature.append(h.getData(), ECCKeyLength);

	return signature;
}

bool Crypto::verify(MemoryBlock signature, MemoryBlock pubKey, MemoryBlock data)
{
	MemoryBlock Y(ECCKeyLength, true); 
	MemoryBlock v(signature.getData(), ECCKeyLength);
	MemoryBlock h(&((char*)signature.getData())[ECCKeyLength], ECCKeyLength);

	verify25519((unsigned char *)Y.getData(), (unsigned char *)v.getData(), (unsigned char *)h.getData(), (unsigned char *)pubKey.getData());
	
	SHA256 sha1(data.getData(), data.getSize());
	MemoryBlock datahash = sha1.getRawData();
	
	SHA256_CTX ctx;
	sha256_init(&ctx);
	sha256_update(&ctx, (BYTE*)datahash.getData(), datahash.getSize());
	sha256_update(&ctx, (BYTE*)Y.getData(), ECCKeyLength);
	MemoryBlock h2(ECCKeyLength, true);
	sha256_final(&ctx, (BYTE*)h2.getData());
	
	return h2.matches(h.getData(), h.getSize());
}

/*
#include "tiny-AES-c/aes.hpp" // https://github.com/kokke/tiny-AES-c

const CCAlgorithm kAlgorithm = kCCAlgorithmAES128;
const NSUInteger kAlgorithmKeySize = kCCKeySizeAES128;
const NSUInteger kAlgorithmBlockSize = kCCBlockSizeAES128;
const NSUInteger kAlgorithmIVSize = kCCBlockSizeAES128;*/
/*
- (NSData*) getSharedSecret:(NSData*)myPrivateKey theirPublicKey:(NSData*)theirPublicKey {
  uint8_t sharedSecret[ECCKeyLength] = {0};
  curve25519(sharedSecret, myPrivateKey.bytes, theirPublicKey.bytes);
  return [NSData dataWithBytes:sharedSecret length:ECCKeyLength];
}

- (NSData*) aesEncrypt: (NSData*) plainText myPrivateKey:(NSData*)privKey theirPublicKey:(NSData*)pubKey {
  void* nonce = malloc(ECCKeyLength);
  return [self aesEncrypt:plainText myPrivateKey:privKey theirPublicKey:pubKey nonce:[NSData dataWithBytes:nonce length:ECCKeyLength]];
}

- (NSData*) aesEncrypt: (NSData*) plainText myPrivateKey:(NSData*)privKey theirPublicKey:(NSData*)pubKey nonce:(NSData*)nonce {
  uint8_t dhSharedSecret[ECCKeyLength] = {0};
  curve25519(dhSharedSecret, privKey.bytes, pubKey.bytes);

  const uint8_t* nonceBytes = nonce.bytes;
  for (int i = 0; i < 32; i++) {
    dhSharedSecret[i] ^= nonceBytes[i];
  }

  uint8_t key[ECCKeyLength] = {0};
  CC_SHA256(dhSharedSecret, ECCKeyLength, key);

  uint8_t iv[16] = {0};
  if (0 != SecRandomCopyBytes(kSecRandomDefault, 16, iv)) {
    return nil;
  }

  NSMutableData* cipherData = [NSMutableData dataWithLength:plainText.length + kAlgorithmBlockSize];

  size_t outLength = 0;
  CCCryptorStatus result = CCCrypt(kCCEncrypt, // operation
                                   kAlgorithm, // Algorithm 
                                   kCCOptionPKCS7Padding, // options
                                   key, // key
                                   ECCKeyLength, // keylength
                                   iv,// iv
                                   plainText.bytes, // dataIn
                                   plainText.length, // dataInLength,
                                   cipherData.mutableBytes, // dataOut
                                   cipherData.length, // dataOutAvailable
                                   &outLength); // dataOutMoved

								   if (result == kCCSuccess) {
								   [cipherData replaceBytesInRange:NSMakeRange(0, 0) withBytes:(const void *)iv length:16];
								   cipherData.length = outLength + 16;
								   } else {
								   return nil;
								   }
  return cipherData;
}

- (NSData*) aesDecrypt: (NSData*) ivCiphertext myPrivateKey:(NSData*)privKey theirPublicKey:(NSData*)pubKey {
  void* nonce = malloc(ECCKeyLength);
  return [self aesDecrypt:ivCiphertext myPrivateKey:privKey theirPublicKey:pubKey nonce:[NSData dataWithBytes:nonce length:ECCKeyLength]];
}

- (NSData*) aesDecrypt: (NSData*) ivCiphertext myPrivateKey:(NSData*)privKey theirPublicKey:(NSData*)pubKey nonce:(NSData*)nonce {
  uint8_t iv[16] = {0};
  [ivCiphertext getBytes:iv range:NSMakeRange(0, 16)];

  unsigned long cipherTextLength = ivCiphertext.length - 16;
  uint8_t* cipherText = malloc(cipherTextLength);
  [ivCiphertext getBytes:cipherText range:NSMakeRange(16, cipherTextLength)];

  uint8_t dhSharedSecret[ECCKeyLength] = {0};
  curve25519(dhSharedSecret, privKey.bytes, pubKey.bytes);

  const uint8_t* nonceBytes = nonce.bytes;
  for (int i = 0; i < 32; i++) {
    dhSharedSecret[i] ^= nonceBytes[i];
  }

  uint8_t key[ECCKeyLength] = {0};
  CC_SHA256(dhSharedSecret, ECCKeyLength, key);

  NSMutableData* plainData = [NSMutableData dataWithLength:cipherTextLength];

  size_t outLength = 0;
  CCCryptorStatus result = CCCrypt(kCCDecrypt, // operation
                                   kAlgorithm, // Algorithm
                                   kCCOptionPKCS7Padding, // options
                                   key, // key
                                   ECCKeyLength, // keylength
                                   iv,// iv
                                   cipherText, // dataIn
                                   cipherTextLength, // dataInLength,
                                   plainData.mutableBytes, // dataOut
                                   plainData.length, // dataOutAvailable
                                   &outLength); // dataOutMoved

  if (result == kCCSuccess) {
    plainData.length = outLength;
  } else {
    return nil;
  }

  return plainData;
}

*/