#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <utility>

/*
Usage
=====
Add an EventManager to your class or function. Define events for your class or function using PRELUDE_IMPLEMENT_EVENT(<FUNCTION TYPE>, <EVENT NAME>).
Subscribe to events using the function or class's EventManager and the event name defined by PRELUDE_IMPLEMENT_EVENT. The scope where
the event was defined is responsible for telling the subscribers when an event happened. For example:

class MyClass {
 public:
  PRELUDE_IMPLEMENT_EVENT(void(std::string), EventToldSomething);
  pre::EventManager EventManager;
  void tellSomething(std::string str) {
    EventManager.CallSubscribers(EventToldSomething(), str, this); // we're sending "this" because we're in a method -- "this" is not used in a function
  }
}

void whatWasSaid(std::string str) {
  cout << "this was said: " << str << "\n";
}

int main() {
  MyClass mc;
  mc.EventManager.Subscribe(MyClass::EventToldSomething, whatWasSaid); 
}

Todo
====

*/

namespace pre {

// Event

class EventInterface { public: virtual ~EventInterface() {} };

template<class SIGNATURE> class Event;
template<class R, class... ArgTypes>
class Event<R(ArgTypes...)> : public EventInterface {
public:
  Event(const Event&) = delete;
  void operator=(const Event&) = delete;
  using Subscribers = std::vector <std::function<R(ArgTypes...)>>;

  Event() : subscribers_(nullptr) {}
  virtual ~Event() { Dispose(); }

  void SubscribeSlot(std::function<R(ArgTypes...)>& slot) {
    if (subscribers_ == nullptr)
      subscribers_ = new Subscribers;

    subscribers_->emplace_back(slot);
  }

  void SubscribeFunction(R (*function)(ArgTypes... args)) {
    if (subscribers_ == nullptr)
      subscribers_ = new Subscribers;

    subscribers_->emplace_back(function);
  }

  template <class METHOD_OWNER>
  void SubscribeMethod(METHOD_OWNER* owner,
                      R (METHOD_OWNER::*method)(ArgTypes... args)){
    if (subscribers_ == nullptr)
      subscribers_ = new Subscribers;

    /*
    TODO: is there a better way of doing this (the lamba wrapper)? I tried bind, but
          I'd need to make it so that bind could handle variadic args.
    Q: What does this do?
    A: I want to subscribe functions to a vector of functions. This vector
       has type `std::vector <std::function<R(ArgTypes...)>>`.
       To subscribe a method to this vector, I need to curry the `this`.
       Because binding a method with std::function requires a type of
       `R(MethodClassPointer&, ArgTypes...)` rather than `R(ArgTypes...)`.
       The following lambda simply curries the `this` argument, or converts
       a method call to a function call so that it can be added to subscribers_.
    */
    std::function<R(ArgTypes...)> f = [=](ArgTypes... args) {
        return (owner->*method)(args...);
    };

    subscribers_->emplace_back(f);
  }

  void CallSubscribers(ArgTypes... args) {
    if (subscribers_ != nullptr) {
      for (size_t i = 0; i < subscribers_->size(); ++i) {
        subscribers_->at(i).operator()(args...);
      }
    }
  }

  std::vector<R> CallSubscribersGetResults(ArgTypes... args) {
    static_assert(!std::is_void<R>::value, "Can't retrieve results given that the return type is void.");
    std::vector<R> results;
    if (subscribers_ != nullptr) {
      for (size_t i = 0; i < subscribers_->size(); ++i) {
        results.emplace_back(subscribers_->at(i).operator()(args...));
      }
    }
    return results;  // rvo
  }


  void Dispose() {
    if (subscribers_ != nullptr) {
      subscribers_->clear();
      delete subscribers_;
      subscribers_ = nullptr;
    }
  }

  Subscribers* mutable_subscribers() const {
    return subscribers_;
  }
 private:
  Subscribers* subscribers_; // only a pointer to keep it lazy
};

// TODO: remove dependency on namespace and macro
#define PRELUDE_IMPLEMENT_EVENT(TYPE, EVENT_NAME) \
struct EVENT_NAME { \
  typedef pre::Event<TYPE>::Subscribers Subscribers; \
  typedef pre::Event<TYPE>::Subscribers::const_iterator Iterator; \
  typedef pre::Event<TYPE> Event; \
  typedef std::function<TYPE> Slot; \
  static const char* const name() { return #EVENT_NAME; } \
}; \

/*
Q: Why is an EventManager needed when the Event class can handle subscribers all
   by itself?
A: 1. It lets you manipulate a scope's events with their textual names.
   2. It lazy loads events. Say your Widget class has a dozen events, and you
      have dozens of widgets. If you simply declare
      pre::Event<void()> EventWidget* in your Widget class, then for every
      Widget you'll add `4 bytes * the number of events` even if those events
      are never subscribed to. If you create a thousand Widgets with a dozen
      events, for example, then you'll have an extra 1000 * 12 * 4 bytes.
      Don't use EventManager if you know you'll be subscribing to
      every event, or if you aren't creating multiple instances of the evented
      class.
*/

class EventManager {
  EventManager(const EventManager&);
  void operator=(const EventManager&);
  typedef std::map <std::string, pre::EventInterface*> Events;
public:
  EventManager() : events_(nullptr) {}
  ~EventManager() { Dispose(); }

  template <class EVENT, class SLOT>
  void SubscribeSlot(SLOT&& slot) {
    typename EVENT::Event* event = GetLazyEvent<EVENT>();
    event->SubscribeSlot(std::forward<SLOT>(slot));
  }

  template <class EVENT, class FUNCTION>
  void SubscribeFunction(FUNCTION&& function) {
    typename EVENT::Event* event = GetLazyEvent<EVENT>();
    event->SubscribeFunction(std::forward<FUNCTION>(function));
  }

  template <class EVENT, class CLASS_OWNER, class METHOD>
  void SubscribeMethod(CLASS_OWNER&& owner, METHOD&& method) {
    typename EVENT::Event* event = GetLazyEvent<EVENT>();
    event->SubscribeMethod(std::forward<CLASS_OWNER>(owner), std::forward<METHOD>(method));
  }

  template <class EVENT, class... ArgTypes>
  void CallSubscribers(ArgTypes... args) {
    typedef typename EVENT::Event event_t;
    event_t* found = static_cast<event_t*>(Find(EVENT::name()));

    if (found == nullptr)
      return;

    typename EVENT::Subscribers* subscribers = found->mutable_subscribers();
    if (subscribers != nullptr) {
      for (typename EVENT::Iterator it = subscribers->begin();
           it != subscribers->end();
           ++it) {
        it->operator()(args...);
      }
    }
  }

  template <class R, class EVENT, class... ArgTypes>
  std::vector<R> CallSubscribersGetResults(ArgTypes... args) {
    static_assert(!std::is_void<R>::value, "Can't retrieve results given that the return type is void.");
    typedef typename EVENT::Event event_t;
    event_t* found = static_cast<event_t*>(Find(EVENT::name()));
    std::vector<R> results;

    if (found == nullptr)
      return results;

    typename EVENT::Subscribers* subscribers = found->mutable_subscribers();
    if (subscribers != nullptr) {
      for (typename EVENT::Iterator it = subscribers->begin();
           it != subscribers->end();
           ++it) {
        results.push_back(it->operator()(args...));
      }
    }
    return results; // rvo
  }

  pre::EventInterface* Find(const std::string& name) {
    if (events_ == nullptr || events_->find(name) == events_->end())
      return nullptr;
    return (*events_)[name];
  }

  bool Contains(const std::string& name) const {
    if (events_ == nullptr)
      return false;
    return events_->find(name) != events_->end();
  }

  void Dispose() {
    if (events_ != nullptr) {
      for (Events::iterator it = events_->begin(); it != events_->end(); ++it) {
        delete it->second;
      }
      delete events_;
      events_ = nullptr;
    }
  }

private:
 template <class EVENT>
 typename EVENT::Event* GetLazyEvent() {
    if (events_ == nullptr)
      events_ = new Events;

    Events::iterator it = events_->find(EVENT::name());
    typename EVENT::Event* event;

    if (it == events_->end()) {
      event = new typename EVENT::Event;
      (*events_)[EVENT::name()] = event;
    } else {
      event = (typename EVENT::Event*)(it->second);
    }
    return event;
 }

 // The only reason `events_` is a pointer is to keep it lazy
 // and probably save memory.
 Events* events_;
};

} // namespace pre
