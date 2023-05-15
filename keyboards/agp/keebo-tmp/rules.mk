# MIN EXAMPLE
# AKB/VERO
# rules.mk, mcuconf.h, info.json, config.h, keymaps/default

# MCU name
MCU = STM32F411

# based on the F411RE
BOARD = GENERIC_STM32_F411XE

# https://docs.qmk.fm/#/hardware_keyboard_guidelines
# info.json, config.h, rules.mk, keebo.c, keebo.h
# Custom AGP Boot file
BOOTLOADER = stm32-dfu

VIA_ENABLE = yes	# enabes VIA support
BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite

EXTRAKEY_ENABLE = no	    # Audio control and System control
NKRO_ENABLE = no            # Enable N-Key Rollover
ENCODER_ENABLE = yes
CONSOLE_ENABLE = yes

MOUSEKEY_ENABLE = no       # Mouse keys
COMMAND_ENABLE = no         # Commands for debug and configuration
AUDIO_ENABLE = no              # Audio output
MIDI_ENABLE = no

STENO_ENABLE = no

RGB_MATRIX_ENABLE = yes
# RGB_MATRIX_DRIVER = IS31FL3741
RGB_MATRIX_DRIVER = custom
RGBLIGHT_ENABLE = no
# RGB_MATRIX_CUSTOM_KB = yes
COMMON_VPATH += $(DRIVER_PATH)/issi

#NO_USB_STARTUP_CHECK = yes	# Disable initialization only when usb is plugged in
LTO_ENABLE = yes # just supposded to improve compiled file size

# project specific files
SRC +=  drivers/led/issi/is31fl3741.c
QUANTUM_LIB_SRC += i2c_master.c


