/*
 * Copyright 2020-2021, Hojin Koh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// A general-purpose registry utility class with name, description and some type
#pragma once
#include <cppcfwv0/config/config.h>
#include <cppcfwv0/pimpl-static.h>
#include <cppcfwv0/hiter.h>

#include <utility>

namespace cppcfwv0 {


  // Basically a 3-element append-only const container
  template <class Derived, typename T>
  struct Reg {
    void add(const char* name, const T& obj, const char* desc = "");
    bool has(const char* name) const;
    decltype(sizeof(0)) size() const;

    const T& get(const char* name) const;
    const char* getDesc(const char* name) const;

    struct Iter : public ::cppcfwv0::HIter<Iter, const char*> {
      using HIter<Iter, const char*>::HIter;
    };
    const Iter begin() const;
    const Iter end() const;

    Reg();
    ~Reg();
    Reg(Reg&& rhs) noexcept;
    Reg& operator=(Reg&& rhs) noexcept;
    Reg(const Reg& rhs);
    Reg& operator=(const Reg& rhs);
  private:
    class Impl; PImplS<Impl, config::sizeReg> pimpl;
  }; // end Reg class

}
