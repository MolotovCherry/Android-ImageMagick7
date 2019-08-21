# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# Common definitions for all variants.
#

LOCAL_PATH:= $(call my-dir)

# Derive a string like 'icudt 48l.dat' from a path like
# 'external/icu/icu4c/source/stubdata/icudt 48l.dat'
stubdata_path:= $(call my-dir)
dat_file := $(notdir $(wildcard $(stubdata_path)/*.dat))

include $(CLEAR_VARS)
LOCAL_MODULE := icu-data_host_i18n_apex
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(HOST_OUT)/com.android.i18n/etc/icu
LOCAL_MODULE_STEM := $(dat_file)
LOCAL_SRC_FILES := $(dat_file)
LOCAL_IS_HOST_MODULE := true
include $(BUILD_PREBUILT)

# Module definition producing ICU .dat prebuilt files in
# /system/etc/icu for standalone ART testing purposes. This is a
# temporary change needed until the ART Buildbot and Golem both fully
# support the Runtime APEX (see b/121117762). This module should never
# be shipped by default (i.e. should never be part of
# `PRODUCT_PACKAGE`.)
#
# TODO(b/121117762): Remove this module definition when the ART
# Buildbot and Golem have full support for the Runtime APEX.
include $(CLEAR_VARS)
LOCAL_MODULE := icu-data-art-test-i18n
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/etc/i18n_module/etc/icu
LOCAL_MODULE_STEM := $(dat_file)
LOCAL_SRC_FILES := $(dat_file)
include $(BUILD_PREBUILT)
