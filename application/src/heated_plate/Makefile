CC		:=	riscv32-unknown-elf-gcc
OBJDUMP := riscv32-unknown-elf-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.data

TARGET	:= heated_plate
PTHREAD := ../utility/acPthread.c
UTIL    := grid_to_bmp
GCC_OPTS = -g -march=rv32ima -std=gnu99 -mabi=ilp32
LINK_OPTS = -nostartfiles -lc -lm
LIB_DIR	:=	-L../libac_sysc
LIBS	:=	-lc -lac_sysc
HAL		:=	../rv_hal/get_id.S
SRCS	:=

all:	$(TARGET).c
	$(CC) -c ../rv_hal/crt.S $(GCC_OPTS)
	$(CC) $(TARGET).c $(PTHREAD) -o $(TARGET).run $(SRCS) $(HAL) $(LIB_DIR) $(LIBS) -T ../rv_hal/test.ld $(GCC_OPTS) $(LINK_OPTS)
	$(OBJDUMP) $(TARGET).run > $(TARGET).out
	g++ -Wall -o $(UTIL) $(UTIL).cpp

clean:
	rm $(TARGET).run crt.o $(TARGET).out *.ll *.s cache_output.txt riscv_proc1.trace *.elf *.read
