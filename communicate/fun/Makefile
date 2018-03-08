#顶层路径
ROOT = $(firstword $(subst Pro2, Pro2 ,$(PWD)))/Pro2

#包含编译规则
include $(ROOT)/Rules.make

CSOURCES = $(wildcard *.c)
BIT = y
targets = $(CSOURCES:.c=)

ifeq ($(BIT),y)

all:$(targets)
$(targets):%:%.c
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS)

else

OUT:$(CSOURCES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)	

endif	

clean:
	rm -f $(targets) $(TEMPFILES) *.o
