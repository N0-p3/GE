#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace PC {
  template <typename T>
  class Singleton {
  private:
    static T instance;

  public:
    static T &getInstance() {
      return instance;
    }
  };

  template <typename T>
  T Singleton<T>::instance = T();
}

#endif