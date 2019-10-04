/*
    This file is part of TON Blockchain Library.

    TON Blockchain Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    TON Blockchain Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with TON Blockchain Library.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2017-2019 Telegram Systems LLP
*/
#pragma once

#include "tonlib/mnemoniclib_export.h"
#include <string>
#include <vector>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

MNEMONICLIB_EXPORT void create(const char* mnemonic_password, void (*callback)(const char*, const char*));

MNEMONICLIB_EXPORT void getPrivateKey(const char* mnemonic, const char* mnemonic_password, void (*callback)(const char*, const char*));

MNEMONICLIB_EXPORT void isBasicSeed(const char* mnemonicwords, void(*callback)(const bool, const char*));

MNEMONICLIB_EXPORT void isPasswordSeed(const char* mnemonicwords, void(*callback)(const bool, const char*));

#ifdef __cplusplus
}  // extern "C"
#endif
