#include <iostream>

struct account
{
    int acc_id{0};
    std::string acc_holder_name{};
    float acc_balance{0};
};
void account_create(account& acc) {
    std::cout << "¬ведите номер счета: ";
    std::cin >> acc.acc_id;
    std::cout << "¬ведите им€ владельца: ";
    std::cin >> acc.acc_holder_name;
    std::cout << "¬ведите баланс: ";
    std::cin >> acc.acc_balance;
}
void account_balance_change(account& acc, int& new_balance) {
    acc.acc_balance = new_balance;
}
void account_print(account& acc) {
    std::cout << "¬аш счет: ";
    std::cout << acc.acc_holder_name << ", " << acc.acc_id << ", " << acc.acc_balance;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";
    
    account mister_x_acc;
    account_create(mister_x_acc);
    int new_balance{ 0 };
    
    std::cout << "¬ведите новый баланс: ";
    std::cin >> new_balance;
    account_balance_change(mister_x_acc, new_balance);
    account_print(mister_x_acc);
}