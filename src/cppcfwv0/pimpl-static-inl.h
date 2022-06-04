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

// Implementation of the static pimpl wrapper
#pragma once
#include <cppcfwv0/pimpl-static.h>

#include <utility> // for forward
#include <new> // for placement new

namespace cppcfwv0 {

  // == Ctor/Dtor ==

  template <class T, int SIZE, int ALIGN>
  template <typename... Args>
  PImplS<T, SIZE, ALIGN>::PImplS(Args&&... args) {
    static_assert(sizeof(T) <= SIZE, "Need bigger size on 2nd template parameter of PImplS<>");
    static_assert(ALIGN % alignof(T) == 0, "Need correct alignment on 3rd template parameter of PImplS<>");
    ::new (m_data) T{std::forward<Args>(args)...};
  }

  template <class T, int SIZE, int ALIGN>
  PImplS<T, SIZE, ALIGN>::~PImplS() {
    reinterpret_cast<T*>(m_data)->~T();
  }

  // == Move and Copy ==

  template <class T, int SIZE, int ALIGN>
  PImplS<T, SIZE, ALIGN>::PImplS(PImplS<T, SIZE, ALIGN>&& rhs) noexcept {
    ::new (m_data) T{std::move(*rhs)};
  }

  template <class T, int SIZE, int ALIGN>
  PImplS<T, SIZE, ALIGN>& PImplS<T, SIZE, ALIGN>::operator=(PImplS<T, SIZE, ALIGN>&& rhs) noexcept {
    if (m_data != rhs.m_data) {
      **this = std::move(*rhs);
    }
    return *this;
  }

  template <class T, int SIZE, int ALIGN>
  PImplS<T, SIZE, ALIGN>::PImplS(const PImplS<T, SIZE, ALIGN>& rhs) {
    ::new (m_data) T{*rhs};
  }

  template <class T, int SIZE, int ALIGN>
  PImplS<T, SIZE, ALIGN>& PImplS<T, SIZE, ALIGN>::operator=(const PImplS<T, SIZE, ALIGN>& rhs) {
    if (m_data != rhs.m_data) {
      **this = *rhs;
    }
    return *this;
  }


  // == Underlying ==

  template <class T, int SIZE, int ALIGN>
  T* PImplS<T, SIZE, ALIGN>::operator->() { return (reinterpret_cast<T*>(m_data)); }

  template <class T, int SIZE, int ALIGN>
  const T* PImplS<T, SIZE, ALIGN>::operator->() const { return (reinterpret_cast<const T*>(m_data)); }

  template <class T, int SIZE, int ALIGN>
  T& PImplS<T, SIZE, ALIGN>::operator*() { return *(reinterpret_cast<T*>(m_data)); }

  template <class T, int SIZE, int ALIGN>
  const T& PImplS<T, SIZE, ALIGN>::operator*() const { return *(reinterpret_cast<const T*>(m_data)); }

}

