#ifndef OBSERVER_OBSERVABLE_HPP
#define OBSERVER_OBSERVABLE_HPP

#include <list>

using namespace std;

namespace PC {
  class Observer {
  public:
    virtual void receiveNotification() = 0;
  };
  

  
  class Observable {
  private:
    list<Observer*> observers;
  public:
    void addObserver(Observer* observer) {
      observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
      observers.remove(observer);
    }

    void notify() {
      for (auto it : observers) {
        it->receiveNotification();
      }
    }
  };
}

#endif