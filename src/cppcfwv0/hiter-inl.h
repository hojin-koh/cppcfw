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

// Implementation of the hidden iterator wrapper
#pragma once
#include <cppcfwv0/hiter.h>
#include <cppcfwv0/pimpl-static-inl.h>

#include <stdexcept>
#include <string>

namespace cppcfwv0 {

  namespace {
    namespace sfinae {
      template <typename T, typename = void>
      struct can_increment : std::false_type {};
      template <typename T>
      struct can_increment<T, std::void_t<decltype(std::declval<T>()++)>> : std::true_type {};
      template <typename T>
      inline constexpr bool can_increment_v = can_increment<T>::value;

      template <typename T, typename = void>
      struct can_decrement : std::false_type {};
      template <typename T>
      struct can_decrement<T, std::void_t<decltype(std::declval<T>()--)>> : std::true_type {};
      template <typename T>
      inline constexpr bool can_decrement_v = can_decrement<T>::value;
    }
  }

  template <typename DerivedOuter, typename Derived, typename Itr>
  struct HIterImpl {
    Itr m_itr;

    HIterImpl(const void *pItr) : m_itr{*static_cast<const Itr*>(pItr)} {}
    HIterImpl() {}
  protected: // To prevent polymorphic use
    ~HIterImpl() {}
  };


  template <class Derived, typename T>
  HIter<Derived,T>::HIter() : pimpl{} {}

  template <class Derived, typename T>
  HIter<Derived,T>::HIter(const void *pItr) : pimpl{pItr} {}

  template <class Derived, typename T>
  HIter<Derived,T>::~HIter() {}


  template <class Derived, typename T>
  HIter<Derived,T>::HIter(const HIter<Derived,T>& rhs) = default;

  template <class Derived, typename T>
  HIter<Derived,T>::HIter(HIter<Derived,T>&& rhs) noexcept = default;

  template <class Derived, typename T>
  HIter<Derived,T>& HIter<Derived,T>::operator=(const HIter<Derived,T>& rhs) = default;

  template <class Derived, typename T>
  HIter<Derived,T>& HIter<Derived,T>::operator=(HIter<Derived,T>&& rhs) noexcept = default;


  template <class Derived, typename T>
  bool HIter<Derived,T>::operator==(const HIter& rhs) const {
    return pimpl->m_itr == rhs.pimpl->m_itr;
  }

  template <class Derived, typename T>
  bool HIter<Derived,T>::operator!=(const HIter& rhs) const {
    return pimpl->m_itr != rhs.pimpl->m_itr;
  }

  template <class Derived, typename T>
  HIter<Derived,T>& HIter<Derived,T>::operator++() {
    using Itr = decltype(pimpl->m_itr);
    if constexpr (sfinae::can_increment_v<Itr>) {
      ++(pimpl->m_itr);
    } else {
      throw std::domain_error(std::string("This iterator ") + typeid(Itr).name() + " does not support incrementing");
    }
    return *this;
  }

  template <class Derived, typename T>
  HIter<Derived,T> HIter<Derived,T>::operator++(int) {
    using Itr = decltype(pimpl->m_itr);
    auto itrTmp = *this;
    if constexpr (sfinae::can_increment_v<Itr>) {
      (pimpl->m_itr)++;
    } else {
      throw std::domain_error(std::string("This iterator ") + typeid(Itr).name() + " does not support incrementing");
    }
    return itrTmp;
  }

  template <class Derived, typename T>
  HIter<Derived,T>& HIter<Derived,T>::operator--() {
    using Itr = decltype(pimpl->m_itr);
    if constexpr (sfinae::can_decrement_v<Itr>) {
      --(pimpl->m_itr);
    } else {
      throw std::domain_error(std::string("This iterator ") + typeid(Itr).name() + " does not support decrementing");
    }
    return *this;
  }

  template <class Derived, typename T>
  HIter<Derived,T> HIter<Derived,T>::operator--(int) {
    using Itr = decltype(pimpl->m_itr);
    auto itrTmp = *this;
    if constexpr (sfinae::can_decrement_v<Itr>) {
      (pimpl->m_itr)--;
    } else {
      throw std::domain_error(std::string("This iterator ") + typeid(Itr).name() + " does not support decrementing");
    }
    return itrTmp;
  }

  template <class Derived, typename T>
  const typename HIter<Derived,T>::value_type& HIter<Derived,T>::operator*() const {
    return *(pimpl->m_itr);
  }

  template <class Derived, typename T>
  typename HIter<Derived,T>::value_type& HIter<Derived,T>::operator*() {
    return *(pimpl->m_itr);
  }

  template <class Derived, typename T>
  const typename HIter<Derived,T>::value_type* HIter<Derived,T>::operator->() const {
    return &*(pimpl->m_itr);
  }

  template <class Derived, typename T>
  typename HIter<Derived,T>::value_type* HIter<Derived,T>::operator->() {
    return &*(pimpl->m_itr);
  }

}

#define CPPCFWV0_HITER_IMPL(classItr, typeValue, typeRealItr) \
  template class ::cppcfwv0::HIter<classItr, typeValue>; \
  template <> \
  struct cppcfwv0::HIter<classItr, typeValue>::Impl : public ::cppcfwv0::HIterImpl<classItr, cppcfwv0::HIter<classItr, typeValue>::Impl, typeRealItr>
