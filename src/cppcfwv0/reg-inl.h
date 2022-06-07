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

// Implementation of the general registry class
#pragma once
#include <cppcfwv0/reg.h>
#include <cppcfwv0/hiter-inl.h>
#include <cppcfwv0/pimpl-static-inl.h>

#include <stdexcept>
#include <string>
using namespace std::string_literals;
#include <map>


namespace cppcfwv0 {

  template <typename Parent, typename T>
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
  Reg<Derived,T>::Reg(const Reg<Derived,T>& rhs) = default;

  template <class Derived, typename T>
  Reg<Derived,T>& Reg<Derived,T>::operator=(const Reg<Derived,T>& rhs) = default;


  template <class Derived, typename T>
  void Reg<Derived,T>::add(const char* name, const T& obj, const char* desc) {
    if (pimpl->m_mData.count(name) > 0) {
      throw std::out_of_range("Key '"s + name + "' already exist when adding to registry");
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
    return pimpl->m_mData.at(name).second.c_str();
  }



  template <class Derived, typename T>
  typename Reg<Derived,T>::Iter Reg<Derived,T>::begin() const {
    auto itr = pimpl->m_mData.begin();
    return Iter{&itr};
  }

  template <class Derived, typename T>
  typename Reg<Derived,T>::Iter Reg<Derived,T>::end() const {
    auto itr = pimpl->m_mData.end();
    return Iter{&itr};
  }

  template <class Derived, typename T>
  typename Reg<Derived, T>::value_type const Reg<Derived, T>::Iter::getValue() const {
    const auto& itr {this->pimpl->m_itr};
    return std::pair(itr->first.c_str(), std::pair(&itr->second.first, itr->second.second.c_str()));
  }

}

#define CPPCFWV0_REG_INST(classReg, typeValue) \
  using RegParent = cppcfwv0::Reg<classReg, typeValue>; \
  using ContainerInner = std::map<std::string, std::pair<typeValue, std::string>>; \
  template struct cppcfwv0::Reg<classReg, typeValue>; \
  template <> \
  struct RegParent::Impl : public ::cppcfwv0::RegImpl<classReg, typeValue> {using RegImpl::RegImpl;}; \
  CPPCFWV0_HITERBASE_INST(RegParent::Iter, ContainerInner::iterator);
