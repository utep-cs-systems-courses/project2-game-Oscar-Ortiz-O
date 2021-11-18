# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: runToy.elf 

#additional rules for files
runToy.elf: ${COMMON_OBJECTS} interruptHandler.o switch.o buzzer.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: runToy.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

buzzer.c: buzzer.h
switch.c: switch.h
