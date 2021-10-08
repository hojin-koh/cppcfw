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

      // Check type match against iterator output and our desired type
      template <typename T, typename Itr>
      inline constexpr bool canSupport_v = canCastInto_v<T, decltype(*std::declval<Itr>())>;
      template <typename T, typename Itr>
      inline constexpr bool canSupportFirst_v = canCastInto_v<T, decltype(std::declval<Itr>()->first)>;
      template <typename T, typename Itr>
      inline constexpr bool canSupportSecond_v = canCastInto_v<T, decltype(std::declval<Itr>()->second)>;

      template <typename T, typename Itr>
      inline constexpr bool canSupportPtr_v = canCastInto_v<T, decltype(&*std::declval<Itr>())>;
      template <typename T, typename Itr>
      inline constexpr bool canSupportPtrFirst_v = canCastInto_v<T, decltype(&(std::declval<Itr>()->first))>;
      template <typename T, typename Itr>
      inline constexpr bool canSupportPtrSecond_v = canCastInto_v<T, decltype(&(std::declval<Itr>()->second))>;

      template <typename T, typename = void>
      struct has_getPtr : std::false_type {};
      template <typename T>
      struct has_getPtr<T, std::void_t<decltype(std::declval<T>().getPtr())>> : std::true_type {};
      template <typename T>
      inline constexpr bool has_getPtr_v = has_getPtr<T>::value;

      template <typename T, typename = void>
      struct has_getRef : std::false_type {};
      template <typename T>
      struct has_getRef<T, std::void_t<decltype(std::declval<T>().getRef())>> : std::true_type {};
      template <typename T>
      inline constexpr bool has_getRef_v = has_getRef<T>::value;

      template <typename T, typename = void>
      struct has_invalidateCache : std::false_type {};
      template <typename T>
      struct has_invalidateCache<T, std::void_t<decltype(std::declval<T>().invalidateCache())>> : std::true_type {};
      template <typename T>
      inline constexpr bool has_invalidateCache_v = has_invalidateCache<T>::value;
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
      if constexpr (sfinae::has_invalidateCache_v<HIter<Derived,T,SIZE>::Impl>) {
        pimpl->invalidateCache();
      }
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
      if constexpr (sfinae::has_invalidateCache_v<HIter<Derived,T,SIZE>::Impl>) {
        pimpl->invalidateCache();
      }
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
      if constexpr (sfinae::has_invalidateCache_v<HIter<Derived,T,SIZE>::Impl>) {
        pimpl->invalidateCache();
      }
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
      if constexpr (sfinae::has_invalidateCache_v<HIter<Derived,T,SIZE>::Impl>) {
        pimpl->invalidateCache();
      }
    } else {
      throw std::domain_error(std::string("This iterator ") + typeid(Itr).name() + " does not support decrementing");
    }
    return itrTmp;
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type const& HIter<Derived,T,SIZE>::operator*() const {
    using Itr = decltype(pimpl->m_itr);
    if constexpr (sfinae::canSupport_v<value_type const&, Itr>) {
      return *(pimpl->m_itr);
    } else if constexpr (sfinae::canSupportFirst_v<value_type const&, Itr>) {
      return pimpl->m_itr->first;
    } else if constexpr (sfinae::canSupportSecond_v<value_type const&, Itr>) {
      return pimpl->m_itr->second;
    } else {
      static_assert(!sizeof(T), "... what kind of iterator does not support dereferencing?");
    }
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type& HIter<Derived,T,SIZE>::operator*() {
    using Itr = decltype(pimpl->m_itr);
    if constexpr (sfinae::canSupport_v<value_type&, Itr>) {
      return *(pimpl->m_itr);
    } else if constexpr (sfinae::canSupportFirst_v<value_type&, Itr>) {
      return pimpl->m_itr->first;
    } else if constexpr (sfinae::canSupportSecond_v<value_type&, Itr>) {
      return pimpl->m_itr->second;
    } else {
      using namespace std::string_literals;
      throw std::domain_error("This iterator "s + typeid(Itr).name() + " does not support non-const dereference");
    }
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type const* HIter<Derived,T,SIZE>::operator->() const {
    using Itr = decltype(pimpl->m_itr);
    if constexpr (sfinae::canSupportPtr_v<value_type const*, Itr>) {
      return &*(pimpl->m_itr);
    } else if constexpr (sfinae::canSupportPtrFirst_v<value_type const*, Itr>) {
      return &pimpl->m_itr->first;
    } else if constexpr (sfinae::canSupportPtrSecond_v<value_type const*, Itr>) {
      return &pimpl->m_itr->second;
    } else {
      static_assert(!sizeof(T), "... what kind of iterator does not support dereferencing?");
    }
  }

  template <class Derived, typename T, int SIZE>
  typename HIter<Derived,T,SIZE>::value_type* HIter<Derived,T,SIZE>::operator->() {
    using Itr = decltype(pimpl->m_itr);
    if constexpr (sfinae::canSupportPtr_v<value_type*, Itr>) {
      return &*(pimpl->m_itr);
    } else if constexpr (sfinae::canSupportPtrFirst_v<value_type*, Itr>) {
      return &pimpl->m_itr->first;
    } else if constexpr (sfinae::canSupportPtrSecond_v<value_type*, Itr>) {
      return &pimpl->m_itr->second;
    } else {
      using namespace std::string_literals;
      throw std::domain_error("This iterator "s + typeid(Itr).name() + " does not support non-const dereference");
    }
  }

}

#define CPPCFWV0_HITER_IMPL_4(classItr, typeValue, typeRealItr, Size) \
  template class ::cppcfwv0::HIter<classItr, typeValue, Size>; \
  template <> \
  struct cppcfwv0::HIter<classItr, typeValue, Size>::Impl : public ::cppcfwv0::HIterImpl<classItr, cppcfwv0::HIter<classItr, typeValue, Size>::Impl, typeRealItr>

#define CPPCFWV0_HITER_IMPL_3(classItr, typeValue, typeRealItr) CPPCFWV0_HITER_IMPL_4(classItr, typeValue, typeRealItr, ::cppcfwv0::config::sizeIterator)

#define CPPCFWV0_HITER_GET_5TH_ARG(arg1, arg2, arg3, arg4, arg5, ...) arg5

#define CPPCFWV0_HITER_IMPL_CHOOSER(...) CPPCFWV0_HITER_GET_5TH_ARG(__VA_ARGS__, CPPCFWV0_HITER_IMPL_4, CPPCFWV0_HITER_IMPL_3)
#define CPPCFWV0_HITER_IMPL(...) CPPCFWV0_HITER_IMPL_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
