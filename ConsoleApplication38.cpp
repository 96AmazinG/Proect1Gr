#include <iostream>
#include <conio.h>

int     DisplayMenu(void); //печать меню и запрос пункта
double* CreateArray(double* m, int size_m); //выделение памяти под массив
int     InputArray(double* m, int size_m); //ввод массива с клавиатуры
int     RandArray(double* m, int size_m); //задание массива случайными числами
int     CopyArray(double* source, double* target, int size_); //копирование из одного массива в другой
double* AddItem(double* m, int size_m, double item, int index); //добавление элемента в массив
double* RemoveItemIndex(double* m, int size_m, int index); //удаление элемента из массива
int     SearchItem(double* m, int size_m, double item); //поиск элемента в массиве по значению
void    DisplayArray(double* m, int size_m); //вывод на экран массива

int main()
{
    setlocale(LC_ALL, "Russian"); //задание русской кодировки для консоли
    srand((unsigned)time(0)); // задание (включение) генератора случайных чисел

    double* m=NULL, a=0;
    int s=0, sel=0, ind=-1;
    //s - размер массива, sel - выбранный пункт меню, ind - используемый индекс

    while (sel != 13)
    {
        system("cls");
        sel = DisplayMenu();
        
        switch (sel)
        {
        case 1: //Выделить память под массив
            printf_s("Выделить память под массив\n");
            printf_s("Введите размер массива: ");
            scanf_s("%d", &s);
            m = CreateArray(m, s);
            break;

        case 2: //Заполнить массив случайными числами
            printf_s("Заполнить массив случайными числами\n");
            RandArray(m, s);
            break;

        case 3: //Ввести массив с клавиатуры
            printf_s("Ввод массива с клавиатуры\n");
            InputArray(m, s);
            break;

        case 4: //Добавить элемент массива в конец
            printf_s("Добавить элемент массива в конец\n");
            printf_s("Введите значение: ");
            scanf_s("%lf", &a);
            m = AddItem(m, s, a, s);
            s++;
            break;

        case 5: //Добавить элемент массива в начало
            printf_s("Добавить элемент массива в начало\n");
            printf_s("Введите значение: ");
            scanf_s("%lf", &a);
            m = AddItem(m, s, a, 0);
            s++;
            break;

        case 6: //Добавить элемент массива на k-ую позицию
            printf_s("Добавить элемент массива на k-ую позицию\n");
            printf_s("Введите значение: ");
            scanf_s("%lf", &a);
            printf_s("Введите позицию элемента (начиная счет с 0): ");
            scanf_s("%d", &ind);
            m = AddItem(m, s, a, ind);
            s++;
            break;

        case 7: //Добавить элемент после искомого значения
            printf_s("Добавить элемент после искомого значения\n");
            printf_s("Введите искомое значение: ");
            scanf_s("%lf", &a);
            ind = SearchItem(m, s, a);
            if (ind != -1) //если элемент найдет, то
            {
                printf_s("Введите добавляемое значение: ");
                scanf_s("%lf", &a);
                m = AddItem(m, s, a, ind + 1);
            }
            else //иначе (элемент не найден)
            {
                printf_s("Искомое значение не найдено\n");
            }
            break;

        case 8: //Удалить последний элемент массива
            printf_s("Удалить последний элемент массива\n");
            m = RemoveItemIndex(m, s, s-1);
            s--;
            break;

        case 9: //Удалить первый элемент массива
            printf_s("Удалить первый элемент массива\n");
            m = RemoveItemIndex(m, s, 0);
            s--;
            break;

        case 10: //Удалить k-ый элемент массива
            printf_s("Удалить k-ый элемент массива\n");
            printf_s("Введите позицию элемента (начиная счет с 0): ");
            scanf_s("%d", &ind);
            m = RemoveItemIndex(m, s, ind);
            s--;
            break;

        case 11: //Удалить элементы массива с указанным значением
            printf_s("Удалить элементы массива с указанным значением\n");
            printf_s("Введите значение: ");
            scanf_s("%lf", &a);
            do // цикл выполняется пока имеются исключаемые элементы
            {
                ind = SearchItem(m, s, a);
                if (ind != -1)
                {
                    m = RemoveItemIndex(m, s, ind);
                    s--;
                }
            } while (ind != -1);

            break;

        case 12: //Вывод массив
            DisplayArray(m, s);
            break;

        default:
            break;
        }
        printf_s("Для продолжения нажмите любую клавишу...\n");
        _getch();
    }



    return 0;
}

int DisplayMenu(void)
{
    int s = 1;
    printf_s("%d. Выделить память под массив\n", s++);
    printf_s("%d. Заполнить массив случайными числами\n", s++);
    printf_s("%d. Ввести массив с клавиатуры\n", s++);
    printf_s("%d. Добавить элемент массива в конец\n", s++);
    printf_s("%d. Добавить элемент массива в начало\n", s++);
    printf_s("%d. Добавить элемент массива на k-ую позицию\n", s++);
    printf_s("%d. Добавить элемент после искомого значения\n", s++);
    printf_s("%d. Удалить последний элемент массива\n", s++);
    printf_s("%d. Удалить первый элемент массива\n", s++);
    printf_s("%d. Удалить k-ый элемент массива\n", s++);
    printf_s("%d. Удалить элементы массива с указанным значением\n", s++);
    printf_s("%d. Вывод массив\n", s++);
    printf_s("%d. Выход\n", s++);
    printf_s("--------------------------------------------------------\n");
    printf_s("Выберете пункт меню: ");
    scanf_s("%d", &s);
    return s;
}

//выделение памяти под массив
double* CreateArray(double* m, int size_m)
{
    if (size_m < 0) return m; //не выделять память если размер отрицательный
    if (m != NULL) delete m;  //если массив уже был создан, то его нужно сначала удалить
    m = new double[size_m];   //само выделение памяти
    return m;
}

//ввод массива с клавы
int InputArray(double* m, int size_m)
{
    if (m == NULL) return 1;
    for (int i = 0; i < size_m; i++)
    {
        printf_s("%d: ", i);
        scanf_s("%lf", &m[i]);
    }
    return 0;
}

//задание элементов массива случаными чсиалми от 0 до 9
int RandArray(double* m, int size_m)
{
    if (m == NULL) return 1;
    for(int i=0; i<size_m; i++)
        m[i] = rand() % 10;
    return 0;
}

//копирование значений элементов массива из source в target
int CopyArray(double* source, double* target, int size_m)
{
    if (source == NULL || target == NULL) return 1;
    for (int i = 0; i < size_m; i++)
        target[i] = source[i];
    return 0;
}

//добавление элемента массива
double* AddItem(double *m, int size_m, double item, int index)
{
    if (m == NULL) return m;
    double* t = new double[size_m + 1];
    CopyArray(m, t, index);
    t[index] = item;
    CopyArray(m + index, t + index + 1, size_m - index + 1);
    delete m;
    return t;
}

//удаление массива с заданным индексом (номер по порядку, начиная с 0)
double* RemoveItemIndex(double* m, int size_m, int index)
{
    if (m == NULL || index < 0 || index >= size_m) return m;
    double* t = new double[size_m + 1];
    CopyArray(m, t, index);
    CopyArray(m+index+1, t+index, size_m - index);
    delete m;
    return t;
}

//поиск элемента массива
int SearchItem(double* m, int size_m, double item)
{
    if (m == NULL || size_m < 0) return -1;
    int i=0;
    while (m[i] != item && i < size_m) i++;
    if (i >= size_m) i = -1;
    return i;
}

//вывод массива
void DisplayArray(double* m, int size_m)
{
    if (m == NULL || size_m < 0) return;
    for (int i = 0; i < size_m; i++)
        printf_s("%lf\t", m[i]);
    printf_s("\n");
    return;
}