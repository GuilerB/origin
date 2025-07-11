#include <iostream>

struct account
{
    int acc_id{0};
    std::string acc_holder_name{};
    float acc_amount{0};
};

void account_create(account& acc) {
    std::cout << "¬ведите номер счета: ";
    std::cin >> acc.acc_id;
    std::cout << "¬ведите им€ владельца: ";
    std::cin >> acc.acc_holder_name;
    std::cout << "¬ведите баланс: ";
    std::cin >> acc.acc_amount;
}

void account_amount_change(account& acc) {
    std::cout << "¬ведите новый баланс: ";
    std::cin >> acc.acc_amount;
}
void account_print(account& acc) {
    std::cout << "¬аш счет: ";
    std::cout << acc.acc_holder_name << ", " << acc.acc_id << ", " << acc.acc_amount;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";
    account mister_x_acc;
    account_create(mister_x_acc);
    account_amount_change(mister_x_acc);
    account_print(mister_x_acc);
}