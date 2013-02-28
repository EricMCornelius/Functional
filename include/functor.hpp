#pragma once

#include <utility>

// http://stackoverflow.com/questions/9530928/checking-a-member-exists-possibly-in-a-base-class-c11-version/9531274#9531274

template <typename Signature, Signature* impl>
struct FunctorImpl {
  template <typename... Args>
  auto operator () (Args&&... args) -> decltype(impl(std::forward<Args>(args)...)) {
    return impl(std::forward<Args>(args)...);
  }
};

#define Functor(func) FunctorImpl<decltype(func), func>

#define FunctorTemplate(func, name) \
struct name { \
  template <typename... Args> \
  void operator () (Args&&... args) const { \
    func(std::forward<Args>(args)...); \
  } \
};
