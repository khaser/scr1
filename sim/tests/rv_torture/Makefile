src_dir := $(dir $(lastword $(MAKEFILE_LIST)))

test_name := rv_torture

default: log_requested_tgt $(bld_dir)/$(test_name).elf $(bld_dir)/$(test_name).hex $(bld_dir)/$(test_name).dump

log_requested_tgt:
	echo $(test_name).hex>> $(bld_dir)/test_info

CFLAGS := -O0 -I$(inc_dir) -I$(src_dir) -DASM -Wa,-march=rv32$(ARCH) -march=rv32$(ARCH) -mabi=$(ABI) -D__riscv_xlen=32 -misa-spec=2.2
LDFLAGS := -static -fvisibility=hidden -nostdlib -nostartfiles -T$(inc_dir)/link.ld -march=rv32$(ARCH) -mabi=$(ABI)

asm_objs := $(bld_dir)/$(test_name).o

$(obj_dir) :
	mkdir -p $(obj_dir)

$(bld_dir)/%.o: %.S 
	@$(RISCV_GCC) $(CFLAGS) $(ADD_ASM_MACRO) -c $< -o $@

$(bld_dir)/%.elf: $(asm_objs) | $(obj_dir)
	@$(RISCV_GCC) -o $@ $^ $(LDFLAGS)

$(bld_dir)/%.hex: $(bld_dir)/%.elf
	@$(RISCV_OBJCOPY) $^ $@

$(bld_dir)/%.dump: $(bld_dir)/%.elf
	@$(RISCV_OBJDUMP) -D -w -x -S $^ > $@

clean:
	$(RM) $(asm_objs) $(bld_dir)/$(test_name).elf $(bld_dir)/$(test_name).hex $(bld_dir)/$(test_name).dump

