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
#include <cppcfwv0/sfinae.h>

#include <stdexcept>
#include <string>

namespace cppcfwv0 {

  namespace {
    namespace sfinae {
      CPPCFWV0_SFINAE_TYPE_TRAIT(canIncrement, std::declval<T>()++);
      CPPCFWV0_SFINAE_TYPE_TRAIT(canDecrement, std::declval<T>()--);
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


  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE>::HIter() : pimpl{} {}

  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE>::HIter(const void *pItr) : pimpl{pItr} {}

  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE>::~HIter() {}


  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE>::HIter(const HIter<Derived,T,SIZE>& rhs) = default;

  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE>& HIter<Derived,T,SIZE>::operator=(const HIter<Derived,T,SIZE>& rhs) = default;


  template <class Derived, typename T, int SIZE>
  bool HIter<Derived,T,SIZE>::operator==(const HIter& rhs) const {
    return pimpl->m_itr == rhs.pimpl->m_itr;
  }

  template <class Derived, typename T, int SIZE>
  bool HIter<Derived,T,SIZE>::operator!=(const HIter& rhs) const {
    return pimpl->m_itr != rhs.pimpl->m_itr;
  }

  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE>& HIter<Derived,T,SIZE>::operator++() {
    using Itr = decltype(pimpl->m_itr);
    if constexpr (sfinae::canIncrement_v<Itr>) {
      ++(pimpl->m_itr);
    } else {
      throw std::domain_error(std::string("This iterator ") + typeid(Itr).name() + " does not support incrementing");
    }
    return *this;
  }

  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE> HIter<Derived,T,SIZE>::operator++(int) {
    using Itr = decltype(pimpl->m_itr);
    auto itrTmp = *this;
    if constexpr (sfinae::canIncrement_v<Itr>) {
      (pimpl->m_itr)++;
    } else {
      throw std::domain_error(std::string("This iterator ") + typeid(Itr).name() + " does not support incrementing");
    }
    return itrTmp;
  }

  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE>& HIter<Derived,T,SIZE>::operator--() {
    using Itr = decltype(pimpl->m_itr);
    if constexpr (sfinae::canDecrement_v<Itr>) {
      --(pimpl->m_itr);
    } else {
      throw std::domain_error(std::string("This iterator ") + typeid(Itr).name() + " does not support decrementing");
    }
    return *this;
  }

  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE> HIter<Derived,T,SIZE>::operator--(int) {
    using Itr = decltype(pimpl->m_itr);
    auto itrTmp = *this;
    if constexpr (sfinae::canDecrement_v<Itr>) {
      (pimpl->m_itr)--;
    } else {
      throw std::domain_error(std::string("This iterator ") + typeid(Itr).name() + " does not support decrementing");
    }
    return itrTmp;
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type const& HIter<Derived,T,SIZE>::operator*() const {
    return *(pimpl->m_itr);
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type& HIter<Derived,T,SIZE>::operator*() {
    return *(pimpl->m_itr);
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type const* HIter<Derived,T,SIZE>::operator->() const {
    return &*(pimpl->m_itr);
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type* HIter<Derived,T,SIZE>::operator->() {
    return &*(pimpl->m_itr);
  }

}

#define CPPCFWV0_HITER_IMPL_3(classItr, typeRealItr, Size) \
  static_assert(std::is_same<typename classItr::value_type, typename typeRealItr::value_type>::value, "HIter type does not match the underlying iterator type"); \
  template class ::cppcfwv0::HIter<classItr, typeRealItr::value_type, Size>; \
  template <> \
  struct cppcfwv0::HIter<classItr, typeRealItr::value_type, Size>::Impl : public ::cppcfwv0::HIterImpl<classItr, cppcfwv0::HIter<classItr, typeRealItr::value_type, Size>::Impl, typeRealItr> {\
    using HIterImpl::HIterImpl; \
  };

#define CPPCFWV0_HITER_IMPL_2(classItr, typeRealItr) CPPCFWV0_HITER_IMPL_3(classItr, typeRealItr, ::cppcfwv0::config::sizeIterator)

#define CPPCFWV0_HITER_GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4

#define CPPCFWV0_HITER_IMPL_CHOOSER(...) CPPCFWV0_HITER_GET_4TH_ARG(__VA_ARGS__, CPPCFWV0_HITER_IMPL_3, CPPCFWV0_HITER_IMPL_2)
#define CPPCFWV0_HITER_IMPL(...) CPPCFWV0_HITER_IMPL_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
