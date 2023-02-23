/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <libinit_utils.h>

#include <libinit_variants.h>

void set_variant_props(const variant_info_t variant) {
    set_ro_build_prop("brand", variant.brand, true);
    set_ro_build_prop("device", variant.device, true);
    set_ro_build_prop("name", variant.name, true);
    set_ro_build_prop("marketname", variant.marketname, true);
    set_ro_build_prop("model", variant.model, true);
    set_ro_build_prop("cert", variant.model, true);
    set_ro_build_prop("product", variant.model, false);
    set_ro_build_prop("fingerprint", variant.build_fingerprint, false);
    set_ro_build_prop("description", fingerprint_to_description(variant.build_fingerprint), false);

    property_override("ro.com.google.clientidbase", "android-xiaomi");
    property_override("ro.com.google.clientidbase.ms", "android-xiaomi-rev1");
    property_override("ro.product.mod_device", variant.mod_device);
    property_override("bluetooth.device.default_name", variant.marketname);
    property_override("vendor.usb.product_string", variant.marketname);
    property_override("ro.boot.hardware.sku", variant.device);
}
