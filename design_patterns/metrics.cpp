#include <iostream>
#include <memory>
#include <list>

class Observer{
 public:
    virtual void notify(int value) = 0;
};

class MaxMetrics : public Observer {
 public:
    void notify(int value_)
    {
      int max = value_;
      if(value_ >= max)
      {
        int max = value_;
      }
      std::cout << "MaxMetric:" << max << std::endl;
    }
};

class ObserverManager {
 public:
  void registerMetric(std::shared_ptr<Observer> o) {
    observers_.push_back(o);
  }

  void handle(int value) { // вызов notify в каждом наследнике observer
    for (auto observer : observers_) {
      observer->notify(value);
    }
  }

 private:
  std::list<std::shared_ptr<Observer>> observers_;
};

class reader
{
 public:
    reader()
    {
      manager.registerMetric(std::shared_ptr<Observer>(new MaxMetrics())); //до цикла
      while(true)
      {
        std::string value; //числа либо команда show_all или show_max
        std::cin >> value; 
        if (value.compare("show_max") == 0)
        { 
          char* val = const_cast<char*>(value.c_str());
          int value_ = std::atoi(val); 
          manager.handle(value_);
        }
      }
    }
    ObserverManager manager = ObserverManager(); //как поле класса
};

int main()
{
  std::cout << "Running observer example\n";
  reader reader;
  exit(EXIT_SUCCESS);
}