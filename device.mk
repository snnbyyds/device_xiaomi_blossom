#
# Copyright (C) 2023 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Enable updating of APEXes
$(call inherit-product, $(SRC_TARGET_DIR)/product/updatable_apex.mk)

# Dynamic Partitions
PRODUCT_USE_DYNAMIC_PARTITIONS := true
PRODUCT_BUILD_SUPER_PARTITION := false

# Installs gsi keys into ramdisk, to boot a developer GSI with verified boot.
$(call inherit-product, $(SRC_TARGET_DIR)/product/developer_gsi_keys.mk)

# Properties
include $(LOCAL_PATH)/vendor_logtag.mk

# Rootdir
PRODUCT_PACKAGES += \
    fstab.mt6765 \
    fstab.mt6762 \
    fstab.mt6765_ramdisk \
    fstab.mt6762_ramdisk \
    init.connectivity.rc \
    init.modem.rc \
    init.mt6765.rc \
    init.mt6762.rc \
    init.mt6765.usb.rc \
    init.project.rc \
    init.sensor_1_0.rc \
    ueventd.mtk.rc \
    init.ago.rc \
    init.mt6765.volte.rc \
    fstab.enableswap

# Recovery
PRODUCT_PACKAGES += \
    init.recovery.mt6765.rc \
    init.recovery.mt6762.rc

# fastbootd
PRODUCT_PACKAGES += \
    android.hardware.fastboot@1.1-impl.custom \
    fastbootd

# Audio
PRODUCT_PACKAGES += \
    android.hardware.audio.service \
    android.hardware.audio.common-util.vendor \
    android.hardware.audio.common@5.0 \
    android.hardware.audio.common@6.0 \
    android.hardware.audio.common@6.0-util.vendor \
    android.hardware.audio.effect@6.0-util.vendor \
    android.hardware.audio.effect@6.0 \
    android.hardware.audio.effect@6.0-impl \
    android.hardware.audio@6.0 \
    android.hardware.audio@6.0-impl \
    android.hardware.audio@6.0-util.vendor \
    android.hardware.bluetooth.audio-impl \
    android.hardware.bluetooth.audio@2.0 \
    android.hardware.bluetooth.audio@2.1 \
    audio.bluetooth.default \
    audio.r_submix.default \
    audio.usb.default \
    audio_policy.stub \
    libtinycompress \
    libtinyxml \
    libaudiofoundation \
    libaudiofoundation.vendor

PRODUCT_COPY_FILES += \
    $(call find-copy-subdir-files,*,$(LOCAL_PATH)/configs/audio/,$(TARGET_COPY_OUT_VENDOR)/etc)

PRODUCT_COPY_FILES += \
    frameworks/av/services/audiopolicy/config/a2dp_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/a2dp_audio_policy_configuration.xml \
    frameworks/av/services/audiopolicy/config/a2dp_in_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/a2dp_in_audio_policy_configuration.xml \
    frameworks/av/services/audiopolicy/config/bluetooth_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/bluetooth_audio_policy_configuration.xml \
    frameworks/av/services/audiopolicy/config/r_submix_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/r_submix_audio_policy_configuration.xml \
    frameworks/av/services/audiopolicy/config/usb_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/usb_audio_policy_configuration.xml \
    frameworks/av/services/audiopolicy/config/default_volume_tables.xml:$(TARGET_COPY_OUT_VENDOR)/etc/default_volume_tables.xml

# Health
PRODUCT_PACKAGES += \
    android.hardware.health@2.1-impl \
    android.hardware.health@2.1-impl.recovery \
    android.hardware.health@2.1-service

# Boot animation
TARGET_SCREEN_HEIGHT := 1600
TARGET_SCREEN_WIDTH := 720
TARGET_BOOT_ANIMATION_RES := 720

# Screen density
PRODUCT_AAPT_CONFIG := xhdpi
PRODUCT_AAPT_PREF_CONFIG := xhdpi
PRODUCT_AAPT_PREBUILT_DPI := xhdpi hdpi

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.software.verified_boot.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.verified_boot.xml \
    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.audio.low_latency.xml \
    frameworks/native/data/etc/android.software.midi.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.midi.xml

# Prebuilts - Kernel
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)-kernel/dtb.img:dtb.img \
    $(call find-copy-subdir-files,*,$(LOCAL_PATH)-kernel/modules,$(TARGET_COPY_OUT_VENDOR)/lib/modules)

# Prebuilts - Touch screen (For recovery)
PRODUCT_COPY_FILES += \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/chipone-tddi-tianma.bin:recovery/root/vendor/firmware/chipone-tddi-tianma.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/chipone-tddi-truly.bin:recovery/root/vendor/firmware/chipone-tddi-truly.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/focaltech_aa_ts_fw_helitai.bin:recovery/root/vendor/firmware/focaltech_aa_ts_fw_helitai.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/focaltech_ab_ts_fw_helitai.bin:recovery/root/vendor/firmware/focaltech_ab_ts_fw_helitai.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/gt1151_default_firmware2.img:recovery/root/vendor/firmware/gt1151_default_firmware2.img \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/hdl_firmware.img:recovery/root/vendor/firmware/hdl_firmware.img \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/Himax_firmware.bin:recovery/root/vendor/firmware/Himax_firmware.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/Himax_mpfw.bin:recovery/root/vendor/firmware/Himax_mpfw.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/hx_criteria.csv:recovery/root/vendor/firmware/hx_criteria.csv \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/ilitek_fw.bin:recovery/root/vendor/firmware/ilitek_fw.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/novatek_ts_djn_fw.bin:recovery/root/vendor/firmware/novatek_ts_djn_fw.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/novatek_ts_djn_mp.bin:recovery/root/vendor/firmware/novatek_ts_djn_mp.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/novatek_ts_ebbg_fw.bin:recovery/root/vendor/firmware/novatek_ts_ebbg_fw.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/novatek_ts_ebbg_mp.bin:recovery/root/vendor/firmware/novatek_ts_ebbg_mp.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/novatek_ts_hlt_fw.bin:recovery/root/vendor/firmware/novatek_ts_hlt_fw.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/novatek_ts_hlt_mp.bin:recovery/root/vendor/firmware/novatek_ts_hlt_mp.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/novatek_ts_truly_fw.bin:recovery/root/vendor/firmware/novatek_ts_truly_fw.bin \
    vendor/xiaomi/blossom/proprietary/vendor/firmware/novatek_ts_truly_mp.bin:recovery/root/vendor/firmware/novatek_ts_truly_mp.bin

# FM Radio
PRODUCT_PACKAGES += \
    FMRadio

# HIDL
PRODUCT_PACKAGES += \
    android.hidl.base@1.0 \
    android.hidl.allocator@1.0 \
    android.hidl.base@1.0.vendor \
    android.hidl.allocator@1.0.vendor \
    libhidltransport \
    libhidltransport.vendor \
    libhwbinder \
    libhwbinder.vendor

# Shims
PRODUCT_PACKAGES += \
    libshim_audio

# Soong namespaces
PRODUCT_SOONG_NAMESPACES += \
    $(LOCAL_PATH)

# Shipping API Level
PRODUCT_SHIPPING_API_LEVEL := 29

# Inherit the proprietary files
$(call inherit-product, vendor/xiaomi/blossom/blossom-vendor.mk)
