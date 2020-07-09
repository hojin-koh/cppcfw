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

// Implementation of the general registry class
#pragma once
#include <cppcfwv0/reg.h>
#include <cppcfwv0/hiter-inl.h>
#include <cppcfwv0/pimpl-static-inl.h>

#include <stdexcept>
#include <string>
#include <cstring>
#include <forward_list>
#include <map>

namespace cppcfwv0 {

  namespace {
    struct lessConstChar {
      bool operator()(const char* a, const char* b) const {
        return std::strcmp(a, b) < 0;
      }
    };
  }

  template <typename DerivedOuter, typename Derived, typename T>
  struct RegImpl {
    std::forward_list<std::string> m_lStrings;
    std::map<const char*, std::pair<T, const char*>, lessConstChar> m_mData;

    RegImpl() {}
  protected: // To prevent polymorphic use
    ~RegImpl() {}
  };

  template <class Derived, typename T>
  Reg<Derived,T>::Reg() : pimpl{} {}

  template <class Derived, typename T>
  Reg<Derived,T>::~Reg() {}


  template <class Derived, typename T>
  Reg<Derived,T>::Reg(Reg<Derived,T>&& rhs) noexcept = default;

  template <class Derived, typename T>
  Reg<Derived,T>& Reg<Derived,T>::operator=(Reg<Derived,T>&& rhs) noexcept = default;


  template <class Derived, typename T>
  void Reg<Derived,T>::add(const char* name, const T& obj, const char* desc) {
    if (pimpl->m_mData.count(name) > 0) {
      throw std::out_of_range(std::string("Key '") + name + "' already exist when adding to registry");
    }
    pimpl->m_lStrings.emplace_front(name);
    const char* pName = pimpl->m_lStrings.front().c_str();
    pimpl->m_lStrings.emplace_front(desc);
    const char* pDesc = pimpl->m_lStrings.front().c_str();
    pimpl->m_mData.insert({pName, {obj, pDesc}});
  }

  // NOTE: Only use this method if you can be sure name/desc are both string literals or can live through the whole lifecycle of Reg object
  template <class Derived, typename T>
  void Reg<Derived,T>::addLiteral(const char* name, const T& obj, const char* desc) {
    if (pimpl->m_mData.count(name) > 0) {
      throw std::out_of_range(std::string("Key '") + name + "' already exist when adding to registry");
    }
    pimpl->m_mData.insert({name, {obj, desc}});
  }

  template <class Derived, typename T>
  bool Reg<Derived,T>::has(const char* name) const {
    return pimpl->m_mData.count(name) > 0;
  }
  
  template <class Derived, typename T>
  decltype(sizeof(0)) Reg<Derived,T>::size() const {
    return pimpl->m_mData.size();
  }


  template <class Derived, typename T>
  const T& Reg<Derived,T>::get(const char* name) const {
    return pimpl->m_mData.at(name).first;
  }

  template <class Derived, typename T>
  const char* Reg<Derived,T>::getDesc(const char* name) const {
    return pimpl->m_mData.at(name).second;
  }


  template <class Derived, typename T>
  const typename Reg<Derived,T>::Iter Reg<Derived,T>::begin() const {
    auto itr = pimpl->m_mData.begin();
    return Reg<Derived,T>::Iter(&itr);
  }

  template <class Derived, typename T>
  const typename Reg<Derived,T>::Iter Reg<Derived,T>::end() const {
    auto itr = pimpl->m_mData.end();
    return Reg<Derived,T>::Iter(&itr);
  }

}

#define CPPCFWV0_REG_IMPL(classReg, typeValue) \
  using RegParent = cppcfwv0::Reg<classReg, typeValue>; \
  using ContainerInner = std::map<const char*, std::pair<typeValue, const char*>>; \
  template struct cppcfwv0::Reg<classReg, typeValue>; \
  \
  CPPCFWV0_HITER_IMPL(RegParent::Iter, const char*, ContainerInner::iterator) { \
    using HIterImpl::HIterImpl; \
    void invalidateCache() { \
      m_isCacheValid = false; \
    } \
    void ensureCache() const { \
      if (!m_isCacheValid) { \
        m_cache = m_itr->first; \
        m_isCacheValid = true; \
      } \
    } \
    const char* const& getRef() const { \
      ensureCache(); \
      return m_cache; \
    } \
    const char*& getRef() { \
      ensureCache(); \
      return m_cache; \
    } \
    const char* const* getPtr() const { \
      ensureCache(); \
      return &m_cache; \
    } \
    const char** getPtr() { \
      ensureCache(); \
      return &m_cache; \
    } \
 \
  private: \
    mutable bool m_isCacheValid {false}; \
    mutable const char* m_cache; \
  }; \
  \
  template <> \
  struct RegParent::Impl : public ::cppcfwv0::RegImpl<classReg, RegParent::Impl, typeValue>
