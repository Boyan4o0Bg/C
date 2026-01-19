#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Структура за лекарство
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Medicine;

Medicine medicines[MAX];
int count = 0;

// Функция за зареждане на лекарства от файл
void loadFromFile() {
    FILE *file = fopen("medicines.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, "%d %s %f %d",
                  &medicines[count].id,
                  medicines[count].name,
                  &medicines[count].price,
                  &medicines[count].quantity) != EOF) {
        count++;
    }
    fclose(file);
}

// Функция за запис във файл
void saveToFile() {
    FILE *file = fopen("medicines.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %.2f %d\n",
                medicines[i].id,
                medicines[i].name,
                medicines[i].price,
                medicines[i].quantity);
    }
    fclose(file);
}

// Добавяне на лекарство
void addMedicine() {
    Medicine m;
    printf("ID: ");
    scanf("%d", &m.id);
    printf("Name: ");
    scanf("%s", m.name);
    printf("Price: ");
    scanf("%f", &m.price);
    printf("Quantity: ");
    scanf("%d", &m.quantity);

    medicines[count++] = m;
    saveToFile();
    printf("Medicine added successfully!\n");
}

// Показване на всички лекарства
void displayMedicines() {
    printf("\n--- Medicines List ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
               medicines[i].id,
               medicines[i].name,
               medicines[i].price,
               medicines[i].quantity);
    }
}

// Търсене по име
void searchMedicine() {
    char name[50];
    printf("Enter medicine name: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(medicines[i].name, name) == 0) {
            printf("Found: %s | Price: %.2f | Quantity: %d\n",
                   medicines[i].name,
                   medicines[i].price,
                   medicines[i].quantity);
            return;
        }
    }
    printf("Medicine not found!\n");
}

// Продажба на лекарство
void sellMedicine() {
    int id, qty;
    printf("Enter medicine ID: ");
    scanf("%d", &id);
    printf("Enter quantity: ");
    scanf("%d", &qty);

    for (int i = 0; i < count; i++) {
        if (medicines[i].id == id) {
            if (medicines[i].quantity >= qty) {
                medicines[i].quantity -= qty;
                float total = qty * medicines[i].price;

                FILE *sales = fopen("sales.txt", "a");
                fprintf(sales, "Sold %d of %s - Total: %.2f\n",
                        qty, medicines[i].name, total);
                fclose(sales);

                saveToFile();
                printf("Sale successful! Total price: %.2f\n", total);
            } else {
                printf("Not enough stock!\n");
            }
            return;
        }
    }
    printf("Medicine not found!\n");
}

// Главно меню
void menu() {
    int choice;
    do {
        printf("\n--- Pharmacy Management System ---\n");
        printf("1. Add Medicine\n");
        printf("2. Display Medicines\n");
        printf("3. Search Medicine\n");
        printf("4. Sell Medicine\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMedicine(); break;
            case 2: displayMedicines(); break;
            case 3: searchMedicine(); break;
            case 4: sellMedicine(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

int main() {
    loadFromFile();
    menu();
    return 0;
}