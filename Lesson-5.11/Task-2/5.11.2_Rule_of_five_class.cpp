#include <iostream>
#include <string>
#include <algorithm>
#include <utility>


class big_integer {
private:
    std::string value;
    bool isNegative;

    std::string addStrings(const std::string& a, const std::string& b) const {
        std::string result;
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

public:
    // конструктор по умолчанию
    big_integer() : value("0"), isNegative(false) {}

    // конструктор с параметрами
    big_integer(const std::string& str) {
        std::string num = str;
        if (num[0] == '-') {
            isNegative = true;
            num = num.substr(1);
        }
        else {
            isNegative = false;
        }

        value = num;
        if (value == "0") isNegative = false;
    }

    big_integer(int num) {
        if (num < 0) {
            isNegative = true;
            num = -num;
        }
        else {
            isNegative = false;
        }
        value = std::to_string(num);
    }

    // конструктор копирования   
    big_integer(const big_integer& other) : value(other.value), isNegative(other.isNegative) {}

    // оператор копирующего присваивания 
    big_integer& operator=(const big_integer& other) 
    {
        return *this = big_integer(other);
    }

    // конструктор перемещения
    big_integer(big_integer&& other) noexcept
        : value(std::move(other.value)), isNegative(other.isNegative) {
        other.value = "0";
        other.isNegative = false;
    }

    // перемещающий оператор присваивания 
    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            value = std::move(other.value);
            isNegative = other.isNegative;
            other.value = "0";
            other.isNegative = false;
        }
        return *this;
    }

    ~big_integer() = default;

    // оператор сложения
    big_integer operator+(const big_integer& other) const {
        if (isNegative != other.isNegative) {
            return big_integer(0);
        }

        big_integer result;
        result.value = addStrings(value, other.value);
        result.isNegative = isNegative;
        return result;
    }

    // оператор умножения на число
    big_integer operator*(int num) const {
        if (num == 0) return big_integer(0);

        big_integer result;
        big_integer temp = *this;

        bool resultNegative = isNegative != (num < 0);
        int absNum = std::abs(num);
                
        for (int i = 0; i < absNum; ++i) {
            result = result + temp;
        }

        result.isNegative = resultNegative;
        if (result.value == "0") result.isNegative = false;
        return result;
    }

    std::string toString() const {
        return (isNegative ? "-" : "") + value;
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num) {
        os << num.toString();
        return os;
    }
    
};

int main() { 

    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result; // 193099
    std::cout << std::endl;

    return 0;
}
