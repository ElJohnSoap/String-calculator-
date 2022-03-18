/*
Создайте приложение для подсчета арифметического выражения пользователя.
Пользователь вводит с клавиатуры некоторое арифметическое выражение.
Выражение может содержать: (), +, -, *, /.
Приложение рассчитывает результат выражения с учетом скобок, приоритетов.
Результат отображается на экране.
Например, если пользователь ввел:
5 * 2+1
Результат: 11
Если пользователь ввел:
5 * (2+1)
Результат: 15*/

/*Проверить задвоенное введение операции*/


#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

struct choise		//структура описывающая любое число или операцию
{
	char type;      //0 для чисел, + для сложения, - вычитание и тп
	double value;   // только для чисел, у операций всегда 0
};

bool match(stack <choise>& Stack_num, stack <choise>& Stack_oper, choise& elem);
//функция мат операций, передаём ссылки на число, операцию и элемент для возврата.
// тип bool, чтобы при ошибке возвращало false


int rankOper(char smbl);//присваевает операции ранг (+ и -:ранг 1; * и / :ранг 2)


int main()
{
	setlocale(LC_ALL, "ru");
	cout << "  Добро пожаловать в калькулятор!\n";
	cout << "Выражение может содержать: (), +, -, *, /, ^\n";
	cout << "Приложение рассчитывает результат выражения с учетом скобок, приоритетов.\n\n";
	char smbl;				   //обрабатываемый текущий символ
	double value;			   //полное число если обрабатывается число
	stack <choise> Stack_num;  //стек для символов
	stack <choise> Stack_oper; //стек для операций
	choise elem;               //элемент структуры
	bool flag = 1;             //флаг отрицательного числа
	bool flag2 = 1;				//флаг ошибочного ввода
	while (1)					//бесконечный цикл
	{
		smbl = cin.peek();      //берём символ
		if (smbl == '\n')	    //выход из цикла, если нажат ввод
			break;
		else if (smbl == ' ') {
			cin.ignore();
			continue;
		}
		else if (smbl >= '0' && smbl <= '9' || smbl == '-' && flag)  //если прочитано число или если первый минус, то число отриц.
		{
			cin >> value;        //получаем всё число
			elem.type = '0';     //тк число, то тип 0
			elem.value = value;  //кладём число в значение
			Stack_num.push(elem);//отправляем в стек
			flag = 0;			 // меняем флаг тк число считано
			continue;            //тк число считано, переход к след итерации
		}

		else if (smbl == '+' || smbl == '-' && flag == 0 || smbl == '*' || smbl == '/' || smbl == '^') //если прочитана операция
		{
			if (Stack_oper.size() == 0 || (Stack_oper.size() != 0 && rankOper(smbl) > rankOper(Stack_oper.top().type)))
				//если стек опер пуст или не пуст, но ранг текущей операции выше лежащей в стеке
			{
				elem.type = smbl;     //тк символ операции, то тип равен значению
				elem.value = 0;       //тк символ, то значение 0
				Stack_oper.push(elem);//отправляем в стек операций
				cin.ignore();         //переход на след элемент
				continue;		      //тк считано, переход к след итерации
			}
			else if (Stack_oper.size() != 0 && rankOper(smbl) <= rankOper(Stack_oper.top().type))
				//не пуст, но ранг текущей операции равен лежащей в стеке
			{
				if (!match(Stack_num, Stack_oper, elem))//если вернёт фолс прекращаем работу
				{
					system("pause");
					return 0;
				}
				continue;
			}
		}
		else if (smbl == '(')      //если символ открывающ скобка, просто кладём в стек
		{
			elem.type = smbl;     //тк символ скобки, то тип равен значению
			elem.value = 0;       //тк символ, то значение 0
			Stack_oper.push(elem);//отправляем в стек операций
			cin.ignore();         //переход на след элемент
			continue;		      //тк считано, переход к след итерации
		}
		else if (smbl == ')')
		{
			while (Stack_oper.top().type != '(') //закрывающаяся скобка, выпоняем операции до закрыв.скобки
			{
				if (!match(Stack_num, Stack_oper, elem)) //если вернёт фолс прекращаем работу
				{
					system("pause");
					return 0;
				}
			}
			Stack_oper.pop();//удаляем откр скобку
			cin.ignore();	 //пропускаем скобку и переход к след
			continue;
		}
		else if (smbl < '0' && smbl > '9' || smbl != '+' || smbl != '-' || smbl != '*' || smbl != '/' || smbl != '(' || smbl != ')'||smbl!='^') {
			cout << "Символ \"" << smbl << "\" не является математическим\n";
			cin.ignore();
			//cin.putback(' ');
			//cin.ignore();
			flag2 = 0;  //переключаем флаг, тк были ошибки ввода
 			system("pause");
			continue;
		}
	}
	while (Stack_oper.size() != 0) {
		if (!match(Stack_num, Stack_oper, elem)) //если вернёт фолс прекращаем работу
		{
			system("pause");
			return 0;
		}
	}
	if (flag) {
		cout << "Вы не ввели ни одного числа!\n";
		return 0;
	}
	if (!flag2) cout << "Один или несколько символов не учитаны в программе,\n но мы всё равно посчитали.\n";
	
	cout << "\nОтвет: " << Stack_num.top().value << endl;
	return 0;

}



bool match(stack <choise>& Stack_num, stack <choise>& Stack_oper, choise& elem) //функция мат операций, передаём ссылки на число, операцию и элемент для возврата.
																				// тип bool, чтобы при ошибке возвращало false
{
	double c;
	double a = Stack_num.top().value; //берём верхний елемент из стека, именно значение(число)
	Stack_num.pop();			      //тк верхний эл уже взят, удаляем его из стека
	double b = Stack_num.top().value; //берём след (уже верхний) елемент из стека
	Stack_num.pop();				  //тк верхний эл уже взят, удаляем его из стека
	switch (Stack_oper.top().type)    //берём верхний елемент из стека операций для выбора
	{
	case '+':
		c = a + b;
		break;
	case '-':
		c = b - a;
		break;
	case '*':
		c = a * b;
		break;
	case '/':
		if (a == 0) {
			cout << "На 0 делить нельзя!";
			return false;
		}
		c = b / a;
		break;
	default:
		cout << "\nНеверная операция";
		return false;

	case '^':
		c = pow(b, a);
		break;
	}
	elem.type = '0';  //отправляем результат в стек
	elem.value = c;
	Stack_num.push(elem);
	Stack_oper.pop();
	return true;
}

int rankOper(char smbl) //присваевает операции ранг (+ и -:ранг 1; * и / :ранг 2)
{
	if (smbl == '+' || smbl == '-')
		return 1;
	if (smbl == '*' || smbl == '/')
		return 2;
	if (smbl == '^')
		return 3;
	return 0;
}
