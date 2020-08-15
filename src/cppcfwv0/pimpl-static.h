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

// A static PImpl wrapper
#pragma once

namespace cppcfwv0 {

  template <class T, int SIZE, int ALIGN = __STDCPP_DEFAULT_NEW_ALIGNMENT__>
  struct PImplS final {
    template <typename... Args> PImplS(Args&& ...);
    ~PImplS();

    // Copy/Move
    PImplS(PImplS&& rhs) noexcept;
    PImplS& operator=(PImplS&& rhs) noexcept;
    PImplS(const PImplS& rhs);
    PImplS& operator=(const PImplS& rhs);

    // Overloadings to get the actual underlying implementation object
    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;

  private:
    alignas(ALIGN) char m_data[SIZE];
  }; // end class PImplS

}

