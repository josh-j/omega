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
  virtual ~DeclarativeInterface() = default;
  virtual void operator()() = 0;
};

template <typename Signature, typename... Args> class Declarative;
template <typename Ret, typename... FuncArgs, typename... Args>
class Declarative<Ret(FuncArgs...), Args...> : public DeclarativeInterface {
public:
  ~Declarative() override = default;
  explicit Declarative(std::function<Ret(FuncArgs...)>&& func, Args... args) : _func{func}, _params{std::make_tuple(args...)} {
  }

  // template <class OWNER>
  // explicit Declarative(OWNER* owner, Ret(OWNER::*func)(Args...), Args... args) : _params{std::make_tuple(args...)} {
  //   std::function<Ret(Args...)> f = [=](Args... args) {
  //       return (owner->*func)(args...);
  //   };

  //   _func = f;

  // }

   void operator()() override {
    std::apply(_func, _params);
  }
private:
  std::function<Ret(FuncArgs...)> _func;
  std::tuple<Args...> _params;
};

template<typename Ret, typename... FuncArgs, typename... Args> Declarative(Ret(FuncArgs...), Args... args) -> Declarative<Ret(FuncArgs...), Args...>;


template <typename Owner, typename Signature, typename... Args> class DeclarativeMethod;
template <typename Owner, typename Ret, typename... FuncArgs, typename... Args>
class DeclarativeMethod<Owner, Ret(Owner::*)(FuncArgs...), Args...> : public DeclarativeInterface {
public:
  ~DeclarativeMethod() override = default;
  explicit DeclarativeMethod(Owner* owner, Ret(Owner::*func)(Args...), Args... args) : _params{std::make_tuple(args...)} {
    std::function<Ret(Args...)> f = [=](Args... args) {
        return (owner->*func)(args...);
    };

    _func = f;

  }

   void operator()() override {
    std::apply(_func, _params);
  }
 private:
   std::function<Ret(FuncArgs...)> _func;
   std::tuple<Args...> _params;
};

template<typename Owner, typename Ret, typename... FuncArgs, typename... Args> DeclarativeMethod(Owner*, Ret(Owner::*)(FuncArgs...), Args... args) -> DeclarativeMethod<Owner, Ret(Owner::*)(FuncArgs...), Args...>;


class DeclarativeVar {
  public:
  std::any _var;
};

class DeclarativeManager {
  public:
  // template <class Signature, class... Args> void add(Signature sig, Args... args);
  // template <class Ret, class... FuncArgs, class... Args>
  // void add(Ret(*func)(FuncArgs...), Args... args) {
  //   _declaratives.push_back(new Declarative{func, args...});
  //       //_declaratives.push_back(std::make_unique<DeclarativeInterface*>(new Declarative{func, args...}));
  // }

  template <class FUNCTION, class... Args>
  void add(FUNCTION&& func, Args&&... args) {
    _declaratives.push_back(new Declarative{std::forward<FUNCTION>(func), args...});
  }

  template <class OWNER, class FUNCTION, class... Args>
  void add_method(OWNER&& owner, FUNCTION&& func,  Args&&... args) {
    _declaratives.push_back(new DeclarativeMethod{std::forward<OWNER>(owner), std::forward<FUNCTION>(func), args...});
  }

  // template <class T, class Signature, class... Args> void add(T::Signature sig, Args... args);
  // template <class T, class Ret, class... FuncArgs, class... Args>
  // void add(Ret (T::*func)(FuncArgs...), Args... args) {
  //   _declaratives.push_back(new Declarative{func, args...});
  //   //_declaratives.push_back(std::make_unique<DeclarativeInterface*>(new
  //   //Declarative{func, args...}));
  // }
  void execute() {
    // for (auto& fn : _declaratives) {
    //  (*fn)->operator()();
    // }

    for (auto fn : _declaratives) {
      fn->operator()();
    }
  }

  //std::vector <std::unique_ptr<DeclarativeInterface*>> _declaratives;
   std::vector <DeclarativeInterface*> _declaratives;
};
