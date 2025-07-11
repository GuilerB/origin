#include <iostream>

struct account
{
    int acc_id{0};
    std::string acc_holder_name{};
    float acc_amount{0};
};

void account_create(account& acc) {
    std::cout << "������� ����� �����: ";
    std::cin >> acc.acc_id;
    std::cout << "������� ��� ���������: ";
    std::cin >> acc.acc_holder_name;
    std::cout << "������� ������: ";
    std::cin >> acc.acc_amount;
}

void account_amount_change(account& acc) {
    std::cout << "������� ����� ������: ";
    std::cin >> acc.acc_amount;
}
void account_print(account& acc) {
    std::cout << "��� ����: ";
    std::cout << acc.acc_holder_name << ", " << acc.acc_id << ", " << acc.acc_amount;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // ����������� ��������� �������
    std::cout << "\n\n\n";
    account mister_x_acc;
    account_create(mister_x_acc);
    account_amount_change(mister_x_acc);
    account_print(mister_x_acc);
}