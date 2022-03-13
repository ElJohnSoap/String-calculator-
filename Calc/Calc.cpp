#include <iostream>
#include <vector>
#include <iomanip>

double expression();
double term();
double power();
double factor();
double number();

int main()
{
    double n;

    setlocale(LC_ALL, "Rus");

    std::cout << "Введите выражение: ";

    n = expression();

    std::cout << std::setprecision(12) << "Результат вычисления: " << n << std::endl;

    std::cin.get();
    std::cin.get();
    return 0;
}

double expression()
{
    double result;
    char operation;

    result = term();

    while (true)
    {
        operation = std::cin.get();

        switch (operation)
        {
        case '+':
            result += term();
            break;
        case '-':
            result -= term();
            break;
        default:
            std::cin.putback(operation);
            return result;
        }
    }
}

double term()
{
    double result;
    char operation;
    double temp;

    result = power();

    while (true)
    {
        operation = std::cin.get();

        switch (operation)
        {
        case '*':
            result *= power();
            break;
        case '/':
            temp = power();

            if (temp == 0.0)
            {
                std::cout << "Деление на нуль!" << std::endl;
                exit(-1);
            }

            result /= temp;
            break;
        default:
            std::cin.putback(operation);
            return result;
        }
    }
}

double power()
{
    double result;
    char operation;
    std::vector < double > args;

    args.push_back(factor());

    while (true)
    {
        operation = std::cin.get();

        while (operation == ' ')
            operation = std::cin.get();

        if (operation == '^')
            args.push_back(factor());
        else
        {
            std::cin.putback(operation);
            break;
        }
    }

    for (int i = args.size() - 1; i > 0; i--)
        args[i - 1] = pow(args[i - 1], args[i]);

    return args[0];
}

double factor()
{
    double result;
    char bracket;
    int sign = 1;

    bracket = std::cin.get();

    while (bracket == ' ')
        bracket = std::cin.get();

    switch (bracket)
    {
    case '-':
        sign = -1;
    case '+':
        bracket = std::cin.get();
        break;
    }

    while (bracket == ' ')
        bracket = std::cin.get();

    if (bracket == '(')
    {
        result = expression();
        bracket = std::cin.get();

        if (bracket != ')')
        {
            std::cout << "Неверная расстановка скобок!" << std::endl;
            exit(-1);
        }
    }
    else
    {
        std::cin.putback(bracket);
        result = number();
    }

    return sign * result;
}

double number()
{
    double result = 0.0;
    char digit;
    double k = 10.0;
    int sign = 1;

    digit = std::cin.get();

    switch (digit)
    {
    case '-':
        sign = -1;
        break;
    default:
        if (digit != '+')
            std::cin.putback(digit);

        break;
    }

    while (true)
    {
        digit = std::cin.get();

        while (digit == ' ')
            digit = std::cin.get();

        if (digit >= '0' && digit <= '9')
            result = result * 10.0 + (digit - '0');
        else
        {
            std::cin.putback(digit);
            break;
        }
    }

    digit = std::cin.get();

    if (digit == '.')
    {
        while (true)
        {
            digit = std::cin.get();

            while (digit == ' ')
                digit = std::cin.get();

            if (digit >= '0' && digit <= '9')
            {
                result += (digit - '0') / k;
                k *= 10.0;
            }
            else
            {
                std::cin.putback(digit);
                break;
            }
        }
    }
    else
        std::cin.putback(digit);

    return sign * result;
}