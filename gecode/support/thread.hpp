/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2009
 *
 *  Bugfixes provided by:
 *     David Rijsman <david.rijsman@quintiq.com>
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <cstddef>

#ifdef GECODE_HAS_THREADS
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#ifdef GECODE_USE_OSX_UNFAIR_MUTEX
#include <os/lock.h>
#include <libkern/OSAtomic.h>
#endif

#endif

/**
 * \defgroup FuncSupportThread Simple thread and synchronization support
 *
 * This is very simplistic, just enough for parallel search engines. Do
 * not mistake it for a full-fledged thread package.
 *
 * If the platform supports threads, the macro GECODE_HAS_THREADS is
 * defined. If threads are not supported, all classes are
 * still available, but are noops with the exception of trying to
 * create a new thread which will throw an exception.
 *
 *
 * \ingroup FuncSupport
 */

namespace Gecode { namespace Support {

  /**
   * \brief A mutex for mutual exclausion among several threads
   *
   * It is not specified whether the mutex is recursive or not.
   * Likewise, there is no guarantee of fairness among the
   * blocking threads.
   *
   * \ingroup FuncSupportThread
   */
  class Mutex {
  private:
#ifdef GECODE_HAS_THREADS
#ifndef GECODE_USE_OSX_UNFAIR_MUTEX
    /// The mutex
    std::mutex m;
#else
    /// The unfair lock
    os_unfair_lock l;
#endif
#endif
  public:
    /// Initialize mutex
    Mutex(void);
    /// Acquire the mutex and possibly block
    void acquire(void);
    /// Try to acquire the mutex, return true if successful
    bool tryacquire(void);
    /// Release the mutex
    void release(void);
    /// Allocate memory from heap
    static void* operator new(size_t s);
    /// Free memory allocated from heap
    static void  operator delete(void* p);
  private:
    /// A mutex cannot be copied
    Mutex(const Mutex&) {}
    /// A mutex cannot be assigned
    void operator=(const Mutex&) {}
  };

  /**
   * \brief A lock as a scoped frontend for a mutex
   *
   * \ingroup FuncSupportThread
   */
  class Lock {
  private:
    /// The mutex used for the lock
    Mutex& m;
  public:
    /// Enter lock
    Lock(Mutex& m0);
    /// Leave lock
    ~Lock(void);
  private:
    /// A lock cannot be copied
    Lock(const Lock& l) : m(l.m) {}
    /// A lock cannot be assigned
    void operator=(const Lock&) {}
  };

  /**
   * \brief An event for synchronization
   *
   * An event can be waited on by a single thread until the event is
   * signalled.
   *
   * \ingroup FuncSupportThread
   */
  class Event {
  private:
#ifdef GECODE_HAS_THREADS
    /// The mutex
    std::mutex m;
    /// The condition variable
    std::condition_variable c;
#endif
    /// Whether the event is signalled
    bool s;
  public:
    /// Initialize event
    Event(void);
    /// Signal the event
    void signal(void);
    /// Wait until the event becomes signalled
    void wait(void);
  private:
    /// An event cannot be copied
    Event(const Event&) {}
    /// An event cannot be assigned
    void operator=(const Event&) {}
  };

  /**
   * \brief An interface for objects that can be called after a
   *        thread has terminated (after running the thread's destructor)
   *
   * \ingroup FuncSupportThread
   */
  class Terminator {
  public:
    /// Destructor
    virtual ~Terminator() {}
    /// The function that is called when the thread has terminated
    virtual void terminated(void) = 0;
  };

  /**
   * \brief An interface for objects that can be run by a thread
   *
   * \ingroup FuncSupportThread
   */
  class Runnable {
  private:
    /// Whether to delete the object when terminated
    bool d;
  public:
    /// Initialize, \a d defines whether object is deleted when terminated
    Runnable(bool d=true);
    /// Set whether to delete upon termination
    void todelete(bool d);
    /// Return whether to be deleted upon termination
    bool todelete(void) const;
    /// Return terminator object
    virtual Terminator* terminator(void) const { return nullptr; }
    /// The function that is executed when the thread starts
    virtual void run(void) = 0;
    /// Destructor
    virtual ~Runnable(void) {}
    /// Allocate memory from heap
    static void* operator new(size_t s);
    /// Free memory allocated from heap
    static void  operator delete(void* p);
  };

  /**
   * \brief Simple threads
   *
   * Threads cannot be created, only runnable objects can be submitted
   * for execution by a thread. Threads are pooled to avoid
   * creation/destruction of threads as much as possible.
   *
   * \ingroup FuncSupportThread
   */
  class Thread {
  public:
    /// A real thread
    class Run {
    public:
      /// Next idle thread
      Run* n;
      /// Runnable object to execute
      std::atomic<Runnable*> r;
      /// Event to wait for next runnable object to execute
      Event e;
      /// Create a new thread
      GECODE_SUPPORT_EXPORT Run(Runnable* r);
      /// Infinite loop for execution
      GECODE_SUPPORT_EXPORT void exec(void);
      /// Run a runnable object
      void run(Runnable* r);
      /// Allocate memory from heap
      static void* operator new(size_t s);
      /// Free memory allocated from heap
      static void  operator delete(void* p);
    };
    /// Mutex for synchronization
    GECODE_SUPPORT_EXPORT static Mutex* m(void);
    /// Idle runners
    GECODE_SUPPORT_EXPORT static Run* idle;
  public:
    /**
     * \brief Construct a new thread and run \a r
     *
     * After \a r terminates, \a r is deleted. After that, the thread
     * terminates.
     *
     * If the operating system does not support any threads, throws an
     * exception of type Support::OperatingSystemError.
     */
    static void run(Runnable* r);
    /// Put current thread to sleep for \a ms milliseconds
    static void sleep(unsigned int ms);
    /// Return number of processing units (1 if information not available)
    static unsigned int npu(void);
    /// acquire mutex \a m globally and possibly lock
    GECODE_SUPPORT_EXPORT static void acquireGlobalMutex(Mutex* m);
    /// release globally acquired mutex \a m
    GECODE_SUPPORT_EXPORT static void releaseGlobalMutex(Mutex* m);
  private:
    /// A thread cannot be copied
    Thread(const Thread&) {}
    /// A thread cannot be assigned
    void operator=(const Thread&) {}
  };

}}

// STATISTICS: support-any
