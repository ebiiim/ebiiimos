TARGET = kernel.elf
OBJS = main.o graphics.o font.o hankaku.o newlib_support.o console.o

CXXFLAGS += -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone \
    -fno-exceptions -fno-rtti -std=c++17

LDFLAGS += --entry KernelMain -z norelro --image-base 0x100000 --static

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf *.o

kernel.elf: $(OBJS) Makefile # rebuild when Makefile changes
	ld.lld $(LDFLAGS) -o kernel.elf $(OBJS) --library=c

%.o: %.cpp Makefile # rebuild when Makefile changes
	clang++ $(CPPFLAGS) $(CXXFLAGS) -c $<

%.o: %.c Makefile
	clang $(CPPFLAGS) $(CFLAGS) -c $<

hankaku.o: ../day05c/hankaku.bin
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 $< $@

../day05c/hankaku.bin: ../day05c/hankaku.txt
	../day05c/makefont.py -o $@ $<
