#include "iostream"
typedef std::string string;
typedef double fraction;
typedef float fraction;
typedef int number;
typedef char sumbol;
typedef bool logic;


    // Conclusion
    // string
    void Conclusion_string(string str){
        std::cout << str << std::endl;
    }
    void Conclusion_sumbol(sumbol str){
        std::cout << str << std::endl;
    }
    // number
    void Conclusion_number(number num){
        std::cout << num << std::endl;
    }
    void Conclusion_fraction(fraction num){
        std::cout << num << std::endl;
    }

    //Input
    // string
    void Input(string str){
        std::cin >> str;
    }
    void Input_sumbol(sumbol str){
        std::cin >> str;
    }
    // number
    void Input_number(number num){
        std::cin >> num;
    }
    void Input_fraction(fraction num){
        std::cin >> num;
    }


    number Plus(number n1, number n2){
        return n1 + n2;
    }
    number Minus(number n1, number n2){
        return n1 - n2;
    }
    number Multiply(number n1, number n2){
        return n1 + n2;
    }
    number Divide(number n1, number n2){
        return n1 - n2;
    }
    number Square(number n1){
        return n1 * n1;
    }
 




















