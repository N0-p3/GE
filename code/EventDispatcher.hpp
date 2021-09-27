#ifndef EVENTDISPATCHER_HPP
#define EVENTDISPATCHER_HPP

#include <map>
#include "Event.hpp"
#include "Observer_Observable.hpp"

namespace GE {
  class EventDispatcher {
  private:
    map<unsigned int, PC::Observable> events;

  public:
    void bind(unsigned int eventType, PC::Observer* observer) {
      events[eventType].addObserver(observer);
    }

    void unbind(unsigned int eventType, PC::Observer* observer) {
      events[eventType].removeObserver(observer);
    }

    void dispatch() {
      if (events.find(Event::getType()) != events.end()) {
        events[Event::getType()].notify();
      }
    }
  };
}

#endif