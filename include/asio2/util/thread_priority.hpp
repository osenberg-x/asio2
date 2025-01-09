/*
 * Copyright (c) 2024 xdo
 *
 * author   : xdo
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#ifndef __ASIO2_THREAD_PRIORITY_HPP__
#define __ASIO2_THREAD_PRIORITY_HPP__

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <sched.h>
#endif

namespace asio2 {

#ifdef _WIN32
inline bool set_thread_priority(int32_t priority) {
  return SetThreadPriority(::GetCurrentThread(), priority);
}
#endif

#ifdef __linux__
inline bool set_thread_priority(int32_t policy, int32_t priority) {
  struct sched_param param;
  param.sched_priority = priority;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
  auto rs = pthread_setschedparam(pthread_self(), policy, &param);
  return !rs;
}
#endif

} // namespace asio2

#endif // !__ASIO2_THREAD_PRIORITY_HPP__