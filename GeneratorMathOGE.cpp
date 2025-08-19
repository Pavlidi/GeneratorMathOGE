#include <iostream>                                             // Для операторов cin и cout
#include <ctime>                                                // Для функции srand() которая помогает делать реальный рандомайзер
#include <cmath>                                                // Для математических операторов
#include <string>
#include <iomanip>                                              // Чтобы небыло лишних нулей вконце ***
#include <sstream>                                              // Чтобы небыло лишних нулей вконце ***
using namespace std;

int main_menu()                                                 // Функция которая выводит главное меню
{
    int choice_mm;
    cout << "\033[2J\033[1;1H";
    cout << "\"Генератор заданий ОГЭ: математика\"\n" << endl;
    cout << "Выберите действие:" << endl;
    cout << "1. Сгенерировать задания по темам" << endl;
    cout << "2. Сгенерировать целый вариант" << endl << endl;
    cout << "0. Выход" << endl << endl;
    cout << "Ваш выбор: ";
    cin >> choice_mm;
    return choice_mm;
}

string FormatDouble(double val, int maxPrecision = 10) {          // Чтобы небыло лишних нулей вконце ***
    ostringstream out;
    out << fixed << setprecision(maxPrecision) << val;
    string s = out.str();
    s.erase(s.find_last_not_of('0') + 1);
    if (s.back() == '.') s.pop_back();
    return s;
}

int NOD(int number1, int number2)                               // Ищет и возвращает НОД двух чисел
{
    int nod = 1;
    int count_del1, count_del2;
    count_del1 = count_del2 = 0;
    for (int i = 2; i <= number1; i++)                                // Считает количество делителей первого числа
    {
        if (number1 % i == 0)
            count_del1++;
    }

    for (int i = 2; i <= number2; i++)                                // Считает количество делителей второго числа
    {
        if (number2 % i == 0)
            count_del2++;
    }

    int count = 0;
    int del1[50], del2[50];                                           // Создаются массивы для делителей
    for (int i = 0; i < 50; i++)
        del1[i] = 1;
    for (int i = 0; i < 50; i++)
        del2[i] = 1;

    for (int i = 2; i <= number1; i++)                               // Заполняется массив делителей первого числа
    {
        if (number1 % i == 0)
        {
            del1[count] = i;
            count++;
        }
    }
    count = 0;
    for (int i = 2; i <= number2; i++)                               // Заполняется массив делителей второго числа
    {
        if (number2 % i == 0)
        {
            del2[count] = i;
            count++;
        }
    }

    for (int i = 0; i < count_del1; i++)                               // Ищет наибольший общий делитель
    {
        for (int n = 0; n < count_del2; n++)
        {
            if ((del1[i] == del2[n]) && (del1[i] > nod))
                nod = del1[i];
        }
    }
    return nod;
}

string SIGN(int pok, int pos)                                   // Возвращает знак операции + или - для Latex (pos - позиция знака в выражении)
{
    string sgn;
    if ((pow(-1, pok) > 0) && (pos == 1))
        sgn = "";
    if ((pow(-1, pok) > 0) && (pos == 2))
        sgn = "+";
    if (pow(-1, pok) < 0)
        sgn = "-";
    return sgn;

}

string SIGN_MultDel(int type)                                   // Возвращает знак * или :  для Latex (type = 1 - умножение, type = 2 - деление)
{
    string sgn;
    if (type == 1)
        sgn = "\\cdot";
    else
        sgn = ":";
    return sgn;

}

string DoubleToString(double number)
{
    string final;
    final = to_string(static_cast<int>(number));
    for (int i = 0; i < 3; i++)
    {
        double raz = (number * pow(10, i)) - static_cast<int>(number * pow(10, i));
        if ((raz > 0) && (i == 0))
        {
            final = final + ".";
            int dob = static_cast<int>(number * pow(10, i + 1)) - (static_cast<int>(number * pow(10, i)) * 10);
            final = final + to_string(dob);
        }
        if ((raz > 0) && (i != 0))
        {
            int dob = static_cast<int>(number * pow(10, i + 1)) - (static_cast<int>(number * pow(10, i)) * 10);
            final = final + to_string(dob);
        }
    }
    return final;
}

string FractionPrint(double number1, double number2)                 // Возвращает дробь в строке для Latex
{
    string fraction;
    int whole;
    if (number1 < number2)
        fraction = "\\frac{" + to_string(static_cast<int>(number1)) + "}{" + to_string(static_cast<int>(number2)) + "}";
    else
    {
        whole = number1 / number2;
        number1 = number1 - (whole * number2);
        fraction = to_string(static_cast<int>(whole)) + "\\frac{" + to_string(static_cast<int>(number1)) + "}{" + to_string(static_cast<int>(number2)) + "}";
    }
    return fraction;
}

string FractionPlusMinus(int number, int AllType)                            // Генерирует примеры на сложение и вычитание обычных дробей
{
    string Answer;
    double a[5];                                                                    // Составные дробей
    double answer, check;
    double  b[4];                                                           // Приведенные знаменатели и числители
    int nod1, nod2;                                                         // Общие делители для сокращения дробей
    int type;                                                               // Тип выражения
    int sign = rand();                                                      // Знак + или -
    do {                                                                    // Генерирует дроби
        for (int n = 0; n < 5; n++)
            a[n] = (rand() % 50) + 1;
        if(AllType == 0)
            type = (rand() % 4) + 1;
        else
            type = AllType;
        switch (type)
        {

        case 1:
            b[0] = a[0];
            b[1] = a[1];
            b[2] = a[2];
            b[3] = a[3];
            answer = (b[0] / b[1]) + pow(-1, sign) * (b[2] / b[3]);
            break;

        case 2:
            if ((a[1] * a[2] < 110) && (a[1] * a[4] < 110))                                        // Проверка не слишком ли большой знаменатель
            {
                b[0] = a[0];
                b[1] = a[1] * a[2];
                b[2] = a[3];
                b[3] = a[1] * a[4];
                answer = (b[0] / b[1]) + pow(-1, sign) * (b[2] / b[3]);
            }
            else
                answer = 1.111111;
            break;

        case 3:
            if (a[1] * a[3] < 110)                                                                 // Проверка не слишком ли большой знаменатель
            {
                b[0] = a[0];
                b[1] = a[1];
                b[2] = a[2];
                b[3] = a[1] * a[3];
                answer = (b[0] / b[1]) + pow(-1, sign) * (b[2] / b[3]);
            }
            else
                answer = 1.111111;
            break;

        case 4:
            if (a[1] * a[2] < 110)                                                                  // Проверка не слишком ли большой знаменатель
            {
                b[0] = a[0];
                b[1] = a[1] * a[2];
                b[2] = a[3];
                b[3] = a[1];
                answer = (b[0] / b[1]) + pow(-1, sign) * (b[2] / b[3]);
            }
            else
                answer = 1.111111;
            break;
        }
        check = (answer * 100) / static_cast<int>((answer * 100));
        nod1 = NOD(b[0], b[1]);
        nod2 = NOD(b[2], b[3]);
        b[0] = b[0] / nod1;                                                         // Сокращает первую дробь
        b[1] = b[1] / nod1;                                                         // Сокращает первую дробь
        b[2] = b[2] / nod2;                                                         // Сокращает вторую дробь
        b[3] = b[3] / nod2;                                                         // Сокращает вторую дробь
        if ((b[1] == b[3]) || (b[1] == 1) || (b[3] == 1))
            check = 0;
    } while (check != 1);
    cout <<  "\\item Найдите значение выражения: \n \\[ \n   " + FractionPrint(b[0], b[1]) + SIGN(sign, 2) + FractionPrint(b[2], b[3]) + "\n \\]" << endl;
    Answer = "  \\item " + FormatDouble(answer) + " \n";
    return Answer;
}

string FractionMultDiv(int number, int AllType)
{
    string Answer;
    double a[4];
    double answer, check;
    int nod1, nod2;                                                         // Общие делители для сокращения дробей
    int type;                                                               // Тип выражения
    do {                                                                    // Генерирует дроби
        for (int n = 0; n < 4; n++)
            a[n] = (rand() % 50) + 1;
        if(AllType == 0)
            type = (rand() % 2) + 1;
        else
            type = AllType;
        switch (type)
        {

        case 1:
            answer = (a[0] / a[1]) * (a[2] / a[3]);
            break;

        case 2:
            answer = (a[0] / a[1]) / (a[2] / a[3]);
            break;
        }
        check = (answer * 100) / static_cast<int>((answer * 100));
        nod1 = NOD(a[0], a[1]);
        nod2 = NOD(a[2], a[3]);
        a[0] = a[0] / nod1;                                                         // Сокращает первую дробь
        a[1] = a[1] / nod1;                                                         // Сокращает первую дробь
        a[2] = a[2] / nod2;                                                         // Сокращает вторую дробь
        a[3] = a[3] / nod2;                                                         // Сокращает вторую дробь
        if (((type == 1) && ((a[1] == 1) || (a[3] == 1))) || ((type == 2) && ((a[1] == 1) || (a[3] == 1))))
            check = -1;
    } while (check != 1);
    cout << "\\item Найдите значение выражения: \n \\[ \n   " + FractionPrint(a[0], a[1]) + SIGN_MultDel(type) + FractionPrint(a[2], a[3]) + "\n \\]" << endl;
    Answer = "  \\item " + FormatDouble(answer) + " \n";
    return Answer;
}

string DFractionMultDiv(int number, int AllType)                               // Генерирует примеры на умножение и деление десятичных дробей
{
    int type;
    double number1, number2, answer;
    string Answer;
    if(AllType == 0)
        type = (rand() % 2) + 1;
    else
        type = AllType;
    switch (type)
    {
    case 1:
        do {
            number1 = (rand() % 999) + 1;
            number1 = number1 / 100;
            number2 = (rand() % 999) + 1;
            number2 = number2 / 100;
            answer = number1 * number2;
        } while (((answer * 100) - static_cast<int>(answer * 100)) != 0);
        cout << "\\item Найдите значение выражения: " << endl;
        cout << "\\[" << endl;
        cout << "   " << number1 << "\\cdot" << number2 << endl;
        cout << "\\]" << endl;
        Answer = "  \\item " + FormatDouble(answer) + " \n";
        break;

    case 2:
        do {
            number1 = (rand() % 999) + 1;
            number1 = number1 / 100;
            number2 = (rand() % 999) + 1;
            number2 = number2 / 100;
            answer = number1 / number2;
        } while (((answer * 100) - static_cast<int>(answer * 100)) != 0);
        cout << "\\item Найдите значение выражения: " << endl;
        cout << "\\[" << endl;
        cout << "   \\frac{" << number1 << "}{" << number2 << "}" << endl;
        cout << "\\]" << endl;
        Answer = "  \\item " + FormatDouble(answer) + " \n";
        break;
    }
    return Answer;
}

string DFractionPlusMinus(int number)                             // Генерирует примеры на сложение и вычитание десятичных дробей
{
    double a[2];
    int znak1 = rand();
    int znak2 = rand();
    double answer;
    string Answer;
    for (int n = 0; n < 2; n++)
        a[n] = static_cast<double>((rand() % 999 + 1)) / 100;
    cout << "\\item Найдите значение выражения: " << endl;
    cout << "\\[" << endl;
    cout << "   " << SIGN(znak1, 1) << a[0] << SIGN(znak2, 2) << a[1] << endl;
    cout << "\\]" << endl;
    answer = pow(-1, znak1)*a[0] + pow(-1,znak2)*a[1];
    Answer = "  \\item " + FormatDouble(answer) + "\n";
    return Answer;

}

string LetterEqu(int number, int AllType)
{
    int type;
    int type_1 = (rand() % 4) + 1;
    double a = rand() % 27 + 2;
    double b = rand() % 27 + 2;
    double c = rand() % 27 + 2;
    double answer;
    string Answer;
    if(AllType == 0)
        type = (rand() % 4) + 1;
    else
        type = AllType;
    switch (type)
    {
    case 1:	// Буквенные 1
        switch (type_1)
        {
        case 1:
            cout << "\\item Найдите значение выражения: \\[\n	(\\sqrt{" << a << "}+" << b <<
                ")^2 - " << 2 * b << "\\sqrt{" << a << "} \n \\]" << endl;
            answer = a + b * b;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 2:
            cout << "\\item Найдите значение выражения: \\[\n	(" << a << "+\\sqrt{" << b <<
                "})^2 - " << 2 * a << "\\sqrt{" << b << "} \n \\]" << endl;
            answer = a * a + b;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 3:
            cout << "\\item Найдите значение выражения: \\[\n	" << 2 * b << "\\sqrt{" << a <<
                "} + (\\sqrt{" << a << "} - " << b << ")^2 \n \\]" << endl;
            answer = a + b * b;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 4:
            cout << "\\item Найдите значение выражения: \\[\n	" << 2 * a << "\\sqrt{" << b <<
                "} - (" << a << " + \\sqrt{" << b << "})^2 \n \\]" << endl;
            answer = (a * a) * (-1) - b;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;
        }
        break;

    case 2: // Буквенные 2
        switch (type_1)
        {
        case 1:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{a^2 + " << 2 * c << "ab + " << c * c << "b^2}$ при a = " << a << " и b = " << b << ".\\\\" << endl;
            answer = fabs(a + c * b);
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 2:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{" << c * c << "a^2 + " << 2 * c << "ab + b^2}$ при a = " << a << " и b = " << b << ".\\\\" << endl;
            answer = fabs(a * c + b);
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 3:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{a^2 - " << 2 * c << "ab + " << c * c << "b^2}$ при a = " << a << " и b = " << b << ".\\\\" << endl;
            answer = fabs(a - c * b);
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 4:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{" << c * c << "a^2 - " << 2 * c << "ab + b^2}$ при a = " << a << " и b = " << b << ".\\\\" << endl;
            answer = fabs(a * c - b);
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;
        }
        break;

    case 3: // Буквенные 3
        double d;
        do {
            d = rand() % 16 + 2;
        } while ((d == 4) || (d == 9) || (d == 16));
        switch (type_1)
        {
        case 1:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(\\sqrt{" << a * a * d << "} - \\sqrt{" << d << "}\\right)\\sqrt{" << d << "}$.\\\\" << endl;
            answer = a * d - d;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 2:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(\\sqrt{" << d << "} + \\sqrt{" << d * a * a << "}\\right)\\sqrt{" << d << "}$.\\\\" << endl;
            answer = a * d + d;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 3:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{" << d << "}\\left(\\sqrt{" << d << "} - \\sqrt{" << a * a * d << "}\\right)$.\\\\" << endl;
            answer = d - a * d;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 4:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{" << d << "}\\left(\\sqrt{" << d * a * a << "} + \\sqrt{" << d << "}\\right)$.\\\\" << endl;
            answer = d + a * d;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;
        }
        break;

    case 4: // Буквенные 4
        double e, f;
        do {
            e = rand() % 50 + 2;
        } while ((e == 4) || (e == 9) || (e == 16) || (e == 25) || (e == 36) || (e == 49));
        do {
            f = rand() % 50 + 2;
        } while ((f == 4) || (f == 9) || (f == 16) || (f == 25) || (f == 36) || (f == 49));
        switch (type_1)
        {
        case 1:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(\\sqrt{" << e << "} - " << a << "\\right)\\left(\\sqrt{" << e << "} + " << a << "\\right)$.\\\\" << endl;
            answer = e - a * a;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 2:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(" << a << "+ \\sqrt{" << e << "}\\right)\\left(" << a << "-\\sqrt{" << e << "}\\right)$.\\\\" << endl;
            answer = a * a - e;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 3:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(\\sqrt{" << e << "}-\\sqrt{" << f << "}\\right)\\left(\\sqrt{" << e << "}+\\sqrt{" << f << "}\\right)$.\\\\" << endl;
            answer = e - f;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 4:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(\\sqrt{" << e << "}+\\sqrt{" << f << "}\\right)\\left(\\sqrt{" << e << "}-\\sqrt{" << f << "}\\right)$.\\\\" << endl;
            answer = e - f;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;
        }
        break;

    }
    return Answer;

}

string Pow(int number, int AllType)
{
    int type;
    int type_1;
    double a, b;
    double pok[4];
    double answer;
    double check;
    string Answer;
    if(AllType == 0)
        type = rand() % 4 + 1;
    else
        type = AllType;
    switch (type)
    {
    case 1:
        do {
            a = rand() % 37 + 2;
            for (int n = 0; n < 3; n++)
                pok[n] = pow(-1, rand()) * (rand() % 20 + 2);
            answer = pow(a, pok[0]) * pow(a, pok[1]) / pow(a, pok[2]);
            check = (answer * 100) / static_cast<int>(answer * 100);
            if (answer > 100)
                check = 0;
        } while (check != 1);
        if (pow(-1, rand()) > 0)
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\frac{" << a << "^{" << pok[0] << "}\\cdot" << a << "^{" << pok[1] << "}}{" << a << "^{" << pok[2] << "}}$. \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow(a, pok[0]) * pow(a, pok[1]) / pow(a, pok[2]);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        else
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\frac{a^{" << pok[0] << "}\\cdot a^{" << pok[1] << "}}{" << "a^{" << pok[2] << "}}$, при a = " << a << ". \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow(a, pok[0]) * pow(a, pok[1]) / pow(a, pok[2]);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        break;

    case 2:
        do {
            a = rand() % 37 + 2;
            for (int n = 0; n < 3; n++)
                pok[n] = pow(-1, rand()) * (rand() % 20 + 2);
            answer = pow(a, pok[0]) * pow(a, pok[1]) / pow(a, pok[2]);
            check = (answer * 100) / static_cast<int>(answer * 100);
            if (answer > 100)
                check = 0;
        } while (check != 1);
        if (pow(-1, rand()) > 0)
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                a << "^{" << pok[0] << "}\\cdot" << a << "^{" << pok[1] << "}:" << a << "^{" << pok[2] << "}$. \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow(a, pok[0]) * pow(a, pok[1]) / pow(a, pok[2]);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        else
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                "a^{" << pok[0] << "}\\cdot a^{" << pok[1] << "}:" << "a^{" << pok[2] << "}$, при a = " << a << ". \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow(a, pok[0]) * pow(a, pok[1]) / pow(a, pok[2]);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        break;

    case 3:
        if (pow(-1, rand()) > 0)
        {
            do {
                a = rand() % 37 + 2;
                for (int n = 0; n < 3; n++)
                    pok[n] = pow(-1, rand()) * (rand() % 20 + 2);
                answer = pow((pow(a, pok[0])), pok[1]) / pow(a, pok[2]);
                check = answer / static_cast<int>(answer);
                if (answer > 100)
                    check = 0;
            } while (check != 1);
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\frac{\\left(a^{" << pok[0] << "}\\right)^{" << pok[1] << "}}{a^{" << pok[2] << "}}$, при a = " << a << ". \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow((pow(a, pok[0])), pok[1]) / pow(a, pok[2]);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        else
        {
            do {
                a = rand() % 37 + 2;
                for (int n = 0; n < 3; n++)
                    pok[n] = pow(-1, rand()) * (rand() % 20 + 2);
                answer = pow((pow(sqrt(a), pok[0])), pok[1]) / pow(sqrt(a), pok[2]);
                check = answer / static_cast<int>(answer);
                if (answer > 100)
                    check = 0;
                if ((a == 4) || (a == 9) || (a == 16) || (a == 25) || (a == 36))
                    check = 0;
            } while (check != 1);
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\frac{\\left(a^{" << pok[0] << "}\\right)^{" << pok[1] << "}}{a^{" << pok[2] << "}}$, при a = $\\sqrt{" << a << "}$. \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow((pow(sqrt(a), pok[0])), pok[1]) / pow(sqrt(a), pok[2]);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        break;

    case 4:
        if (pow(-1, rand()) > 0)
        {
            do {
                a = rand() % 37 + 2;
                b = rand() % 37 + 2;
                for (int n = 0; n < 4; n++)
                    pok[n] = pow(-1, rand()) * (rand() % 20 + 2);
                answer = pow(a, pok[0]) * pow((pow(b, pok[1])), pok[2]) / pow((a * b), pok[3]);
                check = answer / static_cast<int>(answer);
                if (answer > 100)
                    check = 0;
            } while (check != 1);
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\frac{a^{" << pok[0] << "}\\cdot\\left(b^{" << pok[1] << "}\\right)^{" << pok[2] << "}}{\\left(a\\cdot b\\right)^{" << pok[3] << "}}$, при a = " << a << " и b = " << b << ". \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow(a, pok[0]) * pow((pow(b, pok[1])), pok[2]) / pow((a * b), pok[3]);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        else
        {
            do {
                a = rand() % 37 + 2;
                b = rand() % 37 + 2;
                for (int n = 0; n < 4; n++)
                    pok[n] = pow(-1, rand()) * (rand() % 20 + 2);
                answer = pow(a, pok[0]) * pow((pow(sqrt(b), pok[1])), pok[2]) / pow((a * sqrt(b)), pok[3]);
                check = answer / static_cast<int>(answer);
                if (answer > 100)
                    check = 0;
                if ((b == 4) || (b == 9) || (b == 16) || (b == 25) || (b == 36))
                    check = 0;
            } while (check != 1);
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\frac{a^{" << pok[0] << "}\\cdot\\left(b^{" << pok[1] << "}\\right)^{" << pok[2] << "}}{\\left(a\\cdot b\\right)^{" << pok[3] << "}}$, при a = " << a << " и b = $\\sqrt{" << b << "}$. \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow(a, pok[0]) * pow((pow(sqrt(b), pok[1])), pok[2]) / pow((a * sqrt(b)), pok[3]);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        break;
    }
    return Answer;
}

string Sqrt(int number, int AllType)
{
    int type;
    int type_1;
    double a, b, c, d, e;
    double answer;
    string Answer;
    double check;
    if(AllType == 0)
        type = rand() % 5 + 1;
    else
        type = AllType;
    switch (type)
    {
    case 1:
        do {
            a = rand() % 37 + 2;
            b = rand() % 37 + 2;
            c = rand() % 37 + 2;
            answer = sqrt(a) * sqrt(b) / sqrt(c);
            check = answer / static_cast<int>(answer);
            if ((a == 4) || (a == 9) || (a == 16) || (a == 25) || (a == 36))
                check = 0;
            if ((b == 4) || (b == 9) || (b == 16) || (b == 25) || (b == 36))
                check = 0;
            if ((c == 4) || (c == 9) || (c == 16) || (c == 25) || (c == 36))
                check = 0;
        } while (check != 1);
        cout << "\\item     Найдите значение выражения: $ " <<
            "\\frac{\\sqrt{" << a << "}\\cdot\\sqrt{" << b << "}}{\\sqrt{" << c << "}}$." << endl;
        //cout << answer << "\\\\" << endl;
        answer = sqrt(a) * sqrt(b) / sqrt(c);
        Answer = "  \\item " + FormatDouble(answer) + " \n";
        break;

    case 2:
        do {
            a = rand() % 37 + 2;
            b = rand() % 37 + 2;
            c = rand() % 37 + 2;
            answer = sqrt(a) * sqrt(b) * sqrt(c);
            check = answer / static_cast<int>(answer);
            if ((a == 4) || (a == 9) || (a == 16) || (a == 25) || (a == 36))
                check = 0;
            if ((b == 4) || (b == 9) || (b == 16) || (b == 25) || (b == 36))
                check = 0;
            if ((c == 4) || (c == 9) || (c == 16) || (c == 25) || (c == 36))
                check = 0;
            if (answer > 110)
                check = 0;
        } while (check != 1);
        if (pow(-1, rand()) > 0)
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\sqrt{" << a << "\\cdot" << b << "}\\cdot\\sqrt{" << c << "}$." << endl;
            //cout << answer << "\\\\" << endl;
            answer = sqrt(a) * sqrt(b) * sqrt(c);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        else
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\sqrt{" << a << "}\\cdot\\sqrt{" << b << "\\cdot" << c << "}$." << endl;
            //cout << answer << "\\\\" << endl;
            answer = sqrt(a) * sqrt(b) * sqrt(c);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        break;

    case 3:
        do {
            a = rand() % 37 + 2;
            b = rand() % 37 + 2;
            c = rand() % 37 + 2;
            d = rand() % 10 + 2;
            e = rand() % 10 + 2;
            answer = sqrt(a) * sqrt(b) * sqrt(c) * d * e;
            check = answer / static_cast<int>(answer);
            if ((a == 4) || (a == 9) || (a == 16) || (a == 25) || (a == 36))
                check = 0;
            if ((b == 4) || (b == 9) || (b == 16) || (b == 25) || (b == 36))
                check = 0;
            if ((c == 4) || (c == 9) || (c == 16) || (c == 25) || (c == 36))
                check = 0;
            if (answer > 110)
                check = 0;
        } while (check != 1);
        if (pow(-1, rand()) > 0)
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                d << "\\sqrt{" << a << "}\\cdot" << e << "\\sqrt{" << b << "}\\cdot\\sqrt{" << c << "}$." << endl;
            //cout << "\\\\" << answer << "\\\\" << endl;
            answer = sqrt(a) * sqrt(b) * sqrt(c) * d * e;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        else
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                d << "\\sqrt{" << a << "}\\cdot\\sqrt{" << b << "}\\cdot" << e << "\\sqrt{" << c << "}$." << endl;
            //cout << "\\\\" << answer << "\\\\" << endl;
            answer = sqrt(a) * sqrt(b) * sqrt(c) * d * e;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        break;

    case 4:
        type_1 = rand() % 2 + 1;
        switch (type_1)
        {
        case 1:
            do {
                a = rand() % 37 + 2;
                b = rand() % 37 + 2;
                c = rand() % 60 + 2;
                answer = (a * b * b) / c;
                check = (answer * 10) / static_cast<int>((answer * 10));
                if ((a == 4) || (a == 9) || (a == 16) || (a == 25) || (a == 36))
                    check = 0;
                if (answer > 110)
                    check = 0;
            } while (check != 1);
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\frac{\\left(" << b << "\\sqrt{" << a << "}\\right)^2}{" << c << "}$." << endl;
            //cout << "\\\\" << answer << "\\\\" << endl;
            answer = (a * b * b) / c;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 2:
            do {
                a = rand() % 37 + 2;
                b = rand() % 37 + 2;
                c = rand() % 60 + 2;
                answer = c / (b * b * a);
                check = (answer * 10) / static_cast<int>((answer * 10));
                if ((a == 4) || (a == 9) || (a == 16) || (a == 25) || (a == 36))
                    check = 0;
                if (answer > 110)
                    check = 0;
            } while (check != 1);
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\frac{" << c << "}{\\left(" << b << "\\sqrt{" << a << "}\\right)^2}$." << endl;
            //cout << "\\\\" << answer << "\\\\" << endl;
            answer = c / (b * b * a);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;
        }
        break;

    case 5:
        type_1 = rand() % 3 + 1;
        switch (type_1)
        {
        case 1:
            do {
                a = rand() % 37 + 2;
                b = rand() % 37 + 2;
                c = rand() % 37 + 2;
                d = rand() % 10 + 2;
                e = rand() % 10 + 2;
                answer = sqrt(pow(a, d) * pow(b, e) / c);
                check = answer / static_cast<int>(answer);
                if ((a == 4) || (a == 9) || (a == 16) || (a == 25) || (a == 36))
                    check = 0;
                if ((b == 4) || (b == 9) || (b == 16) || (b == 25) || (b == 36))
                    check = 0;
                if (answer > 110)
                    check = 0;
            } while (check != 1);
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\sqrt{\\frac{1}{" << c << "}\\cdot a^{" << d << "}b^{" << e << "}}$ при a = " << a << ", b = " << b << "." << endl;
            //cout << "\\\\" << answer << "\\\\" << endl;
            answer = sqrt(pow(a, d) * pow(b, e) / c);
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 2:
            do {
                a = rand() % 37 + 2;
                b = rand() % 37 + 2;
                d = rand() % 10 + 2;
                e = rand() % 10 + 2;
                answer = sqrt(b * pow(a, d) / pow(a, e));
                check = answer / static_cast<int>(answer);
                if ((a == 4) || (a == 9) || (a == 16) || (a == 25) || (a == 36))
                    check = 0;
                if (answer > 110)
                    check = 0;
                if (d == e)
                    check = 0;
            } while (check != 1);
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\sqrt{\\frac{" << b << "a^{" << d << "}}{a^{" << e << "}}}$ при a = " << a << "." << endl;
            //cout << "\\\\" << answer << "\\\\" << endl;
            answer = sqrt(b * pow(a, d) / pow(a, e));
            Answer = "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 3:
            do {
                a = rand() % 37 + 2;
                d = rand() % 10 + 2;
                e = rand() % 10 + 2;
                answer = sqrt(pow(a, d) * pow(a, e));
                check = answer / static_cast<int>(answer);
                if (answer > 110)
                    check = 0;
                if (d == e)
                    check = 0;
                if ((d == 3) || (d == 5) || (d == 7) || (d == 9) || (d == 11))
                    check = 0;
                if ((e == 3) || (e == 5) || (e == 7) || (e == 9) || (e == 11))
                    check = 0;
            } while (check != 1);
            if (pow(-1, rand()) > 0)
            {
                cout << "\\item     Найдите значение выражения: $ " <<
                    "\\sqrt{(-a)^{" << d << "}\\cdot a^{" << e << "}}$ при a = " << a << "." << endl;
                //cout << "\\\\" << answer << "\\\\" << endl;
                answer = sqrt(pow(a, d) * pow(a, e));
                Answer = "  \\item " + FormatDouble(answer) + " \n";
            }
            else
            {
                cout << "\\item     Найдите значение выражения: $ " <<
                    "\\sqrt{a^{" << d << "}\\cdot (-a)^{" << e << "}}$ при a = " << a << "." << endl;
                //cout << "\\\\" << answer << "\\\\" << endl;
                answer = sqrt(pow(a, d) * pow(a, e));
                Answer = "  \\item " + FormatDouble(answer) + " \n";
            }
            break;

        }
        break;
    }
    return Answer;
}

string TeorVer(int number, int AllType)
{
    int type;
    double a, b, c, d, e, f;
    double answer;
    string Answer;
    double check;
    if(AllType == 0)
        type = rand() % 7 + 1;
    else
        type = AllType;
    switch (type)
    {
    case 1:
        do {
            a = rand() % 40 + 1;
            b = rand() % 40 + 1;
            answer = (a - b) / a;
            check = (answer * 1000) / static_cast<int>((answer * 1000));
            if (b > a)
                check = 0;
        } while (check != 1);
        cout << "\\item    У бабушки " << a << " чашек: " << b << " с красными цветами, остальные с синими.Бабушка наливает чай в случайно выбранную чашку.Найдите вероятность того, что это будет чашка с синими цветами." << endl;
        //cout << "\\\\" << answer << "\\\\" << endl;
        Answer = "  \\item " + FormatDouble(answer) + " \n";
        break;

    case 2:
        do {
            a = rand() % 200 + 1;
            b = rand() % 200 + 1;
            answer = (a - b) / a;
            check = (answer * 1000) / static_cast<int>((answer * 1000));
            if (b > a)
                check = 0;
            if (b > 50)
                check = 0;
            if (a < 100)
                check = 0;
        } while (check != 1);
        cout << "\\item    В среднем из " << a << " карманных фонариков, поступивших в продажу, " << b << " неисправных.Найдите вероятность того, что выбранный наудачу в магазине фонарик окажется исправен." << endl;
        //cout << "\\\\" << answer << "\\\\" << endl;
        Answer = "  \\item " + FormatDouble(answer) + " \n";
        break;

    case 3:
        do {
            a = rand() % 20 + 1;
            b = rand() % 20 + 1;
            c = rand() % 20 + 1;
            d = a - b - c;
            answer = c / a;
            check = (answer * 1000) / static_cast<int>((answer * 1000));
            if (d < 0)
                check = 0;
        } while (check != 1);
        cout << "\\item    В фирме такси в данный момент свободно " << a << " машин: " << b << " чёрных, " << c << " жёлтая и " << d << " зелёных.По вызову выехала одна из машин, случайно оказавшаяся ближе всего к заказчику.Найдите вероятность того, что к нему приедет жёлтое такси." << endl;
        //cout << "\\\\" << answer << "\\\\" << endl;
        Answer = "  \\item " + FormatDouble(answer) + " \n";
        break;

    case 4:
        if (pow(-1, rand()) > 0)
        {
            do {
                a = rand() % 20 + 1;
                b = rand() % 20 + 1;
                c = rand() % 20 + 1;
                answer = b / (a + b + c);
                check = (answer * 1000) / static_cast<int>((answer * 1000));
            } while (check != 1);
            cout << "\\item    В лыжных гонках участвуют " << a << " спортсменов из России, " << b << " спортсмен из Швеции и " << c << " спортсмена из Норвегии.Порядок, в котором спортсмены стартуют, определяется жребием.Найдите вероятность того, что первым будет стартовать спортсмен из Швеции." << endl;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        else
        {
            do {
                a = rand() % 30 + 1;
                b = rand() % 30 + 1;
                c = rand() % 30 + 1;
                answer = (b + c) / (a + b + c);
                check = (answer * 1000) / static_cast<int>((answer * 1000));
            } while (check != 1);
            cout << "\\item    В лыжных гонках участвуют " << a << " спортсменов из России, " << b << " спортсмена из Норвегии и " << c << " спортсменов из Швеции.Порядок, в котором спортсмены стартуют, определяется жребием.Найдите вероятность того, что первым будет стартовать спортсмен не из России." << endl;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + FormatDouble(answer) + " \n";
        }
        break;

    case 5:
        do {
            a = rand() % 20 + 1;
            answer = 1 - (a / 100);
            check = (answer * 1000) / static_cast<int>((answer * 1000));
        } while (check != 1);
        cout << "\\item    Вероятность того, что новая шариковая ручка пишет плохо (или не пишет), равна " << (a / 100) << ". Покупатель в магазине выбирает одну шариковую ручку. Найдите вероятность того, что эта ручка пишет хорошо." << endl;
        //cout << "\\\\" << answer << "\\\\" << endl;
        Answer = "  \\item " + FormatDouble(answer) + " \n";
        break;

    case 6:
        do {
            a = rand() % 100 + 1;
            b = rand() % 20 + 1;
            answer = (a - b) / a;
            check = (answer * 1000) / static_cast<int>((answer * 1000));
            if (b > a)
                check = 0;
        } while (check != 1);
        cout << "\\item    На экзамене " << a << " билетов, Оскар не выучил " << b << " из них. Найдите вероятность того, что ему попадётся выученный билет." << endl;
        //cout << "\\\\" << answer << "\\\\" << endl;
        Answer = "  \\item " + FormatDouble(answer) + " \n";
        break;

    case 7:
        do {
            a = rand() % 100 + 1;
            b = rand() % 20 + 1;
            c = a - b;
            answer = b / a;
            check = (answer * 1000) / static_cast<int>((answer * 1000));
            if (c < 0)
                check = 0;
        } while (check != 1);
        cout << "\\item    Родительский комитет закупил " << a << " пазлов для подарков детям в связи с окончанием учебного года, из них " << b << " с машинами и " << c << " с видами городов.Подарки распределяются случайным образом между " << a << " детьми, среди которых есть Витя.Найдите вероятность того, что Вите достанется пазл с машиной." << endl;
        //cout << "\\\\" << answer << "\\\\" << endl;
        Answer = "  \\item " + FormatDouble(answer) + " \n";
        break;
    }
    return Answer;
}

struct FarString
{
    string STRING;
    int used;
};

struct FarStringTF
{
	string STRING;
	int used;
	int TF;
};

struct Graph
{
    string GraphOut;
    string VarAnswer;
    int PorQ;
    int PorO;
    int TF;
    int used;

};

const double PI = 3.14159265;

string ScobNer(int type, int pos) //type: 1 - строгое неравенство, 2 - нестрогое;   pos: 1 - открывающая скобка, 2 - закрывающая
{
    string scob;
    if ((type == 1) && (pos == 1))
        scob = "(";
    if ((type == 1) && (pos == 2))
        scob = ")";
    if ((type == 2) && (pos == 1))
        scob = "[";
    if ((type == 2) && (pos == 2))
        scob = "]";
    return scob;
}

string ZnakKvadrNer(int type, int Type)
{
    string znak;
    if(type == 1)
    {
        if(Type == 1)
            znak = ">";
        else
            znak = "<";
    }
    if(type == 2)
    {
        if(Type == 1)
            znak = "\\geq";
        else
            znak = "\\leq";
    }
    return znak;
}

string ZnakNer(int type, int Type, int pos) // Type - тип неравенств (от 1го до 4х)
{
    string znak;
    if (type == 1)
    {
        if (Type == 1)
        {
            if (pos == 1)
                znak = ">";
            else
                znak = ">";
        }
        if (Type == 2)
        {
            if (pos == 1)
                znak = ">";
            else
                znak = "<";
        }
        if (Type == 3)
        {
            if (pos == 1)
                znak = "<";
            else
                znak = "<";
        }
        if (Type == 4)
        {
            if (pos == 1)
                znak = "<";
            else
                znak = ">";
        }
    }
    if (type == 2)
    {
        if (Type == 1)
        {
            if (pos == 1)
                znak = "\\geq";
            else
                znak = "\\geq";
        }
        if (Type == 2)
        {
            if (pos == 1)
                znak = "\\geq";
            else
                znak = "\\leq";
        }
        if (Type == 3)
        {
            if (pos == 1)
                znak = "\\leq";
            else
                znak = "\\leq";
        }
        if (Type == 4)
        {
            if (pos == 1)
                znak = "\\leq";
            else
                znak = "\\geq";
        }
    }

    return znak;
}

string NumberLine2(int number, int AllType)
{
            int type;
			double a, p, q, r;
			string min, mid, max;
			FarString True[3];
			FarString False[4];
			string Out[4];
			string Answer;
			double answer, check;
            if(AllType == 0)
                type = rand()%2+1;
            else
                type = AllType;
			switch (type)
			{
			case 1:
				if (pow(-1, rand()) > 0)
				{
					do {
						p = rand() % 90 + 10;
						q = rand() % 90 + 10;
						r = rand() % 90 + 10;
						check = 1;
						if ((fabs(p - q) < 23) || (fabs(p - r) < 23) || (fabs(q - r) < 23))
							check = 0;
					} while (check != 1);
					p = p / 10;
					q = q / 10;
					r = r / 10;
					if ((p < q) && (p < r))
					{
						min = "p";
						if (q < r)
						{
							mid = "q";
							max = "r";
						}
						else
						{
							max = "q";
							mid = "r";
						}
					}
					if ((q < p) && (q < r))
					{
						min = "q";
						if (p < r)
						{
							mid = "p";
							max = "r";
						}
						else
						{
							max = "p";
							mid = "r";
						}
					}
					if ((r < q) && (r < p))
					{
						min = "r";
						if (q < p)
						{
							mid = "q";
							max = "p";
						}
						else
						{
							max = "q";
							mid = "p";
						}
					}
					True[0].STRING = "$" + max + "-" + min + "$";
					True[1].STRING = "$" + max + "-" + mid + "$";
					True[2].STRING = "$" + mid + "-" + min + "$";
					False[0].STRING = "$" + min + "-" + max + "$";
					False[1].STRING = "$" + min + "-" + mid + "$";
					False[2].STRING = "$" + mid + "-" + max + "$";
					False[3].STRING = "ни одна из них";
					for (int i = 0; i < 3; i++)
						True[i].used = 0;
					for (int i = 0; i < 4; i++)
						False[i].used = 0;
					answer = rand() % 4 + 1;
					for (int i = 0; i < 4; i++)
					{
						int done = 0;
						int Var;
						if (i == (answer - 1))
						{
							do {
								Var = rand() % 3;
								if (True[Var].used == 0)
								{
									Out[i] = True[Var].STRING;
									True[Var].used = 1;
									done = 1;
								}
							} while (done != 1);
						}
						else
						{
							do {
								Var = rand() % 4;
								if (False[Var].used == 0)
								{
									Out[i] = False[Var].STRING;
									False[Var].used = 1;
									done = 1;
								}
							} while (done != 1);
						}
					}
					cout << "\\item На координатной прямой отмечены числа $p$, $q$ и $r$:" << endl
						<< "\\begin{center}" << endl << "	\\begin{tikzpicture}" << endl <<
						"		\\draw[thick, -latex] (0,0) -- (10,0);" << endl <<
						"		\\coordinate[label=below:$p$] (p) at (" << p << ", 0);" << endl <<
						"		\\draw[fill=black] (p) circle (1.5pt);" << endl <<
						"		\\coordinate[label=below:$q$] (q) at (" << q << ", 0);" << endl <<
						"		\\draw[fill=black] (q) circle (1.5pt);" << endl <<
						"		\\coordinate[label=below:$r$] (r) at (" << r << ", 0);" << endl <<
						"		\\draw[fill=black] (r) circle (1.5pt);" << endl <<
						"	\\end{tikzpicture}" << endl << "\\end{center}" << endl;
					cout << "Какая из разностей $q-p$, $q-r$, $r-p$ положительна?" << endl;
					cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
						<< "	\\item " << Out[0] << endl
						<< "	\\item " << Out[1] << endl
						<< "	\\item " << Out[2] << endl
						<< "	\\item " << Out[3] << endl
						<< "\\end{enumerate}" << endl << endl;
					//cout << answer << endl;
					Answer = "  \\item " + FormatDouble(answer) + " \n";
				}
				else
				{
					do {
						p = rand() % 90 + 10;
						q = rand() % 90 + 10;
						r = rand() % 90 + 10;
						check = 1;
						if ((fabs(p - q) < 23) || (fabs(p - r) < 23) || (fabs(q - r) < 23))
							check = 0;
					} while (check != 1);
					p = p / 10;
					q = q / 10;
					r = r / 10;
					if ((p < q) && (p < r))
					{
						min = "p";
						if (q < r)
						{
							mid = "q";
							max = "r";
						}
						else
						{
							max = "q";
							mid = "r";
						}
					}
					if ((q < p) && (q < r))
					{
						min = "q";
						if (p < r)
						{
							mid = "p";
							max = "r";
						}
						else
						{
							max = "p";
							mid = "r";
						}
					}
					if ((r < q) && (r < p))
					{
						min = "r";
						if (q < p)
						{
							mid = "q";
							max = "p";
						}
						else
						{
							max = "q";
							mid = "p";
						}
					}
					True[0].STRING = "$" + min + "-" + max + "$";
					True[1].STRING = "$" + min + "-" + mid + "$";
					True[2].STRING = "$" + mid + "-" + max + "$";
					False[0].STRING = "$" + max + "-" + min + "$";
					False[1].STRING = "$" + max + "-" + mid + "$";
					False[2].STRING = "$" + mid + "-" + min + "$";
					False[3].STRING = "ни одна из них";
					for (int i = 0; i < 3; i++)
						True[i].used = 0;
					for (int i = 0; i < 4; i++)
						False[i].used = 0;
					answer = rand() % 4 + 1;
					for (int i = 0; i < 4; i++)
					{
						int done = 0;
						int Var;
						if (i == (answer - 1))
						{
							do {
								Var = rand() % 3;
								if (True[Var].used == 0)
								{
									Out[i] = True[Var].STRING;
									True[Var].used = 1;
									done = 1;
								}
							} while (done != 1);
						}
						else
						{
							do {
								Var = rand() % 4;
								if (False[Var].used == 0)
								{
									Out[i] = False[Var].STRING;
									False[Var].used = 1;
									done = 1;
								}
							} while (done != 1);
						}
					}
					cout << "\\item На координатной прямой отмечены числа $p$, $q$ и $r$:" << endl
						<< "\\begin{center}" << endl << "	\\begin{tikzpicture}" << endl <<
						"		\\draw[thick, -latex] (0,0) -- (10,0);" << endl <<
						"		\\coordinate[label=below:$p$] (p) at (" << p << ", 0);" << endl <<
						"		\\draw[fill=black] (p) circle (1.5pt);" << endl <<
						"		\\coordinate[label=below:$q$] (q) at (" << q << ", 0);" << endl <<
						"		\\draw[fill=black] (q) circle (1.5pt);" << endl <<
						"		\\coordinate[label=below:$r$] (r) at (" << r << ", 0);" << endl <<
						"		\\draw[fill=black] (r) circle (1.5pt);" << endl <<
						"	\\end{tikzpicture}" << endl << "\\end{center}" << endl;
					cout << "Какая из разностей $q-p$, $q-r$, $r-p$ отрицательна?" << endl;
					cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
						<< "	\\item " << Out[0] << endl
						<< "	\\item " << Out[1] << endl
						<< "	\\item " << Out[2] << endl
						<< "	\\item " << Out[3] << endl
						<< "\\end{enumerate}" << endl << endl;
					//cout << answer << endl;
					Answer = "  \\item " + FormatDouble(answer) + " \n";
				}
				break;

			case 2:
				if (pow(-1, rand()) > 0)
				{
					double Xmax = rand() % 7 + 2;
					double x[9];
					int done = 0;
					int VarX, Var;
					x[8] = Xmax;
					double raz = rand() % 75 + 5;
					a = x[8] - (raz / 10);
					for (int i = 7; i >= 0; i--)
					{
						x[i] = x[(i + 1)] - 1;
					}
					answer = rand() % 4 + 1;
					for (int i = 0; i < 3; i++)
						True[i].used = 0;
					for (int i = 0; i < 3; i++)
						False[i].used = 0;
					do {												// Заполнение True
						VarX = rand() % 9;
						Var = rand() % 4 + 1;
						switch (Var)
						{

						case 1:
							if ((x[VarX] - a) > 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != True[m].used)
										check++;
								}
								if (check == 3)
								{
									True[done].STRING = "$ " + to_string(static_cast<int>(x[VarX])) + " - a > 0 $";
									True[done].used = x[VarX];
									done++;
								}
							}
							break;

						case 2:
							if ((x[VarX] - a) < 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != True[m].used)
										check++;
								}
								if (check == 3)
								{
									True[done].STRING = "$ " + to_string(static_cast<int>(x[VarX])) + " - a < 0 $";
									True[done].used = x[VarX];
									done++;
								}
							}
							break;

						case 3:
							if ((a - x[VarX]) > 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != True[m].used)
										check++;
								}
								if (check == 3)
								{
									if (x[VarX] > 0)
									{
										True[done].STRING = "$ a - " + to_string(static_cast<int>(x[VarX])) + " > 0 $";
										True[done].used = x[VarX];
										done++;
									}
									else
									{
										True[done].STRING = "$ a + " + to_string(static_cast<int>(fabs(x[VarX]))) + " > 0 $";
										True[done].used = x[VarX];
										done++;
									}

								}
							}
							break;

						case 4:
							if ((a - x[VarX]) < 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != True[m].used)
										check++;
								}
								if (check == 3)
								{
									if (x[VarX] > 0)
									{
										True[done].STRING = "$ a - " + to_string(static_cast<int>(x[VarX])) + " < 0 $";
										True[done].used = x[VarX];
										done++;
									}
									else
									{
										True[done].STRING = "$ a + " + to_string(static_cast<int>(fabs(x[VarX]))) + " < 0 $";
										True[done].used = x[VarX];
										done++;
									}

								}
							}
							break;
						}
					} while (done != 3);
					done = 0;
					do {												// Заполнение False
						VarX = rand() % 9;
						Var = rand() % 4 + 1;
						switch (Var)
						{

						case 1:
							if ((x[VarX] - a) > 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != False[m].used)
										check++;
								}
								if (check == 3)
								{
									False[done].STRING = "$ " + to_string(static_cast<int>(x[VarX])) + " - a < 0 $";
									False[done].used = x[VarX];
									done++;
								}
							}
							break;

						case 2:
							if ((x[VarX] - a) < 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != False[m].used)
										check++;
								}
								if (check == 3)
								{
									False[done].STRING = "$ " + to_string(static_cast<int>(x[VarX])) + " - a > 0 $";
									False[done].used = x[VarX];
									done++;
								}
							}
							break;

						case 3:
							if ((a - x[VarX]) > 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != False[m].used)
										check++;
								}
								if (check == 3)
								{
									if (x[VarX] > 0)
									{
										False[done].STRING = "$ a - " + to_string(static_cast<int>(x[VarX])) + " < 0 $";
										False[done].used = x[VarX];
										done++;
									}
									else
									{
										False[done].STRING = "$ a + " + to_string(static_cast<int>(fabs(x[VarX]))) + " < 0 $";
										False[done].used = x[VarX];
										done++;
									}

								}
							}
							break;

						case 4:
							if ((a - x[VarX]) < 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != False[m].used)
										check++;
								}
								if (check == 3)
								{
									if (x[VarX] > 0)
									{
										False[done].STRING = "$ a - " + to_string(static_cast<int>(x[VarX])) + " > 0 $";
										False[done].used = x[VarX];
										done++;
									}
									else
									{
										False[done].STRING = "$ a + " + to_string(static_cast<int>(fabs(x[VarX]))) + " > 0 $";
										False[done].used = x[VarX];
										done++;
									}

								}
							}
							break;
						}
					} while (done != 3);
					for (int i = 0; i < 3; i++)
						True[i].used = 0;
					for (int i = 0; i < 3; i++)
						False[i].used = 0;
					done = 0;
					for (int i = 0; i < 4; i++)					// Заполнение Out
					{
						if (i == (answer - 1))
						{
							do {
								Var = rand() % 3;
								if (True[Var].used == 0)
								{
									Out[i] = True[Var].STRING;
									True[Var].used = 1;
									done = 1;
								}
							} while (done != 1);
							done = 0;
						}
						else
						{
							do {
								Var = rand() % 3;
								if (False[Var].used == 0)
								{
									Out[i] = False[Var].STRING;
									False[Var].used = 1;
									done = 1;
								}
							} while (done != 1);
							done = 0;
						}
					}
					cout << "\\item На координатной прямой отмечено число $a$:" << endl
						<< "\\begin{center}" << endl << "	\\begin{tikzpicture}" << endl;
					cout << "		\\draw[thick, -latex] (" << x[0] - 1 << ", 0) -- (" << Xmax + 1 << ", 0); " << endl
						<< "		\\coordinate[label=below:$0$] (O) at (0, 0);" << endl
						<< "		\\coordinate[label=below:$a$] (A) at (" << a << ", 0); " << endl
						<< "		\\draw[fill=black] (A) circle (1.5pt);" << endl;
					for (int i = 0; i < 9; i++)
					{
						cout << "		\\draw[thick] (" << x[i] << ", -0.07) -- (" << x[i] << ", 0.07); " << endl;
					}
					cout << "	\\end{tikzpicture}" << endl << "\\end{center}" << endl;
					cout << "Какое из утверждений для этого числа является верным?" << endl;
					cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
						<< "	\\item " << Out[0] << endl
						<< "	\\item " << Out[1] << endl
						<< "	\\item " << Out[2] << endl
						<< "	\\item " << Out[3] << endl
						<< "\\end{enumerate}" << endl << endl;
					//cout << answer << endl;
					Answer = "  \\item " + FormatDouble(answer) + " \n";
				}
				else
				{
					double Xmax = rand() % 7 + 2;
					double x[9];
					int done = 0;
					int VarX, Var;
					x[8] = Xmax;
					double raz = rand() % 75 + 5;
					a = x[8] - (raz / 10);
					for (int i = 7; i >= 0; i--)
					{
						x[i] = x[(i + 1)] - 1;
					}
					answer = rand() % 4 + 1;
					for (int i = 0; i < 3; i++)
						True[i].used = 0;
					for (int i = 0; i < 4; i++)
						False[i].used = 0;
					do {								// Заполнение True
						VarX = rand() % 9;
						Var = rand() % 4 + 1;
						switch (Var)
						{

						case 1:
							if ((x[VarX] - a) > 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != True[m].used)
										check++;
								}
								if (check == 3)
								{
									True[done].STRING = "$ " + to_string(static_cast<int>(x[VarX])) + " - a > 0 $";
									True[done].used = x[VarX];
									done++;
								}
							}
							break;

						case 2:
							if ((x[VarX] - a) < 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != True[m].used)
										check++;
								}
								if (check == 3)
								{
									True[done].STRING = "$ " + to_string(static_cast<int>(x[VarX])) + " - a < 0 $";
									True[done].used = x[VarX];
									done++;
								}
							}
							break;

						case 3:
							if ((a - x[VarX]) > 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != True[m].used)
										check++;
								}
								if (check == 3)
								{
									if (x[VarX] > 0)
									{
										True[done].STRING = "$ a - " + to_string(static_cast<int>(x[VarX])) + " > 0 $";
										True[done].used = x[VarX];
										done++;
									}
									else
									{
										True[done].STRING = "$ a + " + to_string(static_cast<int>(fabs(x[VarX]))) + " > 0 $";
										True[done].used = x[VarX];
										done++;
									}

								}
							}
							break;

						case 4:
							if ((a - x[VarX]) < 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != True[m].used)
										check++;
								}
								if (check == 3)
								{
									if (x[VarX] > 0)
									{
										True[done].STRING = "$ a - " + to_string(static_cast<int>(x[VarX])) + " < 0 $";
										True[done].used = x[VarX];
										done++;
									}
									else
									{
										True[done].STRING = "$ a + " + to_string(static_cast<int>(fabs(x[VarX]))) + " < 0 $";
										True[done].used = x[VarX];
										done++;
									}

								}
							}
							break;
						}
					} while (done != 3);
					done = 0;
					do {								// Заполнение False
						VarX = rand() % 9;
						Var = rand() % 4 + 1;
						switch (Var)
						{

						case 1:
							if ((x[VarX] - a) > 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != False[m].used)
										check++;
								}
								if (check == 3)
								{
									False[done].STRING = "$ " + to_string(static_cast<int>(x[VarX])) + " - a < 0 $";
									False[done].used = x[VarX];
									done++;
								}
							}
							break;

						case 2:
							if ((x[VarX] - a) < 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != False[m].used)
										check++;
								}
								if (check == 3)
								{
									False[done].STRING = "$ " + to_string(static_cast<int>(x[VarX])) + " - a > 0 $";
									False[done].used = x[VarX];
									done++;
								}
							}
							break;

						case 3:
							if ((a - x[VarX]) > 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != False[m].used)
										check++;
								}
								if (check == 3)
								{
									if (x[VarX] > 0)
									{
										False[done].STRING = "$ a - " + to_string(static_cast<int>(x[VarX])) + " < 0 $";
										False[done].used = x[VarX];
										done++;
									}
									else
									{
										False[done].STRING = "$ a + " + to_string(static_cast<int>(fabs(x[VarX]))) + " < 0 $";
										False[done].used = x[VarX];
										done++;
									}

								}
							}
							break;

						case 4:
							if ((a - x[VarX]) < 0)
							{
								int check = 0;
								for (int m = 0; m < 3; m++)
								{
									if (x[VarX] != False[m].used)
										check++;
								}
								if (check == 3)
								{
									if (x[VarX] > 0)
									{
										False[done].STRING = "$ a - " + to_string(static_cast<int>(x[VarX])) + " > 0 $";
										False[done].used = x[VarX];
										done++;
									}
									else
									{
										False[done].STRING = "$ a + " + to_string(static_cast<int>(fabs(x[VarX]))) + " > 0 $";
										False[done].used = x[VarX];
										done++;
									}

								}
							}
							break;
						}
					} while (done != 4);
					for (int i = 0; i < 3; i++)
						True[i].used = 0;
					for (int i = 0; i < 4; i++)
						False[i].used = 0;
					done = 0;

					for (int i = 0; i < 4; i++)					// Заполнение Out
					{
						if (i == (answer - 1))
						{
							do {
								Var = rand() % 3;
								if (False[Var].used == 0)
								{
									Out[i] = False[Var].STRING;
									False[Var].used = 1;
									done = 1;
								}
							} while (done != 1);
							done = 0;
						}
						else
						{
							do {
								Var = rand() % 3;
								if (True[Var].used == 0)
								{
									Out[i] = True[Var].STRING;
									True[Var].used = 1;
									done = 1;
								}
							} while (done != 1);
							done = 0;
						}
					}
					cout << "\\item На координатной прямой отмечено число $a$:" << endl
						<< "\\begin{center}" << endl << "	\\begin{tikzpicture}" << endl;
					cout << "		\\draw[thick, -latex] (" << x[0] - 1 << ", 0) -- (" << Xmax + 1 << ", 0); " << endl
						<< "		\\coordinate[label=below:$0$] (O) at (0, 0);" << endl
						<< "		\\coordinate[label=below:$a$] (A) at (" << a << ", 0); " << endl
						<< "		\\draw[fill=black] (A) circle (1.5pt);" << endl;
					for (int i = 0; i < 9; i++)
					{
						cout << "		\\draw[thick] (" << x[i] << ", -0.07) -- (" << x[i] << ", 0.07); " << endl;
					}
					cout << "	\\end{tikzpicture}" << endl << "\\end{center}" << endl;
					cout << "Какое из утверждений для этого числа является не верным?" << endl;
					cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
						<< "	\\item " << Out[0] << endl
						<< "	\\item " << Out[1] << endl
						<< "	\\item " << Out[2] << endl
						<< "	\\item " << Out[3] << endl
						<< "\\end{enumerate}" << endl << endl;
					//cout << answer << endl;
					Answer = "  \\item " + FormatDouble(answer) + " \n";
				}

			}
			return Answer;
}

string NumberLine1(int number, int AllType)
{
    int answer;
			int check = 0;
			int type;
			FarString True;
			FarString False[3];
			FarStringTF TrueFalse[4];
			string Out[4];
			string Answer;
            if(AllType == 0)
                type = rand()%7 + 1;
            else
                type = AllType;
			switch (type)
			{
			case 1:
				int a1;
				int b1[8];
				do {
					a1 = rand() % 64 + 35;
					b1[0] = static_cast<int>(sqrt(a1) - 1);
					b1[1] = b1[0] + 2;
					b1[2] = rand() % 9 + 3;
					b1[3] = b1[2] + 2;
					b1[4] = rand() % 64 + 35;
					b1[6] = rand() % 64 + 35;
					b1[5] = b1[4] + 2;
					b1[7] = b1[6] + 2;
					check = 1;
					if ((b1[2] < sqrt(a1)) && (b1[3] > sqrt(a1)))
						check = 0;
					if ((b1[4] < sqrt(a1)) && (b1[5] > sqrt(a1)))
						check = 0;
					if ((b1[6] < sqrt(a1)) && (b1[7] > sqrt(a1)))
						check = 0;
					if ((a1 == 36) || (a1 == 49) || (a1 == 64) || (a1 == 81) || (a1 == 100))
						check = 0;
				} while (check != 1);
				for (int i = 0; i < 3; i++)
				{
					False[i].used = 0;
				}
				True.STRING = to_string(b1[0]) + " и " + to_string(b1[1]) + "\n";
				False[0].STRING = to_string(b1[2]) + " и " + to_string(b1[3]) + "\n";
				False[1].STRING = to_string(b1[4]) + " и " + to_string(b1[5]) + "\n";
				False[2].STRING = to_string(b1[6]) + " и " + to_string(b1[7]) + "\n";

				answer = rand() % 4 + 1;
				for (int i = 0; i < 4; i++)
				{
					int done = 0;
					int Var;
					if (i == (answer - 1))
					{
						Out[i] = True.STRING;
					}
					else
					{
						do {
							Var = rand() % 3;
							if (False[Var].used == 0)
							{
								Out[i] = False[Var].STRING;
								False[Var].used = 1;
								done = 1;
							}
						} while (done != 1);
					}
				}

				cout << "\\item Между какими числами заключено число $\\sqrt{" << a1 << "}$ ? " << endl;
				cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << answer << endl;
				Answer = "  \\item " + FormatDouble(answer) + " \n";
				break;

			case 2:
				double a2[2];
				double b2[8];
				int nod;
				double del;
				//int nod;
				do {
					a2[0] = rand() % 64 + 35;
					a2[1] = rand() % 17 + 4;
					del = a2[0] / a2[1];
					b2[0] = static_cast<int>(del) - 1;
					b2[1] = b2[0] + 2;
					b2[2] = rand() % 9 + 3;
					b2[3] = b2[2] + 2;
					b2[4] = rand() % 64 + 35;
					b2[6] = rand() % 64 + 35;
					b2[5] = b2[4] + 2;
					b2[7] = b2[6] + 2;
					nod = NOD(a2[0], a2[1]);
					a2[0] = a2[0] / nod;
					a2[1] = a2[1] / nod;
					check = 1;
					if ((b2[2] < del) && (b2[3] > del))
						check = 0;
					if ((b2[4] < del) && (b2[5] > del))
						check = 0;
					if ((b2[6] < del) && (b2[7] > del))
						check = 0;
					if (a2[1] == 1)
						check = 0;
					if (((static_cast<int>(a2[1]) % 2) == 0) || ((static_cast<int>(a2[1]) % 5) == 0))
						check = 0;
					if (a2[0] < a2[1])
						check = 0;
				} while (check != 1);
				for (int i = 0; i < 3; i++)
				{
					False[i].used = 0;
				}
				True.STRING = to_string(static_cast<int>(b2[0])) + " и " + to_string(static_cast<int>(b2[1])) + "\n";
				False[0].STRING = to_string(static_cast<int>(b2[2])) + " и " + to_string(static_cast<int>(b2[3])) + "\n";
				False[1].STRING = to_string(static_cast<int>(b2[4])) + " и " + to_string(static_cast<int>(b2[5])) + "\n";
				False[2].STRING = to_string(static_cast<int>(b2[6])) + " и " + to_string(static_cast<int>(b2[7])) + "\n";

				answer = rand() % 4 + 1;
				for (int i = 0; i < 4; i++)
				{
					int done = 0;
					int Var;
					if (i == (answer - 1))
					{
						Out[i] = True.STRING;
					}
					else
					{
						do {
							Var = rand() % 3;
							if (False[Var].used == 0)
							{
								Out[i] = False[Var].STRING;
								False[Var].used = 1;
								done = 1;
							}
						} while (done != 1);
					}
				}

				cout << "\\item Между какими числами заключено число $\\frac{" << a2[0] << "}{" << a2[1] << "}$ ? " << endl;
				cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << answer << endl;
				Answer = "  \\item " + FormatDouble(answer) + " \n";
				break;

			case 3:
				double a3[2];
				double b3[5];
				double del2;
				int nod2;
				do {
					a3[0] = rand() % 67 + 2;
					a3[1] = rand() % 67 + 2;
					b3[0] = rand() % 5 + 1;
					b3[1] = b3[0] + 1;
					b3[2] = b3[1] + 1;
					b3[3] = b3[2] + 1;
					b3[4] = b3[3] + 1;
					del2 = a3[0] / a3[1];
					if ((b3[0] < (del2 * 10)) && (b3[4] > (del2 * 10)))
						check = 1;
					nod2 = NOD(a3[0], a3[1]);
					a3[0] = a3[0] / nod2;
					a3[1] = a3[1] / nod2;
					if (a3[1] == 1)
						check = 0;
				} while (check != 1);
				for (int i = 0; i < 4; i++)
				{
					TrueFalse[i].TF = 0;
				}
				for (int i = 0; i < 4; i++)
				{
					TrueFalse[i].used = 0;
				}
				TrueFalse[0].STRING = "$[0," + to_string(static_cast<int>(b3[0])) + ";0," + to_string(static_cast<int>(b3[1])) + "]$";
				TrueFalse[1].STRING = "$[0," + to_string(static_cast<int>(b3[1])) + ";0," + to_string(static_cast<int>(b3[2])) + "]$";
				TrueFalse[2].STRING = "$[0," + to_string(static_cast<int>(b3[2])) + ";0," + to_string(static_cast<int>(b3[3])) + "]$";
				TrueFalse[3].STRING = "$[0," + to_string(static_cast<int>(b3[3])) + ";0," + to_string(static_cast<int>(b3[4])) + "]$";
				for (int i = 0; i < 4; i++)
				{
					if ((b3[i] < (del2 * 10)) && (b3[i + 1] > (del2 * 10)))
					{
						TrueFalse[i].TF = 1;
					}
				}
				answer = rand() % 4 + 1;
				for (int i = 0; i < 4; i++)
				{
					int done = 0;
					if (i == (answer - 1))
					{
						for (int m = 0; m < 4; m++)
						{
							if (TrueFalse[m].TF == 1)
							{
								Out[i] = TrueFalse[m].STRING;
								TrueFalse[m].used = 1;
							}
						}
					}
					else
					{
						do {
							int Var = rand() % 4;
							if ((TrueFalse[Var].used) == 0)
							{
								Out[i] = TrueFalse[Var].STRING;
								TrueFalse[Var].used = 1;
								done = 1;
							}
						} while (done != 1);
					}
				}
				cout << "\\item Какому из данных промежутков принадлежит число $\\frac{" << a3[0] << "}{" << a3[1] << "}$ ? " << endl;
				cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << answer << endl;
				Answer = "  \\item " + FormatDouble(answer) + " \n";
				break;

			case 4:
				int x[3];
				double razn;
				double number;
				double leter[4];
				check = 0;
				do
				{
					razn = 3;
					number = rand() % 180 + 30;
					if (pow(-1, rand())>0)
						x[0] = static_cast<int>(sqrt(number));                    // Помещает искомое число в первый промежуток
					else
						x[0] = static_cast<int>(sqrt(number)) - 1;                // Помещает искомое число во второй промежуток
					x[1] = x[0] + 1;
					x[2] = x[1] + 1;
					for (int i = 0; i < 3; i++)
					{
						if (razn > fabs(sqrt(number) - x[i]))
							razn = fabs(sqrt(number) - x[i]);
					}
					if ((razn < 0.4) && (razn > 0.1))
						check = 1;
				} while (check != 1);
				

				leter[0] = x[0] + razn;
				leter[1] = x[1] - razn;
				leter[2] = x[1] + razn;
				leter[3] = x[2] - razn;

				TrueFalse[0].STRING = "A";
				TrueFalse[1].STRING = "B";
				TrueFalse[2].STRING = "C";
				TrueFalse[3].STRING = "D";
				for (int i = 0; i < 4; i++)
				{
					TrueFalse[i].used = 0;
				}
				for (int i = 0; i < 4; i++)
				{
					if (sqrt(number) == leter[i])
					{
						TrueFalse[i].TF = 1;
						TrueFalse[i].used = 1;
					}
					else
						TrueFalse[i].TF = 0;
				}
				answer = rand() % 4 + 1;
				for (int i = 0; i < 4; i++)
				{
					int done = 0;
					if (i == (answer - 1))
					{
						for (int m = 0; m < 4; m++)
						{
							if (TrueFalse[m].TF == 1)
							{
								Out[i] = TrueFalse[m].STRING;
							}
						}
					}
					else
					{
						do {
							int Var = rand() % 4;
							if ((TrueFalse[Var].used) == 0)
							{
								Out[i] = TrueFalse[Var].STRING;
								TrueFalse[Var].used = 1;
								done = 1;
							}
						} while (done != 1);
					}
				}
				cout << "\\item На координатной прямой отмечены точки $A$, $B$, $C$, $D$. Одна из них соответствует числу $\\sqrt{" << number << "}$." << endl
					<< "\\begin{center}" << endl << "	\\begin{tikzpicture}" << endl;
				cout << "		\\draw[thick, -latex] (0, 0) -- (10, 0); " << endl
					<< "		\\coordinate[label=below:$" << x[0] << "$] (1) at (1.5, -0.07);" << endl
					<< "        \\draw[thick] (1.5,-0.07) -- (1.5, 0.07);" << endl
					<< "		\\coordinate[label=below:$" << x[1] << "$] (2) at (5, -0.07);" << endl
					<< "        \\draw[thick] (5,-0.07) -- (5, 0.07);" << endl
					<< "		\\coordinate[label=below:$" << x[2] << "$] (3) at (8.5, -0.07);" << endl
					<< "        \\draw[thick] (8.5,-0.07) -- (8.5, 0.07);" << endl
					<< "        \\coordinate[label=above:$A$] (A) at (" << (1.5 + 3.5 * razn) << ",0);" << endl
					<< "        \\draw[fill=black] (A) circle (1.5pt);" << endl
					<< "        \\coordinate[label=above:$B$] (B) at (" << (5 - 3.5 * razn) << ",0);" << endl
					<< "        \\draw[fill=black] (B) circle (1.5pt);" << endl
					<< "        \\coordinate[label=above:$C$] (C) at (" << (5 + 3.5 * razn) << ",0);" << endl
					<< "        \\draw[fill=black] (C) circle (1.5pt);" << endl
					<< "        \\coordinate[label=above:$D$] (D) at (" << (8.5 - 3.5 * razn) << ",0);" << endl
					<< "        \\draw[fill=black] (D) circle (1.5pt);" << endl;


				cout << "	\\end{tikzpicture}" << endl << "\\end{center}" << endl;
				cout << "Какая это точка?" << endl;
				cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << "Ответ: " << answer << endl;
				Answer = "  \\item " + FormatDouble(answer) + " \n";

				break;

			case 5:
				int x5[3];
				double razn5;
				double number5;
				double leter5[4];
				double a5[2];
				int nod5;
				check = 0;
				do
				{
					razn5 = 3;
					do {
						a5[0] = rand() % 130 + 30;
						a5[1] = rand() % 43 + 17;
						nod5 = NOD(a5[0], a5[1]);
						a5[0] = a5[0] / nod5;
						a5[1] = a5[1] / nod5;
						check = 2;
						if ((a5[1] == 1) || (a5[0] < a5[1]))
							check = 0;
					} while (check != 2);

					number5 = a5[0] / a5[1];
					
					if (pow(-1, rand())>0)
						x5[0] = static_cast<int>(number5);                    // Помещает искомое число в первый промежуток
					else
						x5[0] = static_cast<int>(number5) - 1;                // Помещает искомое число во второй промежуток
					x5[1] = x5[0] + 1;
					x5[2] = x5[1] + 1;
					for (int i = 0; i < 3; i++)
					{
						if (razn5 > fabs(number5 - x5[i]))
							razn5 = fabs(number5 - x5[i]);
					}
					if ((razn5 < 0.4) && (razn5 > 0.1))
						check = 1;
				} while (check != 1);
				leter5[0] = x5[0] + razn5;
				leter5[1] = x5[1] - razn5;
				leter5[2] = x5[1] + razn5;
				leter5[3] = x5[2] - razn5;

				TrueFalse[0].STRING = "A";
				TrueFalse[1].STRING = "B";
				TrueFalse[2].STRING = "C";
				TrueFalse[3].STRING = "D";

				for (int i = 0; i < 4; i++)
				{
					TrueFalse[i].used = 0;
				}
				for (int i = 0; i < 4; i++)
				{
					if (number5 == leter5[i])
					{
						TrueFalse[i].TF = 1;
						TrueFalse[i].used = 1;
					}
					else
						TrueFalse[i].TF = 0;
				}

				answer = rand() % 4 + 1;
				for (int i = 0; i < 4; i++)
				{
					int done5 = 0;
					if (i == (answer - 1))
					{
						for (int m = 0; m < 4; m++)
						{
							if (TrueFalse[m].TF == 1)
							{
								Out[i] = TrueFalse[m].STRING;
							}
						}
					}
					else
					{
						do {
							int Var5 = rand() % 4;
							if ((TrueFalse[Var5].used) == 0)
							{
								Out[i] = TrueFalse[Var5].STRING;
								TrueFalse[Var5].used = 1;
								done5 = 1;
							}
						} while (done5 != 1);
					}
				}
				cout << "\\item На координатной прямой отмечены точки $A$, $B$, $C$, $D$. Одна из них соответствует числу $\\frac{" << a5[0] << "}{" << a5[1] << "}$." << endl
					<< "\\begin{center}" << endl << "	\\begin{tikzpicture}" << endl;
				cout << "		\\draw[thick, -latex] (0, 0) -- (10, 0); " << endl
					<< "		\\coordinate[label=below:$" << x5[0] << "$] (1) at (1.5, -0.07);" << endl
					<< "        \\draw[thick] (1.5,-0.07) -- (1.5, 0.07);" << endl
					<< "		\\coordinate[label=below:$" << x5[1] << "$] (2) at (5, -0.07);" << endl
					<< "        \\draw[thick] (5,-0.07) -- (5, 0.07);" << endl
					<< "		\\coordinate[label=below:$" << x5[2] << "$] (3) at (8.5, -0.07);" << endl
					<< "        \\draw[thick] (8.5,-0.07) -- (8.5, 0.07);" << endl
					<< "        \\coordinate[label=above:$A$] (A) at (" << (1.5 + 3.5 * razn5) << ",0);" << endl
					<< "        \\draw[fill=black] (A) circle (1.5pt);" << endl
					<< "        \\coordinate[label=above:$B$] (B) at (" << (5 - 3.5 * razn5) << ",0);" << endl
					<< "        \\draw[fill=black] (B) circle (1.5pt);" << endl
					<< "        \\coordinate[label=above:$C$] (C) at (" << (5 + 3.5 * razn5) << ",0);" << endl
					<< "        \\draw[fill=black] (C) circle (1.5pt);" << endl
					<< "        \\coordinate[label=above:$D$] (D) at (" << (8.5 - 3.5 * razn5) << ",0);" << endl
					<< "        \\draw[fill=black] (D) circle (1.5pt);" << endl;


				cout << "	\\end{tikzpicture}" << endl << "\\end{center}" << endl;
				cout << "Какая это точка?" << endl;
				cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << "Ответ: " << answer << endl;
				Answer = "  \\item " + FormatDouble(answer) + " \n";

				break;
			
			case 6:
				double x6[3];
				double razn6;
				double a6[4];
				double number6;
				int A;
				check = 0;
				do {
					razn6 = 3;
					a6[0] = rand() % 50 + 17;

					for (int i = 1; i <= 3; i++)
					{
						if (pow(-1, rand()) > 0)
							a6[i] = a6[i-1] + 6;
						else
							a6[i] = a6[i-1] + 5;
					}

					answer = rand() % 4;
					A = answer;

					number6 = sqrt(a6[answer]);
					if (pow(-1, rand()) > 0)
						x6[0] = static_cast<int>(number6);                    // Помещает искомое число в первый промежуток
					else
						x6[0] = static_cast<int>(number6) - 1;                // Помещает искомое число во второй промежуток
					x6[1] = x6[0] + 1;
					x6[2] = x6[1] + 1;


					for (int i = 0; i < 3; i++)
					{
						if (razn6 > fabs(number6 - x6[i]))
							razn6 = fabs(number6 - x6[i]);
					}

					check = 1;
					for (int i = 0; i < 4; i++)
					{
						if ((a6[i] == 16) || (a6[i] == 25) || (a6[i] == 36) || (a6[i] == 49) || (a6[i] == 64) || (a6[i] == 81) || (a6[i] == 100) || (a6[i] == 121) || (a6[i] == 144))
							check = 0;
					}
					if (razn6 > 0.35)
						check = 0;
					if (razn6 < 0.08)
						check = 0;

				} while (check != 1);
				
				TrueFalse[0].STRING = "$\\sqrt{" + to_string(static_cast<int>(a6[0])) + "}$";
				TrueFalse[1].STRING = "$\\sqrt{" + to_string(static_cast<int>(a6[1])) + "}$";
				TrueFalse[2].STRING = "$\\sqrt{" + to_string(static_cast<int>(a6[2])) + "}$";
				TrueFalse[3].STRING = "$\\sqrt{" + to_string(static_cast<int>(a6[3])) + "}$";
				
				for (int i = 0; i < 4; i++)
					TrueFalse[i].TF = 0;

				for (int i = 0; i < 4; i++)
					TrueFalse[i].used = 0;

				TrueFalse[answer].TF = 1;
				TrueFalse[answer].used = 1;

				answer = rand() % 4 + 1;
				for (int i = 0; i < 4; i++)
				{
					int done6 = 0;
					if (i == (answer - 1))
					{
						for (int m = 0; m < 4; m++)
						{
							if (TrueFalse[m].TF == 1)
							{
								Out[i] = TrueFalse[m].STRING;
							}
						}
					}
					else
					{
						do {
							int Var6 = rand() % 4;
							if ((TrueFalse[Var6].used) == 0)
							{
								Out[i] = TrueFalse[Var6].STRING;
								TrueFalse[Var6].used = 1;
								done6 = 1;
							}
						} while (done6 != 1);
					}
				}
				cout << "\\item Одно из чисел $\\sqrt{" << a6[0] << "}$, $\\sqrt{" << a6[1] << "}$, $\\sqrt{" << a6[2] << "}$, $\\sqrt{" << a6[3] << "}$ отмечено на прямой точкой $A$." << endl
					<< "\\begin{center}" << endl << "	\\begin{tikzpicture}" << endl;
				cout << "		\\draw[thick, -latex] (0, 0) -- (10, 0); " << endl
					<< "		\\coordinate[label=below:$" << x6[0] << "$] (1) at (1.5, -0.07);" << endl
					<< "        \\draw[thick] (1.5,-0.07) -- (1.5, 0.07);" << endl
					<< "		\\coordinate[label=below:$" << x6[1] << "$] (2) at (5, -0.07);" << endl
					<< "        \\draw[thick] (5,-0.07) -- (5, 0.07);" << endl
					<< "		\\coordinate[label=below:$" << x6[2] << "$] (3) at (8.5, -0.07);" << endl
					<< "        \\draw[thick] (8.5,-0.07) -- (8.5, 0.07);" << endl
					<< "        \\coordinate[label=above:$A$] (A) at (" << (1.5 + 3.5 * (number6-x6[0])) << ",0);" << endl
					<< "        \\draw[fill=black] (A) circle (1.5pt);" << endl;


				cout << "	\\end{tikzpicture}" << endl << "\\end{center}" << endl;
				cout << "Какое это число?" << endl;
				cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << "Ответ: " << answer << endl;
				Answer = "  \\item " + FormatDouble(answer) + " \n";
				break;

			case 7:
				double x7[4];
				double raznMin;
				double a7[4];
				int aanswer;
				double aout7[4];
				check = 0;
				do {
					raznMin = 10;
					for (int i = 0; i < 4; i++)
					{
						a7[i] = pow(-1,rand())*(rand() % 900 + 11);
						a7[i] = a7[i] / 1000;
					}
					for (int i = 0; i < 4; i++)
						aout7[i] = a7[i];
					for (int n = 0; n < 3; n++)	// Сортировка массива
					{
						double change;
						for (int m = 0; m < 3; m++)
						{
							if (a7[m] > a7[m + 1])
							{
								change = a7[m];
								a7[m] = a7[m + 1];
								a7[m + 1] = change;
							}
						}
					}
					for (int i = 0; i < 4; i++)
					{
						x7[i] = 1.5 + ((7 * (a7[i] - a7[0])) / (a7[3] - a7[0]));
					}
					if ((x7[3] - x7[2]) < raznMin)
						raznMin = x7[3] - x7[2];
					if ((x7[2] - x7[1]) < raznMin)
						raznMin = x7[2] - x7[1];
					if ((x7[1] - x7[0]) < raznMin)
						raznMin = x7[1] - x7[0];
					check = 1;
					if (raznMin < 0.5)
						check = 0;
				} while (check != 1);

				TrueFalse[0].STRING = "A";
				TrueFalse[1].STRING = "B";
				TrueFalse[2].STRING = "C";
				TrueFalse[3].STRING = "D";

				for (int i = 0; i < 4; i++)
					TrueFalse[i].TF = 0;

				for (int i = 0; i < 4; i++)
					TrueFalse[i].used = 0;

				aanswer = rand() % 4;
				TrueFalse[aanswer].TF = 1;
				TrueFalse[aanswer].used = 1;

				answer = rand() % 4 + 1;
				for (int i = 0; i < 4; i++)
				{
					int done7 = 0;
					if (i == (answer - 1))
					{
						for (int m = 0; m < 4; m++)
						{
							if (TrueFalse[m].TF == 1)
							{
								Out[i] = TrueFalse[m].STRING;
							}
						}
					}
					else
					{
						do {
							int Var7 = rand() % 4;
							if ((TrueFalse[Var7].used) == 0)
							{
								Out[i] = TrueFalse[Var7].STRING;
								TrueFalse[Var7].used = 1;
								done7 = 1;
							}
						} while (done7 != 1);
					}
				}

				cout << "\\item На координатной прямой точки $A$, $B$, $C$, и $D$ соответсвуют числам\\\\ " << aout7[0] << "; " << aout7[1] << "; " << aout7[2] << "; " << aout7[3] << "." << endl
					<< "\\begin{center}" << endl << "	\\begin{tikzpicture}" << endl;
				cout << "		\\draw[thick, -latex] (0, 0) -- (10, 0); " << endl
					<< "        \\coordinate[label=above:$A$] (A) at (" << x7[0] << ",0);" << endl
					<< "        \\draw[fill=black] (A) circle (1.5pt);" << endl
					<< "        \\coordinate[label=above:$B$] (B) at (" << x7[1] << ",0);" << endl
					<< "        \\draw[fill=black] (B) circle (1.5pt);" << endl
					<< "        \\coordinate[label=above:$C$] (C) at (" << x7[2] << ",0);" << endl
					<< "        \\draw[fill=black] (C) circle (1.5pt);" << endl
					<< "        \\coordinate[label=above:$D$] (D) at (" << x7[3] << ",0);" << endl
					<< "        \\draw[fill=black] (D) circle (1.5pt);" << endl;


				cout << "	\\end{tikzpicture}" << endl << "\\end{center}" << endl;
				cout << "Какой точке соответствует число " << a7[aanswer] << "?" << endl;
				cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << "Ответ: " << answer << endl;
				Answer = "  \\item " + FormatDouble(answer) + " \n";

				break;
			}
            return Answer;
}

string SignUr(int pos, double number)
{
    string sgn;
    if ((number > 0) && (pos == 1))
        sgn = "";
    if ((number > 0) && (pos == 2))
        sgn = "+";
    if (number < 0)
        sgn = "-";
    return sgn;
}

string LineUravn(int number, int AllType)
{
            int type;
            double x;
            double a[4];
            int check = 0;
            double answer;
            double ost;
            string Answer;
            if(AllType == 0)
                type = rand()%2+1;
            else
                type = AllType;
            switch(type)
            {
                case 1:
                    do{
                        for(int i=0; i<3; i++)
                            a[i] = pow(-1,rand())*(rand() % 30 + 2);
                        answer = (a[2]-a[0]*a[1])/a[0];
                        ost = 100*answer - static_cast<int>(100*answer);
                        check = 1;
                        if(a[0]==0)
                            check = 0;
                        if(ost!=0)
                        check = 0;
                    }while(check!=1);

                    cout << "\\item Найдите корень уравнения: $$" << SignUr(1, a[0]) << fabs(a[0]) << "(x " << SignUr(2, a[1]) << fabs(a[1]) << ")=" << SignUr(1, a[2]) << fabs(a[2]) << "$$" << endl;
                    //cout << "\\\\ Ответ:" << answer << endl;
                    Answer = "  \\item " + FormatDouble(answer) + " \n";
                    break;

                case 2:
                    do{
                        for(int i=0; i<4; i++)
                            a[i] = pow(-1,rand())*(rand() % 30 + 2);
                        answer = (a[3]-a[0])/(a[1]-a[2]);
                        ost = 100*answer - static_cast<int>(100*answer);
                        check = 1;
                        if((a[1]-a[2])==0)
                            check = 0;
                        if(ost!=0)
                        check = 0;
                    }while(check!=1);

                    cout << "\\item Найдите корень уравнения: $$" << SignUr(1,a[0]) << fabs(a[0]) << SignUr(2, a[1]) << fabs(a[1]) << "x = " << SignUr(1,a[2]) << fabs(a[2]) << "x" << SignUr(2, a[3]) << fabs(a[3]) << "$$" << endl;
                    //cout << "\\\\ Ответ:" << answer << endl;
                    Answer = "  \\item " + FormatDouble(answer) + " \n";
                    break;

            }
            return Answer;
}

string KvadrUravn(int number, int AllType)
{
            int type;
            int type1;
            double x[2];
            double a[3];
            int check = 0;
            double answer;
            double ost;
            double change;
            string Answer;
            if(AllType == 0)
                type = rand()%3 + 1;
            else
                type = AllType;
            switch(type)
            {
                case 1:
                    do{
                            a[0] = pow(-1,rand())*(rand()%50+3);
                            a[1] = pow(-1,rand())*(rand()%999+3);
                        check = 1;
                        if((a[0]!=0) && ((-1)*(a[1]/a[0])>0))
                        {
                            x[0] = sqrt(-1*(a[1]/a[0]));
                            x[1] = -1 * sqrt((-1)*(a[1]/a[0]));
                            if((10*x[0] - static_cast<int>(10*x[0]))>0)
                                check = 0;
                            if((10*x[1] - static_cast<int>(10*x[1]))>0)
                                check = 0;
                        }
                        else
                        {
                            check = 0;
                        }
                    }while(check!=1);
                    type1 = rand()%2;
                    answer = x[type1];
                    cout << "\\item Решите уравнение: $$" << SignUr(1, a[0]) << fabs(a[0]) << "x^2 " << SignUr(2, a[1]) << fabs(a[1]) << " = 0$$" << endl;
                    if(type1 == 0)
                        cout << "Если уравнение имеет более одного корня, в ответ запишите больший из корней." << endl;
                    else
                        cout << "Если уравнение имеет более одного корня, в ответ запишите меньший из корней." << endl;
                    //cout << "\\\\Ответ: " << answer << endl;
                    Answer = "  \\item " + FormatDouble(answer) + " \n";
                    break;

                case 2:
                    do{
                            for(int i=0;i<2;i++)
                                a[i]=pow(-1,rand())*(rand()%200 + 2);
                            x[0] = 0;
                            x[1] = a[1]/a[0];
                            check = 1;
                            if((fabs(100*x[1])-fabs(static_cast<int>(100*x[1])))>0)
                                check = 0;
                    }while(check!=1);
                    if(x[0]>x[1])
                    {
                        change = x[0];
                        x[0] = x[1];
                        x[1] = change;
                    }
                    type1 = rand()%2;
                    answer = x[type1];
                    cout << "\\item Решите уравнение: $$" << SignUr(1, a[0]) << fabs(a[0]) << "x^2 = " << SignUr(1, a[1]) << fabs(a[1]) << "x$$" << endl;
                    if(type1 == 0)
                        cout << "Если уравнение имеет более одного корня, в ответ запишите меньший из корней." << endl;
                    else
                        cout << "Если уравнение имеет более одного корня, в ответ запишите больший из корней." << endl;
                    //cout << "\\\\Ответ: " << answer << endl;
                    Answer = "  \\item " + FormatDouble(answer) + " \n";
                    break;

                case 3:
                    do{
                        for(int i=0; i<3; i++)
                            a[i] = pow(-1,rand())*(rand()%40+2);
                        check = 1;
                        double D;
                        if(a[0] != 0)
                        {
                            D = pow(a[1],2) - 4 * a[0] * a[2];
                            if(D>=0)
                            {
                                x[0] = (-1*a[1]-sqrt(D))/(2*a[0]);
                                x[1] = (-1*a[1]+sqrt(D))/(2*a[0]);
                                if((fabs(100*x[0])-fabs(static_cast<int>(100*x[0])))>0)
                                    check = 0;
                                if((fabs(100*x[1])-fabs(static_cast<int>(100*x[1])))>0)
                                    check = 0;
                            }
                            else
                                check = 0;
                        }
                        else
                            check = 0;
                    }while(check!=1);
                    if(x[0]>x[1])
                    {
                        change = x[0];
                        x[0] = x[1];
                        x[1] = change;
                    }
                    type1 = rand()%2;
                    answer = x[type1];
                    cout << "\\item Решите уравнение: $$" << SignUr(1,a[0]) << fabs(a[0]) << "x^2" << SignUr(2,a[1]) << fabs(a[1]) << "x" << SignUr(2,a[2]) << fabs(a[2]) << "=0$$" << endl;
                    if(type1 == 0)
                        cout << "Если уравнение имеет более одного корня, в ответ запишите меньший из корней." << endl;
                    else
                        cout << "Если уравнение имеет более одного корня, в ответ запишите больший из корней." << endl;
                    //cout << "\\\\Ответ: " << answer << endl;
                    Answer = "  \\item " + FormatDouble(answer) + " \n";
                    break;

            }
        return Answer;
}

string LineNerav(int number, int AllType)
{
            double x[2];
            double a[4];
            int type;
            int check = 0;
            int answer;
            double ost;
            string Answer;
            FarStringTF TrueFalse[4];
            string Out[4];
            if(AllType == 0)
                type = rand()%4+1;
            else
                type = AllType;
            switch (type)
            {
            case 1:             // >
                do {
                    for (int i = 0; i < 4; i++)
                        a[i] = pow(-1, rand()) * (rand() % 30 + 2);
                    check = 1;
                    if (((a[1] - a[2]) != 0) && ((a[3] - a[0]) != 0))
                    {
                        x[0] = (a[3] - a[0]) / (a[1] - a[2]);
                        x[1] = pow(-1,rand())*(rand()%15 + 1);
                        if ((x[0] - static_cast<int>(x[0])) != 0)
                            check = 0;
                    }
                    else
                    {
                        check = 0;
                    }
                } while (check != 1);
                TrueFalse[0].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[0])) + ")$";
                TrueFalse[1].STRING = "$(" + to_string(static_cast<int>(x[0])) + ";+\\infty)$";
                TrueFalse[2].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[1])) + ")$";
                TrueFalse[3].STRING = "$(" + to_string(static_cast<int>(x[1])) + ";+\\infty)$";

                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                if ((a[0] + a[1] * (x[0] - 1)) > (a[2] * (x[0] - 1) + a[3]))
                {
                    TrueFalse[0].TF = 1;
                    TrueFalse[0].used = 1;
                }
                else
                {
                    TrueFalse[1].TF = 1;
                    TrueFalse[1].used = 1;
                }

                answer = rand() % 4 + 1;
                
                for (int i = 0; i < 4; i++)
                {
                    int done = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            int Var = rand() % 4;
                            if ((TrueFalse[Var].used) == 0)
                            {
                                Out[i] = TrueFalse[Var].STRING;
                                TrueFalse[Var].used = 1;
                                done = 1;
                            }
                        } while (done != 1);
                    }
                }
                cout << "\\item Укажите решение неравенства $" << SignUr(1,a[0]) << fabs(a[0]) << SignUr(2, a[1]) << fabs(a[1]) << "x >" << SignUr(1, a[2]) << fabs(a[2]) << "x" << SignUr(2, a[3]) << fabs(a[3]) << "$." << "\\\\";
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:         // >=
                do {
                    for (int i = 0; i < 4; i++)
                        a[i] = pow(-1, rand()) * (rand() % 30 + 2);
                    check = 1;
                    if (((a[1] - a[2]) != 0) && ((a[3] - a[0]) != 0))
                    {
                        x[0] = (a[3] - a[0]) / (a[1] - a[2]);
                        x[1] = pow(-1, rand()) * (rand() % 15 + 1);
                        if ((x[0] - static_cast<int>(x[0])) != 0)
                            check = 0;
                    }
                    else
                    {
                        check = 0;
                    }
                } while (check != 1);
                TrueFalse[0].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[0])) + "]$";
                TrueFalse[1].STRING = "$[" + to_string(static_cast<int>(x[0])) + ";+\\infty)$";
                TrueFalse[2].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[1])) + "]$";
                TrueFalse[3].STRING = "$[" + to_string(static_cast<int>(x[1])) + ";+\\infty)$";

                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                if ((a[0] + a[1] * (x[0] - 1)) > (a[2] * (x[0] - 1) + a[3]))
                {
                    TrueFalse[0].TF = 1;
                    TrueFalse[0].used = 1;
                }
                else
                {
                    TrueFalse[1].TF = 1;
                    TrueFalse[1].used = 1;
                }

                answer = rand() % 4 + 1;

                for (int i = 0; i < 4; i++)
                {
                    int done = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            int Var = rand() % 4;
                            if ((TrueFalse[Var].used) == 0)
                            {
                                Out[i] = TrueFalse[Var].STRING;
                                TrueFalse[Var].used = 1;
                                done = 1;
                            }
                        } while (done != 1);
                    }
                }
                cout << "\\item Укажите решение неравенства $" << SignUr(1, a[0]) << fabs(a[0]) << SignUr(2, a[1]) << fabs(a[1]) << "x \\geq" << SignUr(1, a[2]) << fabs(a[2]) << "x" << SignUr(2, a[3]) << fabs(a[3]) << "$." << "\\\\";
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:             // <
                do {
                    for (int i = 0; i < 4; i++)
                        a[i] = pow(-1, rand()) * (rand() % 30 + 2);
                    check = 1;
                    if (((a[1] - a[2]) != 0) && ((a[3] - a[0]) != 0))
                    {
                        x[0] = (a[3] - a[0]) / (a[1] - a[2]);
                        x[1] = pow(-1, rand()) * (rand() % 15 + 1);
                        if ((x[0] - static_cast<int>(x[0])) != 0)
                            check = 0;
                    }
                    else
                    {
                        check = 0;
                    }
                } while (check != 1);
                TrueFalse[0].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[0])) + ")$";
                TrueFalse[1].STRING = "$(" + to_string(static_cast<int>(x[0])) + ";+\\infty)$";
                TrueFalse[2].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[1])) + ")$";
                TrueFalse[3].STRING = "$(" + to_string(static_cast<int>(x[1])) + ";+\\infty)$";

                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                if ((a[0] + a[1] * (x[0] + 1)) < (a[2] * (x[0] + 1) + a[3]))
                {
                    TrueFalse[1].TF = 1;
                    TrueFalse[1].used = 1;
                }
                else
                {
                    TrueFalse[0].TF = 1;
                    TrueFalse[0].used = 1;
                }

                answer = rand() % 4 + 1;

                for (int i = 0; i < 4; i++)
                {
                    int done = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            int Var = rand() % 4;
                            if ((TrueFalse[Var].used) == 0)
                            {
                                Out[i] = TrueFalse[Var].STRING;
                                TrueFalse[Var].used = 1;
                                done = 1;
                            }
                        } while (done != 1);
                    }
                }
                cout << "\\item Укажите решение неравенства $" << SignUr(1, a[0]) << fabs(a[0]) << SignUr(2, a[1]) << fabs(a[1]) << "x <" << SignUr(1, a[2]) << fabs(a[2]) << "x" << SignUr(2, a[3]) << fabs(a[3]) << "$." << "\\\\";
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:         // =<
                do {
                    for (int i = 0; i < 4; i++)
                        a[i] = pow(-1, rand()) * (rand() % 30 + 2);
                    check = 1;
                    if (((a[1] - a[2]) != 0) && ((a[3] - a[0]) != 0))
                    {
                        x[0] = (a[3] - a[0]) / (a[1] - a[2]);
                        x[1] = pow(-1, rand()) * (rand() % 15 + 1);
                        if ((x[0] - static_cast<int>(x[0])) != 0)
                            check = 0;
                    }
                    else
                    {
                        check = 0;
                    }
                } while (check != 1);
                TrueFalse[0].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[0])) + "]$";
                TrueFalse[1].STRING = "$[" + to_string(static_cast<int>(x[0])) + ";+\\infty)$";
                TrueFalse[2].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[1])) + "]$";
                TrueFalse[3].STRING = "$[" + to_string(static_cast<int>(x[1])) + ";+\\infty)$";

                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                if ((a[0] + a[1] * (x[0] + 1)) < (a[2] * (x[0] + 1) + a[3]))
                {
                    TrueFalse[1].TF = 1;
                    TrueFalse[1].used = 1;
                }
                else
                {
                    TrueFalse[0].TF = 1;
                    TrueFalse[0].used = 1;
                }

                answer = rand() % 4 + 1;

                for (int i = 0; i < 4; i++)
                {
                    int done = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            int Var = rand() % 4;
                            if ((TrueFalse[Var].used) == 0)
                            {
                                Out[i] = TrueFalse[Var].STRING;
                                TrueFalse[Var].used = 1;
                                done = 1;
                            }
                        } while (done != 1);
                    }
                }
                cout << "\\item Укажите решение неравенства $" << SignUr(1, a[0]) << fabs(a[0]) << SignUr(2, a[1]) << fabs(a[1]) << "x \\leq" << SignUr(1, a[2]) << fabs(a[2]) << "x" << SignUr(2, a[3]) << fabs(a[3]) << "$." << "\\\\";
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;
            }
            return Answer;
}

string KvadrNerav(int number, int AllType)
{
            double x1[2];
            double x2[2];
            double a1[2];
            double a2[2];
            int type;
            int type1;              
            int check = 0;
            int strog;              // Строгое или нестрогое неравенство
            int answer;
            int done, Var;
            double ost;
            double change;
            string Answer;
            FarStringTF TrueFalse[4];
            string Out[4];
            if(AllType == 0)
                type = rand()%4 + 1;
            else
                type = AllType;
            switch(type)
            {
            case 1:
                do{
                    for(int i=0;i<2;i++)
                        a1[i] = rand()%50 + 2;
                    x1[0] = 0;
                    x1[1] = -1*a1[0]/a1[1];
                    check = 1;
                    if(fabs((x1[1]-static_cast<int>(x1[1])))>0)
                        check = 0;
                    if(x1[1]==0)
                        check = 0;
                    if(a1[0]==a1[1])
                        check = 0;
                }while(check!=1);

                if (x1[0] > x1[1])
                {
                    change = x1[0];
                    x1[0] = x1[1];
                    x1[1] = change;
                }

                strog = rand()%2+1;                  // Строгое или нестрогое неравенство

                if (pow(-1, rand()) > 0)
                {
                    TrueFalse[0].STRING = "$(-\\infty;" + to_string(static_cast<int>(x1[0])) + ScobNer(strog, 2) + "$";
                    TrueFalse[1].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x1[1])) + ";+\\infty)$";
                    TrueFalse[2].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x1[0])) + ";" + to_string(static_cast<int>(x1[1])) + ScobNer(strog, 2) + "$";
                    TrueFalse[3].STRING = "$(-\\infty;" + to_string(static_cast<int>(x1[0])) + ScobNer(strog, 2) + "\\cup" + ScobNer(strog, 1) + to_string(static_cast<int>(x1[1])) + ";+\\infty)$";
                }
                else
                {
                    if (strog == 2)
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                    }
                    else
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n  \\end{tikzpicture}";
                    }
                }

                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                type1 = rand()%2+1;
                switch(type1)
                {
                    case 1:
                    if((10000*a1[0])+(a1[1]*100000000)>0)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    else
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    break;

                    case 2:
                    if((10000*a1[0])+(a1[1]*100000000)<0)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    else
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                }

                answer = rand() % 4 + 1;
                for (int i = 0; i < 4; i++)
                {
                    done = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            Var = rand() % 4;
                            if ((TrueFalse[Var].used) == 0)
                            {
                                Out[i] = TrueFalse[Var].STRING;
                                TrueFalse[Var].used = 1;
                                done = 1;
                            }
                        } while (done != 1);
                    }
                }
                cout << "\\item Укажите решение неравенства: $" << SignUr(1,a1[0]) << to_string(static_cast<int>(fabs(a1[0]))) << "x" << SignUr(2,a1[1]) << to_string(static_cast<int>(fabs(a1[1]))) << "x^2" << ZnakKvadrNer(strog, type1) << "0$." << endl;
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";

                break;


            case 2:
                    do{
                    a1[0] = pow(-1,rand())*(rand()%20+1);
                    a1[1] = pow(-1,rand())*(rand()%20+1);
                    check = 1;
                    if(a1[0]==a1[1])
                        check = 0;
                    }while(check !=1);

                    x1[0] = -1*a1[0];
                    x1[1] = -1*a1[1];

                    if (x1[0] > x1[1])
                {
                    change = x1[0];
                    x1[0] = x1[1];
                    x1[1] = change;
                }

                strog = rand()%2+1;                  // Строгое или нестрогое неравенство

                if (pow(-1, rand()) > 0)
                {
                    TrueFalse[0].STRING = "$(-\\infty;" + to_string(static_cast<int>(x1[0])) + ScobNer(strog, 2) + "$";
                    TrueFalse[1].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x1[1])) + ";+\\infty)$";
                    TrueFalse[2].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x1[0])) + ";" + to_string(static_cast<int>(x1[1])) + ScobNer(strog, 2) + "$";
                    TrueFalse[3].STRING = "$(-\\infty;" + to_string(static_cast<int>(x1[0])) + ScobNer(strog, 2) + "\\cup" + ScobNer(strog, 1) + to_string(static_cast<int>(x1[1])) + ";+\\infty)$";
                }
                else
                {
                    if (strog == 2)
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                    }
                    else
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n  \\end{tikzpicture}";
                    }
                }

                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                type1 = rand()%2+1;
                switch(type1)
                {
                    case 1:
                    if((10000+a1[0])*(10000+a1[1])>0)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    else
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    break;

                    case 2:
                    if((10000+a1[0])*(10000+a1[1])<0)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    else
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    break;
                }

                answer = rand() % 4 + 1;
                for (int i = 0; i < 4; i++)
                {
                    done = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            Var = rand() % 4;
                            if ((TrueFalse[Var].used) == 0)
                            {
                                Out[i] = TrueFalse[Var].STRING;
                                TrueFalse[Var].used = 1;
                                done = 1;
                            }
                        } while (done != 1);
                    }
                }

                cout << "\\item Укажите решение неравенства: $(x" << SignUr(2,a1[0]) << to_string(static_cast<int>(fabs(a1[0]))) << ")(x" << SignUr(2,a1[1]) << to_string(static_cast<int>(fabs(a1[1]))) << ")" << ZnakKvadrNer(strog, type1) << "0$." << endl;
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";

                break;

            case 3:
                do{
                    a1[0] = rand()%1000 + 1;
                    x1[0] = sqrt(a1[0]);
                    x1[1] = -1 * x1[0];
                    check = 1;
                    if((x1[0]-static_cast<int>(x1[0]))>0)
                        check = 0;
                }while(check != 1);

                if (x1[0] > x1[1])
                {
                    change = x1[0];
                    x1[0] = x1[1];
                    x1[1] = change;
                }

                strog = rand()%2+1;                  // Строгое или нестрогое неравенство

                if (pow(-1, rand()) > 0)
                {
                    TrueFalse[0].STRING = "$(-\\infty;" + to_string(static_cast<int>(x1[0])) + ScobNer(strog, 2) + "$";
                    TrueFalse[1].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x1[1])) + ";+\\infty)$";
                    TrueFalse[2].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x1[0])) + ";" + to_string(static_cast<int>(x1[1])) + ScobNer(strog, 2) + "$";
                    TrueFalse[3].STRING = "$(-\\infty;" + to_string(static_cast<int>(x1[0])) + ScobNer(strog, 2) + "\\cup" + ScobNer(strog, 1) + to_string(static_cast<int>(x1[1])) + ";+\\infty)$";
                }
                else
                {
                    if (strog == 2)
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                    }
                    else
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n  \\end{tikzpicture}";
                    }
                }


                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                type1 = rand()%2+1;
                switch(type1)
                {
                    case 1:
                    if((100000000 - a1[0])>0)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    else
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    break;

                    case 2:
                    if((100000000 - a1[0])<0)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    else
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    break;
                }

                answer = rand() % 4 + 1;
                for (int i = 0; i < 4; i++)
                {
                    done = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            Var = rand() % 4;
                            if ((TrueFalse[Var].used) == 0)
                            {
                                Out[i] = TrueFalse[Var].STRING;
                                TrueFalse[Var].used = 1;
                                done = 1;
                            }
                        } while (done != 1);
                    }
                }

                if(pow(-1,rand())>0)
                    cout << "\\item Укажите решение неравенства: $x^2-" << to_string(static_cast<int>(fabs(a1[0]))) << "" << ZnakKvadrNer(strog, type1) << "0$." << endl;
                else
                    cout << "\\item Укажите решение неравенства: $x^2" << ZnakKvadrNer(strog, type1) << "" << to_string(static_cast<int>(fabs(a1[0]))) << "$" <<  endl;
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";

                break;
            

            case 4:
                int type2 = rand()%2+1;
                if(type2 == 1)
                {
                    a1[0] = pow(-1,rand())*(rand()%10+2);
                    x1[0] = 0;
                    x1[1] = -1 * a1[0];
                    a2[0] = pow(a1[0],2);
                    x2[0] = a1[0];
                    x2[1] = -1 * a1[0];
                }
                else
                {
                    do{
                        a2[0] = rand()%100+2;
                        x2[0] = sqrt(a2[0]);
                        x2[1] = -1 * x2[0];
                        check = 1;
                        if((x2[0]-static_cast<int>(x2[0]))>0)
                            check = 0;
                    }while(check!=1);
                    a1[0] = pow(-1,rand())*x2[0];
                    x1[0] = 0;
                    x1[1] = -1 * a1[0];
                }
                
                if (x1[0] > x1[1])
                {
                    change = x1[0];
                    x1[0] = x1[1];
                    x1[1] = change;
                }

                if (x2[0] > x2[1])
                {
                    change = x2[0];
                    x2[0] = x2[1];
                    x2[1] = change;
                }

                strog = rand()%2+1;                  // Строгое или нестрогое неравенство

                    if (strog == 2)
                    {
                        TrueFalse[0].STRING = "\\begin{center} \n \\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture} \n \\end{center}";
                        TrueFalse[1].STRING = "\\begin{center} \n \\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n \\end{tikzpicture} \n \\end{center}";
                        TrueFalse[2].STRING = "\\begin{center} \n \\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x2[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x2[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture} \n \\end{center}";
                        TrueFalse[3].STRING = "\\begin{center} \n \\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x2[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x2[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n \\end{tikzpicture} \n \\end{center}";
                    }
                    else
                    {
                        TrueFalse[0].STRING = "\\begin{center} \n \\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture} \n \\end{center}";
                        TrueFalse[1].STRING = "\\begin{center} \n \\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x1[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n  \\end{tikzpicture} \n \\end{center}";
                        TrueFalse[2].STRING = "\\begin{center} \n \\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x2[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x2[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture} \n \\end{center}";
                        TrueFalse[3].STRING = "\\begin{center} \n \\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x2[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (1.5,0.2); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x2[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (3.5,0) rectangle (5,0.2); \n  \\end{tikzpicture} \n \\end{center}";
                    }
            

                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                type1 = rand()%2+1;

                if(type2 == 1)
                {
                    switch(type1)
                {
                    case 1:
                    if((100000000 + 10000 * a1[0])>0)
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    else
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    break;

                    case 2:
                    if((100000000 + 10000 * a1[0])<0)
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    else
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    break;
                }
                }
                else
                {
                    switch(type1)
                {
                    case 1:
                    if((100000000 - a2[0])>0)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    else
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    break;

                    case 2:
                    if((100000000 - a2[0])<0)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    else
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    break;
                }
                }

                int PravGraph;


                for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                PravGraph = m;
                            }
                        }
                cout << "\\item Укажите неравенство, решение которого изображено на рисунке:" << endl;
                cout << TrueFalse[PravGraph].STRING << endl;

                TrueFalse[0].STRING = "$x^2" + SignUr(2, a1[0]) + to_string(static_cast<int>(fabs(a1[0]))) + "x" + ZnakKvadrNer(strog, 1) + "0$ \n";
                TrueFalse[1].STRING = "$x^2" + SignUr(2, a1[0]) + to_string(static_cast<int>(fabs(a1[0]))) + "x" + ZnakKvadrNer(strog, 2) + "0$ \n";
                TrueFalse[2].STRING = "$x^2 - " + to_string(static_cast<int>(fabs(a2[0]))) + ZnakKvadrNer(strog, 1) + "0$ \n";
                TrueFalse[3].STRING = "$x^2 - " + to_string(static_cast<int>(fabs(a2[0]))) + ZnakKvadrNer(strog, 2) + "0$ \n";

                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                if((type2==1)&&(type1==1))
                {
                    TrueFalse[0].TF = 1;
                    TrueFalse[0].used = 1;
                }
                if((type2==1)&&(type1==2))
                {
                    TrueFalse[1].TF = 1;
                    TrueFalse[1].used = 1;
                }
                if((type2==2)&&(type1==1))
                {
                    TrueFalse[2].TF = 1;
                    TrueFalse[2].used = 1;
                }
                if((type2==2)&&(type1==2))
                {
                    TrueFalse[3].TF = 1;
                    TrueFalse[3].used = 1;
                }

                answer = rand() % 4 + 1;
                for (int i = 0; i < 4; i++)
                {
                    done = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            Var = rand() % 4;
                            if ((TrueFalse[Var].used) == 0)
                            {
                                Out[i] = TrueFalse[Var].STRING;
                                TrueFalse[Var].used = 1;
                                done = 1;
                            }
                        } while (done != 1);
                    }
                }

                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";

                break;


            }
            return Answer;
}

string SistNerav(int number, int AllType)
{
    double x[2];
            double a1[3];
            double a2[3];
            int type;
            int type1;              
            int check = 0;
            int strog;              // Строгое или нестрогое неравенство
            int answer;
            double ost;
            double change;
            string Answer;
            FarStringTF TrueFalse[4];
            string Out[4];
            if(AllType == 0)
                type = rand()%2+1;
            else
                type = AllType;
            switch (type)
            {
            case 1:
                a1[0] = pow(-1, rand()) * (rand() % 20 + 2);
                a1[1] = pow(-1, rand()) * (rand() % 20 + 2);
                x[0] = a1[1] - a1[0];

                a2[0] = pow(-1, rand()) * (rand() % 20 + 2);
                a2[1] = pow(-1, rand()) * (rand() % 20 + 2);
                x[1] = a2[1] - a2[0];

                if (x[0] > x[1])
                {
                    change = x[0];
                    x[0] = x[1];
                    x[1] = change;
                }

                strog = rand()%2+1;                  // Строгое или нестрогое неравенство
                if (pow(-1, rand()) > 0)
                {
                    TrueFalse[0].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[0])) + ScobNer(strog, 2) + "$";
                    TrueFalse[1].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x[1])) + ";+\\infty)$";
                    TrueFalse[2].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x[0])) + ";" + to_string(static_cast<int>(x[1])) + ScobNer(strog, 2) + "$";
                    TrueFalse[3].STRING = "Нет решения";
                }
                else
                {
                    if (strog == 2)
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\end{tikzpicture}";
                    }
                    else
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\end{tikzpicture}";
                    }
                }
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                type1 = rand()%4+1;
                switch (type1)
                {
                case 1:
                    if ((-10000 + a1[0] > a1[1]) && (-10000 + a2[0] > a2[1]))
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    if ((10000 + a1[0] > a1[1]) && (10000 + a2[0] > a2[1]))
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    if ((((x[0]+x[1]) / 2) + a1[0] > a1[1]) && (((x[0] + x[1]) / 2) + a2[0] > a2[1]))
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    break;

                case 2:
                    check = 0;
                    if ((-10000 + a1[0] > a1[1]) && (-10000 + a2[0] < a2[1]))
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    if ((10000 + a1[0] > a1[1]) && (10000 + a2[0] < a2[1]))
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    if ((((x[0] + x[1]) / 2) + a1[0] > a1[1]) && (((x[0] + x[1]) / 2) + a2[0] < a2[1]))
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        if (TrueFalse[i].TF == 0)
                        {
                            check++;
                        }
                    }
                    if (check == 4)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    break;

                case 3:
                    check = 0;
                    if ((-10000 + a1[0] < a1[1]) && (-10000 + a2[0] < a2[1]))
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    if ((10000 + a1[0] < a1[1]) && (10000 + a2[0] < a2[1]))
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    if ((((x[0] + x[1]) / 2) + a1[0] < a1[1]) && (((x[0] + x[1]) / 2) + a2[0] < a2[1]))
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        if (TrueFalse[i].TF == 0)
                        {
                            check++;
                        }
                    }
                    if (check == 4)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    break;

                case 4:
                    check = 0;
                    if ((-10000 + a1[0] < a1[1]) && (-10000 + a2[0] > a2[1]))
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    if ((10000 + a1[0] < a1[1]) && (10000 + a2[0] > a2[1]))
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    if ((((x[0] + x[1]) / 2) + a1[0] < a1[1]) && (((x[0] + x[1]) / 2) + a2[0] > a2[1]))
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        if (TrueFalse[i].TF == 0)
                        {
                            check++;
                        }
                    }
                    if (check == 4)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    break;

                }

                answer = rand() % 4 + 1;
                for (int i = 0; i < 4; i++)
                {
                    int done1 = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            int Var1 = rand() % 4;
                            if ((TrueFalse[Var1].used) == 0)
                            {
                                Out[i] = TrueFalse[Var1].STRING;
                                TrueFalse[Var1].used = 1;
                                done1 = 1;
                            }
                        } while (done1 != 1);
                    }
                }
                cout << "\\item Укажите решение системы неравенств:" << endl;
                cout << "$$" << endl
                    << "\\begin{cases}" << endl
                    << "    x" << SignUr(2, a1[0]) << to_string(static_cast<int>(fabs(a1[0]))) << ZnakNer(strog, type1, 1) << SignUr(1, a1[1]) << to_string(static_cast<int>(fabs(a1[1]))) << "\\\\" << endl
                    << "    x" << SignUr(2, a2[0]) << to_string(static_cast<int>(fabs(a2[0]))) << ZnakNer(strog, type1, 2) << SignUr(1, a2[1]) << to_string(static_cast<int>(fabs(a2[1]))) << endl
                    << "\\end{cases}" << endl
                    << "$$" << endl << endl;
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                check = 0;
                int check2 = 0;
                do {
                    do {
                        for (int i = 0; i < 3; i++)
                            a1[i] = pow(-1, rand()) * (rand() % 20 + 2);
                        check = 1;
                        x[0] = (a1[2] - a1[0]) / a1[1];
                        if ((fabs(x[0] - static_cast<int>(x[0]))) > 0)
                            check = 0;

                    } while (check != 1);
                    check = 0;

                    do {
                        for (int i = 0; i < 3; i++)
                            a2[i] = pow(-1, rand()) * (rand() % 20 + 2);
                        check = 1;
                        x[1] = (a2[2] - a2[0]) / a2[1];
                        if ((fabs(x[1] - static_cast<int>(x[1]))) > 0)
                            check = 0;

                    } while (check != 1);
                    check2 = 1;
                    if (x[0] == x[1])
                        check2 = 0;
                } while (check2 != 1);
                if (x[0] > x[1])
                {
                    change = x[0];
                    x[0] = x[1];
                    x[1] = change;
                }

                strog = rand() % 2 + 1;                  // Строгое или нестрогое неравенство
                if (pow(-1, rand()) > 0)
                {
                    TrueFalse[0].STRING = "$(-\\infty;" + to_string(static_cast<int>(x[0])) + ScobNer(strog, 2) + "$";
                    TrueFalse[1].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x[1])) + ";+\\infty)$";
                    TrueFalse[2].STRING = "$" + ScobNer(strog, 1) + to_string(static_cast<int>(x[0])) + ";" + to_string(static_cast<int>(x[1])) + ScobNer(strog, 2) + "$";
                    TrueFalse[3].STRING = "Нет решения";
                }
                else
                {
                    if (strog == 2)
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\end{tikzpicture}";
                    }
                    else
                    {
                        TrueFalse[0].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[0])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (0,0) rectangle (2.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[1].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[1])) + "$] (x1) at (2.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\fill[pattern=north east lines] (2.5,0) rectangle (5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[2].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[0])) + "$] (x1) at (1.5,0); \n \\draw[fill=black] (x1) circle(1.5pt); \n \\draw[fill=white] (x1) circle(1pt); \n \\coordinate[label=below:$" + to_string(static_cast<int>(x[1])) + "$] (x2) at (3.5,0); \n \\draw[fill=black] (x2) circle(1.5pt); \n \\draw[fill=white] (x2) circle(1pt); \n \\fill[pattern=north east lines] (1.5,0) rectangle (3.5,0.2); \n \\end{tikzpicture}";
                        TrueFalse[3].STRING = "\\begin{tikzpicture} \n \\draw[thick, -latex] (0,0) -- (5,0); \n \\end{tikzpicture}";
                    }
                }
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].used = 0;
                for (int i = 0; i < 4; i++)
                    TrueFalse[i].TF = 0;

                type1 = rand() % 4 + 1;
                switch (type1)
                {
                case 1:
                    check = 0;
                    if ((a1[0] + a1[1]*(-10000) > a1[2]) && (a2[0] + a2[1] * (-10000) > a2[2]))
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    if ((a1[0] + a1[1] * (10000) > a1[2]) && (a2[0] + a2[1] * (10000) > a2[2]))
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    if ((a1[0] + a1[1] * ((x[0] + x[1]) / 2) > a1[2]) && (a2[0] + a2[1] * ((x[0] + x[1]) / 2) > a2[2]))
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        if (TrueFalse[i].TF == 0)
                        {
                            check++;
                        }
                    }
                    if (check == 4)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    break;

                case 2:
                    check = 0;
                    if ((a1[0] + a1[1] * (-10000) > a1[2]) && (a2[0] + a2[1] * (-10000) < a2[2]))
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    if ((a1[0] + a1[1] * (10000) > a1[2]) && (a2[0] + a2[1] * (10000) < a2[2]))
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    if ((a1[0] + a1[1] * ((x[0] + x[1]) / 2) > a1[2]) && (a2[0] + a2[1] * ((x[0] + x[1]) / 2) < a2[2]))
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        if (TrueFalse[i].TF == 0)
                        {
                            check++;
                        }
                    }
                    if (check == 4)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    break;

                case 3:
                    check = 0;
                    if ((a1[0] + a1[1] * (-10000) < a1[2]) && (a2[0] + a2[1] * (-10000) < a2[2]))
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    if ((a1[0] + a1[1] * (10000) < a1[2]) && (a2[0] + a2[1] * (10000) < a2[2]))
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    if ((a1[0] + a1[1] * ((x[0] + x[1]) / 2) < a1[2]) && (a2[0] + a2[1] * ((x[0] + x[1]) / 2) < a2[2]))
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        if (TrueFalse[i].TF == 0)
                        {
                            check++;
                        }
                    }
                    if (check == 4)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    break;

                case 4:
                    check = 0;
                    if ((a1[0] + a1[1] * (-10000) < a1[2]) && (a2[0] + a2[1] * (-10000) > a2[2]))
                    {
                        TrueFalse[0].TF = 1;
                        TrueFalse[0].used = 1;
                    }
                    if ((a1[0] + a1[1] * (10000) < a1[2]) && (a2[0] + a2[1] * (10000) > a2[2]))
                    {
                        TrueFalse[1].TF = 1;
                        TrueFalse[1].used = 1;
                    }
                    if ((a1[0] + a1[1] * ((x[0] + x[1]) / 2) < a1[2]) && (a2[0] + a2[1] * ((x[0] + x[1]) / 2) > a2[2]))
                    {
                        TrueFalse[2].TF = 1;
                        TrueFalse[2].used = 1;
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        if (TrueFalse[i].TF == 0)
                        {
                            check++;
                        }
                    }
                    if (check == 4)
                    {
                        TrueFalse[3].TF = 1;
                        TrueFalse[3].used = 1;
                    }
                    break;

                }

                answer = rand() % 4 + 1;
                for (int i = 0; i < 4; i++)
                {
                    int done2 = 0;
                    if (i == (answer - 1))
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (TrueFalse[m].TF == 1)
                            {
                                Out[i] = TrueFalse[m].STRING;
                            }
                        }
                    }
                    else
                    {
                        do {
                            int Var2 = rand() % 4;
                            if ((TrueFalse[Var2].used) == 0)
                            {
                                Out[i] = TrueFalse[Var2].STRING;
                                TrueFalse[Var2].used = 1;
                                done2 = 1;
                            }
                        } while (done2 != 1);
                    }
                }
                cout << "\\item Укажите решение системы неравенств:" << endl;
                cout << "$$" << endl
                    << "\\begin{cases}" << endl
                    << "    " << SignUr(1,a1[0]) << to_string(static_cast<int>(fabs(a1[0]))) << SignUr(2,a1[1]) << to_string(static_cast<int>(fabs(a1[1]))) << "x" << ZnakNer(strog, type1, 1) << SignUr(1, a1[2]) << to_string(static_cast<int>(fabs(a1[2]))) << "\\\\" << endl
                    << "    " << SignUr(1, a2[0]) << to_string(static_cast<int>(fabs(a2[0]))) << SignUr(2, a2[1]) << to_string(static_cast<int>(fabs(a2[1]))) << "x" << ZnakNer(strog, type1, 2) << SignUr(1, a2[2]) << to_string(static_cast<int>(fabs(a2[2]))) << endl
                    << "\\end{cases}" << endl
                    << "$$" << endl << endl;
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            }
            return Answer;
}

string RaschetForm(int number, int AllType)
{
    double P, I, R, tc, tf, n, Price1, Price2, a, w, sin1, sin2, S, d, t1, t2;
            int type;
            string Answer;
            int check = 0;
            double answer;
            if(AllType == 0)
                type = rand()%7+1;
            else
                type = AllType;
            switch (type)
            {
            case 1:
                do {
                    P = rand() % 300 + 60;
                    I = rand() % 30 + 6;
                    answer = P / pow(I, 2);
                    check = 1;
                    if (answer - static_cast<int>(answer) != 0)
                        check = 0;
                } while (check != 1);
                cout << "\\item Мощность постоянного тока (в ваттах) вычисляется по формуле $P=I^2R$, где $I$ -- сила тока (в амперах), $R$ -- сопротивление (в омах). " << endl
                   << "Пользуясь этой формулой, найдите сопротивление $R$, если мощность составляет " << P << " Вт, а сила тока равна " << I << "А. Ответ дайте в омах." << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                do {
                    tf = rand() % 100 + 10;
                    answer = (tf - 32) * 5 / 9;
                    check = 1;
                    if (answer - static_cast<int>(answer) != 0)
                        check = 0;
                } while (check != 1);
                cout << "\\item Перевести значение температуры по шкале Фаренгейта в шкалу Цельсия позволяет формула $t_C=\\frac{5}{9}(t_F-32)$, где $t_C$ -- температура в градусах Цельсия, $t_F$ -- температура в градусах Фаренгейта. Скольким градусам по шкале Цельсия соответствует " << tf << " градусов по шкале Фаренгейта?" << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                n = rand() % 30 + 9;
                Price1 = 1000 * (rand() % 8 + 2);
                Price2 = 100 * (rand() % 40 + 10);
                answer = Price1 + (Price2 * n);
                cout << "\\item В фирме <<Родник>> стоимость (в рублях) колодца из железобетонных колец рассчитывается по формуле $C=" << Price1 << "+" << Price2 << "n$, где $n$ -- число колец, установленных в колодце. Пользуясь этой формулой, рассчитайте стоимость колодца из " << n << " колец. Ответ дайте в рублях." << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:
                do {
                    tc = pow(-1,rand())*(rand() % 50 + 10);
                    answer = 1.8 * tc + 32;
                    check = 1;
                    if (answer - static_cast<int>(answer) != 0)
                        check = 0;
                } while (check != 1);
                cout << "\\item Чтобы перевести значение температуры по шкале Цельсия в шкалу Фаренгейта, пользуются формулой $t_F=1,8t_C+32$, " << endl
                    << "где $t_C$ -- температура в градусах Цельсия, $t_F$ -- температура в градусах Фаренгейта. Скольким градусам по шкале Фаренгейта соответствует " << tc << "градусов по шкале Цельсия?" << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 5:
                do {
                    a = rand() % 500 + 40;
                    w = rand() % 25 + 2;
                    answer = a / pow(w, 2);
                    check = 1;
                    if (answer - static_cast<int>(answer) != 0)
                        check = 0;
                } while (check != 1);
                cout << "\\item Центростремительное ускорение при движении по окружности $\\left(\\text{в }\\frac{\\text{м}}{\\text{с}^2}\\right)$ " << endl
                    << "вычисляется по формуле $a=\\omega^2R$, где $\\omega$ -- угловая скорость $\\left(\\text{в }\\text{с}^{-1}\\right)$, $R$ -- радиус окружности (в метрах)." << endl
                    << " Пользуясь этой формулой, найдите радиус $R$, если угловая скорость равна $" << w << "\\text{ с}^ {-1}$, а центростремительное ускорение равно $" << a << "\\frac{\\text{м}}{\\text{с} ^ 2}$.Ответ дайте в метрах." << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 6:
                do {
                    S = rand() % 50 + 4;
                    d = rand()%15 + 3;
                    sin1 = rand() % 6 + 1;
                    sin2 = rand() % 9 + 3;
                    answer = (S * 2 * sin2) / (d * sin1);
                    check = 1;
                    if (sin1 >= sin2)
                        check = 0;
                    if (answer - static_cast<int>(answer) != 0)
                        check = 0;
                } while (check != 1);
                cout << "\\item Площадь четырехугольника можно вычислить по формуле $S=\\frac{d_1d_2\\sin(\\alpha)}{2}$, где $d_1$ и $d_2$ -- длины диагоналей четырехугольника, $\\alpha$." << endl
                    << " Пользуясь этой формулой, найдите длину диагонали $d_2$, если $d_1=" << d << "$, $\\sin(\\alpha)=\\frac{" << sin1 << "}{" << sin2 << "}$, а $S=" << S << "$." << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 7:
                do {
                    t1 = rand() % 5 + 5;
                    t2 = rand() % 13 + 4;
                    Price1 = rand() % 200 + 40;
                    Price2 = rand() % 15 + 5;
                    answer = Price1 + Price2 * (t2 - t1);
                    check = 1;
                    if (t1 > t2)
                        check = 0;
                } while (check != 1);
                cout << "\\item В фирме <<Эх, прокачу!>> стоимость поездки на такси (в рублях) длительностью более " << t1 << " минут рассчитывается по формуле $C=" << Price1 << "+" << Price2 << "(t-" << t1 << ")$, где $t$ -- длительность поездки (в минутах). " << endl
                    << "Пользуясь этой формулой, рассчитайте стоимость " << t2 << "-минутной поездки. Ответ дайте в рублях." << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;
            }
            return Answer;    
}

string Graphic(int AllType)
{
    // Код начало
            double k[4];
            double b[4];
            double a[4];
            double c[4];
            double xver[4];
            double yver[4];
            int type;
            if(AllType == 0)
                type = rand()%4+1;
            else
                type = AllType;
            int answer[3];
            int Var;
            Graph GraphVar[4];
            string Answer;
            int check = 0;
            switch (type)
            {
            case 1:
                do{
                    k[0] = rand()%5 + 1;
                    b[0] = rand()%10 + 1;

                    k[1] = -1*(rand()%5 + 1);
                    b[1] = rand()%10 + 1;

                    k[2] = -1*(rand()%5 + 1);
                    b[2] = -1*(rand()%10 + 1);

                    k[3] = rand()%5 + 1;
                    b[3] = -1*(rand()%10 + 1);
                    check = 1;

                    if((b[0]<-3.5)||(b[0]>3.5)||((-1*b[0]/k[0])>3.5)||((-1*b[0]/k[0])<-3.5))
                        check = 0;

                    if((b[1]<-3.5)||(b[1]>3.5)||((-1*b[1]/k[1])>3.5)||((-1*b[1]/k[1])<-3.5))
                        check = 0;

                    if((b[2]<-3.5)||(b[2]>3.5)||((-1*b[2]/k[2])>3.5)||((-1*b[2]/k[2])<-3.5))
                        check = 0;

                    if((b[3]<-3.5)||(b[3]>3.5)||((-1*b[3]/k[3])>3.5)||((-1*b[3]/k[3])<-3.5))
                        check = 0;
                }while(check != 1);
                for(int i=0; i<4; i++)
                {
                    GraphVar[i].PorO = 0;
                    GraphVar[i].PorQ = 0;
                    GraphVar[i].TF = 0;
                    GraphVar[i].used = 0;
                    GraphVar[i].GraphOut = "";
                    if((k[i]==1)||(k[i]==-1))
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, k[i]) + "1*x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "}\n";
                    else
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, k[i]) + to_string(static_cast<int>(fabs(k[i]))) + "* x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "}\n";
                }
                GraphVar[0].VarAnswer = "$k>0$, $b>0$";
                GraphVar[1].VarAnswer = "$k<0$, $b>0$";
                GraphVar[2].VarAnswer = "$k<0$, $b<0$";
                GraphVar[3].VarAnswer = "$k>0$, $b<0$";

                for(int i=0; i<3; i++)
                    answer[i] = 0;

                for(int i=0; i<3; i++)
                {
                    do{
                        check = 0;
                        Var = rand()%3 +1;
                        if((answer[0]!=Var)&&(answer[1]!=Var)&&(answer[2]!=Var))
                        {
                            answer[i] = Var;
                            check = 1;
                        }    
                    }while(check!=1);
                }
                for(int i=0; i<3; i++)
                {
                    check = 0;
                    do{
                            Var = rand()%4;
                            if(GraphVar[Var].used==0)
                            {
                                GraphVar[Var].PorQ = i+1;
                                for(int m=0; m<3; m++)
                                {
                                    if((i+1)==answer[m])
                                    {
                                        GraphVar[Var].PorO = m + 1;
                                    }
                                }
                                GraphVar[Var].used = 1;
                                check = 1;
                            }
                    }while(check!=1);
                }
                cout << "\\item На рисунках изображены графики функций вида $y=kx+b$. Установите соответствие между знаками коэффициентов $k$ и $b$ и графиками функций." << endl << endl;
                cout << "\\vspace{1em}" << endl << endl 
                    << "\\noindent" << endl;
                    for(int i = 1; i<=3; i++)
                    {
                        cout << "\\begin{minipage}[t]{0.3\\textwidth}" << endl 
                             << "\\centering" << endl;
                        for(int m = 0; m<4; m++)
                        {
                            if(GraphVar[m].PorQ == i)
                            {
                                cout << GraphVar[m].GraphOut;
                            }
                        }
                        cout << "График " << i << endl << "\\end{minipage} " << endl;
                        if(i != 3)
                            cout << "\\hfill" << endl;
                    }
                cout << endl << "\\vspace{1.5em}" << endl;
                cout << "\\textbf{Варианты ответа:}" << endl;
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl;
                for(int i = 1; i<=3; i++)
                {
                    for(int m=0; m<4; m++)
                    {
                        if(GraphVar[m].PorO==i)
                            cout << "\\item     " << GraphVar[m].VarAnswer << endl;
                    }
                }
                cout << "\\end{enumerate}" << endl << endl << endl;

                Answer = "  \\item ";
                for(int i = 1; i <= 3; i++)
                {
                    for(int m = 0; m<4; m++)
                    {
                        if(GraphVar[m].PorQ == i)
                            Answer = Answer + to_string(static_cast<int>(GraphVar[m].PorO));
                    }
                }
                Answer = Answer + " \n";

                //cout << Answer << endl;
                break;

            case 2:
                do{
                    k[0] = rand()%2 + 1;
                    b[0] = rand()%10 + 1;

                    k[1] = -1*(rand()%2 + 1);
                    b[1] = rand()%10 + 1;

                    k[2] = -1*(rand()%2 + 1);
                    b[2] = -1*(rand()%10 + 1);

                    k[3] = rand()%2 + 1;
                    b[3] = -1*(rand()%10 + 1);
                    check = 1;

                    if((b[0]<-3.5)||(b[0]>3.5)||((-1*b[0]/k[0])>3.5)||((-1*b[0]/k[0])<-3.5))
                        check = 0;

                    if((b[1]<-3.5)||(b[1]>3.5)||((-1*b[1]/k[1])>3.5)||((-1*b[1]/k[1])<-3.5))
                        check = 0;

                    if((b[2]<-3.5)||(b[2]>3.5)||((-1*b[2]/k[2])>3.5)||((-1*b[2]/k[2])<-3.5))
                        check = 0;

                    if((b[3]<-3.5)||(b[3]>3.5)||((-1*b[3]/k[3])>3.5)||((-1*b[3]/k[3])<-3.5))
                        check = 0;
                }while(check != 1);
                if(pow(-1,rand())>0)
                {
                    k[3] = 0;
                    b[3] = pow(-1,rand())*(rand()%3+1);
                }
                for(int i=0; i<4; i++)
                {
                    GraphVar[i].PorO = 0;
                    GraphVar[i].PorQ = 0;
                    GraphVar[i].TF = 0;
                    GraphVar[i].used = 0;
                    GraphVar[i].GraphOut = "";
                    if((k[i]==1)||(k[i]==-1))
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, k[i]) + "1*x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "}\n";
                    else
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, k[i]) + to_string(static_cast<int>(fabs(k[i]))) + "* x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "}\n";
                }

                if((k[0]==1)||(k[0]==-1))
                    GraphVar[0].VarAnswer = "$y=" + SignUr(1, k[0]) + "x" + SignUr(2, b[0]) + to_string(static_cast<int>(fabs(b[0]))) + "$";
                else
                    GraphVar[0].VarAnswer = "$y=" + SignUr(1, k[0]) + to_string(static_cast<int>(fabs(k[0]))) + "x" + SignUr(2, b[0]) + to_string(static_cast<int>(fabs(b[0]))) + "$";

                if((k[1]==1)||(k[1]==-1))
                    GraphVar[1].VarAnswer = "$y=" + SignUr(1, k[1]) + "x" + SignUr(2, b[1]) + to_string(static_cast<int>(fabs(b[1]))) + "$";
                else
                    GraphVar[1].VarAnswer = "$y=" + SignUr(1, k[1]) + to_string(static_cast<int>(fabs(k[1]))) + "x" + SignUr(2, b[1]) + to_string(static_cast<int>(fabs(b[1]))) + "$";

                if((k[2]==1)||(k[2]==-1))
                    GraphVar[2].VarAnswer = "$y=" + SignUr(1, k[2]) + "x" + SignUr(2, b[2]) + to_string(static_cast<int>(fabs(b[2]))) + "$";
                else
                    GraphVar[2].VarAnswer = "$y=" + SignUr(1, k[2]) + to_string(static_cast<int>(fabs(k[2]))) + "x" + SignUr(2, b[2]) + to_string(static_cast<int>(fabs(b[2]))) + "$";

                if((k[3]==1)||(k[3]==-1))
                    GraphVar[3].VarAnswer = "$y=" + SignUr(1, k[3]) + "x" + SignUr(2, b[3]) + to_string(static_cast<int>(fabs(b[3]))) + "$";
                else
                    GraphVar[3].VarAnswer = "$y=" + SignUr(1, k[3]) + to_string(static_cast<int>(fabs(k[3]))) + "x" + SignUr(2, b[3]) + to_string(static_cast<int>(fabs(b[3]))) + "$";
                if(k[3]==0)
                    GraphVar[3].VarAnswer = "$y=" + SignUr(2, b[3]) + to_string(static_cast<int>(fabs(b[3]))) + "$";
                for(int i=0; i<3; i++)
                    answer[i] = 0;

                for(int i=0; i<3; i++)
                {
                    do{
                        check = 0;
                        Var = rand()%3 +1;
                        if((answer[0]!=Var)&&(answer[1]!=Var)&&(answer[2]!=Var))
                        {
                            answer[i] = Var;
                            check = 1;
                        }    
                    }while(check!=1);
                }
                for(int i=0; i<3; i++)
                {
                    check = 0;
                    do{
                            Var = rand()%4;
                            if(GraphVar[Var].used==0)
                            {
                                GraphVar[Var].PorQ = i+1;
                                for(int m=0; m<3; m++)
                                {
                                    if((i+1)==answer[m])
                                    {
                                        GraphVar[Var].PorO = m + 1;
                                    }
                                }
                                GraphVar[Var].used = 1;
                                check = 1;
                            }
                    }while(check!=1);
                }
                cout << "\\item Установите соответствие между графиками функций и формулами, которые их задают." << endl;
                cout << "\\vspace{1em}" << endl << endl 
                    << "\\noindent" << endl;
                    for(int i = 1; i<=3; i++)
                    {
                        cout << "\\begin{minipage}[t]{0.3\\textwidth}" << endl 
                             << "\\centering" << endl;
                        for(int m = 0; m<4; m++)
                        {
                            if(GraphVar[m].PorQ == i)
                            {
                                cout << GraphVar[m].GraphOut;
                            }
                        }
                        cout << "График " << i << endl << "\\end{minipage} " << endl;
                        if(i != 3)
                            cout << "\\hfill" << endl;
                    }
                cout << endl << "\\vspace{1.5em}" << endl;
                cout << "\\textbf{Варианты ответа:}" << endl;
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl;
                for(int i = 1; i<=3; i++)
                {
                    for(int m=0; m<4; m++)
                    {
                        if(GraphVar[m].PorO==i)
                            cout << "\\item     " << GraphVar[m].VarAnswer << endl;
                    }
                }
                cout << "\\end{enumerate}" << endl << endl << endl;

                Answer = "  \\item ";
                for(int i = 1; i <= 3; i++)
                {
                    for(int m = 0; m<4; m++)
                    {
                        if(GraphVar[m].PorQ == i)
                            Answer = Answer + to_string(static_cast<int>(GraphVar[m].PorO));
                    }
                }
                Answer = Answer + " \n";

                //cout << Answer << endl;
                break;
            
            case 3:
                do{
                    a[0] = rand()%5 + 1;
                    b[0] = pow(-1,rand())*(rand()%10+2);
                    c[0] = rand()%3 + 1;

                    a[1] = -1*(rand()%5 + 1);
                    b[1] = pow(-1,rand())*(rand()%10+2);
                    c[1] = rand()%3 + 1;

                    a[2] = -1*(rand()%5 + 1);
                    b[2] = pow(-1,rand())*(rand()%10+2);
                    c[2] = -1*(rand()%3 + 1);

                    a[3] = rand()%5 + 1;
                    b[3] = pow(-1,rand())*(rand()%10+2);
                    c[3] = -1*(rand()%3 + 1);

                    for(int i=0; i<4; i++)
                    {
                        xver[i] = -1*b[i]/(2*a[i]);
                        yver[i] = a[i]*xver[i]*xver[i]+b[i]*xver[i]+c[i];
                    }
                    check = 1;
                    for(int i = 0; i<4; i++)
                    {
                        if((xver[i]>2.5)||(xver[i]<-2.5))
                            check = 0;
                    }
                    for(int i = 0; i<4; i++)
                    {
                        if((yver[i]>2.5)||(yver[i]<-2.5))
                            check = 0;
                    }
                }while(check!=1);

                for(int i=0; i<4; i++)
                {
                    GraphVar[i].PorO = 0;
                    GraphVar[i].PorQ = 0;
                    GraphVar[i].TF = 0;
                    GraphVar[i].used = 0;
                    GraphVar[i].GraphOut = "";
                    if((a[i]==1)||(a[i]==-1))
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, a[i]) + "1*x*x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "*x" + SignUr(2,c[i]) + to_string(static_cast<int>(fabs(c[i]))) + "}\n";
                    else
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, a[i]) + to_string(static_cast<int>(fabs(a[i]))) + "*x*x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "*x" + SignUr(2,c[i]) + to_string(static_cast<int>(fabs(c[i]))) + "}\n";
                }
                GraphVar[0].VarAnswer = "$a>0$, $c>0$";
                GraphVar[1].VarAnswer = "$a<0$, $c>0$";
                GraphVar[2].VarAnswer = "$a<0$, $c<0$";
                GraphVar[3].VarAnswer = "$a>0$, $c<0$";

                for(int i=0; i<3; i++)
                    answer[i] = 0;

                for(int i=0; i<3; i++)
                {
                    do{
                        check = 0;
                        Var = rand()%3 +1;
                        if((answer[0]!=Var)&&(answer[1]!=Var)&&(answer[2]!=Var))
                        {
                            answer[i] = Var;
                            check = 1;
                        }    
                    }while(check!=1);
                }
                for(int i=0; i<3; i++)
                {
                    check = 0;
                    do{
                            Var = rand()%4;
                            if(GraphVar[Var].used==0)
                            {
                                GraphVar[Var].PorQ = i+1;
                                for(int m=0; m<3; m++)
                                {
                                    if((i+1)==answer[m])
                                    {
                                        GraphVar[Var].PorO = m + 1;
                                    }
                                }
                                GraphVar[Var].used = 1;
                                check = 1;
                            }
                    }while(check!=1);
                }
                cout << "\\item На рисунках изображены графики функций вида $y=ax^2+bx+c$. Установите соответствие между знаками коэффициентов $a$ и $c$ и графиками функций." << endl;
                cout << "\\vspace{1em}" << endl << endl 
                    << "\\noindent" << endl;
                    for(int i = 1; i<=3; i++)
                    {
                        cout << "\\begin{minipage}[t]{0.3\\textwidth}" << endl 
                             << "\\centering" << endl;
                        for(int m = 0; m<4; m++)
                        {
                            if(GraphVar[m].PorQ == i)
                            {
                                cout << GraphVar[m].GraphOut;
                            }
                        }
                        cout << "График " << i << endl << "\\end{minipage} " << endl;
                        if(i != 3)
                            cout << "\\hfill" << endl;
                    }
                cout << endl << "\\vspace{1.5em}" << endl;
                cout << "\\textbf{Варианты ответа:}" << endl;
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl;
                for(int i = 1; i<=3; i++)
                {
                    for(int m=0; m<4; m++)
                    {
                        if(GraphVar[m].PorO==i)
                            cout << "\\item     " << GraphVar[m].VarAnswer << endl;
                    }
                }
                cout << "\\end{enumerate}" << endl << endl << endl;

                Answer = "  \\item ";
                for(int i = 1; i <= 3; i++)
                {
                    for(int m = 0; m<4; m++)
                    {
                        if(GraphVar[m].PorQ == i)
                            Answer = Answer + to_string(static_cast<int>(GraphVar[m].PorO));
                    }
                }
                Answer = Answer + " \n";

                //cout << Answer << endl;
                break;

            case 4:
                do{
                    k[0] = pow(-1,rand())*(rand()%5 + 1);
                    b[0] = pow(-1,rand())*(rand()%10 + 2);

                    a[0] = pow(-1,rand())*(rand()%5 + 1);
                    b[1] = pow(-1,rand())*(rand()%10+2);
                    c[0] = pow(-1,rand())*(rand()%3 + 1);

                    k[1] = pow(-1,rand())*(rand()%10+1);            // Гипербола

                    k[2] = pow(-1,rand())*(rand()%10+1);            // Корень


                    xver[0] = -1*b[1]/(2*a[0]);
                    yver[0] = a[0]*xver[0]*xver[0]+b[1]*xver[0]+c[0];

                    check = 1;

                    if((b[0]<-3.5)||(b[0]>3.5)||((-1*b[0]/k[0])>3.5)||((-1*b[0]/k[0])<-3.5))
                        check = 0;
                    
                    if((xver[0]>2.5)||(xver[0]<-2.5))
                        check = 0;
                    if((yver[0]>2.5)||(yver[0]<-2.5))
                        check = 0;

                    if((k[1]>2.8)||(k[1]<-2.8))
                        check = 0;

                    if((k[2]>2.8)||(k[2]<-2.8))
                        check = 0;

                }while(check!=1);

                for(int i=0; i<4; i++)
                {
                    GraphVar[i].PorO = 0;
                    GraphVar[i].PorQ = 0;
                    GraphVar[i].TF = 0;
                    GraphVar[i].used = 0;
                }

                GraphVar[0].GraphOut = "";
                    if((k[0]==1)||(k[0]==-1))
                        GraphVar[0].GraphOut = GraphVar[0].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, k[0]) + "1*x" + SignUr(2,b[0]) + to_string(static_cast<int>(fabs(b[0]))) + "}\n";
                    else
                        GraphVar[0].GraphOut = GraphVar[0].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, k[0]) + to_string(static_cast<int>(fabs(k[0]))) + "* x" + SignUr(2,b[0]) + to_string(static_cast<int>(fabs(b[0])))  + "}\n";


                GraphVar[1].GraphOut = "";
                if((a[0]==1)||(a[0]==-1))
                        GraphVar[1].GraphOut = GraphVar[1].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, a[0]) + "1*x*x" + SignUr(2,b[1]) + to_string(static_cast<int>(fabs(b[1]))) + "*x" + SignUr(2,c[0]) + to_string(static_cast<int>(fabs(c[0])))  + "}\n";
                else
                    GraphVar[1].GraphOut = GraphVar[1].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, a[0]) + to_string(static_cast<int>(fabs(a[0]))) + "*x*x" + SignUr(2,b[1]) + to_string(static_cast<int>(fabs(b[1]))) + "*x" + SignUr(2,c[0]) + to_string(static_cast<int>(fabs(c[0])))  + "}\n";
                
                GraphVar[2].GraphOut = "";
                GraphVar[2].GraphOut = GraphVar[2].GraphOut + "\\mygraphonlyfirst{" + to_string(static_cast<int>(k[1])) +  "/x}; \n ";

                GraphVar[3].GraphOut = "";
                GraphVar[3].GraphOut = GraphVar[3].GraphOut + "\\mygraphonlyfirst{" + SignUr(1, k[2]) + to_string(static_cast<int>(fabs(k[2]))) + "*sqrt(x)" + "} \n";

                if((k[0]==1)||(k[0]==-1))
                    GraphVar[0].VarAnswer = "$y=" + SignUr(1,k[0]) + "x" + SignUr(2,b[0]) + to_string(static_cast<int>(fabs(b[0]))) + "$";
                else
                    GraphVar[0].VarAnswer = "$y=" + SignUr(1,k[0]) + to_string(static_cast<int>(fabs(k[0]))) + "x" + SignUr(2,b[0]) + to_string(static_cast<int>(fabs(b[0]))) + "$";
                
                if((a[0]==1)||(a[0]==-1))
                    GraphVar[1].VarAnswer = "$y=" + SignUr(1,a[0]) + "x^2" + SignUr(2,b[1]) + to_string(static_cast<int>(fabs(b[1]))) + "x" + SignUr(2,c[0]) + to_string(static_cast<int>(fabs(c[0]))) + "$";
                else
                    GraphVar[1].VarAnswer = "$y=" + SignUr(1,a[0]) + to_string(static_cast<int>(fabs(a[0]))) + "x^2" + SignUr(2,b[1]) + to_string(static_cast<int>(fabs(b[1]))) + "x" + SignUr(2,c[0]) + to_string(static_cast<int>(fabs(c[0]))) + "$";
                
                GraphVar[2].VarAnswer = "$y=" + SignUr(1,k[1]) + "\\frac{" + to_string(static_cast<int>(fabs(k[1]))) + "}{x} $";

                if(fabs(k[2])!=1)
                    GraphVar[3].VarAnswer = "$y=" + SignUr(1,k[2]) + to_string(static_cast<int>(fabs(k[2]))) + "\\sqrt{x}" + "$";
                else
                    GraphVar[3].VarAnswer = "$y=" + SignUr(1,k[2]) +  "\\sqrt{x}" + "$";


                for(int i=0; i<3; i++)
                    answer[i] = 0;

                for(int i=0; i<3; i++)
                {
                    do{
                        check = 0;
                        Var = rand()%3 +1;
                        if((answer[0]!=Var)&&(answer[1]!=Var)&&(answer[2]!=Var))
                        {
                            answer[i] = Var;
                            check = 1;
                        }    
                    }while(check!=1);
                }
                for(int i=0; i<3; i++)
                {
                    check = 0;
                    do{
                            Var = rand()%4;
                            if(GraphVar[Var].used==0)
                            {
                                GraphVar[Var].PorQ = i+1;
                                for(int m=0; m<3; m++)
                                {
                                    if((i+1)==answer[m])
                                    {
                                        GraphVar[Var].PorO = m + 1;
                                    }
                                }
                                GraphVar[Var].used = 1;
                                check = 1;
                            }
                    }while(check!=1);
                }
                cout << "\\item Установите соответствие между функциями и их графиками." << endl;
                cout << "\\vspace{1em}" << endl << endl 
                    << "\\noindent" << endl;
                    for(int i = 1; i<=3; i++)
                    {
                        cout << "\\begin{minipage}[t]{0.3\\textwidth}" << endl 
                             << "\\centering" << endl;
                        for(int m = 0; m<4; m++)
                        {
                            if(GraphVar[m].PorQ == i)
                            {
                                cout << GraphVar[m].GraphOut;
                            }
                        }
                        cout << "График " << i << endl << "\\end{minipage} " << endl;
                        if(i != 3)
                            cout << "\\hfill" << endl;
                    }
                cout << endl << "\\vspace{1.5em}" << endl;
                cout << "\\textbf{Варианты ответа:}" << endl;
                cout << "\\begin{enumerate}[label=\\arabic*)]" << endl;
                for(int i = 1; i<=3; i++)
                {
                    for(int m=0; m<4; m++)
                    {
                        if(GraphVar[m].PorO==i)
                            cout << "\\item     " << GraphVar[m].VarAnswer << endl;
                    }
                }
                cout << "\\end{enumerate}" << endl << endl << endl;

                Answer = "  \\item ";
                for(int i = 1; i <= 3; i++)
                {
                    for(int m = 0; m<4; m++)
                    {
                        if(GraphVar[m].PorQ == i)
                            Answer = Answer + to_string(static_cast<int>(GraphVar[m].PorO));
                    }
                }
                Answer = Answer + " \n";

                //cout << Answer << endl;
                break;

            }
            return Answer;
}

string ArivmetProgr(int AllType)
{
    double t[3];
            double delta;
            double a0, an;
            double answer;
            int type;
            if(AllType == 0)
                type = rand()%4 + 1;
            else
                type = AllType;
            string Answer;
            switch (type)
            {
            case 1:
                t[0] = rand() % 10 + 9;
                t[1] = rand() % 5 + 3;
                delta = rand() % 7 + 4;
                a0 = pow(01, rand()) * (rand() % 13 + 2);
                answer = a0 - delta * t[1];
                cout << "\\item При проведении опыта вещество равномерно охлаждали в течение " << t[0] << " минут. При этом каждую минуту температура вещества уменьшалась на $" << delta << "^{\\circ}C$." <<
                    "Найдите температуру вещества (в градусах Цельсия) через " << t[1] << " минуты после начала проведения опыта, если его начальная температура составляла $" << a0 << "^{\\circ}C$." << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                t[0] = rand() % 13 + 3;
                delta = 10;
                a0 = rand() % 6 + 4;
                an = a0 + delta * (t[0] - 1);
                answer = t[0] * (a0 + an) / 2;
                cout << "\\item Камень бросают в глубокое ущелье. При этом в первую секунду он пролетает " << a0 << " метров, а в каждую следующую секунду на 10 метров больше, чем в предыдущую, до тех пор, пока не достигнет дна ущелья. Сколько метров пролетит камень за первые " << t[0] << " секунд?" << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                t[0] = rand() % 9 + 10;
                delta = rand() % 7 + 2;
                a0 = rand() % 9 + 10;
                an = a0 + delta * (t[0] - 1);
                answer = t[0] * (a0 + an) / 2;
                if (delta <= 4)
                {
                    cout << "\\item В амфитеатре " << t[0] << " рядов. В первом ряду " << a0 << " мест, а в каждом следующем на " << delta << " места больше, чем в предыдущем. Сколько всего мест в амфитеатре?" << endl;
                }
                else
                {
                    cout << "\\item В амфитеатре " << t[0] << " рядов. В первом ряду " << a0 << " мест, а в каждом следующем на " << delta << " мест больше, чем в предыдущем. Сколько всего мест в амфитеатре?" << endl;
                }
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:
                t[0] = rand() % 10 + 15;
                int check = 0;
                double a2, a3;
                do {
                    t[1] = rand() % 7 + 2;
                    t[2] = rand() % 7 + 2;
                    check = 1;
                    if (t[1] >= t[2])
                        check = 0;
                } while (check != 1);
                do {
                    a2 = rand() % 30 + 12;
                    a3 = rand() % 30 + 12;
                    delta = (a3 - a2) / (t[2] - t[1]);
                    a0 = a2 - delta * (t[1] - 1);
                    answer = a0 + delta * (t[0] - 1);
                    check = 1;
                    if (a3 <= a2)
                        check = 0;
                    if ((fabs(delta) - static_cast<int>(fabs(delta))) > 0)
                        check = 0;
                    if (a0 < 1)
                        check = 0;
                } while (check != 1);
                cout << "\\item В амфитеатре " << t[0] << " рядов, причём в каждом следующем ряду на одно и то же число мест больше, чем в предыдущем. В " << t[1] << "-м ряду " << a2 << " мест, а в " << t[2] << "-м ряду " << a3 << " мест. Сколько мест в последнем ряду амфитеатра?" << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;
            }
            return Answer;
}

string GeomProgr(int AllType)
{
    double t[2];                   // t0 - период, tn - время когда  ищем
            double a0, an, A;
            double delta;
            int type;
            double answer;
            int check = 0;
            string Answer;
            if(AllType == 0)
                type = rand()%3+1;
            else
                type = AllType;
            switch (type)
            {
            case 1:
                do {
                    a0 = rand() % 900 + 50;
                    delta = rand() % 5 + 2;
                    t[0] = rand() % 5 + 5;
                    t[1] = rand() % 70 + 9;
                    answer = a0 / pow(delta,(t[1]/t[0]));
                    check = 1;
                    if ((t[1] / t[0]) - static_cast<int>(t[1] / t[0]) != 0)
                        check = 0;
                    if (answer - static_cast<int>(answer) != 0)
                        check = 0;
                    if ((t[1] / t[0]) < 3)
                        check = 0;
                } while (check != 1);
                if ((delta == 2) || (delta == 3) || (delta == 4))
                {
                    cout << "\\item В ходе распада радиоактивного изотопа его масса уменьшается в " << delta << " раза каждые " << t[0] << " минут. В начальный момент масса изотопа" <<
                        "составляла " << a0 << " мг. Найдите массу изотопа через " << t[1] << " минуты. Ответ дайте в миллиграммах." << endl;
                }
                else
                {
                    cout << "\\item В ходе распада радиоактивного изотопа его масса уменьшается в " << delta << " раз каждые " << t[0] << " минут. В начальный момент масса изотопа" <<
                        "составляла " << a0 << " мг.Найдите массу изотопа через " << t[1] << " минуты.Ответ дайте в миллиграммах." << endl;
                }
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                do {
                    a0 = rand() % 300 + 100;
                    an = rand() % 40 + 10;
                    delta = rand() % 3 + 2;
                    t[0] = 1;
                    A = a0;
                    check = 1;
                    if (a0 > an)
                    {
                        do {
                            A = A / delta;
                            t[0]++;
                        } while (A>an);
                        answer = t[0];
                    }
                } while (check != 1);
                cout << "\\item У Тани есть теннисный мячик. Она со всей силы бросила его об асфальт. После первого отскока мячик подлетел на" << endl
                    << "высоту " << a0 << " см, а после каждого следующего отскока от асфальта подлетал на высоту в " << delta << " раза меньше предыдущей. После какого по счёту отскока высота, на которую подлетит мячик, станет меньше " << an << " см?" << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                if (pow(-1, rand()) > 0)
                {
                    do {
                        delta = rand() % 3 + 2;
                        t[0] = rand() % 5 + 4;
                        t[1] = rand() % 100 + 50;
                        a0 = rand() % 700 + 99;
                        answer = a0 / (pow(delta, (t[1] / t[0])));
                        check = 1;
                        if (t[0] > t[1])
                            check = 0;
                        if (fabs(t[1] / t[0]) - static_cast<int>(t[1] / t[0]) != 0)
                            check = 0;
                        if (answer - static_cast<int>(answer) != 0)
                            check = 0;
                    } while (check != 1);
                    cout << "\\item В ходе распада радиоактивного изотопа его масса уменьшается в " << delta << " раза каждые " << t[0] << " минут. В начальный момент масса изотопа составляла " << a0 << " мг. Найдите массу изотопа через " << t[1] << " минуты. Ответ дайте в миллиграммах." << endl;
                    //cout << answer << endl;
                }
                else
                {
                    do {
                        delta = rand() % 3 + 2;
                        t[0] = rand() % 5 + 4;
                        t[1] = rand() % 100 + 50;
                        a0 = rand() % 30 + 5;
                        answer = a0 * (pow(delta, (t[1] / t[0])));
                        check = 1;
                        if (t[0] > t[1])
                            check = 0;
                        if (fabs(t[1] / t[0]) - static_cast<int>(t[1] / t[0]) != 0)
                            check = 0;
                        if (answer - static_cast<int>(answer) != 0)
                            check = 0;
                        if (t[1] / t[0] > 8)
                            check = 0;
                        if (answer > 2000)
                            check = 0;
                    } while (check != 1);
                    cout << "\\item В ходе биологического эксперимента в чашку Петри с питательной средой поместили колонию микроорганизмов массой " << a0 << " мг. За каждые " << t[0] <<" минут масса колонии увеличивается в " << delta << " раза. Найдите массу колонии микроорганизмов через " << t[1] << " минут после начала эксперимента. Ответ дайте в миллиграммах." << endl;
                    //cout << answer << endl;
                }
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;


            }
            return Answer;
}

string TreugUgli(int i, int AllType)
{
    double Agrad, Bgrad, Arad, Brad;
            double r1, r2;
            int type;
            string Answer;
            double answer;
            int check = 0;
            if(AllType == 0)
                type = rand()%6+1;
            else
                type = AllType;
            switch (type)
            {
            case 1:
                do {
                    r1 = rand() % 20 + 10;
                    r1 = r1 / 10;

                    r2 = rand() % 20 + 10;
                    r2 = r2 / 10;

                    Agrad = rand() % 70 + 9;
                    Arad = PI * Agrad / 180;

                    Bgrad = 180 - Agrad;

                    check = 1;
                    if (Agrad < 30)
                        check = 0;
                    if ((r1 + (r2 * cos(Arad))) > 3.5)
                        check = 0;
                    if ((r1 + (r2 * cos(Arad))) < 3.4)
                        check = 0;
                    if ((r2 * sin(Arad)) > 1.5)
                        check = 0;
                    if ((r2 * sin(Arad)) < 1.4)
                        check = 0;
                    answer = Agrad;
                } while (check != 1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "       В треугольник $ABC$ угол $C$ равен $" << Bgrad << "^{\\circ}$. Найдите внешний угол при вершине $C$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << Agrad << ":" << r2 << ");" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << r1 << ");" << endl
                    << "            \\coordinate (O) at (0:{" << r2 << "*cos(" << Agrad << ")});" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (O);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                do {
                    Agrad = rand() % 70 + 10;
                    Arad = PI * Agrad / 180;
                    r1 = rand() % 100 + 1;
                    answer = Agrad;
                    check = 1;
                    if ((r1 * sin(Arad)) > 1.6)
                        check = 0;
                    if ((r1 * sin(Arad)) < 1)
                        check = 0;
                    if ((2 * r1 * cos(Arad)) > 4)
                        check = 0;
                } while (check != 1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольник $ABC$ известно, что $AB=BC$, $\\angle ABC=" << (180-2*Agrad) << "^{\\circ}$. Найдите угол $BCA$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (-" << Agrad << ":" << r1 << ");" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (-" << (180-Agrad) << ":" << r1 << ");" << endl
                    << "            \\tkzMarkSegment[mark=|](B,A);" << endl
                    << "            \\tkzMarkSegment[mark=|](B,C);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                do {
                    r1 = rand() % 80 + 5;
                    r1 = r1 / 10;
                    Agrad = rand() % 80 + 2;
                    Arad = PI * Agrad / 180;
                    answer = Agrad / 2;
                    check = 1;
                    if (Agrad < 30)
                        check = 0;
                    if ((r1 * sin(Arad)) > 1.6)
                        check = 0;
                    if ((r1 * sin(Arad)) < 1.3)
                        check = 0;
                } while (check != 1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ известно, что $\\angle BAC=" << Agrad << "^{\\circ}$, $AD$ -- биссектриса. Найдите угол $BAD$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (0,0);" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (3.5,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << Agrad << ":" << r1 << ");" << endl
                    << "            \\coordinate[label=above right:$D$] (D) at ($(B)!{" << r1 << "/(3.5+" << r1 << ")}!(C)$);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (D);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](D,A,B);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](C,A,D);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:
                do {
                    Agrad = rand() % 60 + 3;
                    Arad = PI * Agrad / 180;
                    r1 = 3.5 * cos(Arad);
                    answer = 90 - Agrad;
                    check = 1;
                    if ((r1 * sin(Arad)) > 1.6)
                        check = 0;
                    if ((r1 * sin(Arad)) < 1.4)
                        check = 0;
                } while (check != 1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Один из острых углов прямоугольного треугольника равен $" << Agrad << "^{\\circ}$. Найдите его другой острый угол. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (C) at (3.5,0);" << endl
                    << "            \\coordinate (B) at (23:3.22);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,B,C);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 5:
                do {
                    Agrad = rand() % 70 + 4;
                    Arad = PI * Agrad / 180;
                    r1 = rand() % 30 + 3;
                    r1 = r1 / 10;
                    answer = 90 - Agrad;
                    check = 1;
                    if ((r1 * sin(Arad)) > 1.6)
                        check = 0;
                    if ((r1 * sin(Arad)) < 1.4)
                        check = 0;
                } while (check != 1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В остроугольном треугольнике $ABC$ проведена высота $BH$, $\\angle BAC=" << Agrad << "^{\\circ}$. Найдите угол $ABH$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (0,0);" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (3.5,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << Agrad << ":{" << (3.5*cos(Arad)) << "});" << endl
                    << "            \\coordinate[label=below:$H$] (H) at (0:{" << (3.5 * pow(cos(Arad),2)) << "});" << endl
                    << "            \\draw[thick] (B) -- (A) -- (C) -- (B) -- (H);" << endl
                    << "            \\tkzMarkRightAngle(B,H,A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 6:
                do {
                    Agrad = rand() % 50 + 8;
                    Arad = PI * Agrad / 180;
                    Bgrad = rand() % 50 + 8;
                    Brad = PI * Bgrad / 180;
                    r1 = 1.5 / sin(Arad);
                    r2 = 1.5 / sin(Brad);
                    answer = 180 - Agrad - Bgrad;
                    check = 1;
                    if ((r1 * cos(Arad) + r2 * cos(Brad)) < 3.3)
                        check = 0;
                    if ((r1 * cos(Arad) + r2 * cos(Brad)) > 3.5)
                        check = 0;
                } while (check != 1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике два угла равны $" << Agrad << "^{\\circ}$ и $" << Bgrad << "^{\\circ}$. Найдите его третий угол. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (C) at (-" << Agrad << ":" << r1 << ");" << endl
                    << "            \\coordinate (B) at ({-180+" << Bgrad << "}:" << r2 << ");" << endl
                    << "            \\draw[thick] (B) -- (A) -- (C) -- (B);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;
            }
            return Answer;
}

string TreugStoron(int i, int AllType)
{
    double r, R, a, h, b, c, k, max, betta[2], gamma[3];
            double alpha;
            int type;
            string Answer;
            double answer;
            int check = 0;
            if(AllType == 0)
                type = rand()%16 + 1;
            else
                type = AllType;
            switch(type)
            {
            case 1:
                r = rand()%15+3;
                answer = 6*r;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Радиус окружности, вписанной в равносторонний треугольник, равен $" << r << "\\sqrt{3}$. Найдите длину стороны этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\draw[thick] (O) circle(0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                a = rand()%40+2;
                answer = a/2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Сторона равностороннего треугольника равна $" << a << "\\sqrt{3}$. Найдите радиус окружности, вписанной в этот треугольник." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\draw[thick] (O) circle(0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                a = rand()%40+2;
                answer = a;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Сторона равностороннего треугольника равна $" << a << "\\sqrt{3}$. Найдите радиус окружности, описанной около этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\draw[thick] (O) circle(1.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:
                R = rand()%15+3;
                answer = 3*R;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Радиус окружности,  описанной около равностороннего треугольника, равен $" << R << "\\sqrt{3}$. Найдите длину стороны этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\draw[thick] (O) circle(1.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 5:
                h = rand()%15+3;
                answer = 2*h;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Медиана равностороннего треугольника равна $" << h << "\\sqrt{3}$. Найдите сторону этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\coordinate (D) at (-90:0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (D) -- (C);" << endl
                    << "            \\tkzMarkSegment[mark=|, thick](B,D);" << endl
                    << "            \\tkzMarkSegment[mark=|, thick](D,A);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 6:
                a = rand()%15+3;
                answer = 1.5*a;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Сторона равностороннего треугольника равна $" << a << "\\sqrt{3}$. Найдите биссектрису этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\coordinate (D) at (-90:0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (D) -- (C);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.7](B,C,D);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.7](D,C,A);" << endl;
                   cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 7:
                h = rand()%15+3;
                answer = 2*h;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Высота равностороннего треугольника равна $" << h << "\\sqrt{3}$. Найдите сторону этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\coordinate (D) at (-90:0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (D) -- (C);" << endl
                    << "            \\tkzMarkRightAngle(A,D,C);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 8:
                do{
                    a = rand()%100+1;
                    b = rand()%100+1;
                    answer = sqrt(pow(a,2)+pow(b,2));
                    check = 1;
                    if(answer-static_cast<int>(answer)!=0)
                        check = 0;
                }while(check!=1);
                if(a>=b)
                    max = a;
                else
                    max = b;
                k = max/2.2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Катеты прямоугольного треугольника равны $" << a << "$ и $" << b << "$. Найдите гипотенузу этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (C) at (0,0);" << endl
                    << "            \\coordinate (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 9:
                do{
                    c = rand()%100+1;
                    a = rand()%100+1;
                    check = 1;
                    if(c>a)
                    {
                        b = sqrt(pow(c,2)-pow(a,2));
                        if(b-static_cast<int>(b)!=0)
                            check = 0;
                    }
                    else
                        check = 0;
                }while(check!=1);
                answer = b;
                if(a>=b)
                    max = a;
                else
                    max = b;
                k = max/2.2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В прямоугольном треугольнике катет и гипотенуза равны $" << a << "$ и $" << c << " соответственно$. Найдите другой катет этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (C) at (0,0);" << endl
                    << "            \\coordinate (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 10:
                do{
                    a = rand()%100+1;
                    b = rand()%100+1;
                    c = sqrt(pow(a,2)+pow(b,2));
                    check = 1;
                    if(c-static_cast<int>(c)!=0)
                        check = 0;
                }while(check!=1);
                if(a>=b)
                    max = a;
                else
                    max = b;
                k = max/2.2;
                answer = c/2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ известно, что $AC = " << a << "$, $BC = " << b << "$, угол $C$ равен $90^{\\circ}$. Найдите радиус описанной около этого треугольника окружности." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (C) at (0,0);" << endl
                    << "            \\coordinate (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 11:
                do{
                    a = rand()%100 + 1;
                    b = rand()%100 + 1;
                    c = rand()%100 + 1;
                    check = 1;
                    if(((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b)<1)&&((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b)>0))
                    {
                        alpha = acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));
                        alpha = 180*alpha/PI;
                        if(alpha>70)
                            check = 0;
                    }
                    else
                        check = 0;
                    answer = a/2;
                    if(a>=b)
                        max = a;
                    else
                        max = b;
                    if(c>=max)
                        max = c;
                    k=max/2.2;
                    if((a/k)<1.3)
                        check = 0;
                    if((b/k)<1.3)
                        check = 0;
                    if((c/k)<1.3)
                        check = 0;
                }while(check!=1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Точки $M$ и $N$ являются серединами сторон $AB$ и $BC$ треугольника $ABC$, сторона $AB$ равна " << b << ", сторона $BC$ равна " << c << ", сторона $AC$ равна " << a << ". Найдите $MN$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$A$]   (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << alpha << ":" << (b/k) << ");" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (0:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=left:$M$] (M) at ($(A)!0.5!(B)$);" << endl
                    << "            \\coordinate[label=right:$N$] (N) at ($(C)!0.5!(B)$);" << endl
                    << "            \\tkzMarkSegment[mark=|](A,M);" << endl
                    << "            \\tkzMarkSegment[mark=|](B,M);" << endl
                    << "            \\tkzMarkSegment[mark=||](N,B);" << endl
                    << "            \\tkzMarkSegment[mark=||](C,N);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (M) -- (N);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 12:
                do{
                    a = rand()%100 + 1;
                    b = rand()%100 + 1;
                    c = rand()%100 + 1;
                    check = 1;
                    if(((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b)<1)&&((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b)>0))
                    {
                        alpha = acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));
                        alpha = 180*alpha/PI;
                        if(alpha>70)
                            check = 0;
                    }
                    else
                        check = 0;
                    answer = a/2;
                    if(a>=b)
                        max = a;
                    else
                        max = b;
                    if(c>=max)
                        max = c;
                    k=max/2.2;
                    if((a/k)<1.2)
                        check = 0;
                    if((b/k)<1.2)
                        check = 0;
                    if((c/k)<1.2)
                        check = 0;
                    r = sqrt(pow((a/2),2)+pow(b,2)-a*b*cos(alpha*PI/180));
                    if(r-static_cast<int>(r)!=0)
                        check = 0;
                    if(a<b)
                        check = 0;
                }while(check!=1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ известно, что $AC=" << a << "$, $BM$ -- медиана, $BM=" << r << "$. Найдите $AM$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$A$]   (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << alpha << ":" << (b/k) << ");" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (0:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=below:$M$] (M) at ($(A)!0.5!(C)$);" << endl
                    << "            \\tkzMarkSegment[mark=|](A,M);" << endl
                    << "            \\tkzMarkSegment[mark=|](C,M);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (M) -- (B);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 13:
                do{
                    a = rand()%100+1;
                    b = rand()%100+1;
                    answer = sqrt(pow(a,2)+pow(b,2));
                    check = 1;
                    if(answer-static_cast<int>(answer)!=0)
                        check = 0;
                }while(check!=1);
                if(a>=b)
                    max = a;
                else
                    max = b;
                k = max/2.2;
                answer = a*b/2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Катеты прямоугольного треугольника равны $" << a << "$ и $" << b << "$. Найдите площадь этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (C) at (0,0);" << endl
                    << "            \\coordinate (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 14:
                do{
                    a = rand()%100 +1;
                    b = rand()%100 +1;
                    betta[0]=rand()%10+2;
                    betta[1]=rand()%10+2;
                    alpha = 180*asin(betta[0]/betta[1])/PI;
                    check = 1;
                    answer = a*b*betta[0]/(2*betta[1]);
                    if(a>b)
                        k=a/2;
                    else
                        k=b/2;
                    if(betta[0]>betta[1])
                        check = 0;
                    if(answer-static_cast<int>(answer)!=0)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                    if(b/k<1)
                        check = 0;
                    if(alpha<30)
                        check = 0;
                    if(betta[0]==betta[1])
                        check = 0;
                }while(check!=1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ известно, что $AB=" << a << "$, $BC=" << b << "$, $\\sin(\\angle ABC)=\\frac{" << betta[0] << "}{" << betta[1] << "}$. Найдите площадь треугольника $ABC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (-30-" << alpha << ":" << a/k << ");" << endl
                    << "            \\coordinate[label=right:$C$] (C) at (-30:" << b/k << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 15:
            do{
                    a = rand()%100 +1;
                    b = rand()%100 +1;
                    alpha = rand()%80+1;
                    h = static_cast<int>(b * sin((PI*alpha)/180));
                    check = 1;
                    answer = a * h/2;
                    if(a>b)
                        k=a/2;
                    else
                        k=b/2;
                    if(answer-static_cast<int>(answer)!=0)
                        check = 0;
                    if(2.3*a<b)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                    if(b/k<1)
                        check = 0;
                    if((a-a*cos((PI*alpha)/180))/k<0.4)
                        check = 0;
                    if(h/k<0.8)
                        check = 0;
                    if(alpha<15)
                        check = 0;
                }while(check!=1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Сторона треугольника равна " << a << ", а высота, проведенная к этой стороне, равна " << h << ". Найдите площадь этого треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (B) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30-" << alpha << ":" << a/k << ");" << endl
                    << "            \\coordinate (C) at (-30:" << b/k << ");" << endl
                    << "            \\coordinate (O) at (-30-" << alpha << ":" << (b*cos((PI*alpha)/180))/k << ");" << endl
                    << "            \\tkzMarkRightAngle(A,O,C);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (O) -- (C);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 16:
                do{
                    betta[0] = rand()%40 + 3;
                    betta[1] = rand()%40 + 120;
                    r = rand()%20 + 1;
                    gamma[0] = betta[1] - betta[0];
                    gamma[1] = 270 - betta[1];
                    gamma[2] = 360 + betta[0] - 270;
                    a = static_cast<int>((r*tan((PI*gamma[1])/360)) + (r*tan((PI*gamma[2])/360)));
                    b = static_cast<int>((r*tan((PI*gamma[0])/360)) + (r*tan((PI*gamma[2])/360)));
                    c = static_cast<int>((r*tan((PI*gamma[0])/360)) + (r*tan((PI*gamma[1])/360)));
                    max = 0;
                    if(a>max)
                        max = a;
                    if(b>max)
                        max = b;
                    if(c>max)
                        max = c;
                    k = max/2.5;
                    check = 1;
                    answer = r*(a+b+c)/2;
                }while(check!=1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Периметр треугольника равен " << a+b+c << ", одна из его сторон равна " << a << ", а радиус вписанной в него окружности равен " << r << ". Найдите площадь этого  треугольника." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << r/k << ");" << endl
                    << "            \\coordinate (A) at (" << betta[0] + gamma[0]/2 << ":" << (r/cos((PI*gamma[0])/360))/k << ");" << endl
                    << "            \\coordinate (B) at (" << betta[1] + gamma[1]/2 << ":" << (r/cos((PI*gamma[1])/360))/k << ");" << endl
                    << "            \\coordinate (C) at (" << 270 + gamma[2]/2 << ":" << (r/cos((PI*gamma[2])/360))/k << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;


            }
            return Answer;
}

string TreugReshotka(int i, int AllType)
{
            int type;
            double xmax, ymax, xmid, x, y;
            string Answer;
            double answer;
            int check = 0;
            if(AllType == 0)
                type = rand()%3+1;
            else
                type = AllType;
            switch (type)
            {
            case 1:
                do {
                    xmax = rand() % 50 + 1;
                    ymax = rand() % 50 + 1;
                    check = 1;
                    y = (ymax - 10) / 5;
                    x = (xmax - 10) / 5;
                    if ((xmax < 30)||(ymax<30))
                        check = 0;
                    if((static_cast<int>(xmax)%10!=0)|| (static_cast<int>(ymax) % 10 != 0))
                        check = 0;
                } while (check != 1);
                if (y > x)
                    answer = y;
                else
                    answer = x;
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1х1 изображен ромб. Найдите длину его большей диагонали." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << (xmax/10) << "," << (ymax/10) << ");" << endl
                    << "            \\coordinate (A) at (0.5," << (ymax/20) << ");" << endl
                    << "            \\coordinate (B) at (" << xmax/20 << "," << (ymax/10)-0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << (xmax/10)-0.5 << "," << (ymax/20) << ");" << endl
                    << "            \\coordinate (D) at (" << xmax/20 << "," << 0.5 << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                do {
                    xmax = rand() % 50 + 1;
                    ymax = rand() % 50 + 1;
                    check = 1;
                    xmid = rand() % 50 + 1;
                    x = (ymax - 10) / 5;
                    check = 1;
                    if ((xmax < 30) || (ymax < 30))
                        check = 0;
                    if ((static_cast<int>(xmax) % 5 != 0) || (static_cast<int>(ymax) % 5 != 0))
                        check = 0;
                    if ((xmid > (xmax - 5)) || (xmid < 5))
                        check = 0;
                    if (static_cast<int>(xmid) % 5 != 0)
                        check = 0;
                } while (check != 1);
                answer = (xmax - 10) / 10;
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен треугольник $ABC$. Найдите длину его средней линии, параллельной стороне $AC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << (xmax / 10) << "," << (ymax / 10) << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (0.5,0.5);" << endl
                    << "            \\coordinate[label=above right:$B$] (B) at (" << (xmid/10) << "," << ((ymax - 5) / 10) << ");"
                    << "            \\coordinate[label=below right:$C$] (C) at (" << ((xmax - 5) / 10) << ",0.5);"
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);";
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                do {
                    xmax = rand() % 50 + 1;
                    ymax = rand() % 50 + 1;
                    check = 1;
                    xmid = rand() % 50 + 1;
                    x = (ymax - 10) / 5;
                    check = 1;
                    if ((xmax < 30) || (ymax < 30))
                        check = 0;
                    if ((static_cast<int>(xmax) % 5 != 0) || (static_cast<int>(ymax) % 5 != 0))
                        check = 0;
                    if ((xmid > (xmax - 5)) || (xmid < 5))
                        check = 0;
                    if (static_cast<int>(xmid) % 5 != 0)
                        check = 0;
                } while (check != 1);
                answer = ((xmax/5)-2)*((ymax/5)-2)/2;
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен треугольник. Найдите его площадь." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << (xmax / 10) << "," << (ymax / 10) << ");" << endl
                    << "            \\coordinate (A) at (0.5,0.5);" << endl
                    << "            \\coordinate (B) at (" << (xmid/10) << "," << ((ymax - 5) / 10) << ");"
                    << "            \\coordinate (C) at (" << ((xmax - 5) / 10) << ",0.5);"
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);";
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;
            }
            return Answer;
}

string TreugTrigonom(int i, int AllType)
{
    double a, b, c, max, k, chisl, znam;
            double alpha;
            int type;
            string Answer;
            double answer;
            int nod;
            int check = 0;
            if(AllType == 0)
                type = rand()%18+1;
            else
                type = AllType;
            switch(type)
            {
            case 1: // sinA
                do{
                    b = rand()%90+9;
                    c = rand()%99+9;
                    check = 1;
                    if(c>b)
                    {
                        answer = b/c;
                        if((100*answer)-(static_cast<int>(100*b/c))!=0)
                            check = 0;
                    }
                    else
                    {
                        check = 0;
                    }
                }while(check!=1);
                if(b>sqrt(c*c-b*b))
                        max = b;
                    else
                        max = sqrt(c*c-b*b);
                    k=max/2.2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $BC=" << b << "$, $AB=" << c << "$. Найдите $\\sin(A)$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (sqrt(pow(c,2)-pow(b,2))/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:     // sinB
                do{
                    a = rand()%90+9;
                    c = rand()%99+9;
                    check = 1;
                    if(c>a)
                    {
                        answer = a/c;
                        if((100*answer)-(static_cast<int>(100*a/c))!=0)
                            check = 0;
                    }
                    else
                    {
                        check = 0;
                    }
                }while(check!=1);
                if(a>sqrt(c*c-a*a))
                    max = a;
                else
                    max = sqrt(c*c-a*a);
                k=max/2.2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $AC=" << a << "$, $AB=" << c << "$. Найдите $\\sin(B)$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (sqrt(pow(c,2)-pow(a,2))/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:     //cosA
                do{
                    a = rand()%90+9;
                    c = rand()%99+9;
                    check = 1;
                    if(c>a)
                    {
                        answer = a/c;
                        if((100*answer)-(static_cast<int>(100*a/c))!=0)
                            check = 0;
                    }
                    else
                    {
                        check = 0;
                    }
                }while(check!=1);
                if(a>sqrt(c*c-a*a))
                    max = a;
                else
                    max = sqrt(c*c-a*a);
                k=max/2.2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $AC=" << a << "$, $AB=" << c << "$. Найдите $\\cos(A)$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (sqrt(pow(c,2)-pow(a,2))/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:
                do{
                    b = rand()%90+9;
                    c = rand()%99+9;
                    check = 1;
                    if(c>b)
                    {
                        answer = b/c;
                        if((100*answer)-(static_cast<int>(100*b/c))!=0)
                            check = 0;
                    }
                    else
                    {
                        check = 0;
                    }
                }while(check!=1);
                if(b>sqrt(c*c-b*b))
                    max = b;
                else
                    max = sqrt(c*c-b*b);
                k=max/2.2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $BC=" << b << "$, $AB=" << c << "$. Найдите $\\cos(B)$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (sqrt(pow(c,2)-pow(b,2))/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 5:     // tgA
                do{
                    a = rand()%90 + 9;
                    b = rand()%90 + 9;
                    answer = b/a;
                    check = 1;
                    if(100*answer-static_cast<int>(100*answer)!=0)
                        check = 0;
                }while(check!=1);
                if(b>a)
                    max = b;
                else
                    max = a;
                k=max/2.2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $BC=" << b << "$, $AC=" << a << "$. Найдите $\\tg(A)$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 6:         // tgB
                do{
                    a = rand()%90 + 9;
                    b = rand()%90 + 9;
                    answer = a/b;
                    check = 1;
                    if(100*answer-static_cast<int>(100*answer)!=0)
                        check = 0;
                }while(check!=1);
                if(b>a)
                    max = b;
                else
                    max = a;
                k=max/2.2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $BC=" << b << "$, $AC=" << a << "$. Найдите $\\tg(B)$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 7:     // sinA kat
                do{
                    c = rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    b = (c*chisl)/znam;
                    a = sqrt(pow(c,2)-pow(b,2));
                    check = 1;
                    if(a==c)
                        check = 0;
                    if(chisl>znam)
                        check = 0;
                    if((b-static_cast<int>(b))!=0)
                        check = 0;
                    if(a<1)
                        check = 0;
                }while(check!=1);
                if(b>a)
                    max = b;
                else
                    max = a;
                k=max/2.2;
                answer = b;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\sin(A)=\\frac{" << chisl << "}{" << znam << "}$, $AB=" << c << "$. Найдите $BC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 8:     //sinA gip
                do{
                    b = rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    c = b*znam/chisl;
                    a = sqrt(pow(c,2)-pow(b,2));
                    check = 1;
                    if(a==c)
                        check = 0;
                    if(chisl>znam)
                        check = 0;
                    if((c-static_cast<int>(c))!=0)
                        check = 0;
                    if(b>a)
                    max = b;
                    else
                    max = a;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = c;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\sin(A)=\\frac{" << chisl << "}{" << znam << "}$, $BC=" << b << "$. Найдите $AB$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 9:         // sinB kat
                do{
                    c = rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    a = (c*chisl)/znam;
                    b = sqrt(pow(c,2)-pow(a,2));
                    check = 1;
                    if(b==0)
                        check = 0;
                    if(chisl>znam)
                        check = 0;
                    if((a-static_cast<int>(a))!=0)
                        check = 0;
                    if(b>a)
                    max = b;
                    else
                    max = a;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = a;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\sin(B)=\\frac{" << chisl << "}{" << znam << "}$, $AB=" << c << "$. Найдите $AC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 10:        // sin B gip
                do{
                    a = rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    c = a*znam/chisl;
                    b = sqrt(pow(c,2)-pow(a,2));
                    check = 1;
                    if(b==0)
                        check = 0;
                    if(chisl>znam)
                        check = 0;
                    if((c-static_cast<int>(c))!=0)
                        check = 0;
                    if(b>a)
                    max = b;
                    else
                    max = a;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = c;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\sin(B)=\\frac{" << chisl << "}{" << znam << "}$, $AC=" << a << "$. Найдите $AB$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 11:
                do{
                    c = rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    b = (c*chisl)/znam;
                    a = sqrt(pow(c,2)-pow(b,2));
                    check = 1;
                    if(a==c)
                        check = 0;
                    if(chisl>znam)
                        check = 0;
                    if((b-static_cast<int>(b))!=0)
                        check = 0;
                    if(b>a)
                    max = b;
                    else
                    max = a;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = b;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\cos(B)=\\frac{" << chisl << "}{" << znam << "}$, $AB=" << c << "$. Найдите $BC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 12:
                do{
                    b = rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    c = b*znam/chisl;
                    a = sqrt(pow(c,2)-pow(b,2));
                    check = 1;
                    if(a==c)
                        check = 0;
                    if(chisl>znam)
                        check = 0;
                    if((c-static_cast<int>(c))!=0)
                        check = 0;
                    if(b>a)
                    max = b;
                    else
                    max = a;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = c;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\cos(B)=\\frac{" << chisl << "}{" << znam << "}$, $BC=" << b << "$. Найдите $AB$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 13:
                do{
                    c = rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    a = (c*chisl)/znam;
                    b = sqrt(pow(c,2)-pow(a,2));
                    check = 1;
                    if(b==0)
                        check = 0;
                    if(chisl>znam)
                        check = 0;
                    if((a-static_cast<int>(a))!=0)
                        check = 0;
                    if(b>a)
                    max = b;
                    else
                    max = a;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = a;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\cos(A)=\\frac{" << chisl << "}{" << znam << "}$, $AB=" << c << "$. Найдите $AC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 14:
                do{
                    a = rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    c = a*znam/chisl;
                    b = sqrt(pow(c,2)-pow(a,2));
                    check = 1;
                    if(b==0)
                        check = 0;
                    if(chisl>znam)
                        check = 0;
                    if((c-static_cast<int>(c))!=0)
                        check = 0;
                    if(b>a)
                    max = b;
                    else
                    max = a;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = c;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\cos(A)=\\frac{" << chisl << "}{" << znam << "}$, $AC=" << a << "$. Найдите $AB$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 15:
                do{
                    a =rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    check = 1;
                    b = a*chisl/znam;
                    if((b-static_cast<int>(b))!=0)
                        check = 0;
                        if(b>a)
                    max = b;
                    else
                    max = a;
                    if(znam==1)
                        check = 0;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = b;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\tg(A)=\\frac{" << chisl << "}{" << znam << "}$, $AC=" << a << "$. Найдите $BC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 16:
                do{
                    b =rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    check = 1;
                    a = b*znam/chisl;
                    if((a-static_cast<int>(a))!=0)
                        check = 0;
                        if(b>a)
                    max = b;
                    else
                    max = a;
                    if(znam==1)
                        check = 0;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = a;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\tg(A)=\\frac{" << chisl << "}{" << znam << "}$, $BC=" << b << "$. Найдите $AC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 17:
                do{
                    b =rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    check = 1;
                    a = b*chisl/znam;
                    if((a-static_cast<int>(a))!=0)
                        check = 0;
                        if(b>a)
                    max = b;
                    else
                    max = a;
                    if(znam==1)
                        check = 0;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = a;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\tg(B)=\\frac{" << chisl << "}{" << znam << "}$, $BC=" << b << "$. Найдите $AC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 18:
                do{
                    a =rand()%90+9;
                    znam = rand()%20+1;
                    chisl = rand()%20 +1;
                    nod = NOD(znam, chisl);
                    znam = znam/nod;
                    chisl = chisl/nod;
                    check = 1;
                    b = a*znam/chisl;
                    if((b-static_cast<int>(b))!=0)
                        check = 0;
                        if(b>a)
                    max = b;
                    else
                    max = a;
                    if(znam==1)
                        check = 0;
                    k=max/2.2;
                    if(b/k<1)
                        check = 0;
                    if(a/k<1)
                        check = 0;
                }while(check!=1);
                answer = b;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\tg(B)=\\frac{" << chisl << "}{" << znam << "}$, $AC=" << a << "$. Найдите $BC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;


            }
            return Answer;
}

string Parallelogramm(int i, int AllType)
{
            int type;
            string Answer;
            double alpha, betta;
            double a, b, c, h, max, k, l, h1, h2, S;
            double answer;
            int check = 0;
            if(AllType == 0)
                type = rand()%15 + 1;
            else
                type = AllType;
            switch(type)
            {
            case 1:
                do{
                        a = rand()%50 + 2;
                        alpha = rand()%40 + 5;
                        betta = rand()%40 + 5;
                        h = a*sin((PI*(alpha+betta))/180);
                        c = h/sin((PI*alpha)/180);
                        b = (c*cos((PI*alpha)/180)) - (a*cos((PI*(alpha+betta))/180));
                        answer = 180 - alpha - betta;
                        check = 1;
                        if(alpha<20)
                            check = 0;
                        if(betta<20)
                            check = 0;
                        if(a>b)
                            max = a;
                        else
                            max = b;
                        k=max/2.2;
                        if(alpha+betta>80)
                            check = 0;
                }while(check!=1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Диагональ $AC$ параллелограмма $ABCD$ образует с его сторонами углы, равные $" << alpha << "^{\\circ}$ и $" << betta << "^{\\circ}$. Найдите больший угол этого параллелограмма. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$A$]   (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << (alpha+betta) << ":" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << alpha << ":" << (c/k) << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (" << 0 << ":" << (b/k) << ");" << endl
                    << "            \\tkzMarkAngle[mark=,arc=ll,size=0.7](D,A,C);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.7](C,A,B);" << endl
                    << "            \\tkzLabelAngle[pos=1](D,A,C) {$\\alpha$};" << endl
                    << "            \\tkzLabelAngle[pos=1](C,A,B) {$\\beta$};" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;
                
            case 2:
                do{
                        a = rand()%50 + 2;
                        alpha = rand()%40 + 5;
                        betta = rand()%40 + 5;
                        h = a*sin((PI*(alpha+betta))/180);
                        c = h/sin((PI*alpha)/180);
                        b = (c*cos((PI*alpha)/180)) - (a*cos((PI*(alpha+betta))/180));
                        answer = 180 - alpha - betta;
                        l = sqrt(pow(h,2) + pow((b-a*cos((PI*(alpha+betta))/180)),2));
                        check = 1;
                        if(alpha<20)
                            check = 0;
                        if(betta<20)
                            check = 0;
                        if(a>b)
                            max = a;
                        else
                            max = b;
                        k=max/2.2;
                        if(b/k<1.5)
                            check = 0;
                        if(alpha+betta>80)
                            check = 0;
                }while(check!=1);
                answer = (static_cast<double>(static_cast<int>(l)))/2;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Диагонали $AC$ и $BD$ параллелограмма $ABCD$ пересекаются в точке $O$, $AC=" << static_cast<int>(c) << "$, $BD=" << static_cast<int>(l) << "$, $AB=" << a << "$. Найдите $DO$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$A$]   (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << (alpha+betta) << ":" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << alpha << ":" << (c/k) << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (" << 0 << ":" << (b/k) << ");" << endl
                    << "            \\coordinate[label=left:$O$] (O) at (" << alpha << ":" << (c/(2*k)) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                do{
                        a = rand()%50 + 2;
                        alpha = rand()%90 + 5;
                        betta = rand()%90 + 5;
                        h = a*sin((PI*(alpha+betta))/180);
                        c = h/sin((PI*betta)/180);
                        b = (c*cos((PI*betta)/180)) - (a*cos((PI*(alpha+betta))/180));
                        answer = 180 - alpha - betta;
                        l = sqrt(pow(h,2) + pow((b-a*cos((PI*(alpha+betta))/180)),2));
                        check = 1;
                        if(alpha<20)
                            check = 0;
                        if(betta<20)
                            check = 0;
                        if(a>b)
                            max = a;
                        else
                            max = b;
                        k=max/2.2;
                        if(b/k<1.5)
                            check = 0;
                        if(c/k<1)
                            check = 0;
                        if(alpha+betta<100)
                            check = 0;
                }while(check!=1);
                answer = 180 - alpha - betta;
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Диагональ $BD$ параллелограмма $ABCD$ образует с его сторонами углы, равные $" << alpha << "^{\\circ}$ и $" << betta << "^{\\circ}$. Найдите меньший угол этого параллелограмма. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (0:" << (b/k) << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (-" << betta << ":" << (c/k) << ");" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (-" << (alpha+betta) << ":" << (a/k) << ");" << endl
                    << "            \\tkzMarkAngle[mark=,arc=ll,size=0.5](D,B,C);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](A,B,D);" << endl
                    << "            \\tkzLabelAngle[pos=0.8](D,B,C) {$\\alpha$};" << endl
                    << "            \\tkzLabelAngle[pos=0.8](A,B,D) {$\\beta$};" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (D);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:
                do{
                            a = rand()%50 + 2;
                            alpha = rand()%90 + 5;
                            betta = rand()%90 + 5;
                            h = a*sin((PI*(alpha+betta))/180);
                            c = h/sin((PI*betta)/180);
                            b = (c*cos((PI*betta)/180)) - (a*cos((PI*(alpha+betta))/180));
                            answer = 180 - alpha - betta;
                            l = sqrt(pow(h,2) + pow((b-a*cos((PI*(alpha+betta))/180)),2));
                            check = 1;
                            if(alpha<20)
                                check = 0;
                            if(betta<20)
                                check = 0;
                            if(a>b)
                                max = a;
                            else
                                max = b;
                            k=max/2.2;
                            if(b/k<1.5)
                                check = 0;
                            if(c/k<1)
                                check = 0;
                            if((alpha+betta)!=90)
                                check = 0;
                    }while(check!=1);
                    if(2*betta<90)
                        answer = 2*betta;
                    else
                        answer = 180 - 2*betta;
                    cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        Диагональ прямоугольника образует угол $" << betta << "^{\\circ}$ с одной из его сторон. Найдите острый угол между диагоналями этого прямоугольника. Ответ дайте в градусах." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                        << "            \\coordinate (B) at (0,0);" << endl
                        << "            \\coordinate (C) at (0:" << (b/k) << ");" << endl
                        << "            \\coordinate (D) at (-" << betta << ":" << (c/k) << ");" << endl
                        << "            \\coordinate (A) at (-" << (alpha+betta) << ":" << (a/k) << ");" << endl
                        << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                        cout << "\\end{tikzpicture}" << endl << endl;
                    //cout << answer << endl;
                    Answer = "  \\item " + FormatDouble(answer) + " \n";
                    break;

                case 5:
                    do{
                        a = rand()%50+2;
                        alpha = rand()%80+2;
                        check = 1;
                        answer = (180-alpha)/2;
                        c = 2*a*sin((PI*answer)/180);
                        if(alpha<20)
                            check = 0;
                        k = a/2.2;
                    }while(check!=1);
                    cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        В ромбе $ABCD$ угол $ABC$ равен $" << alpha << "^{\\circ}$. Найдите угол $ACD$. Ответ дайте в градусах." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                        << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                        << "            \\coordinate[label=above:$C$] (C) at (0:" << (a/k) << ");" << endl
                        << "            \\coordinate[label=below:$D$] (D) at (-" << (alpha/2) << ":" << (c/k) << ");" << endl
                        << "            \\coordinate[label=below:$A$] (A) at (-" << (alpha) << ":" << (a/k) << ");" << endl
                        << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl;
                        cout << "\\end{tikzpicture}" << endl << endl;
                    //cout << answer << endl;
                    Answer = "  \\item " + FormatDouble(answer) + " \n";
                    break;

                case 6:
                    do{
                        a = rand()%50 + 2;
                        alpha = rand()%40 + 5;
                        betta = rand()%40 + 5;
                        h = a*sin((PI*(alpha+betta))/180);
                        c = h/sin((PI*alpha)/180);
                        b = (c*cos((PI*alpha)/180)) - (a*cos((PI*(alpha+betta))/180));
                        answer = 180 - alpha - betta;
                        check = 1;
                        if(alpha<20)
                            check = 0;
                        if(betta<20)
                            check = 0;
                        if(a>b)
                            max = a;
                        else
                            max = b;
                        k=max/2.2;
                        if(alpha+betta>80)
                            check = 0;
                }while(check!=1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Один из углов параллелограмма равен $" << (alpha+betta) << "^{\\circ}$. Найдите больший угол этого параллелограмма. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate   (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (" << (alpha+betta) << ":" << (a/k) << ");" << endl
                    << "            \\coordinate (C) at (" << alpha << ":" << (c/k) << ");" << endl
                    << "            \\coordinate(D) at (" << 0 << ":" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 7:
                do{
                    a = rand()%50 + 2;
                    b = rand()%50 + 2;
                    alpha = rand()%40 + 5;
                    h = a*sin((PI*alpha)/180);
                    c = sqrt(pow(h,2)+pow((b+a*cos((PI*alpha)/180)),2));
                    l=h/sin((PI*alpha)/360);
                    check = 1;
                    if(alpha<20)
                        check = 0;
                    answer = alpha;
                    if(a>b)
                        k = a/2.2;
                    else
                        k = b/2.2;
                    if((l*cos((PI*alpha)/360))/k>((b+a*cos((PI*alpha)/180))/k)-0.3)
                        check = 0;
                    if((h/k)<0.8)
                        check = 0;
                }while(check!=1);
                cout << "%" << (i+1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Найдите острый угол параллелограмма $ABCD$, если биссектриса угла $A$ образует со стороной $BC$ угол, равный $" << (alpha/2) << "^{\\circ}$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$A$]  (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << (alpha) << ":" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << ((b+a*cos((alpha*PI)/180))/k) << "," << (h/k) << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (0:" << (b/k) << ");" << endl
                    << "            \\coordinate (O) at (" << (alpha/2) << ":" << (l/k) << ");"
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](O,A,B);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](D,A,O);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (O);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 8:
                    a = rand()%20 + 3;
                    answer = pow(a,2)/2;
                    cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        Периметр ромба равен " << (4*a) << ", а один из углов равен $30^{\\circ}$. Найдите площадь этого ромба." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (30:2.2);" << endl
                    << "            \\coordinate (C) at (" << (2.2+(2.2*cos(PI/6))) << "," << (2.2*sin(PI/6)) << ");" << endl
                    << "            \\coordinate(D) at (0:2.2);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 9:
                   a = rand()%20 + 3;
                    answer = a/2;
                    cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        Сторона ромба равна " << (a) << ", а один из углов равен $150^{\\circ}$. Найдите высоту этого ромба." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (30:2.2);" << endl
                    << "            \\coordinate (C) at (" << (2.2+(2.2*cos(PI/6))) << "," << (2.2*sin(PI/6)) << ");" << endl
                    << "            \\coordinate (D) at (0:2.2);" << endl
                    << "            \\coordinate (O) at (" << (2.2*cos(PI/6)) << ", 0);" << endl
                    << "            \\tkzMarkRightAngle(A,O,B);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (O);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 10:
                do{
                    a = rand()%170 + 4;
                    b = rand()%170 + 4;
                    S = rand()%200 + 9;
                    h1=S/a;
                    h2=S/b;
                    alpha = asin(h1/a);
                    check = 1;
                    if(a>b)
                        k = a/2.2;
                    else
                        k = b/2.2;
                    if(h1-static_cast<int>(h1)!=0)
                        check = 0;
                    if(h2-static_cast<int>(h2)!=0)
                        check = 0;
                    if((h1/k)<0.5)
                        check = 0;
                    if(h1>a)
                        check = 0;
                    if((a*cos(alpha))/k>(b/k)-0.2)
                        check = 0;
                    if((b*cos(alpha))/k>(a/k)-0.1)
                        check = 0;
                    if(sin(alpha)==1)
                        check = 0;
                    if(a==b)
                        check =0;
                }while(check!=1);
                    if(h1>h2)
                        answer = h1;
                    else
                        answer = h2;
                    cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        Площадь параллелограмма равна " << S << ", а две его стороны равны " << a << " и " << b << ". Найдите его высоты. В ответе укажите большую высоту." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (" << ((a*cos(alpha))/k) << ", " << ((a*sin(alpha))/k) << ");" << endl
                    << "            \\coordinate (C) at (" << ((a*cos(alpha)+b)/k) << "," << ((a*sin(alpha))/k) << ");" << endl
                    << "            \\coordinate (D) at (" <<  (b/k) << ",0);" << endl
                    << "            \\coordinate (O1) at (" << (a*cos(alpha)/k) << ", 0);" << endl
                    << "            \\coordinate (O2) at (" << ((b+a*cos(alpha)-(b*pow(cos(alpha),2)))/k) << ", " << ((a*sin(alpha)-(b*sin(alpha)*cos(alpha)))/k) << ");" << endl
                    << "            \\tkzMarkRightAngle(A,O1,B);" << endl
                    << "            \\tkzMarkRightAngle(C,O2,B);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (O1) -- (D) -- (O2) -- (B);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;
            
            case 11:
                a = rand()%20+3;
                answer = a*2;
                cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        Сторона квадрата равна $" << a << "\\sqrt{2}$. Найдите диагональ этого квадрата." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (2,0);" << endl
                    << "            \\coordinate (C) at (2,2);" << endl
                    << "            \\coordinate (D) at (0,2);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 12:
                a = rand()%20+3;
                answer = a;
                cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        Диагональ квадрата равна $" << a << "\\sqrt{2}$. Найдите сторону этого квадрата." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (2,0);" << endl
                    << "            \\coordinate (C) at (2,2);" << endl
                    << "            \\coordinate (D) at (0,2);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 13:
                do{
                    a = rand()%100 + 2;
                    b = rand()%100 + 2;
                    c = sqrt(pow(a,2)+pow(b,2));
                    check = 1;
                    if(c-static_cast<int>(c)!=0)
                        check = 0;
                    h = static_cast<int>(c)%2;
                    if(h!=0)
                        check = 0;
                    answer = c;
                    if(a>b)
                        k=a/2;
                    else    
                        k=b/2;
                    if((a/k)<1)
                        check = 0;
                    if((b/k)<1)
                        check = 0;
                }while(check!=1);
                cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        Диагонали $AC$ и $BD$ прямоугольника $ABCD$ пересекаются в точке $O$, $BO=" << c/2 << "$, $AB=" << a << "$. Найдите $AC$." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (0," << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << (b/k) << "," << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$O$] (O) at (" << (b/k)/2 << "," << (a/k)/2 << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (" << (b/k) << ",0);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                    cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 14:
                do{
                        a = rand()%50+2;
                        alpha = rand()%80+2;
                        check = 1;
                        answer = (180-alpha)/2;
                        c = 2*a*sin((PI*answer)/180);
                        if(alpha<20)
                            check = 0;
                        k = a/2.2;
                        answer = alpha/2;
                    }while(check!=1);
                    cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        В ромбе $ABCD$ угол $BCD$ равен $" << 180 - alpha << "^{\\circ}$. Найдите угол $BCD$. Ответ дайте в градусах." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                        << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                        << "            \\coordinate[label=above:$C$] (C) at (0:" << (a/k) << ");" << endl
                        << "            \\coordinate[label=below:$D$] (D) at (-" << (alpha/2) << ":" << (c/k) << ");" << endl
                        << "            \\coordinate[label=below:$A$] (A) at (-" << (alpha) << ":" << (a/k) << ");" << endl
                        << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (D);" << endl;
                        cout << "\\end{tikzpicture}" << endl << endl;
                    //cout << answer << endl;
                    Answer = "  \\item " + FormatDouble(answer) + " \n";
                    break;

            case 15:
                do{
                    a = rand()%20 + 2;
                    b = rand()%20 + 2;
                    h = rand()%20 + 2;
                    c = sqrt(pow(a,2) + pow(h,2));
                    check = 1;
                    if(c-static_cast<int>(c)!=0)
                        check = 0;
                    if((a+b)>c)
                        k = (a+b)/2.5;
                    else
                        k = c/2.5;
                    if(h/k<1)
                        check = 0;
                }while(check!=1);
                answer = (a+b)*h;
                cout << "%" << (i+1) << endl;
                    cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                    cout << "        Найдите площадь параллелограмма, изображенного на рисунке." << endl;
                    cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                        << "        \\coordinate (O) at (" << a/k << ",0);" << endl
                        << "        \\coordinate (A) at (0,0);" << endl
                        << "        \\coordinate (B) at (" << (a/k) << ", " << (h/k) << ");" << endl
                        << "        \\coordinate (C) at (" << (2*a + b)/k << ", " << (h/k) << ");" << endl
                        << "        \\coordinate (D) at (" << (a+b)/k << ",0);" << endl
                        << "        \\coordinate[label=below:$" << a << "$] (Q1) at (" << (a*0.5)/k << ",0);" << endl
                        << "        \\coordinate[label=below:$" << b << "$] (Q2) at (" << (a+b*0.5)/k << ",0);" << endl
                        << "        \\coordinate[label=right:$" << h << "$] (Q3) at (" << a/k << "," << (h*0.5)/k << ");" << endl
                        << "        \\coordinate[label=left:$" << c << "$] (Q4) at (" << (a*0.5)/k << "," << (h*0.5)/k << ");" << endl
                        << "        \\tkzMarkRightAngle(B,O,D);" << endl
                        << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (O) -- (B);" << endl;
                        cout << "\\end{tikzpicture}" << endl << endl;
                    //cout << answer << endl;
                    Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            }
            return Answer;
}

string Trapet(int i, int AllType)
{
            int type;
            string Answer;
            double alpha, betta;
            double a, b, c, h, max, k, l, h1, h2, S;
            double answer;
            int check = 0;
            if(AllType == 0)
                type = rand()%10 + 1;
            else
                type = AllType;
            switch (type)
            {
            case 1:
                do {
                    a = rand() % 50 + 2;
                    alpha = rand() % 70 + 2;
                    b = a / tan((PI * alpha) / 180);
                    answer = 180 - alpha;
                    check = 1;
                    k = (a + b) / 2.2;
                    if (a / k < 1)
                        check = 0;
                } while (check != 1);
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Один из углов прямоугольной трапеции равен $" << alpha << "^{\\circ}$. Найдите больший угол этой трапеции. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (0," << (a / k) << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << (a / k) << ");" << endl
                    << "            \\coordinate (D) at (" << ((a + b) / k) << ",0);" << endl
                    << "            \\tkzMarkRightAngle(B,A,D);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                do {
                    a = rand() % 100 + 2;
                    b = rand() % 100 + 2;
                    k = (2 * a + 2 * b) / 4;
                    check = 1;
                    if (b / k < 1)
                        check = 0;
                    if (2 * a < 1)
                        check = 0;
                } while (check != 1);
                answer = 2 * (a + b);
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В равнобедренной трапеции известны высота, меньшее основание и угол при основании (см.рисунок). Найдите большее основание." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (-" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (B) at (-" << a / k << "," << (b / k) << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << (b / k) << ");" << endl
                    << "            \\coordinate (D) at (" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (O) at (-" << a / k << ",0);" << endl
                    << "            \\coordinate[label=right:$" << b << "$] (O1) at (-" << (a / k) << "," << (b / (2 * k)) << ");" << endl
                    << "            \\coordinate[label=above:$" << (2 * a) << "$] (O2) at (0," << (b / k) << ");" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.3](D,A,B);" << endl
                    << "            \\tkzLabelAngle[pos=1](D,A,B) {$45^{\\circ}$};" << endl
                    << "            \\tkzMarkRightAngle(B,O,D);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (O);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                do {
                    a = rand() % 50 + 2;
                    b = rand() % 50 + 2;
                    k = (2 * a + 2 * b) / 4;
                    check = 1;
                    if (b / k < 1)
                        check = 0;
                    if (2 * a < 1)
                        check = 0;
                } while (check != 1);
                answer = 2 * a;
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В равнобедренной трапеции известны высота, большее основание и угол при основании (см.рисунок). Найдите меньшее основание." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (-" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (B) at (-" << a / k << "," << (b / k) << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << (b / k) << ");" << endl
                    << "            \\coordinate (D) at (" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (O) at (-" << a / k << ",0);" << endl
                    << "            \\coordinate[label=right:$" << b << "$] (O1) at (-" << (a / k) << "," << (b / (2 * k)) << ");" << endl
                    << "            \\coordinate[label=below:$" << (2 * a + 2 * b) << "$] (O2) at (0,0);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.3](D,A,B);" << endl
                    << "            \\tkzLabelAngle[pos=1](D,A,B) {$45^{\\circ}$};" << endl
                    << "            \\tkzMarkRightAngle(B,O,D);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (O);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:
                do {
                    a = rand() % 50 + 2;
                    b = rand() % 50 + 2;
                    h = rand() % 10 + 2;
                    h1 = rand() % 50 + 2;
                    check = 1;
                    if (a > b)
                        check = 0;
                    if (h > a)
                        check = 0;
                    if ((h + a) > b)
                        check = 0;
                    answer = a + b;
                    k = 2 * b / 3;
                    if ((h1 / k < 1)||(h1/k>2))
                        check = 0;
                } while (check != 1);
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Основания трапеции равны " << 2*a << " и " << 2*b << ", а высота равна " << h1 << ". Найдите среднюю линию этой трапеции." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (-" << b / k << ",0);" << endl
                    << "            \\coordinate (B) at (-" << (a - h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate (C) at (" << (a + h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate (D) at (" << b / k << ",0);" << endl
                    << "            \\coordinate (O) at (-" << (a - h) / k << ",0);" << endl
                    << "            \\coordinate (N) at (-" << (b + a - h) / (2 * k) << "," << h1 / (2 * k) << ");" << endl
                    << "            \\coordinate (M) at (" << (b + a + h) / (2 * k) << "," << h1 / (2 * k) << ");" << endl
                    << "            \\tkzMarkRightAngle(B,O,A);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl
                    << "            \\draw[thick] (B) -- (O);" << endl
                    << "            \\draw[thick] (N) -- (M);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 5:
                do {
                    a = rand() % 50 + 2;
                    b = rand() % 50 + 2;
                    h = rand() % 10 + 2;
                    h1 = rand() % 50 + 2;
                    check = 1;
                    if (a > b)
                        check = 0;
                    if (h > a)
                        check = 0;
                    if ((h + a) > b)
                        check = 0;
                    answer = b;
                    k = 2 * b / 3;
                    if ((h1 / k < 1) || (h1 / k > 2))
                        check = 0;
                } while (check != 1);
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Основания трапеции равны " << 2 * a << " и " << 2 * b << ". Найдите больший из отрезков, на которые делит среднюю линию этой трапеции одна из ее диагоналей." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (-" << b / k << ",0);" << endl
                    << "            \\coordinate (B) at (-" << (a - h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate (C) at (" << (a + h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate (D) at (" << b / k << ",0);" << endl
                    << "            \\coordinate (O) at (-" << (a - h) / k << ",0);" << endl
                    << "            \\coordinate (N) at (-" << (b + a - h) / (2 * k) << "," << h1 / (2 * k) << ");" << endl
                    << "            \\coordinate (M) at (" << (b + a + h) / (2 * k) << "," << h1 / (2 * k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl
                    << "            \\draw[thick] (N) -- (M);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 6:
                do {
                    a = rand() % 50 + 2;
                    b = rand() % 50 + 2;
                    h = 0; // Сдвиг меньшего основания
                    h1 = rand() % 50 + 2;
                    check = 1;
                    if (a > b)
                        check = 0;
                    if (h > a)
                        check = 0;
                    if ((h + a) > b)
                        check = 0;
                    answer = 2*a;
                    k = 2 * b / 3;
                    if ((h1 / k < 1) || (h1 / k > 2))
                        check = 0;
                    if (2 * a / k < 0.5)
                        check = 0;
                    if ((b - a)/k < 0.5)
                        check = 0;
                } while (check != 1);
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Высота равнобедренной трапеции, проведенная из вершины $C$, делит основание $AD$ на отрезки длиной $" << (b-a) << "$ и $" << (a+b) << "$. Найдите длину основания $BC$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (-" << b / k << ",0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (-" << (a - h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << (a + h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (" << b / k << ",0);" << endl
                    << "            \\coordinate (O) at (" << (a - h) / k << ",0);" << endl
                    << "            \\tkzMarkRightAngle(D,O,C);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl
                    << "            \\draw[thick] (C) -- (O);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 7:
                do {
                    a = rand() % 50 + 2;
                    alpha = rand() % 80 + 2;
                    h = 0; // Сдвиг меньшего основания
                    h1 = rand() % 50 + 2;
                    b = h1 / tan((PI * alpha) / 180);
                    check = 1;
                    if (alpha < 15)
                        check = 0;
                    answer = 180 - alpha;
                    k = 2 * (a+b) / 3;
                    if ((h1 / k < 1) || (h1 / k > 2))
                        check = 0;
                    if (2 * a / k < 0.5)
                        check = 0;
                    if (b / k < 0.5)
                        check = 0;
                } while (check != 1);
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Один из углов равнобедренной трапеции равен $" << alpha << "^{\\circ}$. Найдите больший угол этой трапеции. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (-" << (a+b) / k << ",0);" << endl
                    << "            \\coordinate (B) at (-" << (a / k) << "," << h1 / k << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << h1 / k << ");" << endl
                    << "            \\coordinate (D) at (" << (a + b) / k << ",0);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 8:
                do {
                    a = rand() % 50 + 2;
                    alpha = rand() % 80 + 2;
                    h = 0; // Сдвиг меньшего основания
                    h1 = rand() % 50 + 2;
                    b = h1 / tan((PI * alpha) / 180);
                    check = 1;
                    if (alpha < 15)
                        check = 0;
                    answer = 180 - alpha;
                    k = 2 * (a + b) / 3;
                    if ((h1 / k < 1) || (h1 / k > 2))
                        check = 0;
                    if (2 * a / k < 0.5)
                        check = 0;
                    if (b / k < 0.5)
                        check = 0;
                } while (check != 1);
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Сумма двух углов равнобедренной трапеции равна $" << 2*alpha << "^{\\circ}$. Найдите больший угол этой трапеции. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (-" << (a + b) / k << ",0);" << endl
                    << "            \\coordinate (B) at (-" << (a / k) << "," << h1 / k << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << h1 / k << ");" << endl
                    << "            \\coordinate (D) at (" << (a + b) / k << ",0);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 9:
                do {
                    a = rand() % 50 + 2;
                    b = rand() % 50 + 2;
                    h = rand() % 10 + 2;
                    h1 = rand() % 50 + 2;
                    check = 1;
                    if (a > b)
                        check = 0;
                    if (h > a)
                        check = 0;
                    if ((h + a) > b)
                        check = 0;
                    answer = a + b;
                    k = 2 * b / 3;
                    if ((h1 / k < 1)||(h1/k>2))
                        check = 0;
                } while (check != 1);
                answer = h1*(a+b);
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Основания трапеции равны " << 2*a << " и " << 2*b << ", а высота равна " << h1 << ". Найдите площадь этой трапеции." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (-" << b / k << ",0);" << endl
                    << "            \\coordinate (B) at (-" << (a - h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate (C) at (" << (a + h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate (D) at (" << b / k << ",0);" << endl
                    << "            \\coordinate (O) at (-" << (a - h) / k << ",0);" << endl
                    << "            \\coordinate (N) at (-" << (b + a - h) / (2 * k) << "," << h1 / (2 * k) << ");" << endl
                    << "            \\coordinate (M) at (" << (b + a + h) / (2 * k) << "," << h1 / (2 * k) << ");" << endl
                    << "            \\tkzMarkRightAngle(B,O,A);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl
                    << "            \\draw[thick] (B) -- (O);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 10:
                do {
                    a = rand() % 50 + 2;
                    b = rand() % 50 + 2;
                    k = (2 * a + 2 * b) / 4;
                    check = 1;
                    if (b / k < 1)
                        check = 0;
                    if (2 * a < 1)
                        check = 0;
                } while (check != 1);
                answer = (2*a + 2*b + 2*a)*b/2;
                cout << "%" << (i + 1) << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В равнобедренной трапеции известны высота, большее основание и угол при основании (см.рисунок). Найдите меньшее основание." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (-" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (B) at (-" << a / k << "," << (b / k) << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << (b / k) << ");" << endl
                    << "            \\coordinate (D) at (" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (O) at (-" << a / k << ",0);" << endl
                    << "            \\coordinate[label=above:$" << 2*a << "$] (O1) at (0," << (b / k) << ");" << endl
                    << "            \\coordinate[label=below:$" << (2 * a + 2 * b) << "$] (O2) at (0,0);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.3](D,A,B);" << endl
                    << "            \\tkzLabelAngle[pos=1](D,A,B) {$45^{\\circ}$};" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;
            }
            return Answer;
}

string MnogougReshotka(int i, int AllType)
{
            int type;
            double xmax, ymax, x, y, delta1, delta2, x1;
            string Answer;
            double answer;
            int check = 0;
            if(AllType == 0)
                type = rand()%5+1;
            else
                type = AllType;
            switch (type)
            {
            case 1:
                do {
                    xmax = rand() % 5 + 1;
                    ymax = rand() % 4 + 1;
                    check = 1;
                    if (ymax < 3)
                        check = 0;
                    if (xmax < 3)
                        check = 0;
                    y = 2 * (ymax - 1);
                    x = 2 * (xmax - 1);
                    if (y > x)
                        answer = y;
                    else
                        answer = x;
                } while (check != 1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен ромб. Найдите длину его большей диагонали. " << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5," << ymax/2 << ");" << endl
                    << "            \\coordinate (B) at (" << xmax/2 << "," << ymax-0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << xmax-0.5 << "," << ymax/2 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax/2 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                do {
                    xmax = rand() % 5 + 1;
                    ymax = rand() % 4 + 1;
                    check = 1;
                    if (ymax < 3)
                        check = 0;
                    if (xmax < 3)
                        check = 0;
                    y = 2 * (ymax - 1);
                    x = 2 * (xmax - 1);
                    answer = x * y / 2;
                } while (check != 1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен ромб. Найдите площадь этого ромба. " << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5," << ymax / 2 << ");" << endl
                    << "            \\coordinate (B) at (" << xmax / 2 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << xmax - 0.5 << "," << ymax / 2 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax / 2 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                do {
                    xmax = rand() % 5 + 1;
                    ymax = rand() % 4 + 1;
                    delta1 = rand() % 2 + 1;
                    delta2 = rand() % 2 + 1;
                    check = 1;
                    if (ymax < 3)
                        check = 0;
                    if (xmax < 3)
                        check = 0;
                    y = 2 * (ymax - 1);
                    x = 2 * (xmax - 1);
                    if ((delta1 + delta2) == x)
                        check = 0;
                    answer = (delta1 +delta2 + x)/2;
                } while (check != 1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображена трапеция. Найдите длину её средней линии. " << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5,0.5);" << endl
                    << "            \\coordinate (B) at (" << (xmax-delta1) / 2 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << (xmax + delta2) / 2 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax-0.5 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:
                do {
                    xmax = rand() % 5 + 1;
                    ymax = rand() % 4 + 1;
                    delta1 = rand() % 3 + 2;
                    check = 1;
                    if (ymax < 3)
                        check = 0;
                    if (xmax < 3)
                        check = 0;
                    y = 2 * (ymax - 1);
                    x = 2 * (xmax - 0.5 - 0.5*delta1);
                    answer = x*y;
                } while (check != 1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен параллелограмм. Найдите его площадь." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5,0.5);" << endl
                    << "            \\coordinate (B) at (" << (delta1*0.5) << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << xmax - 0.5 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax-0.5*delta1 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 5:
                do {
                    xmax = rand() % 5 + 1;
                    ymax = rand() % 4 + 1;
                    delta1 = rand() % 4 + 1;
                    delta2 = rand() % 4 + 1;
                    check = 1;
                    if (ymax < 3)
                        check = 0;
                    if (xmax < 3)
                        check = 0;
                    y = 2 * (ymax - 1);
                    x = 2 * (xmax - 1);
                    x1 = 2*(xmax - 0.5*delta1 - 0.5*delta2);
                    answer = y*(x+x1)/2;
                    if((delta1==1)&&(delta2==1))
                        check = 0;
                    if(0.5*(delta1+delta2)==xmax)
                        check = 0;
                } while (check != 1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображена трапеция. Найдите её площадь." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5,0.5);" << endl
                    << "            \\coordinate (B) at (" << (delta1*0.5) << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << xmax - 0.5*delta2 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax - 0.5 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;
            }
            return Answer;
}

string Okrugn(int i, int AllType)
{
    double r, R, a, alpha[4], change, k, l[4], side[4], betta[4], max;
            double answer;
            string Answer;
            int check = 0;
            int type;
            if(AllType == 0)
                type = rand()%14 + 1;
            else
                type = AllType;
            switch (type)
            {
            case 1:
                a = rand() % 15 + 2;
                answer = a;
                R = 1.5;
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Сторона квадрата равна $" << a << "\\sqrt{2}$. Найдите радиус окружности, описанной около этого квадрата." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 2:
                a = rand() % 15 + 2;
                answer = pow(2*a,2);
                R = 1.5;
                r = R / sqrt(2);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Найдите площадь квадрата, описанного около окружности радиуса " << a << "." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[fill=black] (0,0) circle(1pt);" << endl
                    << "            \\draw[thick] (0,0) circle(" << r << ");" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 3:
                a = rand() % 30 + 2;
                answer = a/2;
                R = 1.5;
                r = R / sqrt(2);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Сторона квадрата равна " << a << ". Найдите радиус окружности, вписанной в этот квадрат." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[fill=black] (0,0) circle(1pt);" << endl
                    << "            \\draw[thick] (0,0) circle(" << r << ");" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 4:
                a = rand() % 15 + 2;
                answer = 2*a;
                R = 1.5;
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Радиус окружности, описанной около квадрата, равен $" << a << "\\sqrt{2}$. Найдите длину стороны этого квадрата." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[fill=black] (0,0) circle(1pt);" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 5:
                a = rand() % 20 + 2;
                answer = 4*a;
                R = 1.5;
                r = R / sqrt(2);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Радиус вписанной в квадрат окружности равен $" << a << "\\sqrt{2}$. Найдите диагональ этого квадрата." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[fill=black] (0,0) circle(1pt);" << endl
                    << "            \\draw[thick] (0,0) circle(" << r << ");" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
               // cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 6:
                do{
                    max = 0;
                    R = rand()%50 + 2;
                    for(int i=0; i<4; i++)
                        alpha[i] = rand()%361;
                    
                    for(int i = 0; i<3; i++)
                    {
                        for(int m = i+1; m<4; m++)
                        {
                            if(alpha[i]>alpha[m])
                            {
                                change = alpha[i];
                                alpha[i] = alpha[m];
                                alpha[m] = change;
                            }
                        }
                    }
                    check = 1;

                    betta[0] = 360 + alpha[0] - alpha[3];
                    betta[1] = alpha[1] - alpha[0];
                    betta[2] = alpha[2] - alpha[1];
                    betta[3] = alpha[3] - alpha[2];

                    for(int i=0; i<4; i++)
                        l[i] = R/cos((betta[i]*PI)/360);

                    side[0] = static_cast<int>(l[0]*sin((PI*betta[0])/360) + l[1]*sin((PI*betta[1])/360));
                    side[1] = static_cast<int>(l[1]*sin((PI*betta[1])/360) + l[2]*sin((PI*betta[1])/360));
                    side[2] = static_cast<int>(l[2]*sin((PI*betta[2])/360) + l[3]*sin((PI*betta[1])/360));
                    side[3] = static_cast<int>(l[3]*sin((PI*betta[3])/360) + l[0]*sin((PI*betta[1])/360));

                    for(int i=0; i<4; i++)
                    {
                        if(side[i]>max)
                            max = side[i];
                    }

                    k=max/3;
                    answer = side[2] + side[0] - side[1];
 

                    if((alpha[1]-alpha[0]<20)||(alpha[2]-alpha[1]<20)||(alpha[3]-alpha[2]<20)||(360 + alpha[0]-alpha[3]<20))
                        check = 0;

                    if((betta[0]/2>90)||(betta[1]/2>90)||(betta[2]/2>90)||(betta[3]/2>90))
                        check = 0;

                    if((R/k<0.7)||(R/k)>1)
                        check = 0;
                    if((l[0]/k>4)||(l[1]/k>4)||(l[2]/k>4)||(l[3]/k>4))
                        check = 0;
                    if(alpha[0]+betta[1]/2<80)
                        check = 0;

                }while(check!=1);
                cout << "%" << i + 1 << endl;

                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Четырехугольник $ABCD$ описан около окружности, $AB=" << side[2] << "$, $BC=" << side[1] << "$, $CD=" << side[0] << "$. Найдите $AD$." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << R/k << ");" << endl
                    << "            \\coordinate[label=left:$C$] (C) at (" << (alpha[0]+(betta[1]/2)) << ":" << l[1]/k << ");" << endl
                    << "            \\coordinate[label=left:$B$] (B) at (" << (alpha[1]+(betta[2]/2)) << ":" << l[2]/k << ");" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (" << (alpha[2]+(betta[3]/2)) << ":" << l[3]/k << ");" << endl
                    << "            \\coordinate[label=right:$D$] (D) at (" << (alpha[3]+(betta[0]/2)) << ":" << l[0]/k << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 7:
                do{
                    max = 0;
                    R = rand()%50 + 2;
                    alpha[1] = 90;
                    alpha[3] = 270;
                    alpha[0] = rand()%70+2;
                    alpha[2] = 180 - alpha[0];
                    
                    
                    for(int i = 0; i<3; i++)
                    {
                        for(int m = i+1; m<4; m++)
                        {
                            if(alpha[i]>alpha[m])
                            {
                                change = alpha[i];
                                alpha[i] = alpha[m];
                                alpha[m] = change;
                            }
                        }
                    }
                    check = 1;

                    betta[0] = 360 + alpha[0] - alpha[3];
                    betta[1] = alpha[1] - alpha[0];
                    betta[2] = alpha[2] - alpha[1];
                    betta[3] = alpha[3] - alpha[2];

                    for(int i=0; i<4; i++)
                        l[i] = R/cos((betta[i]*PI)/360);

                    side[0] = static_cast<int>(l[0]*sin((PI*betta[0])/360) + l[1]*sin((PI*betta[1])/360));
                    side[1] = static_cast<int>(l[1]*sin((PI*betta[1])/360) + l[2]*sin((PI*betta[1])/360));
                    side[2] = static_cast<int>(l[2]*sin((PI*betta[2])/360) + l[3]*sin((PI*betta[1])/360));
                    side[3] = static_cast<int>(l[3]*sin((PI*betta[3])/360) + l[0]*sin((PI*betta[1])/360));

                    for(int i=0; i<4; i++)
                    {
                        if(side[i]>max)
                            max = side[i];
                    }

                    k=max/3;
                    answer = 2*R;
 

                    if((R/k<0.7)||(R/k)>1)
                        check = 0;
                    if((l[0]/k>4)||(l[1]/k>4)||(l[2]/k>4)||(l[3]/k>4))
                        check = 0;

                }while(check!=1);
                cout << "%" << i + 1 << endl;

                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Радиус окружности, вписанной в равнобедренную трапецию, равен " << R << ". Найдите высоту этой трапеции." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << R/k << ");" << endl
                    << "            \\coordinate (C) at (" << (alpha[0]+(betta[1]/2)) << ":" << l[1]/k << ");" << endl
                    << "            \\coordinate (B) at (" << (alpha[1]+(betta[2]/2)) << ":" << l[2]/k << ");" << endl
                    << "            \\coordinate (A) at (" << (alpha[2]+(betta[3]/2)) << ":" << l[3]/k << ");" << endl
                    << "            \\coordinate (D) at (" << (alpha[3]+(betta[0]/2)) << ":" << l[0]/k << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 8:
                do{
                    max = 0;
                    R = rand()%50 + 2;
                    alpha[1] = 90;
                    alpha[3] = 270;
                    alpha[0] = rand()%70+2;
                    alpha[2] = 180 - alpha[0];
                    alpha[0] = 0;
                    
                    
                    for(int i = 0; i<3; i++)
                    {
                        for(int m = i+1; m<4; m++)
                        {
                            if(alpha[i]>alpha[m])
                            {
                                change = alpha[i];
                                alpha[i] = alpha[m];
                                alpha[m] = change;
                            }
                        }
                    }
                    check = 1;

                    betta[0] = 360 + alpha[0] - alpha[3];
                    betta[1] = alpha[1] - alpha[0];
                    betta[2] = alpha[2] - alpha[1];
                    betta[3] = alpha[3] - alpha[2];

                    for(int i=0; i<4; i++)
                        l[i] = R/cos((betta[i]*PI)/360);

                    side[0] = static_cast<int>(l[0]*sin((PI*betta[0])/360) + l[1]*sin((PI*betta[1])/360));
                    side[1] = static_cast<int>(l[1]*sin((PI*betta[1])/360) + l[2]*sin((PI*betta[1])/360));
                    side[2] = static_cast<int>(l[2]*sin((PI*betta[2])/360) + l[3]*sin((PI*betta[1])/360));
                    side[3] = static_cast<int>(l[3]*sin((PI*betta[3])/360) + l[0]*sin((PI*betta[1])/360));

                    for(int i=0; i<4; i++)
                    {
                        if(side[i]>max)
                            max = side[i];
                    }

                    k=max/3;
                    answer = 2*R;
 

                    if((R/k<0.7)||(R/k)>1)
                        check = 0;
                    if((l[0]/k>4)||(l[1]/k>4)||(l[2]/k>4)||(l[3]/k>4))
                        check = 0;

                }while(check!=1);
                cout << "%" << i + 1 << endl;

                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Радиус окружности, вписанной в прямоугольную трапецию, равен " << R << ". Найдите высоту этой трапеции." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << R/k << ");" << endl
                    << "            \\coordinate (C) at (" << (alpha[0]+(betta[1]/2)) << ":" << l[1]/k << ");" << endl
                    << "            \\coordinate (B) at (" << (alpha[1]+(betta[2]/2)) << ":" << l[2]/k << ");" << endl
                    << "            \\coordinate (A) at (" << (alpha[2]+(betta[3]/2)) << ":" << l[3]/k << ");" << endl
                    << "            \\coordinate (D) at (" << (alpha[3]+(betta[0]/2)) << ":" << l[0]/k << ");" << endl
                    << "            \\tkzMarkRightAngle(A,D,C);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 9:
                do{
                    alpha[0] = rand()%70 +10;
                    betta[0] = rand()%30 +10;
                    r = 1.5;
                    answer = (180 - betta[0] + alpha[0])/2;
                    check = 1;
                    if(alpha[0]==betta[0])
                        check = 0;
                }while(check!=1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Угол $A$ трапеции $ABCD$ с основаниями $AD$ и $BC$, вписанной в окружность, равен $" << (180 - answer) << "^{\\circ}$. Найдите угол $B$ этой трапеции. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << r << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << 180 + betta[0] << ":" << r << ");" << endl
                    << "            \\coordinate[label=above left:$B$] (B) at (" << 180 - alpha[0] << ":" << r << ");" << endl
                    << "            \\coordinate[label=above right:$C$] (C) at (" << alpha[0] << ":" << r << ");" << endl
                    << "            \\coordinate[label=below right:$D$] (D) at (-" <<  betta[0] << ":" << r << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 10:
                do{
                    max = 0;
                    R = 1.5;
                    for(int i=0; i<4; i++)
                        alpha[i] = rand()%361;
                    
                    for(int i = 0; i<3; i++)
                    {
                        for(int m = i+1; m<4; m++)
                        {
                            if(alpha[i]>alpha[m])
                            {
                                change = alpha[i];
                                alpha[i] = alpha[m];
                                alpha[m] = change;
                            }
                        }
                    }
                    betta[2] = (alpha[1]+360-alpha[3])/2;
                    betta[0] = 180 - betta[2];
                    betta[3] = (alpha[2]-alpha[0])/2;
                    betta[1] = 180 - betta[3];
                    check = 1;
                    for(int i=0; i<4; i++)
                    {
                        if(betta[i]<20)
                            check = 0;
                    }
                    if(alpha[1]-alpha[0]<60)
                        check = 0;
                    if(alpha[2]-alpha[1]<60)
                        check = 0;
                    if(alpha[3]-alpha[2]<60)
                        check = 0;
                    if(360-alpha[3]+alpha[0]<60)
                        check = 0;
                    answer = betta[1];
                }while(check!=1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Четырехугольник $ABCD$ вписан в окружность. Угол $ABD$ равен $" << (alpha[3]-alpha[2])/2 << "^{\\circ}$, угол $CAD$ равен $" << (360-alpha[3]+alpha[0])/2 << "^{\\circ}$. Найдите угол $ABC$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above left:$B$] (B) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above right:$C$] (C) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below right:$D$] (D) at (" <<  alpha[3] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 11:
                do{
                    max = 0;
                    R = 1.5;
                    for(int i=0; i<4; i++)
                        alpha[i] = rand()%180;
                    
                    for(int i = 0; i<3; i++)
                    {
                        for(int m = i+1; m<4; m++)
                        {
                            if(alpha[i]>alpha[m])
                            {
                                change = alpha[i];
                                alpha[i] = alpha[m];
                                alpha[m] = change;
                            }
                        }
                    }
                    alpha[2] = alpha[0] + 180;
                    alpha[3] = alpha[1] + 180;
                    betta[2] = (alpha[1]+360-alpha[3])/2;
                    betta[0] = 180 - betta[2];
                    betta[3] = (alpha[2]-alpha[0])/2;
                    betta[1] = 180 - betta[3];
                    check = 1;
                    for(int i=0; i<4; i++)
                    {
                        if(betta[i]<20)
                            check = 0;
                    }
                    if(alpha[1]-alpha[0]<90)
                        check = 0;
                    answer = (alpha[2] - alpha[1])/2;
                }while(check!=1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        В окружности с центром в точке $O$ отрезки $AC$ и $BD$ -- диаметры. Угол $AOD$ равен $" << (alpha[3] - alpha[2]) << "^{\\circ}$. Найдите угол $ACB$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=below:$O$] (O) at(0,0);" << endl
                    << "            \\draw[fill=black] (O) circle(1pt);" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above left:$B$] (B) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above right:$C$] (C) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below right:$D$] (D) at (" <<  alpha[3] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (C) -- (B) -- (D);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 12:
                do{
                    max = 0;
                    R = 1.5;
                    alpha[0] = 0;
                    alpha[2] = 180;
                    alpha[1] = rand()%110+40;
                    alpha[3] = rand()%80 + 220;
                    betta[2] = (alpha[1]+360-alpha[3])/2;
                    betta[0] = 180 - betta[2];
                    betta[3] = (alpha[2]-alpha[0])/2;
                    betta[1] = 180 - betta[3];
                    check = 1;
                    for(int i=0; i<4; i++)
                    {
                        if(betta[i]<20)
                            check = 0;
                    }
                    if(alpha[1]-alpha[0]<90)
                        check = 0;
                    answer = 90 - (180-alpha[1])/2;
                }while(check!=1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        На окружности по разные стороны от диаметра $AB$ взяты точки $M$ и $N$. Известно, что угол $NBA=" << (180-alpha[1])/2 << "^{\\circ}$. Найдите угол $NMB$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=left:$A$] (A) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above left:$N$] (N) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=right:$B$] (B) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below right:$M$] (M) at (" <<  alpha[3] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (N) -- (M) -- (B);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 13:
                do{
                    max = 0;
                    R = 1.5;
                    alpha[0] = rand()%110 + 40;
                    alpha[1] = rand()%70 + 180;
                    alpha[2] = rand()%70 + 270;
                    answer = (alpha[2]-alpha[1])/2;
                    check = 1;
                }while(check!=1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Треугольник $ABC$ вписан в окружность с центром в точке $O$. Точки $O$ и $C$ лежат в одной полуплоскости относительно прямой $AB$. Найдите угол $ACB$, если угол $AOB$  равен $" << (alpha[2] - alpha[1]) << "^{\\circ}$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=above:$O$] (O) at(0,0);" << endl
                    << "            \\draw[fill=black] (O) circle(1pt);" << endl
                    << "            \\coordinate[label=below right:$B$] (B) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (C) -- (B) -- (A) -- (O) -- (B);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;

            case 14:
                do{
                    max = 0;
                    R = 1.5;
                    for(int i=0; i<4; i++)
                        alpha[i] = rand()%361;
                    
                    for(int i = 0; i<3; i++)
                    {
                        for(int m = i+1; m<4; m++)
                        {
                            if(alpha[i]>alpha[m])
                            {
                                change = alpha[i];
                                alpha[i] = alpha[m];
                                alpha[m] = change;
                            }
                        }
                    }
                    betta[2] = (alpha[1]+360-alpha[3])/2;
                    betta[0] = 180 - betta[2];
                    betta[3] = (alpha[2]-alpha[0])/2;
                    betta[1] = 180 - betta[3];
                    check = 1;
                    for(int i=0; i<4; i++)
                    {
                        if(betta[i]<20)
                            check = 0;
                    }
                    if(alpha[1]-alpha[0]<60)
                        check = 0;
                    if(alpha[2]-alpha[1]<60)
                        check = 0;
                    if(alpha[3]-alpha[2]<60)
                        check = 0;
                    if(360-alpha[3]+alpha[0]<60)
                        check = 0;
                    answer = (alpha[3]-alpha[2])/2;
                }while(check!=1);
                cout << "%" << i + 1 << endl;
                cout << "\\item\n" << endl << "\\begin{geometrytask}" << endl;
                cout << "        Четырехугольник $ABCD$ вписан в окружность. Угол $ABC$ равен $" << (360-alpha[2]+alpha[0])/2 << "^{\\circ}$, угол $CAD$ равен $" << (360-alpha[3]+alpha[0])/2 << "^{\\circ}$. Найдите угол $ABD$. Ответ дайте в градусах." << endl;
                cout << "\\end{geometrytask}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above left:$B$] (B) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above right:$C$] (C) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below right:$D$] (D) at (" <<  alpha[3] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + FormatDouble(answer) + " \n";
                break;


            }
            return Answer;
}

string FirstFiveRoad(int i, int AllType)
{
    string Answer;
    int type = rand()%9 + 1;
    if(type >= 6)
        type = 6;
    int typeother;
    switch(type)
    {
        case 1:     // Тип 1 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.4\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.4\\textwidth]{Дороги1.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Саша летом отдыхает у дедушки в деревне Масловка. В субботу они собираются съездить на велосипедах в село Захарово в магазин. Из деревни Масловка в село Захарово можно проехать по прямой лесной дорожке. Есть более длинный путь: по прямолинейному шоссе через деревню Вёсенка до деревни Полянка, где нужно повернуть под прямым углом направо на другое шоссе, ведущее в село Захарово. Есть и третий маршрут: в деревне Вёсенка можно свернуть на прямую тропинку в село Захарово, которая идёт мимо пруда. Лесная дорожка и тропинка образуют с шоссе прямоугольные треугольники. По шоссе Саша с дедушкой едут со скоростью 20 км/ч, а по лесной дорожке и тропинке -- со скоростью 15 км/ч. На плане изображено взаимное расположение населённых пунктов, сторона каждой клетки равна 1 км." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & д. Масловка & с. Захарово & д. Вёсенка \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 142 \n";
                break;

                case 2:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & д. Полянка & с. Захарово & д. Вёсенка \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 342 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько километров проедут Саша с дедушкой от деревни Масловка до села Захарово, если они поедут по шоссе через деревню Полянка?" << endl << endl;
                Answer = Answer + "  \\item 41 \n";
                break;

                case 2:
                cout << "\\item     Сколько километров проедут Саша с дедушкой от деревни Вёсенка до села Захарово, если они поедут по шоссе через деревню Полянка?" << endl << endl;
                Answer = Answer + "  \\item 35 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите расстояние от деревни Масловка до села Захарово по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 29 \n";
                break;

                case 2:
                cout << "\\item     Найдите расстояние от деревни Вёсенка до села Захарово по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 25 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Масловка в село Захарово Саша с дедушкой, если они поедут по прямой лесной дорожке?" << endl << endl;
                Answer = Answer + "  \\item 116 \n";
                break;

                case 2:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Масловка в село Захарово Саша с дедушкой, если они поедут сначала по шоссе, а затем свернут в деревне Вёсенка на прямую тропинку, которая проходит мимо пруда?" << endl << endl;
                Answer = Answer + "  \\item 118 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
                << "В таблице указана стоимость (в рублях) некоторых продуктов в четырёх магазинах, расположенных в деревне Масловка, селе Захарово, деревне Вёсенка и деревне Полянка." << endl
                << "\\begin{center}" << endl
                << "\\resizebox{\\linewidth}{!}{%" << endl
                << "\\begin{tabular}{|l|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "Наименование продукта & д. Масловка & с. Захарово & д. Вёсенка & д. Полянка\\\\ \\hline" << endl
                << "Молоко (1 л) & 45 & 40 & 42 & 52 \\\\ \\hline" << endl
                << "Хлеб (1 батон) & 29 & 28 & 31 & 22 \\\\ \\hline" << endl
                << "Сыр \"Российский\" (1 кг) & 250 & 270 & 290 & 280 \\\\ \\hline" << endl
                << "Говядина (1 кг) & 350 & 380 & 360 & 390 \\\\ \\hline" << endl
                << "Картофель (1 кг) & 35 & 25 & 32 & 24 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl << "}" << endl
                << "\\end{center}" << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Саша с дедушкой хотят купить 2 л молока, 2 кг говядины и 4 кг картофеля. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 930 \n";
                break;

                case 2:
                cout << "Саша с дедушкой хотят купить 3 батона хлеба, 2 кг сыра «Российский» и 5 кг картофеля. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 746 \n";
                break;
            }
            break;

        case 2:     // Тип 3 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.4\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.4\\textwidth]{Дороги3.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Гриша летом отдыхает у дедушки в деревне Грушёвка. В понедельник они собираются съездить на велосипедах в село Абрамово на ярмарку. Из деревни Грушёвка в село Абрамово можно проехать по прямой лесной дорожке. Есть более длинный путь: по прямолинейному шоссе через деревню Таловка до деревни Новая, где нужно повернуть под прямым углом направо на другое шоссе, ведущее в село Абрамово. Есть и третий маршрут: в деревне Таловка можно свернуть на прямую тропинку в село Абрамово, которая идёт мимо пруда. Лесная дорожка и тропинка образуют с шоссе прямоугольные треугольники. По шоссе Гриша с дедушкой едут со скоростью 15 км/ч, а по лесной дорожке и тропинке — со скоростью 12 км/ч. На плане изображено взаимное расположение населённых пунктов, длина стороны каждой клетки равна 2 км." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & д. Новая & с. Абрамово & д. Грушёвшка \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 143 \n";
                break;

                case 2:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & д. Таловка & д. Грушёвка & с. Абрамово \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 234 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько километров проедут Гриша с дедушкой от деревни Грушёвка до села Абрамово, если они поедут по шоссе через деревню Новая?" << endl << endl;
                Answer = Answer + "  \\item 42 \n";
                break;

                case 2:
                cout << "\\item     Сколько километров проедут Гриша с дедушкой от деревни Таловка до села Абрамово, если они поедут по шоссе через деревню Новая?" << endl << endl;
                Answer = Answer + "  \\item 34 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите расстояние от деревни Грушёвка до села Абрамово по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 30 \n";
                break;

                case 2:
                cout << "\\item     Найдите расстояние от деревни Таловка до села Абрамово по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 26 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Грушёвка в село Абрамово Гриша с дедушкой, если поедут через деревню Новая?" << endl << endl;
                Answer = Answer + "  \\item 168 \n";
                break;

                case 2:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Грушёвка в село Абрамово Гриша с дедушкой, если они поедут сначала по шоссе, а затем свернут в Таловке на прямую тропинку, которая проходит мимо пруда?" << endl << endl;
                Answer = Answer + "  \\item 162 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
                << "В таблице указана стоимость (в рублях) некоторых продуктов в четырёх магазинах, расположенных в деревне Грушёвка, селе Абрамово, деревне Таловка и деревне Новая." << endl
                << "\\begin{center}" << endl
                << "\\resizebox{\\linewidth}{!}{%" << endl
                << "\\begin{tabular}{|l|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "Наименование продукта & д. Грушёвка & с. Абрамово & д. Таловка & д. Новая\\\\ \\hline" << endl
                << "Молоко (1 л) & 32 & 33 & 31 & 34 \\\\ \\hline" << endl
                << "Хлеб (1 батон) & 24 & 21 & 26 & 20 \\\\ \\hline" << endl
                << "Сыр \"Российский\" (1 кг) & 320 & 310 & 330 & 300 \\\\ \\hline" << endl
                << "Говядина (1 кг) & 390 & 360 & 370 & 420 \\\\ \\hline" << endl
                << "Картофель (1 кг) & 10 & 18 & 15 & 12 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl << "}" << endl
                << "\\end{center}" << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Гриша с дедушкой хотят купить 3 батона хлеба, 1,5 кг сыра \"Российский\" и 5 кг картофеля. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 570 \n";
                break;

                case 2:
                cout << "Гриша с дедушкой хотят купить 4 л молока, 5 батонов хлеба и 2 кг говядины. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 957 \n";
                break;
            }
            break;

        case 3:     // Тип 2 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.4\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.4\\textwidth]{Дороги2.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Гриша летом отдыхает у дедушки в деревне Осиновка. В субботу они собираются съездить на велосипедах в село Николаево в магазин. Из деревни Осиновка в село Николаево можно проехать по прямой лесной дорожке. Есть более длинный путь: по прямолинейному шоссе через деревню Зябликово до деревни Старая, где нужно повернуть под прямым углом направо на другое шоссе, ведущее в село Николаево. Есть и третий маршрут: в деревне Зябликово можно свернуть на прямую тропинку в село Николаево, которая идёт мимо пруда. Лесная дорожка и тропинка образуют с шоссе прямоугольные треугольники. По шоссе Гриша с дедушкой едут со скоростью 15 км/ч, а по лесной дорожке и тропинке — со скоростью 10 км/ч. На плане изображено взаимное расположение населённых пунктов, длина стороны каждой клетки равна 1 км." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & д. Осиновка & с. Николаево & д. Зябликово \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 432 \n";
                break;

                case 2:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & д. Старая & д. Николаево & с. Зябликово \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 132 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько километров проедут Гриша с дедушкой от деревни Осиновка до села Николаево, если они поедут по шоссе через деревню Старая?" << endl << endl;
                Answer = Answer + "  \\item 35 \n";
                break;

                case 2:
                cout << "\\item     Сколько километров проедут Гриша с дедушкой от деревни Зябликово до села Николаево, если они поедут по шоссе через деревню Старая?" << endl << endl;
                Answer = Answer + "  \\item 23 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите расстояние от деревни Осиновка до села Николаево по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 30 \n";
                break;

                case 2:
                cout << "\\item     Найдите расстояние от деревни Зябликово до села Николаево по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 26 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Осиновка в село Николаево Гриша с дедушкой, если они поедут по прямой лесной дорожке?" << endl << endl;
                Answer = Answer + "  \\item 150 \n";
                break;

                case 2:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Осиновка в село Николаево Гриша с дедушкой, если они поедут сначала по шоссе, а затем свернут в деревне Зябликово на прямую тропинку, которая проходит мимо пруда?" << endl << endl;
                Answer = Answer + "  \\item 150 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
                << "В таблице указана стоимость (в рублях) некоторых продуктов в четырёх магазинах, расположенных в деревне Осиновка, селе Николаево, деревне Зябликово и деревне Старая." << endl
                << "\\begin{center}" << endl
                << "\\resizebox{\\linewidth}{!}{%" << endl
                << "\\begin{tabular}{|l|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "Наименование продукта & д. Осиновка & с. Николаево & д. Зябликово & д. Старая\\\\ \\hline" << endl
                << "Молоко (1 л) & 44 & 48 & 54 & 60 \\\\ \\hline" << endl
                << "Хлеб (1 батон) & 26 & 19 & 23 & 18 \\\\ \\hline" << endl
                << "Сыр \"Российский\" (1 кг) & 310 & 330 & 340 & 290 \\\\ \\hline" << endl
                << "Говядина (1 кг) & 370 & 320 & 330 & 360 \\\\ \\hline" << endl
                << "Картофель (1 кг) & 24 & 26 & 25 & 27 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl << "}" << endl
                << "\\end{center}" << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Гриша с дедушкой хотят купить 3 л молока, 2 батона хлеба и 3 кг картофеля. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 256 \n";
                break;

                case 2:
                cout << "Гриша с дедушкой хотят купить 5 л молока, 2 кг сыра «Российский» и 2 кг говядины. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 1540 \n";
                break;
            }
            break;

        case 4:     // Тип 4 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.4\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.4\\textwidth]{Дороги4.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Володя летом отдыхает у дедушки в деревне Ёлочки. В воскресенье они собираются съездить на машине в село Кленовое. Из деревни Ёлочки в село Кленовое можно проехать по прямой грунтовой дороге. Есть более длинный путь: по прямолинейному шоссе через деревню Сосенки до деревни Жуки, где нужно повернуть под прямым углом направо на другое шоссе, ведущее в село Кленовое. Есть и третий маршрут: в деревне Сосенки можно свернуть на прямую грунтовую дорогу в село Кленовое, которая идёт мимо пруда. Шоссе и грунтовые дороги образуют прямоугольные треугольники. По шоссе Володя с дедушкой едут со скоростью 80 км/ч, а по грунтовой дороге — со скоростью 40 км/ч. На плане изображено взаимное расположение населённых пунктов, длина стороны каждой клетки равна 4 км." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & д. Ёлочки & с. Кленовое & д. Жуки \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 421 \n";
                break;

                case 2:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & с. Кленовое & д. Ёлочки & д. Сосенки \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 243 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько километров проедут Володя с дедушкой от деревни Ёлочки до села Кленовое, если они поедут по шоссе через деревню Жуки?" << endl << endl;
                Answer = Answer + "  \\item 92 \n";
                break;

                case 2:
                cout << "\\item     Сколько километров проедут Володя с дедушкой от деревни Сосенки до села Кленовое, если они поедут по шоссе через деревню Жуки?" << endl << endl;
                Answer = Answer + "  \\item 56 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите расстояние от деревни Ёлочки до села Кленовое по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 68 \n";
                break;

                case 2:
                cout << "\\item     Найдите расстояние от деревни Сосенки до села Кленовое по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 40 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Ёлочки в село Кленовое Володя с дедушкой, если они поедут по прямой грунтовой дороге?" << endl << endl;
                Answer = Answer + "  \\item 102 \n";
                break;

                case 2:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Ёлочки в село Кленовое Володя с дедушкой, если они поедут сначала по шоссе, а затем свернут в деревне Сосенки на грунтовую дорогу, которая проходит мимо пруда?" << endl << endl;
                Answer = Answer + "  \\item 87 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
                << "В таблице указана стоимость (в рублях) некоторых продуктов в четырёх магазинах, расположенных в деревне Ёлочки, селе Кленовое, деревне Сосенки и деревне Жуки." << endl
                << "\\begin{center}" << endl
                << "\\resizebox{\\linewidth}{!}{%" << endl
                << "\\begin{tabular}{|l|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "Наименование продукта & д. Ёлочки & с. Кленовое & д. Сосенки & д. Жуки\\\\ \\hline" << endl
                << "Молоко (1 л) & 42 & 45 & 38 & 43 \\\\ \\hline" << endl
                << "Хлеб (1 батон) & 22 & 25 & 23 & 27 \\\\ \\hline" << endl
                << "Сыр \"Российский\" (1 кг) & 320 & 290 & 270 & 280 \\\\ \\hline" << endl
                << "Говядина (1 кг) & 410 & 420 & 450 & 430 \\\\ \\hline" << endl
                << "Картофель (1 кг) & 26 & 18 & 24 & 16 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl << "}" << endl
                << "\\end{center}" << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Володя с дедушкой хотят купить 5 л молока, 3 кг сыра «Российский» и 4 кг картофеля. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 1096 \n";
                break;

                case 2:
                cout << "Володя с дедушкой хотят купить 3 батона хлеба, 2 кг сыра «Российский» и 3 кг говядины. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 1915 \n";
                break;
            }
            break;

        case 5:     // Тип 5 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.4\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.4\\textwidth]{Дороги5.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Полина летом отдыхает у дедушки в деревне Ясная. В четверг они собираются съездить на велосипедах в село Майское в магазин. Из деревни Ясная в село Майское можно проехать по прямой лесной дорожке. Есть более длинный путь: по прямолинейному шоссе через деревню Камышёвка до деревни Хомяково, где нужно повернуть под прямым углом налево на другое шоссе, ведущее в село Майское. Есть и третий маршрут: в деревне Камышёвка можно свернуть на прямую тропинку в село Майское, которая идёт мимо пруда. Лесная дорожка и тропинка образуют с шоссе прямоугольные треугольники. По шоссе Полина с дедушкой едут со скоростью 20 км/ч, а по лесной дорожке и тропинке — со скоростью 15 км/ч. На плане изображено взаимное расположение населённых пунктов, длина стороны каждой клетки равна 2 км." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & д. Камышёвшка & д. Ясная & д. Хомяково \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 213 \n";
                break;

                case 2:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Насел. пункты & с. Майское & д. Хомяково & д. Ясная \\\\ \\hline" << endl
                << "Цифры &  &  &  \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 431 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько километров проедут Полина с дедушкой от деревни Ясная до села Майское, если они поедут по шоссе через деревню Хомяково?" << endl << endl;
                Answer = Answer + "  \\item 56 \n";
                break;

                case 2:
                cout << "\\item     Сколько километров проедут Полина с дедушкой от деревни Камышёвка до села Майское, если они поедут по шоссе через деревню Хомяково?" << endl << endl;
                Answer = Answer + "  \\item 34 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите расстояние от деревни Ясная до села Майское по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 40 \n";
                break;

                case 2:
                cout << "\\item     Найдите расстояние от деревни Камышёвка до села Майское по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 26 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Ясная в село Майское Полина с дедушкой, если поедут через деревню Хомяково?" << endl << endl;
                Answer = Answer + "  \\item 168 \n";
                break;

                case 2:
                cout << "\\item     Сколько минут затратят на дорогу из деревни Ясная в село Майское Полина с дедушкой, если они поедут сначала по шоссе, а затем свернут в Камышёвке на прямую тропинку, которая проходит мимо пруда?" << endl << endl;
                Answer = Answer + "  \\item 170 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
                << "В таблице указана стоимость (в рублях) некоторых продуктов в четырёх магазинах, расположенных в деревне Ясная, селе Майское, деревне Камышёвка и деревне Хомяково." << endl
                << "\\begin{center}" << endl
                << "\\resizebox{\\linewidth}{!}{%" << endl
                << "\\begin{tabular}{|l|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "Наименование продукта & д. Ёлочки & с. Кленовое & д. Сосенки & д. Жуки\\\\ \\hline" << endl
                << "Молоко (1 л) & 42 & 38 & 41 & 33 \\\\ \\hline" << endl
                << "Хлеб (1 батон) & 25 & 21 & 29 & 30 \\\\ \\hline" << endl
                << "Сыр \"Российский\" (1 кг) & 310 & 320 & 290 & 280 \\\\ \\hline" << endl
                << "Говядина (1 кг) & 340 & 380 & 410 & 390 \\\\ \\hline" << endl
                << "Картофель (1 кг) & 15 & 20 & 17 & 18 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl << "}" << endl
                << "\\end{center}" << endl;
            typeother = rand()%2 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Полина с дедушкой хотят купить 2 л молока, 3 кг говядины и 2 кг картофеля. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 1134 \n";
                break;

                case 2:
                cout << "Полина с дедушкой хотят купить 3 л молока, 1 кг сыра «Российский» и 3 кг картофеля. В каком магазине такой набор продуктов будет стоить дешевле всего? В ответ запишите стоимость данного набора в этом магазине." << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 433 \n";
                break;
            }
            break;

        case 6:     // Тип 11 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.4\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.4\\textwidth]{Дороги6.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "На рисунке изображён план сельской местности. Таня на летних каникулах приезжает в гости к дедушке в деревню Антоновка (на плане обозначена цифрой 1). В конце каникул дедушка на машине собирается отвезти Таню на автобусную станцию, которая находится в деревне Богданово. Из Антоновки в Богданово можно проехать по просёлочной дороге мимо реки. Есть другой путь — по шоссе до деревни Ванютино, где нужно повернуть под прямым углом налево на другое шоссе, ведущее в Богданово. Третий маршрут проходит по просёлочной дороге мимо пруда до деревни Горюново, где можно свернуть на шоссе до Богданово. Четвёртый маршрут пролегает по шоссе до деревни Доломино, от Доломино до Горюново по просёлочной дороге мимо конюшни и от Горюново до Богданово по шоссе. Ещё один маршрут проходит по шоссе до деревни Егорка, по просёлочной дороге мимо конюшни от Егорки до Жилино и по шоссе от Жилино до Богданово. Шоссе и просёлочные дороги образуют прямоугольные треугольники. По шоссе Таня с дедушкой едут со скоростью 50 км/ч, а по просёлочным дорогам — со скоростью 30 км/ч. Расстояние от Антоновки до Доломино равно 12 км, от Доломино до Егорки — 4 км, от Егорки до Ванютино — 12 км, от Горюново до Ванютино — 15 км, от Ванютино до Жилино — 9 км, а от Жилино до Богданово — 12 км." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%4 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Деревни & Ванютино & Горюново & Егорка & Жилино \\\\ \\hline" << endl
                << "Цифры &  &  &  & \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 4625 \n";
                break;

                case 2:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Деревни & Егорка & Ванютино & Доломино & Жилино \\\\ \\hline" << endl
                << "Цифры &  &  &  & \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 2435 \n";
                break;

                case 3:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Деревни & Егорка & Ванютино & Доломино & Жилино \\\\ \\hline" << endl
                << "Цифры &  &  &  & \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 7632 \n";
                break;

                case 4:
                cout << "Пользуясь описанием, определите, какими цифрами на плане обозначены населённые пункты. Заполните таблицу, в бланк ответов перенесите последовательность трёх цифр без пробелов, запятых и других дополнительных символов." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|l|l|l|l|l|}" << endl
                << "\\hline" << endl
                << "\\small Деревни & Богданово & Горнюново & Доломино & Егорка \\\\ \\hline" << endl
                << "Цифры &  &  &  & \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 7425 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%4 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите расстояние от Антоновки до Егорки по шоссе. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 8 \n";
                break;

                case 2:
                cout << "\\item     Найдите расстояние от Доломино до Ванютино по шоссе. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 8 \n";
                break;

                case 3:
                cout << "\\item     Найдите расстояние от Горюново до Жилино по шоссе. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 6 \n";
                break;

                case 4:
                cout << "\\item     Найдите расстояние от Ванютино до Богданово по шоссе. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 21 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%4 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите расстояние от Егорки до Жилино по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 15 \n";
                break;

                case 2:
                cout << "\\item     Найдите расстояние от Доломино до Горюново по прямой.  \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 17 \n";
                break;

                case 3:
                cout << "\\item     Найдите расстояние от Антоновки до Горюново по прямой. \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 25 \n";
                break;

                case 4:
                cout << "\\item     Найдите расстояние от Антоновки до Богданово по прямой.  \\\\Ответ дайте в километрах." << endl << endl;
                Answer = Answer + "  \\item 29 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%4 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Сколько минут затратят на дорогу Таня с дедушкой из Антоновки в Богданово, если поедут мимо пруда через Горюново?" << endl << endl;
                Answer = Answer + "  \\item 57 \n";
                break;

                case 2:
                cout << "\\item     Сколько минут затратят на дорогу Таня с дедушкой из Антоновки в Богданово, если поедут через Доломино и Горюново мимо конюшни?" << endl << endl;
                Answer = Answer + "  \\item 55 \n";
                break;

                case 3:
                cout << "\\item     Сколько минут затратят на дорогу Таня с дедушкой из Антоновки в Богданово, если поедут через Егорку и Жилино мимо конюшни?" << endl << endl;
                Answer = Answer + "  \\item 54 \n";
                break;

                case 4:
                cout << "\\item     Сколько минут затратят на дорогу Таня с дедушкой из Антоновки в Богданово, если поедут напрямик?" << endl << endl;
                Answer = Answer + "  \\item 58 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl;
            typeother = rand()%4 + 1;
            switch(typeother)
            {
                case 1:
                cout << "На шоссе машина дедушки расходует 6,8 литра бензина на 100 км. Известно, что на путь из Антоновки до Богданово через Ванютино и путь через Доломино и Горюново мимо конюшни ей необходим один и тот же объём бензина. Сколько литров бензина на 100 км машина дедушки расходует на просёлочных дорогах?" << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 9,2 \n";
                break;

                case 2:
                cout << "На шоссе машина дедушки расходует 5,8 литра бензина на 100 км. Известно, что на путь из Антоновки до Богданово через Ванютино и путь напрямик ей необходим один и тот же объём бензина. Сколько литров бензина на 100 км машина дедушки расходует на просёлочных дорогах?" << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 8,2 \n";
                break;

                case 3:
                cout << "На шоссе машина дедушки расходует 6,5 литра бензина на 100 км. Известно, что на путь из Антоновки до Богданово через Ванютино и путь через Горюново мимо пруда ей необходим один и тот же объём бензина. Сколько литров бензина на 100 км машина дедушки расходует на просёлочных дорогах?" << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 9,1 \n";
                break;

                case 4:
                cout << "На шоссе машина дедушки расходует 5,5 литра бензина на 100 км. Известно, что на путь из Антоновки до Богданово через Ванютино и путь через Егорку и Жилино мимо конюшни ей необходим один и тот же объём бензина. Сколько литров бензина на 100 км машина дедушки расходует на просёлочных дорогах?" << endl
                    << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 7,7 \n";
                break;
            }
            break;
    }
    return Answer;
}

string FirstFiveFlat(int i, int AllType)
{
    string Answer;
    int typeother;
    cout << "%" << i + 1 << endl; // 1
    cout << "\\item" << endl
        << "\\begin{minipage}[t]{\\linewidth}" << endl
        << "\\begin{center}" << endl
        << "\\includegraphics[width=0.8\\textwidth]{Квартира.png}" << endl
        << "\\end{center}" << endl
        << "На рисунке изображѐн план двухкомнатной квартиры в многоэтажном жилом доме. Сторона одной клетки на плане соответствует 0,4 м, а условные обозначения двери и окна приведены в правой части рисунка. Вход в квартиру находится в коридоре. Слева от входа в квартиру находится санузел, а в противоположном конце коридора — дверь в кладовую. Рядом с кладовой находится спальня, из которой можно пройти на одну из застеклѐнных лоджий. Самое большое по площади помещение — гостиная, откуда можно попасть в коридор и на кухню. Из кухни также можно попасть на застеклѐнную лоджию." << endl
        << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк перенесите последовательность четырѐх цифр без пробелов, запятых и других дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Объекты & коридор & кладовая & спальня & кухня \\\\ \\hline" << endl
        << "Цифры &  &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 2347 \n";
        break;

        case 2:
        cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк перенесите последовательность четырѐх цифр без пробелов, запятых и других дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Объекты & коридор & кладовая & спальня & гостиная \\\\ \\hline" << endl
        << "Цифры &  &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 2346 \n";
        break;

        case 3:
        cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк перенесите последовательность четырѐх цифр без пробелов, запятых и других дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Объекты & коридор & кладовая & спальня & санузел \\\\ \\hline" << endl
        << "Цифры &  &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 2341 \n";
        break;

        case 4:
        cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк перенесите последовательность четырѐх цифр без пробелов, запятых и других дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Объекты & коридор & кладовая & санузел & гостиная \\\\ \\hline" << endl
        << "Цифры &  &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 2316 \n";
        break;
    }

    cout << "%" << i + 2 << endl; // 2
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     Паркетная доска размером 20 см на 80 см продается в упаковках по 14 штук. Сколько упаковок паркетной доски понадобилось, чтобы выложить пол в гостиной?" << endl << endl;
        Answer = Answer + "  \\item 12 \n";
        break;

        case 2:
        cout << "\\item     Паркетная доска размером 20 см на 40 см продается в упаковках по 8 штук. Сколько упаковок паркетной доски понадобилось, чтобы выложить пол в коридоре?" << endl << endl;
        Answer = Answer + "  \\item 32 \n";
        break;

        case 3:
        cout << "\\item     Плитка для пола размером 40 см на 40 см продается в упаковках по 12 штук. Сколько упаковок плитки понадобилось, чтобы выложить пол на обеих лоджиях?" << endl << endl;
        Answer = Answer + "  \\item 7 \n";
        break;

        case 4:
        cout << "\\item     Плитка для пола размером 40 см на 40 см продается в упаковках по 12 штук. Сколько упаковок плитки понадобилось, чтобы выложить пол на кухне?" << endl << endl;
        Answer = Answer + "  \\item 8 \n";
        break;
    }

    cout << "%" << i + 3 << endl; // 3
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     Найдите площадь санузла. Ответ дайте в квадратных метрах." << endl << endl;
        Answer = Answer + "  \\item 4,8 \n";
        break;

        case 2:
        cout << "\\item     Найдите площадь коридора. Ответ дайте в квадратных метрах." << endl << endl;
        Answer = Answer + "  \\item 20 \n";
        break;

        case 3:
        cout << "\\item     Найдите площадь кладовой. Ответ дайте в квадратных метрах." << endl << endl;
        Answer = Answer + "  \\item 3,2 \n";
        break;

        case 4:
        cout << "\\item     Найдите площадь спальни. Ответ дайте в квадратных метрах." << endl << endl;
        Answer = Answer + "  \\item 15,84 \n";
        break;
    }

    cout << "%" << i + 4 << endl; // 4
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     На сколько процентов площадь коридора больше площади кладовой?" << endl << endl;
        Answer = Answer + "  \\item 525 \n";
        break;

        case 2:
        cout << "\\item     На сколько процентов площадь гостиной больше площади кладовой?" << endl << endl;
        Answer = Answer + "  \\item 680 \n";
        break;

        case 3:
        cout << "\\item     На сколько процентов площадь кухни больше площади кладовой?" << endl << endl;
        Answer = Answer + "  \\item 350 \n";
        break;

        case 4:
        cout << "\\item     На сколько процентов площадь спальни больше площади лоджии, примыкающей к спальне?" << endl << endl;
        Answer = Answer + "  \\item 125 \n";
        break;
    }

    cout << "%" << i + 5 << endl; // 5
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "В квартире планируется установить стиральную машину. Характеристики стиральных машин, условия подключения и доставки приведены в таблице. Планируется купить стиральную машину с вертикальной загрузкой, не превосходящую 85 см по высоте." << endl
        << "\\begin{center}" << endl
        << "\\resizebox{\\linewidth}{!}{%" << endl
        << "\\begin{tabular}{|p{2cm}|p{2cm}|p{1.5cm}|p{1.5cm}|p{1.5cm}|p{1.5cm}|p{2.5cm}|}" << endl
        << "\\hline" << endl
        << "Модель & Вместимость барабана (кг) & Тип загрузки & Стоимость (руб.) & Стоимость подключения (руб.) & Стоимость доставки (\\% от стоимости машины) & Габариты (высота х ширина х глубина, см;) \\\\ \\hline" << endl
        << "А & 7 & верт. & 28 000 & 1700 & бесплатно & 85 х 60 х 45 \\\\ \\hline" << endl
        << "Б & 5 & фронт. & 24 000 & 4500 & 10 & 85 х 60 х 40 \\\\ \\hline" << endl
        << "В & 5 & фронт. & 25 000 & 5000 & 10 & 85 х 60 х 40 \\\\ \\hline" << endl
        << "Г & 6,5 & фронт. & 24 000 & 4500 & 10 & 85 х 60 х 44 \\\\ \\hline" << endl
        << "Д & 6 & фронт. & 28 000 & 1700 & бесплатно & 85 х 60 х 45 \\\\ \\hline" << endl
        << "Е & 6 & верт. & 27 600 & 2300 & бесплатно & 89 х 60 х 40 \\\\ \\hline" << endl
        << "Ж & 6 & верт. & 27 585 & 1900 & 10 & 89 х 60 х 40 \\\\ \\hline" << endl
        << "З & 6 & фронт. & 20 000 & 6300 & 15 & 85 х 60 х 42 \\\\ \\hline" << endl
        << "И & 5 & фронт. & 27 000 & 1800 & бесплатно & 85 х 60 х 40 \\\\ \\hline" << endl
        << "К & 5 & верт. & 27 000 & 1800 & бесплатно & 85 х 60 х 40 \\\\ \\hline" << endl
        << "\\end{tabular}" << endl << "}" << endl
        << "\\end{center}" << endl;
        cout << "Сколько рублей будет стоить наиболее дешевый подходящий вариант вместе с подключением и доставкой?" << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 28800 \n";
        break;

        case 2:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "В квартире планируется установить стиральную машину. Характеристики стиральных машин, условия подключения и доставки приведены в таблице. Планируется купить стиральную машину с вертикальной загрузкой вместимостью не менее 6 кг." << endl
        << "\\begin{center}" << endl
        << "\\resizebox{\\linewidth}{!}{%" << endl
        << "\\begin{tabular}{|p{2cm}|p{2cm}|p{1.5cm}|p{1.5cm}|p{1.5cm}|p{1.5cm}|p{2.5cm}|}" << endl
        << "\\hline" << endl
        << "Модель & Вместимость барабана (кг) & Тип загрузки & Стоимость (руб.) & Стоимость подключения (руб.) & Стоимость доставки (\\% от стоимости машины) & Габариты (высота х ширина х глубина, см;) \\\\ \\hline" << endl
        << "А & 7 & верт. & 28 000 & 1700 & бесплатно & 85 х 60 х 45 \\\\ \\hline" << endl
        << "Б & 5 & фронт. & 24 000 & 4500 & 10 & 85 х 60 х 40 \\\\ \\hline" << endl
        << "В & 5 & фронт. & 25 000 & 5000 & 10 & 85 х 60 х 40 \\\\ \\hline" << endl
        << "Г & 6,5 & фронт. & 24 000 & 4500 & 10 & 85 х 60 х 44 \\\\ \\hline" << endl
        << "Д & 6 & фронт. & 28 000 & 1700 & бесплатно & 85 х 60 х 45 \\\\ \\hline" << endl
        << "Е & 6 & верт. & 27 600 & 2300 & бесплатно & 89 х 60 х 40 \\\\ \\hline" << endl
        << "Ж & 6 & верт. & 27 585 & 1900 & 10 & 89 х 60 х 40 \\\\ \\hline" << endl
        << "З & 6 & фронт. & 20 000 & 6300 & 15 & 85 х 60 х 42 \\\\ \\hline" << endl
        << "И & 5 & фронт. & 27 000 & 1800 & бесплатно & 85 х 60 х 40 \\\\ \\hline" << endl
        << "К & 5 & верт. & 27 000 & 1800 & бесплатно & 85 х 60 х 40 \\\\ \\hline" << endl
        << "\\end{tabular}" << endl << "}" << endl
        << "\\end{center}" << endl;
        cout << "Сколько рублей будет стоить наиболее дешевый подходящий вариант вместе с подключением и доставкой?" << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 29700 \n";
        break;

        case 3:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "В квартире планируется установить стиральную машину. Характеристики стиральных машин, условия подключения и доставки приведены в таблице. Планируется купить стиральную машину с фронтальной загрузкой вместимостью не менее 6 кг." << endl
        << "\\begin{center}" << endl
        << "\\resizebox{\\linewidth}{!}{%" << endl
        << "\\begin{tabular}{|p{2cm}|p{2cm}|p{1.5cm}|p{1.5cm}|p{1.5cm}|p{1.5cm}|p{2.5cm}|}" << endl
        << "\\hline" << endl
        << "Модель & Вместимость барабана (кг) & Тип загрузки & Стоимость (руб.) & Стоимость подключения (руб.) & Стоимость доставки (\\% от стоимости машины) & Габариты (высота х ширина х глубина, см;) \\\\ \\hline" << endl
        << "А & 7 & верт. & 28 000 & 1700 & бесплатно & 85 х 60 х 45 \\\\ \\hline" << endl
        << "Б & 5 & фронт. & 24 000 & 4500 & 10 & 85 х 60 х 40 \\\\ \\hline" << endl
        << "В & 5 & фронт. & 25 000 & 5000 & 10 & 85 х 60 х 40 \\\\ \\hline" << endl
        << "Г & 6,5 & фронт. & 24 000 & 4500 & 10 & 85 х 60 х 44 \\\\ \\hline" << endl
        << "Д & 6 & фронт. & 28 000 & 1700 & бесплатно & 85 х 60 х 45 \\\\ \\hline" << endl
        << "Е & 6 & верт. & 27 600 & 2300 & бесплатно & 89 х 60 х 40 \\\\ \\hline" << endl
        << "Ж & 6 & верт. & 27 585 & 1900 & 10 & 89 х 60 х 40 \\\\ \\hline" << endl
        << "З & 6 & фронт. & 20 000 & 6300 & 15 & 85 х 60 х 42 \\\\ \\hline" << endl
        << "И & 5 & фронт. & 27 000 & 1800 & бесплатно & 85 х 60 х 40 \\\\ \\hline" << endl
        << "К & 5 & верт. & 27 000 & 1800 & бесплатно & 85 х 60 х 40 \\\\ \\hline" << endl
        << "\\end{tabular}" << endl << "}" << endl
        << "\\end{center}" << endl;
        cout << "Сколько рублей будет стоить наиболее дешевый подходящий вариант вместе с подключением и доставкой?" << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 29300 \n";
        break;

        case 4:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "В квартире планируется установить стиральную машину. Характеристики стиральных машин, условия подключения и доставки приведены в таблице. Планируется купить стиральную машину с фронтальной загрузкой, по глубине не превосходящую 42 см." << endl
        << "\\begin{center}" << endl
        << "\\resizebox{\\linewidth}{!}{%" << endl
        << "\\begin{tabular}{|p{2cm}|p{2cm}|p{1.5cm}|p{1.5cm}|p{1.5cm}|p{1.5cm}|p{2.5cm}|}" << endl
        << "\\hline" << endl
        << "Модель & Вместимость барабана (кг) & Тип загрузки & Стоимость (руб.) & Стоимость подключения (руб.) & Стоимость доставки (\\% от стоимости машины) & Габариты (высота х ширина х глубина, см;) \\\\ \\hline" << endl
        << "А & 7 & верт. & 28 000 & 1700 & бесплатно & 85 х 60 х 45 \\\\ \\hline" << endl
        << "Б & 5 & фронт. & 24 000 & 4500 & 10 & 85 х 60 х 40 \\\\ \\hline" << endl
        << "В & 5 & фронт. & 25 000 & 5000 & 10 & 85 х 60 х 40 \\\\ \\hline" << endl
        << "Г & 6,5 & фронт. & 24 000 & 4500 & 10 & 85 х 60 х 44 \\\\ \\hline" << endl
        << "Д & 6 & фронт. & 28 000 & 1700 & бесплатно & 85 х 60 х 45 \\\\ \\hline" << endl
        << "Е & 6 & верт. & 27 600 & 2300 & бесплатно & 89 х 60 х 40 \\\\ \\hline" << endl
        << "Ж & 6 & верт. & 27 585 & 1900 & 10 & 89 х 60 х 40 \\\\ \\hline" << endl
        << "З & 6 & фронт. & 20 000 & 6300 & 15 & 85 х 60 х 42 \\\\ \\hline" << endl
        << "И & 5 & фронт. & 27 000 & 1800 & бесплатно & 85 х 60 х 40 \\\\ \\hline" << endl
        << "К & 5 & верт. & 27 000 & 1800 & бесплатно & 85 х 60 х 40 \\\\ \\hline" << endl
        << "\\end{tabular}" << endl << "}" << endl
        << "\\end{center}" << endl;
        cout << "Сколько рублей будет стоить наиболее дешевый подходящий вариант вместе с подключением и доставкой?" << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 28800 \n";
        break;
    }
    return Answer;
}

string FirstFivePaper(int i, int AllType)
{
    string Answer;
    int typeother;
    cout << "%" << i + 1 << endl; // 1
    cout << "\\item" << endl
        << "\\begin{minipage}[t]{\\linewidth}" << endl
        << "\\begin{wrapfigure}{r}{0.4\\textwidth}" << endl
        << "\\centering" << endl
        << "\\includegraphics[width=0.4\\textwidth]{Листы.png}" << endl
        << "\\end{wrapfigure}" << endl
        << "Общепринятые форматы листов бумаги обозначают буквой А и цифрой: А0, А1, А2 и так далее. Лист формата А0 имеет форму прямоугольника, площадь которого равна 1 кв. м. Если лист формата А0 разрезать пополам параллельно меньшей стороне, получается два равных листа формата А1. Если лист А1 разрезать так же пополам, получается два листа формата А2. И так далее. Отношение большей стороны к меньшей стороне листа каждого формата одно и то же, поэтому листы всех форматов подобны. Это сделано специально для того, чтобы пропорции текста и его расположение на листе сохранялись при уменьшении или увеличении шрифта при изменении формата листа." << endl
        << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "В таблице даны размеры (с точностью до мм) четырёх листов, имеющих форматы А2, А3, А5 и А6." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Номер листа & Длина (мм) & Ширина (мм) \\\\ \\hline" << endl
        << "1 & 210 & 148 \\\\ \\hline" << endl
        << "2 & 594 & 420 \\\\ \\hline" << endl
        << "3 & 148 & 105 \\\\ \\hline" << endl
        << "4 & 420 & 297 \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "Установите Установите соответствие между форматами и номерами листов. Заполните таблицу, в бланк ответов перенесите последовательность четырёх цифр, соответствующих номерам листов, без пробелов, запятых и дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small А2 & А3 & А5 & А6 \\\\ \\hline" << endl
        << " &  &  & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 2413 \n";
        break;

        case 2:
        cout << "В таблице даны размеры (с точностью до мм) четырёх листов, имеющих форматы А2, А3, А4 и А6." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Номер листа & Длина (мм) & Ширина (мм) \\\\ \\hline" << endl
        << "1 & 594 & 420 \\\\ \\hline" << endl
        << "2 & 420 & 297 \\\\ \\hline" << endl
        << "3 & 148 & 105 \\\\ \\hline" << endl
        << "4 & 297 & 210 \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "Установите Установите соответствие между форматами и номерами листов. Заполните таблицу, в бланк ответов перенесите последовательность четырёх цифр, соответствующих номерам листов, без пробелов, запятых и дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small А2 & А3 & А4 & А6 \\\\ \\hline" << endl
        << " &  &  & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 1243 \n";
        break;

        case 3:
        cout << "В таблице даны размеры (с точностью до мм) четырёх листов, имеющих форматы А0, А1, А2 и А4." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Номер листа & Длина (мм) & Ширина (мм) \\\\ \\hline" << endl
        << "1 & 841 & 594 \\\\ \\hline" << endl
        << "2 & 1189 & 841 \\\\ \\hline" << endl
        << "3 & 297 & 210 \\\\ \\hline" << endl
        << "4 & 594 & 420 \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "Установите Установите соответствие между форматами и номерами листов. Заполните таблицу, в бланк ответов перенесите последовательность четырёх цифр, соответствующих номерам листов, без пробелов, запятых и дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small А0 & А1 & А2 & А4 \\\\ \\hline" << endl
        << " &  &  & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 2143 \n";
        break;

        case 4:
        cout << "В таблице даны размеры (с точностью до мм) четырёх листов, имеющих форматы А0, А2, А3 и А5." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Номер листа & Длина (мм) & Ширина (мм) \\\\ \\hline" << endl
        << "1 & 594 & 420 \\\\ \\hline" << endl
        << "2 & 420 & 297 \\\\ \\hline" << endl
        << "3 & 1189 & 841 \\\\ \\hline" << endl
        << "4 & 210 & 148 \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "Установите Установите соответствие между форматами и номерами листов. Заполните таблицу, в бланк ответов перенесите последовательность четырёх цифр, соответствующих номерам листов, без пробелов, запятых и дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small А0 & А2 & А3 & А5 \\\\ \\hline" << endl
        << " &  &  & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 3124 \n";
        break;
    }

    cout << "%" << i + 2 << endl; // 2
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     Сколько листов формата А3 получится из одного листа формата А2?" << endl << endl;
        Answer = Answer + "  \\item 2 \n";
        break;

        case 2:
        cout << "\\item     Сколько листов формата А5 получится из одного листа формата А3?" << endl << endl;
        Answer = Answer + "  \\item 4 \n";
        break;

        case 3:
        cout << "\\item     Сколько листов формата А4 получится из одного листа формата А2?" << endl << endl;
        Answer = Answer + "  \\item 4 \n";
        break;

        case 4:
        cout << "\\item     Сколько листов формата А4 получится из одного листа формата А1?" << endl << endl;
        Answer = Answer + "  \\item 2 \n";
        break;
    }

    cout << "%" << i + 3 << endl; // 3
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     Найдите площадь листа формата А3. Ответ дайте в квадратных сантиметрах." << endl << endl;
        Answer = Answer + "  \\item 1250 или 1247,4 \n";
        break;

        case 2:
        cout << "\\item     Найдите площадь листа формата А5. Ответ дайте в квадратных сантиметрах." << endl << endl;
        Answer = Answer + "  \\item 312,5 \n";
        break;

        case 3:
        cout << "\\item     Найдите ширину листа бумаги формата А0. Ответ дайте в миллиметрах и округлите до ближайшего целого числа, кратного 10." << endl << endl;
        Answer = Answer + "  \\item 840 \n";
        break;

        case 4:
        cout << "\\item     Найдите ширину листа бумаги формата А4. Ответ дайте в миллиметрах и округлите до ближайшего целого числа, кратного 10." << endl << endl;
        Answer = Answer + "  \\item 210 \n";
        break;
    }

    cout << "%" << i + 4 << endl; // 4
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     Найдите длину листа бумаги формата А1. Ответ дайте в миллиметрах и округлите до ближайшего целого числа, кратного 10." << endl << endl;
        Answer = Answer + "  \\item 840 \n";
        break;

        case 2:
        cout << "\\item     Найдите длину листа бумаги формата А6. Ответ дайте в миллиметрах и округлите до ближайшего целого числа, кратного 10." << endl << endl;
        Answer = Answer + "  \\item 150 \n";
        break;

        case 3:
        cout << "\\item     Найдите отношение длины меньшей стороны листа формата А4 к большей. Ответ округлите до десятых." << endl << endl;
        Answer = Answer + "  \\item 0,7 \n";
        break;

        case 4:
        cout << "\\item     Найдите отношение длины большей стороны листа формата А1 к меньшей. Ответ округлите до десятых." << endl << endl;
        Answer = Answer + "  \\item 1,4 \n";
        break;
    }

    cout << "%" << i + 5 << endl; // 5
    typeother = rand()%4 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "Бумагу формата А5 упаковали в пачки по 500 листов. Найдите массу пачки, если масса бумаги площади 1 кв. м равна 80 г. Ответ дайте в граммах." << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 1250 или 1243,2 \n";
        break;

        case 2:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "Бумагу формата А1 упаковали в пачки по 80 листов. Найдите массу пачки, если масса бумаги площади 1 кв. м равна 120 г. Ответ дайте в граммах." << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 4800 \n";
        break;

        case 3:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "Размер (высота) типографского шрифта измеряется в пунктах. Один пункт равен 1/72 дюйма, то есть 0,3528 мм. Какой высоты нужен шрифт (в пунктах), чтобы текст был расположен на листе формата А3 так же, как этот же текст, напечатанный шрифтом высотой 15 пунктов на листе формата А4? Размер шрифта округляется до целого." << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 21 \n";
        break;

        case 4:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "Размер (высота) типографского шрифта измеряется в пунктах. Один пункт равен 1/72 дюйма, то есть 0,3528 мм. Какой высоты нужен шрифт (в пунктах), чтобы текст был расположен на листе формата А5 так же, как этот же текст, напечатанный шрифтом высотой 16 пунктов на листе формата А4? Размер шрифта округляется до целого." << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 11 \n";
        break;
    }
    return Answer;
}

string FirstFivePechi(int i, int AlType)
{
    string Answer;
    int typeother;
    cout << "%" << i + 1 << endl; // 1
    cout << "\\item" << endl
        << "Хозяин дачного участка строит баню с парным отделением. Парное отделение имеет размеры: длина 3,5 м, ширина 2,2 м, высота 2 м. Окон в парном отделении нет, для доступа внутрь планируется дверь шириной 60 см, высота дверного проѐма 1,8 м. Для прогрева парного отделения можно использовать электрическую или дровяную печь. В таблице представлены характеристики трѐх печей." << endl
        << "\\begin{center}" << endl
        << "\\resizebox{\\linewidth}{!}{%" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "Номер печи & Тип & Объём помещения (кв.м) & Масса (кг) & Стоимость (руб.)\\\\ \\hline" << endl
        << "1 & дровяная & 8-12 & 40 & 18 000 \\\\ \\hline" << endl
        << "2 & дровяная & 10-16 & 48 & 19 500 \\\\ \\hline" << endl
        << "3 & электрическая & 9-15,5 & 15 & 15 000 \\\\ \\hline" << endl
        << "\\end{tabular}" << endl << "}" << endl
        << "\\end{center}" << endl
        << "Для установки дровяной печи дополнительных затрат не потребуется. Установка электрической печи потребует подведения специального кабеля, что обойдется в 6500 руб." << endl << endl;
    typeother = rand()%2 + 1;
    switch(typeother)
    {
        case 1:
        cout << "Установите соответствие между массами и номерами печей. Заполните таблицу, в бланк ответов перенесите последовательность трѐх цифр без пробелов, запятых и других дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Масса (кг) & 15 & 40 & 48 \\\\ \\hline" << endl
        << "Номер печи &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl << endl;
        Answer = Answer + "  \\item 312 \n";
        break;

        case 2:
        cout << "Установите соответствие между стоимостями и номерами печей. Заполните таблицу, в бланк ответов перенесите последовательность трѐх цифр без пробелов, запятых и других дополнительных символов." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Стоимость (руб.) & 15 000 & 19 500 & 18 000 \\\\ \\hline" << endl
        << "Номер печи &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl  << endl;
        Answer = Answer + "  \\item 321 \n";
        break;
    }

    cout << "%" << i + 2 << endl; // 2
    typeother = rand()%2 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     Найдите объем парного отделения строящейся бани. Ответ дайте в кубических метрах." << endl << endl;
        Answer = Answer + "  \\item 15,4 \n";
        break;

        case 2:
        cout << "\\item     Найдите площадь пола парного отделения строящейся бани. Ответ дайте в квадратных метрах." << endl << endl;
        Answer = Answer + "  \\item 7,7 \n";
        break;
    }

    cout << "%" << i + 3 << endl; // 3
    typeother = rand()%2 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     На сколько рублей покупка дровяной печи, подходящей по объему парного отделения, обойдется дешевле электрической с учетом установки?" << endl << endl;
        Answer = Answer + "  \\item 2000 \n";
        break;

        case 2:
        cout << "\\item     На сколько рублей покупка дровяной печи, подходящей по объему парного отделения, обойдется дороже электрической без учета установки?" << endl << endl;
        Answer = Answer + "  \\item 4500 \n";
        break;
    }

    cout << "%" << i + 4 << endl; // 4
    typeother = rand()%2 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     На дровяную печь, масса которой 40 кг, сделали скидку 10\\%. Сколько рублей стала стоить печь?" << endl << endl;
        Answer = Answer + "  \\item 16200 \n";
        break;

        case 2:
        cout << "\\item     На дровяную печь, масса которой 48 кг, сделали скидку 10\\%. Сколько рублей стала стоить печь?" << endl << endl;
        Answer = Answer + "  \\item 17550 \n";
        break;
    }

    cout << "%" << i + 5 << endl; // 5
    typeother = rand()%2 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "Хозяин выбрал дровяную печь (рис. 1). Чертеж передней панели печи показан на рисунке 2." << endl
        << "\\begin{center}" << endl
        << "  \\begin{minipage}{0.5\\textwidth}" << endl 
        << "    \\centering" << endl
        << "    \\includegraphics[width=0.4\\linewidth]{Печи.png} % Немного меньше, чтобы точно поместиться" << endl
        << "  \\end{minipage}\\hfill" << endl
        << "  \\begin{minipage}{0.5\\textwidth}" << endl
        << "    \\centering" << endl
        << "    \\includegraphics[width=0.5\\linewidth]{Печи1.png} % Немного меньше, чтобы точно поместиться" << endl
        << "  \\end{minipage}" << endl
        << "\\end{center}" << endl
        << "Печь снабжена кожухом вокруг дверцы топки. Верхняя часть кожуха выполнена в виде арки, приваренной к передней стенке печки по дуге окружности с центром в середине нижней части кожуха (рис. 2). Для установки печки хозяину понадобилось узнать радиус закругления арки R. Размеры кожуха в сантиметрах показаны на рисунке. Найдите радиус закругления арки в сантиметрах." << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 65 \n";
        break;

        case 2:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "Хозяин выбрал дровяную печь (рис. 1). Чертеж передней панели печи показан на рисунке 2." << endl
        << "\\begin{center}" << endl
        << "  \\begin{minipage}{0.5\\textwidth}" << endl 
        << "    \\centering" << endl
        << "    \\includegraphics[width=0.4\\linewidth]{Печи.png} % Немного меньше, чтобы точно поместиться" << endl
        << "  \\end{minipage}\\hfill" << endl
        << "  \\begin{minipage}{0.5\\textwidth}" << endl
        << "    \\centering" << endl
        << "    \\includegraphics[width=0.5\\linewidth]{Печи2.png} % Немного меньше, чтобы точно поместиться" << endl
        << "  \\end{minipage}" << endl
        << "\\end{center}" << endl
        << "Печь снабжена кожухом вокруг дверцы топки. Верхняя часть кожуха выполнена в виде арки, приваренной к передней стенке печки по дуге окружности с центром в середине нижней части кожуха (рис. 2). Для установки печки хозяину понадобилось узнать радиус закругления арки R. Размеры кожуха в сантиметрах показаны на рисунке. Найдите радиус закругления арки в сантиметрах." << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 50 \n";
        break;
    }
    return Answer;
}

string FirstFiveTarif(int i, int AllType)
{
    string Answer;
    int typeother;
    cout << "%" << i + 1 << endl; // 1
    cout << "\\item" << endl
        << "\\begin{minipage}[t]{\\linewidth}" << endl
        << "На рисунке точками показано количество минут исходящих вызовов и трафик мобильного интернета в гигабайтах, израсходованных абонентом в процессе пользования смартфоном, за каждый месяц 2019 года. Для удобства точки, соответствующие минутам и гигабайтам, соединены сплошными и пунктирными линиями соответственно." << endl
        << "\\begin{center}" << endl
        << "\\includegraphics[width=0.8\\textwidth]{Тарифы.png}" << endl
        << "\\end{center}" << endl
        << "В течение года абонент пользовался тарифом «Стандартный», абонентская плата по которому составляла 350 рублей в месяц. При условии нахождения абонента на территории РФ в абонентскую плату тарифа «Стандартный» входит:" << endl
        << "\\begin{itemize}" << endl
        << "\\item пакет минут, включающий 300 минут исходящих вызовов на номера, зарегистрированные на территории РФ;" << endl
        << "\\item  пакет интернета, включающий 3 гигабайта мобильного интернета;" << endl
        << "\\item пакет СМС, включающий 120 СМС в месяц;" << endl
        << "\\item безлимитные бесплатные входящие вызовы." << endl
        << "\\end{itemize}" << endl
        << "Стоимость минут, интернета и СМС сверх пакета тарифа указана в таблице." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Исходящие вызовы & 3 руб./мин. \\\\ \\hline" << endl
        << "Мобильный интернет (пакет) & 90 руб. за 0,5 Гб \\\\ \\hline" << endl
        << "СМС & 2 руб./шт. \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "Абонент не пользовался услугами связи в роуминге. За весь год абонент отправил 110 СМС." << endl
        << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
    typeother = rand()%5 + 1;
    switch(typeother)
    {
        case 1:
        cout << "Определите, какие месяцы соответствуют указанному в таблице трафику мобильного интернета. Заполните таблицу, в бланк ответов перенесите числа, соответствующие номерам месяцев, без пробелов, запятых и других дополнительных символов (например, для месяцев май, январь, ноябрь, август в ответе нужно записать число 51118)." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Мобильный интернет & 1,5 ГБ & 2 ГБ & 3,75 ГБ & 1 ГБ \\\\ \\hline" << endl
        << "Номер месяца &  &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 83117 \n";
        break;

        case 2:
        cout << "Определите, какие месяцы соответствуют указанному в таблице трафику мобильного интернета. Заполните таблицу, в бланк ответов перенесите числа, соответствующие номерам месяцев, без пробелов, запятых и других дополнительных символов (например, для месяцев май, январь, ноябрь, август в ответе нужно записать число 51118)." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Мобильный интернет & 2 ГБ & 2,25 ГБ & 4 ГБ & 3,5 ГБ \\\\ \\hline" << endl
        << "Номер месяца &  &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 31242 \n";
        break;

        case 3:
        cout << "Определите, какие месяцы соответствуют указанному в таблице трафику мобильного интернета. Заполните таблицу, в бланк ответов перенесите числа, соответствующие номерам месяцев, без пробелов, запятых и других дополнительных символов (например, для месяцев май, январь, ноябрь, август в ответе нужно записать число 51118)." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Исходящие вызовы & 150 мин. & 300 мин. & 175 мин. & 375 мин. \\\\ \\hline" << endl
        << "Номер месяца &  &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 3517 \n";
        break;

        case 4:
        cout << "Определите, какие месяцы соответствуют указанному в таблице трафику мобильного интернета. Заполните таблицу, в бланк ответов перенесите числа, соответствующие номерам месяцев, без пробелов, запятых и других дополнительных символов (например, для месяцев май, январь, ноябрь, август в ответе нужно записать число 51118)." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Исходящие вызовы & 175 мин. & 300 мин. & 275 мин. & 150 мин. \\\\ \\hline" << endl
        << "Номер месяца &  &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 1523 \n";
        break;

        case 5:
        cout << "Определите, какие месяцы соответствуют указанному в таблице трафику мобильного интернета. Заполните таблицу, в бланк ответов перенесите числа, соответствующие номерам месяцев, без пробелов, запятых и других дополнительных символов (например, для месяцев май, январь, ноябрь, август в ответе нужно записать число 51118)." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\small Исходящие вызовы & 375 мин. & 150 мин. & 275 мин. & 300 мин. \\\\ \\hline" << endl
        << "Номер месяца &  &  & & \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl
        << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 7325 \n";
        break;
    }

    cout << "%" << i + 2 << endl; // 2
    typeother = rand()%5 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     Сколько рублей потратил абонент на услуги связи в июне?" << endl << endl;
        Answer = Answer + "  \\item 425 \n";
        break;

        case 2:
        cout << "\\item     Сколько рублей потратил абонент на услуги связи в июле?" << endl << endl;
        Answer = Answer + "  \\item 575 \n";
        break;

        case 3:
        cout << "\\item     Сколько рублей потратил абонент на услуги связи в августе?" << endl << endl;
        Answer = Answer + "  \\item 425 \n";
        break;

        case 4:
        cout << "\\item     Сколько рублей потратил абонент на услуги связи в апреле?" << endl << endl;
        Answer = Answer + "  \\item 680 \n";
        break;

        case 5:
        cout << "\\item     Сколько рублей потратил абонент на услуги связи в декабре?" << endl << endl;
        Answer = Answer + "  \\item 500 \n";
        break;
    }

    cout << "%" << i + 3 << endl; // 3
    typeother = rand()%5 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     Сколько месяцев в 2019 году абонент не превышал лимит ни по пакету минут, ни по пакету мобильного интернета?" << endl << endl;
        Answer = Answer + "  \\item 4 \n";
        break;

        case 2:
        cout << "\\item     Сколько месяцев в 2019 году абонент превысил лимит и по пакету минут, и по пакету мобильного интернета?" << endl << endl;
        Answer = Answer + "  \\item 2 \n";
        break;

        case 3:
        cout << "\\item     Сколько месяцев в 2019 году расходы по тарифу составили ровно 350 рублей?" << endl << endl;
        Answer = Answer + "  \\item 4 \n";
        break;

        case 4:
        cout << "\\item     Какое наименьшее количество минут исходящих вызовов за месяц было в 2019 году?" << endl << endl;
        Answer = Answer + "  \\item 150 \n";
        break;

        case 5:
        cout << "\\item     Какой наименьший трафик мобильного интернета в гигабайтах за месяц был в 2019 году?" << endl << endl;
        Answer = Answer + "  \\item 1 \n";
        break;
    }

    cout << "%" << i + 4 << endl; // 4
    typeother = rand()%5 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item     На сколько процентов увеличился трафик мобильного интернета в августе по сравнению с июлем 2019 года?" << endl << endl;
        Answer = Answer + "  \\item 50 \n";
        break;

        case 2:
        cout << "\\item     Известно, что в 2018 году абонентская плата по тарифу «Стандартный» составляла 200 рублей. На сколько процентов выросла абонентская плата в 2019 году по сравнению с 2018 годом?" << endl << endl;
        Answer = Answer + "  \\item 75 \n";
        break;

        case 3:
        cout << "\\item     Известно, что в 2019 году абонентская плата по тарифу «Стандартный» выросла на 75\\% по сравнению с 2018 годом. Сколько рублей составляла абонентская плата в 2018 году?" << endl << endl;
        Answer = Answer + "  \\item 200 \n";
        break;

        case 4:
        cout << "\\item     Известно, что в 2019 году абонентская плата по тарифу «Стандартный» снизилась на 30\\% по сравнению с 2018 годом. Сколько рублей составляла абонентская плата в 2018 году?" << endl << endl;
        Answer = Answer + "  \\item 500 \n";
        break;

        case 5:
        cout << "\\item     В январе 2020 года абонентская плата по тарифу «Стандартный» повысилась и составила 490 рублей. На сколько процентов повысилась абонентская плата?" << endl << endl;
        Answer = Answer + "  \\item 40 \n";
        break;
    }

    cout << "%" << i + 5 << endl; // 5
    typeother = rand()%5 + 1;
    switch(typeother)
    {
        case 1:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "В конце 2019 года оператор связи предложил абоненту перейти на новый тариф, условия которого приведены в таблице." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|}" << endl
        << "\\hline" << endl
        << "\\textbf{Стоимость перехода на тариф} & 0 руб. \\\\ \\hline" << endl
        << "\\textbf{Абонентская плата в месяц} & 460 руб. \\\\ \\hline" << endl
        << "\\multicolumn{2}{|l|}{\\textbf{В абонентскую плату включены пакеты:}} \\\\ \\hline" << endl
        << "пакет исходящих вызовов & 400 минут \\\\ \\hline" << endl
        << "пакет мобильного интернета & 4 ГБ \\\\ \\hline" << endl
        << "пакет SMS & 130 SMS \\\\ \\hline" << endl
        << "\\multicolumn{2}{|l|}{\\textbf{После расходования пакетов:}} \\\\ \\hline" << endl
        << "входящие вызовы & 0 руб./мин. \\\\ \\hline" << endl
        << "исходящие вызовы & 4 руб./мин. \\\\ \\hline" << endl
        << "мобильный интернет (пакет) & 160 руб. за 0,5 ГБ \\\\ \\hline" << endl
        << "SMS & 2 руб./шт. \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl;
        cout << "Абонент решает, перейти ли ему на новый тариф, посчитав, сколько бы он потратил на услуги связи за 2019 г., если бы пользовался им. Если получится меньше, чем он потратил фактически за 2019 г., то абонент примет решение сменить тариф. Перейдѐт ли абонент на новый тариф? В ответе запишите ежемесячную абонентскую плату по тарифу, который выберет абонент на 2020 год." << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 350 \n";
        break;

        case 2:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "В конце 2019 года оператор связи предложил абоненту перейти на новый тариф, условия которого приведены в таблице." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|}" << endl
        << "\\hline" << endl
        << "\\textbf{Стоимость перехода на тариф} & 0 руб. \\\\ \\hline" << endl
        << "\\textbf{Абонентская плата в месяц} & 430 руб. \\\\ \\hline" << endl
        << "\\multicolumn{2}{|l|}{\\textbf{В абонентскую плату включены пакеты:}} \\\\ \\hline" << endl
        << "пакет исходящих вызовов & 400 минут \\\\ \\hline" << endl
        << "пакет мобильного интернета & 4 ГБ \\\\ \\hline" << endl
        << "пакет SMS & 120 SMS \\\\ \\hline" << endl
        << "\\multicolumn{2}{|l|}{\\textbf{После расходования пакетов:}} \\\\ \\hline" << endl
        << "входящие вызовы & 0 руб./мин. \\\\ \\hline" << endl
        << "исходящие вызовы & 4 руб./мин. \\\\ \\hline" << endl
        << "мобильный интернет (пакет) & 180 руб. за 0,5 ГБ \\\\ \\hline" << endl
        << "SMS & 2 руб./шт. \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl;
        cout << "Абонент решает, перейти ли ему на новый тариф, посчитав, сколько бы он потратил на услуги связи за 2019 г., если бы пользовался им. Если получится меньше, чем он потратил фактически за 2019 г., то абонент примет решение сменить тариф. Перейдѐт ли абонент на новый тариф? В ответе запишите ежемесячную абонентскую плату по тарифу, который выберет абонент на 2020 год." << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 430 \n";
        break;

        case 3:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "В конце 2019 года оператор связи предложил абоненту перейти на новый тариф, условия которого приведены в таблице." << endl
        << "\\begin{center}" << endl
        << "\\begin{tabular}{|l|l|}" << endl
        << "\\hline" << endl
        << "\\textbf{Стоимость перехода на тариф} & 0 руб. \\\\ \\hline" << endl
        << "\\textbf{Абонентская плата в месяц} & 470 руб. \\\\ \\hline" << endl
        << "\\multicolumn{2}{|l|}{\\textbf{В абонентскую плату включены пакеты:}} \\\\ \\hline" << endl
        << "пакет исходящих вызовов & 400 минут \\\\ \\hline" << endl
        << "пакет мобильного интернета & 4 ГБ \\\\ \\hline" << endl
        << "пакет SMS & 120 SMS \\\\ \\hline" << endl
        << "\\multicolumn{2}{|l|}{\\textbf{После расходования пакетов:}} \\\\ \\hline" << endl
        << "входящие вызовы & 0 руб./мин. \\\\ \\hline" << endl
        << "исходящие вызовы & 4 руб./мин. \\\\ \\hline" << endl
        << "мобильный интернет (пакет) & 160 руб. за 0,5 ГБ \\\\ \\hline" << endl
        << "SMS & 2 руб./шт. \\\\ \\hline" << endl
        << "\\end{tabular}" << endl
        << "\\end{center}" << endl;
        cout << "Абонент решает, перейти ли ему на новый тариф, посчитав, сколько бы он потратил на услуги связи за 2019 г., если бы пользовался им. Если получится меньше, чем он потратил фактически за 2019 г., то абонент примет решение сменить тариф. Перейдѐт ли абонент на новый тариф? В ответе запишите ежемесячную абонентскую плату по тарифу, который выберет абонент на 2020 год." << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 350 \n";
        break;

        case 4:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "Помимо мобильного интернета, абонент использует домашний интернет от провайдера «Омега». Этот интернет-провайдер предлагает три тарифных плана. Условия приведены в таблице." << endl
        << "\\begin{center}" << endl
        << "\\resizebox{\\linewidth}{!}{%" << endl
        << "\\begin{tabular}{|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\textbf{Тарифный план} & \\textbf{Абонентская плата} & \\textbf{Плата за трафик} \\\\ \\hline" << endl
        << "«0» & Нет & 1,1 руб. за 1 МБ \\\\ \\hline" << endl
        << "200 & 204 руб. за 200 МБ трафика в месяц & 1,2 руб. за 1 МБ сверх 200 МБ \\\\ \\hline" << endl
        << "700 & 672 руб. за 700 МБ трафика в месяц & 0,5 руб. за 1 МБ сверх 700 МБ \\\\ \\hline" << endl
        << "\\end{tabular}" << endl << "}" << endl
        << "\\end{center}" << endl;
        cout << "Абонент предполагает, что трафик составит 700 Мб в месяц, и выбирает наиболее дешѐвый тарифный план. Сколько рублей должен будет заплатить абонент за месяц, если трафик действительно будет равен 700 Мб?" << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 880 \n";
        break;

        case 5:
        cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
        << "Помимо мобильного интернета, абонент использует домашний интернет от провайдера «Омега». Этот интернет-провайдер предлагает три тарифных плана. Условия приведены в таблице." << endl
        << "\\begin{center}" << endl
        << "\\resizebox{\\linewidth}{!}{%" << endl
        << "\\begin{tabular}{|l|l|l|}" << endl
        << "\\hline" << endl
        << "\\textbf{Тарифный план} & \\textbf{Абонентская плата} & \\textbf{Плата за трафик} \\\\ \\hline" << endl
        << "«0» & Нет & 1,1 руб. за 1 МБ \\\\ \\hline" << endl
        << "300 & 290 руб. за 300 МБ трафика в месяц & 1,2 руб. за 1 МБ сверх 300 МБ \\\\ \\hline" << endl
        << "800 & 930 руб. за 800 МБ трафика в месяц & 0,5 руб. за 1 МБ сверх 800 МБ \\\\ \\hline" << endl
        << "\\end{tabular}" << endl << "}" << endl
        << "\\end{center}" << endl;
        cout << "Абонент предполагает, что трафик составит 800 Мб в месяц, и выбирает наиболее дешѐвый тарифный план. Сколько рублей должен будет заплатить абонент за месяц, если трафик действительно будет равен 800 Мб?" << endl
            << "\\end{minipage}" << endl << endl;
        Answer = Answer + "  \\item 880 \n";
        break;
    }
    return Answer;
}

string FirstFiveDacha(int i, int AllType)
{
    string Answer;
    int type = rand()%2 + 1;
    int typeother;
    switch(type)
    {
        case 1:
        cout << "%" << i + 1 << endl; // 1
        cout << "\\item" << endl
        << "\\begin{minipage}[t]{\\linewidth}" << endl
        << "\\begin{center}" << endl
        << "\\includegraphics[width=0.8\\textwidth]{Дача1.png}" << endl
        << "\\end{center}" << endl
        << "На плане изображѐн дачный участок по адресу: п. Сосновка, ул. Зелѐная, д. 19 (сторона каждой клетки на плане равна 2 м). Участок имеет прямоугольную форму. Выезд и въезд осуществляются через единственные ворота. При входе на участок слева от ворот находится гараж. Справа от ворот находится сарай площадью 24 кв. м, а чуть подальше -- жилой дом. Напротив жилого дома расположены яблоневые посадки. Также на участке есть баня, к которой ведѐт дорожка, выложенная плиткой, и огород с теплицей внутри (огород отмечен на плане цифрой 6). Все дорожки внутри участка имеют ширину 1 м и вымощены тротуарной плиткой размером 1м х 1м. Между гаражом и сараем находится площадка, вымощенная такой же плиткой. К участку подведено электричество. Имеется магистральное газоснабжение." << endl
        << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
        typeother = rand()%4 + 1;
        switch(typeother)
        {
            case 1:
            cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк ответов перенесите последовательность четырѐх цифр." << endl
            << "\\begin{center}" << endl
            << "\\begin{tabular}{|l|l|l|l|l|}" << endl
            << "\\hline" << endl
            << "\\small Объекты & жилой дом & баня & гараж & теплица \\\\ \\hline" << endl
            << "Цифры &  &  & & \\\\ \\hline" << endl
            << "\\end{tabular}" << endl
            << "\\end{center}" << endl
            << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 7425 \n";
            break;

            case 2:
            cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк ответов перенесите последовательность четырѐх цифр." << endl
            << "\\begin{center}" << endl
            << "\\begin{tabular}{|l|l|l|l|l|}" << endl
            << "\\hline" << endl
            << "\\small Объекты & яблони & теплица & сарай & жилой дом \\\\ \\hline" << endl
            << "Цифры &  &  & & \\\\ \\hline" << endl
            << "\\end{tabular}" << endl
            << "\\end{center}" << endl
            << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 3517 \n";
            break;

            case 3:
            cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк ответов перенесите последовательность четырѐх цифр." << endl
            << "\\begin{center}" << endl
            << "\\begin{tabular}{|l|l|l|l|l|}" << endl
            << "\\hline" << endl
            << "\\small Объекты & жилой дом & яблони & теплица & гараж \\\\ \\hline" << endl
            << "Цифры &  &  & & \\\\ \\hline" << endl
            << "\\end{tabular}" << endl
            << "\\end{center}" << endl
            << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 7352 \n";
            break;

            case 4:
            cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк ответов перенесите последовательность четырѐх цифр." << endl
            << "\\begin{center}" << endl
            << "\\begin{tabular}{|l|l|l|l|l|}" << endl
            << "\\hline" << endl
            << "\\small Объекты & гараж & баня & жилой дом & яблони \\\\ \\hline" << endl
            << "Цифры &  &  & & \\\\ \\hline" << endl
            << "\\end{tabular}" << endl
            << "\\end{center}" << endl
            << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 2473 \n";
            break;
        }

        cout << "%" << i + 2 << endl; // 2
        typeother = rand()%4 + 1;
        switch(typeother)
        {
            case 1:
            cout << "\\item     Плитки для садовых дорожек продаются в упаковках по 10 штук. Сколько упаковок плиток понадобилось, чтобы выложить все дорожки и площадку между сараем и гаражом?" << endl << endl;
            Answer = Answer + "  \\item 7 \n";
            break;

            case 2:
            cout << "\\item     Плитки для садовых дорожек продаются в упаковках по 8 штук. Сколько упаковок плиток понадобилось, чтобы выложить все дорожки и площадку между сараем и гаражом?" << endl << endl;
            Answer = Answer + "  \\item 9 \n";
            break;

            case 3:
            cout << "\\item     Плитки для садовых дорожек продаются в упаковках по 6 штук. Сколько упаковок плиток понадобилось, чтобы выложить все дорожки?" << endl << endl;
            Answer = Answer + "  \\item 5 \n";
            break;

            case 4:
            cout << "\\item     Плитки для садовых дорожек продаются в упаковках по 4 штуки. Сколько упаковок плиток понадобилось, чтобы выложить все дорожки?" << endl << endl;
            Answer = Answer + "  \\item 7 \n";
            break;
        }

        cout << "%" << i + 3 << endl; // 3
        typeother = rand()%4 + 1;
        switch(typeother)
        {
            case 1:
            cout << "\\item     Найдите периметр фундамента жилого дома. Ответ дайте в метрах." << endl << endl;
            Answer = Answer + "  \\item 36 \n";
            break;

            case 2:
            cout << "\\item     Найдите расстояние от жилого дома до гаража (расстояние между двумя ближайшими точками по прямой) в метрах." << endl << endl;
            Answer = Answer + "  \\item 6 \n";
            break;

            case 3:
            cout << "\\item     Найдите площадь, которую занимает баня. Ответ дайте в квадратных метрах." << endl << endl;
            Answer = Answer + "  \\item 36 \n";
            break;

            case 4:
            cout << "\\item     Найдите площадь открытого грунта огорода (вне теплицы). Ответ дайте в квадратных метрах." << endl << endl;
            Answer = Answer + "  \\item 108 \n";
            break;
        }

        cout << "%" << i + 4 << endl; // 4
        typeother = rand()%4 + 1;
        switch(typeother)
        {
            case 1:
            cout << "\\item     Сколько процентов от площади всего участка занимают строения (жилой дом, гараж, сарай, баня)? Ответ округлите до целого." << endl << endl;
            Answer = Answer + "  \\item 29 \n";
            break;

            case 2:
            cout << "\\item     Сколько процентов от площади всего огорода занимает теплица?" << endl << endl;
            Answer = Answer + "  \\item 10 \n";
            break;

            case 3:
            cout << "\\item     На сколько процентов площадь, которую занимает теплица, меньше площади, которую занимает гараж?" << endl << endl;
            Answer = Answer + "  \\item 75 \n";
            break;

            case 4:
            cout << "\\item     На сколько процентов площадь, которую занимает гараж, больше площади, которую занимает теплица?" << endl << endl;
            Answer = Answer + "  \\item 300 \n";
            break;
        }

        cout << "%" << i + 5 << endl; // 5
        typeother = rand()%4 + 1;
        switch(typeother)
        {
            case 1:
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
            << "Хозяин участка планирует установить в жилом доме систему отопления. Он рассматривает два варианта: электрическое или газовое отопление. Цены на оборудование и стоимость его установки, данные о расходе газа, электроэнергии и их стоимости даны в таблице." << endl
            << "\\begin{center}" << endl
            << "\\resizebox{\\linewidth}{!}{%" << endl
            << "\\begin{tabular}{|l|p{2.3cm}|p{2.175cm}|p{3.5cm}|p{3.5cm}|}" << endl
            << "\\hline" << endl
            << "& \\textbf{Нагреватель (котёл)} & \\textbf{Прочее оборудование и монтаж} & \\textbf{Средн. расход газа / средн. потребл. мощность} & \\textbf{Стоимость газа/электроэнергии} \\\\ \\hline" << endl
            << "Газовое отопление & 20 000 руб. & 15 370 руб. & 1,6 куб. м/ч & 4,9 руб./куб. м \\\\ \\hline" << endl
            << "Электрическое отопление & 15 000 руб. & 14 000 руб. & 4,9 кВт & 4,2 руб./(кВт·ч) \\\\ \\hline" << endl
            << "\\end{tabular}" << endl << "}" << endl
            << "\\end{center}" << endl;
            cout << "Обдумав оба варианта, хозяин решил установить газовое отопление. Через сколько часов непрерывной работы отопления экономия от использования газа вместо электричества компенсирует разницу в стоимости покупки и установки газового и электрического оборудования?" << endl
                << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 500 \n";
            break;

            case 2:
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
            << "Хозяин участка планирует установить в жилом доме систему отопления. Он рассматривает два варианта: электрическое или газовое отопление. Цены на оборудование и стоимость его установки, данные о расходе газа, электроэнергии и их стоимости даны в таблице." << endl
            << "\\begin{center}" << endl
            << "\\resizebox{\\linewidth}{!}{%" << endl
            << "\\begin{tabular}{|l|p{2.3cm}|p{2.175cm}|p{3.5cm}|p{3.5cm}|}" << endl
            << "\\hline" << endl
            << "& \\textbf{Нагреватель (котёл)} & \\textbf{Прочее оборудование и монтаж} & \\textbf{Средн. расход газа / средн. потребл. мощность} & \\textbf{Стоимость газа/электроэнергии} \\\\ \\hline" << endl
            << "Газовое отопление & 18 000 руб. & 13 896 руб. & 1,6 куб. м/ч & 4,7 руб./куб. м \\\\ \\hline" << endl
            << "Электрическое отопление & 15 000 руб. & 9 000 руб. & 4,7 кВт & 4,4 руб./(кВт·ч) \\\\ \\hline" << endl
            << "\\end{tabular}" << endl << "}" << endl
            << "\\end{center}" << endl;
            cout << "Обдумав оба варианта, хозяин решил установить газовое отопление. Через сколько часов непрерывной работы отопления экономия от использования газа вместо электричества компенсирует разницу в стоимости покупки и установки газового и электрического оборудования?" << endl
                << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 600 \n";
            break;

            case 3:
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
            << "Хозяин участка планирует установить в жилом доме систему отопления. Он рассматривает два варианта: электрическое или газовое отопление. Цены на оборудование и стоимость его установки, данные о расходе газа, электроэнергии и их стоимости даны в таблице." << endl
            << "\\begin{center}" << endl
            << "\\resizebox{\\linewidth}{!}{%" << endl
            << "\\begin{tabular}{|l|p{2.3cm}|p{2.175cm}|p{3.5cm}|p{3.5cm}|}" << endl
            << "\\hline" << endl
            << "& \\textbf{Нагреватель (котёл)} & \\textbf{Прочее оборудование и монтаж} & \\textbf{Средн. расход газа / средн. потребл. мощность} & \\textbf{Стоимость газа/электроэнергии} \\\\ \\hline" << endl
            << "Газовое отопление & 25 000 руб. & 17 552 руб. & 1,3 куб. м/ч & 5,2 руб./куб. м \\\\ \\hline" << endl
            << "Электрическое отопление & 21 000 руб. & 15 000 руб. & 5,2 кВт & 4,1 руб./(кВт·ч) \\\\ \\hline" << endl
            << "\\end{tabular}" << endl << "}" << endl
            << "\\end{center}" << endl;
            cout << "Обдумав оба варианта, хозяин решил установить газовое отопление. Через сколько часов непрерывной работы отопления экономия от использования газа вместо электричества компенсирует разницу в стоимости покупки и установки газового и электрического оборудования?" << endl
                << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 450 \n";
            break;

            case 4:
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
            << "Хозяин участка планирует установить в жилом доме систему отопления. Он рассматривает два варианта: электрическое или газовое отопление. Цены на оборудование и стоимость его установки, данные о расходе газа, электроэнергии и их стоимости даны в таблице." << endl
            << "\\begin{center}" << endl
            << "\\resizebox{\\linewidth}{!}{%" << endl
            << "\\begin{tabular}{|l|p{2.3cm}|p{2.175cm}|p{3.5cm}|p{3.5cm}|}" << endl
            << "\\hline" << endl
            << "& \\textbf{Нагреватель (котёл)} & \\textbf{Прочее оборудование и монтаж} & \\textbf{Средн. расход газа / средн. потребл. мощность} & \\textbf{Стоимость газа/электроэнергии} \\\\ \\hline" << endl
            << "Газовое отопление & 22 000 руб. & 20 105 руб. & 1,5 куб. м/ч & 4,9 руб./куб. м \\\\ \\hline" << endl
            << "Электрическое отопление & 19 000 руб. & 16 000 руб. & 4,9 кВт & 4,4 руб./(кВт·ч) \\\\ \\hline" << endl
            << "\\end{tabular}" << endl << "}" << endl
            << "\\end{center}" << endl;
            cout << "Обдумав оба варианта, хозяин решил установить газовое отопление. Через сколько часов непрерывной работы отопления экономия от использования газа вместо электричества компенсирует разницу в стоимости покупки и установки газового и электрического оборудования?" << endl
                << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 500 \n";
            break;
        }
        break;

        case 2:
        cout << "%" << i + 1 << endl; // 1
        cout << "\\item" << endl
        << "\\begin{minipage}[t]{\\linewidth}" << endl
        << "\\begin{center}" << endl
        << "\\includegraphics[width=0.8\\textwidth]{Дача2.png}" << endl
        << "\\end{center}" << endl
        << "На плане изображено домохозяйство по адресу: с. Авдеево, 3-й Поперечный пер., д. 13 (сторона каждой клетки на плане равна 2 м). Участок имеет прямоугольную форму. Выезд и въезд осуществляются через единственные ворота. При входе на участок справа от ворот находится баня, а слева — гараж, отмеченный на плане цифрой 7. Площадь, занятая гаражом, равна 32 кв. м. Жилой дом находится в глубине территории. Помимо гаража, жилого дома и бани, на участке имеется сарай (подсобное помещение), расположенный рядом с гаражом, и теплица, построенная на территории огорода (огород отмечен цифрой 2). Перед жилым домом имеются яблоневые посадки. Все дорожки внутри участка имеют ширину 1 м и вымощены тротуарной плиткой размером 1м х 1м. Между баней и гаражом имеется площадка площадью 64 кв. м, вымощенная такой же плиткой. К домохозяйству подведено электричество. Имеется магистральное газоснабжение." << endl
        << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
        typeother = rand()%2 + 1;
        switch(typeother)
        {
            case 1:
            cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк ответов перенесите последовательность четырѐх цифр." << endl
            << "\\begin{center}" << endl
            << "\\begin{tabular}{|l|l|l|l|l|}" << endl
            << "\\hline" << endl
            << "\\small Объекты & жилой дом & сарай & баня & теплица \\\\ \\hline" << endl
            << "Цифры &  &  & & \\\\ \\hline" << endl
            << "\\end{tabular}" << endl
            << "\\end{center}" << endl
            << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 3461 \n";
            break;

            case 2:
            cout << "Для объектов, указанных в таблице, определите, какими цифрами они обозначены на плане. Заполните таблицу, в бланк ответов перенесите последовательность четырѐх цифр." << endl
            << "\\begin{center}" << endl
            << "\\begin{tabular}{|l|l|l|l|l|}" << endl
            << "\\hline" << endl
            << "\\small Объекты & яблони & теплица & жилой дом & баня \\\\ \\hline" << endl
            << "Цифры &  &  & & \\\\ \\hline" << endl
            << "\\end{tabular}" << endl
            << "\\end{center}" << endl
            << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 5136 \n";
            break;
        }

        cout << "%" << i + 2 << endl; // 2
        typeother = rand()%2 + 1;
        switch(typeother)
        {
            case 1:
            cout << "\\item     Тротуарная плитка продаѐтся в упаковках по 4 штуки. Сколько упаковок плитки понадобилось, чтобы выложить все дорожки и площадку перед гаражом?" << endl << endl;
            Answer = Answer + "  \\item 23 \n";
            break;

            case 2:
            cout << "\\item     Тротуарная плитка продаѐтся в упаковках по 5 штук. Сколько упаковок плитки понадобилось, чтобы выложить все дорожки?" << endl << endl;
            Answer = Answer + "  \\item 6 \n";
            break;
        }

        cout << "%" << i + 3 << endl; // 3
        typeother = rand()%2 + 1;
        switch(typeother)
        {
            case 1:
            cout << "\\item     Найдите площадь, которую занимает жилой дом. Ответ дайте в квадратных метрах." << endl << endl;
            Answer = Answer + "  \\item 68 \n";
            break;

            case 2:
            cout << "\\item     Найдите площадь открытого грунта огорода (вне теплицы). Ответ дайте в квадратных метрах." << endl << endl;
            Answer = Answer + "  \\item 72 \n";
            break;
        }

        cout << "%" << i + 4 << endl; // 4
        typeother = rand()%2 + 1;
        switch(typeother)
        {
            case 1:
            cout << "\\item     Найдите расстояние от жилого дома до гаража (расстояние между двумя ближайшими точками по прямой) в метрах." << endl << endl;
            Answer = Answer + "  \\item 10 \n";
            break;

            case 2:
            cout << "\\item     Найдите расстояние от ворот до сарая (расстояние между двумя ближайшими точками по прямой) в метрах." << endl << endl;
            Answer = Answer + "  \\item 10 \n";
            break;
        }

        cout << "%" << i + 5 << endl; // 5
        typeother = rand()%2 + 1;
        switch(typeother)
        {
            case 1:
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
            << "Хозяин участка планирует установить в жилом доме систему отопления. Он рассматривает два варианта: электрическое или газовое отопление. Цены на оборудование и стоимость его установки, данные о расходе газа, электроэнергии и их стоимости даны в таблице." << endl
            << "\\begin{center}" << endl
            << "\\resizebox{\\linewidth}{!}{%" << endl
            << "\\begin{tabular}{|l|p{2.3cm}|p{2.175cm}|p{3.5cm}|p{3.5cm}|}" << endl
            << "\\hline" << endl
            << "& \\textbf{Нагреватель (котёл)} & \\textbf{Прочее оборудование и монтаж} & \\textbf{Средн. расход газа / средн. потребл. мощность} & \\textbf{Стоимость газа/электроэнергии} \\\\ \\hline" << endl
            << "Газовое отопление & 24 000 руб. & 18 280 руб. & 1,2 куб. м/ч & 5,6 руб./куб. м \\\\ \\hline" << endl
            << "Электрическое отопление & 20 000 руб. & 15 000 руб. & 5,6 кВт & 3,8 руб./(кВт·ч) \\\\ \\hline" << endl
            << "\\end{tabular}" << endl << "}" << endl
            << "\\end{center}" << endl;
            cout << "Обдумав оба варианта, хозяин решил установить газовое отопление. Через сколько часов непрерывной работы отопления экономия от использования газа вместо электричества компенсирует разницу в стоимости покупки и установки газового и электрического оборудования?" << endl
                << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 500 \n";
            break;

            case 2:
            cout << "\\item  \\begin{minipage}[t]{\\linewidth}" << endl
            << "Хозяин участка планирует установить в жилом доме систему отопления. Он рассматривает два варианта: электрическое или газовое отопление. Цены на оборудование и стоимость его установки, данные о расходе газа, электроэнергии и их стоимости даны в таблице." << endl
            << "\\begin{center}" << endl
            << "\\resizebox{\\linewidth}{!}{%" << endl
            << "\\begin{tabular}{|l|p{2.3cm}|p{2.175cm}|p{3.5cm}|p{3.5cm}|}" << endl
            << "\\hline" << endl
            << "& \\textbf{Нагреватель (котёл)} & \\textbf{Прочее оборудование и монтаж} & \\textbf{Средн. расход газа / средн. потребл. мощность} & \\textbf{Стоимость газа/электроэнергии} \\\\ \\hline" << endl
            << "Газовое отопление & 22 000 руб. & 14 580 руб. & 1,4 куб. м/ч & 5,5 руб./куб. м \\\\ \\hline" << endl
            << "Электрическое отопление & 15 000 руб. & 13 000 руб. & 5,6 кВт & 3,8 руб./(кВт·ч) \\\\ \\hline" << endl
            << "\\end{tabular}" << endl << "}" << endl
            << "\\end{center}" << endl;
            cout << "Обдумав оба варианта, хозяин решил установить газовое отопление. Через сколько часов непрерывной работы отопления экономия от использования газа вместо электричества компенсирует разницу в стоимости покупки и установки газового и электрического оборудования?" << endl
                << "\\end{minipage}" << endl << endl;
            Answer = Answer + "  \\item 650 \n";
            break;
        }
        break;
    }
    return Answer;
}

string FirstFiveKolesa(int i, int AllType)
{
    string Answer;
    int type = rand()%8 + 1;
    int typeother;
    switch(type)
    {
        case 1:     // Тип 1 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.3\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.3\\textwidth]{Шины.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Автомобильное колесо, как правило, представляет из себя металлический диск с установленной на него резиновой шиной. Диаметр диска совпадает с диаметром внутреннего отверстия в шине. Для маркировки автомобильных шин применяется единая система обозначений. Например, 195/65 R15 (рис. 1). Первое число (число 195 в приведенном примере) обозначает ширину шины в миллиметрах (параметр B на рисунке 2). Второе число (число 65 в приведенном примере) — процентное отношение высоты боковины (параметр H на рисунке 2) к ширине шины, то есть $100\\cdot\\frac{H}{B}$. Последующая буква обозначает тип конструкции шины. В данном примере буква R означает, что шина радиальная, то есть нити каркаса в боковине шины расположены вдоль радиусов колеса. На всех легковых автомобилях применяются шины радиальной конструкции. За обозначением типа конструкции шины идет число, указывающее диаметр диска колеса d в дюймах (в одном дюйме 25,4 мм). Таким образом, общий диаметр колеса D легко найти, зная диаметр диска и высоту боковины. Возможны дополнительные маркировки, обозначающие допустимую нагрузку на шину, сезонность использования, тип дорожного покрытия и другие параметры. Завод производит внедорожники определѐнной модели и устанавливает на них колеса с шинами маркировки 215/65 R16." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Завод допускает установку шин с другими маркировками. В таблице показаны разрешенные размеры шин." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|c|c|c|c|}" << endl
                << "\\hline" << endl
                << "\\textbf{Ширина шины (мм)} & \\multicolumn{3}{c|}{\\textbf{Диаметр диска (дюймы)}} \\\\ \\cline{2-4} & \\textbf{16} & \\textbf{17} & \\textbf{18} \\\\ \\hline" << endl
                << "215 & 215/65 & 215/60 & — \\\\ \\hline" << endl
                << "225 & 225/65; 225/60 & 225/55 & — \\\\ \\hline" << endl
                << "235 & 235/60 & 235/55; 235/50 & 235/50 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "Шины какой наименьшей ширины можно устанавливать на автомобиль, если диаметр диска равен 17 дюймам? Ответ дайте в миллиметрах." << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 235 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров радиус колеса с шиной маркировки 215/55 R17 меньше, чем радиус колеса с шиной маркировки 275/50 R17?" << endl << endl;
                Answer = Answer + "  \\item 19,25 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров увеличится диаметр колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 235/50 R18?" << endl << endl;
                Answer = Answer + "  \\item 6,3 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите диаметр колеса автомобиля, выходящего с завода. Ответ дайте в миллиметрах." << endl << endl;
                Answer = Answer + "  \\item 685,9 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item     На сколько процентов увеличится пробег автомобиля при одном обороте колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 225/65 R16? Результат округлите до десятых." << endl << endl;
            Answer = Answer + "  \\item 1,9 \n";
            break;

        case 3:     // Тип 3 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.3\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.3\\textwidth]{Шины.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Автомобильное колесо, как правило, представляет из себя металлический диск с установленной на него резиновой шиной. Диаметр диска совпадает с диаметром внутреннего отверстия в шине. Для маркировки автомобильных шин применяется единая система обозначений. Например, 195/65 R15 (рис. 1). Первое число (число 195 в приведенном примере) обозначает ширину шины в миллиметрах (параметр B на рисунке 2). Второе число (число 65 в приведенном примере) — процентное отношение высоты боковины (параметр H на рисунке 2) к ширине шины, то есть $100\\cdot\\frac{H}{B}$. Последующая буква обозначает тип конструкции шины. В данном примере буква R означает, что шина радиальная, то есть нити каркаса в боковине шины расположены вдоль радиусов колеса. На всех легковых автомобилях применяются шины радиальной конструкции. За обозначением типа конструкции шины идет число, указывающее диаметр диска колеса d в дюймах (в одном дюйме 25,4 мм). Таким образом, общий диаметр колеса D легко найти, зная диаметр диска и высоту боковины. Возможны дополнительные маркировки, обозначающие допустимую нагрузку на шину, сезонность использования, тип дорожного покрытия и другие параметры. Завод производит внедорожники определѐнной модели и устанавливает на них колеса с шинами маркировки 265/60 R18." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Завод допускает установку шин с другими маркировками. В таблице показаны разрешенные размеры шин." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|c|c|c|c|c|}" << endl
                << "\\hline" << endl
                << "\\textbf{Ширина шины (мм)} & \\multicolumn{4}{c|}{\\textbf{Диаметр диска (дюймы)}} \\\\ \\cline{2-5} & \\textbf{17} & \\textbf{18} & \\textbf{19} & \\textbf{20} \\\\ \\hline" << endl
                << "245 & 245/70 & — & — & — \\\\ \\hline" << endl
                << "255 & 255/70 & 255/65 & — & — \\\\ \\hline" << endl
                << "265 & 265/65 & 265/60; 265/65 & — & — \\\\ \\hline" << endl
                << "275 & 275/65 & 275/60 & 275/55 & 275/50 \\\\ \\hline" << endl
                << "285 & — & 285/60 & 285/55 & 285/50 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "Шины какой наименьшей ширины можно устанавливать на автомобиль, если диаметр диска равен 17 дюймам? Ответ дайте в миллиметрах." << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 275 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров радиус колеса с шиной маркировки 245/70 R17 меньше, чем радиус колеса с шиной маркировки 275/65 R17?" << endl << endl;
                Answer = Answer + "  \\item 7,25 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров увеличится диаметр колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 285/50 R20?" << endl << endl;
                Answer = Answer + "  \\item 17,8 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите диаметр колеса автомобиля, выходящего с завода. Ответ дайте в миллиметрах." << endl << endl;
                Answer = Answer + "  \\item 775,2 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item     На сколько процентов увеличится пробег автомобиля при одном обороте колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 285/50 R20? Результат округлите до десятых." << endl << endl;
            Answer = Answer + "  \\item 2,3 \n";
            break;

        case 2:     // Тип 2 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.3\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.3\\textwidth]{Шины.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Автомобильное колесо, как правило, представляет из себя металлический диск с установленной на него резиновой шиной. Диаметр диска совпадает с диаметром внутреннего отверстия в шине. Для маркировки автомобильных шин применяется единая система обозначений. Например, 195/65 R15 (рис. 1). Первое число (число 195 в приведенном примере) обозначает ширину шины в миллиметрах (параметр B на рисунке 2). Второе число (число 65 в приведенном примере) — процентное отношение высоты боковины (параметр H на рисунке 2) к ширине шины, то есть $100\\cdot\\frac{H}{B}$. Последующая буква обозначает тип конструкции шины. В данном примере буква R означает, что шина радиальная, то есть нити каркаса в боковине шины расположены вдоль радиусов колеса. На всех легковых автомобилях применяются шины радиальной конструкции. За обозначением типа конструкции шины идет число, указывающее диаметр диска колеса d в дюймах (в одном дюйме 25,4 мм). Таким образом, общий диаметр колеса D легко найти, зная диаметр диска и высоту боковины. Возможны дополнительные маркировки, обозначающие допустимую нагрузку на шину, сезонность использования, тип дорожного покрытия и другие параметры. Завод производит внедорожники определѐнной модели и устанавливает на них колеса с шинами маркировки 185/60 R15." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Завод допускает установку шин с другими маркировками. В таблице показаны разрешенные размеры шин." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|c|c|c|c|c|}" << endl
                << "\\hline" << endl
                << "\\textbf{Ширина шины (мм)} & \\multicolumn{4}{c|}{\\textbf{Диаметр диска (дюймы)}} \\\\ \\cline{2-5} & \\textbf{14} & \\textbf{15} & \\textbf{16} & \\textbf{17} \\\\ \\hline" << endl
                << "175 & 175/70 & 175/65 & — & — \\\\ \\hline" << endl
                << "185 & 185/70 & 185/60 & 185/55 & — \\\\ \\hline" << endl
                << "195 & 195/65 & 195/60 & 195/50; 195/55 & 195/45 \\\\ \\hline" << endl
                << "205 & 205/60 & 205/55 & 205/50 & 205/45 \\\\ \\hline" << endl
                << "215 & — & — & 215/45 & 215/40 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "Шины какой наименьшей ширины можно устанавливать на автомобиль, если диаметр диска равен 16 дюймам? Ответ дайте в миллиметрах." << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 185 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров радиус колеса с шиной маркировки 175/65 R15 больше, чем радиус колеса с шиной маркировки 205/55 R15?" << endl << endl;
                Answer = Answer + "  \\item 1 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров увеличится диаметр колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 205/45 R17?" << endl << endl;
                Answer = Answer + "  \\item 13,3 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите диаметр колеса автомобиля, выходящего с завода. Ответ дайте в миллиметрах." << endl << endl;
                Answer = Answer + "  \\item 603 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item     На сколько процентов увеличится пробег автомобиля при одном обороте колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 205/45 R17? Результат округлите до десятых." << endl << endl;
            Answer = Answer + "  \\item 2,2 \n";
            break;

        case 4:     // Тип 4 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.3\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.3\\textwidth]{Шины.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Автомобильное колесо, как правило, представляет из себя металлический диск с установленной на него резиновой шиной. Диаметр диска совпадает с диаметром внутреннего отверстия в шине. Для маркировки автомобильных шин применяется единая система обозначений. Например, 195/65 R15 (рис. 1). Первое число (число 195 в приведенном примере) обозначает ширину шины в миллиметрах (параметр B на рисунке 2). Второе число (число 65 в приведенном примере) — процентное отношение высоты боковины (параметр H на рисунке 2) к ширине шины, то есть $100\\cdot\\frac{H}{B}$. Последующая буква обозначает тип конструкции шины. В данном примере буква R означает, что шина радиальная, то есть нити каркаса в боковине шины расположены вдоль радиусов колеса. На всех легковых автомобилях применяются шины радиальной конструкции. За обозначением типа конструкции шины идет число, указывающее диаметр диска колеса d в дюймах (в одном дюйме 25,4 мм). Таким образом, общий диаметр колеса D легко найти, зная диаметр диска и высоту боковины. Возможны дополнительные маркировки, обозначающие допустимую нагрузку на шину, сезонность использования, тип дорожного покрытия и другие параметры. Завод производит внедорожники определѐнной модели и устанавливает на них колеса с шинами маркировки 205/55 R16." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Завод допускает установку шин с другими маркировками. В таблице показаны разрешенные размеры шин." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|c|c|c|c|}" << endl
                << "\\hline" << endl
                << "\\textbf{Ширина шины (мм)} & \\multicolumn{3}{c|}{\\textbf{Диаметр диска (дюймы)}} \\\\ \\cline{2-4} & \\textbf{16} & \\textbf{17} & \\textbf{18} \\\\ \\hline" << endl
                << "205 & 205/55 & — & — \\\\ \\hline" << endl
                << "215 & 215/55; 215/50 & 215/45 & 215/40 \\\\ \\hline" << endl
                << "225 & 225/50; 225/45 & 225/45; 225/40 & 225/40 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "Шины какой наименьшей ширины можно устанавливать на автомобиль, если диаметр диска равен 17 дюймам? Ответ дайте в миллиметрах." << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 215 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров радиус колеса с шиной маркировки 205/45 R17 меньше, чем радиус колеса с шиной маркировки 215/55 R17?" << endl << endl;
                Answer = Answer + "  \\item 26 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров увеличится диаметр колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 225/45 R17?" << endl << endl;
                Answer = Answer + "  \\item 2,4 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите диаметр колеса автомобиля, выходящего с завода. Ответ дайте в миллиметрах." << endl << endl;
                Answer = Answer + "  \\item 631,9 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item     На сколько процентов увеличится пробег автомобиля при одном обороте колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 215/55 R16? Результат округлите до десятых." << endl << endl;
            Answer = Answer + "  \\item 1,7 \n";
            break;

        case 5:     // Тип 5 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.3\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.3\\textwidth]{Шины.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Автомобильное колесо, как правило, представляет из себя металлический диск с установленной на него резиновой шиной. Диаметр диска совпадает с диаметром внутреннего отверстия в шине. Для маркировки автомобильных шин применяется единая система обозначений. Например, 195/65 R15 (рис. 1). Первое число (число 195 в приведенном примере) обозначает ширину шины в миллиметрах (параметр B на рисунке 2). Второе число (число 65 в приведенном примере) — процентное отношение высоты боковины (параметр H на рисунке 2) к ширине шины, то есть $100\\cdot\\frac{H}{B}$. Последующая буква обозначает тип конструкции шины. В данном примере буква R означает, что шина радиальная, то есть нити каркаса в боковине шины расположены вдоль радиусов колеса. На всех легковых автомобилях применяются шины радиальной конструкции. За обозначением типа конструкции шины идет число, указывающее диаметр диска колеса d в дюймах (в одном дюйме 25,4 мм). Таким образом, общий диаметр колеса D легко найти, зная диаметр диска и высоту боковины. Возможны дополнительные маркировки, обозначающие допустимую нагрузку на шину, сезонность использования, тип дорожного покрытия и другие параметры. Завод производит внедорожники определѐнной модели и устанавливает на них колеса с шинами маркировки 205/60 R16." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Завод допускает установку шин с другими маркировками. В таблице показаны разрешенные размеры шин." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|c|c|c|c|}" << endl
                << "\\hline" << endl
                << "\\textbf{Ширина шины (мм)} & \\multicolumn{3}{c|}{\\textbf{Диаметр диска (дюймы)}} \\\\ \\cline{2-4} & \\textbf{16} & \\textbf{17} & \\textbf{18} \\\\ \\hline" << endl
                << "205 & 205/60 & 205/55 & — \\\\ \\hline" << endl
                << "215 & 215/60; 215/55 & 215/50 & 215/45 \\\\ \\hline" << endl
                << "225 & — & 225/45; 225/40 & 225/40 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "Шины какой наименьшей ширины можно устанавливать на автомобиль, если диаметр диска равен 18 дюймам? Ответ дайте в миллиметрах." << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 215 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров радиус колеса с шиной маркировки 275/50 R17 меньше, чем радиус колеса с шиной маркировки 245/60 R17?" << endl << endl;
                Answer = Answer + "  \\item 9,5 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров уменьшится диаметр колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 215/45 R18?" << endl << endl;
                Answer = Answer + "  \\item 1,7 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите диаметр колеса автомобиля, выходящего с завода. Ответ дайте в миллиметрах." << endl << endl;
                Answer = Answer + "  \\item 652,4 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item     На сколько процентов увеличится пробег автомобиля при одном обороте колеса, если заменить колѐса, установленные на заводе, колѐсами с шинами маркировки 215/60 R16? Результат округлите до десятых." << endl << endl;
            Answer = Answer + "  \\item 1,8 \n";
            break;

        case 6:     // Тип 6 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.3\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.3\\textwidth]{Шины.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Автомобильное колесо, как правило, представляет из себя металлический диск с установленной на него резиновой шиной. Диаметр диска совпадает с диаметром внутреннего отверстия в шине. Для маркировки автомобильных шин применяется единая система обозначений. Например, 195/65 R15 (рис. 1). Первое число (число 195 в приведенном примере) обозначает ширину шины в миллиметрах (параметр B на рисунке 2). Второе число (число 65 в приведенном примере) — процентное отношение высоты боковины (параметр H на рисунке 2) к ширине шины, то есть $100\\cdot\\frac{H}{B}$. Последующая буква обозначает тип конструкции шины. В данном примере буква R означает, что шина радиальная, то есть нити каркаса в боковине шины расположены вдоль радиусов колеса. На всех легковых автомобилях применяются шины радиальной конструкции. За обозначением типа конструкции шины идет число, указывающее диаметр диска колеса d в дюймах (в одном дюйме 25,4 мм). Таким образом, общий диаметр колеса D легко найти, зная диаметр диска и высоту боковины. Возможны дополнительные маркировки, обозначающие допустимую нагрузку на шину, сезонность использования, тип дорожного покрытия и другие параметры. Завод производит внедорожники определѐнной модели и устанавливает на них колеса с шинами маркировки 235/65 R17." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Завод допускает установку шин с другими маркировками. В таблице показаны разрешенные размеры шин." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|c|c|c|c|}" << endl
                << "\\hline" << endl
                << "\\textbf{Ширина шины (мм)} & \\multicolumn{3}{c|}{\\textbf{Диаметр диска (дюймы)}} \\\\ \\cline{2-4} & \\textbf{17} & \\textbf{18} & \\textbf{19} \\\\ \\hline" << endl
                << "235 & 235/65 & 235/60 & — \\\\ \\hline" << endl
                << "245 & 245/65 & 245/60; 245/55 & 245/50 \\\\ \\hline" << endl
                << "255 & — & 255/55 & 255/50; 255/45 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "Шины какой наименьшей ширины можно устанавливать на автомобиль, если диаметр диска равен 19 дюймам? Ответ дайте в миллиметрах." << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 245 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров радиус колеса с шиной маркировки 220/60 R16 меньше, чем радиус колеса с шиной маркировки 245/55 R16?" << endl << endl;
                Answer = Answer + "  \\item 2,75 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров увеличится диаметр колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 255/50 R19?" << endl << endl;
                Answer = Answer + "  \\item 0,3 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите диаметр колеса автомобиля, выходящего с завода. Ответ дайте в миллиметрах." << endl << endl;
                Answer = Answer + "  \\item 737,3 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item     На сколько процентов увеличится пробег автомобиля при одном обороте колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 245/65 R17? Результат округлите до десятых." << endl << endl;
            Answer = Answer + "  \\item 1,8 \n";
            break;

        case 7:     // Тип 7 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.3\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.3\\textwidth]{Шины.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Автомобильное колесо, как правило, представляет из себя металлический диск с установленной на него резиновой шиной. Диаметр диска совпадает с диаметром внутреннего отверстия в шине. Для маркировки автомобильных шин применяется единая система обозначений. Например, 195/65 R15 (рис. 1). Первое число (число 195 в приведенном примере) обозначает ширину шины в миллиметрах (параметр B на рисунке 2). Второе число (число 65 в приведенном примере) — процентное отношение высоты боковины (параметр H на рисунке 2) к ширине шины, то есть $100\\cdot\\frac{H}{B}$. Последующая буква обозначает тип конструкции шины. В данном примере буква R означает, что шина радиальная, то есть нити каркаса в боковине шины расположены вдоль радиусов колеса. На всех легковых автомобилях применяются шины радиальной конструкции. За обозначением типа конструкции шины идет число, указывающее диаметр диска колеса d в дюймах (в одном дюйме 25,4 мм). Таким образом, общий диаметр колеса D легко найти, зная диаметр диска и высоту боковины. Возможны дополнительные маркировки, обозначающие допустимую нагрузку на шину, сезонность использования, тип дорожного покрытия и другие параметры. Завод производит внедорожники определѐнной модели и устанавливает на них колеса с шинами маркировки 175/60 R15." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Завод допускает установку шин с другими маркировками. В таблице показаны разрешенные размеры шин." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|c|c|c|c|}" << endl
                << "\\hline" << endl
                << "\\textbf{Ширина шины (мм)} & \\multicolumn{3}{c|}{\\textbf{Диаметр диска (дюймы)}} \\\\ \\cline{2-4} & \\textbf{14} & \\textbf{15} & \\textbf{16} \\\\ \\hline" << endl
                << "165 & 165/70 & 165/60; 165/65 & — \\\\ \\hline" << endl
                << "175 & 175/65 & 175/60 & — \\\\ \\hline" << endl
                << "185 & 185/60 & 185/55 & 185/50 \\\\ \\hline" << endl
                << "195 & 195/60 & 195/55 & 195/45 \\\\ \\hline" << endl
                << "205 & — & — & 205/45 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "Шины какой наименьшей ширины можно устанавливать на автомобиль, если диаметр диска равен 16 дюймам? Ответ дайте в миллиметрах." << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 185 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров радиус колеса с шиной маркировки 195/60 R14 больше, чем радиус колеса с шиной маркировки 165/70 R14?" << endl << endl;
                Answer = Answer + "  \\item 1,5 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров уменьшится диаметр колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 195/45 R16?" << endl << endl;
                Answer = Answer + "  \\item 9,1 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите диаметр колеса автомобиля, выходящего с завода. Ответ дайте в миллиметрах." << endl << endl;
                Answer = Answer + "  \\item 591 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item     На сколько процентов увеличится пробег автомобиля при одном обороте колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 195/55 R15? Результат округлите до десятых." << endl << endl;
            Answer = Answer + "  \\item 0,8 \n";
            break;

        case 8:     // Тип 8 из файла
            cout << "%" << i + 1 << endl; // 1
            cout << "\\item" << endl
             << "\\begin{minipage}[t]{\\linewidth}" << endl
             << "\\begin{wrapfigure}{r}{0.3\\textwidth}" << endl
             << "\\centering" << endl
             << "\\includegraphics[width=0.3\\textwidth]{Шины.png}" << endl
             << "\\end{wrapfigure}" << endl
             << "Автомобильное колесо, как правило, представляет из себя металлический диск с установленной на него резиновой шиной. Диаметр диска совпадает с диаметром внутреннего отверстия в шине. Для маркировки автомобильных шин применяется единая система обозначений. Например, 195/65 R15 (рис. 1). Первое число (число 195 в приведенном примере) обозначает ширину шины в миллиметрах (параметр B на рисунке 2). Второе число (число 65 в приведенном примере) — процентное отношение высоты боковины (параметр H на рисунке 2) к ширине шины, то есть $100\\cdot\\frac{H}{B}$. Последующая буква обозначает тип конструкции шины. В данном примере буква R означает, что шина радиальная, то есть нити каркаса в боковине шины расположены вдоль радиусов колеса. На всех легковых автомобилях применяются шины радиальной конструкции. За обозначением типа конструкции шины идет число, указывающее диаметр диска колеса d в дюймах (в одном дюйме 25,4 мм). Таким образом, общий диаметр колеса D легко найти, зная диаметр диска и высоту боковины. Возможны дополнительные маркировки, обозначающие допустимую нагрузку на шину, сезонность использования, тип дорожного покрытия и другие параметры. Завод производит внедорожники определѐнной модели и устанавливает на них колеса с шинами маркировки 265/70 R17." << endl
             << "\\vspace{1em} % Пустая строка (вертикальный пробел)" << endl << endl;
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "Завод допускает установку шин с другими маркировками. В таблице показаны разрешенные размеры шин." << endl
                << "\\begin{center}" << endl
                << "\\begin{tabular}{|c|c|c|c|}" << endl
                << "\\hline" << endl
                << "\\textbf{Ширина шины (мм)} & \\multicolumn{3}{c|}{\\textbf{Диаметр диска (дюймы)}} \\\\ \\cline{2-4} & \\textbf{17} & \\textbf{18} & \\textbf{20} \\\\ \\hline" << endl
                << "265 & 265/70 & 265/65 & — \\\\ \\hline" << endl
                << "275 & 275/70; 275/65 & 275/65; 275/60 & 275/55 \\\\ \\hline" << endl
                << "285 & 285/65; 285/60 & 285/60 & 285/50 \\\\ \\hline" << endl
                << "\\end{tabular}" << endl
                << "\\end{center}" << endl
                << "Шины какой наименьшей ширины можно устанавливать на автомобиль, если диаметр диска равен 20 дюймам? Ответ дайте в миллиметрах." << endl
                << "\\end{minipage}" << endl << endl;
                Answer = Answer + "  \\item 275 \n";
                break;
            }

            cout << "%" << i + 2 << endl; // 2
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров радиус колеса с шиной маркировки 195/50 R16 меньше, чем радиус колеса с шиной маркировки 215/60 R16?" << endl << endl;
                Answer = Answer + "  \\item 31,5 \n";
                break;
            }

            cout << "%" << i + 3 << endl; // 3
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     На сколько миллиметров увеличится диаметр колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 275/55 R20?" << endl << endl;
                Answer = Answer + "  \\item 7,7 \n";
                break;
            }

            cout << "%" << i + 4 << endl; // 4
            typeother = rand()%1 + 1;
            switch(typeother)
            {
                case 1:
                cout << "\\item     Найдите диаметр колеса автомобиля, выходящего с завода. Ответ дайте в миллиметрах." << endl << endl;
                Answer = Answer + "  \\item 802,8 \n";
                break;
            }

            cout << "%" << i + 5 << endl; // 5
            cout << "\\item     На сколько процентов увеличится пробег автомобиля при одном обороте колеса, если заменить колеса, установленные на заводе, колесами с шинами маркировки 275/70 R17? Результат округлите до десятых." << endl << endl;
            Answer = Answer + "  \\item 1,7 \n";
            break;
    }
    return Answer;
}

string Second20Uravn(int i, int AllType)
{
    string Answer;
    double answer;
    double a[4];
    double b[4];
    double c[2];
    double x[2];
    double D;
    string A[4];
    string B[4];
    int check;
    int type = rand()%10+1;
    switch(type)
    {
        case 1:
            check = 0;
            do{
                for(int i = 0; i < 4; i++)
                {
                    a[i] = rand()%9+1;
                }
                b[0] = a[1]*a[3] - a[0];
                b[1] = a[0]*a[3] - a[1];
                b[2] = a[2]*a[3] - a[2];
                b[3] = rand()%89 + 10;
                if((b[0] > 0)&&(b[1] > 0)&&(b[2] > 0)&&(b[0]!=b[1]))
                    check = 1;
            }while(check != 1);
            answer = b[3] - b[2];
            for(int i = 0; i<4; i++)
            {
                if((a[i] == 1)&&(i != 2)&&(i != 3))
                    A[i] = " ";
                else
                    A[i] = FormatDouble(a[i]);

                if((b[i] == 1)&&(i != 2)&&(i != 3))
                    B[i] = " ";
                else
                    B[i] = FormatDouble(b[i]);
            }
            cout << "\\item Найдите значение выражения при данном условии: $$" << B[0] << "a-" << B[1] << "b+" << B[3] << ",\\text{ если }\\frac{" << A[0] << "a-" << A[1] << "b + " << A[2] << "}{" << A[1] << "a- " << A[0] << "b + " << A[2] << "}=" << A[3] << "$$" << endl;
            Answer = Answer + "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 2:
            a[0] = rand()%15 + 1;
            a[1] = rand()%10 + 1;
            if(pow(-1,rand()) > 0)
                a[1] = 1;
            b[0] = a[0];
            b[1] = a[1]*a[1];
            b[2] = a[0]*a[1]*a[1];
            for(int i = 0; i<2; i++)
            {
                if(b[i] == 1)
                    B[i] = " ";
                else
                    B[i] = FormatDouble(b[i]);
            }
            B[2] = FormatDouble(b[2]);
            if(pow(-1,rand()) > 0)
                cout << "\\item Решите уравнение: $$x^3 + " << B[0] << "x^2 - " << B[1] << "x - " << B[2] << " = 0$$" << endl;
            else
                cout << "\\item Решите уравнение: $$x^3 + " << B[0] << "x^2 = " << B[1] << "x + " << B[2] << "$$" << endl;
            Answer = Answer + "  \\item $-" + FormatDouble(a[0]) + ";\\pm" + FormatDouble(a[1]) + "$ \n";
            break;

        case 3:
            check = 0;
            do{
                for(int i = 0; i < 3; i++)
                    a[i] = rand()%10 + 1;
                if((a[2]<a[1])&&((-1*a[0])<a[2]))
                    check = 1;
                if((a[0]==a[1])||(a[1]<a[0]))
                    check = 0;
            }while(check != 1);
            b[0] = a[1] - a[0];
            b[1] = a[1]*a[0];
            b[2] = a[2];
            if(b[0] == 1)
                B[0] = " ";
            else
                B[0] = FormatDouble(b[0]);
            B[2] = FormatDouble(b[2]);
            B[1] = FormatDouble(b[1]);
            cout << "\\item Решите уравнение: $$x^2-" << B[0] << "x +\\sqrt{" << B[2] << "-x} = \\sqrt{" << B[2] << "-x} + " << B[1] << "$$" << endl;
            Answer = Answer + "  \\item -" + FormatDouble(a[0]) + " \n";
            break;

        case 4:
            check = 0;
            do{
                check = 1;
                a[0] = rand()%10 + 1;
                a[1] = rand()%9 + 2;
                c[0] = a[0];
                c[1] = -1*a[1];
                D = c[0]*c[0] - 4*c[1];
                D = pow(D,0.5);
                if((10*D-static_cast<int>(10*D)) > 0)
                    check = 0;
                else
                {
                    x[0] = (-1*c[0]-D)/2;
                    x[1] = (-1*c[0]+D)/2;
                }
            }while(check != 1);
            b[0] = 2*a[0];
            b[1] = a[0]*a[0];
            B[0] = FormatDouble(b[0]);
            B[1] = FormatDouble(b[1]);
            B[2] = FormatDouble(a[1]);
            cout << "\\item Решите уравнение: $$x(x^2+" << B[0] << "x + " << B[1] << ")=" << B[2] << "(x+" << FormatDouble(a[0]) << ")$$" << endl;
            Answer = Answer + "  \\item -" + FormatDouble(a[0]) + "; " + FormatDouble(x[0]) + "; " + FormatDouble(x[1]) + "; \n";
            break;

        case 5:
            check = 0;
            do{
                check = 1;
                for(int i=0; i<2; i++)
                    a[i] = rand()%10 + 1;
                a[2] = rand()%9 + 2;
                c[0] = a[1] - a[0];
                c[1] = -1*(a[1]+a[2]);
                D = c[0]*c[0] - 4*c[1];
                D = pow(D,0.5);
                if(c[0] == 0)
                    check = 0;
                if((10*D-static_cast<int>(10*D)) > 0)
                    check = 0;
                else
                {
                    x[0] = (-1*c[0]-D)/2;
                    x[1] = (-1*c[0]+D)/2;
                }
            }while(check != 1);
            b[0] = 2*a[1];
            b[1] = a[1]*a[1];
            cout << "\\item Решите уравнение: $$(x-" << FormatDouble(a[0]) << ")(x^2+" << FormatDouble(b[0]) << "x+" << FormatDouble(b[1]) << ")=" << FormatDouble(a[2]) << "(x+" << FormatDouble(a[1]) << ")$$" << endl;
            Answer = Answer + "  \\item -" + FormatDouble(a[1]) + "; " + FormatDouble(x[0]) + "; " + FormatDouble(x[1]) + "; \n";
            break;

        case 6:
            check = 0;
            do{
                check = 1;
                c[0] = pow(-1,rand())*(rand()%10+1);
                c[1] = -1*(rand()%40+1);
                D = c[0]*c[0] - 4*c[1];
                D = pow(D,0.5);
                if(((10*D-static_cast<int>(10*D)) > 0)||(D>3000))
                    check = 0;
                else
                {
                    x[0] = (-1*c[0]-D)/2;
                    x[1] = (-1*c[0]+D)/2;
                    if((pow(pow(x[0],2),0.5)>10)||(pow(pow(x[1],2),0.5)>10))
                        check = 0;
                    else
                    {
                        if(pow(-1,rand())>0)
                        {
                            a[0] = pow(pow(x[0],2),0.5);
                            answer = x[0];
                        }
                        else
                        {
                            a[0] = pow(pow(x[1],2),0.5);
                            answer = x[1];
                        }
                    }
                }
            }while(check != 1);
            if(c[0]==-1)
                B[0] = "-";
            if(c[0]==1)
                B[0] = "+";
            if(pow(pow(c[0],2),0.5)>1)
            {
                if(c[0]>0)
                    B[0] = "+" + FormatDouble(c[0]);
                else
                    B[0] = FormatDouble(c[0]);
            }
            cout << "\\item Решите уравнение: $$(x^2-" << FormatDouble(a[0]*a[0]) << ")^2+(x^2" << B[0] << "x" << FormatDouble(c[1]) << ")^2=0$$" << endl;
            Answer = Answer + "  \\item " + FormatDouble(answer) + " \n";
            break;

        case 7:
            check = 0;
            do{
                check = 1;
                c[0] = pow(-1,rand())*(rand()%10+1);
                c[1] = -1*(rand()%40+1);
                D = c[0]*c[0] - 4*c[1];
                D = pow(D,0.5);
                if(((10*D-static_cast<int>(10*D)) > 0)||(D>3000))
                    check = 0;
                else
                {
                    x[0] = (-1*c[0]-D)/2;
                    x[1] = (-1*c[0]+D)/2;
                }
            }while(check != 1);
            x[0]=1/x[0];
            x[1]=1/x[1];
            if(c[0]>0)
                B[0] = "+\\frac{" + FormatDouble(c[0]) + "}";
            else
                B[0] = "-\\frac{" + FormatDouble(pow(pow(c[0],2),0.5)) + "}";
            cout << "\\item Решите уравнение: $$\\frac{1}{x^2}" << B[0] << "{x}" << FormatDouble(c[1]) << "=0$$" << endl;
            Answer = Answer + "  \\item " + FormatDouble(x[0]) + "; " + FormatDouble(x[1]) + "; \n";
            break;

        case 8:
            check = 0;
            a[0] = rand()%10+1;
            do{
                check = 1;
                c[0] = pow(-1,rand())*(rand()%10+1);
                c[1] = -1*(rand()%40+1);
                D = c[0]*c[0] - 4*c[1];
                D = pow(D,0.5);
                if(((10*D-static_cast<int>(10*D)) > 0)||(D>3000))
                    check = 0;
                else
                {
                    x[0] = (-1*c[0]-D)/2;
                    x[1] = (-1*c[0]+D)/2;
                }
            }while(check != 1);
            x[0]=a[0] + (1/x[0]);
            x[1]=a[0]+ (1/x[1]);
            if(c[0]>0)
                B[0] = "+\\frac{" + FormatDouble(c[0]) + "}";
            else
                B[0] = "-\\frac{" + FormatDouble(pow(pow(c[0],2),0.5)) + "}";
            cout << "\\item Решите уравнение: $$\\frac{1}{(x-" << FormatDouble(a[0]) << ")^2}" << B[0] << "{x-" << FormatDouble(a[0]) << "}" << FormatDouble(c[1]) << "=0$$" << endl;
            Answer = Answer + "  \\item " + FormatDouble(x[0]) + "; " + FormatDouble(x[1]) + "; \n";
            break;

        case 9:
            check = 0;
            a[0] = pow(-1,rand())*(rand()%10+1);
            do{
                check = 1;
                c[0] = pow(-1,rand())*(rand()%10+1);
                c[1] = -1*(rand()%40+1);
                D = c[0]*c[0] - 4*c[1];
                D = pow(D,0.5);
                if(((10*D-static_cast<int>(10*D)) > 0)||(D>3000))
                    check = 0;
                else
                {
                    x[0] = (-1*c[0]-D)/2;
                    x[1] = (-1*c[0]+D)/2;
                    if(x[0]>0)
                        a[1] = x[0];
                    else
                        a[1] = x[1];
                    if((10*pow(a[1],0.5)-static_cast<int>(10*pow(a[1],0.5)))==0)
                        check = 0;
                }
                x[0] = -1*a[0];
            }while(check != 1);
            if(c[0]==-1)
                B[0] = "-";
            if(c[0]==1)
                B[0] = "+";
            if(c[0]>1)
                B[0] = "+" + FormatDouble(c[0]);
            if(c[0]<0)
                B[0] = FormatDouble(c[0]);
            if(a[0]>0)
                B[1] = "+" + FormatDouble(a[0]);
            else
                B[1] = FormatDouble(a[0]);
            cout << "\\item Решите уравнение: $$(x" << B[1] << ")^4" << B[0] << "(x" << B[1] << ")^2" << c[1] << "=0$$" << endl;
            Answer = Answer + "  \\item $" + FormatDouble(x[0]) + "\\pm\\sqrt{" + FormatDouble(a[1]) + "}$ \n";
            break;

        case 10:
            check = 0;
            do{
                check = 1;
                c[0] = rand()%10+1;
                c[1] = -1*(rand()%40+1);
                D = c[0]*c[0] - 4*c[1];
                D = pow(D,0.5);
                if(((10*D-static_cast<int>(10*D)) > 0)||(D>3000))
                    check = 0;
                else
                {
                    x[0] = (-1*c[0]-D)/2;
                    x[1] = (-1*c[0]+D)/2;
                }
                D = c[0]*c[0] + 4*c[1];
                if(D >= 0)
                    check = 0;
            }while(check != 1);
            if(c[0]==1)
                B[0] = " ";
            else
                B[0] = FormatDouble(c[0]);
            B[1] = FormatDouble(c[1]);
            cout << "\\item Решите уравнение: $$x^4=(" << B[0] << "x" << B[1] << ")^2$$" << endl;
            Answer = Answer + "  \\item " + FormatDouble(x[0]) + "; " + FormatDouble(x[1]) + "; \n";
            break;
    }
    return Answer;
}

string Second20Sistem(int i, int AllType)
{
    string Answer;
    double answer;
    double a[4];
    double b[5];
    double c[3];
    double x[2];
    double y[2];
    double D;
    string A[4];
    string B[7];
    int check;
    int type = rand()%3 + 1;
    switch(type)
    {
        case 1:
            check = 0;
            do{
                check = 1;
                for(int i = 0; i < 4; i++)
                {
                    a[i] = rand()%9+1;
                }
                c[0] = a[0];
                c[1] = a[1] + a[2];
                c[2] = a[3];
                D = c[1]*c[1]-4*c[0]*c[2];
                if(D <= 0)
                    check = 0;
                else
                {
                    D = pow(D,0.5);
                    if(((10*D-static_cast<int>(10*D)) > 0)||(D>3000))
                        check = 0;
                    else
                    {
                        x[0] = (c[1]-D)/(2*c[0]);
                        x[1] = (c[1]+D)/(2*c[0]);
                        y[0] = a[2]*x[0]-a[3];
                        y[1] = a[2]*x[1]-a[3];
                    }
                }
            }while(check != 1);
            for(int i = 0; i<3; i++)
            {
                if(a[i] == 1)
                    A[i] = " ";
                else
                    A[i] = FormatDouble(a[i]);
            }
            A[3] = FormatDouble(a[3]);
            cout << "\\item Решите систему уравнений: \n $$\\begin{cases} \n " << A[0] << "x^2-" << A[1] << "x = y, \\\\ \n " << A[2] << "x-" << A[3] << "=y; \n \\end{cases}$$ " << endl << endl;
            Answer = Answer + "\\item  (" + FormatDouble(x[0]) + ";" + FormatDouble(y[0]) + "), (" + FormatDouble(x[1]) + ";" + FormatDouble(y[1]) + ") \n";
            break;
        
        case 2:
            check = 0;
            do{
                check = 1;
                for(int i = 0; i < 4; i++)
                {
                    a[i] = rand()%20+1;
                }
                c[0] = (a[1] + a[3])/(a[0] + a[2]);
                if((10*pow(c[0], 0.5) - static_cast<int>(10*pow(c[0], 0.5))) > 0)
                    check = 0;
                else
                {
                    x[0] = -1*pow(c[0],0.5);
                    x[1] = pow(c[0],0.5);
                    y[0] = a[1]-a[0]*c[0];
                    y[1] = y[0];
                }
            }while(check != 1);
            if(a[0] == 1)
                A[0] = " ";
            else
                A[0] = FormatDouble(a[0]);
            if(a[2] == 1)
                A[2] = " ";
            else
                A[2] = FormatDouble(a[2]);
            A[1] = FormatDouble(a[1]);
            A[3] = FormatDouble(a[3]);
            cout << "\\item Решите систему уравнений: \n $$\\begin{cases} \n " << A[0] << "x^2+y=" << A[1] << ", \\\\ \n " << A[2] << "x^2-y=" << A[3] << "; \n \\end{cases}$$ " << endl << endl;
            Answer = Answer + "\\item (" + FormatDouble(x[0]) + ";" + FormatDouble(y[0]) + "), (" + FormatDouble(x[1]) + ";" + FormatDouble(y[1]) + ") \n";
            break;

        case 3:
            check = 0;
            do{
                check = 1;
                a[0] = rand()%9 + 1;
                a[1] = rand()%9 + 1;
                a[2] = rand()%100 + 1;
                x[0] = rand()%7 + 2;
                x[1] = x[0];
                D = (a[2]-a[0]*x[0]*x[0])/a[1];
                if(D <= 0)
                    check = 0;
                else
                {
                    D = pow(D,0.5);
                    if((10*D - static_cast<int>(10*D)) > 0)
                        check = 0;
                    else
                    {
                        y[0] = -1*D;
                        y[1] = D;
                    }
                }
            }while(check != 1);
            if(a[0] == 1)
                B[0] = " ";
            else
                B[0] = FormatDouble(a[0]);
            if(a[1] == 1)
                B[1] = " ";
            else
                B[1] = FormatDouble(a[1]);
            if(a[2] == 1)
                B[5] = " ";
            else
                B[5] = FormatDouble(a[2]);
            B[2] = FormatDouble(a[0]*x[0]);
            B[3] = FormatDouble(a[1]*x[0]);
            B[4] = FormatDouble(a[2]);
            cout << "\\item Решите систему уравнений: \n $$\\begin{cases} \n" << B[0] << "x^2+" << B[1] << "y^2=" << B[4] << ", \\\\ \n " << B[2] << "x^2 + " << B[3] << "y^2 = " << B[5] << "x; \n \\end{cases}$$" << endl << endl;
            Answer = Answer + "\\item (" + FormatDouble(x[0]) + ";" + FormatDouble(y[0]) + "), (" + FormatDouble(x[0]) + ";" + FormatDouble(y[1]) + ") \n";
            break;
    }
    return Answer;
}

string Second20Nerav(int i, int AllType)
{
    string Answer;
    int d;
    double answer;
    double a[4];
    double b[5];
    double c[3];
    double x[2];
    double y[2];
    double D;
    string A[4];
    string B[7];
    int check;
    int type = rand()%3 + 1;
    switch(type)
    {
        case 1:
            check = 0;
            do{
                check = 1;
                for(int i = 0; i < 2; i++)
                {
                    a[i] = rand()%15+1;
                }
                if((10*pow(a[0],0.5)-static_cast<int>(10*pow(a[0],0.5))) == 0)
                    check = 0;
            }while(check != 1);
            d = rand()%4 + 1;
            switch(d)
            {
                case 1:
                    cout << "\\item Решите неравенство: $$(x-" << FormatDouble(a[1]) << ")^2>\\sqrt{" << FormatDouble(a[0]) << "}(x-" << a[1] << ")$$" << endl;
                    Answer = Answer + "\\item  $(\\infty;" + FormatDouble(a[1]) + ")\\cup(" + FormatDouble(a[1]) + "+\\sqrt{" + FormatDouble(a[0]) + "};+\\infty)$ \n";
                    break;

                case 2:
                    cout << "\\item Решите неравенство: $$(x-" << FormatDouble(a[1]) << ")^2<\\sqrt{" << FormatDouble(a[0]) << "}(x-" << a[1] << ")$$" << endl;
                    Answer = Answer + "\\item  $(" + FormatDouble(a[1]) + ";" + FormatDouble(a[1]) + "+\\sqrt{" + FormatDouble(a[0]) + "})$ \n";
                    break;

                case 3:
                    cout << "\\item Решите неравенство: $$(x-" << FormatDouble(a[1]) << ")^2\\geq\\sqrt{" << FormatDouble(a[0]) << "}(x-" << a[1] << ")$$" << endl;
                    Answer = Answer + "\\item  $(\\infty;" + FormatDouble(a[1]) + "]\\cup[" + FormatDouble(a[1]) + "+\\sqrt{" + FormatDouble(a[0]) + "};+\\infty)$ \n";
                    break;

                case 4:
                    cout << "\\item Решите неравенство: $$(x-" << FormatDouble(a[1]) << ")^2\\leq\\sqrt{" << FormatDouble(a[0]) << "}(x-" << a[1] << ")$$" << endl;
                    Answer = Answer + "\\item  $[" + FormatDouble(a[1]) + ";" + FormatDouble(a[1]) + "+\\sqrt{" + FormatDouble(a[0]) + "}]$ \n";
                    break;
            }
            break;
        
        case 2:
            check = 0;    
            do{
                check = 1;
                a[0] = pow(-1,rand())*(rand()%10+1);
                a[1] = pow(-1,rand())*(rand()%10+1);
                a[2] = rand()%40 + 1;
                if(a[0] > a[1])
                {
                    D = a[0];
                    a[0] = a[1];
                    a[1] = D;
                }
                b[0] = -1*(a[0] + a[1]);
                b[1] = a[0]*a[1];
                if((b[0] == 0)||(a[0]==a[1]))
                    check = 0;
            }while(check != 1);
            for(int i=0; i<2; i++)
            {
                if(b[i]>0)
                    B[i] = "+";
                else
                    B[i] = "-";
                b[i] = pow(pow(b[i],2),0.5);
                B[i] = B[i] + FormatDouble(b[i]);
            }
            d = rand()%2 + 1;
            switch(d)
            {
                case 1:
                    cout << "\\item Решите неравенство: $$-\\frac{" << FormatDouble(a[2]) << "}{x^2" << B[0] << "x" << B[1] << "}\\geq 0$$" << endl;
                    Answer = Answer + "\\item  $(" + FormatDouble(a[0]) + ";" + FormatDouble(a[1]) + ")$ \n";
                    break;

                case 2:
                    cout << "\\item Решите неравенство: $$-\\frac{" << FormatDouble(a[2]) << "}{x^2" << B[0] << "x" << B[1] << "}\\leq 0$$" << endl;
                    Answer = Answer + "\\item  $(-\\infty;" + FormatDouble(a[0]) + ")\\cup(" + FormatDouble(a[1]) + ";+\\infty)$ \n";
                    break;
            }
            break;

        case 3:
            check = 0;
            do{
                check = 1;
                a[0] = pow(-1,rand())*(rand()%10+1);
                a[1] = rand()%16 + 1;
                a[2] = rand()%34 + 1;
                if((10*pow(a[1],0.5)-static_cast<int>(10*pow(a[1],0.5))) == 0)
                    check = 0;
            }while(check != 1);
            if(a[0]>0)
                B[0] = "-";
            else
                B[0] = "+";
            a[3] = pow(pow(a[0],2),0.5);
            B[0] = B[0] + FormatDouble(a[3]);
            d = rand()%2 + 1;
            switch(d)
            {
                case 1:
                    cout << "\\item Решите неравенство: $$-\\frac{" << FormatDouble(a[2]) << "}{(x" << B[0] << ")^2-" << FormatDouble(a[1]) << "}\\geq 0$$" << endl;
                    Answer = Answer + "\\item  $(" + FormatDouble(a[0]) + " -\\sqrt{" + FormatDouble(a[1]) + "};" + FormatDouble(a[0]) + "+\\sqrt{" + FormatDouble(a[1]) + "})$ \n";
                    break;

                case 2:
                    cout << "\\item Решите неравенство: $$-\\frac{" << FormatDouble(a[2]) << "}{(x" << B[0] << ")^2-" << FormatDouble(a[1]) << "}\\leq 0$$" << endl;
                    Answer = Answer + "\\item $(-\\infty;" + FormatDouble(a[0]) + "-\\sqrt{" + FormatDouble(a[1]) + "})\\cup(" + FormatDouble(a[0]) + "+\\sqrt{" + FormatDouble(a[1]) + "};+\\infty)$ \n";
                    break;
            }
        
    }
    return Answer;
}

string Second21Road(int i, int AllType)
{
    string Answer;
    int type;
    int a[10];
    type = rand()%7 + 1;
    int type_2, type_3;
    switch(type)
    {
        case 1:         // Движение по прямой
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    a[0] = 60;
                    a[1] = 10;
                    a[2] = 3;
                    Answer = Answer + "\\item  10 \n";
                    break;

                case 2:
                    a[0] = 209;
                    a[1] = 8;
                    a[2] = 8;
                    Answer = Answer + "\\item  11 \n";
                    break;

                case 3:
                    a[0] = 180;
                    a[1] = 5;
                    a[2] = 8;
                    Answer = Answer + "\\item  15 \n";
                    break;

                case 4:
                    a[0] = 105;
                    a[1] = 16;
                    a[2] = 3;
                    Answer = Answer + "\\item  14 \n";
                    break;

                case 5:
                    a[0] = 224;
                    a[1] = 2;
                    a[2] = 2;
                    Answer = Answer + "\\item  16 \n";
                    break;
            }
            cout << "\\item Велосипедист выехал с постоянной скоростью из города А в город В, расстояние между которыми равно " << a[0] << " км. На следующий день он отправился обратно в А, увеличив скорость на " << a[1] << " км/ч. По пути он сделал остановку на " << a[2] << " часа, в результате чего затратил на обратный путь столько же времени, сколько на путь из А в В. Найдите скорость велосипедиста на пути из А в В." << endl;
            break;

        case 2: // Движение на встречу
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    a[0] = 36;
                    a[1] = 82;
                    a[2] = 28;
                    a[3] = 10;
                    Answer = Answer + "\\item  26 \n";
                    break;

                case 2:
                    a[0] = 56;
                    a[1] = 182;
                    a[2] = 13;
                    a[3] = 15;
                    Answer = Answer + "\\item  104 \n";
                    break;

                case 3:
                    a[0] = 2;
                    a[1] = 277;
                    a[2] = 16;
                    a[3] = 30;
                    Answer = Answer + "\\item  181 \n";
                    break;

                case 4:
                    a[0] = 51;
                    a[1] = 251;
                    a[2] = 10;
                    a[3] = 20;
                    Answer = Answer + "\\item  173 \n";
                    break;

                case 5:
                    a[0] = 28;
                    a[1] = 286;
                    a[2] = 10;
                    a[3] = 30;
                    Answer = Answer + "\\item  218 \n";
                    break;
            }
            cout << "\\item Из двух городов одновременно навстречу друг другу отправились два велосипедиста. Проехав некоторую часть пути, первый велосипедист сделал остановку на " << a[0] << " минут, а затем продолжил движение до встречи со вторым велосипедистом. Расстояние между городами составляет " << a[1] << " км, скорость первого велосипедиста равна " << a[2] << " км/ч, скорость второго – " << a[3] << " км/ч. Определите расстояние от города, из которого выехал второй велосипедист, до места встречи." << endl;
            break;
            
        case 3: // Движение в догонку
            type_3 = rand()%3 + 1;
            switch(type_3)
            {
                case 1:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 560;
                            a[1] = 10;
                            a[2] = 1;
                            Answer = Answer + "\\item  80 \n";
                            break;

                        case 2:
                            a[0] = 800;
                            a[1] = 36;
                            a[2] = 5;
                            Answer = Answer + "\\item  96 \n";
                            break;

                        case 3:
                            a[0] = 980;
                            a[1] = 28;
                            a[2] = 4;
                            Answer = Answer + "\\item  98 \n";
                            break;

                        case 4:
                            a[0] = 420;
                            a[1] = 24;
                            a[2] = 2;
                            Answer = Answer + "\\item  84 \n";
                            break;

                        case 5:
                            a[0] = 660;
                            a[1] = 11;
                            a[2] = 2;
                            Answer = Answer + "\\item  66 \n";
                            break;
                    }
                    cout << "\\item Два автомобиля одновременно отправляются в " << a[0] << "-километровый пробег. Первый едет со скоростью, на " << a[1] << " км/ч большей, чем второй, и прибывает к финишу на " << a[2] << " час раньше второго. Найдите скорость первого автомобиля." << endl;
                    break;

                case 2:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 6;
                            a[1] = 56;
                            a[2] = 45;
                            Answer = Answer + "\\item  48 \n";
                            break;

                        case 2:
                            a[0] = 17;
                            a[1] = 102;
                            a[2] = 65;
                            Answer = Answer + "\\item  68 \n";
                            break;

                        case 3:
                            a[0] = 11;
                            a[1] = 66;
                            a[2] = 40;
                            Answer = Answer + "\\item  44 \n";
                            break;

                        case 4:
                            a[0] = 8;
                            a[1] = 90;
                            a[2] = 75;
                            Answer = Answer + "\\item  80 \n";
                            break;

                        case 5:
                            a[0] = 9;
                            a[1] = 60;
                            a[2] = 40;
                            Answer = Answer + "\\item  45 \n";
                            break;
                    }
                    cout << "\\item  Из А в В одновременно выехали два автомобиля. Первый проехал с постоянной скоростью весь путь. Второй проехал первую половину пути со скоростью, меньшей скорости первого автомобиля на " << a[0] << " км/ч, а вторую половину пути проехал со скоростью " << a[1] << " км/ч, в результате чего прибыл в В одновременно с первым автомобилем. Найдите скорость первого автомобиля, если известно, что она больше " << a[2] << " км/ч." << endl;
                    break;

                case 3:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 48;
                            a[1] = 32;
                            Answer = Answer + "\\item  64 \n";
                            break;

                        case 2:
                            a[0] = 57;
                            a[1] = 38;
                            Answer = Answer + "\\item  76 \n";
                            break;

                        case 3:
                            a[0] = 36;
                            a[1] = 54;
                            Answer = Answer + "\\item  54 \n";
                            break;

                        case 4:
                            a[0] = 70;
                            a[1] = 21;
                            Answer = Answer + "\\item  84 \n";
                            break;

                        case 5:
                            a[0] = 30;
                            a[1] = 9;
                            Answer = Answer + "\\item  36 \n";
                            break;
                    }
                    cout << "\\item Из А в В одновременно выехали два автомобиля. Первый проехал с постоянной скоростью весь путь. Второй проехал первую половину пути со скоростью " << a[0] << " км/ч, а вторую половину пути проехал со скоростью на " << a[1] << " км/ч больше скорости первого, в результате чего прибыл в В одновременно с первым автомобилем. Найдите скорость первого автомобиля." << endl;
                    break;
            }
            break;

        case 4: // Движение по окружности
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    a[0] = 4;
                    a[1] = 18;
                    a[2] = 10;
                    Answer = Answer + "\\item  10 \n";
                    break;

                case 2:
                    a[0] = 2;
                    a[1] = 9;
                    a[2] = 5;
                    Answer = Answer + "\\item  15 \n";
                    break;

                case 3:
                    a[0] = 7;
                    a[1] = 3;
                    a[2] = 8;
                    Answer = Answer + "\\item  12 \n";
                    break;

                case 4:
                    a[0] = 1;
                    a[1] = 15;
                    a[2] = 5;
                    Answer = Answer + "\\item  11 \n";
                    break;

                case 5:
                    a[0] = 4;
                    a[1] = 20;
                    a[2] = 11;
                    Answer = Answer + "\\item  10 \n";
                    break;
            }
            cout << "\\item Два бегуна одновременно стартовали в одном направлении из одного и того же места круговой трассы в беге на несколько кругов. Спустя один час, когда одному из них оставалось " << a[0] << " км до окончания первого круга, ему сообщили, что второй бегун прошёл первый круг " << a[1] << " минуты назад. Найдите скорость первого бегуна, если известно, что она на " << a[2] << " км/ч меньше скорости второго." << endl;
            break;

        case 5: // Средняя скорость
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    a[0] = 450;
                    a[1] = 90;
                    a[2] = 230;
                    a[3] = 115;
                    a[4] = 120;
                    a[5] = 40;
                    Answer = Answer + "\\item  80 \n";
                    break;

                case 2:
                    a[0] = 200;
                    a[1] = 50;
                    a[2] = 320;
                    a[3] = 80;
                    a[4] = 140;
                    a[5] = 35;
                    Answer = Answer + "\\item  55 \n";
                    break;

                case 3:
                    a[0] = 140;
                    a[1] = 70;
                    a[2] = 195;
                    a[3] = 65;
                    a[4] = 225;
                    a[5] = 75;
                    Answer = Answer + "\\item  70 \n";
                    break;

                case 4:
                    a[0] = 350;
                    a[1] = 70;
                    a[2] = 105;
                    a[3] = 35;
                    a[4] = 160;
                    a[5] = 80;
                    Answer = Answer + "\\item  61,5 \n";
                    break;

                case 5:
                    a[0] = 160;
                    a[1] = 80;
                    a[2] = 100;
                    a[3] = 50;
                    a[4] = 360;
                    a[5] = 90;
                    Answer = Answer + "\\item  77,5 \n";
                    break;
            }
            cout << "\\item Первые " << a[0] << " км автомобиль ехал со скоростью " << a[1] << " км/ч, следующие " << a[2] << " км – со скоростью " << a[3] << " км/ч, а последние " << a[4] << " км – со скоростью " << a[5] << " км/ч. Найдите среднюю скорость автомобиля на протяжении всего пути." << endl;
            break;

        case 6: // Движение протяженных тел
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    a[0] = 75;
                    a[1] = 3;
                    a[2] = 30;
                    Answer = Answer + "\\item  650 \n";
                    break;

                case 2:
                    a[0] = 36;
                    a[1] = 4;
                    a[2] = 54;
                    Answer = Answer + "\\item  600 \n";
                    break;

                case 3:
                    a[0] = 151;
                    a[1] = 5;
                    a[2] = 15;
                    Answer = Answer + "\\item  650 \n";
                    break;

                case 4:
                    a[0] = 129;
                    a[1] = 6;
                    a[2] = 8;
                    Answer = Answer + "\\item  300 \n";
                    break;

                case 5:
                    a[0] = 57;
                    a[1] = 3;
                    a[2] = 36;
                    Answer = Answer + "\\item  600 \n";
                    break;
            }
            cout << "\\item Поезд, двигаясь равномерно со скоростью " << a[0] << " км/ч, проезжает мимо пешехода, идущего параллельно путям со скоростью " << a[1] << " км/ч навстречу поезду, за " << a[2] << " секунд. Найдите длину поезда в метрах." << endl;
            break;

        case 7: // Движение по воде
            type_3 = rand()%4 + 1;
            switch(type_3)
            {
                case 1:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 56;
                            a[1] = 54;
                            a[2] = 5;
                            a[3] = 5;
                            Answer = Answer + "\\item  23 \n";
                            break;

                        case 2:
                            a[0] = 32;
                            a[1] = 24;
                            a[2] = 4;
                            a[3] = 5;
                            Answer = Answer + "\\item  15 \n";
                            break;

                        case 3:
                            a[0] = 84;
                            a[1] = 66;
                            a[2] = 10;
                            a[3] = 5;
                            Answer = Answer + "\\item  16 \n";
                            break;

                        case 4:
                            a[0] = 72;
                            a[1] = 54;
                            a[2] = 9;
                            a[3] = 5;
                            Answer = Answer + "\\item  15 \n";
                            break;

                        case 5:
                            a[0] = 48;
                            a[1] = 42;
                            a[2] = 5;
                            a[3] = 5;
                            Answer = Answer + "\\item  19 \n";
                            break;
                    }
                    cout << "\\item Баржа прошла по течению реки " << a[0] << " км и, повернув обратно, прошла ещё " << a[1] << " км, затратив на весь путь " << a[2] << " часов. Найдите собственную скорость баржи, если скорость течения реки равна " << a[3] << " км/ч." << endl;
                    break;

                case 2:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 72;
                            a[1] = 33;
                            a[2] = 3;
                            Answer = Answer + "\\item  15 \n";
                            break;

                        case 2:
                            a[0] = 126;
                            a[1] = 36;
                            a[2] = 4;
                            Answer = Answer + "\\item  32 \n";
                            break;

                        case 3:
                            a[0] = 48;
                            a[1] = 25;
                            a[2] = 5;
                            Answer = Answer + "\\item  25 \n";
                            break;

                        case 4:
                            a[0] = 140;
                            a[1] = 51;
                            a[2] = 3;
                            Answer = Answer + "\\item  18 \n";
                            break;

                        case 5:
                            a[0] = 108;
                            a[1] = 50;
                            a[2] = 5;
                            Answer = Answer + "\\item  25 \n";
                            break;
                    }
                    cout << "\\item Расстояние между пристанями А и В равно " << a[0] << " км. Из А в В по течению реки отправился плот, а через час вслед за ним отправилась моторная лодка, которая, прибыв в пункт В, тотчас повернула обратно и возвратилась в А. К этому времени плот прошёл " << a[1] << " км. Найдите скорость лодки в неподвижной воде, если скорость течения реки равна " << a[2] << " км/ч." << endl;
                    break;

                case 3:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 72;
                            a[1] = 2;
                            a[2] = 3;
                            Answer = Answer + "\\item  15 \n";
                            break;

                        case 2:
                            a[0] = 77;
                            a[1] = 2;
                            a[2] = 4;
                            Answer = Answer + "\\item  18 \n";
                            break;

                        case 3:
                            a[0] = 132;
                            a[1] = 5;
                            a[2] = 5;
                            Answer = Answer + "\\item  17 \n";
                            break;

                        case 4:
                            a[0] = 192;
                            a[1] = 4;
                            a[2] = 4;
                            Answer = Answer + "\\item  20 \n";
                            break;

                        case 5:
                            a[0] = 255;
                            a[1] = 2;
                            a[2] = 1;
                            Answer = Answer + "\\item  16 \n";
                            break;
                    }
                    cout << "\\item Моторная лодка прошла против течения реки " << a[0] << " км и вернулась в пункт отправления, затратив на обратный путь на " << a[1] << " часа меньше, чем на путь против течения. Найдите скорость лодки в неподвижной воде, если скорость течения реки равна " << a[2] << " км/ч." << endl;
                    break;

                case 4:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 210;
                            a[1] = 4;
                            a[2] = 9;
                            a[3] = 27;
                            Answer = Answer + "\\item  24 \n";
                            break;

                        case 2:
                            a[0] = 80;
                            a[1] = 5;
                            a[2] = 23;
                            a[3] = 35;
                            Answer = Answer + "\\item  15 \n";
                            break;

                        case 3:
                            a[0] = 280;
                            a[1] = 4;
                            a[2] = 15;
                            a[3] = 39;
                            Answer = Answer + "\\item  24 \n";
                            break;

                        case 4:
                            a[0] = 216;
                            a[1] = 5;
                            a[2] = 5;
                            a[3] = 23;
                            Answer = Answer + "\\item  25 \n";
                            break;

                        case 5:
                            a[0] = 70;
                            a[1] = 24;
                            a[2] = 8;
                            a[3] = 14;
                            Answer = Answer + "\\item  4 \n";
                            break;
                    }
                    cout << "\\item Теплоход проходит по течению реки до пункта назначения " << a[0] << " км и после стоянки возвращается в пункт отправления. Найдите скорость теплохода в неподвижной воде, если скорость течения равна " << a[1] << " км/ч, стоянка длится " << a[2] << " часов, а в пункт отправления теплоход возвращается через " << a[3] << " часа после отплытия из него." << endl;
                    break;
                
            }
            break;

    }
    return Answer;
}

string Second21Per(int i, int AllType)
{
    string Answer;
    int type;
    int a[10];
    type = rand()%2 + 1;
    int type_2, type_3;
    switch(type)
    {
        case 1:
            type_3 = rand()%2 + 1;
            switch(type_3)
            {
                case 1:
                    type_2 = rand()%4 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 10;
                            a[1] = 16;
                            a[2] = 55;
                            a[3] = 61;
                            Answer = Answer + "\\item  8,7 \n";
                            break;

                        case 2:
                            a[0] = 12;
                            a[1] = 8;
                            a[2] = 65;
                            a[3] = 60;
                            Answer = Answer + "\\item  10,2 \n";
                            break;

                        case 3:
                            a[0] = 80;
                            a[1] = 70;
                            a[2] = 63;
                            a[3] = 65;
                            Answer = Answer + "\\item  28 \n";
                            break;

                        case 4:
                            a[0] = 40;
                            a[1] = 25;
                            a[2] = 30;
                            a[3] = 36;
                            Answer = Answer + "\\item  4 \n";
                            break;

                        case 5:
                            a[0] = 90;
                            a[1] = 45;
                            a[2] = 32;
                            a[3] = 33;
                            Answer = Answer + "\\item  27 \n";
                            break;
                    }
                    cout << "\\item Имеются два сосуда, содержащие " << a[0] << " кг и " << a[1] << " кг раствора кислоты различной концентрации. Если их слить вместе, то получится раствор, содержащий " << a[2] << "\\% кислоты. Если же слить равные массы этих растворов, то полученный раствор будет содержать " << a[3] << " \\% кислоты. Сколько процентов кис- лоты содержится в первом растворе?" << endl;
                    break;

                case 2:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 78;
                            a[1] = 22;
                            a[2] = 22;
                            Answer = Answer + "\\item  78 \n";
                            break;

                        case 2:
                            a[0] = 93;
                            a[1] = 16;
                            a[2] = 21;
                            Answer = Answer + "\\item  252 \n";
                            break;

                        case 3:
                            a[0] = 88;
                            a[1] = 30;
                            a[2] = 72;
                            Answer = Answer + "\\item  420 \n";
                            break;

                        case 4:
                            a[0] = 75;
                            a[1] = 25;
                            a[2] = 45;
                            Answer = Answer + "\\item  135 \n";
                            break;

                        case 5:
                            a[0] = 95;
                            a[1] = 22;
                            a[2] = 55;
                            Answer = Answer + "\\item  858 \n";
                            break;
                    }
                    cout << "\\item Свежие фрукты содержат " << a[0] << "\\% воды, а высушенные – " << a[1] << "\\%. Сколько требуется свежих фруктов для приготовления " << a[2] << " кг высушенных фруктов?" << endl;
                    break;
            }
            break;

        case 2:
            type_3 = rand()%2 + 1;
            switch(type_3)
            {
                case 1:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 13;
                            a[1] = 208;
                            a[2] = 8;
                            Answer = Answer + "\\item  13 \n";
                            break;

                        case 2:
                            a[0] = 9;
                            a[1] = 216;
                            a[2] = 4;
                            Answer = Answer + "\\item  18 \n";
                            break;

                        case 3:
                            a[0] = 5;
                            a[1] = 200;
                            a[2] = 2;
                            Answer = Answer + "\\item  20 \n";
                            break;

                        case 4:
                            a[0] = 10;
                            a[1] = 60;
                            a[2] = 3;
                            Answer = Answer + "\\item  10 \n";
                            break;

                        case 5:
                            a[0] = 9;
                            a[1] = 112;
                            a[2] = 4;
                            Answer = Answer + "\\item  12 \n";
                            break;
                    }
                    cout << "\\item Первый рабочий за час делает на " << a[0] << " деталей больше, чем второй, и выполняет заказ, состоящий из " << a[1] << " деталей, на " << a[2] << " часов быстрее, чем второй рабочий, выполняющий такой же заказ. Сколько деталей в час делает второй рабочий?" << endl;
                    break;

                case 2:
                    type_2 = rand()%5 + 1;
                    switch(type_2)
                    {
                        case 1:
                            a[0] = 3;
                            a[1] = 260;
                            a[2] = 6;
                            Answer = Answer + "\\item  13 \n";
                            break;

                        case 2:
                            a[0] = 16;
                            a[1] = 105;
                            a[2] = 4;
                            Answer = Answer + "\\item  30 \n";
                            break;

                        case 3:
                            a[0] = 13;
                            a[1] = 208;
                            a[2] = 8;
                            Answer = Answer + "\\item  26 \n";
                            break;

                        case 4:
                            a[0] = 5;
                            a[1] = 200;
                            a[2] = 2;
                            Answer = Answer + "\\item  25 \n";
                            break;

                        case 5:
                            a[0] = 15;
                            a[1] = 100;
                            a[2] = 6;
                            Answer = Answer + "\\item  25 \n";
                            break;
                    }
                    cout << "\\item Первая труба пропускает на " << a[0] << " литров воды в минуту меньше, чем вторая труба. Сколько литров воды в минуту пропускает вторая труба, если резервуар объёмом " << a[1] << " литров она заполняет на " << a[2] << " минуты быстрее, чем первая труба?" << endl;
                    break;
            }
            break;
    }
    return Answer;
}

string Second22Lin(int i, int AllType)
{
    string Answer;
    int type;
    type = rand()%5 + 1;
    switch(type)
    {
        case 1:
            cout << "\\item Постройте график функции:" << endl
                << "    $$y = \\begin{cases}" << endl
                << "    x - 2.5, & \\text{если } x < 2, \\\\" << endl
                << "    -x + 1.5, & \\text{если } 2 \\leq x \\leq 3, \\\\" << endl
                << "      x - 5, & \\text{если } x > 3." << endl
                << "    \\end{cases}$$" << endl
                << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
            Answer = Answer + "\\item  $[-2;-1,5)\\cup {-0,5}$ \n";
            break;

        case 2:
            cout << "\\item Постройте график функции:" << endl
                << "    $$y = \\begin{cases}" << endl
                << "    4x - 5, & \\text{если } x < 1, \\\\" << endl
                << "    -2,5x + 5, & \\text{если } 1 \\leq x \\leq 4, \\\\" << endl
                << "      x - 9, & \\text{если } x > 4." << endl
                << "    \\end{cases}$$" << endl
                << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
            Answer = Answer + "\\item  $(-1;2,5]\\cup {-5}$ \n";
            break;

        case 3:
            cout << "\\item Постройте график функции:" << endl
                << "    $$y = \\begin{cases}" << endl
                << "    3x - 3, & \\text{если } x < 2, \\\\" << endl
                << "    -3x + 8.5, & \\text{если } 2 \\leq x \\leq 3, \\\\" << endl
                << "      3,5x - 11, & \\text{если } x > 3." << endl
                << "    \\end{cases}$$" << endl
                << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
            Answer = Answer + "\\item  $(2,5;3]\\cup {-0,5}$ \n";
            break;

        case 4:
            cout << "\\item Постройте график функции:" << endl
                << "    $$y = \\begin{cases}" << endl
                << "    2x - 2, & \\text{если } x < 3, \\\\" << endl
                << "    -3x + 13, & \\text{если } 3 \\leq x \\leq 4, \\\\" << endl
                << "      1,5x - 7, & \\text{если } x > 4." << endl
                << "    \\end{cases}$$" << endl
                << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
            Answer = Answer + "\\item  $[-1;1)\\cup {4}$ \n";
            break;

        case 5:
            cout << "\\item Постройте график функции:" << endl
                << "    $$y = \\begin{cases}" << endl
                << "    2,5x - 1, & \\text{если } x < 2, \\\\" << endl
                << "    -3,5x + 11, & \\text{если } 2 \\leq x \\leq 3, \\\\" << endl
                << "      x - 1, & \\text{если } x > 3." << endl
                << "    \\end{cases}$$" << endl
                << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
            Answer = Answer + "\\item  $[0,5;2)\\cup {4}$ \n";
            break;
    }
    return Answer;
}

string Second22Parab(int i, int AllType)
{
    string Answer;
    int type;
    type = rand()%9 + 1;
    int type_2;
    switch(type)
    {
        case 1:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    -x^2 - 2x + 3, & \\text{если } x \\geq -2, \\\\" << endl
                        << "      -x - 1, & \\text{если } x < - 2." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  $[1;3)\\cup {4}$ \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    x^2 - 10x + 25, & \\text{если } x \\geq 4, \\\\" << endl
                        << "      x - 2, & \\text{если } x < 4." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  $(1;2]\\cup {0}$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    -x^2 - 4x - 1, & \\text{если } x \\geq -3, \\\\" << endl
                        << "      -x - 3, & \\text{если } x < - 3." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  $[0;2) \\cup {3}$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    x^2 - 6x + 11, & \\text{если } x \\geq 2, \\\\" << endl
                        << "      x + 3, & \\text{если } x < 2." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  $(3;5]\\cup {2}$ \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    -x^2 + 10x - 21, & \\text{если } x \\geq 3, \\\\" << endl
                        << "      -x + 5, & \\text{если } x < 3." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях m прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  $[0;2) \\cup {4}$ \n";
                    break;
            }
            break;

        case 2:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции $y=|x^2-16|$. Какое наибольшее число общих точек график данной функции может иметь с прямой, параллельной оси абсцисс?" << endl;
                    Answer = Answer + "\\item  4 \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции $y=|x^2-9|$. Какое наибольшее число общих точек график данной функции может иметь с прямой, параллельной оси абсцисс?" << endl;
                    Answer = Answer + "\\item  4 \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции $y=|x^2+x-2|$. Какое наибольшее число общих точек график данной функции может иметь с прямой, параллельной оси абсцисс?" << endl;
                    Answer = Answer + "\\item  4 \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции $y=|x^2+2x-3|$. Какое наибольшее число общих точек график данной функции может иметь с прямой, параллельной оси абсцисс?" << endl;
                    Answer = Answer + "\\item  4 \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции $y=|x^2+4x-5|$. Какое наибольшее число общих точек график данной функции может иметь с прямой, параллельной оси абсцисс?" << endl;
                    Answer = Answer + "\\item  4 \n";
                    break;
            }
            break;

        case 3:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции $y=x|x|-|x|-5x$. Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  4;-9 \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции $y=x|x|-|x|-2x$. Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  -2,25;0,25 \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции $y=x|x|-|x|-3x$. Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  -4;1 \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции $y=x|x|-|x|-6x$. Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  -12,25; 6,25 \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции $y=x|x|+2|x|-5x$. Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  -2,25; 12,25 \n";
                    break;
            }
            break;

        case 4:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции $y=|x|(x-1)-5x$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  -9; 4 \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции $y=|x|(x-1)-3x$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  1; -4 \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции $y=|x|(x-1)-2x$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  -2,25; 0,25 \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции $y=|x|(x-1)-6x$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  -12,25; 6,25 \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции $y=|x|(x-1)-3x$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно две общие точки." << endl;
                    Answer = Answer + "\\item  6,25; -0,25 \n";
                    break;
            }
            break;

        case 5:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции $y=x^2-|2x+1|$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  0; 0,25 \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции $y=x^2-|4x+7|$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  $3;\\frac{49}{16}$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции $y=x^2-|6x+5|$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  $-4;\\frac{25}{36}$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции $y=x^2-|8x+3|$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  $-13;\\frac{9}{64}$ \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции $y=x^2-|6x+1|$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  $-8;\\frac{1}{36}$ \n";
                    break;
            }
            break;

        case 6:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции $y=x^2+3x-3|x+2|+2$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  $-1;0$ \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции $y=x^2-11x-2|x-5|+30$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  $-0,25;0$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции $y=x^2+13x-3|x+7|+42$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  $-1;0$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции $y=x^2-8x-4|x-3|+15$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  $-1;0$ \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции $y=x^2+14x-3|x+8|+48$ и определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно три общие точки." << endl;
                    Answer = Answer + "\\item  $-0,25;0$ \n";
                    break;
            }
            break;

        case 7:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции: $$y=\\frac{(0,5x^2-x)|x|}{x-2}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком ни одной общей точки." << endl;
                    Answer = Answer + "\\item  $2$ \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции: $$y=\\frac{(0,25x^2-x)|x|}{x-4}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком ни одной общей точки." << endl;
                    Answer = Answer + "\\item  $4$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции: $$y=\\frac{(0,75x^2-0,75x)|x|}{x-1}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком ни одной общей точки." << endl;
                    Answer = Answer + "\\item  $0,75$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции: $$y=\\frac{(0,75x^2-2,25x)|x|}{x-3}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком ни одной общей точки." << endl;
                    Answer = Answer + "\\item  $6,75$ \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции: $$y=\\frac{(0,5x^2+2x)|x|}{x+4}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком ни одной общей точки." << endl;
                    Answer = Answer + "\\item  $8$ \n";
                    break;
            }
            break;

        case 8:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции: $$y=\\frac{(x^2+1)(x-2)}{2-x}$$ Определите, при каких значениях параметра $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-2;2;-2,5$ \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции: $$y=\\frac{(x^2+4)(x-3)}{3-x}$$ Определите, при каких значениях параметра $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-4;4;-\\frac{13}{3}$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции: $$y=\\frac{(x^2+2,25)(x-1)}{1-x}$$ Определите, при каких значениях параметра $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-3;3;-3,25$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции: $$y=\\frac{(x^2+6,25)(x-1)}{1-x}$$ Определите, при каких значениях параметра $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-5;5;-7,25$ \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции: $$y=\\frac{(x^2+1)(x+3)}{-3-x}$$ Определите, при каких значениях параметра $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-2;2;\\frac{10}{3}$ \n";
                    break;
            }
            break;

        case 9:
            type_2 = rand()%4 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции: $$y=\\frac{x^4-13x^2+36}{(x-3)(x+2)}$$ Определите, при каких значениях параметра $c$ прямая $y=c$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-6,25$ \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции: $$y=\\frac{x^4-10x^2+9}{(x-3)(x+1)}$$ Определите, при каких значениях параметра $c$ прямая $y=c$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-4$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции: $$y=\\frac{x^4-20x^2+64}{(x+4)(x-2)}$$ Определите, при каких значениях параметра $c$ прямая $y=c$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-9$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции: $$y=\\frac{x^4-25x^2+144}{(x-4)(x+3)}$$ Определите, при каких значениях параметра $c$ прямая $y=c$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-12,25$ \n";
                    break;
            }
            break;
    }
    return Answer;
}

string Second22Drob(int i, int AllType)
{
    string Answer;
    int type;
    type = rand()%4 + 1;
    int type_2;
    switch(type)
    {
        case 1:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    x^2+1, & \\text{если } x \\geq -1, \\\\" << endl
                        << "      -\\frac{4}{x}, & \\text{если } x < -1." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком одну общую точку." << endl;
                    Answer = Answer + "\\item  $(0;1)\\cup(4;+\\infty)$ \n";
                    break;
                
                case 2:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    x^2+2, & \\text{если } x \\geq -2, \\\\" << endl
                        << "      -\\frac{6}{x}, & \\text{если } x < -2." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком одну общую точку." << endl;
                    Answer = Answer + "\\item  $(0;2)\\cup(6;+\\infty)$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    x^2-4x+4, & \\text{если } x \\geq -1, \\\\" << endl
                        << "      -\\frac{9}{x}, & \\text{если } x < -1." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком одну общую точку." << endl;
                    Answer = Answer + "\\item  ${0}\\cup[9;+\\infty)$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    x^2+6x+9, & \\text{если } x \\geq -5, \\\\" << endl
                        << "      -\\frac{20}{x}, & \\text{если } x < -5." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком одну общую точку." << endl;
                    Answer = Answer + "\\item  ${0}\\cup[4;+\\infty)$ \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции:" << endl
                        << "    $$y = \\begin{cases}" << endl
                        << "    x^2-2x+1, & \\text{если } x \\geq -2, \\\\" << endl
                        << "      -\\frac{18}{x}, & \\text{если } x < -2." << endl
                        << "    \\end{cases}$$" << endl
                        << "    Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком одну общую точку." << endl;
                    Answer = Answer + "\\item  ${0}\\cup[9;+\\infty)$ \n";
                    break;
            }
            break;

        case 2:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции: $$y=3-\\frac{x+2}{x^2+2x}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком общих точек." << endl;
                    Answer = Answer + "\\item  $3;3,5$ \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции: $$y=-2-\\frac{x+4}{x^2+4x}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком общих точек." << endl;
                    Answer = Answer + "\\item  $-2;-1,75$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции: $$y=1-\\frac{x+5}{x^2+5x}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком общих точек." << endl;
                    Answer = Answer + "\\item  $1;1,2$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции: $$y=-4-\\frac{x+1}{x^2+x}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком общих точек." << endl;
                    Answer = Answer + "\\item  $-4;-3$ \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции: $$y=2-\\frac{x-5}{x^2-5x}$$ Определите, при каких значениях $m$ прямая $y=m$ не имеет с графиком общих точек." << endl;
                    Answer = Answer + "\\item  $2;1,8$ \n";
                    break;
            }
            break;

        case 3:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции: $$y=\\frac{1}{2}\\left(\\left|\\frac{x}{2}-\\frac{2}{x}\\right|+\\frac{x}{2}+\\frac{2}{x}\\right)$$ Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-1;1$ \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции: $$y=\\frac{1}{2}\\left(\\left|\\frac{x}{3}-\\frac{3}{x}\\right|+\\frac{x}{3}+\\frac{3}{x}\\right)$$ Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-1;1$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции: $$y=\\frac{1}{2}\\left(\\left|\\frac{x}{4}-\\frac{4}{x}\\right|+\\frac{x}{4}+\\frac{4}{x}\\right)$$ Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-1;1$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции: $$y=\\frac{1}{2}\\left(\\left|\\frac{x}{6}-\\frac{6}{x}\\right|+\\frac{x}{6}+\\frac{6}{x}\\right)$$ Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-1;1$ \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции: $$y=\\frac{1}{2}\\left(\\left|\\frac{x}{1,5}-\\frac{1,5}{x}\\right|+\\frac{x}{1,5}+\\frac{1,5}{x}\\right)$$ Определите, при каких значениях $m$ прямая $y=m$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $-1;1$ \n";
                    break;
            }
            break;

        case 4:
            type_2 = rand()%5 + 1;
            switch(type_2)
            {
                case 1:
                    cout << "\\item Постройте график функции: $$y=\\frac{4x-5}{4x^2-5x}$$ и определите, при каких значениях $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $0,64$ \n";
                    break;

                case 2:
                    cout << "\\item Постройте график функции: $$y=\\frac{5x-8}{5x^2-8x}$$ и определите, при каких значениях $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $2,56$ \n";
                    break;

                case 3:
                    cout << "\\item Постройте график функции: $$y=\\frac{7x-10}{7x^2-10x}$$ и определите, при каких значениях $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $0,49$ \n";
                    break;

                case 4:
                    cout << "\\item Постройте график функции: $$y=\\frac{6x-7}{6x^2-7x}$$ и определите, при каких значениях $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $\\frac{36}{49}$ \n";
                    break;

                case 5:
                    cout << "\\item Постройте график функции: $$y=\\frac{2x+5}{2x^2+5x}$$ и определите, при каких значениях $k$ прямая $y=kx$ имеет с графиком ровно одну общую точку." << endl;
                    Answer = Answer + "\\item  $0,16$ \n";
                    break;
            }
            break;
    }
    return Answer;
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    int count_task[68];              // Создает массив из номеров заданий
    for (int i = 0; i < 68; i++)     // Обнуляет количество заданий в номерах
        count_task[i] = 0;
    int choice = 0;
    string Answers = "\\newpage \n {\\centering \\subsubsection*{Ответы}} \n \\begin{enumerate} \n";
    do {
        choice = main_menu();       // Выводит на экран главное меню
        switch (choice)
        {
        case 1:
            do {
                cout << "\033[2J\033[1;1H";
                cout << "Выберите темы:" << endl;
                cout << "1. Числа и вычисления (" << count_task[0] + count_task[1] + count_task[2] + count_task[3] + count_task[4] + count_task[5] + count_task[6] + count_task[37] << ")" << endl;
                cout << "2. Алгебраические выражения (" << count_task[7] + count_task[8] + count_task[9] + count_task[10] + count_task[38] << ")" << endl;
                cout << "3. Теория вероятности (" << count_task[11] + count_task[39] << ")" << endl; // Задание 12
                cout << "4. Числовые неравенства, координатная прямая (" << count_task[12] + count_task[13] + count_task[14] + count_task[40] << ")" << endl;
                cout << "5. Уравнения (" << count_task[15] + count_task[16] + count_task[17] + count_task[41] << ")" << endl;
                cout << "6. Неравенства (" << count_task[18] + count_task[19] + count_task[20] + count_task[21] + count_task[42] << ")" << endl;
                cout << "7. Рассчеты по формулам (" << count_task[22] + count_task[43] << ")" << endl;
                cout << "8. Графики (" << count_task[23] + count_task[44] << ")" << endl;
                cout << "9. Прогрессии (" << count_task[24] + count_task[25] + count_task[26] + count_task[45] << ")" << endl;
                cout << "10. Треугольники (" << count_task[27] + count_task[28] + count_task[29] + count_task[30] + count_task[31] + count_task[46] << ")" << endl;
                cout << "11. Многоугольники (" << count_task[32] + count_task[33] + count_task[34] + count_task[35] + count_task[47] << ")" << endl;
                cout << "12. Окружности (" << count_task[36] + count_task[48] << ")" << endl;
                cout << "13. Первые пять задач (" << count_task[49] + count_task[50] + count_task[51] + count_task[52] + count_task[53] + count_task[54] + count_task[55] + count_task[56] << ")" << endl;
                cout << "14. Задание 20: Алгебраические выражения, уравнения, неравенства (" << count_task[57] + count_task[58] + count_task[59] + count_task[60] << ")" << endl;
                cout << "15. Задание 21: Текстовые задачи (" << count_task[61] + count_task[62] + count_task[63] << ")" << endl;
                cout << "16. Задание 22: Графики (" << count_task[64] + count_task[65] + count_task[66] + count_task[67] << ")" << endl;
                cout << endl << "69. Сгенерировать" << endl;
                cout << "0. Назад" << endl;
                cout << "Ваш выбор: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    do {
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Обычные дроби (" << count_task[0] + count_task[1] + count_task[2] << ")" << endl;
                        cout << "2. Десятичные дроби (" << count_task[3] + count_task[4] + count_task[5] << ")" << endl;
                        cout << "3. Все целиком (" << count_task[6] << ")" << endl; // Задание 7
                        cout << "4. Все типы этого номер (" << count_task[37] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            do {
                                cout << "\033[2J\033[1;1H";
                                cout << "1. Сложение и вычитание дробей (" << count_task[0] << ")" << endl;   // Задание 1
                                cout << "2. Умножение и деление дробей (" << count_task[1] << ")" << endl;    // Задание 2
                                cout << "3. Все целиком (" << count_task[2] << ")" << endl << endl;           // Задание 3
                                cout << "0. Назад" << endl;
                                cout << "Ваш выбор: ";
                                cin >> choice;
                                switch (choice)
                                {
                                case 1:
                                    cout << "\033[2J\033[1;1H";
                                    cout << "Введите количество заданий: ";
                                    cin >> count_task[0];
                                    break;

                                case 2:
                                    cout << "\033[2J\033[1;1H";
                                    cout << "Введите количество заданий: ";
                                    cin >> count_task[1];
                                    break;

                                case 3:
                                    cout << "\033[2J\033[1;1H";
                                    cout << "Введите количество заданий: ";
                                    cin >> count_task[2];
                                    break;
                                    
                                }
                            } while (choice != 0);
                            choice = -1;
                            break;
                        case 2:
                            do {
                                cout << "\033[2J\033[1;1H";
                                cout << "1. Сложение и вычитание десятичных дробей (" << count_task[3] << ")" << endl;  // Задание 4
                                cout << "2. Умножение и деление десятичных дробей (" << count_task[4] << ")" << endl;   // Задание 5
                                cout << "3. Все целиком (" << count_task[5] << ")" << endl << endl;                     // Задание 6
                                cout << "0. Назад" << endl;
                                cout << "Ваш выбор: ";
                                cin >> choice;
                                switch (choice)
                                {
                                case 1:
                                    cout << "\033[2J\033[1;1H";
                                    cout << "Введите количество заданий: ";
                                    cin >> count_task[3];
                                    break;

                                case 2:
                                    cout << "\033[2J\033[1;1H";
                                    cout << "Введите количество заданий: ";
                                    cin >> count_task[4];
                                    break;

                                case 3:
                                    cout << "\033[2J\033[1;1H";
                                    cout << "Введите количество заданий: ";
                                    cin >> count_task[5];
                                    break;
                                }

                            } while (choice != 0);
                            choice = -1;
                            break;
                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[6];
                            break;

                        case 4:
                            count_task[37] = 1;
                            break;
                        }
                    } while (choice != 0);
                    choice = -1;
                    break;
                case 2:
                    do {
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Буквенные выражения (" << count_task[7] << ")" << endl; // Задание 8
                        cout << "2. Степени (" << count_task[8] << ")" << endl; // Задание 9
                        cout << "3. Корни (" << count_task[9] << ")" << endl; // Задание 10
                        cout << "4. Все целиком (" << count_task[10] << ")" << endl; // Задание 11
                        cout << "5. Все типы этого номер (" << count_task[38] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[7];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[8];
                            break;

                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[9];
                            break;

                        case 4:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[10];
                            break;

                        case 5:
                            count_task[38] = 1;
                            break;
                        }
                    } while (choice != 0);
                    choice = -1;
                    break;
                case 3:
                    do {
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Произвольное количество (" << count_task[11] << ")" << endl;
                        cout << "2. Все типы этого номер (" << count_task[39] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[11];
                            break;

                        case 2:
                            count_task[39] = 1;
                            break;
                        }
                    } while (choice != 0);
                    choice = -1;
                    break;
                case 4:
                    do {
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Координатная прямая (" << count_task[12] << ")" << endl; // Задание 13
                        cout << "2. Числовые неравенства (" << count_task[13] << ")" << endl; // Задание 14
                        cout << "3. Все целиком (" << count_task[14] << ")" << endl; // Задание 15
                        cout << "4. Все типы этого номер (" << count_task[40] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[12];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[13];
                            break;

                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[14];
                            break;

                        case 4:
                            count_task[40] = 1;
                            break;
                        }
                    } while (choice != 0);
                    choice = -1;
                    break;
                case 5:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Линейные уравнения (" << count_task[15] << ")" << endl; // Задание 16
                        cout << "2. Квадратные уравнения (" << count_task[16] << ")" << endl; // Задание 17
                        cout << "3. Все целиком (" << count_task[17] << ")" << endl; // Задание 18
                        cout << "4. Все типы этого номер (" << count_task[41] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[15];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[16];
                            break;

                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[17];
                            break;

                        case 4:
                            count_task[41] = 1;
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 6:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Линейные неравенства (" << count_task[18] << ")" << endl; // Задание 19
                        cout << "2. Квадратные неравенства (" << count_task[19] << ")" << endl; // Задание 20
                        cout << "3. Системы неравенства (" << count_task[20] << ")" << endl; // Задание 21
                        cout << "4. Все целиком (" << count_task[21] << ")" << endl; // Задание 22
                        cout << "5. Все типы этого номер (" << count_task[42] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[18];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[19];
                            break;

                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[20];
                            break;

                        case 4:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[21];
                            break;

                        case 5:
                            count_task[42] = 1;
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 7:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Произвольное количество (" << count_task[22] << ")" << endl; // Задание 19
                        cout << "2. Все типы этого номер (" << count_task[43] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[22];
                            break;

                        case 2:
                            count_task[43] = 1;
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 8:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Произвольное количество (" << count_task[23] << ")" << endl; // Задание 19
                        cout << "2. Все типы этого номер (" << count_task[44] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[23];
                            break;

                        case 2:
                            count_task[44] = 1;
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 9:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Арифметические прогрессии (" << count_task[24] << ")" << endl; // Задание 25
                        cout << "2. Геометрические прогрессии (" << count_task[25] << ")" << endl; // Задание 26
                        cout << "3. Все целиком (" << count_task[26] << ")" << endl; // Задание 27
                        cout << "4. Все типы этого номер (" << count_task[45] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[24];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[25];
                            break;

                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[26];
                            break;

                        case 4:
                            count_task[45] = 1;
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 10:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Треугольники - углы (" << count_task[27] << ")" << endl; // Задание 25
                        cout << "2. Треугольники - стороны и площадь (" << count_task[28] << ")" << endl; // Задание 26
                        cout << "3. Треугольники - на квадратной решетке (" << count_task[29] << ")" << endl; // Задание 26
                        cout << "4. Треугольники - тригонометрия (" << count_task[30] << ")" << endl; // Задание 26
                        cout << "5. Все целиком (" << count_task[31] << ")" << endl; // Задание 27
                        cout << "6. Все типы этого номер (" << count_task[46] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[27];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[28];
                            break;

                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[29];
                            break;

                        case 4:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[30];
                            break;

                        case 5:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[31];
                            break;

                        case 6:
                            count_task[46] = 1;
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 11:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Параллелограммы (" << count_task[32] << ")" << endl; // Задание 33
                        cout << "2. Трапеции (" << count_task[33] << ")" << endl; // Задание 34
                        cout << "3. Многоугольник - на квадратной решетке (" << count_task[34] << ")" << endl; // Задание 35
                        cout << "4. Все целиком (" << count_task[35] << ")" << endl; // Задание 36
                        cout << "5. Все типы этого номер (" << count_task[47] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[32];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[33];
                            break;

                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[34];
                            break;

                        case 4:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[35];
                            break;

                        case 5:
                            count_task[47] = 1;
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 12:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Произвольное количество (" << count_task[36] << ")" << endl; // Задание 19
                        cout << "2. Все типы этого номер (" << count_task[48] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[36];
                            break;

                        case 2:
                            count_task[48] = 1;
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 13:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Дороги (" << count_task[49] << ")" << endl;
                        cout << "2. Квартира (" << count_task[50] << ")" << endl;
                        cout << "3. Листы (" << count_task[51] << ")" << endl;
                        cout << "4. Печи (" << count_task[52] << ")" << endl;
                        cout << "5. Тарифы (" << count_task[53] << ")" << endl;
                        cout << "6. Участки (" << count_task[54] << ")" << endl;
                        cout << "7. Шины (" << count_task[55] << ")" << endl;
                        cout << "8. Все целиком (" << count_task[56] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[49];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[50];
                            break;
                        
                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[51];
                            break;

                        case 4:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[52];
                            break;

                        case 5:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[53];
                            break;

                        case 6:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[54];
                            break;
                        
                        case 7:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[55];
                            break;

                        case 8:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[56];
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 14:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Уравнения и выражения (" << count_task[57] << ")" << endl;
                        cout << "2. Системы уравнений (" << count_task[58] << ")" << endl;
                        cout << "3. Неравенства (" << count_task[59] << ")" << endl;
                        cout << "4. Все целиком (" << count_task[60] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[57];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[58];
                            break;

                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[59];
                            break;

                        case 4:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[60];
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 15:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Задачи на движение (" << count_task[61] << ")" << endl;
                        cout << "2. Работа и проценты (" << count_task[62] << ")" << endl;
                        cout << "3. Все целиком (" << count_task[63] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[61];
                            break;

                        case 2:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[62];
                            break;

                        case 3:
                            cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[63];
                            break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 16:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Линейная функция (" << count_task[64] << ")" << endl;
                        cout << "2. Параболы (" << count_task[65] << ")" << endl;
                        cout << "3. Дробные функции (" << count_task[66] << ")" << endl;
                        cout << "4. Все целиком (" << count_task[67] << ")" << endl;
                        cout << endl << "0. Назад" << endl;
                        cout << "Ваш выбор: ";
                        cin >> choice;
                        switch (choice)
                        {
                            case 1:
                                cout << "\033[2J\033[1;1H";
                                cout << "Введите количество заданий: ";
                                cin >> count_task[64];
                                break;

                            case 2:
                                cout << "\033[2J\033[1;1H";
                                cout << "Введите количество заданий: ";
                                cin >> count_task[65];
                                break;

                            case 3:
                                cout << "\033[2J\033[1;1H";
                                cout << "Введите количество заданий: ";
                                cin >> count_task[66];
                                break;

                            case 4:
                                cout << "\033[2J\033[1;1H";
                                cout << "Введите количество заданий: ";
                                cin >> count_task[67];
                                break;
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 69:
                    cout << "\033[2J\033[1;1H";
                    int Count = 0;
                    if(count_task[49] != 0)
                    {
                        for (int i = 0; i < count_task[49]; i++)
                        {
                            Answers = Answers + FirstFiveRoad(Count, 0);
                            Count = Count + 5;
                        }
                        count_task[49] = 0;
                    }
                    if(count_task[50] != 0)
                    {
                        for (int i = 0; i < count_task[50]; i++)
                        {
                            Answers = Answers + FirstFiveFlat(Count, 0);
                            Count = Count + 5;
                        }
                        count_task[50] = 0;
                    }
                    if(count_task[51] != 0)
                    {
                        for (int i = 0; i < count_task[51]; i++)
                        {
                            Answers = Answers + FirstFivePaper(Count, 0);
                            Count = Count + 5;
                        }
                        count_task[51] = 0;
                    }
                    if(count_task[52] != 0)
                    {
                        for (int i = 0; i < count_task[52]; i++)
                        {
                            Answers = Answers + FirstFivePechi(Count, 0);
                            Count = Count + 5;
                        }
                        count_task[52] = 0;
                    }
                    if(count_task[53] != 0)
                    {
                        for (int i = 0; i < count_task[53]; i++)
                        {
                            Answers = Answers + FirstFiveTarif(Count, 0);
                            Count = Count + 5;
                        }
                        count_task[53] = 0;
                    }
                    if(count_task[54] != 0)
                    {
                        for (int i = 0; i < count_task[54]; i++)
                        {
                            Answers = Answers + FirstFiveDacha(Count, 0);
                            Count = Count + 5;
                        }
                        count_task[54] = 0;
                    }
                    if(count_task[55] != 0)
                    {
                        for (int i = 0; i < count_task[55]; i++)
                        {
                            Answers = Answers + FirstFiveKolesa(Count, 0);
                            Count = Count + 5;
                        }
                        count_task[55] = 0;
                    }
                    if(count_task[56] != 0)
                    {
                        for (int i = 0; i < count_task[56]; i++)
                        {
                            int q = rand()%7 + 1;
                            switch(q)
                            {
                                case 1:
                                    Answers = Answers + FirstFiveDacha(Count, 0);
                                    Count = Count + 5;
                                    break;

                                case 2:
                                    Answers = Answers + FirstFiveFlat(Count, 0);
                                    Count = Count + 5;
                                    break;

                                case 3:
                                    Answers = Answers + FirstFiveKolesa(Count, 0);
                                    Count = Count + 5;
                                    break;

                                case 4:
                                    Answers = Answers + FirstFivePaper(Count, 0);
                                    Count = Count + 5;
                                    break;

                                case 5:
                                    Answers = Answers + FirstFivePechi(Count, 0);
                                    Count = Count + 5;
                                    break;

                                case 6:
                                    Answers = Answers + FirstFiveRoad(Count, 0);
                                    Count = Count + 5;
                                    break;

                                case 7:
                                    Answers = Answers + FirstFiveTarif(Count, 0);
                                    Count = Count + 5;
                                    break;
                            }
                        }
                        count_task[56] = 0;
                    }
                    if (count_task[0] != 0)
                    {
                        for (int i = 0; i < count_task[0]; i++)
                        {
                            Answers = Answers + FractionPlusMinus(Count, 0);
                            Count++;
                        }
                        count_task[0] = 0;
                    }
                    if (count_task[1] != 0)
                    {
                        for (int i = 0; i < count_task[1]; i++)
                        {
                            Answers = Answers + FractionMultDiv(Count, 0);
                            Count++;
                        }
                        count_task[1] = 0;
                    }
                    if (count_task[2] != 0)
                    {
                        for (int i = 0; i < count_task[2]; i++)
                        {
                            if (pow(-1, rand()) > 0)
                                Answers = Answers + FractionMultDiv(Count, 0);
                            else
                                Answers = Answers + FractionPlusMinus(Count, 0);
                            Count++;
                        }
                        count_task[2] = 0;
                    }
                    if (count_task[3] != 0)
                    {
                        for (int i = 0; i < count_task[3]; i++)
                        {
                            Answers = Answers + DFractionPlusMinus(Count);
                            Count++;
                        }
                        count_task[3] = 0;
                    }
                    if (count_task[4] != 0)
                    {
                        for (int i = 0; i < count_task[4]; i++)
                        {
                            Answers = Answers + DFractionMultDiv(Count, 0);
                            Count++;
                        }
                        count_task[4] = 0;
                    }
                    if (count_task[5] != 0)
                    {
                        for (int i = 0; i < count_task[5]; i++)
                        {
                            int z = rand();
                            if (z % 2 == 0)
                            {
                                Answers = Answers + DFractionPlusMinus(Count);
                                Count++;
                            }
                            else
                            {
                                Answers = Answers + DFractionMultDiv(Count, 0);
                                Count++;
                            }
                        }
                        count_task[5] = 0;
                    }
                    if (count_task[6] != 0)
                    {
                        for (int i = 0; i < count_task[6]; i++)
                        {
                            int z = rand() % 4 + 1;
                            switch (z)
                            {
                            case 1:
                                Answers = Answers + FractionPlusMinus(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + FractionMultDiv(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + DFractionPlusMinus(Count);
                                Count++;
                                break;

                            case 4:
                                Answers = Answers + DFractionMultDiv(Count, 0);
                                Count++;
                                break;
                            }
                        }
                        count_task[6] = 0;
                    }
                    if (count_task[7] != 0)
                    {
                        for (int i = 0; i < count_task[7]; i++)
                        {
                            Answers = Answers + LetterEqu(Count, 0);
                            Count++;
                        }
                        count_task[7] = 0;
                    }
                    if (count_task[8] != 0)
                    {
                        for (int i = 0; i < count_task[8]; i++)
                        {
                            Answers = Answers + Pow(Count, 0);
                            Count++;
                        }
                        count_task[8] = 0;
                    }
                    if (count_task[9] != 0)
                    {
                        for (int i = 0; i < count_task[9]; i++)
                        {
                            Answers = Answers + Sqrt(Count, 0);
                            Count++;
                        }
                        count_task[9] = 0;
                    }
                    if (count_task[10] != 0)
                    {
                        for (int i = 0; i < count_task[10]; i++)
                        {
                            int type_1 = rand() % 3 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + LetterEqu(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Pow(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + Sqrt(Count, 0);
                                Count++;
                                break;
                            }
                        }
                        count_task[10] = 0;
                    }
                    if (count_task[11] != 0)
                    {
                        for (int i = 0; i < count_task[11]; i++)
                        {
                            Answers = Answers + TeorVer(Count, 0);
                            Count++;
                        }
                        count_task[11] = 0;
                    }
                    if (count_task[12] != 0)
                    {
                        for (int i = 0; i < count_task[12]; i++)
                        {
                            Answers = Answers + NumberLine1(Count, 0);
                            Count++;
                        }
                        count_task[12] = 0;
                    }
                    if (count_task[13] != 0)
                    {
                        for (int i = 0; i < count_task[13]; i++)
                        {
                            Answers = Answers + NumberLine2(Count, 0);
                            Count++;
                        }
                        count_task[13] = 0;
                    }
                    if (count_task[14] != 0)
                    {
                        for (int i = 0; i < count_task[14]; i++)
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + NumberLine1(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + NumberLine2(Count, 0);
                                Count++;
                                break;
                            }
                        }
                        count_task[14] = 0;
                    }
                    if (count_task[15] != 0)
                    {
                        for (int i = 0; i < count_task[15]; i++)
                        {
                            Answers = Answers + LineUravn(Count, 0);
                            Count++;
                        }
                        count_task[15] = 0;
                    }
                    if (count_task[16] != 0)
                    {
                        for (int i = 0; i < count_task[16]; i++)
                        {
                            Answers = Answers + KvadrUravn(Count, 0);
                            Count++;
                        }
                        count_task[16] = 0;
                    }
                    if (count_task[17] != 0)
                    {
                        for (int i = 0; i < count_task[17]; i++)
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + LineUravn(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + KvadrUravn(Count, 0);
                                Count++;
                                break;
                            }
                        }
                        count_task[17] = 0;
                    }
                    if (count_task[18] != 0)
                    {
                        for (int i = 0; i < count_task[18]; i++)
                        {
                            Answers = Answers + LineNerav(Count, 0);
                            Count++;
                        }
                        count_task[18] = 0;
                    }
                    if (count_task[19] != 0)
                    {
                        for (int i = 0; i < count_task[19]; i++)
                        {
                            Answers = Answers + KvadrNerav(Count, 0);
                            Count++;
                        }
                        count_task[19] = 0;
                    }
                    if (count_task[20] != 0)
                    {
                        for (int i = 0; i < count_task[20]; i++)
                        {
                            Answers = Answers + SistNerav(Count, 0);
                            Count++;
                        }
                        count_task[20] = 0;
                    }
                    if (count_task[21] != 0)
                    {
                        for (int i = 0; i < count_task[21]; i++)
                        {
                            int type_1 = rand() % 3 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + LineNerav(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + KvadrNerav(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + SistNerav(Count, 0);
                                Count++;
                                break;
                            }
                        }
                        count_task[21] = 0;
                    }
                    if (count_task[22] != 0)
                    {
                        for (int i = 0; i < count_task[22]; i++)
                        {
                            Answers = Answers + RaschetForm(Count, 0);
                            Count++;
                        }
                        count_task[22] = 0;
                    }
                    if (count_task[23] != 0)
                    {
                        for (int i = 0; i < count_task[23]; i++)
                        {
                            Answers = Answers + Graphic(0);
                            Count++;
                        }
                        count_task[23] = 0;
                    }
                    if (count_task[24] != 0)
                    {
                        for (int i = 0; i < count_task[24]; i++)
                        {
                            Answers = Answers + ArivmetProgr(0);
                            Count++;
                        }
                        count_task[24] = 0;
                    }
                    if (count_task[25] != 0)
                    {
                        for (int i = 0; i < count_task[25]; i++)
                        {
                            Answers = Answers + GeomProgr(0);
                            Count++;
                        }
                        count_task[25] = 0;
                    }
                    if (count_task[26] != 0)
                    {
                        for (int i = 0; i < count_task[26]; i++)
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + ArivmetProgr(0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + GeomProgr(0);
                                Count++;
                                break;
                            }
                        }
                        count_task[26] = 0;
                    }
                    if (count_task[27] != 0)
                    {
                        for (int i = 0; i < count_task[27]; i++)
                        {
                            Answers = Answers + TreugUgli(Count, 0);
                            Count++;
                        }
                        count_task[27] = 0;
                    }
                    if (count_task[28] != 0)
                    {
                        for (int i = 0; i < count_task[28]; i++)
                        {
                            Answers = Answers + TreugStoron(Count, 0);
                            Count++;
                        }
                        count_task[28] = 0;
                    }
                    if (count_task[29] != 0)
                    {
                        for (int i = 0; i < count_task[29]; i++)
                        {
                            Answers = Answers + TreugReshotka(Count, 0);
                            Count++;
                        }
                        count_task[29] = 0;
                    }
                    if (count_task[30] != 0)
                    {
                        for (int i = 0; i < count_task[30]; i++)
                        {
                            Answers = Answers + TreugTrigonom(Count, 0);
                            Count++;
                        }
                        count_task[30] = 0;
                    }
                    if (count_task[31] != 0)
                    {
                        for (int i = 0; i < count_task[31]; i++)
                        {
                            int type_1 = rand() % 4 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + TreugUgli(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + TreugStoron(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + TreugReshotka(Count, 0);
                                Count++;
                                break;

                            case 4:
                                Answers = Answers + TreugTrigonom(Count, 0);
                                Count++;
                                break;
                            }
                        }
                        count_task[31] = 0;
                    }
                    if (count_task[32] != 0)
                    {
                        for (int i = 0; i < count_task[32]; i++)
                        {
                            Answers = Answers + Parallelogramm(Count, 0);
                            Count++;
                        }
                        count_task[32] = 0;
                    }
                    if (count_task[33] != 0)
                    {
                        for (int i = 0; i < count_task[33]; i++)
                        {
                            Answers = Answers + Trapet(Count, 0);
                            Count++;
                        }
                        count_task[33] = 0;
                    }
                    if (count_task[34] != 0)
                    {
                        for (int i = 0; i < count_task[34]; i++)
                        {
                            Answers = Answers + MnogougReshotka(Count, 0);
                            Count++;
                        }
                        count_task[34] = 0;
                    }
                    if (count_task[35] != 0)
                    {
                        for (int i = 0; i < count_task[35]; i++)
                        {
                            int type_1 = rand() % 3 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + Parallelogramm(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Trapet(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + MnogougReshotka(Count, 0);
                                Count++;
                                break;
                            }
                        }
                        count_task[35] = 0;
                    }
                    if (count_task[36] != 0)
                    {
                        for (int i = 0; i < count_task[36]; i++)
                        {
                            Answers = Answers + Okrugn(Count, 0);
                            Count++;
                        }
                        count_task[36] = 0;
                    }
                    if (count_task[37] != 0)
                    {
                        for(int i = 1; i <= 4; i++)
                        {
                            Answers = Answers + FractionPlusMinus(Count, i);
                            Count++;
                        }
                        for(int i = 1; i <= 2; i++)
                        {
                            Answers = Answers + FractionMultDiv(Count, i);
                            Count++;
                        }
                        for(int i = 1; i <= 2; i++)
                        {
                            Answers = Answers + DFractionMultDiv(Count, i);
                            Count++;
                        }
                        Answers = Answers + DFractionPlusMinus(Count);
                        Count++;
                        count_task[37] = 0;
                    }
                    if(count_task[38] != 0)
                    {
                        for(int i = 1; i <=4; i++)
                        {
                            Answers = Answers + LetterEqu(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=4; i++)
                        {
                            Answers = Answers + Pow(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=5; i++)
                        {
                            Answers = Answers + Sqrt(Count, i);
                            Count ++;
                        }
                        count_task[38] = 0;
                    }
                    if(count_task[39] != 0)
                    {
                        for(int i = 1; i <=7; i++)
                        {
                            Answers = Answers + TeorVer(Count, i);
                            Count ++;
                        }
                        count_task[39] = 0;
                    }
                    if(count_task[40] != 0)
                    {
                        for(int i = 1; i <=7; i++)
                        {
                            Answers = Answers + NumberLine1(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=2; i++)
                        {
                            Answers = Answers + NumberLine2(Count, i);
                            Count ++;
                        }
                        count_task[40] = 0;
                    }
                    if(count_task[41] != 0)
                    {
                        for(int i = 1; i <=2; i++)
                        {
                            Answers = Answers + LineUravn(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=3; i++)
                        {
                            Answers = Answers + KvadrUravn(Count, i);
                            Count ++;
                        }
                        count_task[41] = 0;
                    }
                    if(count_task[42] != 0)
                    {
                        for(int i = 1; i <=4; i++)
                        {
                            Answers = Answers + LineNerav(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=4; i++)
                        {
                            Answers = Answers + KvadrNerav(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=2; i++)
                        {
                            Answers = Answers + SistNerav(Count, i);
                            Count ++;
                        }
                        count_task[42] = 0;
                    }
                    if(count_task[43] != 0)
                    {
                        for(int i = 1; i <=7; i++)
                        {
                            Answers = Answers + RaschetForm(Count, i);
                            Count ++;
                        }
                        count_task[43] = 0;
                    }
                    if(count_task[44] != 0)
                    {
                        for(int i = 1; i <=4; i++)
                        {
                            Answers = Answers + Graphic(i);
                            Count ++;
                        }
                        count_task[44] = 0;
                    }
                    if(count_task[45] != 0)
                    {
                        for(int i = 1; i <=4; i++)
                        {
                            Answers = Answers + ArivmetProgr(i);
                            Count ++;
                        }
                        for(int i = 1; i <=3; i++)
                        {
                            Answers = Answers + GeomProgr(i);
                            Count ++;
                        }
                        count_task[45] = 0;
                    }
                    if(count_task[46] != 0)
                    {
                        for(int i = 1; i <=6; i++)
                        {
                            Answers = Answers + TreugUgli(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=16; i++)
                        {
                            Answers = Answers + TreugStoron(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=3; i++)
                        {
                            Answers = Answers + TreugReshotka(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=18; i++)
                        {
                            Answers = Answers + TreugTrigonom(Count, i);
                            Count ++;
                        }
                        count_task[46] = 0;
                    }
                    if(count_task[47] != 0)
                    {
                        for(int i = 1; i <=15; i++)
                        {
                            Answers = Answers + Parallelogramm(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=10; i++)
                        {
                            Answers = Answers + Trapet(Count, i);
                            Count ++;
                        }
                        for(int i = 1; i <=5; i++)
                        {
                            Answers = Answers + MnogougReshotka(Count, i);
                            Count ++;
                        }
                        count_task[47] = 0;
                    }
                    if(count_task[48] != 0)
                    {
                        for(int i = 1; i <=14; i++)
                        {
                            Answers = Answers + Okrugn(Count, i);
                            Count ++;
                        }
                        count_task[48] = 0;
                    }
                    if(count_task[57] != 0)
                    {
                        for(int i = 0; i < count_task[57]; i++)
                        {
                            Answers = Answers + Second20Uravn(Count, i);
                            Count ++;
                        }
                        count_task[57] = 0;
                    }
                    if(count_task[58] != 0)
                    {
                        for(int i = 0; i < count_task[58]; i++)
                        {
                            Answers = Answers + Second20Sistem(Count, i);
                            Count ++;
                        }
                        count_task[58] = 0;
                    }
                    if(count_task[59] != 0)
                    {
                        for(int i = 0; i < count_task[59]; i++)
                        {
                            Answers = Answers + Second20Nerav(Count, i);
                            Count ++;
                        }
                        count_task[59] = 0;
                    }
                    if(count_task[60] != 0) 
                    {
                        for(int i = 0; i < count_task[60]; i++)
                        {
                            int type_1 = rand() % 3 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + Second20Uravn(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Second20Sistem(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + Second20Nerav(Count, 0);
                                Count++;
                                break;
                            }
                        }
                        count_task[60] = 0;
                    }
                    if(count_task[61] != 0)
                    {
                        for(int i = 0; i < count_task[61]; i++)
                        {
                            Answers = Answers + Second21Road(Count, i);
                            Count ++;
                        }
                        count_task[61] = 0;
                    }
                    if(count_task[62] != 0)
                    {
                        for(int i = 0; i < count_task[62]; i++)
                        {
                            Answers = Answers + Second21Per(Count, i);
                            Count ++;
                        }
                        count_task[62] = 0;
                    }
                    if(count_task[63] != 0) 
                    {
                        for(int i = 0; i < count_task[63]; i++)
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + Second21Road(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Second21Per(Count, 0);
                                Count++;
                                break;
                            }
                        }
                        count_task[63] = 0;
                    }
                    if(count_task[64] != 0)
                    {
                        for(int i = 0; i < count_task[64]; i++)
                        {
                            Answers = Answers + Second22Lin(Count, i);
                            Count ++;
                        }
                        count_task[64] = 0;
                    }
                    if(count_task[65] != 0)
                    {
                        for(int i = 0; i < count_task[65]; i++)
                        {
                            Answers = Answers + Second22Parab(Count, i);
                            Count ++;
                        }
                        count_task[65] = 0;
                    }
                    if(count_task[66] != 0)
                    {
                        for(int i = 0; i < count_task[66]; i++)
                        {
                            Answers = Answers + Second22Drob(Count, i);
                            Count ++;
                        }
                        count_task[66] = 0;
                    }
                    if(count_task[67] != 0)
                    {
                        for(int i = 0; i < count_task[67]; i++)
                        {
                            int type_1 = rand() % 3 + 1;
                            switch (type_1)
                            {
                                case 1:
                                    Answers = Answers + Second22Lin(Count, 0);
                                    Count++;
                                    break;

                                case 2:
                                    Answers = Answers + Second22Parab(Count, 0);
                                    Count++;
                                    break;

                                case 3:
                                    Answers = Answers + Second22Drob(Count, 0);
                                    Count++;
                                    break;
                            }
                        }
                        count_task[67] = 0;
                    }
                    cout << endl << "}" << endl << "\\end{enumerate} \n" << Answers << endl << "\\end{enumerate}" << endl << endl;
                    Answers = "\\newpage \n {\\centering \\subsubsection*{Ответы}} \n \\begin{enumerate} \n";
                    cout << "0. Назад" << endl;
                    cout << "Ваш выбор: ";
                    cin >> choice;
                    choice = -1;
                    break;
                }
            } while (choice != 0);
            choice = -1;
            break;
        case 2:
            do {
                cout << "\033[2J\033[1;1H";
                int Count = 0;
                
                for (int i = 0; i < 1; i++)             // 6
                        {
                            int z = rand() % 4 + 1;
                            switch (z)
                            {
                            case 1:
                                Answers = Answers + FractionPlusMinus(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + FractionMultDiv(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + DFractionPlusMinus(Count);
                                Count++;
                                break;

                            case 4:
                                Answers = Answers + DFractionMultDiv(Count, 0);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 14
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + NumberLine1(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + NumberLine2(Count, 0);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 10
                        {
                            int type_1 = rand() % 3 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + LetterEqu(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Pow(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + Sqrt(Count, 0);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 17
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + LineUravn(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + KvadrUravn(Count, 0);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 11
                        {
                            Answers = Answers + TeorVer(Count, 0);
                            Count++;
                        }

                for (int i = 0; i < 1; i++)             // 23
                        {
                            Answers = Answers + Graphic(0);
                            Count++;
                        }

                for (int i = 0; i < 1; i++)             // 22
                        {
                            Answers = Answers + RaschetForm(Count, 0);
                            Count++;
                        }

                for (int i = 0; i < 1; i++)             // 21
                        {
                            int type_1 = rand() % 3 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + LineNerav(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + KvadrNerav(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + SistNerav(Count, 0);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 26
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + ArivmetProgr(0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + GeomProgr(0);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 27 28 29
                        {
                            int type_1 = rand() % 3 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + TreugUgli(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + TreugStoron(Count, 0);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + TreugTrigonom(Count, 0);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 32  33
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + Parallelogramm(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Trapet(Count, 0);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 36
                        {
                            Answers = Answers + Okrugn(Count, 0);
                            Count++;
                        }

                for (int i = 0; i < 1; i++)             // 29 34
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + TreugReshotka(Count, 0);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + MnogougReshotka(Count, 0);
                                Count++;
                                break;
                            }
                        }

                cout << endl << "}" << endl << "\\end{enumerate} \n" << Answers << endl << "\\end{enumerate}" << endl << endl;
                Answers = "\\newpage \n {\\centering \\subsubsection*{Ответы}} \n \\begin{enumerate} \n";
                cout << "0. Назад" << endl;
                cout << "Ваш выбор: ";
                cin >> choice;
                choice = -1;
                break;
            } while (choice != 0);
            choice = -1;
            break;
        }
    } while (choice != 0);
}
