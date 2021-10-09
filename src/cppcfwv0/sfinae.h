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

// Some utilities
#pragma once

#define CPPCFWV0_SFINAE_TYPE_TRAIT(name, expr) \
  template <typename T, typename = void> \
  struct name : std::false_type {}; \
  template <typename T> \
  struct name<T, std::void_t<decltype(expr)>> : std::true_type {}; \
  template <typename T> \
  inline constexpr bool name ## _v = name<T>::value;

#define CPPCFWV0_SFINAE_TYPE_MATCH(name, T1, expr) \
  template <typename T1, typename T, typename = void> \
  struct name : std::false_type {}; \
  template <typename T1, typename T> \
  struct name<T1, T, std::void_t<decltype((T1)expr)>> : std::true_type {}; \
  template <typename T1, typename T> \
  inline constexpr bool name ## _v = name<T1, T>::value;
