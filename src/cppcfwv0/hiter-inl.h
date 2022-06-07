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

// Implementation of the input hidden iterator wrapper
#pragma once
#include <cppcfwv0/hiter.h>
#include <cppcfwv0/pimpl-static-inl.h>
#include <cppcfwv0/sfinae.h>

#include <stdexcept>

namespace cppcfwv0 {

  namespace sfinae {
    CPPCFWV0_SFINAE_TYPE_TRAIT(hasFirst, std::declval<T>()->first);
    CPPCFWV0_SFINAE_TYPE_TRAIT(hasCStr, std::declval<T>()->c_str());
  }

  template <class Parent, typename Itr>
  struct HIterImpl {
    Itr m_itr;

    HIterImpl(const void *pItr) : m_itr{*static_cast<const Itr*>(pItr)} {}
    HIterImpl() {}
  protected: // To prevent polymorphic use
    ~HIterImpl() {}
  };

  template <class Derived, typename T, int SIZE>
  HIterBase<Derived,T,SIZE>::HIterBase() : pimpl{} {}

  template <class Derived, typename T, int SIZE>
  HIterBase<Derived,T,SIZE>::HIterBase(const void *pItr) : pimpl{pItr} {}

  template <class Derived, typename T, int SIZE>
  HIterBase<Derived,T,SIZE>::~HIterBase() {}


  template <class Derived, typename T, int SIZE>
  HIterBase<Derived,T,SIZE>::HIterBase(const HIterBase<Derived,T,SIZE>& rhs) = default;

  template <class Derived, typename T, int SIZE>
  HIterBase<Derived,T,SIZE>& HIterBase<Derived,T,SIZE>::operator=(const HIterBase<Derived,T,SIZE>& rhs) = default;


  template <class Derived, typename T, int SIZE>
  bool HIterBase<Derived,T,SIZE>::operator==(const HIterBase& rhs) const {
    return pimpl->m_itr == rhs.pimpl->m_itr;
  }

  template <class Derived, typename T, int SIZE>
  bool HIterBase<Derived,T,SIZE>::operator!=(const HIterBase& rhs) const {
    return pimpl->m_itr != rhs.pimpl->m_itr;
  }

  template <class Derived, typename T, int SIZE>
  HIterBase<Derived,T,SIZE>& HIterBase<Derived,T,SIZE>::operator++() {
    ++(pimpl->m_itr);
    return *this;
  }

  template <class Derived, typename T, int SIZE>
  HIterBase<Derived,T,SIZE> HIterBase<Derived,T,SIZE>::operator++(int) {
    auto itrTmp = *this;
    (pimpl->m_itr)++;
    return itrTmp;
  }

  template <class Derived, typename T, int SIZE>
  T const HIterBase<Derived,T,SIZE>::operator*() const {
    return static_cast<const Derived*>(this)->getValue();
  }

  template <class Derived, typename T, int SIZE>
  HIterValueWrapper<T> const HIterBase<Derived,T,SIZE>::operator->() const {
    return HIterValueWrapper<T>(static_cast<const Derived*>(this)->getValue());
  }

  template <class Derived, typename T, int SIZE>
  T const HIterBase<Derived,T,SIZE>::getValue() const {
    throw std::logic_error("Should not reach here. Please provide your own getValue() implementation or use the HIter variant.");
  }

  // First explicitly instantiate the main class, then instantiate the Impl class
#define CPPCFWV0_HITERBASE_INST_SIZE(classItr, typeRealItr, Size) \
  template class ::cppcfwv0::HIterBase<classItr, classItr::value_type, Size>; \
  template <> \
  struct cppcfwv0::HIterBase<classItr, classItr::value_type, Size>::Impl : public ::cppcfwv0::HIterImpl<classItr, typeRealItr> {\
    using HIterImpl::HIterImpl; \
  };

#define CPPCFWV0_HITERBASE_INST(classItr, typeRealItr) CPPCFWV0_HITERBASE_INST_SIZE(classItr, typeRealItr, ::cppcfwv0::config::sizeIterator)


  template <class Derived, typename T, int SIZE>
  T const& HIter<Derived,T,SIZE>::operator*() const {
    return *this->pimpl->m_itr;
  }

  template <class Derived, typename T, int SIZE>
  T const* HIter<Derived,T,SIZE>::operator->() const {
    return &(*this->pimpl->m_itr);
  }

  template <class Derived, int SIZE>
  const char* HIter<Derived,const char*,SIZE>::operator*() const {
    if constexpr (sfinae::hasFirst_v<decltype(this->pimpl->m_itr)>) {
      return this->pimpl->m_itr->first.c_str();
    } else if constexpr (sfinae::hasCStr_v<decltype(this->pimpl->m_itr)>) {
      return this->pimpl->m_itr->c_str();
    } else {
      return *this->pimpl->m_itr;
    }
  }

#define CPPCFWV0_HITER_INST_SIZE(classItr, typeRealItr, Size) \
  template class ::cppcfwv0::HIter<classItr, classItr::value_type, Size>; \
  template class ::cppcfwv0::HIterBase<classItr, classItr::value_type, Size>; \
  template <> \
  struct cppcfwv0::HIterBase<classItr, classItr::value_type, Size>::Impl : public ::cppcfwv0::HIterImpl<classItr, typeRealItr> {\
    using HIterImpl::HIterImpl; \
  };

#define CPPCFWV0_HITER_INST(classItr, typeRealItr) CPPCFWV0_HITER_INST_SIZE(classItr, typeRealItr, ::cppcfwv0::config::sizeIterator)

} // end namespace cppcfwv0
