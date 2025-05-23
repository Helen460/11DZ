#include "lib.h" // Підключення власного заголовочного файлу, який містить прототипи функцій, оголошення структур, функцій, кольорів

int main() {
    SetConsoleCP(1251);           // Встановлення кодування вводу в консолі
    SetConsoleOutputCP(1251);     // Встановлення кодування виводу в консолі

    Product* products = nullptr;  // Вказівник на масив продуктів, спочатку не виділено пам’ять
    int pc = 0;                   // Кількість продуктів (product count)

    Employee* employees = nullptr; // Вказівник на масив співробітників
    int ec = 0;                    // Кількість співробітників (employee count)

    load_products_from_file(products, pc);     // Завантаження продуктів з файлу в масив
    load_employees_from_file(employees, ec);   // Завантаження співробітників з файлу в масив

    while (true) { // Нескінченний цикл для роботи головного меню
        system("cls"); // Очищення екрану

        // Вивід заголовку програми в заданій позиції 
        show_text(5, 1, Color::YELLOW, "Консольний застосунок — База даних магазину продуктів та його співробітників");
        show_menu(); // Виведення головного меню

        int choice;     // Змінна для вибору користувача
        cin >> choice;  // Зчитування вибору
        cin.ignore();   // Очищення буфера після вводу

        // Обробка вибору користувача
        switch (choice) {
        case 1: view_products(products, pc);         break; // Перегляд усіх продуктів
        case 2: add_product(products, pc);           break; // Додавання нового продукту
        case 3: find_product(products, pc);          break; // Пошук продукту
        case 4: update_product(products, pc);        break; // Редагування даних продукту
        case 5: delete_product(products, pc);        break; // Видалення продукту
        case 6: save_products_to_file(products, pc); break; // Збереження продуктів у файл
        case 7: view_employees(employees, ec);       break; // Перегляд усіх співробітників
        case 8: add_employee(employees, ec);         break; // Додавання нового співробітника
        case 9: update_employee(employees, ec);      break; // Редагування даних співробітника
        case 10:delete_employee(employees, ec);      break; // Видалення співробітника
        case 11:save_employees_to_file(employees, ec); break; // Збереження співробітників у файл

        case 12:
            // Збереження всіх даних перед виходом з програми
            save_products_to_file(products, pc);
            save_employees_to_file(employees, ec);
            delete[] products;    // Звільнення динамічної пам’яті, виділеної під продукти
            delete[] employees;  // Звільнення пам’яті, виділеної під співробітників
            return 0;            // Завершення програми

        default:
            cout << "Невірний вибір.\n"; // Повідомлення про неправильний ввід
        }

        pause(); // Очікування натискання клавіші користувачем перед продовженням
    }
}
