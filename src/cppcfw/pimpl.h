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

// The factory to produce pimpl classes
#pragma once

namespace ccwall {

  template <class T>
  class PImpl {
  private:
    // Yes, horrible raw pointer in order not to include smart pointer headers here
    T* m_ptr {nullptr};
  public:
    template <typename... Args> PImpl(Args&& ...);
    ~PImpl();

    // Overloadings to get the actual underlying implementation object
    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;
  }; // end class PImpl

}

