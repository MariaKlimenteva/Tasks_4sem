#include <iostream>
#include <memory>
#include <list>

class Observer{
 public:
    virtual void notify(int value) = 0;
};

class MaxMetrics : public Observer {
    int max_;
 public:
    MaxMetrics() : max_(0){}
    void notify(int value)
    {
      if(value > max_)
      {
        max_ = value;
      }
      std::cout << "MaxMetric:" << max_ << std::endl;
    }
};

class ObserverManager {
 public:
  void registerMetric(std::shared_ptr<Observer> o) {
    observers_.push_back(o);
  }

  void handle(int value) { 
    for (auto observer : observers_) {
      observer->notify(value);
    }
  }

 private:
  std::list<std::shared_ptr<Observer>> observers_;
};

class reader
{
    int value_;
 public:
    reader()
    {
      manager.registerMetric(std::shared_ptr<Observer>(new MaxMetrics())); 
      while(true)
      {
        std::string value; //числа либо команда show_all или show_max
        std::cin >> value; 
        
        if (value.compare("show_max") != 0)
        { 
          char* val = const_cast<char*>(value.c_str());
          value_ = std::atoi(val);
        }
        else
        {
          manager.handle(value_);
        }
      }
    }
    ObserverManager manager = ObserverManager();
};

int main()
{
  std::cout << "Running observer example\n";
  reader reader;
  exit(EXIT_SUCCESS);
}