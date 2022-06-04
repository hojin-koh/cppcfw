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

// forward-decleration of std::string
#pragma once

#ifdef _LIBCPP_VERSION // clang/libc++
  #include <iosfwd>
#elif defined(__GLIBCXX__) // gcc/libstdc++
  #include <bits/stringfwd.h>
#else // sorry MSVC
  #include <string>
#endif
