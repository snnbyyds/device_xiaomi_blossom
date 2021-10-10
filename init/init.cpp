/*
 * Copyright (C) 2021 crDroid Android Project
 * Copyright (C) 2020 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fstream>
#include <string>
#include <cstring>
#include <sys/sysinfo.h>

#include <android-base/properties.h>
#include <libinit_variants.h>
#include <libinit_utils.h>

#include "vendor_init.h"

using android::base::GetProperty;

void load_dalvik_properties()
{
    char const *heapstartsize;
    char const *heapgrowthlimit;
    char const *heapsize;
    char const *heapminfree;
    char const *heapmaxfree;
    char const *heaptargetutilization;
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram >= 5ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        heapstartsize = "16m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.5";
        heapminfree = "8m";
        heapmaxfree = "32m";
    } else if (sys.totalram >= 3ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-4096-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.6";
        heapminfree = "8m";
        heapmaxfree = "16m";
    } else {
        // from - phone-xhdpi-2048-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.75";
        heapminfree = "512k";
        heapmaxfree = "8m";
    }

    property_override("dalvik.vm.heapstartsize", heapstartsize);
    property_override("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_override("dalvik.vm.heapsize", heapsize);
    property_override("dalvik.vm.heaptargetutilization", heaptargetutilization);
    property_override("dalvik.vm.heapminfree", heapminfree);
    property_override("dalvik.vm.heapmaxfree", heapmaxfree);
}

bool check_device_has_fp() {
    std::ifstream ifs("/proc/bus/input/devices");
    std::string line;

    if (ifs.is_open()) {
        while (std::getline(ifs, line)) {
            if (line.find("uinput-") != std::string::npos)
                return true;
        }
        ifs.close();
    }
    return false;
}

void load_device_properties() {
    std::string country = GetProperty("ro.boot.hwc", "");
    std::string name = GetProperty("ro.boot.hwname", "");

    variant_info_t variant;

    if (name == "dandelion") {
        if (check_device_has_fp()) {
            if (country == "CN" || country == "CN_2PA") {
                // Redmi 10A (China)
                variant = {
                    .brand = "Redmi",
                    .device = "dandelion",
                    .name = "dandelion_cn",
                    .mod_device = "dandelion_c3l2",
                    .marketname = "Redmi 10A",
                    .model = "220233L2C",
                    .build_fingerprint = "Redmi/dandelion_cn/dandelion:11/RP1A.200720.011/V12.5.13.0.RCZCNXM:user/release-keys"
                };
            } else if (country == "Global" || country == "Global_VC") {
dandelion_10a_global:
                // Redmi 10A (Global)
                variant = {
                    .brand = "Redmi",
                    .device = "dandelion",
                    .name = "dandelion_global2",
                    .mod_device = "dandelion_c3l2_global",
                    .marketname = "Redmi 10A",
                    .model = "220233L2G",
                    .build_fingerprint = "Redmi/dandelion_global2/dandelion:11/RP1A.200720.011/V12.5.11.0.RCZMIXM:user/release-keys"
                };
            } else if (country == "India" || country == "India_VC") {
                // Redmi 10A / 10A Sport (India)
                variant = {
                    .brand = "Redmi",
                    .device = "dandelion",
                    .name = "dandelion_in2",
                    .mod_device = "dandelion_c3l2_in_global",
                    .marketname = "Redmi 10A / 10A Sport",
                    .model = "220233L2I",
                    .build_fingerprint = "Redmi/dandelion_in2/dandelion:11/RP1A.200720.011/V12.5.14.0.RCZINXM:user/release-keys"
                };
            } else
                goto dandelion_10a_global;  // fallback to global variant
        } else {  /* check_device_has_fp() */
            if (country == "CN" || country == "CN2PA") {
                // Redmi 9A (China)
                variant = {
                    .brand = "Redmi",
                    .device = "dandelion",
                    .name = "dandelion",
                    .mod_device = "dandelion",
                    .marketname = "Redmi 9A",
                    .model = "M2006C3LC",
                    .build_fingerprint = "Redmi/dandelion/dandelion:11/RP1A.200720.011/V12.5.21.0.RCDCNXM:user/release-keys"
                };
            } else if (country == "Global" || country == "Global_VC") {
dandelion_9a_global:
                // Redmi 9A (Global)
                variant = {
                    .brand = "Redmi",
                    .device = "dandelion",
                    .name = "dandelion_global",
                    .mod_device = "dandelion_global",
                    .marketname = "Redmi 9A",
                    .model = "M2006C3LG",
                    .build_fingerprint = "Redmi/dandelion_global/dandelion:11/RP1A.200720.011/V12.5.7.0.RCDMIXM:user/release-keys"
                };
            } else if (country == "India" || country == "India_VC") {
                // Redmi 9A / 9A Sport (India)
                variant = {
                    .brand = "Redmi",
                    .device = "dandelion",
                    .name = "dandelion_in",
                    .mod_device = "dandelion_in_global",
                    .marketname = "Redmi 9A / 9A Sport",
                    .model = "M2006C3LI",
                    .build_fingerprint = "Redmi/dandelion_in/dandelion:11/RP1A.200720.011/V12.5.9.0.RCDINXM:user/release-keys"
                };
            } else if (country == "India_9i") {
                // Redmi 9i / 9i Sport (India)
                variant = {
                    .brand = "Redmi",
                    .device = "dandelion",
                    .name = "dandelion_in",
                    .mod_device = "dandelion_in_global",
                    .marketname = "Redmi 9i / 9i Sport",
                    .model = "M2006C3LII",
                    .build_fingerprint = "Redmi/dandelion_in/dandelion:11/RP1A.200720.011/V12.5.9.0.RCDINXM:user/release-keys"
                };
            } else if (country == "VDF") {
                // Redmi 9AT (Global)
                variant = {
                    .brand = "Redmi",
                    .device = "dandelion",
                    .name = "dandelion_eea",
                    .mod_device = "dandelion_eea_global",
                    .marketname = "Redmi 9AT",
                    .model = "M2006C3LVG",
                    .build_fingerprint = "Redmi/dandelion_eea/dandelion:11/RP1A.200720.011/V12.5.7.0.RCDEUXM:user/release-keys"
                };
            } else
                goto dandelion_9a_global;  // fallback to global variant
        }  /* check_device_has_fp() */
    } else if (name == "angelica" || name == "angelica_second") {
        if (country == "Global" || country == "Global_DIP") {
angelica_global:
            // Redmi 9C (Global)
            variant = {
                .brand = "Redmi",
                .device = "angelica",
                .name = "angelica_global",
                .mod_device = "angelica_global",
                .marketname = "Redmi 9C",
                .model = "M2006C3MG",
                .build_fingerprint = "Redmi/angelica_global/angelica:11/RP1A.200720.011/V12.5.4.0.RCRMIXM:user/release-keys"
            };
        } else if (country == "Thailand") {
            // Redmi 9C (Thailand)
            variant = {
                .brand = "Redmi",
                .device = "angelica",
                .name = "angelica_global",
                .mod_device = "angelica_global",
                .marketname = "Redmi 9C",
                .model = "M2006C3MT",
                .build_fingerprint = "Redmi/angelica_global/angelica:11/RP1A.200720.011/V12.5.4.0.RCRMIXM:user/release-keys"
            };
        } else
            goto angelica_global;  // fallback to global variant
    } else if (name == "angelican") {
        if (country == "Global" || country == "Global_DIP") {
angelican_global:
            // Redmi 9C NFC (Global)
            variant = {
                .brand = "Redmi",
                .device = "angelican",
                .name = "angelican_global",
                .mod_device = "angelican_global",
                .marketname = "Redmi 9C NFC",
                .model = "M2006C3MNG",
                .build_fingerprint = "Redmi/angelican_global/angelican:11/RP1A.200720.011/V12.5.3.0.RCSMIXM:user/release-keys"
            };
        } else
            goto angelican_global; // fallback to global variant
    } else if (name == "angelicain") {
        if (country == "India" || country == "India_DIP") {
angelicain_india:
            if (check_device_has_fp()) {
                // POCO C31 (India)
                variant = {
                    .brand = "POCO",
                    .device = "angelicain",
                    .name = "angelicain_in",
                    .mod_device = "angelicain_in_rf_global",
                    .marketname = "POCO C31",
                    .model = "211033MI",
                    .build_fingerprint = "POCO/angelicain_in/angelicain:11/RP1A.200720.011/V12.5.4.0.RCRINRF:user/release-keys"
                };
            } else {
                // POCO C3 (India)
                variant = {
                    .brand = "POCO",
                    .device = "angelicain",
                    .name = "angelicain",
                    .mod_device = "angelicain_in_global",
                    .marketname = "POCO C3",
                    .model = "M2006C3MI",
#if 0
                    .build_fingerprint = "POCO/angelicain/angelicain:10/QP1A.190711.020/V12.0.19.0.QCRINXM:user/release-keys"
#else
                    /* POCO C3 didn't get A11 MIUI, using POCO C31's build fingerprint here */
                    .build_fingerprint = "POCO/angelicain_in/angelicain:11/RP1A.200720.011/V12.5.4.0.RCRINRF:user/release-keys"
#endif
                };
            }
        } else
            goto angelicain_india; // fallback to india variants
    } else if (name == "cattail") {
        if (country == "India" || country == "India_DIP") {
cattail_india:
            // Redmi 9 / 9 Activ (India)
            variant = {
                .brand = "Redmi",
                .device = "cattail",
                .name = "cattail",
                .mod_device = "cattail_in_global",
                .marketname = "Redmi 9 / 9 Activ",
                .model = "M2006C3MII",
                .build_fingerprint = "Redmi/cattail/cattail:11/RP1A.200720.011/V12.5.6.0.RCTINXM:user/release-keys"
            };
        } else
            goto cattail_india;  // fallback to india variant
    } else
        goto dandelion_10a_global;  // fallback to redmi 10a global variant
    set_variant_props(variant);
}

void vendor_load_properties() {
    load_dalvik_properties();
    load_device_properties();
}
