#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAXBYTE 256 

void error(char *fmt, ...);
void usage();
void genchar(unsigned char *s, unsigned int size);
void genkey(unsigned char *s, unsigned int size);
size_t readBuf(FILE *f, unsigned char *buf, size_t size);
size_t writeBuf(FILE *f, unsigned char *buf, size_t size);

#endif