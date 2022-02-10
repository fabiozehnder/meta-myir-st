SUMMARY = "OpenSTLinux core image."
LICENSE = "Proprietary"

include recipes-myir/images/myir-image.inc

inherit core-image

IMAGE_LINGUAS = "en-us"

#IMAGE_FEATURES += "\
#    package-management  \
#    ssh-server-dropbear \    
#   "

# Enable use of extra partition(s)
ST_BOOTFS   ?= "1"
ST_VENDORFS ?= "1"
ST_USERFS   ?= "1"

# Define max size for ROOTFS image being built to this value
IMAGE_ROOTFS_MAXSIZE ?= "763904"



#
# INSTALL addons
#
CORE_IMAGE_EXTRA_INSTALL += " \
    resize-helper   \
    \
    packagegroup-framework-core-base    \
    packagegroup-framework-tools-base   \
    \
    ${@bb.utils.contains('COMBINED_FEATURES', 'optee', 'packagegroup-optee-core', '', d)}   \
    ${@bb.utils.contains('COMBINED_FEATURES', 'optee', 'packagegroup-optee-test', '', d)}   \
    \
    libgssapi-krb5 \
    \
    tcpdump         \
    packagegroup-core-full-cmdline-extended \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wifi', 'iw', '', d)}                       \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wifi', 'wpa-supplicant', '', d)}           \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wifi', 'hostapd', '', d)}                  \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wifi', 'wireless-regdb-static', '', d)}    \
    openssh-sftp \
    networkmanager \
    ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'dhcp-client', '', d)}                       \
    bridge-utils    \
    \
    "

#    ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd-networkd-configuration', '', d)}
#     usbip           


#    ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd-mount-partitions', '', d)} \
#    ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'userfs-cleanup-package', '', d)}   \
#    libgpiod        \
#    libgpiod-tools  \   
#    can-utils       \
#    ethtool         \    
#    packagegroup-framework-tools-network  \
#

# 
# 
#
# 
#

EXTRAZ = " \
    tzdata \
    packagegroup-core-ssh-openssh openssh openssh-keygen openssh-sftp-server \
    kernel-modules \
    coreutils \
    cpp \
    cpp-symlinks \
    g++ \
    g++-symlinks \
    gettext \
    git \
    ldd \
    libstdc++ \
    libstdc++-dev \
    ltrace \
    nano \
    coreutils \
    curl \
    fbset \
    i2c-tools \
    ifupdown \
    iproute2 \
    ntp ntp-tickadj \
    procps \
    sysfsutils \
    tcpdump \
    util-linux \
    util-linux-blkid \
    wpa-supplicant \
    dhcp-client \
"

IMAGE_INSTALL += " \
    ${EXTRAZ} \
"

#IMAGE_INSTALL_append += " \
#    resolvconf \
#"


IMAGE_INSTALL_remove += " \
    alsa-lib \
    alsa-plugins \
    alsa-state \
    alsa-state-stm32mp1 \
    alsa-topology-conf \
    alsa-ucm-conf \
    alsa-utils \
    alsa-utils-scripts \
    demo-application-3d-cube \
    demo-application-bluetooth \
    demo-application-camera \
    demo-application-netdata-hotspot \
    demo-application-video \
    demo-hotspot-wifi \
    demo-launcher \
    gstreamer1.0 \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-base \
    gtk+3 \
"

PACKAGE_EXCLUDE += " alsa pulseaudio gstreamer "

