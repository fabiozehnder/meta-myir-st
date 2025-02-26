#@DESCRIPTION: STM32MP machine storage device configuration

# -----------------------------------------------------------------------------
# Define device storage name and type mapping
# -----------------------------------------------------------------------------
DEVICE_STORAGE ?= "EMMC:mmc1, NAND:nand0, NOR:nor0, SDCARD:mmc0"

# -----------------------------------------------------------------------------
# Define device storage name alias
# -----------------------------------------------------------------------------
DEVICE_STORAGE_NAMES += "EMMC"
DEVICE_STORAGE_NAMES += "NAND"
DEVICE_STORAGE_NAMES += "NOR"
DEVICE_STORAGE_NAMES += "SDCARD"

# -----------------------------------------------------------------------------
# Define device storage type
# -----------------------------------------------------------------------------
DEVICE_STORAGE_TYPES += "mmc0"
DEVICE_STORAGE_TYPES += "mmc1"
DEVICE_STORAGE_TYPES += "mmc2"
DEVICE_STORAGE_TYPES += "nand0"
DEVICE_STORAGE_TYPES += "nor0"

python () {
    """
    This function configure dynamically the needed alias between generic storage
    device name and device type.
    Output for this function is the initialization of:
        DEVICE_<device_name> = '<device_type>'
        DEVICE_<device_type> = '<device_name>'
    """
    device_storage_config = d.getVar('DEVICE_STORAGE') or ''
    if not device_storage_config:
        return
    if not device_storage_config.strip():
        return
    if len(device_storage_config.split(',')) > 0:
        # Init supported device storage configuration
        supported_device_names = (d.getVar('DEVICE_STORAGE_NAMES') or '').split()
        supported_device_types = (d.getVar('DEVICE_STORAGE_TYPES') or '').split()
        # Loop for all storage device configurations
        for device_storage in device_storage_config.split(','):
            device_name = device_storage.split(':')[0].strip()
            device_type = device_storage.split(':')[1].strip()
            # Check for configuration consistency
            if device_name and device_type:
                # Make sure configuration is correctly done
                if device_name not in supported_device_names:
                    bb.fatal('Wrong DEVICE_STORAGE configuration: "%s" is not part of supported device name (%s)' % (device_name, supported_device_names))
                if device_type not in supported_device_types:
                    bb.fatal('Wrong DEVICE_STORAGE configuration: "%s" is not part of supported device type (%s)' % (device_type, supported_device_types))
                # Configure alias
                d.setVar('DEVICE_%s' % device_name, device_type)
                d.setVar('DEVICE_%s' % device_type, device_name)
            else:
                bb.fatal('Wrong DEVICE_STORAGE configuration: expecting DEVICE_STORAGE = "<device_name1>:<devie_type1>,<device_name2>:<device_type2>"')
}

# -----------------------------------------------------------------------------
# EMMC
# Extra space is required to store 'Protective MBR' and 'Primary GPT Header'
# Currently the required size is 17kBytes (i.e. 0x4400)
# We need to align this size to get the first offset to use
DEVICE_START_OFFSET_EMMC    ?= "0x00080000"
DEVICE_ALIGNMENT_SIZE_EMMC  ?= "0x00080000"

# Specific to EMMC, there are two boot partitions using specific offset to access
DEVICE_START_OFFSET_BOOT0_EMMC ?= "boot1"
DEVICE_START_OFFSET_BOOT1_EMMC ?= "boot2"

# Configure the rootfs partition uid used in gpt partition table for EMMC
DEVICE_PARTUUID_ROOTFS_EMMC ?= "${@d.getVar(d.expand('DEVICE_PARTUUID_ROOTFS_${DEVICE_EMMC}')) or ''}"

# Configure the list of boards that enable EMMC
DEVICE_BOARD_ENABLE_EMMC += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'emmc', '${STM32MP_DT_FILES_ED}', '', d)}"
DEVICE_BOARD_ENABLE_EMMC += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'emmc', '${STM32MP_DT_FILES_EV}', '', d)}"
DEVICE_BOARD_ENABLE_EMMC += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'emmc', '${STM32MP_DT_FILE_YA157C}', '', d)}"


# -----------------------------------------------------------------------------
# NAND
DEVICE_START_OFFSET_NAND   ?= "0x00000000"
DEVICE_ALIGNMENT_SIZE_NAND ?= "0x00040000"

# Configure the list of boards that enable EMMC
DEVICE_BOARD_ENABLE_NAND   += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'nand-2-256', '${STM32MP_DT_FILES_ED}', '', d)}"
DEVICE_BOARD_ENABLE_NAND   += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'nand-2-256', '${STM32MP_DT_FILES_EV}', '', d)}"
DEVICE_BOARD_ENABLE_NAND   += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'nand-2-256', '${STM32MP_DT_FILE_YA157C}', '', d)}"


# -----------------------------------------------------------------------------
# NOR
DEVICE_START_OFFSET_NOR    ?= "0x00000000"
DEVICE_ALIGNMENT_SIZE_NOR  ?= "0x00010000"

# Configure the list of boards that enable EMMC
DEVICE_BOARD_ENABLE_NOR    += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'nor-sdcard' , '${STM32MP_DT_FILES_EV}', '', d)}"

# -----------------------------------------------------------------------------
# SDCARD
# Extra space is required to store 'Protective MBR' and 'Primary GPT Header'
# Currently the required size is 17kBytes (i.e. 0x4400)
# We need to align this size to get the first offset to use
DEVICE_START_OFFSET_SDCARD    ?= "0x00004400"
DEVICE_ALIGNMENT_SIZE_SDCARD  ?= "0x00000200"

# Configure the rootfs partition uid used in gpt partition table for SDCARD
DEVICE_PARTUUID_ROOTFS_SDCARD ?= "${@d.getVar(d.expand('DEVICE_PARTUUID_ROOTFS_${DEVICE_SDCARD}')) or ''}"

# Configure the list of boards that enable SDCARD
DEVICE_BOARD_ENABLE_SDCARD    += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'sdcard', '${STM32MP_DT_FILES_DK}', '', d)}"
DEVICE_BOARD_ENABLE_SDCARD    += "${@bb.utils.contains('BOOTDEVICE_LABELS', 'sdcard', '${STM32MP_DT_FILE_YA157C}', '', d)}"
DEVICE_BOARD_ENABLE_SDCARD    += "${@bb.utils.contains_any('BOOTDEVICE_LABELS', [ 'sdcard', 'nor-sdcard' ], '${STM32MP_DT_FILES_ED}', '', d)}"
DEVICE_BOARD_ENABLE_SDCARD    += "${@bb.utils.contains_any('BOOTDEVICE_LABELS', [ 'sdcard', 'nor-sdcard' ], '${STM32MP_DT_FILES_EV}', '', d)}"

# -----------------------------------------------------------------------------
# Fixed configuration from U-Boot source code
# -----------------------------------------------------------------------------
DEVICE_PARTUUID_ROOTFS_mmc0 ?= "e91c4e10-16e6-4c0e-bd0e-77becf4a3582"
DEVICE_PARTUUID_ROOTFS_mmc1 ?= "491f6117-415d-4f53-88c9-6e0de54deac6"
DEVICE_PARTUUID_ROOTFS_mmc2 ?= "fd58f1c7-be0d-4338-8ee9-ad8f050aeb18"
