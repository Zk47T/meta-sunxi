SOC_FAMILY ??= ""
include conf/machine/include/soc-family.inc

MACHINEOVERRIDES =. "sunxi:sunxi64:"

PREFERRED_PROVIDER_virtual/kernel ?= "linux-mainline"
PREFERRED_VERSION_linux-mainline ?= "6.18.%"
PREFERRED_PROVIDER_u-boot ?= "u-boot"
PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot"

KERNEL_IMAGETYPE ?= "Image"

IMAGE_FSTYPES += "ext4 tar.gz wic.gz wic.bmap"

MACHINE_EXTRA_RRECOMMENDS = "kernel-modules"

UBOOT_LOCALVERSION = "-g${@d.getVar('SRCPV', True).partition('+')[2][0:7]}"

UBOOT_ENTRYPOINT ?= "0x40008000"
UBOOT_LOADADDRESS ?= "0x40008000"

#UBOOT_BINARY ?= "u-boot.itb"
SPL_BINARY ?= "u-boot-sunxi-with-spl.bin"

SERIAL_CONSOLES ?= "115200;ttyS0"
MACHINE_FEATURES ?= "alsa apm keyboard rtc serial screen usbgadget usbhost vfat"

SUNXI_BOOT_SPACE ?= "40"
# With CONFIG_OF_UPSTREAM, U-Boot's ${fdtfile} keeps the vendor directory
# (allwinner/board.dtb), so ship that path as well as the flat name.
SUNXI_DTB_BOOT_FILES = "${@' '.join(('%s %s;%s' % (os.path.basename(f), os.path.basename(f), f)) if os.path.dirname(f) else os.path.basename(f) for f in (d.getVar('KERNEL_DEVICETREE') or '').split())}"
IMAGE_BOOT_FILES ?= "${KERNEL_IMAGETYPE} boot.scr ${SUNXI_DTB_BOOT_FILES}"

WKS_FILES ?= "sunxi-sdcard-image.wks.in"
WKS_FILE_DEPENDS ?= "virtual/kernel u-boot"
