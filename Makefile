CC = gcc

OBJS = utils.o ecb.o
PROGM = ecb
LIB = -lcrypto

COMPILE = $(CC) -c

.SUFFIXES:

%.o:%.c
	$(COMPILE) $< -o $@

$(PROGM): $(OBJS)
	$(CC) -o $(PROGM) $(OBJS) $(LIB)

all: $(PROGM)

clean: 
	rm -f $(PROGM) $(OBJS) 
