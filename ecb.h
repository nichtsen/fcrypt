#ifndef ECB_H
#define ECB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include <openssl/aes.h>
#include "utils.h"

#define KEYSIZE 16
#define MAXBYTE 256 
#define BUFSIZE 1024 

#ifndef AES_ENCRYPT
#define AES_ENCRYPT 1
#endif

#ifndef AES_DECRYPT
#define AES_DECRYPT 0
#endif


AES_KEY *klloc(void);
void pad(unsigned char *buf, const unsigned int num);
int isPad(unsigned char *buf, const unsigned int last);
void strip(unsigned char *buf, const unsigned int last);
int unpad(unsigned char *buf, const size_t num);
size_t encrypt(unsigned char * buf, AES_KEY *key, size_t num);
size_t decrypt(unsigned char *buf, AES_KEY *key, size_t num);


#endif
