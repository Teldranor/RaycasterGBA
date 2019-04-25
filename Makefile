CC= ./devkitARM/bin/arm-none-eabi-gcc 
OBJCOPY= ./devkitARM/bin/arm-none-eabi-objcopy
FIX= ./devkitARM/bin/gbafix
CFLAGS= -mthumb-interwork -mthumb -O2 -Wall -fno-strict-aliasing
LDFLAGS=  -mthumb-interwork -mthumb -specs=gba.specs
TARGET= ray
OBJS= main.o text.o raycaster.o

build: $(TARGET).gba

$(TARGET).gba : $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@
	$(FIX) $@

$(TARGET).elf : $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJS) : %.o : %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean : 
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o

