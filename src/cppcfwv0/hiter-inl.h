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
    ++(pimpl->m_itr);
    return *this;
  }

  template <class Derived, typename T, int SIZE>
  HIter<Derived,T,SIZE> HIter<Derived,T,SIZE>::operator++(int) {
    auto itrTmp = *this;
    (pimpl->m_itr)++;
    return itrTmp;
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type const& HIter<Derived,T,SIZE>::operator*() const {
    return *(pimpl->m_itr);
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type const* HIter<Derived,T,SIZE>::operator->() const {
    return &*(pimpl->m_itr);
  }

#define CPPCFWV0_HITER_IMPL_SIZE(classItr, typeRealItr, Size) \
  static_assert(std::is_same<typename classItr::value_type, typename typeRealItr::value_type>::value, "HIter type does not match the underlying iterator type"); \
  template class ::cppcfwv0::HIter<classItr, typeRealItr::value_type, Size>; \
  template <> \
  struct cppcfwv0::HIter<classItr, typeRealItr::value_type, Size>::Impl : public ::cppcfwv0::HIterImpl<classItr, cppcfwv0::HIter<classItr, typeRealItr::value_type, Size>::Impl, typeRealItr> {\
    using HIterImpl::HIterImpl; \
  };

#define CPPCFWV0_HITER_IMPL(classItr, typeRealItr) CPPCFWV0_HITER_IMPL_SIZE(classItr, typeRealItr, ::cppcfwv0::config::sizeIterator)



  // String-specilized version below

  template <class Derived, int SIZE>
  HIter<Derived,const char*,SIZE>::HIter() : pimpl{} {}

  template <class Derived, int SIZE>
  HIter<Derived,const char*,SIZE>::HIter(const void *pItr) : pimpl{pItr} {}

  template <class Derived, int SIZE>
  HIter<Derived,const char*,SIZE>::~HIter() {}


  template <class Derived, int SIZE>
  HIter<Derived,const char*,SIZE>::HIter(const HIter<Derived,const char*,SIZE>& rhs) = default;

  template <class Derived, int SIZE>
  HIter<Derived,const char*,SIZE>& HIter<Derived,const char*,SIZE>::operator=(const HIter<Derived,const char*,SIZE>& rhs) = default;


  template <class Derived, int SIZE>
  bool HIter<Derived,const char*,SIZE>::operator==(const HIter& rhs) const {
    return pimpl->m_itr == rhs.pimpl->m_itr;
  }

  template <class Derived, int SIZE>
  bool HIter<Derived,const char*,SIZE>::operator!=(const HIter& rhs) const {
    return pimpl->m_itr != rhs.pimpl->m_itr;
  }

  template <class Derived, int SIZE>
  HIter<Derived,const char*,SIZE>& HIter<Derived,const char*,SIZE>::operator++() {
    ++(pimpl->m_itr);
    return *this;
  }

  template <class Derived, int SIZE>
  HIter<Derived,const char*,SIZE> HIter<Derived,const char*,SIZE>::operator++(int) {
    auto itrTmp = *this;
    (pimpl->m_itr)++;
    return itrTmp;
  }

  template <class Derived, int SIZE>
  const char* HIter<Derived,const char*,SIZE>::operator*() const {
    return pimpl->m_itr->c_str();
  }

#define CPPCFWV0_HITER_IMPL_STR_SIZE(classItr, typeRealItr, Size) \
  static_assert(std::is_same<std::string, typename typeRealItr::value_type>::value, "The string-specialized HIter can only be used with iterators with std::string element type"); \
  template class ::cppcfwv0::HIter<classItr, const char*, Size>; \
  template <> \
  struct cppcfwv0::HIter<classItr, const char*, Size>::Impl : public ::cppcfwv0::HIterImpl<classItr, cppcfwv0::HIter<classItr, const char*, Size>::Impl, typeRealItr> {\
    using HIterImpl::HIterImpl; \
  };

#define CPPCFWV0_HITER_IMPL_STR(classItr, typeRealItr) CPPCFWV0_HITER_IMPL_STR_SIZE(classItr, typeRealItr, ::cppcfwv0::config::sizeIterator)

} // end namespace cppcfwv0
