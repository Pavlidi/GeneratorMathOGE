#include <iostream>                                             // Для операторов cin и cout
#include <ctime>                                                // Для функции srand() которая помогает делать реальный рандомайзер
#include <cmath>                                                // Для математических операторов
#include <string>
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

string FractionPlusMinus(int number)                            // Генерирует примеры на сложение и вычитание обычных дробей
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
        type = (rand() % 4) + 1;
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
    Answer = "  \\item " + to_string(answer) + " \n";
    return Answer;
}

string FractionMultDiv(int number)
{
    string Answer;
    double a[4];
    double answer, check;
    int nod1, nod2;                                                         // Общие делители для сокращения дробей
    int type;                                                               // Тип выражения
    do {                                                                    // Генерирует дроби
        for (int n = 0; n < 4; n++)
            a[n] = (rand() % 50) + 1;
        type = (rand() % 2) + 1;
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
    Answer = "  \\item " + to_string(answer) + " \n";
    return Answer;
}

string DFractionMultDiv(int number)                               // Генерирует примеры на умножение и деление десятичных дробей
{
    int type;
    double number1, number2, answer;
    string Answer;
    type = (rand() % 2) + 1;
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
        Answer = "  \\item " + to_string(answer) + " \n";
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
        Answer = "  \\item " + to_string(answer) + " \n";
        break;
    }
    return Answer;
}

string DFractionPlusMinus(int number)                             // Генерирует примеры на сложение и вычитание десятичных дробей
{
    double a[2];
    string Answer;
    for (int n = 0; n < 2; n++)
        a[n] = static_cast<double>((rand() % 999 + 1)) / 100;
    cout << "\\item Найдите значение выражения: " << endl;
    cout << "\\[" << endl;
    cout << "   " << SIGN(rand(), 1) << a[0] << SIGN(rand(), 2) << a[1] << endl;
    cout << "\\]" << endl;
    Answer = "  \\item Десятичные дроби \n";
    return Answer;

}

string LetterEqu(int number)
{
    int type = (rand() % 4) + 1;
    int type_1 = (rand() % 4) + 1;
    double a = rand() % 27 + 2;
    double b = rand() % 27 + 2;
    double c = rand() % 27 + 2;
    double answer;
    string Answer;
    switch (type)
    {
    case 1:	// Буквенные 1
        switch (type_1)
        {
        case 1:
            cout << "\\item Найдите значение выражения: \\[\n	(\\sqrt{" << a << "}+" << b <<
                ")^2 - " << 2 * b << "\\sqrt{" << a << "} \n \\]" << endl;
            answer = a + b * b;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 2:
            cout << "\\item Найдите значение выражения: \\[\n	(" << a << "+\\sqrt{" << b <<
                "})^2 - " << 2 * a << "\\sqrt{" << b << "} \n \\]" << endl;
            answer = a * a + b;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 3:
            cout << "\\item Найдите значение выражения: \\[\n	" << 2 * b << "\\sqrt{" << a <<
                "} + (\\sqrt{" << a << "} - " << b << ")^2 \n \\]" << endl;
            answer = a + b * b;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 4:
            cout << "\\item Найдите значение выражения: \\[\n	" << 2 * a << "\\sqrt{" << b <<
                "} - (" << a << " + \\sqrt{" << b << "})^2 \n \\]" << endl;
            answer = (a * a) * (-1) - b;
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 2:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{" << c * c << "a^2 + " << 2 * c << "ab + b^2}$ при a = " << a << " и b = " << b << ".\\\\" << endl;
            answer = fabs(a * c + b);
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 3:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{a^2 - " << 2 * c << "ab + " << c * c << "b^2}$ при a = " << a << " и b = " << b << ".\\\\" << endl;
            answer = fabs(a - c * b);
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 4:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{" << c * c << "a^2 - " << 2 * c << "ab + b^2}$ при a = " << a << " и b = " << b << ".\\\\" << endl;
            answer = fabs(a * c - b);
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 2:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(\\sqrt{" << d << "} + \\sqrt{" << d * a * a << "}\\right)\\sqrt{" << d << "}$.\\\\" << endl;
            answer = a * d + d;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 3:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{" << d << "}\\left(\\sqrt{" << d << "} - \\sqrt{" << a * a * d << "}\\right)$.\\\\" << endl;
            answer = d - a * d;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 4:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\sqrt{" << d << "}\\left(\\sqrt{" << d * a * a << "} + \\sqrt{" << d << "}\\right)$.\\\\" << endl;
            answer = d + a * d;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 2:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(" << a << "+ \\sqrt{" << e << "}\\right)\\left(" << a << "-\\sqrt{" << e << "}\\right)$.\\\\" << endl;
            answer = a * a - e;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 3:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(\\sqrt{" << e << "}-\\sqrt{" << f << "}\\right)\\left(\\sqrt{" << e << "}+\\sqrt{" << f << "}\\right)$.\\\\" << endl;
            answer = e - f;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;

        case 4:
            cout << "\\item Найдите значение выражения: $ " <<
                "\\left(\\sqrt{" << e << "}+\\sqrt{" << f << "}\\right)\\left(\\sqrt{" << e << "}-\\sqrt{" << f << "}\\right)$.\\\\" << endl;
            answer = e - f;
            //cout << "\\\\" << answer << "\\\\" << endl;
            Answer = "  \\item " + to_string(answer) + " \n";
            break;
        }
        break;

    }
    return Answer;

}

string Pow(int number)
{
    int type = rand() % 4 + 1;
    int type_1;
    double a, b;
    double pok[4];
    double answer;
    double check;
    string Answer;
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
            Answer = "  \\item " + to_string(answer) + " \n";
        }
        else
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\frac{a^{" << pok[0] << "}\\cdot a^{" << pok[1] << "}}{" << "a^{" << pok[2] << "}}$, при a = " << a << ". \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow(a, pok[0]) * pow(a, pok[1]) / pow(a, pok[2]);
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
        }
        else
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                "a^{" << pok[0] << "}\\cdot a^{" << pok[1] << "}:" << "a^{" << pok[2] << "}$, при a = " << a << ". \\\\" << endl;
            //cout << answer << "\\\\" << endl;
            answer = pow(a, pok[0]) * pow(a, pok[1]) / pow(a, pok[2]);
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
        }
        break;
    }
    return Answer;
}

string Sqrt(int number)
{
    int type = rand() % 5 + 1;
    int type_1;
    double a, b, c, d, e;
    double answer;
    string Answer;
    double check;

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
        Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
        }
        else
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                "\\sqrt{" << a << "}\\cdot\\sqrt{" << b << "\\cdot" << c << "}$." << endl;
            //cout << answer << "\\\\" << endl;
            answer = sqrt(a) * sqrt(b) * sqrt(c);
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
        }
        else
        {
            cout << "\\item     Найдите значение выражения: $ " <<
                d << "\\sqrt{" << a << "}\\cdot\\sqrt{" << b << "}\\cdot" << e << "\\sqrt{" << c << "}$." << endl;
            //cout << "\\\\" << answer << "\\\\" << endl;
            answer = sqrt(a) * sqrt(b) * sqrt(c) * d * e;
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
            }
            else
            {
                cout << "\\item     Найдите значение выражения: $ " <<
                    "\\sqrt{a^{" << d << "}\\cdot (-a)^{" << e << "}}$ при a = " << a << "." << endl;
                //cout << "\\\\" << answer << "\\\\" << endl;
                answer = sqrt(pow(a, d) * pow(a, e));
                Answer = "  \\item " + to_string(answer) + " \n";
            }
            break;

        }
        break;
    }
    return Answer;
}

string TeorVer(int number)
{
    int type = rand() % 7 + 1;
    double a, b, c, d, e, f;
    double answer;
    string Answer;
    double check;
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
        Answer = "  \\item " + to_string(answer) + " \n";
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
        Answer = "  \\item " + to_string(answer) + " \n";
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
        Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
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
            Answer = "  \\item " + to_string(answer) + " \n";
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
        Answer = "  \\item " + to_string(answer) + " \n";
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
        Answer = "  \\item " + to_string(answer) + " \n";
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
        Answer = "  \\item " + to_string(answer) + " \n";
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

string NumberLine2(int number)
{
    int type = rand()%2+1;
			double a, p, q, r;
			string min, mid, max;
			FarString True[3];
			FarString False[4];
			string Out[4];
			string Answer;
			double answer, check;
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
					cout << "\\begin{enumerate}" << endl
						<< "	\\item " << Out[0] << endl
						<< "	\\item " << Out[1] << endl
						<< "	\\item " << Out[2] << endl
						<< "	\\item " << Out[3] << endl
						<< "\\end{enumerate}" << endl << endl;
					//cout << answer << endl;
					Answer = "  \\item " + to_string(answer) + " \n";
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
					cout << "\\begin{enumerate}" << endl
						<< "	\\item " << Out[0] << endl
						<< "	\\item " << Out[1] << endl
						<< "	\\item " << Out[2] << endl
						<< "	\\item " << Out[3] << endl
						<< "\\end{enumerate}" << endl << endl;
					//cout << answer << endl;
					Answer = "  \\item " + to_string(answer) + " \n";
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
					cout << "\\begin{enumerate}" << endl
						<< "	\\item " << Out[0] << endl
						<< "	\\item " << Out[1] << endl
						<< "	\\item " << Out[2] << endl
						<< "	\\item " << Out[3] << endl
						<< "\\end{enumerate}" << endl << endl;
					//cout << answer << endl;
					Answer = "  \\item " + to_string(answer) + " \n";
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
					cout << "\\begin{enumerate}" << endl
						<< "	\\item " << Out[0] << endl
						<< "	\\item " << Out[1] << endl
						<< "	\\item " << Out[2] << endl
						<< "	\\item " << Out[3] << endl
						<< "\\end{enumerate}" << endl << endl;
					//cout << answer << endl;
					Answer = "  \\item " + to_string(answer) + " \n";
				}

			}
			return Answer;
}

string NumberLine1(int number)
{
    int answer;
			int check = 0;
			int type = rand()%7 + 1;
			FarString True;
			FarString False[3];
			FarStringTF TrueFalse[4];
			string Out[4];
			string Answer;
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
				cout << "\\begin{enumerate}" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << answer << endl;
				Answer = "  \\item " + to_string(answer) + " \n";
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
				cout << "\\begin{enumerate}" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << answer << endl;
				Answer = "  \\item " + to_string(answer) + " \n";
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
				cout << "\\begin{enumerate}" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << answer << endl;
				Answer = "  \\item " + to_string(answer) + " \n";
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
				cout << "\\begin{enumerate}" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << "Ответ: " << answer << endl;
				Answer = "  \\item " + to_string(answer) + " \n";

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
				cout << "\\begin{enumerate}" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << "Ответ: " << answer << endl;
				Answer = "  \\item " + to_string(answer) + " \n";

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
				cout << "\\begin{enumerate}" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << "Ответ: " << answer << endl;
				Answer = "  \\item " + to_string(answer) + " \n";
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
				cout << "\\begin{enumerate}" << endl
					<< "	\\item " << Out[0] << endl
					<< "	\\item " << Out[1] << endl
					<< "	\\item " << Out[2] << endl
					<< "	\\item " << Out[3] << endl
					<< "\\end{enumerate}" << endl << endl;
				//cout << "Ответ: " << answer << endl;
				Answer = "  \\item " + to_string(answer) + " \n";

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

string LineUravn(int number)
{
    int type = rand()%2+1;
            double x;
            double a[4];
            int check = 0;
            double answer;
            double ost;
            string Answer;
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

                    cout << "\\item Найдите корень уравнения $" << SignUr(1, a[0]) << fabs(a[0]) << "(x " << SignUr(2, a[1]) << fabs(a[1]) << ")=" << SignUr(1, a[2]) << fabs(a[2]) << "$." << endl;
                    //cout << "\\\\ Ответ:" << answer << endl;
                    Answer = "  \\item " + to_string(answer) + " \n";
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

                    cout << "\\item Найдите корень уравнения $" << SignUr(1,a[0]) << fabs(a[0]) << SignUr(2, a[1]) << fabs(a[1]) << "x = " << SignUr(1,a[2]) << fabs(a[2]) << "x" << SignUr(2, a[3]) << fabs(a[3]) << "$." << endl;
                    //cout << "\\\\ Ответ:" << answer << endl;
                    Answer = "  \\item " + to_string(answer) + " \n";
                    break;

            }
            return Answer;
}

string KvadrUravn(int number)
{
    int type = rand()%3 + 1;
            int type1;
            double x[2];
            double a[3];
            int check = 0;
            double answer;
            double ost;
            double change;
            string Answer;
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
                    cout << "\\item Решите уравнение $" << SignUr(1, a[0]) << fabs(a[0]) << "x^2 " << SignUr(2, a[1]) << fabs(a[1]) << " = 0$. \\\\" << endl;
                    if(type1 == 0)
                        cout << "Если уравнение имеет более одного корня, в ответ запишите больший из корней." << endl;
                    else
                        cout << "Если уравнение имеет более одного корня, в ответ запишите меньший из корней." << endl;
                    //cout << "\\\\Ответ: " << answer << endl;
                    Answer = "  \\item " + to_string(answer) + " \n";
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
                    cout << "\\item Решите уравнение $" << SignUr(1, a[0]) << fabs(a[0]) << "x^2 = " << SignUr(1, a[1]) << fabs(a[1]) << "x$. \\\\" << endl;
                    if(type1 == 0)
                        cout << "Если уравнение имеет более одного корня, в ответ запишите меньший из корней." << endl;
                    else
                        cout << "Если уравнение имеет более одного корня, в ответ запишите больший из корней." << endl;
                    //cout << "\\\\Ответ: " << answer << endl;
                    Answer = "  \\item " + to_string(answer) + " \n";
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
                    cout << "\\item Решите уравнение $" << SignUr(1,a[0]) << fabs(a[0]) << "x^2" << SignUr(2,a[1]) << fabs(a[1]) << "x" << SignUr(2,a[2]) << fabs(a[2]) << "=0$. \\\\" << endl;
                    if(type1 == 0)
                        cout << "Если уравнение имеет более одного корня, в ответ запишите меньший из корней." << endl;
                    else
                        cout << "Если уравнение имеет более одного корня, в ответ запишите больший из корней." << endl;
                    //cout << "\\\\Ответ: " << answer << endl;
                    Answer = "  \\item " + to_string(answer) + " \n";
                    break;

            }
        return Answer;
}

string LineNerav(int number)
{
    double x[2];
            double a[4];
            int type = rand()%4+1;
            int check = 0;
            int answer;
            double ost;
            string Answer;
            FarStringTF TrueFalse[4];
            string Out[4];
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
                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;
            }
            return Answer;
}

string KvadrNerav(int number)
{
    double x1[2];
            double x2[2];
            double a1[2];
            double a2[2];
            int type = rand()%4 + 1;
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
                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";

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
                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";

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
                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";

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

                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";

                break;


            }
            return Answer;
}

string SistNerav(int number)
{
    double x[2];
            double a1[3];
            double a2[3];
            int type = rand()%2+1;
            int type1;              
            int check = 0;
            int strog;              // Строгое или нестрогое неравенство
            int answer;
            double ost;
            double change;
            string Answer;
            FarStringTF TrueFalse[4];
            string Out[4];
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
                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\begin{enumerate}" << endl
                    << "	\\item " << Out[0] << endl
                    << "	\\item " << Out[1] << endl
                    << "	\\item " << Out[2] << endl
                    << "	\\item " << Out[3] << endl
                    << "\\end{enumerate}" << endl << endl;
                //cout << "Ответ: " << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            }
            return Answer;
}

string RaschetForm(int number)
{
    double P, I, R, tc, tf, n, Price1, Price2, a, w, sin1, sin2, S, d, t1, t2;
            int type = rand()%7+1;
            string Answer;
            int check = 0;
            double answer;
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
                Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 3:
                n = rand() % 30 + 9;
                Price1 = 1000 * (rand() % 8 + 2);
                Price2 = 100 * (rand() % 40 + 10);
                answer = Price1 + (Price2 * n);
                cout << "\\item В фирме <<Родник>> стоимость (в рублях) колодца из железобетонных колец рассчитывается по формуле $C=" << Price1 << "+" << Price2 << "n$, где $n$ -- число колец, установленных в колодце. Пользуясь этой формулой, рассчитайте стоимость колодца из " << n << " колец. Ответ дайте в рублях." << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
                break;
            }
            return Answer;    
}

string Graphic()
{
    // Код начало
            double k[4];
            double b[4];
            double a[4];
            double c[4];
            double xver[4];
            double yver[4];
            int type = rand()%4+1;
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
                    GraphVar[i].GraphOut = "     \\pgfplotsset{compat=1.18, \n       width=6cm %ширина графика% \n} \n       \\begin{axis}[xmin=-3.5, xmax=3.5, \n       ymin=-3.5, ymax=3.5, \n         axis lines=middle, \n       xtick={-3, -2, -1, 0, 1, 2, 3}, %задает иксы которые будут отмечены \n      xticklabels={$$, $$, $$, $$, $1$, $$, $$}, %то что нужно будет отметить по х \n         xticklabel style={anchor=north}, %где будет отмечено значение х \n      ytick={-3, -2, -1, 0, 1, 2, 3}, \n      yticklabels={$$, $$, $$, $$, $1$, $$, $$}, \n       yticklabel style={anchor=east}, \n      xmajorgrids=true, %полоски от значений на оси \n        ymajorgrids=true, \n        grid style=dashed, %стиль дополнительных полосок \n         xlabel=$x$, ylabel=$y$,]  \n";
                    if((k[i]==1)||(k[i]==-1))
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, k[i]) + "1*x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "}; \n       \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";
                    else
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, k[i]) + to_string(static_cast<int>(fabs(k[i]))) + "* x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "}; \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";
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
                cout << "\\item На рисунках изображены графики функций вида $y=kx+b$. Установите соответствие между знаками коэффициентов $k$ и $b$ и графиками функций.\\\\" << endl << "\\textbf{Графики:}";
                cout << "\\begin{table}[h!]" << endl
                    << "    \\centering" << endl
                    << "   \\begin{tabular}{m{4.5cm} m{4.5cm} m{4.5cm}}" << endl;
                    for(int i = 1; i<=3; i++)
                    {
                        cout << "\\textbf{" << i << ")}" << endl << "  \\begin{tikzpicture} " << endl;
                        for(int m = 0; m<4; m++)
                        {
                            if(GraphVar[m].PorQ == i)
                            {
                                cout << GraphVar[m].GraphOut;
                            }
                        }
                        cout << "\\end{axis} " << endl << "\\end{tikzpicture} " << endl;
                        if(i!=3)
                            cout << "&" << endl;
                    }
                cout << "   \\end{tabular}" << endl << "\\end{table}" << endl << endl;
                cout << "\\textbf{Варианты ответа:}" << endl;
                cout << "\\begin{enumerate}" << endl;
                for(int i = 1; i<=3; i++)
                {
                    for(int m=0; m<4; m++)
                    {
                        if(GraphVar[m].PorO==i)
                            cout << "\\item     " << GraphVar[m].VarAnswer << endl;
                    }
                }
                cout << "\\end{enumerate}" << endl;
                Answer = "  \\item " + to_string(static_cast<int>(answer[0])) + to_string(static_cast<int>(answer[1])) + to_string(static_cast<int>(answer[2])) + "\n";
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
                    GraphVar[i].GraphOut = "     \\pgfplotsset{compat=1.18, \n       width=6cm %ширина графика% \n} \n       \\begin{axis}[xmin=-3.5, xmax=3.5, \n       ymin=-3.5, ymax=3.5, \n         axis lines=middle, \n       xtick={-3, -2, -1, 0, 1, 2, 3}, %задает иксы которые будут отмечены \n      xticklabels={$$, $$, $$, $$, $1$, $$, $$}, %то что нужно будет отметить по х \n         xticklabel style={anchor=north}, %где будет отмечено значение х \n      ytick={-3, -2, -1, 0, 1, 2, 3}, \n      yticklabels={$$, $$, $$, $$, $1$, $$, $$}, \n       yticklabel style={anchor=east}, \n      xmajorgrids=true, %полоски от значений на оси \n        ymajorgrids=true, \n        grid style=dashed, %стиль дополнительных полосок \n         xlabel=$x$, ylabel=$y$,]  \n";
                    if((k[i]==1)||(k[i]==-1))
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, k[i]) + "1*x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "}; \n       \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";
                    else
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, k[i]) + to_string(static_cast<int>(fabs(k[i]))) + "* x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "}; \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";
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
                cout << "\\item Установите соответствие между графиками функций и формулами, которые их задают.\\\\" << endl << "\\textbf{Графики:}";
                cout << "\\begin{table}[h!]" << endl
                    << "    \\centering" << endl
                    << "   \\begin{tabular}{m{4.5cm} m{4.5cm} m{4.5cm}}" << endl;
                    for(int i = 1; i<=3; i++)
                    {
                        cout << "\\textbf{" << i << ")}" << endl << "  \\begin{tikzpicture} " << endl;
                        for(int m = 0; m<4; m++)
                        {
                            if(GraphVar[m].PorQ == i)
                            {
                                cout << GraphVar[m].GraphOut;
                            }
                        }
                        cout << "\\end{axis} " << endl << "\\end{tikzpicture} " << endl;
                        if(i!=3)
                            cout << "&" << endl;
                    }
                cout << "   \\end{tabular}" << endl << "\\end{table}" << endl << endl;
                cout << "\\textbf{Варианты ответа:}" << endl;
                cout << "\\begin{enumerate}" << endl;
                for(int i = 1; i<=3; i++)
                {
                    for(int m=0; m<4; m++)
                    {
                        if(GraphVar[m].PorO==i)
                            cout << "\\item     " << GraphVar[m].VarAnswer << endl;
                    }
                }
                cout << "\\end{enumerate}" << endl;
                Answer = "  \\item " + to_string(static_cast<int>(answer[0])) + to_string(static_cast<int>(answer[1])) + to_string(static_cast<int>(answer[2])) + "\n";
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
                    GraphVar[i].GraphOut = "     \\pgfplotsset{compat=1.18, \n       width=6cm %ширина графика% \n} \n       \\begin{axis}[xmin=-3.5, xmax=3.5, \n       ymin=-3.5, ymax=3.5, \n         axis lines=middle, \n       xtick={-3, -2, -1, 0, 1, 2, 3}, %задает иксы которые будут отмечены \n      xticklabels={$$, $$, $$, $$, $1$, $$, $$}, %то что нужно будет отметить по х \n         xticklabel style={anchor=north}, %где будет отмечено значение х \n      ytick={-3, -2, -1, 0, 1, 2, 3}, \n      yticklabels={$$, $$, $$, $$, $1$, $$, $$}, \n       yticklabel style={anchor=east}, \n      xmajorgrids=true, %полоски от значений на оси \n        ymajorgrids=true, \n        grid style=dashed, %стиль дополнительных полосок \n         xlabel=$x$, ylabel=$y$,]  \n";
                    if((a[i]==1)||(a[i]==-1))
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, a[i]) + "1*x*x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "*x" + SignUr(2,c[i]) + to_string(static_cast<int>(fabs(c[i]))) + "}; \n       \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";
                    else
                        GraphVar[i].GraphOut = GraphVar[i].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, a[i]) + to_string(static_cast<int>(fabs(a[i]))) + "*x*x" + SignUr(2,b[i]) + to_string(static_cast<int>(fabs(b[i]))) + "*x" + SignUr(2,c[i]) + to_string(static_cast<int>(fabs(c[i]))) + "}; \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";
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
                cout << "\\item На рисунках изображены графики функций вида $y=ax^2+bx+c$. Установите соответствие между знаками коэффициентов $a$ и $c$ и графиками функций.\\\\" << endl << "\\textbf{Графики:}";
                cout << "\\begin{table}[h!]" << endl
                    << "    \\centering" << endl
                    << "   \\begin{tabular}{m{4.5cm} m{4.5cm} m{4.5cm}}" << endl;
                    for(int i = 1; i<=3; i++)
                    {
                        cout << "\\textbf{" << i << ")}" << endl << "  \\begin{tikzpicture} " << endl;
                        for(int m = 0; m<4; m++)
                        {
                            if(GraphVar[m].PorQ == i)
                            {
                                cout << GraphVar[m].GraphOut;
                            }
                        }
                        cout << "\\end{axis} " << endl << "\\end{tikzpicture} " << endl;
                        if(i!=3)
                            cout << "&" << endl;
                    }
                cout << "   \\end{tabular}" << endl << "\\end{table}" << endl << endl;
                cout << "\\textbf{Варианты ответа:}" << endl;
                cout << "\\begin{enumerate}" << endl;
                for(int i = 1; i<=3; i++)
                {
                    for(int m=0; m<4; m++)
                    {
                        if(GraphVar[m].PorO==i)
                            cout << "\\item     " << GraphVar[m].VarAnswer << endl;
                    }
                }
                cout << "\\end{enumerate}" << endl;
                Answer = "  \\item " + to_string(static_cast<int>(answer[0])) + to_string(static_cast<int>(answer[1])) + to_string(static_cast<int>(answer[2])) + "\n";
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

                GraphVar[0].GraphOut = "     \\pgfplotsset{compat=1.18, \n       width=6cm %ширина графика% \n} \n       \\begin{axis}[xmin=-3.5, xmax=3.5, \n       ymin=-3.5, ymax=3.5, \n         axis lines=middle, \n       xtick={-3, -2, -1, 0, 1, 2, 3}, %задает иксы которые будут отмечены \n      xticklabels={$$, $$, $$, $$, $1$, $$, $$}, %то что нужно будет отметить по х \n         xticklabel style={anchor=north}, %где будет отмечено значение х \n      ytick={-3, -2, -1, 0, 1, 2, 3}, \n      yticklabels={$$, $$, $$, $$, $1$, $$, $$}, \n       yticklabel style={anchor=east}, \n      xmajorgrids=true, %полоски от значений на оси \n        ymajorgrids=true, \n        grid style=dashed, %стиль дополнительных полосок \n         xlabel=$x$, ylabel=$y$,]  \n";
                    if((k[0]==1)||(k[0]==-1))
                        GraphVar[0].GraphOut = GraphVar[0].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, k[0]) + "1*x" + SignUr(2,b[0]) + to_string(static_cast<int>(fabs(b[0]))) + "}; \n       \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";
                    else
                        GraphVar[0].GraphOut = GraphVar[0].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, k[0]) + to_string(static_cast<int>(fabs(k[0]))) + "* x" + SignUr(2,b[0]) + to_string(static_cast<int>(fabs(b[0]))) + "}; \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";


                GraphVar[1].GraphOut = "     \\pgfplotsset{compat=1.18, \n       width=6cm %ширина графика% \n} \n       \\begin{axis}[xmin=-3.5, xmax=3.5, \n       ymin=-3.5, ymax=3.5, \n         axis lines=middle, \n       xtick={-3, -2, -1, 0, 1, 2, 3}, %задает иксы которые будут отмечены \n      xticklabels={$$, $$, $$, $$, $1$, $$, $$}, %то что нужно будет отметить по х \n         xticklabel style={anchor=north}, %где будет отмечено значение х \n      ytick={-3, -2, -1, 0, 1, 2, 3}, \n      yticklabels={$$, $$, $$, $$, $1$, $$, $$}, \n       yticklabel style={anchor=east}, \n      xmajorgrids=true, %полоски от значений на оси \n        ymajorgrids=true, \n        grid style=dashed, %стиль дополнительных полосок \n         xlabel=$x$, ylabel=$y$,]  \n";
                if((a[0]==1)||(a[0]==-1))
                        GraphVar[1].GraphOut = GraphVar[1].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, a[0]) + "1*x*x" + SignUr(2,b[1]) + to_string(static_cast<int>(fabs(b[1]))) + "*x" + SignUr(2,c[0]) + to_string(static_cast<int>(fabs(c[0]))) + "}; \n       \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";
                else
                    GraphVar[1].GraphOut = GraphVar[1].GraphOut + "     \\addplot[domain=-3.5:3.5,black, thick, samples=1000]{" + SignUr(1, a[0]) + to_string(static_cast<int>(fabs(a[0]))) + "*x*x" + SignUr(2,b[1]) + to_string(static_cast<int>(fabs(b[1]))) + "*x" + SignUr(2,c[0]) + to_string(static_cast<int>(fabs(c[0]))) + "}; \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";
                
                GraphVar[2].GraphOut = "     \\pgfplotsset{compat=1.18, \n       width=6cm %ширина графика% \n} \n       \\begin{axis}[xmin=-3.5, xmax=3.5, \n       ymin=-3.5, ymax=3.5, \n         axis lines=middle, \n       xtick={-3, -2, -1, 0, 1, 2, 3}, %задает иксы которые будут отмечены \n      xticklabels={$$, $$, $$, $$, $1$, $$, $$}, %то что нужно будет отметить по х \n         xticklabel style={anchor=north}, %где будет отмечено значение х \n      ytick={-3, -2, -1, 0, 1, 2, 3}, \n      yticklabels={$$, $$, $$, $$, $1$, $$, $$}, \n       yticklabel style={anchor=east}, \n      xmajorgrids=true, %полоски от значений на оси \n        ymajorgrids=true, \n        grid style=dashed, %стиль дополнительных полосок \n         xlabel=$x$, ylabel=$y$,]  \n";
                GraphVar[2].GraphOut = GraphVar[2].GraphOut + "     \\addplot[domain=-3.5:-0.1,black, thick, samples=1000]{" + to_string(static_cast<int>(k[1])) +  "/x}; \n        \\addplot[domain=0.1:3.5,black, thick, samples=1000]{ " + to_string(static_cast<int>(k[1])) + "/x};\n        \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";

                GraphVar[3].GraphOut = "     \\pgfplotsset{compat=1.18, \n       width=6cm %ширина графика% \n} \n       \\begin{axis}[xmin=-3.5, xmax=3.5, \n       ymin=-3.5, ymax=3.5, \n         axis lines=middle, \n       xtick={-3, -2, -1, 0, 1, 2, 3}, %задает иксы которые будут отмечены \n      xticklabels={$$, $$, $$, $$, $1$, $$, $$}, %то что нужно будет отметить по х \n         xticklabel style={anchor=north}, %где будет отмечено значение х \n      ytick={-3, -2, -1, 0, 1, 2, 3}, \n      yticklabels={$$, $$, $$, $$, $1$, $$, $$}, \n       yticklabel style={anchor=east}, \n      xmajorgrids=true, %полоски от значений на оси \n        ymajorgrids=true, \n        grid style=dashed, %стиль дополнительных полосок \n         xlabel=$x$, ylabel=$y$,]  \n";
                GraphVar[3].GraphOut = GraphVar[3].GraphOut + "     \\addplot[domain=0:3.5,black, thick, samples=1000]{" + SignUr(1, k[2]) + to_string(static_cast<int>(fabs(k[2]))) + "*sqrt(x)" + "}; \n       \\coordinate[label=below left:$0$] (O) at (0,0); \n         \\coordinate[label=below left:$0$] (O) at (0,0); \n";

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
                cout << "\\item Установите соответствие между функциями и их графиками.\\\\" << endl << "\\textbf{Графики:}";
                cout << "\\begin{table}[h!]" << endl
                    << "    \\centering" << endl
                    << "   \\begin{tabular}{m{4.5cm} m{4.5cm} m{4.5cm}}" << endl;
                    for(int i = 1; i<=3; i++)
                    {
                        cout << "\\textbf{" << i << ")}" << endl << "  \\begin{tikzpicture} " << endl;
                        for(int m = 0; m<4; m++)
                        {
                            if(GraphVar[m].PorQ == i)
                            {
                                cout << GraphVar[m].GraphOut;
                            }
                        }
                        cout << "\\end{axis} " << endl << "\\end{tikzpicture} " << endl;
                        if(i!=3)
                            cout << "&" << endl;
                    }
                cout << "   \\end{tabular}" << endl << "\\end{table}" << endl << endl;
                cout << "\\textbf{Варианты ответа:}" << endl;
                cout << "\\begin{enumerate}" << endl;
                for(int i = 1; i<=3; i++)
                {
                    for(int m=0; m<4; m++)
                    {
                        if(GraphVar[m].PorO==i)
                            cout << "\\item     " << GraphVar[m].VarAnswer << endl;
                    }
                }
                cout << "\\end{enumerate}" << endl;
                Answer = "  \\item " + to_string(static_cast<int>(answer[0])) + to_string(static_cast<int>(answer[1])) + to_string(static_cast<int>(answer[2])) + "\n";
                //cout << Answer << endl;
                break;

            }
            return Answer;
}

string ArivmetProgr()
{
    double t[3];
            double delta;
            double a0, an;
            double answer;
            int type = rand()%4 + 1;
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
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 2:
                t[0] = rand() % 13 + 3;
                delta = 10;
                a0 = rand() % 6 + 4;
                an = a0 + delta * (t[0] - 1);
                answer = t[0] * (a0 + an) / 2;
                cout << "\\item Камень бросают в глубокое ущелье. При этом в первую секунду он пролетает " << a0 << " метров, а в каждую следующую секунду на 10 метров больше, чем в предыдущую, до тех пор, пока не достигнет дна ущелья. Сколько метров пролетит камень за первые " << t[0] << " секунд?" << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
                break;
            }
            return Answer;
}

string GeomProgr()
{
    double t[2];                   // t0 - период, tn - время когда  ищем
            double a0, an, A;
            double delta;
            int type = rand()%3+1;
            double answer;
            int check = 0;
            string Answer;
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
                Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
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
                Answer = "  \\item " + to_string(answer) + " \n";
                break;


            }
            return Answer;
}

string TreugUgli(int i)
{
    double Agrad, Bgrad, Arad, Brad;
            double r1, r2;
            int type = rand()%6+1;
            string Answer;
            double answer;
            int check = 0;
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "       В треугольник $ABC$ угол $C$ равен $" << Bgrad << "^{\\circ}$. Найдите внешний угол при вершине $C$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << Agrad << ":" << r2 << ");" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << r1 << ");" << endl
                    << "            \\coordinate (O) at (0:{" << r2 << "*cos(" << Agrad << ")});" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (O);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольник $ABC$ известно, что $AB=BC$, $\\angle ABC=" << (180-2*Agrad) << "^{\\circ}$. Найдите угол $BCA$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (-" << Agrad << ":" << r1 << ");" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (-" << (180-Agrad) << ":" << r1 << ");" << endl
                    << "            \\tkzMarkSegment[mark=|](B,A);" << endl
                    << "            \\tkzMarkSegment[mark=|](B,C);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ известно, что $\\angle BAC=" << Agrad << "^{\\circ}$, $AD$ -- биссектриса. Найдите угол $BAD$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (0,0);" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (3.5,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << Agrad << ":" << r1 << ");" << endl
                    << "            \\coordinate[label=above right:$D$] (D) at ($(B)!{" << r1 << "/(3.5+" << r1 << ")}!(C)$);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (D);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](D,A,B);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](C,A,D);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Один из острых углов прямоугольного треугольника равен $" << Agrad << "^{\\circ}$. Найдите его другой острый угол. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (C) at (3.5,0);" << endl
                    << "            \\coordinate (B) at (23:3.22);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,B,C);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В остроугольном треугольнике $ABC$ проведена высота $BH$, $\\angle BAC=" << Agrad << "^{\\circ}$. Найдите угол $ABH$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (0,0);" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (3.5,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << Agrad << ":{" << (3.5*cos(Arad)) << "});" << endl
                    << "            \\coordinate[label=below:$H$] (H) at (0:{" << (3.5 * pow(cos(Arad),2)) << "});" << endl
                    << "            \\draw[thick] (B) -- (A) -- (C) -- (B) -- (H);" << endl
                    << "            \\tkzMarkRightAngle(B,H,A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике два угла равны $" << Agrad << "^{\\circ}$ и $" << Bgrad << "^{\\circ}$. Найдите его третий угол. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (C) at (-" << Agrad << ":" << r1 << ");" << endl
                    << "            \\coordinate (B) at ({-180+" << Bgrad << "}:" << r2 << ");" << endl
                    << "            \\draw[thick] (B) -- (A) -- (C) -- (B);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;
            }
            return Answer;
}

string TreugStoron(int i)
{
    double r, R, a, h, b, c, k, max, betta[2], gamma[3];
            double alpha;
            int type = rand()%16 + 1;
            string Answer;
            double answer;
            int check = 0;
            switch(type)
            {
            case 1:
                r = rand()%15+3;
                answer = 6*r;
                cout << "%" << (i+1) << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Радиус окружности, вписанной в равносторонний треугольник, равен $" << r << "\\sqrt{3}$. Найдите длину стороны этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\draw[thick] (O) circle(0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 2:
                a = rand()%40+2;
                answer = a/2;
                cout << "%" << (i+1) << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Сторона равностороннего треугольника равна $" << a << "\\sqrt{3}$. Найдите радиус окружности, вписанной в этот треугольник. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\draw[thick] (O) circle(0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 3:
                a = rand()%40+2;
                answer = a;
                cout << "%" << (i+1) << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Сторона равностороннего треугольника равна $" << a << "\\sqrt{3}$. Найдите радиус окружности, описанной около этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\draw[thick] (O) circle(1.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 4:
                R = rand()%15+3;
                answer = 3*R;
                cout << "%" << (i+1) << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Радиус окружности,  описанной около равностороннего треугольника, равен $" << R << "\\sqrt{3}$. Найдите длину стороны этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\draw[thick] (O) circle(1.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 5:
                h = rand()%15+3;
                answer = 2*h;
                cout << "%" << (i+1) << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Медиана равностороннего треугольника равна $" << h << "\\sqrt{3}$. Найдите сторону этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\coordinate (D) at (-90:0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (D) -- (C);" << endl
                    << "            \\tkzMarkSegment[mark=|, thick](B,D);" << endl
                    << "            \\tkzMarkSegment[mark=|, thick](D,A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 6:
                a = rand()%15+3;
                answer = 1.5*a;
                cout << "%" << (i+1) << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Сторона равностороннего треугольника равна $" << a << "\\sqrt{3}$. Найдите биссектрису этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\coordinate (D) at (-90:0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (D) -- (C);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.7](B,C,D);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.7](D,C,A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 7:
                h = rand()%15+3;
                answer = 2*h;
                cout << "%" << (i+1) << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Высота равностороннего треугольника равна $" << h << "\\sqrt{3}$. Найдите сторону этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (O) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30:1.5);" << endl
                    << "            \\coordinate (B) at (-150:1.5);" << endl
                    << "            \\coordinate (C) at (90:1.5);" << endl
                    << "            \\coordinate (D) at (-90:0.75);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (D) -- (C);" << endl
                    << "            \\tkzMarkRightAngle(A,D,C);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Катеты прямоугольного треугольника равны $" << a << "$ и $" << b << "$. Найдите гипотенузу этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (C) at (0,0);" << endl
                    << "            \\coordinate (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В прямоугольном треугольнике катет и гипотенуза равны $" << a << "$ и $" << c << " соответственно$. Найдите другой катет этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (C) at (0,0);" << endl
                    << "            \\coordinate (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ известно, что $AC = " << a << "$, $BC = " << b << "$, угол $C$ равен $90^{\\circ}$. Найдите радиус описанной около этого треугольника окружности. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (C) at (0,0);" << endl
                    << "            \\coordinate (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Точки $M$ и $N$ являются серединами сторон $AB$ и $BC$ треугольника $ABC$, сторона $AB$ равна " << b << ", сторона $BC$ равна " << c << ", сторона $AC$ равна " << a << ". Найдите $MN$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
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
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ известно, что $AC=" << a << "$, $BM$ -- медиана, $BM=" << r << "$. Найдите $AM$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$A$]   (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << alpha << ":" << (b/k) << ");" << endl
                    << "            \\coordinate[label=below:$C$] (C) at (0:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=below:$M$] (M) at ($(A)!0.5!(C)$);" << endl
                    << "            \\tkzMarkSegment[mark=|](A,M);" << endl
                    << "            \\tkzMarkSegment[mark=|](C,M);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (M) -- (B);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Катеты прямоугольного треугольника равны $" << a << "$ и $" << b << "$. Найдите площадь этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (C) at (0,0);" << endl
                    << "            \\coordinate (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ известно, что $AB=" << a << "$, $BC=" << b << "$, $\\sin(\\angle ABC)=\\frac{" << betta[0] << "}{" << betta[1] << "}$. Найдите площадь треугольника $ABC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (-30-" << alpha << ":" << a/k << ");" << endl
                    << "            \\coordinate[label=right:$C$] (C) at (-30:" << b/k << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Сторона треугольника равна " << a << ", а высота, проведенная к этой стороне, равна " << h << ". Найдите площадь этого треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (B) at (0,0);" << endl
                    << "            \\coordinate (A) at (-30-" << alpha << ":" << a/k << ");" << endl
                    << "            \\coordinate (C) at (-30:" << b/k << ");" << endl
                    << "            \\coordinate (O) at (-30-" << alpha << ":" << (b*cos((PI*alpha)/180))/k << ");" << endl
                    << "            \\tkzMarkRightAngle(A,O,C);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A) -- (O) -- (C);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Периметр треугольника равен " << a+b+c << ", одна из его сторон равна " << a << ", а радиус вписанной в него окружности равен " << r << ". Найдите площадь этого  треугольника. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << r/k << ");" << endl
                    << "            \\coordinate (A) at (" << betta[0] + gamma[0]/2 << ":" << (r/cos((PI*gamma[0])/360))/k << ");" << endl
                    << "            \\coordinate (B) at (" << betta[1] + gamma[1]/2 << ":" << (r/cos((PI*gamma[1])/360))/k << ");" << endl
                    << "            \\coordinate (C) at (" << 270 + gamma[2]/2 << ":" << (r/cos((PI*gamma[2])/360))/k << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;


            }
            return Answer;
}

string TreugReshotka(int i)
{
    int type = rand()%3+1;
            double xmax, ymax, xmid, x, y;
            string Answer;
            double answer;
            int check = 0;
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1х1 изображен ромб. Найдите длину его большей диагонали. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << (xmax/10) << "," << (ymax/10) << ");" << endl
                    << "            \\coordinate (A) at (0.5," << (ymax/20) << ");" << endl
                    << "            \\coordinate (B) at (" << xmax/20 << "," << (ymax/10)-0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << (xmax/10)-0.5 << "," << (ymax/20) << ");" << endl
                    << "            \\coordinate (D) at (" << xmax/20 << "," << 0.5 << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен треугольник $ABC$. Найдите длину его средней линии, параллельной стороне $AC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << (xmax / 10) << "," << (ymax / 10) << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (0.5,0.5);" << endl
                    << "            \\coordinate[label=above right:$B$] (B) at (" << (xmid/10) << "," << ((ymax - 5) / 10) << ");"
                    << "            \\coordinate[label=below right:$C$] (C) at (" << ((xmax - 5) / 10) << ",0.5);"
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);";
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен треугольник. Найдите его площадь. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << (xmax / 10) << "," << (ymax / 10) << ");" << endl
                    << "            \\coordinate (A) at (0.5,0.5);" << endl
                    << "            \\coordinate (B) at (" << (xmid/10) << "," << ((ymax - 5) / 10) << ");"
                    << "            \\coordinate (C) at (" << ((xmax - 5) / 10) << ",0.5);"
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);";
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;
            }
            return Answer;
}

string TreugTrigonom(int i)
{
    double a, b, c, max, k, chisl, znam;
            double alpha;
            int type = rand()%18+1;
            string Answer;
            double answer;
            int nod;
            int check = 0;
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $BC=" << b << "$, $AB=" << c << "$. Найдите $\\sin(A)$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (sqrt(pow(c,2)-pow(b,2))/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $AC=" << a << "$, $AB=" << c << "$. Найдите $\\sin(B)$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (sqrt(pow(c,2)-pow(a,2))/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $AC=" << a << "$, $AB=" << c << "$. Найдите $\\cos(A)$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (sqrt(pow(c,2)-pow(a,2))/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $BC=" << b << "$, $AB=" << c << "$. Найдите $\\cos(B)$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (sqrt(pow(c,2)-pow(b,2))/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $BC=" << b << "$, $AC=" << a << "$. Найдите $\\tg(A)$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $BC=" << b << "$, $AC=" << a << "$. Найдите $\\tg(B)$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\sin(A)=\\frac{" << chisl << "}{" << znam << "}$, $AB=" << c << "$. Найдите $BC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\sin(A)=\\frac{" << chisl << "}{" << znam << "}$, $BC=" << b << "$. Найдите $AB$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\sin(B)=\\frac{" << chisl << "}{" << znam << "}$, $AB=" << c << "$. Найдите $AC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\sin(B)=\\frac{" << chisl << "}{" << znam << "}$, $AC=" << a << "$. Найдите $AB$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\cos(B)=\\frac{" << chisl << "}{" << znam << "}$, $AB=" << c << "$. Найдите $BC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\cos(B)=\\frac{" << chisl << "}{" << znam << "}$, $BC=" << b << "$. Найдите $AB$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\cos(A)=\\frac{" << chisl << "}{" << znam << "}$, $AB=" << c << "$. Найдите $AC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\cos(A)=\\frac{" << chisl << "}{" << znam << "}$, $AC=" << a << "$. Найдите $AB$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\tg(A)=\\frac{" << chisl << "}{" << znam << "}$, $AC=" << a << "$. Найдите $BC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\tg(A)=\\frac{" << chisl << "}{" << znam << "}$, $BC=" << b << "$. Найдите $AC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\tg(B)=\\frac{" << chisl << "}{" << znam << "}$, $BC=" << b << "$. Найдите $AC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В треугольнике $ABC$ угол $C$ равен $90^{\\circ}$, $\\tg(B)=\\frac{" << chisl << "}{" << znam << "}$, $AC=" << a << "$. Найдите $BC$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$C$]   (C) at (0,0);" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (180:" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (90:" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (A);" << endl
                    << "            \\tkzMarkRightAngle(A,C,B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;


            }
            return Answer;
}

string Parallelogramm(int i)
{
    int type = rand()%15 + 1;
            string Answer;
            double alpha, betta;
            double a, b, c, h, max, k, l, h1, h2, S;
            double answer;
            int check = 0;
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Диагональ $AC$ параллелограмма $ABCD$ образует с его сторонами углы, равные $" << alpha << "^{\\circ}$ и $" << betta << "^{\\circ}$. Найдите больший угол этого параллелограмма. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$A$]   (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << (alpha+betta) << ":" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << alpha << ":" << (c/k) << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (" << 0 << ":" << (b/k) << ");" << endl
                    << "            \\tkzMarkAngle[mark=,arc=ll,size=0.7](D,A,C);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.7](C,A,B);" << endl
                    << "            \\tkzLabelAngle[pos=1](D,A,C) {$\\alpha$};" << endl
                    << "            \\tkzLabelAngle[pos=1](C,A,B) {$\\beta$};" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Диагонали $AC$ и $BD$ параллелограмма $ABCD$ пересекаются в точке $O$, $AC=" << static_cast<int>(c) << "$, $BD=" << static_cast<int>(l) << "$, $AB=" << a << "$. Найдите $DO$.  &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$A$]   (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << (alpha+betta) << ":" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << alpha << ":" << (c/k) << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (" << 0 << ":" << (b/k) << ");" << endl
                    << "            \\coordinate[label=left:$O$] (O) at (" << alpha << ":" << (c/(2*k)) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Диагональ $BD$ параллелограмма $ABCD$ образует с его сторонами углы, равные $" << alpha << "^{\\circ}$ и $" << betta << "^{\\circ}$. Найдите меньший угол этого параллелограмма. Ответ дайте в градусах.   &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (0:" << (b/k) << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (-" << betta << ":" << (c/k) << ");" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (-" << (alpha+betta) << ":" << (a/k) << ");" << endl
                    << "            \\tkzMarkAngle[mark=,arc=ll,size=0.5](D,B,C);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](A,B,D);" << endl
                    << "            \\tkzLabelAngle[pos=0.8](D,B,C) {$\\alpha$};" << endl
                    << "            \\tkzLabelAngle[pos=0.8](A,B,D) {$\\beta$};" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (D);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        Диагональ прямоугольника образует угол $" << betta << "^{\\circ}$ с одной из его сторон. Найдите острый угол между диагоналями этого прямоугольника. Ответ дайте в градусах.  &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                        << "            \\coordinate (B) at (0,0);" << endl
                        << "            \\coordinate (C) at (0:" << (b/k) << ");" << endl
                        << "            \\coordinate (D) at (-" << betta << ":" << (c/k) << ");" << endl
                        << "            \\coordinate (A) at (-" << (alpha+betta) << ":" << (a/k) << ");" << endl
                        << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                        cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                    //cout << answer << endl;
                    Answer = "  \\item " + to_string(answer) + " \n";
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
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        В ромбе $ABCD$ угол $ABC$ равен $" << alpha << "^{\\circ}$. Найдите угол $ACD$. Ответ дайте в градусах.  &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                        << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                        << "            \\coordinate[label=above:$C$] (C) at (0:" << (a/k) << ");" << endl
                        << "            \\coordinate[label=below:$D$] (D) at (-" << (alpha/2) << ":" << (c/k) << ");" << endl
                        << "            \\coordinate[label=below:$A$] (A) at (-" << (alpha) << ":" << (a/k) << ");" << endl
                        << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl;
                        cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                    //cout << answer << endl;
                    Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Один из углов параллелограмма равен $" << (alpha+betta) << "^{\\circ}$. Найдите больший угол этого параллелограмма. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate   (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (" << (alpha+betta) << ":" << (a/k) << ");" << endl
                    << "            \\coordinate (C) at (" << alpha << ":" << (c/k) << ");" << endl
                    << "            \\coordinate(D) at (" << 0 << ":" << (b/k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Найдите острый угол параллелограмма $ABCD$, если биссектриса угла $A$ образует со стороной $BC$ угол, равный $" << (alpha/2) << "^{\\circ}$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$A$]  (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (" << (alpha) << ":" << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << ((b+a*cos((alpha*PI)/180))/k) << "," << (h/k) << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (0:" << (b/k) << ");" << endl
                    << "            \\coordinate (O) at (" << (alpha/2) << ":" << (l/k) << ");"
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](O,A,B);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.5](D,A,O);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (O);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 8:
                    a = rand()%20 + 3;
                    answer = pow(a,2)/2;
                    cout << "%" << (i+1) << endl;
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        Периметр ромба равен " << (4*a) << ", а один из углов равен $30^{\\circ}$. Найдите площадь этого ромба. &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (30:2.2);" << endl
                    << "            \\coordinate (C) at (" << (2.2+(2.2*cos(PI/6))) << "," << (2.2*sin(PI/6)) << ");" << endl
                    << "            \\coordinate(D) at (0:2.2);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 9:
                   a = rand()%20 + 3;
                    answer = a/2;
                    cout << "%" << (i+1) << endl;
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        Сторона ромба равна " << (a) << ", а один из углов равен $150^{\\circ}$. Найдите высоту этого ромба. &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (30:2.2);" << endl
                    << "            \\coordinate (C) at (" << (2.2+(2.2*cos(PI/6))) << "," << (2.2*sin(PI/6)) << ");" << endl
                    << "            \\coordinate (D) at (0:2.2);" << endl
                    << "            \\coordinate (O) at (" << (2.2*cos(PI/6)) << ", 0);" << endl
                    << "            \\tkzMarkRightAngle(A,O,B);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (O);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        Площадь параллелограмма равна " << S << ", а две его стороны равны " << a << " и " << b << ". Найдите его высоты. В ответе укажите большую высоту. &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (" << ((a*cos(alpha))/k) << ", " << ((a*sin(alpha))/k) << ");" << endl
                    << "            \\coordinate (C) at (" << ((a*cos(alpha)+b)/k) << "," << ((a*sin(alpha))/k) << ");" << endl
                    << "            \\coordinate (D) at (" <<  (b/k) << ",0);" << endl
                    << "            \\coordinate (O1) at (" << (a*cos(alpha)/k) << ", 0);" << endl
                    << "            \\coordinate (O2) at (" << ((b+a*cos(alpha)-(b*pow(cos(alpha),2)))/k) << ", " << ((a*sin(alpha)-(b*sin(alpha)*cos(alpha)))/k) << ");" << endl
                    << "            \\tkzMarkRightAngle(A,O1,B);" << endl
                    << "            \\tkzMarkRightAngle(C,O2,B);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (O1) -- (D) -- (O2) -- (B);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;
            
            case 11:
                a = rand()%20+3;
                answer = a*2;
                cout << "%" << (i+1) << endl;
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        Сторона квадрата равна $" << a << "\\sqrt{2}$. Найдите диагональ этого квадрата. &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (2,0);" << endl
                    << "            \\coordinate (C) at (2,2);" << endl
                    << "            \\coordinate (D) at (0,2);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 12:
                a = rand()%20+3;
                answer = a;
                cout << "%" << (i+1) << endl;
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        Диагональ квадрата равна $" << a << "\\sqrt{2}$. Найдите сторону этого квадрата. &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (2,0);" << endl
                    << "            \\coordinate (C) at (2,2);" << endl
                    << "            \\coordinate (D) at (0,2);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        Диагонали $AC$ и $BD$ прямоугольника $ABCD$ пересекаются в точке $O$, $BO=" << c/2 << "$, $AB=" << a << "$. Найдите $AC$. &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (0,0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (0," << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << (b/k) << "," << (a/k) << ");" << endl
                    << "            \\coordinate[label=above:$O$] (O) at (" << (b/k)/2 << "," << (a/k)/2 << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (" << (b/k) << ",0);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                    cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        В ромбе $ABCD$ угол $BCD$ равен $" << 180 - alpha << "^{\\circ}$. Найдите угол $BCD$. Ответ дайте в градусах.  &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                        << "            \\coordinate[label=above:$B$] (B) at (0,0);" << endl
                        << "            \\coordinate[label=above:$C$] (C) at (0:" << (a/k) << ");" << endl
                        << "            \\coordinate[label=below:$D$] (D) at (-" << (alpha/2) << ":" << (c/k) << ");" << endl
                        << "            \\coordinate[label=below:$A$] (A) at (-" << (alpha) << ":" << (a/k) << ");" << endl
                        << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (D);" << endl;
                        cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                    //cout << answer << endl;
                    Answer = "  \\item " + to_string(answer) + " \n";
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
                    cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                    cout << "        Найдите площадь параллелограмма, изображенного на рисунке.  &" << endl;
                    cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
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
                        cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                    //cout << answer << endl;
                    Answer = "  \\item " + to_string(answer) + " \n";
                break;

            }
            return Answer;
}

string Trapet(int i)
{
    int type = rand()%10 + 1;
            string Answer;
            double alpha, betta;
            double a, b, c, h, max, k, l, h1, h2, S;
            double answer;
            int check = 0;
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Один из углов прямоугольной трапеции равен $" << alpha << "^{\\circ}$. Найдите больший угол этой трапеции. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (0,0);" << endl
                    << "            \\coordinate (B) at (0," << (a / k) << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << (a / k) << ");" << endl
                    << "            \\coordinate (D) at (" << ((a + b) / k) << ",0);" << endl
                    << "            \\tkzMarkRightAngle(B,A,D);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В равнобедренной трапеции известны высота, меньшее основание и угол при основании (см.рисунок). Найдите большее основание. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (-" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (B) at (-" << a / k << "," << (b / k) << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << (b / k) << ");" << endl
                    << "            \\coordinate (D) at (" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (O) at (-" << a / k << ",0);" << endl
                    << "            \\coordinate[label=right:$" << b << "$] (O1) at (-" << (a / k) << "," << (b / (2 * k)) << ");" << endl
                    << "            \\coordinate[label=above:$" << (2 * a) << "$] (O2) at (0," << (b / k) << ");" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.3](D,A,B);" << endl
                    << "            \\tkzLabelAngle[pos=0.7](D,A,B) {$45^{\\circ}$};" << endl
                    << "            \\tkzMarkRightAngle(B,O,D);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (O);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В равнобедренной трапеции известны высота, большее основание и угол при основании (см.рисунок). Найдите меньшее основание. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (-" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (B) at (-" << a / k << "," << (b / k) << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << (b / k) << ");" << endl
                    << "            \\coordinate (D) at (" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (O) at (-" << a / k << ",0);" << endl
                    << "            \\coordinate[label=right:$" << b << "$] (O1) at (-" << (a / k) << "," << (b / (2 * k)) << ");" << endl
                    << "            \\coordinate[label=below:$" << (2 * a + 2 * b) << "$] (O2) at (0,0);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.3](D,A,B);" << endl
                    << "            \\tkzLabelAngle[pos=0.7](D,A,B) {$45^{\\circ}$};" << endl
                    << "            \\tkzMarkRightAngle(B,O,D);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (B) -- (O);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Основания трапеции равны " << 2*a << " и " << 2*b << ", а высота равна " << h1 << ". Найдите среднюю линию этой трапеции. & " << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
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
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Основания трапеции равны " << 2 * a << " и " << 2 * b << ". Найдите больший из отрезков, на которые делит среднюю линию этой трапеции одна из ее диагоналей. & " << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (-" << b / k << ",0);" << endl
                    << "            \\coordinate (B) at (-" << (a - h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate (C) at (" << (a + h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate (D) at (" << b / k << ",0);" << endl
                    << "            \\coordinate (O) at (-" << (a - h) / k << ",0);" << endl
                    << "            \\coordinate (N) at (-" << (b + a - h) / (2 * k) << "," << h1 / (2 * k) << ");" << endl
                    << "            \\coordinate (M) at (" << (b + a + h) / (2 * k) << "," << h1 / (2 * k) << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C);" << endl
                    << "            \\draw[thick] (N) -- (M);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Высота равнобедренной трапеции, проведенная из вершины $C$, делит основание $AD$ на отрезки длиной $" << (b-a) << "$ и $" << (a+b) << "$. Найдите длину основания $BC$. & " << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (-" << b / k << ",0);" << endl
                    << "            \\coordinate[label=above:$B$] (B) at (-" << (a - h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << (a + h) / k << "," << h1 / k << ");" << endl
                    << "            \\coordinate[label=below:$D$] (D) at (" << b / k << ",0);" << endl
                    << "            \\coordinate (O) at (" << (a - h) / k << ",0);" << endl
                    << "            \\tkzMarkRightAngle(D,O,C);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl
                    << "            \\draw[thick] (C) -- (O);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Один из углов равнобедренной трапеции равен $" << alpha << "^{\\circ}$. Найдите больший угол этой трапеции. Ответ дайте в градусах. & " << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (-" << (a+b) / k << ",0);" << endl
                    << "            \\coordinate (B) at (-" << (a / k) << "," << h1 / k << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << h1 / k << ");" << endl
                    << "            \\coordinate (D) at (" << (a + b) / k << ",0);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Сумма двух углов равнобедренной трапеции равна $" << 2*alpha << "^{\\circ}$. Найдите больший угол этой трапеции. Ответ дайте в градусах. & " << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (-" << (a + b) / k << ",0);" << endl
                    << "            \\coordinate (B) at (-" << (a / k) << "," << h1 / k << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << h1 / k << ");" << endl
                    << "            \\coordinate (D) at (" << (a + b) / k << ",0);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Основания трапеции равны " << 2*a << " и " << 2*b << ", а высота равна " << h1 << ". Найдите площадь этой трапеции. & " << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
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
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В равнобедренной трапеции известны высота, большее основание и угол при основании (см.рисунок). Найдите меньшее основание. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (-" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (B) at (-" << a / k << "," << (b / k) << ");" << endl
                    << "            \\coordinate (C) at (" << (a / k) << "," << (b / k) << ");" << endl
                    << "            \\coordinate (D) at (" << ((a + b) / k) << ",0);" << endl
                    << "            \\coordinate (O) at (-" << a / k << ",0);" << endl
                    << "            \\coordinate[label=above:$" << 2*a << "$] (O1) at (0," << (b / k) << ");" << endl
                    << "            \\coordinate[label=below:$" << (2 * a + 2 * b) << "$] (O2) at (0,0);" << endl
                    << "            \\tkzMarkAngle[mark=,arc=l,size=0.3](D,A,B);" << endl
                    << "            \\tkzLabelAngle[pos=0.7](D,A,B) {$45^{\\circ}$};" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;
            }
            return Answer;
}

string MnogougReshotka(int i)
{
    int type = rand()%5+1;
            double xmax, ymax, x, y, delta1, delta2, x1;
            string Answer;
            double answer;
            int check = 0;
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
                cout << "\\item\n" << endl << "\\begin{minipage}[t]{0.75\\textwidth}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен ромб. Найдите длину его большей диагонали. " << endl;
                cout << "\\end{minipage}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5," << ymax/2 << ");" << endl
                    << "            \\coordinate (B) at (" << xmax/2 << "," << ymax-0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << xmax-0.5 << "," << ymax/2 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax/2 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item\n" << endl << "\\begin{minipage}[t]{0.75\\textwidth}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен ромб. Найдите площадь этого ромба. " << endl;
                cout << "\\end{minipage}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5," << ymax / 2 << ");" << endl
                    << "            \\coordinate (B) at (" << xmax / 2 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << xmax - 0.5 << "," << ymax / 2 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax / 2 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item\n" << endl << "\\begin{minipage}[t]{0.75\\textwidth}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображена трапеция. Найдите длину её средней линии. " << endl;
                cout << "\\end{minipage}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5,0.5);" << endl
                    << "            \\coordinate (B) at (" << (xmax-delta1) / 2 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << (xmax + delta2) / 2 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax-0.5 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item\n" << endl << "\\begin{minipage}[t]{0.75\\textwidth}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображен параллелограмм. Найдите его площадь." << endl;
                cout << "\\end{minipage}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5,0.5);" << endl
                    << "            \\coordinate (B) at (" << (delta1*0.5) << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << xmax - 0.5 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax-0.5*delta1 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item\n" << endl << "\\begin{minipage}[t]{0.75\\textwidth}" << endl;
                cout << "        На клетчатой бумаге с размером клетки 1x1 изображена трапеция. Найдите её площадь." << endl;
                cout << "\\end{minipage}\\hfill" << endl << "\\begin{tikzpicture}[scale=0.7, baseline=(current bounding box.center)] % Добавлено baseline" << endl
                    << "            \\draw [gray!50, step=0.5] (0,0) grid (" << xmax << "," << ymax << ");" << endl
                    << "            \\coordinate (A) at (0.5,0.5);" << endl
                    << "            \\coordinate (B) at (" << (delta1*0.5) << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (C) at (" << xmax - 0.5*delta2 << "," << ymax - 0.5 << ");" << endl
                    << "            \\coordinate (D) at (" << xmax - 0.5 << ",0.5);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "\\end{tikzpicture}" << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;
            }
            return Answer;
}

string Okrugn(int i)
{
    double r, R, a, alpha[4], change, k, l[4], side[4], betta[4], max;
            double answer;
            string Answer;
            int check = 0;
            int type = rand()%14 + 1;
            switch (type)
            {
            case 1:
                a = rand() % 15 + 2;
                answer = a;
                R = 1.5;
                cout << "%" << i + 1 << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Сторона квадрата равна $" << a << "\\sqrt{2}$. Найдите радиус окружности, описанной около этого квадрата. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 2:
                a = rand() % 15 + 2;
                answer = pow(2*a,2);
                R = 1.5;
                r = R / sqrt(2);
                cout << "%" << i + 1 << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Найдите площадь квадрата, описанного около окружности радиуса " << a << ". &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[fill=black] (0,0) circle(1pt);" << endl
                    << "            \\draw[thick] (0,0) circle(" << r << ");" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 3:
                a = rand() % 30 + 2;
                answer = a/2;
                R = 1.5;
                r = R / sqrt(2);
                cout << "%" << i + 1 << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Сторона квадрата равна " << a << ". Найдите радиус окружности, вписанной в этот квадрат. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[fill=black] (0,0) circle(1pt);" << endl
                    << "            \\draw[thick] (0,0) circle(" << r << ");" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 4:
                a = rand() % 15 + 2;
                answer = 2*a;
                R = 1.5;
                cout << "%" << i + 1 << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Радиус окружности, описанной около квадрата, равен $" << a << "\\sqrt{2}$. Найдите длину стороны этого квадрата. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[fill=black] (0,0) circle(1pt);" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;

            case 5:
                a = rand() % 20 + 2;
                answer = 4*a;
                R = 1.5;
                r = R / sqrt(2);
                cout << "%" << i + 1 << endl;
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Радиус вписанной в квадрат окружности равен $" << a << "\\sqrt{2}$. Найдите диагональ этого квадрата. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[fill=black] (0,0) circle(1pt);" << endl
                    << "            \\draw[thick] (0,0) circle(" << r << ");" << endl
                    << "            \\coordinate (A) at (45:" << R << ");" << endl
                    << "            \\coordinate (B) at (135:" << R << ");" << endl
                    << "            \\coordinate (C) at (225:" << R << ");" << endl
                    << "            \\coordinate (D) at (315:" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
               // cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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

                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Четырехугольник $ABCD$ описан около окружности, $AB=" << side[2] << "$, $BC=" << side[1] << "$, $CD=" << side[0] << "$. Найдите $AD$. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << R/k << ");" << endl
                    << "            \\coordinate[label=left:$C$] (C) at (" << (alpha[0]+(betta[1]/2)) << ":" << l[1]/k << ");" << endl
                    << "            \\coordinate[label=left:$B$] (B) at (" << (alpha[1]+(betta[2]/2)) << ":" << l[2]/k << ");" << endl
                    << "            \\coordinate[label=below:$A$] (A) at (" << (alpha[2]+(betta[3]/2)) << ":" << l[3]/k << ");" << endl
                    << "            \\coordinate[label=right:$D$] (D) at (" << (alpha[3]+(betta[0]/2)) << ":" << l[0]/k << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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

                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Радиус окружности, вписанной в равнобедренную трапецию, равен " << R << ". Найдите высоту этой трапеции. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << R/k << ");" << endl
                    << "            \\coordinate (C) at (" << (alpha[0]+(betta[1]/2)) << ":" << l[1]/k << ");" << endl
                    << "            \\coordinate (B) at (" << (alpha[1]+(betta[2]/2)) << ":" << l[2]/k << ");" << endl
                    << "            \\coordinate (A) at (" << (alpha[2]+(betta[3]/2)) << ":" << l[3]/k << ");" << endl
                    << "            \\coordinate (D) at (" << (alpha[3]+(betta[0]/2)) << ":" << l[0]/k << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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

                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Радиус окружности, вписанной в прямоугольную трапецию, равен " << R << ". Найдите высоту этой трапеции. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << R/k << ");" << endl
                    << "            \\coordinate (C) at (" << (alpha[0]+(betta[1]/2)) << ":" << l[1]/k << ");" << endl
                    << "            \\coordinate (B) at (" << (alpha[1]+(betta[2]/2)) << ":" << l[2]/k << ");" << endl
                    << "            \\coordinate (A) at (" << (alpha[2]+(betta[3]/2)) << ":" << l[3]/k << ");" << endl
                    << "            \\coordinate (D) at (" << (alpha[3]+(betta[0]/2)) << ":" << l[0]/k << ");" << endl
                    << "            \\tkzMarkRightAngle(A,D,C);" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Угол $A$ трапеции $ABCD$ с основаниями $AD$ и $BC$, вписанной в окружность, равен $" << (180 - answer) << "^{\\circ}$. Найдите угол $B$ этой трапеции. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << r << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << 180 + betta[0] << ":" << r << ");" << endl
                    << "            \\coordinate[label=above left:$B$] (B) at (" << 180 - alpha[0] << ":" << r << ");" << endl
                    << "            \\coordinate[label=above right:$C$] (C) at (" << alpha[0] << ":" << r << ");" << endl
                    << "            \\coordinate[label=below right:$D$] (D) at (-" <<  betta[0] << ":" << r << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Четырехугольник $ABCD$ вписан в окружность. Угол $ABD$ равен $" << (alpha[3]-alpha[2])/2 << "^{\\circ}$, угол $CAD$ равен $" << (360-alpha[3]+alpha[0])/2 << "^{\\circ}$. Найдите угол $ABC$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above left:$B$] (B) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above right:$C$] (C) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below right:$D$] (D) at (" <<  alpha[3] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        В окружности с центром в точке $O$ отрезки $AC$ и $BD$ -- диаметры. Угол $AOD$ равен $" << (alpha[3] - alpha[2]) << "^{\\circ}$. Найдите угол $ACB$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=below:$O$] (O) at(0,0);" << endl
                    << "            \\draw[fill=black] (O) circle(1pt);" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above left:$B$] (B) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above right:$C$] (C) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below right:$D$] (D) at (" <<  alpha[3] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (C) -- (B) -- (D);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        На окружности по разные стороны от диаметра $AB$ взяты точки $M$ и $N$. Известно, что угол $NBA=" << (180-alpha[1])/2 << "^{\\circ}$. Найдите угол $NMB$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=left:$A$] (A) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above left:$N$] (N) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=right:$B$] (B) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below right:$M$] (M) at (" <<  alpha[3] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (N) -- (M) -- (B);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Треугольник $ABC$ вписан в окружность с центром в точке $O$. Точки $O$ и $C$ лежат в одной полуплоскости относительно прямой $AB$. Найдите угол $ACB$, если угол $AOB$  равен $" << (alpha[2] - alpha[1]) << "^{\\circ}$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=above:$O$] (O) at(0,0);" << endl
                    << "            \\draw[fill=black] (O) circle(1pt);" << endl
                    << "            \\coordinate[label=below right:$B$] (B) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above:$C$] (C) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (C) -- (B) -- (A) -- (O) -- (B);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
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
                cout << "\\item  \\textbf{Условие}:" << endl << "\\begin{table}[h!]" << endl << "   \\begin{tabular}{m{10cm} m{3cm}}" << endl;
                cout << "        Четырехугольник $ABCD$ вписан в окружность. Угол $ABC$ равен $" << (360-alpha[2]+alpha[0])/2 << "^{\\circ}$, угол $CAD$ равен $" << (360-alpha[3]+alpha[0])/2 << "^{\\circ}$. Найдите угол $ABD$. Ответ дайте в градусах. &" << endl;
                cout << "       \\begin{center}" << endl << "            \\begin{tikzpicture}" << endl
                    << "            \\draw[thick] (0,0) circle(" << R << ");" << endl
                    << "            \\coordinate[label=below left:$A$] (A) at (" << alpha[2] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above left:$B$] (B) at (" << alpha[1] << ":" << R << ");" << endl
                    << "            \\coordinate[label=above right:$C$] (C) at (" << alpha[0] << ":" << R << ");" << endl
                    << "            \\coordinate[label=below right:$D$] (D) at (" <<  alpha[3] << ":" << R << ");" << endl
                    << "            \\draw[thick] (A) -- (B) -- (C) -- (D) -- (A) -- (C) -- (B) -- (D);" << endl;
                cout << "        \\end{tikzpicture}" << endl << "     \\end{center}" << endl << "      \\end{tabular}" << endl << "\\end{table}" << endl << endl << endl << endl;
                //cout << answer << endl;
                Answer = "  \\item " + to_string(answer) + " \n";
                break;


            }
            return Answer;
}


int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    int count_task[37];              // Создает массив из номеров заданий
    for (int i = 0; i < 37; i++)     // Обнуляет количество заданий в номерах
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
                cout << "1. Числа и вычисления (" << count_task[0] + count_task[1] + count_task[2] + count_task[3] + count_task[4] + count_task[5] + count_task[6] << ")" << endl;
                cout << "2. Алгебраические выражения (" << count_task[7] + count_task[8] + count_task[9] + count_task[10] << ")" << endl;
                cout << "3. Теория вероятности (" << count_task[11] << ")" << endl; // Задание 12
                cout << "4. Числовые неравенства, координатная прямая (" << count_task[12] + count_task[13] + count_task[14] << ")" << endl;
                cout << "5. Уравнения (" << count_task[15] + count_task[16] + count_task[17] << ")" << endl;
                cout << "6. Неравенства (" << count_task[18] + count_task[19] + count_task[20] + count_task[21] << ")" << endl;
                cout << "7. Рассчеты по формулам (" << count_task[22] << ")" << endl;
                cout << "8. Графики (" << count_task[23] << ")" << endl;
                cout << "9. Прогрессии (" << count_task[24] + count_task[25] + count_task[26] << ")" << endl;
                cout << "10. Треугольники (" << count_task[27] + count_task[28] + count_task[29] + count_task[30] + count_task[31] << ")" << endl;
                cout << "11. Многоугольники (" << count_task[32] + count_task[33] + count_task[34] + count_task[35] << ")" << endl;
                cout << "12. Окружности (" << count_task[36] << ")" << endl << endl;
                cout << "69. Сгенерировать" << endl;
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
                        cout << "3. Все целиком (" << count_task[6] << ")" << endl << endl; // Задание 7
                        cout << "0. Назад" << endl;
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
                        cout << "4. Все целиком (" << count_task[10] << ")" << endl << endl; // Задание 11
                        cout << "0. Назад" << endl;
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
                        }
                    } while (choice != 0);
                    choice = -1;
                    break;
                case 3:
                    cout << "\033[2J\033[1;1H";
                    cout << "Введите количество заданий: ";
                    cin >> count_task[11];
                    break;
                case 4:
                    do {
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Координатная прямая (" << count_task[12] << ")" << endl; // Задание 13
                        cout << "2. Числовые неравенства (" << count_task[13] << ")" << endl; // Задание 14
                        cout << "3. Все целиком (" << count_task[14] << ")" << endl << endl; // Задание 15
                        cout << "0. Назад" << endl;
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
                        cout << "0. Назад" << endl;
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
                        cout << "0. Назад" << endl;
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
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 7:
                    cout << "\033[2J\033[1;1H";
                    cout << "Введите количество заданий: ";
                    cin >> count_task[22];                              // Задание 23
                    break;
                case 8:
                    cout << "\033[2J\033[1;1H";
                    cout << "Введите количество заданий: ";
                    cin >> count_task[23];                              // Задание 24
                    break;
                case 9:
                    do{
                        cout << "\033[2J\033[1;1H";
                        cout << "Выберите темы:" << endl;
                        cout << "1. Арифметические прогрессии (" << count_task[24] << ")" << endl; // Задание 25
                        cout << "2. Геометрические прогрессии (" << count_task[25] << ")" << endl; // Задание 26
                        cout << "3. Все целиком (" << count_task[26] << ")" << endl; // Задание 27
                        cout << "0. Назад" << endl;
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
                        cout << "0. Назад" << endl;
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
                        cout << "0. Назад" << endl;
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
                        }
                    }while (choice != 0);
                    choice = -1;
                    break;
                case 12:
                    cout << "\033[2J\033[1;1H";
                            cout << "Введите количество заданий: ";
                            cin >> count_task[36];                      // Задание 37
                            break;
                case 69:
                    cout << "\033[2J\033[1;1H";
                    int Count = 0;
                    if (count_task[0] != 0)
                    {
                        for (int i = 0; i < count_task[0]; i++)
                        {
                            Answers = Answers + FractionPlusMinus(Count);
                            Count++;
                        }
                        count_task[0] = 0;
                    }
                    if (count_task[1] != 0)
                    {
                        for (int i = 0; i < count_task[1]; i++)
                        {
                            Answers = Answers + FractionMultDiv(Count);
                            Count++;
                        }
                        count_task[1] = 0;
                    }
                    if (count_task[2] != 0)
                    {
                        for (int i = 0; i < count_task[2]; i++)
                        {
                            if (pow(-1, rand()) > 0)
                                Answers = Answers + FractionMultDiv(Count);
                            else
                                Answers = Answers + FractionPlusMinus(Count);
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
                            Answers = Answers + DFractionMultDiv(Count);
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
                                Answers = Answers + DFractionMultDiv(Count);
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
                                Answers = Answers + FractionPlusMinus(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + FractionMultDiv(Count);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + DFractionPlusMinus(Count);
                                Count++;
                                break;

                            case 4:
                                Answers = Answers + DFractionMultDiv(Count);
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
                            Answers = Answers + LetterEqu(Count);
                            Count++;
                        }
                        count_task[7] = 0;
                    }
                    if (count_task[8] != 0)
                    {
                        for (int i = 0; i < count_task[8]; i++)
                        {
                            Answers = Answers + Pow(Count);
                            Count++;
                        }
                        count_task[8] = 0;
                    }
                    if (count_task[9] != 0)
                    {
                        for (int i = 0; i < count_task[9]; i++)
                        {
                            Answers = Answers + Sqrt(Count);
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
                                Answers = Answers + LetterEqu(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Pow(Count);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + Sqrt(Count);
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
                            Answers = Answers + TeorVer(Count);
                            Count++;
                        }
                        count_task[11] = 0;
                    }
                    if (count_task[12] != 0)
                    {
                        for (int i = 0; i < count_task[12]; i++)
                        {
                            Answers = Answers + NumberLine1(Count);
                            Count++;
                        }
                        count_task[12] = 0;
                    }
                    if (count_task[13] != 0)
                    {
                        for (int i = 0; i < count_task[13]; i++)
                        {
                            Answers = Answers + NumberLine2(Count);
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
                                Answers = Answers + NumberLine1(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + NumberLine2(Count);
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
                            Answers = Answers + LineUravn(Count);
                            Count++;
                        }
                        count_task[15] = 0;
                    }
                    if (count_task[16] != 0)
                    {
                        for (int i = 0; i < count_task[16]; i++)
                        {
                            Answers = Answers + KvadrUravn(Count);
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
                                Answers = Answers + LineUravn(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + KvadrUravn(Count);
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
                            Answers = Answers + LineNerav(Count);
                            Count++;
                        }
                        count_task[18] = 0;
                    }
                    if (count_task[19] != 0)
                    {
                        for (int i = 0; i < count_task[19]; i++)
                        {
                            Answers = Answers + KvadrNerav(Count);
                            Count++;
                        }
                        count_task[19] = 0;
                    }
                    if (count_task[20] != 0)
                    {
                        for (int i = 0; i < count_task[20]; i++)
                        {
                            Answers = Answers + SistNerav(Count);
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
                                Answers = Answers + LineNerav(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + KvadrNerav(Count);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + SistNerav(Count);
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
                            Answers = Answers + RaschetForm(Count);
                            Count++;
                        }
                        count_task[22] = 0;
                    }
                    if (count_task[23] != 0)
                    {
                        for (int i = 0; i < count_task[23]; i++)
                        {
                            Answers = Answers + Graphic();
                            Count++;
                        }
                        count_task[23] = 0;
                    }
                    if (count_task[24] != 0)
                    {
                        for (int i = 0; i < count_task[24]; i++)
                        {
                            Answers = Answers + ArivmetProgr();
                            Count++;
                        }
                        count_task[24] = 0;
                    }
                    if (count_task[25] != 0)
                    {
                        for (int i = 0; i < count_task[25]; i++)
                        {
                            Answers = Answers + GeomProgr();
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
                                Answers = Answers + ArivmetProgr();
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + GeomProgr();
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
                            Answers = Answers + TreugUgli(Count);
                            Count++;
                        }
                        count_task[27] = 0;
                    }
                    if (count_task[28] != 0)
                    {
                        for (int i = 0; i < count_task[28]; i++)
                        {
                            Answers = Answers + TreugStoron(Count);
                            Count++;
                        }
                        count_task[28] = 0;
                    }
                    if (count_task[29] != 0)
                    {
                        for (int i = 0; i < count_task[29]; i++)
                        {
                            Answers = Answers + TreugReshotka(Count);
                            Count++;
                        }
                        count_task[29] = 0;
                    }
                    if (count_task[30] != 0)
                    {
                        for (int i = 0; i < count_task[30]; i++)
                        {
                            Answers = Answers + TreugTrigonom(Count);
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
                                Answers = Answers + TreugUgli(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + TreugStoron(Count);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + TreugReshotka(Count);
                                Count++;
                                break;

                            case 4:
                                Answers = Answers + TreugTrigonom(Count);
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
                            Answers = Answers + Parallelogramm(Count);
                            Count++;
                        }
                        count_task[32] = 0;
                    }
                    if (count_task[33] != 0)
                    {
                        for (int i = 0; i < count_task[33]; i++)
                        {
                            Answers = Answers + Trapet(Count);
                            Count++;
                        }
                        count_task[33] = 0;
                    }
                    if (count_task[34] != 0)
                    {
                        for (int i = 0; i < count_task[34]; i++)
                        {
                            Answers = Answers + MnogougReshotka(Count);
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
                                Answers = Answers + Parallelogramm(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Trapet(Count);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + MnogougReshotka(Count);
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
                            Answers = Answers + Okrugn(Count);
                            Count++;
                        }
                        count_task[36] = 0;
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
                                Answers = Answers + FractionPlusMinus(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + FractionMultDiv(Count);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + DFractionPlusMinus(Count);
                                Count++;
                                break;

                            case 4:
                                Answers = Answers + DFractionMultDiv(Count);
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
                                Answers = Answers + NumberLine1(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + NumberLine2(Count);
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
                                Answers = Answers + LetterEqu(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Pow(Count);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + Sqrt(Count);
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
                                Answers = Answers + LineUravn(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + KvadrUravn(Count);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 11
                        {
                            Answers = Answers + TeorVer(Count);
                            Count++;
                        }

                for (int i = 0; i < 1; i++)             // 23
                        {
                            Answers = Answers + Graphic();
                            Count++;
                        }

                for (int i = 0; i < 1; i++)             // 22
                        {
                            Answers = Answers + RaschetForm(Count);
                            Count++;
                        }

                for (int i = 0; i < 1; i++)             // 21
                        {
                            int type_1 = rand() % 3 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + LineNerav(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + KvadrNerav(Count);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + SistNerav(Count);
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
                                Answers = Answers + ArivmetProgr();
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + GeomProgr();
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
                                Answers = Answers + TreugUgli(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + TreugStoron(Count);
                                Count++;
                                break;

                            case 3:
                                Answers = Answers + TreugTrigonom(Count);
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
                                Answers = Answers + Parallelogramm(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + Trapet(Count);
                                Count++;
                                break;
                            }
                        }

                for (int i = 0; i < 1; i++)             // 36
                        {
                            Answers = Answers + Okrugn(Count);
                            Count++;
                        }

                for (int i = 0; i < 1; i++)             // 29 34
                        {
                            int type_1 = rand() % 2 + 1;
                            switch (type_1)
                            {
                            case 1:
                                Answers = Answers + TreugReshotka(Count);
                                Count++;
                                break;

                            case 2:
                                Answers = Answers + MnogougReshotka(Count);
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
