#@DESCRIPTION: STM32MP machine extlinux file configuration

# Define extlinux console for stm32mp machine
UBOOT_EXTLINUX_CONSOLE = "console=${@d.getVar('SERIAL_CONSOLE').split()[1]},${@d.getVar('SERIAL_CONSOLE').split()[0]}"
# Define default FDTDIR for all configs
UBOOT_EXTLINUX_FDTDIR = "/"
# Define default MENU DESCRIPTION for all configs
UBOOT_EXTLINUX_MENU_DESCRIPTION += "stm32mp157c-ya157c-v2"
# Define default boot config for all config
UBOOT_EXTLINUX_DEFAULT_LABEL ?= "stm32mp157c-ya157c-hdmi-v2"
# Define default INITRD for all configs
INITRD_SHORTNAME ??= ""
UBOOT_EXTLINUX_INITRD ?= "${@bb.utils.contains('COMBINED_FEATURES', 'autoresize', '/${INITRD_SHORTNAME}', '', d)}"

# -----------------------------------------------------------------------------
# Configurations
# -----------------------------------------------------------------------------
# Define additional targets to use
UBOOT_EXTLINUX_TARGETS += "${@bb.utils.contains_any('BOOTDEVICE_LABELS', [ 'sdcard', 'nor-sdcard' ], 'target-sdcard', '', d)}"
UBOOT_EXTLINUX_TARGETS += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'emmc', 'target-emmc', '', d)}"
UBOOT_EXTLINUX_TARGETS += "${@bb.utils.contains_any('BOOTDEVICE_LABELS', [ 'nand-2-256', 'nor-nand-2-256' ], 'target-nand', '', d)}"
# Define labels for each target
# (mandatory to allow specific var override if needed)
UBOOT_EXTLINUX_LABELS_target-sdcard += "rootfs"
UBOOT_EXTLINUX_LABELS_target-emmc += "rootfs"
UBOOT_EXTLINUX_LABELS_target-nand += "rootfs"
# Define specific bootprefix for each target
UBOOT_EXTLINUX_BOOTPREFIXES_target-sdcard = "${DEVICE_SDCARD}_"
UBOOT_EXTLINUX_BOOTPREFIXES_target-emmc = "${DEVICE_EMMC}_"
UBOOT_EXTLINUX_BOOTPREFIXES_target-nand = "${DEVICE_NAND}_"
# Define ROOT overrides for each target
UBOOT_EXTLINUX_ROOT_target-nand = "ubi.mtd=UBI rootfstype=ubifs root=ubi0:rootfs"
UBOOT_EXTLINUX_ROOT_target-sdcard = "root=PARTUUID=${DEVICE_PARTUUID_ROOTFS_SDCARD}"
UBOOT_EXTLINUX_ROOT_target-emmc = "root=PARTUUID=${DEVICE_PARTUUID_ROOTFS_EMMC}"
# Define INITRD overrides for nand target
UBOOT_EXTLINUX_INITRD_target-nand = ""
# -----------------------------------------------------------------------------
# Append specific examples configs
# -----------------------------------------------------------------------------
# Enable UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG var that allows to configure
# additional target:
#   UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG = "extra-target"
# Then define new label(s) to append to the label list from current target
#   UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[extra-target] = "newlabel1 newlabel2"
# This will create new 'extlinux.conf' file with name 'extra-target_extlinux.conf'
# that will use UBOOT_EXTLINUX_LABELS label list defined for current target plus
# the 'newlabel1' and 'newlabel2' labels.
# -----------------------------------------------------------------------------
# Define additional extra targets to consider
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-sdcard += "${STM32MP_DT_FILES_DK}"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-sdcard += "${STM32MP_DT_FILES_ED}"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-sdcard += "${STM32MP_DT_FILES_EV}"
UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-sdcard += " ${STM32MP_DT_FILES_YA157C}"


#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-emmc += "${STM32MP_DT_FILES_ED}"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-emmc += "${STM32MP_DT_FILES_EV}"
UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-emmc += "${STM32MP_DT_FILES_YA157C}"


#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-nand += "${STM32MP_DT_FILES_ED}"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-nand += "${STM32MP_DT_FILES_EV}"
UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG_target-nand += "${STM32MP_DT_FILES_YA157C}"


# Define extra label configuration
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157c-dk2] += "stm32mp157c-dk2-a7"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157c-dk2] += "stm32mp157c-dk2-m4"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157c-ev1] += "stm32mp157c-ev1-a7"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157c-ev1] += "stm32mp157c-ev1-m4"

#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157f-dk2] += "stm32mp157f-dk2-a7"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157f-dk2] += "stm32mp157f-dk2-m4"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157f-ev1] += "stm32mp157f-ev1-a7"
#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157f-ev1] += "stm32mp157f-ev1-m4"

#UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157c-ya157c-v2] += "stm32mp157c-ya157c-v2"
UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157c-ya157c-v2] += "stm32mp157c-ya157c-hdmi-v2"
UBOOT_EXTLINUX_TARGETS_EXTRA_CONFIG[stm32mp157c-ya157c-v2] += "stm32mp157c-ya157c-lcd-v2"



# -----------------------------------------------------------------------------
# Configure myir labels
# -----------------------------------------------------------------------------
#UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157c-ya157c-v2 = "ya157c-core"
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157c-ya157c-hdmi-v2 = "stm32mp157c-ya157c-hdmi-v2"
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157c-ya157c-lcd-v2 = "stm32mp157c-ya157c-lcd-v2"

#UBOOT_EXTLINUX_FDT_stm32mp157c-ya157c-v2 = "/stm32mp157c-ya157c-v2.dtb"
UBOOT_EXTLINUX_FDT_stm32mp157c-ya157c-hdmi-v2 = "/stm32mp157c-ya157c-hdmi-v2.dtb"
UBOOT_EXTLINUX_FDT_stm32mp157c-ya157c-lcd-v2 = "/stm32mp157c-ya157c-lcd-v2.dtb"



# -----------------------------------------------------------------------------
# Configure A7 examples labels
# -----------------------------------------------------------------------------
# Define MENU DESCRIPTION overrides for new A7 labels
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157c-dk2-a7 = "stm32mp157c-dk2-a7-examples"
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157c-ev1-a7 = "stm32mp157c-ev1-a7-examples"
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157f-dk2-a7 = "stm32mp157f-dk2-a7-examples"
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157f-ev1-a7 = "stm32mp157f-ev1-a7-examples"
# Define FDT overrides for new A7 labels
UBOOT_EXTLINUX_FDT_stm32mp157c-dk2-a7 = "/stm32mp157c-dk2-a7-examples.dtb"
UBOOT_EXTLINUX_FDT_stm32mp157c-ev1-a7 = "/stm32mp157c-ev1-a7-examples.dtb"
UBOOT_EXTLINUX_FDT_stm32mp157f-dk2-a7 = "/stm32mp157f-dk2-a7-examples.dtb"
UBOOT_EXTLINUX_FDT_stm32mp157f-ev1-a7 = "/stm32mp157f-ev1-a7-examples.dtb"

# -----------------------------------------------------------------------------
# Configure M4 examples labels
# -----------------------------------------------------------------------------
# Define MENU DESCRIPTION overrides for new A7 labels
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157c-dk2-m4 = "stm32mp157c-dk2-m4-examples"
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157c-ev1-m4 = "stm32mp157c-ev1-m4-examples"
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157f-dk2-m4 = "stm32mp157f-dk2-m4-examples"
UBOOT_EXTLINUX_MENU_DESCRIPTION_stm32mp157f-ev1-m4 = "stm32mp157f-ev1-m4-examples"
# Define FDT overrides for new M4 labels
UBOOT_EXTLINUX_FDT_stm32mp157c-dk2-m4 = "/stm32mp157c-dk2-m4-examples.dtb"
UBOOT_EXTLINUX_FDT_stm32mp157c-ev1-m4 = "/stm32mp157c-ev1-m4-examples.dtb"
UBOOT_EXTLINUX_FDT_stm32mp157f-dk2-m4 = "/stm32mp157f-dk2-m4-examples.dtb"
UBOOT_EXTLINUX_FDT_stm32mp157f-ev1-m4 = "/stm32mp157f-ev1-m4-examples.dtb"
