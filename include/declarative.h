#pragma once

#include <functional>
#include <tuple>
#include <type_traits>
#include <variant>
#include <utility>
#include <any>
#include <memory>
//https://stackoverflow.com/questions/47496358/c-lambdas-how-to-capture-variadic-parameter-pack-from-the-upper-scope
//https://stackoverflow.com/questions/15537817/c-how-to-store-a-parameter-pack-as-a-variable
class DeclarativeInterface {
public:
  virtual ~DeclarativeInterface() = default;
  virtual void operator()() = 0;
};

template <typename FuncSig, typename... Args>
class Declarative : public DeclarativeInterface {
public:
  ~Declarative() override = default;
  explicit Declarative(FuncSig&& func, Args&&... args) : _func{
    [func, args...]() mutable {
      //std::apply(func, args...);
      (func)(args...);
    }
  } {}

  void operator()() override {
    _func();
  }
private:
  std::function<void()> _func;
};

template<typename FuncSig, typename... Args> Declarative(FuncSig&& func, Args&&... args) -> Declarative<FuncSig&&, Args&&...>;

/*
template <typename Owner, typename Signature, typename... Args>
class DeclarativeMethod : public DeclarativeInterface {
public:
  ~DeclarativeMethod() override = default;
  explicit DeclarativeMethod(Owner&& owner, Signature&& func, Args&&... args) : _func{
    [owner, func, args = std::forward_as_tuple(args...)]() {
      std::apply(Ownerfunc, args);
      //(func)(args);
    }
  } {}

  void operator()() override {
    _func();
  }
private:
  std::function<void()> _func;
};

template<typename Owner, typename Signature, typename... Args> DeclarativeMethod(Owner&& owner, Signature&& func, Args&&... args) -> DeclarativeMethod<Owner&&, Signature&&, Args&&...>;
*/
class DeclarativeManager {
  public:
  template <class FuncSig, class... Args>
  void add(FuncSig&& func, Args&&... args) {
     _declaratives.push_back(new Declarative{std::forward<FuncSig>(func), std::forward<Args>(args)...});
  }
/*
  template <class Owner, class FUNCTION, class... Args>
  void add_method(Owner&& owner, FUNCTION&& func, Args&&... args) {
     _declaratives.push_back(new DeclarativeMethod{std::forward<Owner>(owner), std::forward<FUNCTION>(func), std::forward<Args>(args)...});
  }
*/
  void execute() {
    for (auto fn : _declaratives) {
      fn->operator()();
    }
  }
   std::vector <DeclarativeInterface*> _declaratives;
};
