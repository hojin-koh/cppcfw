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

// Implementation of the straightforward pimpl wrapper
#pragma once
#include <cppcfwv0/pimpl.h>

#include <utility> // for forward

namespace cppcfwv0 {

  // == Ctor/Dtor ==

  template <class T>
  template <typename... Args>
  PImpl<T>::PImpl(Args&&... args) : m_ptr{new T{std::forward<Args>(args)...}} {}

  template <class T>
  PImpl<T>::~PImpl() {
    if (m_ptr) delete m_ptr;
  }

  // == Move and Copy ==

  template <class T>
  PImpl<T>::PImpl(PImpl<T>&& rhs) noexcept : m_ptr{rhs.m_ptr} {
    rhs.m_ptr = nullptr;
  }

  template <class T>
  PImpl<T>& PImpl<T>::operator=(PImpl<T>&& rhs) noexcept {
    if (m_ptr != rhs.m_ptr) {
      if (m_ptr) delete m_ptr;
      m_ptr = rhs.m_ptr;
      rhs.m_ptr = nullptr;
    }

    return *this;
  }

  template <class T>
  PImpl<T>::PImpl(const PImpl<T>& rhs) : m_ptr{new T{*rhs.m_ptr}} {}

  template <class T>
  PImpl<T>& PImpl<T>::operator=(const PImpl<T>& rhs) {
    if (m_ptr != rhs.m_ptr) {
      if (m_ptr) delete m_ptr;
      m_ptr = new T{*rhs.m_ptr};
    }
    return *this;
  }

  // == Underlying ==

  template <class T>
  T* PImpl<T>::operator->() { return m_ptr; }

  template <class T>
  const T* PImpl<T>::operator->() const { return m_ptr; }

  template <class T>
  T& PImpl<T>::operator*() { return *m_ptr; }

  template <class T>
  const T& PImpl<T>::operator*() const { return *m_ptr; }

}

