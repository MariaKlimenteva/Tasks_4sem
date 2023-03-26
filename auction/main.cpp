#include <iostream>
#include <memory>
#include <string>
#include <vector>

class User
{
 public:
    User() //присвоение каждому новому юзеру уникального имени из рандомной последовательности цифр
    {
        srand(time(NULL));
        user_name = 97 + rand() % 25;
        std::cout << "New user's name is: #" << user_name << "\n" << std::endl;
    }
    int user_name;
    void Make_bet(int lot_name, int bid); //метод - сделать ставку
    std::vector<std::string> lots; //список лотов для одного юзера
}

class Lot //один лот, описание этого состояния
{
 public:
    Lot(); //конструктор
    int lot_value = 1; //начальная цена лота, которая изменяется потом
    void Introduce(std::string lot_name, int lot_value);
    std::vector<std::string> users;
}

class Auction
{
 public:
    Auction()// создание списков людей, лотов
    {
        srand(time(NULL));
        for (int i = 0; i < max_lot; i++)
        {
            lot_name[i] = 97 + rand() % 25;
        }
    }
    int max_lot = 15;
    std::vector<std::string> lot_name;
    void print_list_of_lots(std::vector<std::string> lot_name)
    {
        for (int i = 0; i < max_lot; i++)
        {
            std::cout << lot_name[i] << "\n" << std::endl;
        }
    }
}

//vector::push_back - вставить элемент в конец вектора
// деструктор : удаление человека или лота из списка аукциона

int main()
{
    User user1;
    std::cout << user1.user_name << std::endl;
    exit(EXIT_SUCCESS);
}