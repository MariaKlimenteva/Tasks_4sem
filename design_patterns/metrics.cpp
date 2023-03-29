#include <iostream>
#include <memory>
#include <list>
#include <iterator>

class Observer
{
 public:
    virtual void notify(int value) = 0;
};

class MaxMetrics : public Observer 
{
  int max_;

 public:
  MaxMetrics() : max_(0){}
  void notify(int value)
  {
    if(value > max_)
    {
      max_ = value;
    }
    std::cout << "Max Metric:" << max_ << std::endl;
  }
};

class MinMetrics: public Observer 
{
  int min_;

 public:
  MinMetrics() : min_(0){}
  void notify(int value)
  {
    if(value < min_)
    {
      min_ = value;
    }
    std::cout << "Min Metrics:" << min_ <<std::endl;
  }
};

class ObserverManager 
{
 public:
  void registerMetric(std::shared_ptr<Observer> o) 
  {
    observers_.push_back(o);
  }

  void handle(int value) 
  { 
    for (auto observer : observers_) 
    {
      observer->notify(value);
    }
  }

  void handle(int value, std::string metric)
  {
    if(metric.compare("max") == 0)
    {
      observers_.begin()->notify(value);
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
      std::string value; 
      std::cin >> value; 

      char* val = const_cast<char*>(value.c_str());
      value_ = std::atoi(val); //turns value (string) into the number
      
      if (value.compare("show_max") == 0)
      { 
        std::string metric = "max";
        manager.handle(value_, metric);
      }

      if (value.compare("show_min") == 0)
      {

      }

      if (value.compare("show_all") == 0)
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