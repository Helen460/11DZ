#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <stdio.h>

using namespace std;

// ================= ПРОТОТИПИ ФУНКЦІЙ =================

// Функції для керування кольором тексту та очищення консолі
void SetColor(int text, int background); // Встановлення кольору тексту та фону
void ClearConsole();                     // Очищення консолі

// Функції роботи з меню
void ShowMainMenu();        // Виведення головного меню
void ShowProductMenu();     // Виведення меню керування продуктами
void ShowEmployeeMenu();    // Виведення меню керування співробітниками

// Функції роботи з масивом продуктів
void AddProduct();              // Додавання нового продукту
void ShowProducts();            // Виведення списку продуктів
void EditProduct();             // Редагування інформації про продукт
void DeleteProduct();           // Видалення продукту зі списку
void SaveProductsToFile();      // Збереження списку продуктів у файл
void LoadProductsFromFile();    // Завантаження списку продуктів з файлу

// Функції роботи з масивом співробітників
void AddEmployee();              // Додавання нового співробітника
void ShowEmployees();            // Виведення списку співробітників
void EditEmployee();             // Редагування інформації про співробітника
void DeleteEmployee();           // Видалення співробітника зі списку
void SaveEmployeesToFile();      // Збереження списку співробітників у файл
void LoadEmployeesFromFile();    // Завантаження списку співробітників з файлу

// Функції для перевірки коректності введення
void InputString(char* str, int size);          // Безпечне зчитування рядка з клавіатури
int InputInt();                                 // Безпечне зчитування цілого числа
float InputFloat();                             // Безпечне зчитування дробового числа

// Функції для службових операцій
void Pause();                   // Призупинення виконання програми до натискання клавіші
void PrintLine(int length);    // Виведення горизонтальної лінії
void WaitForKey();             // Очікування натискання клавіші

// Перелік кольорів для тексту
enum class Color : unsigned short {
    BLACK, DARKBLUE, DARKGREEN, TURQUOISE, DARKRED,
    PURPLE, DARKYELLOW, GREY, DARKGREY, BLUE,
    GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
};

// Функція для виводу тексту у певній позиції та кольорі
void show_text(int x, int y, Color color, const string& text) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { SHORT(x), SHORT(y) };
    SetConsoleCursorPosition(h, pos);
    SetConsoleTextAttribute(h, (WORD)color);
    cout << text;
    SetConsoleTextAttribute(h, (WORD)Color::WHITE);
}

// Структура для опису продукту
struct Product {
    string name;
    string category;
    double price;
    int quantity;
};

// Структура для опису співробітника
struct Employee {
    string name;
    string position;
    double salary;
    string phone;
    string birthday;
};

// Функція затримки — очікує натискання клавіші Enter
void pause() {
    cout << "\nНатисніть Enter для продовження...";
    _getch();
}

// ====== ЗБЕРЕЖЕННЯ ТА ЗАВАНТАЖЕННЯ ПРОДУКТІВ ======

// Зберігає всі продукти у файл
void save_products_to_file(Product* products, int count) {
    FILE* f;
    if (fopen_s(&f, "products.txt", "w") != 0 || !f) {
        cout << "Не вдалося відкрити products.txt для запису.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s\n%s\n%.2f\n%d\n",
            products[i].name.c_str(),
            products[i].category.c_str(),
            products[i].price,
            products[i].quantity);
    }
    fclose(f);
}

// Завантажує всі продукти з файлу
void load_products_from_file(Product*& products, int& count) {
    FILE* f;
    if (fopen_s(&f, "products.txt", "r") != 0 || !f) {
        products = nullptr;
        count = 0;
        return;
    }
    count = 0;
    Product* temp = nullptr;
    char name[128], category[128];
    double price;
    int quantity;
    while (fscanf_s(f, " %127[^\n] \n", name, (unsigned)sizeof(name)) == 1 &&
        fscanf_s(f, " %127[^\n] \n", category, (unsigned)sizeof(category)) == 1 &&
        fscanf_s(f, " %lf\n", &price) == 1 &&
        fscanf_s(f, " %d\n", &quantity) == 1) {
        Product p;
        p.name = name;
        p.category = category;
        p.price = price;
        p.quantity = quantity;
        Product* nt = new Product[count + 1];
        for (int i = 0; i < count; i++) nt[i] = temp[i];
        nt[count++] = p;
        delete[] temp;
        temp = nt;
    }
    fclose(f);
    products = temp;
}

// ====== ЗБЕРЕЖЕННЯ ТА ЗАВАНТАЖЕННЯ СПІВРОБІТНИКІВ ======

// Зберігає всіх співробітників у файл
void save_employees_to_file(Employee* emps, int count) {
    FILE* f;
    if (fopen_s(&f, "employees.txt", "w") != 0 || !f) {
        cout << "Не вдалося відкрити employees.txt для запису.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s\n%s\n%.2f\n%s\n%s\n",
            emps[i].name.c_str(),
            emps[i].position.c_str(),
            emps[i].salary,
            emps[i].phone.c_str(),
            emps[i].birthday.c_str());
    }
    fclose(f);
}

// Завантажує всіх співробітників з файлу
void load_employees_from_file(Employee*& emps, int& count) {
    FILE* f;
    if (fopen_s(&f, "employees.txt", "r") != 0 || !f) {
        emps = nullptr;
        count = 0;
        return;
    }
    count = 0;
    Employee* temp = nullptr;
    char name[128], position[128], phone[128], birthday[128];
    double salary;
    while (fscanf_s(f, " %127[^\n] \n", name, (unsigned)sizeof(name)) == 1 &&
        fscanf_s(f, " %127[^\n] \n", position, (unsigned)sizeof(position)) == 1 &&
        fscanf_s(f, " %lf\n", &salary) == 1 &&
        fscanf_s(f, " %127[^\n] \n", phone, (unsigned)sizeof(phone)) == 1 &&
        fscanf_s(f, " %127[^\n] \n", birthday, (unsigned)sizeof(birthday)) == 1) {
        Employee e;
        e.name = name;
        e.position = position;
        e.salary = salary;
        e.phone = phone;
        e.birthday = birthday;
        Employee* nt = new Employee[count + 1];
        for (int i = 0; i < count; i++) nt[i] = temp[i];
        nt[count++] = e;
        delete[] temp;
        temp = nt;
    }
    fclose(f);
    emps = temp;
}

// ====== ОПЕРАЦІЇ З ПРОДУКТАМИ ======

// Додає новий продукт
void add_product(Product*& products, int& count) {
    Product p;
    cout << "Введіть назву продукту: ";      getline(cin, p.name);
    cout << "Введіть категорію продукту: "; getline(cin, p.category);
    cout << "Введіть ціну продукту: ";      cin >> p.price;
    cout << "Введіть кількість продуктів: "; cin >> p.quantity; cin.ignore();
    Product* nt = new Product[count + 1];
    for (int i = 0; i < count; i++) nt[i] = products[i];
    nt[count++] = p;
    delete[] products;
    products = nt;
    cout << "Продукт додано.\n";
}

// Виводить список усіх продуктів
void view_products(Product* products, int count) {
    if (!products || count == 0) {
        cout << "Немає продуктів у базі.\n";  return;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::YELLOW);
    cout << "\nСПИСОК ПРОДУКТІВ:\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::CYAN);
    cout << left << setw(25) << "Назва"
        << setw(25) << "Категорія"
        << setw(12) << "Ціна"
        << setw(12) << "Кількість" << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::WHITE);
    for (int i = 0; i < count; i++) {
        cout << left << setw(25) << products[i].name
            << setw(25) << products[i].category
            << setw(12) << fixed << setprecision(2) << products[i].price
            << setw(12) << products[i].quantity << "\n";
    }
}

// Пошук продукту за назвою
void find_product(Product* products, int count) {
    string key;
    cout << "Введіть назву продукту для пошуку: "; getline(cin, key);
    for (int i = 0; i < count; i++) {
        if (products[i].name == key) {
            cout << "Знайдено:\n"
                << "Категорія: " << products[i].category << "\n"
                << "Ціна: " << products[i].price << "\n"
                << "Кількість: " << products[i].quantity << "\n";
            return;
        }
    }
    cout << "Продукт не знайдено.\n";
}

// Оновлення ціни або кількості продукту
void update_product(Product* products, int count) {
    string key;
    cout << "Введіть назву продукту для оновлення: "; getline(cin, key);
    for (int i = 0; i < count; i++) {
        if (products[i].name == key) {
            cout << "1. Змінити ціну\n2. Змінити кількість\nВаш вибір: ";
            int choice; cin >> choice;
            if (choice == 1) { cout << "Нова ціна: ";      cin >> products[i].price; }
            else { cout << "Нова кількість: "; cin >> products[i].quantity; }
            cin.ignore();
            return;
        }
    }
    cout << "Продукт не знайдено.\n";
}

// Видаляє продукт з бази
void delete_product(Product*& products, int& count) {
    string key;
    cout << "Введіть назву продукту для видалення: "; getline(cin, key);
    int idx = -1;
    for (int i = 0; i < count; i++) if (products[i].name == key) { idx = i; break; }
    if (idx < 0) { cout << "Продукт не знайдено.\n"; return; }
    Product* nt = new Product[count - 1];
    for (int i = 0, j = 0; i < count; i++) if (i != idx) nt[j++] = products[i];
    delete[] products;
    products = nt;
    count--;
}

// ====== ОПЕРАЦІЇ ЗІ СПІВРОБІТНИКАМИ ======

// Додає нового співробітника
void add_employee(Employee*& emps, int& count) {
    Employee e;
    cout << "Введіть ПІБ: "; getline(cin, e.name);
    cout << "Введіть посаду: "; getline(cin, e.position);
    cout << "Введіть зарплату: "; cin >> e.salary; cin.ignore();
    cout << "Введіть номер телефону: "; getline(cin, e.phone);
    cout << "Введіть Дату народження: "; getline(cin, e.birthday);
    Employee* nt = new Employee[count + 1];
    for (int i = 0; i < count; i++) nt[i] = emps[i];
    nt[count++] = e;
    delete[] emps;
    emps = nt;
}

// Виводить список усіх співробітників
void view_employees(Employee* emps, int count) {
    if (!emps || count == 0) {
        cout << "Немає співробітників у базі.\n"; return;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::YELLOW);
    cout << "\nСПИСОК СПІВРОБІТНИКІВ:\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::CYAN);
    cout << left
        << setw(25) << "ПІБ"
        << setw(20) << "Посада"
        << setw(12) << "Зарплата"
        << setw(18) << "Телефон"
        << setw(15) << "Дата народження"
        << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::WHITE);
    for (int i = 0; i < count; i++) {
        cout << left
            << setw(25) << emps[i].name
            << setw(20) << emps[i].position
            << setw(12) << fixed << setprecision(2) << emps[i].salary
            << setw(18) << emps[i].phone
            << setw(15) << emps[i].birthday
            << "\n";
    }
}

// Оновлює дані співробітника
void update_employee(Employee* emps, int count) {
    string key;
    cout << "Введіть ПІБ співробітника для оновлення: "; getline(cin, key);
    for (int i = 0; i < count; i++) {
        if (emps[i].name == key) {
            cout << "1. Змінити посаду\n2. Змінити зарплату\n3. Змінити телефон\n4. Змінити Дату народження\nВаш вибір: ";
            int c; cin >> c; cin.ignore();
            switch (c) {
            case 1: cout << "Нова посада: "; getline(cin, emps[i].position); break;
            case 2: cout << "Нова зарплата: "; cin >> emps[i].salary; cin.ignore(); break;
            case 3: cout << "Новий телефон: "; getline(cin, emps[i].phone); break;
            case 4: cout << "Нова Дата народження: "; getline(cin, emps[i].birthday); break;
            default: cout << "Невірний вибір.\n"; return;
            }
            return;
        }
    }
    cout << "Співробітника не знайдено.\n";
}

// Видаляє співробітника з бази
void delete_employee(Employee*& emps, int& count) {
    string key;
    cout << "Введіть ПІБ співробітника для видалення: "; getline(cin, key);
    int idx = -1;
    for (int i = 0; i < count; i++) if (emps[i].name == key) { idx = i; break; }
    if (idx < 0) { cout << "Співробітника не знайдено.\n"; return; }
    Employee* nt = new Employee[count - 1];
    for (int i = 0, j = 0; i < count; i++) if (i != idx) nt[j++] = emps[i];
    delete[] emps;
    emps = nt;
    count--;
}

// ===== Меню та main =====

void show_menu() {
    show_text(0, 3, Color::YELLOW, "====== МЕНЮ ======");
    show_text(0, 4, Color::GREEN, "1. Переглянути продукти");
    show_text(0, 5, Color::GREEN, "2. Додати продукт");
    show_text(0, 6, Color::GREEN, "3. Знайти продукт");
    show_text(0, 7, Color::GREEN, "4. Оновити продукт");
    show_text(0, 8, Color::GREEN, "5. Видалити продукт");
    show_text(0, 9, Color::GREEN, "6. Зберегти продукти у файл");
    show_text(0, 10, Color::CYAN, "7. Переглянути співробітників");
    show_text(0, 11, Color::CYAN, "8. Додати співробітника");
    show_text(0, 12, Color::CYAN, "9. Оновити співробітника");
    show_text(0, 13, Color::CYAN, "10. Видалити співробітника");
    show_text(0, 14, Color::CYAN, "11. Зберегти співробітників у файл");
    show_text(0, 15, Color::RED, "12. Вийти");
    show_text(0, 16, Color::YELLOW, "Ваш вибір: ");
}

