/*
 * Copyright 2020-2022, Hojin Koh
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

// An input "hidden iterator" wrapper for hiding the underlying containers
#pragma once
#include <cppcfwv0/pimpl-static.h>
#include <cppcfwv0/config/config.h>
#include <utility>

namespace cppcfwv0 {

  // The value wrapper to properly support -> operator
  template <typename T>
  struct HIterValueWrapper {
    HIterValueWrapper(const T& val) : val{val} {}
    T const* operator->() const {return &val;}
    T* operator->() {return &val;}
  private:
    T val;
  };


  // The Derived parameter is to make each hidden iterator class different
  // Base class for input forward iterators
  template <class Derived, typename T, int SIZE = config::sizeIterator>
  struct HIterBase {
    HIterBase();
    HIterBase(const void* pItr);
    ~HIterBase();

    HIterBase(const HIterBase& rhs);
    HIterBase& operator=(const HIterBase& rhs);

    using value_type = T;
    bool operator==(const HIterBase& rhs) const;
    bool operator!=(const HIterBase& rhs) const;
    HIterBase& operator++();
    HIterBase operator++(int);

    T const operator*() const;
    HIterValueWrapper<T> const operator->() const;
    T const getValue() const; // Useless definition in this class

  protected:
    class Impl; PImplS<Impl, SIZE> pimpl;
  };


  // Case when the output type and that of the underlying container is identical
  template <class Derived, typename T, int SIZE = config::sizeIterator>
  struct HIter : public HIterBase<Derived, T, SIZE> {
    T const& operator*() const;
    T const* operator->() const;
  };

  // Special case when the output type is const char*
  template <class Derived, int SIZE>
  struct HIter<Derived, const char*, SIZE> : public HIterBase<Derived, const char*, SIZE> {
    const char* operator*() const;
  };

}

