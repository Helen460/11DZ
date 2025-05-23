#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <stdio.h>

using namespace std;

// ================= ��������� ����ֲ� =================

// ������� ��� ��������� �������� ������ �� �������� ������
void SetColor(int text, int background); // ������������ ������� ������ �� ����
void ClearConsole();                     // �������� ������

// ������� ������ � ����
void ShowMainMenu();        // ��������� ��������� ����
void ShowProductMenu();     // ��������� ���� ��������� ����������
void ShowEmployeeMenu();    // ��������� ���� ��������� �������������

// ������� ������ � ������� ��������
void AddProduct();              // ��������� ������ ��������
void ShowProducts();            // ��������� ������ ��������
void EditProduct();             // ����������� ���������� ��� �������
void DeleteProduct();           // ��������� �������� � ������
void SaveProductsToFile();      // ���������� ������ �������� � ����
void LoadProductsFromFile();    // ������������ ������ �������� � �����

// ������� ������ � ������� �����������
void AddEmployee();              // ��������� ������ �����������
void ShowEmployees();            // ��������� ������ �����������
void EditEmployee();             // ����������� ���������� ��� �����������
void DeleteEmployee();           // ��������� ����������� � ������
void SaveEmployeesToFile();      // ���������� ������ ����������� � ����
void LoadEmployeesFromFile();    // ������������ ������ ����������� � �����

// ������� ��� �������� ���������� ��������
void InputString(char* str, int size);          // �������� ���������� ����� � ���������
int InputInt();                                 // �������� ���������� ������ �����
float InputFloat();                             // �������� ���������� ��������� �����

// ������� ��� ��������� ��������
void Pause();                   // ������������ ��������� �������� �� ���������� ������
void PrintLine(int length);    // ��������� ������������� ��
void WaitForKey();             // ���������� ���������� ������

// ������ ������� ��� ������
enum class Color : unsigned short {
    BLACK, DARKBLUE, DARKGREEN, TURQUOISE, DARKRED,
    PURPLE, DARKYELLOW, GREY, DARKGREY, BLUE,
    GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
};

// ������� ��� ������ ������ � ����� ������� �� ������
void show_text(int x, int y, Color color, const string& text) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { SHORT(x), SHORT(y) };
    SetConsoleCursorPosition(h, pos);
    SetConsoleTextAttribute(h, (WORD)color);
    cout << text;
    SetConsoleTextAttribute(h, (WORD)Color::WHITE);
}

// ��������� ��� ����� ��������
struct Product {
    string name;
    string category;
    double price;
    int quantity;
};

// ��������� ��� ����� �����������
struct Employee {
    string name;
    string position;
    double salary;
    string phone;
    string birthday;
};

// ������� �������� � ����� ���������� ������ Enter
void pause() {
    cout << "\n�������� Enter ��� �����������...";
    _getch();
}

// ====== ���������� �� ������������ ������Ҳ� ======

// ������ �� �������� � ����
void save_products_to_file(Product* products, int count) {
    FILE* f;
    if (fopen_s(&f, "products.txt", "w") != 0 || !f) {
        cout << "�� ������� ������� products.txt ��� ������.\n";
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

// ��������� �� �������� � �����
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

// ====== ���������� �� ������������ �ϲ��������ʲ� ======

// ������ ��� ����������� � ����
void save_employees_to_file(Employee* emps, int count) {
    FILE* f;
    if (fopen_s(&f, "employees.txt", "w") != 0 || !f) {
        cout << "�� ������� ������� employees.txt ��� ������.\n";
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

// ��������� ��� ����������� � �����
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

// ====== �����ֲ� � ���������� ======

// ���� ����� �������
void add_product(Product*& products, int& count) {
    Product p;
    cout << "������ ����� ��������: ";      getline(cin, p.name);
    cout << "������ �������� ��������: "; getline(cin, p.category);
    cout << "������ ���� ��������: ";      cin >> p.price;
    cout << "������ ������� ��������: "; cin >> p.quantity; cin.ignore();
    Product* nt = new Product[count + 1];
    for (int i = 0; i < count; i++) nt[i] = products[i];
    nt[count++] = p;
    delete[] products;
    products = nt;
    cout << "������� ������.\n";
}

// �������� ������ ��� ��������
void view_products(Product* products, int count) {
    if (!products || count == 0) {
        cout << "���� �������� � ���.\n";  return;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::YELLOW);
    cout << "\n������ ������Ҳ�:\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::CYAN);
    cout << left << setw(25) << "�����"
        << setw(25) << "��������"
        << setw(12) << "ֳ��"
        << setw(12) << "ʳ������" << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::WHITE);
    for (int i = 0; i < count; i++) {
        cout << left << setw(25) << products[i].name
            << setw(25) << products[i].category
            << setw(12) << fixed << setprecision(2) << products[i].price
            << setw(12) << products[i].quantity << "\n";
    }
}

// ����� �������� �� ������
void find_product(Product* products, int count) {
    string key;
    cout << "������ ����� �������� ��� ������: "; getline(cin, key);
    for (int i = 0; i < count; i++) {
        if (products[i].name == key) {
            cout << "��������:\n"
                << "��������: " << products[i].category << "\n"
                << "ֳ��: " << products[i].price << "\n"
                << "ʳ������: " << products[i].quantity << "\n";
            return;
        }
    }
    cout << "������� �� ��������.\n";
}

// ��������� ���� ��� ������� ��������
void update_product(Product* products, int count) {
    string key;
    cout << "������ ����� �������� ��� ���������: "; getline(cin, key);
    for (int i = 0; i < count; i++) {
        if (products[i].name == key) {
            cout << "1. ������ ����\n2. ������ �������\n��� ����: ";
            int choice; cin >> choice;
            if (choice == 1) { cout << "���� ����: ";      cin >> products[i].price; }
            else { cout << "���� �������: "; cin >> products[i].quantity; }
            cin.ignore();
            return;
        }
    }
    cout << "������� �� ��������.\n";
}

// ������� ������� � ����
void delete_product(Product*& products, int& count) {
    string key;
    cout << "������ ����� �������� ��� ���������: "; getline(cin, key);
    int idx = -1;
    for (int i = 0; i < count; i++) if (products[i].name == key) { idx = i; break; }
    if (idx < 0) { cout << "������� �� ��������.\n"; return; }
    Product* nt = new Product[count - 1];
    for (int i = 0, j = 0; i < count; i++) if (i != idx) nt[j++] = products[i];
    delete[] products;
    products = nt;
    count--;
}

// ====== �����ֲ� ǲ �ϲ������������ ======

// ���� ������ �����������
void add_employee(Employee*& emps, int& count) {
    Employee e;
    cout << "������ ϲ�: "; getline(cin, e.name);
    cout << "������ ������: "; getline(cin, e.position);
    cout << "������ ��������: "; cin >> e.salary; cin.ignore();
    cout << "������ ����� ��������: "; getline(cin, e.phone);
    cout << "������ ���� ����������: "; getline(cin, e.birthday);
    Employee* nt = new Employee[count + 1];
    for (int i = 0; i < count; i++) nt[i] = emps[i];
    nt[count++] = e;
    delete[] emps;
    emps = nt;
}

// �������� ������ ��� �����������
void view_employees(Employee* emps, int count) {
    if (!emps || count == 0) {
        cout << "���� ����������� � ���.\n"; return;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::YELLOW);
    cout << "\n������ �ϲ��������ʲ�:\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::CYAN);
    cout << left
        << setw(25) << "ϲ�"
        << setw(20) << "������"
        << setw(12) << "��������"
        << setw(18) << "�������"
        << setw(15) << "���� ����������"
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

// ������� ��� �����������
void update_employee(Employee* emps, int count) {
    string key;
    cout << "������ ϲ� ����������� ��� ���������: "; getline(cin, key);
    for (int i = 0; i < count; i++) {
        if (emps[i].name == key) {
            cout << "1. ������ ������\n2. ������ ��������\n3. ������ �������\n4. ������ ���� ����������\n��� ����: ";
            int c; cin >> c; cin.ignore();
            switch (c) {
            case 1: cout << "���� ������: "; getline(cin, emps[i].position); break;
            case 2: cout << "���� ��������: "; cin >> emps[i].salary; cin.ignore(); break;
            case 3: cout << "����� �������: "; getline(cin, emps[i].phone); break;
            case 4: cout << "���� ���� ����������: "; getline(cin, emps[i].birthday); break;
            default: cout << "������� ����.\n"; return;
            }
            return;
        }
    }
    cout << "����������� �� ��������.\n";
}

// ������� ����������� � ����
void delete_employee(Employee*& emps, int& count) {
    string key;
    cout << "������ ϲ� ����������� ��� ���������: "; getline(cin, key);
    int idx = -1;
    for (int i = 0; i < count; i++) if (emps[i].name == key) { idx = i; break; }
    if (idx < 0) { cout << "����������� �� ��������.\n"; return; }
    Employee* nt = new Employee[count - 1];
    for (int i = 0, j = 0; i < count; i++) if (i != idx) nt[j++] = emps[i];
    delete[] emps;
    emps = nt;
    count--;
}

// ===== ���� �� main =====

void show_menu() {
    show_text(0, 3, Color::YELLOW, "====== ���� ======");
    show_text(0, 4, Color::GREEN, "1. ����������� ��������");
    show_text(0, 5, Color::GREEN, "2. ������ �������");
    show_text(0, 6, Color::GREEN, "3. ������ �������");
    show_text(0, 7, Color::GREEN, "4. ������� �������");
    show_text(0, 8, Color::GREEN, "5. �������� �������");
    show_text(0, 9, Color::GREEN, "6. �������� �������� � ����");
    show_text(0, 10, Color::CYAN, "7. ����������� �����������");
    show_text(0, 11, Color::CYAN, "8. ������ �����������");
    show_text(0, 12, Color::CYAN, "9. ������� �����������");
    show_text(0, 13, Color::CYAN, "10. �������� �����������");
    show_text(0, 14, Color::CYAN, "11. �������� ����������� � ����");
    show_text(0, 15, Color::RED, "12. �����");
    show_text(0, 16, Color::YELLOW, "��� ����: ");
}

