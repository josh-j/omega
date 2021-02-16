#ifndef SHARED_DEPENDENCY_MANAGER_H__
#define SHARED_DEPENDENCY_MANAGER_H__
#include <vector>
#include <cassert>

namespace pre {

#define DEPENDENCYACCESSOR_MEMBER_NAME _depaccessor_
static const unsigned kMaxDependencies = 256;
typedef void* Dependencies[kMaxDependencies];

/* Rationale:
 * This obviates almost all the criticisms for singletons.
 */

class DependencyAccessor {
  DependencyAccessor(const DependencyAccessor&);
  void operator=(const DependencyAccessor&);
  template <class T> friend class DependencyInjector;

public:
  DependencyAccessor() {
    memset(dependencies_, 0, sizeof(dependencies_));
  }
  ~DependencyAccessor() {}

  template <class T>
  inline T* Request(unsigned dependency_id) {
    assert(dependencies_ != nullptr);
    assert(dependency_id < kMaxDependencies);
//#ifdef ASSERT_BAD_DEPENDENCY_REQUEST
    assert(dependencies_[dependency_id] != nullptr);
//#endif
    return static_cast<T*>(*dependencies_[dependency_id]);
  }

 private:
  void*const* dependencies_[kMaxDependencies];
};


class DependencyManager {
  DependencyManager(const DependencyManager&);
  void operator=(const DependencyManager&);
  template <class T> friend class DependencyInjector;
  template <class T> friend class StaticDependencyInjector;
public:
  DependencyManager() {
    memset(dependencies_, 0, sizeof(dependencies_) / sizeof(*dependencies_));
    memset(allocated_, 0, sizeof(allocated_) / sizeof(*allocated_));
  }
  ~DependencyManager() { Clean(); }

public:
  void Add(unsigned dependency_id, void* dependency) {
    // YOU HAVE MORE THAN 256 DEPENDENCIES?! You're doing something wrong.
    assert(dependency_id < kMaxDependencies);
    // A dependency was already added at this id
    assert(dependencies_[dependency_id] == nullptr);
    if (dependency_id >= kMaxDependencies
      || dependencies_[dependency_id] != nullptr) return;

    dependencies_[dependency_id] = dependency;
  }

  void Remove(unsigned dependency_id) {
    // YOU HAVE MORE THAN 256 DEPENDENCIES?! You're doing something wrong.
    assert(dependency_id < kMaxDependencies);
    // A dependency was already added at this id
    assert(dependencies_[dependency_id] == nullptr);
    if (dependency_id >= kMaxDependencies
      || dependencies_[dependency_id] != nullptr) return;
    dependencies_[dependency_id] = nullptr;
  }

  template <class T> void Create(unsigned dependency_id, T** dependency_out) {
    assert(dependency_out != nullptr && *dependency_out == nullptr);
    assert(dependency_id < kMaxDependencies);
    // A dependency was already created at this id
    assert(dependencies_[dependency_id] == nullptr);
    // Not returning means potentially leaked memory
    if (dependencies_[dependency_id] != nullptr) return;
    if (dependency_id >= kMaxDependencies
      || dependencies_[dependency_id] != nullptr) return;

    *dependency_out = new T;
    dependencies_[dependency_id] = *dependency_out;
    allocated_[dependency_id] = *dependency_out;
  }

  void Clean() {
    for (unsigned i = 0; i < kMaxDependencies; ++i) {
      if (allocated_[i] != nullptr) {
        delete ((DWORD*)allocated_[i]);
        allocated_[i] = nullptr;
      }
    }
    memset(dependencies_, 0, sizeof(dependencies_));
    memset(allocated_, 0, sizeof(allocated_));
  }

private:
  Dependencies dependencies_;
  Dependencies allocated_;
};

template <class RECEIVER_CLASS>
class DependencyInjector {
  DependencyInjector(const DependencyInjector&);
  void operator=(const DependencyInjector&);
  DependencyInjector() { }
public:
  DependencyInjector(const DependencyAccessor& parent_accessor)
    : parent_dependencies_(&parent_accessor.dependencies_) {
      // You're here because you forgot to DECLARE_DEPENDENCY and IMPLEMENT_DEPEDENCY your class
      //static_assert(std::is_member_pointer<pre::DependencyAccessor>(&RECEIVER_CLASS::DEPENDENCYACCESSOR_MEMBER_NAME), "blah");
      //if (!&RECEIVER_CLASS::DEPENDENCYACCESSOR_MEMBER_NAME) (void)0;
  }

  DependencyInjector(const DependencyManager& dependency_manager)
    : parent_dependencies_(&dependency_manager.dependencies_) {
      // You're here because you forgot to DECLARE_DEPENDENCY and IMPLEMENT_DEPEDENCY your class
      //static_assert(std::is_member_pointer<pre::DependencyAccessor>(&RECEIVER_CLASS::DEPENDENCYACCESSOR_MEMBER_NAME), "blah");
      //if (!&RECEIVER_CLASS::DEPENDENCYACCESSOR_MEMBER_NAME]) (void)0;
  }

  DependencyInjector& operator<<(unsigned dependency_id) {
    assert(dependency_id < kMaxDependencies);
    if (dependency_id > kMaxDependencies) return *this;
    RECEIVER_CLASS::DEPENDENCYACCESSOR_MEMBER_NAME.dependencies_[dependency_id]
      = &(*parent_dependencies_)[dependency_id];
    return *this;
  }

private:
  const Dependencies* const parent_dependencies_;
};


#define DECLARE_DEPENDENCY_ACCESSOR(CLASS) \
protected: \
  template <class T> friend class pre::DependencyInjector; \
  static pre::DependencyAccessor DEPENDENCYACCESSOR_MEMBER_NAME; \

#define IMPLEMENT_DEPENDENCY_ACCESSOR(CLASS) \
  pre::DependencyAccessor CLASS::DEPENDENCYACCESSOR_MEMBER_NAME; \


#define INJECT_DEPENDENCY(CLASS_NAME, DEPENDENCY_CONTAINER) pre::DependencyInjector<CLASS_NAME>(DEPENDENCY_CONTAINER)
#define INJECT_DEPENDENCY_THIS(CLASS_NAME) pre::DependencyInjector<CLASS_NAME>(*this)

#ifdef DISABLE_DEPENDENCIES
#define REQUEST_DEPENDENCY(DEPENDID, CLASS_NAME, DEPENDENCY_POINTER_HOLDER_NAME) (void)0
#define REQUEST_DEPENDENCY_RETFAIL(DEPENDID, CLASS_NAME, DEPENDENCY_POINTER_HOLDER_NAME) (void)0
#define REQUEST_DEPENDENCY_RETFAILVAL(DEPENDID, CLASS_NAME, DEPENDENCY_POINTER_HOLDER_NAME, FAIL_RETVAL) (void)0
#define REQUEST_DEPENDENCY_ASSERT(DEPENDID, CLASS_NAME, DEPENDENCY_POINTER_HOLDER_NAME) (void)0
#else
#define REQUEST_DEPENDENCY(DEPENDID, CLASS_NAME, DEPENDENCY_POINTER_HOLDER_NAME) \
  CLASS_NAME* DEPENDENCY_POINTER_HOLDER_NAME = DEPENDENCYACCESSOR_MEMBER_NAME.Request<CLASS_NAME>(DEPENDID);

#define REQUEST_DEPENDENCY_THIS(DEPENDID, CLASS_NAME, DEPENDENCY_POINTER_HOLDER_NAME) \
  DEPENDENCY_POINTER_HOLDER_NAME = DEPENDENCYACCESSOR_MEMBER_NAME.Request<CLASS_NAME>(DEPENDID);

#define REQUEST_DEPENDENCY_RETFAIL(DEPENDID, CLASS_NAME, DEPENDENCY_POINTER_HOLDER_NAME) \
  CLASS_NAME* DEPENDENCY_POINTER_HOLDER_NAME = DEPENDENCYACCESSOR_MEMBER_NAME.Request<CLASS_NAME>(DEPENDID); \
  if (DEPENDENCY_POINTER_HOLDER_NAME == nullptr) return;

#define REQUEST_DEPENDENCY_RETFAILVAL(DEPENDID, CLASS_NAME, DEPENDENCY_POINTER_HOLDER_NAME, FAIL_RETVAL) \
  CLASS_NAME* DEPENDENCY_POINTER_HOLDER_NAME = DEPENDENCYACCESSOR_MEMBER_NAME.Request<CLASS_NAME>(DEPENDID); \
  if (DEPENDENCY_POINTER_HOLDER_NAME == nullptr) return FAIL_RETVAL;

#define REQUEST_DEPENDENCY_ASSERT(DEPENDID, CLASS_NAME, DEPENDENCY_POINTER_HOLDER_NAME) \
  CLASS_NAME* DEPENDENCY_POINTER_HOLDER_NAME = DEPENDENCYACCESSOR_MEMBER_NAME.Request<CLASS_NAME>(DEPENDID); \
  assert(DEPENDENCY_POINTER_HOLDER_NAME != nullptr);
#endif

/* Example usage:

Panel.h:
class Panel {
  DECLARE_DEPENDENCY_ACCESSOR(Panel);
}

ProjectRoot.cpp:
ProjectRoot::Init() {
  dependency_manager.Add(DEPID_PanelManager, &screen);
  dependency_manager.Add(DEPID_InputHandler, &input_handler);
  dependency_manager.Add(DEPID_brush, &brush);
  dependency_manager.Add(DEPID_RENDERER, &renderer_);

  //INJECT_DEPENDENCY(Screen, dependency_manager) << DEPID_InputHandler << DEPID_brush;
  INJECT_DEPENDENCY(Panel, dependency_manager) << DEPID_ThemeManager;
  INJECT_DEPENDENCY(PanelSettings, dependency_manager) << DEPID_FontManager;
}

Panel.cpp:
IMPLEMENT_DEPENDENCY_ACCESSOR(Panel);
Panel::Init() {
  REQUEST_DEPENDENCY(DEPID_InputHandler, InputHandler, input_handler);
}

*/


} // namespace pre

#endif // SHARED_DEPENDENCY_MANAGER_H__
