/*
    This file is part of TON Blockchain Library.

    TON Blockchain Library is free software: you can redistribute it and/or
   modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    TON Blockchain Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with TON Blockchain Library.  If not, see
   <http://www.gnu.org/licenses/>.

    Copyright 2017-2019 Telegram Systems LLP
*/
#include "tonlib/mnemoniclib.h"
#include <string>
#include <vector>
#include <iostream>

#include "tonlib/keys/Mnemonic.h"

void create(const char* mnemonic_password, void (*callback)(const char*, const char*)) {
  SET_VERBOSITY_LEVEL(verbosity_ERROR);

  tonlib::Mnemonic::Options create_options;

  create_options.password = td::SecureString(std::string(mnemonic_password));

  auto mnemonic = tonlib::Mnemonic::create_new(std::move(create_options));

  if (mnemonic.is_error()) {
    callback({0}, mnemonic.error().to_string().c_str());
  } else {
    auto words = mnemonic.move_as_ok().get_words();

    std::string res;

    for (const auto &word : words) {
      if (!res.empty()) {
        res += " ";
      }

      res += std::string(word.data(), word.size());
    }

    callback(res.c_str(), {0});
  }
}

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

void getPrivateKey(const char* mnemonicwords, const char* mnemonic_password, void (*callback)(const char*, const char*)) {
  SET_VERBOSITY_LEVEL(verbosity_ERROR);

  auto mnemonic = tonlib::Mnemonic::create(td::SecureString(std::string(mnemonicwords)), td::SecureString(std::string(mnemonic_password)));

  if (mnemonic.is_error()) {
    callback({0}, mnemonic.error().to_string().c_str());
  } else {
    auto pk = mnemonic.move_as_ok().to_private_key().as_octet_string();

    std::string res;

    res += std::string(pk.data(), pk.size());
    callback(string_to_hex(res).c_str(), {0});
  }
}

void isBasicSeed(const char* mnemonicwords, void(*callback)(const bool, const char*)) {
  SET_VERBOSITY_LEVEL(verbosity_ERROR);

  auto mnemonic = tonlib::Mnemonic::create(td::SecureString(std::string(mnemonicwords)), td::SecureString(std::string("")));

  if (mnemonic.is_error()) {
    callback(false, mnemonic.error().to_string().c_str());
  } else {
    auto is_basic = mnemonic.move_as_ok().is_basic_seed();

    if (is_basic) {
      callback(true, {0});
    } else {
      callback(false, {0});
    }
  }
}

void isPasswordSeed(const char* mnemonicwords, void(*callback)(const bool, const char*)) {
  SET_VERBOSITY_LEVEL(verbosity_ERROR);

  auto mnemonic = tonlib::Mnemonic::create(td::SecureString(std::string(mnemonicwords)), td::SecureString(std::string("")));

  if (mnemonic.is_error()) {
    callback(false, mnemonic.error().to_string().c_str());
  } else {
    auto is_basic = mnemonic.move_as_ok().is_password_seed();

    if (is_basic) {
      callback(true, {0});
    } else {
      callback(false, {0});
    }
  }
}
