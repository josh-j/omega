#pragma once

// This is what I used before std::function

namespace pre {

class SlotInterface {};

template<class SIGNATURE>
class Slot;

template <class R, class... Args>
class Slot<R(Args...)> : public SlotInterface {
  void operator=(const Slot&);
  typedef R (*FunctionCallback)(Args...);

  struct ReceiverInterface {
    virtual ~ReceiverInterface() {}
    virtual R operator()(Args... args) = 0;
    virtual bool compare(ReceiverInterface* other) const = 0;
  };

  struct ReceiverFunction : public ReceiverInterface {
    ReceiverFunction() {}
    virtual ~ReceiverFunction() {}
    FunctionCallback callback;

    virtual R operator()(Args... args) {
      return callback(args...);
    }

    virtual bool compare(ReceiverInterface* other) const {
      return ((ReceiverFunction*)other)->callback == callback;
    }
  };

  template <class T>
  struct ReceiverMethod : public ReceiverInterface {
    ReceiverMethod() {}
    virtual ~ReceiverMethod() {}
    typedef R (T::*MethodCallback)(Args...);
    T* method_owner;
    MethodCallback callback;

    virtual R operator()(Args... args) {
      return (method_owner->*callback)(args...);
    }

    virtual bool compare(ReceiverInterface* other) const {
      return ((ReceiverMethod<T>*)other)->callback == callback &&
             ((ReceiverMethod<T>*)other)->method_owner == method_owner;
    }
  };

public:
  Slot() : receiver_(nullptr) {}

  template <class METHOD_OWNER>
  Slot(METHOD_OWNER* owner,
       typename ReceiverMethod<METHOD_OWNER>::MethodCallback method)
       : receiver_(nullptr) {
    set_method(owner, method);
  }

  Slot(FunctionCallback function) : receiver_(nullptr) {
    set_function(function);
  }

  Slot(Slot&& other) {
    receiver_ = other.receiver_;
    other.receiver_ = nullptr;
  }

  virtual ~Slot() {
    clear();
  }

  void take(Slot& other) {
    receiver_ = other.receiver_;
    other.receiver_ = nullptr;
  }

  template <class METHOD_OWNER>
  Slot* set_method(METHOD_OWNER* owner,
      typename ReceiverMethod<METHOD_OWNER>::MethodCallback method) {
    ReceiverMethod<METHOD_OWNER>* rm = new ReceiverMethod<METHOD_OWNER>;
    rm->method_owner = owner;
    rm->callback = method;
    clear();
    receiver_ = rm;
    return this;
  }

  Slot* set_function(FunctionCallback function) {
    ReceiverFunction* rf = new ReceiverFunction;
    rf->callback = function;
    clear();
    receiver_ = rf;
    return this;
  }

  R call(Args... args) {
    if (receiver_ != nullptr)
      return receiver_->operator()(args...);
    return R();
  }

  R operator()(Args... args) {
    return call(args...);
  }

  bool compare(Slot& other) const {
    return receiver_ != nullptr &&
           other.receiver_ != nullptr &&
           receiver_->compare(other.receiver_);
  }

  void clear() {
    if (receiver_ != nullptr) {
      delete receiver_;
      receiver_ = nullptr;
    }
  }
private:
  ReceiverInterface* receiver_;
};

} // namespace pre
