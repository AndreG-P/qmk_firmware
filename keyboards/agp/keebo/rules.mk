# MCU name
MCU = STM32F411

# based on the F411RE nucleo board
BOARD = ST_NUCLEO64_F411RE

# https://docs.qmk.fm/#/hardware_keyboard_guidelines
# info.json, config.h, rules.mk, keebo.c, keebo.h
# Custom AGP Boot file
BOOTLOADER = stm32-dfu

BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = no	    # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
#NO_USB_STARTUP_CHECK = yes	# Disable initialization only when usb is plugged in

RGB_MATRIX_ENABLE = yes
# RGB_MATRIX_DRIVER = IS31FL3741
RGB_MATRIX_DRIVER = custom  # Enable RGB matrix effects.
RGBLIGHT_ENABLE = no
COMMON_VPATH += $(DRIVER_PATH)/issi

# project specific files
SRC +=  drivers/led/issi/is31fl3741.c
QUANTUM_LIB_SRC += i2c_master.c

CONSOLE_ENABLE = yes
