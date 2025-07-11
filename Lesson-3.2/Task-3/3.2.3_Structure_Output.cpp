#include <iostream>

struct address
{
    std::string city{};
    std::string street{};
    int block_num{0};
    int apart_num{0};
    int mail_index{0};
};

void print_address(address& mail_ddrss) {
    std::cout << "Город: " << mail_ddrss.city << std::endl;
    std::cout << "Улица: " << mail_ddrss.street << std::endl;
    std::cout << "Номер дома: " << mail_ddrss.block_num << std::endl;
    std::cout << "Номер квартиры: " << mail_ddrss.apart_num << std::endl;
    std::cout << "Индекс: " << mail_ddrss.mail_index << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    
    address dvfu = { "Владивосток", "поселок Русский, поселок Аякс", 10, 101, 690922 };
    address ufa_modern_art_mus{"Уфа", "Карла Маркса", 32, 1, 450077};
    address dom_lenina{"Казань", "Ульянова-Ленина", 58, 1, 420012};
    
    std::cout << "\n\n\n";
    print_address(dvfu);
    
    std::cout << "\n";
    print_address(ufa_modern_art_mus);
    
    std::cout << "\n";
    print_address(dom_lenina);
}
