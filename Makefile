# Don't Look Down — GBA Makefile
# Targets devkitARM / libgba in the official devkitPro Docker image.

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment.")
endif

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment.")
endif

# Explicit paths — do NOT rely on gba_rules to define these
LIBGBA   := $(DEVKITPRO)/libgba
ARCH     := -mthumb -mthumb-interwork
TARGET   := DLD
BUILD    := build
SOURCES  := src
INCLUDES := include

CFLAGS  := -g -Wall -O2 -mcpu=arm7tdmi -mtune=arm7tdmi \
           -ffunction-sections -fdata-sections $(ARCH)
CFLAGS  += $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
           -I$(LIBGBA)/include

LDFLAGS := -g $(ARCH) -Wl,-Map,$(TARGET).map
LIBS    := -lgba

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT    := $(CURDIR)/$(TARGET)
export VPATH     := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR   := $(CURDIR)/$(BUILD)
export PATH      := $(DEVKITARM)/bin:$(PATH)
export LD        := $(CC)

CFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
export OFILES := $(CFILES:.c=.o) $(SFILES:.s=.o)

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba $(TARGET).map

else

DEPENDS := $(OFILES:.o=.d)

$(OUTPUT).gba: $(OUTPUT).elf
	@arm-none-eabi-objcopy -O binary $< $@
	@echo ">>> Wrote $@ ($(shell wc -c < $@) bytes)"

$(OUTPUT).elf: $(OFILES)
	@echo ">>> Linking $@"
	$(CC) $(LDFLAGS) $(OFILES) -L$(LIBGBA)/lib $(LIBS) -o $@

-include $(DEPENDS)

endif
