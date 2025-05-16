#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>

using namespace std;

// Структури даних

// Структура для продуктів
struct Product {
    string name;
    string category;
    double price;
    int quantity;
};

// Структура для співробітників
struct Employee {
    string name;
    string position;
    double salary;
};

// Структура для клієнтів
struct Client {
    string name;
    string contact;
    double total_spent;
};

// Функції для роботи з продуктами

// Показати всі продукти
void view_products(Product* products, int count) {
    if (count == 0) {
        cout << "Немає продуктів у базі.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        cout << "Назва: " << products[i].name << "\n"
            << "Категорія: " << products[i].category << "\n"
            << "Ціна: " << products[i].price << "\n"
            << "Кількість: " << products[i].quantity << "\n"
            << "----------------------------------------\n";
    }
}

// Додати новий продукт
void add_product(Product*& products, int& count) {
    Product new_product;
    cout << "Введіть назву продукту: ";
    getline(cin, new_product.name);
    cout << "Введіть категорію продукту: ";
    getline(cin, new_product.category);
    cout << "Введіть ціну продукту: ";
    cin >> new_product.price;
    cout << "Введіть кількість продукту: ";
    cin >> new_product.quantity;
    cin.ignore();  // очищаємо буфер

    Product* temp = new Product[count + 1];
    for (int i = 0; i < count; i++) {
        temp[i] = products[i];
    }
    temp[count] = new_product;
    delete[] products;
    products = temp;
    count++;
    cout << "Продукт додано до бази.\n";
}

// Оновити продукт
void update_product(Product* products, int count) {
    string name;
    cout << "Назва продукту для оновлення: ";
    getline(cin, name);

    for (int i = 0; i < count; i++) {
        if (products[i].name == name) {
            cout << "1. Нова ціна\n2. Нова кількість\nВаш вибір: ";
            int option;
            cin >> option;

            if (option == 1) {
                cout << "Нова ціна: ";
                cin >> products[i].price;
            }
            else if (option == 2) {
                cout << "Нова кількість: ";
                cin >> products[i].quantity;
            }
            else {
                cout << "Невірний вибір.\n";
            }
            cin.ignore();
            return;
        }
    }
    cout << "Продукт не знайдено.\n";
}

// Видалити продукт
void delete_product(Product*& products, int& count) {
    string name;
    cout << "Назва продукту для видалення: ";
    getline(cin, name);

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (products[i].name == name) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Продукт не знайдено.\n";
        return;
    }

    Product* temp = new Product[count - 1];
    for (int i = 0, j = 0; i < count; i++) {
        if (i != index) {
            temp[j++] = products[i];
        }
    }

    delete[] products;
    products = temp;
    count--;

    cout << "Продукт видалено.\n";
}

// Збереження продуктів у файл
void save_products_to_file(Product* products, int count) {
    ofstream file("products.txt");
    for (int i = 0; i < count; i++) {
        file << products[i].name << "\n"
            << products[i].category << "\n"
            << products[i].price << "\n"
            << products[i].quantity << "\n";
    }
    cout << "Продукти збережено у файл.\n";
}

// Завантаження продуктів з файлу
void load_products_from_file(Product*& products, int& count) {
    ifstream file("products.txt");
    string line;
    while (getline(file, line)) {
        Product new_product;
        new_product.name = line;
        getline(file, new_product.category);
        file >> new_product.price;
        file >> new_product.quantity;
        file.ignore();

        Product* temp = new Product[count + 1];
        for (int i = 0; i < count; i++) {
            temp[i] = products[i];
        }
        temp[count] = new_product;
        delete[] products;
        products = temp;
        count++;
    }
    cout << "Продукти завантажено з файлу.\n";
}

// Пошук продукту
void find_product(Product* products, int count) {
    string name;
    cout << "Введіть назву продукту для пошуку: ";
    getline(cin, name);

    for (int i = 0; i < count; i++) {
        if (products[i].name == name) {
            cout << "Продукт знайдено: \n";
            cout << "Назва: " << products[i].name << "\n"
                << "Категорія: " << products[i].category << "\n"
                << "Ціна: " << products[i].price << "\n"
                << "Кількість: " << products[i].quantity << "\n";
            return;
        }
    }
    cout << "Продукт не знайдено.\n";
}

// Функції для роботи з співробітниками

// Додати нового співробітника
void add_employee(Employee*& employees, int& emp_count) {
    Employee new_employee;
    cout << "Введіть ім'я співробітника: ";
    getline(cin, new_employee.name);
    cout << "Введіть посаду співробітника: ";
    getline(cin, new_employee.position);
    cout << "Введіть зарплату співробітника: ";
    cin >> new_employee.salary;
    cin.ignore();

    Employee* temp = new Employee[emp_count + 1];
    for (int i = 0; i < emp_count; i++) {
        temp[i] = employees[i];
    }
    temp[emp_count] = new_employee;
    delete[] employees;
    employees = temp;
    emp_count++;
    cout << "Співробітник доданий.\n";
}

// Переглянути всіх співробітників
void view_employees(Employee* employees, int emp_count) {
    if (emp_count == 0) {
        cout << "Немає співробітників.\n";
        return;
    }
    for (int i = 0; i < emp_count; i++) {
        cout << "Ім'я: " << employees[i].name << "\n"
            << "Посада: " << employees[i].position << "\n"
            << "Зарплата: " << employees[i].salary << "\n";
    }
}

// Функції для роботи з клієнтами

// Додати нового клієнта
void add_client(Client*& clients, int& client_count) {
    Client new_client;
    cout << "Введіть ім'я клієнта: ";
    getline(cin, new_client.name);
    cout << "Введіть контакт клієнта: ";
    getline(cin, new_client.contact);
    cout << "Введіть загальні витрати клієнта: ";
    cin >> new_client.total_spent;
    cin.ignore();

    Client* temp = new Client[client_count + 1];
    for (int i = 0; i < client_count; i++) {
        temp[i] = clients[i];
    }
    temp[client_count] = new_client;
    delete[] clients;
    clients = temp;
    client_count++;
    cout << "Клієнт доданий.\n";
}

// Переглянути всіх клієнтів
void view_clients(Client* clients, int client_count) {
    if (client_count == 0) {
        cout << "Немає клієнтів.\n";
        return;
    }
    for (int i = 0; i < client_count; i++) {
        cout << "Ім'я: " << clients[i].name << "\n"
            << "Контакт: " << clients[i].contact << "\n"
            << "Загальні витрати: " << clients[i].total_spent << "\n";
    }
}

// Показати меню
void show_menu() {
    cout << "\nМеню:\n";
    cout << "1. Переглянути всі продукти\n";
    cout << "2. Додати новий продукт\n";
    cout << "3. Знайти продукт за назвою\n";
    cout << "4. Оновити продукт\n";
    cout << "5. Видалити продукт\n";
    cout << "6. Зберегти у файл (Продукти)\n";
    cout << "7. Переглянути співробітників\n";
    cout << "8. Додати нового співробітника\n";
    cout << "9. Переглянути клієнтів\n";
    cout << "10. Додати нового клієнта\n";
    cout << "11. Вийти\n";
    cout << "Ваш вибір: ";
}

// Головна функція
int main() {
    // Завдання коду для правильної роботи кодування
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);

    Product* products = nullptr;
    int count = 0;
    Employee* employees = nullptr;
    int emp_count = 0;
    Client* clients = nullptr;
    int client_count = 0;

    // Завантаження продуктів при старті програми
    load_products_from_file(products, count);

    int choice;
    while (true) {
        show_menu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            view_products(products, count);
            break;
        case 2:
            add_product(products, count);
            break;
        case 3:
            find_product(products, count);
            break;
        case 4:
            update_product(products, count);
            break;
        case 5:
            delete_product(products, count);
            break;
        case 6:
            save_products_to_file(products, count);
            break;
        case 7:
            view_employees(employees, emp_count);
            break;
        case 8:
            add_employee(employees, emp_count);
            break;
        case 9:
            view_clients(clients, client_count);
            break;
        case 10:
            add_client(clients, client_count);
            break;
        case 11:
            save_products_to_file(products, count);
            delete[] products;
            delete[] employees;
            delete[] clients;
            cout << "Програма завершена.\n";
            return 0;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }
}
