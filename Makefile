CC = gcc

OBJS = utils.o lib/aes_core.o lib/aes_ecb.o ecb.o
PROGM = ecb

DIR = lib

COMPILE = $(CC) -I $(DIR) -c

.SUFFIXES:

%.o:%.c
	$(COMPILE) $< -o $@

$(PROGM): $(OBJS)
	$(CC) -o $(PROGM) $(OBJS)

all: $(PROGM)

clean: 
	rm -f $(PROGM) $(OBJS) 
