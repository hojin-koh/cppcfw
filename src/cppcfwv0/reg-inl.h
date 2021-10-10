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
#include <map>

namespace cppcfwv0 {

  template <typename DerivedOuter, typename Derived, typename T>
  struct RegImpl {
    std::map<std::string, std::pair<T, std::string>> m_mData;

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
  void Reg<Derived,T>::add(const std::string& name, const T& obj, const std::string& desc) {
    using namespace std::string_literals;
    if (pimpl->m_mData.count(name) > 0) {
      throw std::out_of_range("Key '"s + name + "' already exist when adding to registry");
    }
    pimpl->m_mData.insert({name, {obj, desc}});
  }

  template <class Derived, typename T>
  bool Reg<Derived,T>::has(const std::string& name) const {
    return pimpl->m_mData.count(name) > 0;
  }
  
  template <class Derived, typename T>
  decltype(sizeof(0)) Reg<Derived,T>::size() const {
    return pimpl->m_mData.size();
  }


  template <class Derived, typename T>
  const T& Reg<Derived,T>::get(const std::string& name) const {
    return pimpl->m_mData.at(name).first;
  }

  template <class Derived, typename T>
  const char* Reg<Derived,T>::getDesc(const std::string& name) const {
    return pimpl->m_mData.at(name).second.c_str();
  }



  template <class Derived, typename T>
  const typename Reg<Derived,T>::Iter Reg<Derived,T>::begin() const {
    auto itr = pimpl->m_mData.begin();
    return Iter(&itr);
  }

  template <class Derived, typename T>
  const typename Reg<Derived,T>::Iter Reg<Derived,T>::end() const {
    auto itr = pimpl->m_mData.end();
    return Iter(&itr);
  }

}

#define CPPCFWV0_REG_IMPL(classReg, typeValue) \
  using RegParent = cppcfwv0::Reg<classReg, typeValue>; \
  using ContainerInner = std::map<std::string, std::pair<typeValue, std::string>>; \
  template struct cppcfwv0::Reg<classReg, typeValue>; \
  \
  CPPCFWV0_HITER_IMPL(RegParent::Iter, ContainerInner::iterator::value_type, ContainerInner::iterator); \
  \
  template <> \
  struct RegParent::Impl : public ::cppcfwv0::RegImpl<classReg, RegParent::Impl, typeValue> {};
