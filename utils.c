#include "utils.h"

size_t num;

void error(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}

void usage() {
	fprintf(stdout,
	"Welcome to ecb, a quick file encryption/decryption tool with aes-128\n    Usage:\necb [mode] [filename] \n    mode = de | en \n"
	);
}

void genchar(unsigned char *s, unsigned int size) {
	unsigned int i;
	for (i = 0; i < size; i++) {
		s[i] = rand() % 26 + 97;
	}
}

void genkey(unsigned char *s, unsigned int size) {
	unsigned int i;
	for (i = 0; i < size; i++) {
		s[i] = rand() % MAXBYTE;
	}
}

size_t writeBuf(FILE *f, unsigned char *buf, size_t size) {
	if ((num = fwrite(buf, 1, size, f)) != size) {
		fclose(f);
		error("Writing error");
	};
	return num;
}

size_t readBuf(FILE *f, unsigned char *buf, size_t size) {
	if ((num = fread(buf, 1, size, f)) == size) {
		return num;
	} else if (feof(f)) {
		return num;
		printf("%d\n", num);
	} else {
		fclose(f);
		error("Reading error");
	}
}

