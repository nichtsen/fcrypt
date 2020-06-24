#include "ecb.h"

unsigned char tmp[KEYSIZE];

AES_KEY *klloc(void) {
	return (AES_KEY *)malloc(sizeof(AES_KEY));
}

void pad(unsigned char *buf, const unsigned int num) {
	int i, gap;
	gap = KEYSIZE - (num % KEYSIZE);
	for (i = 0; i < gap; i++)
		buf[num + i] = gap;
}

int isPad(unsigned char *buf, const unsigned int last) {
	if (buf[last] >= KEYSIZE){
		return 0;
	}
	int i;
	for (i = 1; i < buf[last]; i++) {
		if (buf[last - i] != buf[last]) {
			return 0;
		}
	}
	return 1;
}

void strip(unsigned char *buf, const unsigned int last) {
	int i, gap;
	gap = buf[last];
	for (i = 0; i < gap; i++) {
		buf[last - i] = '\0';
	}
}

int unpad(unsigned char *buf, const size_t num) {
	if (isPad(buf, num - 1)) {
		unsigned int gap = buf[num - 1];
		strip(buf, num - 1);
		return gap;
	}
	return 0;
}

size_t encrypt(unsigned char * buf, AES_KEY *key, size_t num) {
	if (num % KEYSIZE > 0) {
		pad(buf, num);
		num = num + KEYSIZE - (num % KEYSIZE);
	}
	int i;
	for (i = 0; i < num; i += KEYSIZE) {
		AES_ecb_encrypt(buf + i, tmp, key, AES_ENCRYPT);
		memcpy(buf + i, tmp, KEYSIZE);
	}
	return num;
}

size_t decrypt(unsigned char *buf, AES_KEY *key, size_t num) {
	int i;
	for (i = 0; i < num; i += KEYSIZE) {
		AES_ecb_encrypt(buf + i, tmp, key, AES_DECRYPT);
		memcpy(buf + i, tmp, KEYSIZE);
	}
	return (num - unpad(buf, num));
}

void main(int argc, char *argv[]) {
	if (argc != 3) {
		usage();
		error("Invalid arguments\n");
	}

	if (strcmp(argv[1], "-en") && strcmp(argv[1], "-de")) {
		usage();
		while (argc-- > 0) {
			printf("%s\n", *argv++);
		}
		exit(1);
	}

	unsigned char ukey[KEYSIZE];
	unsigned char buf[BUFSIZE];
	size_t num;
	unsigned int count = 0;
	char filename[MAXBYTE];
	AES_KEY *key;
	AES_KEY *dkey;
	FILE *f, *fw;
	strcpy(filename, argv[2]);

	if (!strcmp(argv[1], "-en")) {

		if ((f = fopen(filename, "rb")) == NULL) {
			error("Error occurs while opening file %s", filename);
		}
		strcat(filename, ".en");
		if ((fw = fopen(filename, "wb")) == NULL) {
			error("Error occurs while opening file %s", filename);
		}

		key = klloc();
		srand((unsigned)time(NULL));
		genkey(ukey, KEYSIZE);
		assert(AES_set_encrypt_key(ukey, 128, key) == 0);

		while ((num = readBuf(f, buf, sizeof(buf))) != 0) {
			num = encrypt(buf, key, num);
			if (writeBuf(fw, buf, num) == NULL) {
				break;
			}
			count += num;
		}
		fclose(fw);
		fclose(f);

		strcat(strcpy(filename, argv[2]), ".key");
		if ((fw = fopen(filename, "wb")) == NULL) {
			error("Error occurs when opening file %s", filename);
		}
		writeBuf(fw, ukey, KEYSIZE);
		fclose(fw);
	}

	if (!strcmp(argv[1], "-de")){
		if (!(filename[strlen(filename) - 1] == 'n'  &&
			filename[strlen(filename) - 2] == 'e' &&
			filename[strlen(filename) - 3] == '.'
		)) {
			error("Invalid file extension");
		}
		filename[strlen(filename) - 3] = 0 ;
		strcat(filename, ".key");
		
		if ((f = fopen(filename, "rb")) == NULL) {
			error("Error occurs while searching for file %s", filename);
		}
		readBuf(f, ukey, sizeof(ukey));
		fclose(f);

		dkey = klloc();
		assert(AES_set_decrypt_key(ukey, 128, dkey) == 0);

		strcpy(filename, argv[2]);
		if ((f = fopen(filename, "rb")) == NULL) {
			error("Error occurs while opening file %s", filename);
		}
		strcat(filename, ".de");
		if ((fw = fopen(filename, "wb")) == NULL) {
			error("Error occurs while opening file %s", filename);
		}

		while ((num = readBuf(f, buf, sizeof(buf))) != 0) {
			num = decrypt(buf, dkey, num);
			if (writeBuf(fw, buf, num) == NULL) {
				break;
			}
			count += num;
		}
		fclose(fw);
		fclose(f);
	}
	/*
	testing
	unsigned char in[KEYSIZE];
	unsigned char out[KEYSIZE];
	unsigned char outin[KEYSIZE];
	genchar(in, KEYSIZE);
	int i;
	for (i=0; i<sizeof(in); i++ )
		printf("%x ", in[i]); 
	AES_ecb_encrypt(in, out, key, AES_ENCRYPT);
	AES_ecb_encrypt(out, outin, dkey, AES_DECRYPT);
	printf("=====================\n");
	for (i = 0; i<sizeof(out); i++)
		printf("%x ", out[i]);
	printf("=====================\n");
	for (i = 0; i<sizeof(out); i++)
		printf("%x ", outin[i]);
	*/
	fprintf(stdout, "Successfully writing %d bytes data", count);
	exit(0);
}

