#pragma once

#include <utility>

template <typename... Args>
struct chain;

template <typename Head, typename... Tail>
struct chain<Head, Tail...> {
  chain() : _h(Head()), _t(chain<Tail...>()) { }
  chain(Head h, Tail... t) : _h(h), _t(t...) { }

  template <typename... Args>
  void operator () (Args&&... args) const {
    _h(_t, std::forward<Args>(args)...);
  }

  Head _h;
  chain<Tail...> _t;
};

template <>
struct chain<> {
  template <typename... Args>
  void operator () (Args&&... args) const {

  }
};

template <typename... Functors>
auto make_chain(Functors... f) -> decltype(chain<Functors...>(f...)) {
  return chain<Functors...>(f...);
}
