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

// A "hidden iterator" wrapper for hiding the underlying containers
#pragma once
#include <cppcfwv0/pimpl-static.h>
#include <cppcfwv0/config/config.h>

namespace cppcfwv0 {

  template <class Derived, typename T, int SIZE = config::sizeIterator>
  struct HIter {
    HIter();
    HIter(const void* pItr);
    ~HIter();

    HIter(const HIter& rhs);
    HIter(HIter&& rhs) noexcept;
    HIter& operator=(const HIter& rhs);
    HIter& operator=(HIter&& rhs) noexcept;

    using value_type = T;
    bool operator==(const HIter& rhs) const;
    bool operator!=(const HIter& rhs) const;
    HIter& operator++();
    HIter operator++(int);
    HIter& operator--();
    HIter operator--(int);

    value_type const& operator*() const;
    value_type& operator*();
    value_type const* operator->() const;
    value_type* operator->();

  protected:
    class Impl; PImplS<Impl, SIZE> pimpl;
  };

}

