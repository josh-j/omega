#pragma once

#include <functional>
#include <tuple>
#include <type_traits>
#include <variant>
#include <utility>
#include <any>
#include <memory>

class DeclarativeInterface {
public:
  virtual ~DeclarativeInterface() {}
  virtual void operator()() = 0;
};

template <typename Signature, typename... Args> class Declarative;
template <typename Ret, typename... FuncArgs, typename... Args>
class Declarative<Ret(FuncArgs...), Args...> : public DeclarativeInterface {
public:
  virtual ~Declarative() {}
  Declarative(std::function<Ret(FuncArgs...)>&& func, Args... args) : _func{func}, _params{std::make_tuple(args...)} {
  }
  virtual void operator()() {
    std::apply(_func, _params);
  }
private:
  std::function<Ret(FuncArgs...)> _func;
  std::tuple<Args...> _params;
};

template<typename Ret, typename... FuncArgs, typename... Args> Declarative(Ret(FuncArgs...), Args... args) -> Declarative<Ret(FuncArgs...), Args...>;


class DeclarativeVar {
  public:
  std::any _var;
};

class DeclarativeManager {
  public:
  template <class Signature, class... Args> void add(Signature sig, Args... args);
  template <class Ret, class... FuncArgs, class... Args>
  void add(Ret(*func)(FuncArgs...), Args... args) {
    //_declaratives.push_back(new Declarative{func, args2...})
    _declaratives.push_back(std::make_unique<DeclarativeInterface*>(new Declarative{func, args...}));
  }

  void execute() {
     for (auto& fn : _declaratives) {
      (*fn)->operator()();
     }

  //    for (auto fn : _declaratives) {
  //      fn->operator()();
  //    }
  }
  std::vector <std::unique_ptr<DeclarativeInterface*>> _declaratives;
  // std::vector <DeclarativeInterface*> _declaratives;
};
