#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <string>

#pragma execution_character_set("utf-8") //Установка кодировки UTF-8 для текстов
using namespace std;

struct Event {
    string name;         //название мероприятия
    string date;         //дата мероприятия
    string place;        //место мероприятия
    double budget;       //бюджет
    int guests;          //количество гостей
} event;
const int MAX_EVENT = 4;

struct SortByName
{
    string name; // ключ
    int index;  // индекс в массиве
};

struct SortByBudget
{
    double budget;; // ключ
    int index;  // индекс в массиве
};

struct EventList
{
    Event event;
    EventList* next;
};

struct TreeNode
{
    int key; // ключевой атрибут для индексации: возраст
    int index; // номер элемента в массиве
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k, int i)
    {
        key = k;
        index = i;
        left = right = nullptr;
    }
};

void insertionSortByName(SortByName arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].name > arr[j + 1].name)
            {
                SortByName temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSortByBudget(SortByBudget arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].budget < arr[j + 1].budget)
            {
                SortByBudget temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void editBudget(Event event[], int arraySize, std::string nameToSearch, int newBudget)
{
    // Ищем индекс записи в массиве по имени
    int indexByName = -1;
    for (int i = 0; i < arraySize; i++)
    {
        if (event[i].name == nameToSearch)
        {
            indexByName = i;
            break;
        }
    }
    // Если запись по имени найдена, редактируем поле бюджета
    if (indexByName != -1)
    {
        event[indexByName].budget = newBudget;

        std::cout << "Line with name' '" << nameToSearch << "'  changed. New budget : " << newBudget << std::endl;
    }
    else
    {
        std::cout << "Line with name'" << nameToSearch << "' has not found." << std::endl;
    }
}

void editName(Event event[], int arraySize, std::string newName, int numberToSearch)
{
    // Ищем индекс записи в массиве по имени
    int indexByNumber = -1;
    for (int i = 0; i < arraySize; i++)
    {
        if (event[i].budget == numberToSearch)
        {
            indexByNumber = i;
            break;
        }
    }
    // Если запись по имени найдена, редактируем поле бюджета
    if (indexByNumber != -1)
    {
        event[indexByNumber].name = newName;

        std::cout << "Line with budget' '" << numberToSearch << "'  changed. New name : " << newName << std::endl;
    }
    else
    {
        std::cout << "Line with budget'" << numberToSearch << "' has not found." << std::endl;
    }
}

// Рекурсивная функция бинарного поиска по названию
int binarySearchByName(SortByName arr[], int left, int right, std::string key)
{
    if (right >= left)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid].name == key)
            return mid;

        if (arr[mid].name > key)
            return binarySearchByName(arr, left, mid - 1, key);

        return binarySearchByName(arr, mid + 1, right, key);
    }
    // Если элемент не найден
    return -1;
}

// Итеративная функция бинарного поиска по бюджету
int binarySearchByBudget(SortByBudget arr[], int n, int key)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid].budget == key)
            return mid;

        else if (arr[mid].budget < key)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

void inputData(Event event[], int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        cout << "Enter data for event " << i + 1 << ":" << endl;
        cout << "Name: ";
        cin.ignore();
        getline(cin, event[i].name);

        cout << "Date: ";
        getline(cin, event[i].date);

        cout << "Place: ";
        getline(cin, event[i].place);

        cout << "Budget: ";
        cin >> event[i].budget;

        cout << "Guests: ";
        cin >> event[i].guests;
        cout << endl;
    }
}
void outputData(Event event[], int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        cout << "Event " << i + 1 << ":\n";
        cout << "Name: " << event[i].name << ", Date: " << event[i].date << ", Place: " << event[i].place << ", Budget: " << event[i].budget << ", Guests: " << event[i].guests << endl << endl;
        //cout << "Date: " << event[i].date << endl;
        //cout << "Place: " << event[i].place << endl;
        //cout << "Budget: " << event[i].budget << endl;
        //cout << "Guests: " << event[i].guests << endl << endl;
    }
}

void deleteRec(Event event[], int arraySize, std::string nameToDelete)
{
    int deleteIndex = -1;

    // Найдем индекс записи в массиве по имени для удаления
    for (int i = 0; i < arraySize; i++)
    {
        if (event[i].name == nameToDelete)
        {
            deleteIndex = i;
            break;
        }
    }

    if (deleteIndex != -1)
    {
        // Сдвигаем элементы в массиве на одну позицию влево
        for (int i = deleteIndex; i < arraySize - 1; i++)
        {
            event[i] = event[i + 1];
        }

        std::cout << "Line with name '" << nameToDelete << "' deleted" << std::endl;
    }
    else
    {
        std::cout << " Line with name '" << nameToDelete << "' has not founded" << std::endl;
    }
}

//_______________________________________________ВТОРЯ ЧАСТЬ

void insert(TreeNode*& root, int key, int index)
{
    if (root == nullptr)
    {
        root = new TreeNode(key, index);
    }
    else if (key < root->key)
    {
        insert(root->left, key, index);
    }
    else
    {
        insert(root->right, key, index);
    }
}

void inOrderTree(TreeNode* root, Event event[])
{
    if (root == nullptr)
    {
        return;
    }

    inOrderTree(root->left, event);
    cout << "Name: " << event[root->index].name << ", Date: " << event[root->index].date << ", Place: " << event[root->index].place << ", Budget: " << event[root->index].budget << ", Guests: " << event[root->index].guests << endl << endl;
    inOrderTree(root->right, event);
}

void reverseOrderTree(TreeNode* root, Event event[])
{
    if (root == nullptr)
    {
        return;
    }
    reverseOrderTree(root->right, event);
    cout << "Name: " << event[root->index].name << ", Date: " << event[root->index].date << ", Place: " << event[root->index].place << ", Budget: " << event[root->index].budget << ", Guests: " << event[root->index].guests << endl << endl;
    reverseOrderTree(root->left, event);
}

void searchElement(TreeNode* root, Event event[], int key)
{
    if (root == nullptr)
    {
        cout << "Элемент не найден." << endl;
        return;
    }

    if (key == event[root->index].budget)
    {
        cout << "Элемент найден:" << endl;
        cout << "Name: " << event[root->index].name << ", Date: " << event[root->index].date << ", Place: " << event[root->index].place << ", Budget: " << event[root->index].budget << ", Guests: " << event[root->index].guests << endl << endl;
        return;
    }

    if (key < event[root->index].budget)
    {
        searchElement(root->left, event, key);
    }
    else
    {
        searchElement(root->right, event, key);
    }
}

void deleteNode(TreeNode*& root, int key, Event event[], int& size)
{
    if (root == nullptr)
    {
        cout << "Элемент не найден." << endl;
        return;
    }

    if (event[root->index].budget > key)
    {
        deleteNode(root->left, key, event, size);
    }
    else if (event[root->index].budget < key)
    {
        deleteNode(root->right, key, event, size);
    }
    else
    {
        if (root->left == nullptr)
        {
            TreeNode* temp = root->right;
            delete root;
            root = temp;
            size--;
        }
        else if (root->right == nullptr)
        {
            TreeNode* temp = root->left;
            delete root;
            root = temp;
            size--;
        }
        else
        {
            TreeNode* temp = root->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            root->index = temp->index;
            deleteNode(root->right, event[temp->index].budget, event, size);
        }
    }
}

void editRecord(TreeNode* root, Event events[], double key, const string& newName, const string& newDate, const string& newPlace, double newBudget, int newGuests)
{
    if (root == nullptr)
    {
        cout << "Элемент не найен." << endl;
        return;
    }

    if (key == events[root->index].budget)
    {
        events[root->index].name = newName;
        events[root->index].date = newDate;
        events[root->index].place = newPlace;
        events[root->index].budget = newBudget;
        events[root->index].guests = newGuests;

        cout << "Запись обновлена" << endl;
        return;
    }

    if (key < events[root->index].budget)
    {
        editRecord(root->left, events, key, newName, newDate, newPlace, newBudget, newGuests);
    }
    else
    {
        editRecord(root->right, events, key, newName, newDate, newPlace, newBudget, newGuests);
    }
}


//_______________________________________________ТРЕТЬЯ ЧАСТЬ

// Процедура просмотра элементов списка от головы к хвосту
void ListFromFirst(EventList* head)
{
    if (head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }
    while (head != nullptr)
    {
        //    Вывод информационного поля текущего элемента, на который указывает ссылка:	
        cout << "Name: " << head->event.name << ", Date: " << head->event.date << ", Place: " << head->event.place << ", Budget: " << head->event.budget << ", Guests: " << head->event.guests << " " << endl;
        head = head->next;//    Переход к следующему элементу по ссылке next в текущем элементе:
    }
}

// Процедура просмотра элементов списка от хвоста к голове (рекурсивно)
void ListFromEnd(EventList* head)
{
    if (head == nullptr)
    {
        return;
    }
    if (head != nullptr)
    {
        ListFromEnd(head->next);
        cout << "Name: " << head->event.name << ", Date: " << head->event.date << ", Place: " << head->event.place << ", Budget: " << head->event.budget << ", Guests: " << head->event.guests << " " << endl;
    }
}

void sortListByGuests(EventList*& head)
{
    if (head == nullptr || head->next == nullptr)
        return;

    EventList* i, * j;
    Event temp;

    for (i = head; i != nullptr; i = i->next)
    {
        for (j = i->next; j != nullptr; j = j->next)
        {
            if (i->event.guests > j->event.guests)
            {
                temp = i->event;
                i->event = j->event;
                j->event = temp;
            }
        }
    }
}

// Функция для сортировки списка по убыванию атрибута "place"
void sortListByPlace(EventList*& head)
{
    if (head == nullptr || head->next == nullptr)
        return;

    EventList* i, * j;
    Event temp;

    for (i = head; i != nullptr; i = i->next)
    {
        for (j = i->next; j != nullptr; j = j->next)
        {
            if (i->event.place < j->event.place)
            {
                temp = i->event;
                i->event = j->event;
                j->event = temp;
            }
        }
    }
}

void AddAndSortByGuests(EventList*& head, Event newEvent)
{
    EventList* newNode = new EventList;
    newNode->event = newEvent;
    newNode->next = nullptr;
    if (head == nullptr || head->event.guests >= event.guests)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        EventList* current = head;
        while (current->next != nullptr && current->next->event.guests < newEvent.guests)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    sortListByGuests(newNode);
}

// Функция для добавления новой записи в список с сортировкой по убыванию поля "place"
void AddAndSortByPlace(EventList*& head, Event newEvent)
{
    EventList* newNode = new EventList;
    newNode->event = newEvent;
    newNode->next = nullptr;

    if (head == nullptr || head->event.place <= newEvent.place)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        EventList* current = head;
        while (current->next != nullptr && current->next->event.place > event.place)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    sortListByPlace(newNode);
}

// Функция для поиска и вывода записи/записей с заданным значением атрибута "guests"
void searchByGuests(EventList* head, int purposeGuests)
{
    bool found = false;

    EventList* current = head;
    while (current != nullptr)
    {
        if (current->event.guests == purposeGuests)
        {
            found = true;
            cout << "Name: " << current->event.name << ", Date: " << current->event.date << ", Place: " << current->event.place << ", Budget: " << current->event.budget << ", Guests: " << current->event.guests << " " << endl;
        }
        current = current->next;
    }

    if (!found)
    {
        std::cout << "Запись с гостями " << purposeGuests << " не найдена." << std::endl;
    }
}

// Функция для поиска и вывода записи/записей с заданным значением атрибута "place"
void searchByPlace(EventList* head, string purposePlace)
{
    bool found = false;

    EventList* current = head;
    while (current != nullptr)
    {
        if (current->event.place == purposePlace)
        {
            found = true;
            cout << "Name: " << current->event.name << ", Date: " << current->event.date << ", Place: " << current->event.place << ", Budget: " << current->event.budget << ", Guests: " << current->event.guests << " " << endl;
        }
        current = current->next;
    }

    if (!found)
    {
        std::cout << "Запись с местом " << purposePlace << " не найдена." << std::endl;
    }
}

// Функция для удаления записи с заданным значением атрибута "guests"
void deleteByGuests(EventList*& head, int purposeGuests)
{
    EventList* current = head;
    EventList* previous = nullptr;

    while ((current != nullptr) && (current->event.guests != purposeGuests))
    {
        previous = current;
        current = current->next;
    }

    if (current != nullptr)
    {
        if (current == head)
        {
            head = current->next;
        }
        else
        {
            if (current->next == nullptr)
            {
                previous->next = nullptr;
            }
            else
            {
                previous->next = current->next;
            }
        }

        delete current;
        std::cout << "Запись с 'guests' = " << purposeGuests << " удалена." << std::endl;
    }
    else
    {
        std::cout << "Запись с 'guests' = " << purposeGuests << " не найдена." << std::endl;
    }
}

void deleteByPlace(EventList*& head, string purposePlace)
{
    EventList* current = head;
    EventList* previous = nullptr;

    while ((current != nullptr) && (current->event.place != purposePlace))
    {
        previous = current;
        current = current->next;
    }

    if (current != nullptr)
    {
        if (current == head)
        {
            head = current->next;
        }
        else
        {
            if (current->next == nullptr)
            {
                previous->next = nullptr;
            }
            else
            {
                previous->next = current->next;
            }
        }

        delete current;
        std::cout << "Запись с местом " << purposePlace << " удалена." << std::endl;
    }
    else
    {
        std::cout << "Запись с местом " << purposePlace << " не найдена." << std::endl;
    }
}

int main() {

    SetConsoleOutputCP(65001); //Установка кодировки UTF-8 для вывода в консоль
    int answer = 0;
    int choice = 0;
    struct Event events[MAX_EVENT];

    do {
        std::cout << " ------------------------ Г Л А В Н О Е   М Е Н Ю ------------------------ \n" << std::endl;
        std::cout << " 1. Первое задание (использование индексов-массивов)" << std::endl;
        std::cout << " 2. Второе задание (бинарное дерево)" << std::endl;
        std::cout << " 3. Третье задание (линейные списки)" << std::endl;
        std::cout << " 4. Выход \n" << std::endl;
        cin >> answer;

        switch (answer) {
        case 1: {
            struct SortByName sortedByNameEvent[MAX_EVENT];
            struct SortByBudget sortedByBudgetEvent[MAX_EVENT];

            //ТЕСТ №1
            events[0].name = "Christmas";
            events[0].date = "07.01.22";
            events[0].place = "Moscow";
            events[0].budget = 232000;
            events[0].guests = 30;
            sortedByNameEvent[0].name = events[0].name;
            sortedByNameEvent[0].index = 0;
            sortedByBudgetEvent[0].budget = events[0].budget;
            sortedByBudgetEvent[0].index = 0;

            events[1].name = "Wedding";
            events[1].date = "17.08.20";
            events[1].place = "Perm";
            events[1].budget = 500000;
            events[1].guests = 40;
            sortedByNameEvent[1].name = events[1].name;
            sortedByNameEvent[1].index = 1;
            sortedByBudgetEvent[1].budget = events[1].budget;
            sortedByBudgetEvent[1].index = 1;

            events[2].name = "Birthday";
            events[2].date = "11.10.24";
            events[2].place = "Kungur";
            events[2].budget = 20000;
            events[2].guests = 10;
            sortedByNameEvent[2].name = events[2].name;
            sortedByNameEvent[2].index = 2;
            sortedByBudgetEvent[2].budget = events[2].budget;
            sortedByBudgetEvent[2].index = 2;

            events[3].name = "Victory Day";
            events[3].date = "09.05.24";
            events[3].place = "Saint Petersburg";
            events[3].budget = 600000;
            events[3].guests = 100;
            sortedByNameEvent[3].name = events[3].name;
            sortedByNameEvent[3].index = 3;
            sortedByBudgetEvent[3].budget = events[3].budget;
            sortedByBudgetEvent[3].index = 3;

            //ТЕСТ №2
            /*events[0].name = "Christmas";
            events[0].date = "07.01.22";
            events[0].place = "Moscow";
            events[0].budget = 232000;
            events[0].guests = 30;
            sortedByNameEvent[0].name = events[0].name;
            sortedByNameEvent[0].index = 0;
            sortedByBudgetEvent[0].budget = events[0].budget;
            sortedByBudgetEvent[0].index = 0;

            events[1].name = "Wedding";
            events[1].date = "17.08.20";
            events[1].place = "Perm";
            events[1].budget = 232000;
            events[1].guests = 40;
            sortedByNameEvent[1].name = events[1].name;
            sortedByNameEvent[1].index = 1;
            sortedByBudgetEvent[1].budget = events[1].budget;
            sortedByBudgetEvent[1].index = 1;

            events[2].name = "Christmas";
            events[2].date = "11.10.24";
            events[2].place = "Kungur";
            events[2].budget = 232000;
            events[2].guests = 10;
            sortedByNameEvent[2].name = events[2].name;
            sortedByNameEvent[2].index = 2;
            sortedByBudgetEvent[2].budget = events[2].budget;
            sortedByBudgetEvent[2].index = 2;

            events[3].name = "Wedding";
            events[3].date = "09.05.24";
            events[3].place = "Saint Petersburg";
            events[3].budget = 232000;
            events[3].guests = 100;
            sortedByNameEvent[3].name = events[3].name;
            sortedByNameEvent[3].index = 3;
            sortedByBudgetEvent[3].budget = events[3].budget;
            sortedByBudgetEvent[3].index = 3;*/

            cout << "\n------------- Изначальный массив ---------\n";
            outputData(events, MAX_EVENT);
            Event originalEvents[MAX_EVENT];
            for (int i = 0; i < MAX_EVENT; i++) {
                originalEvents[i] = events[i];
            }

            do {
                std::cout << " ------------------- П Е Р В О Е   З А Д А Н И Е \n" << std::endl;
                std::cout << " 1. Сортировка по названию" << std::endl;
                std::cout << " 2. Сортировка по бюджету" << std::endl;
                std::cout << " 3. Бинарный поиск по названию" << std::endl;
                std::cout << " 4. Бинарный поиск по бюджету" << std::endl;
                std::cout << " 5. Редактирование бюджета" << std::endl;
                std::cout << " 6. Редактирование названия" << std::endl;
                std::cout << " 7. Удаление по названию" << std::endl;
                std::cout << " 8. Назад" << std::endl;
                std::cout << " " << std::endl;

                cin >> choice;

                switch (choice) {
                case 1: { //сортирова пузырьком по названию мероприятий
                    insertionSortByName(sortedByNameEvent, MAX_EVENT);
                    for (int i = 0; i < MAX_EVENT; i++) {
                        events[i] = originalEvents[sortedByNameEvent[i].index];
                    }
                    outputData(events, MAX_EVENT);
                    break;
                }
                case 2: { //сортировка пузырьком по бюджету мероприятий
                    insertionSortByBudget(sortedByBudgetEvent, MAX_EVENT);
                    for (int i = 0; i < MAX_EVENT; i++) {
                        events[i] = originalEvents[sortedByBudgetEvent[i].index];
                    }
                    outputData(events, MAX_EVENT);
                    break;
                }
                case 3: { //бинарный поиск по названию мероприятий
                    insertionSortByName(sortedByNameEvent, MAX_EVENT);
                    for (int i = 0; i < MAX_EVENT; i++) {
                        events[i] = originalEvents[sortedByNameEvent[i].index];
                    }
                    int resultIndexByName = binarySearchByName(sortedByNameEvent, 0, 4, "Wedding");
                    if (resultIndexByName != -1)
                    {
                        int indByName = sortedByNameEvent[resultIndexByName].index;
                        std::cout << "Элемент с именем "<< sortedByNameEvent[resultIndexByName].name << " был найден:" << endl;
                        std::cout << "Name: " << sortedByNameEvent[resultIndexByName].name << ", Date: " << events[indByName].date << ", Place: " << events[indByName].place << ", Budget: " << events[indByName].budget << ", Guests: " << events[indByName].guests << endl << endl;
                    }
                    else
                    {
                        std::cout << "Элемент с таким именым не был найден" << std::endl;
                    }
                    break;
                }
                case 4: { //бинарный поиск по бюджету
                    insertionSortByBudget(sortedByBudgetEvent, MAX_EVENT);
                    for (int i = 0; i < MAX_EVENT; i++) {
                        events[i] = originalEvents[sortedByBudgetEvent[i].index];
                    }
                    int resultIndexByBudget = binarySearchByBudget(sortedByBudgetEvent, 5, 20000);
                    if (resultIndexByBudget != -1)
                    {
                        std::cout << "Элемент с бюджетом " << sortedByBudgetEvent[resultIndexByBudget].budget << " был найден:" << endl;
                        int indByBudget = sortedByBudgetEvent[resultIndexByBudget].index;
                        std::cout << "Budget: " << sortedByBudgetEvent[resultIndexByBudget].budget << ", Name: " << events[indByBudget].name << ", Date: " << events[indByBudget].date << ", Place: " << events[indByBudget].place << ", Guests: " << events[indByBudget].guests << endl << endl;
                    }
                    else
                    {
                        std::cout << "Элемент не найден" << std::endl;
                    }
                    break;
                }
                case 5: { //редактирование бюджета
                    std::string nameToEdit = "Christmas";
                    int newBudget = 120000;
                    editBudget(originalEvents, MAX_EVENT, nameToEdit, newBudget);
                    outputData(originalEvents, MAX_EVENT);
                    break;
                }
                case 6: {//редактирование по имени
                    std::string newName = "Anniversary";
                    int numberToEdit = 600000;
                    editName(originalEvents, MAX_EVENT, newName, numberToEdit);
                    outputData(originalEvents, MAX_EVENT);
                    break;
                }
                case 7: {
                    std::string nameToDelete = "Birthday";
                    //int arraySize = MAX_EVENT;
                    deleteRec(originalEvents, MAX_EVENT, nameToDelete);
                    int newArraySize = MAX_EVENT - 1;
                    outputData(originalEvents, newArraySize);
                    break;
                }
                case 8: {
                    break;
                }
                default: {
                    cout << "Неверный ввод. Попробуйте снова.\n";
                }
                }
            } while (choice != 8);
            break;
        }
        case 2: {
            //ТЕСТ №1
            //struct Event events[MAX_EVENT] = {
            //{"Christmas", "07.01.22", "Moscow", 232000, 30},
            //{"Wedding", "17.08.20", "Perm", 500000, 40},
            //{"Birthday", "11.10.24", "Kungur", 20000, 10},
            //{"Victory Day", "09.05.24", "Saint Petersburg", 600000, 100}
            //};

            //ТЕСТ №2
            struct Event events[MAX_EVENT] = {
            {"Christmas", "07.01.22", "Moscow", 232000, 30},
            {"Christmas", "17.08.20", "Perm", 232000, 30},
            {"Christmas", "11.10.24", "Kungur", 232000, 30},
            {"Christmas", "09.05.24", "Saint Petersburg", 232000, 30}
            };

            //ТЕСТ №3
            //struct Event events[MAX_EVENT] = {
            //};

            TreeNode* root = nullptr;
            for (int i = 0; i < MAX_EVENT; i++)
            {
                insert(root, events[i].budget, i);
            }
            do
            {
                std::cout << " ------------------- В Т О Р О Е   З А Д А Н И Е (БИНАРНОЕ ДЕРЕВО) \n" << std::endl;
                std::cout << " 1. Обход дерева для вывода записей в порядке возрастания" << std::endl;
                std::cout << " 2. Обход дерева для вывода записей в порядке убывания" << std::endl;
                std::cout << " 3. Поиск элемента с заданным ключом" << std::endl;
                std::cout << " 4. Удаление элемента с заданным ключом" << std::endl;
                std::cout << " 5. Обновление записи с заданным ключом и значениями атрибутов" << std::endl;
                std::cout << " 6. Назад" << std::endl;

                cin >> choice;

                switch (choice) {
                case 1: { //Обход дерева для вывода записей в порядке возрастания
                    inOrderTree(root, events);
                    std::cout << " " << std::endl;
                    break;
                }
                case 2: { //Обход дерева для вывода записей в порядке убывания
                    reverseOrderTree(root, events);
                    std::cout << " " << std::endl;
                    break;
                }
                case 3: { //Поиск элемента с заданным ключом
                    int keySearch = 232000;
                    searchElement(root, events, keySearch);
                    break;
                }
                case 4: { //Удаление элемента с заданным ключом
                    int size = MAX_EVENT;
                    int keyToDelete = 232000;
                    deleteNode(root, keyToDelete, events, size);
                    std::cout << "-------- RESULT OF REMOVING AN ELEMENT WITH A BUDGET " << keyToDelete << ":" << endl;
                    inOrderTree(root, events);
                    break;
                }
                case 5: { //Обновление записи с заданным ключом и значениями атрибутов
                    int key = 500000;
                    string newNames = "Easter";
                    string newDate = "04.04.24";
                    string newPlace = "Kungur";
                    double newBudgets = 15000;
                    int newGuests = 7;
                    editRecord(root, events, key, newNames, newDate, newPlace, newBudgets, newGuests);
                    inOrderTree(root, events);
                    break;
                }
                case 6: {
                    break;
                }
                default: {
                    cout << "Неверный ввод. Попробуйте снова.\n";
                }
                }
            } while (choice != 6);
            break;
        }
        case 3: {
            //ТЕСТ №1
            //struct Event events[MAX_EVENT] = {
            //{"Christmas", "07.01.22", "Moscow", 232000, 30},
            //{"Wedding", "17.08.20", "Perm", 500000, 40},
            //{"Birthday", "11.10.24", "Kungur", 20000, 10},
            //{"Victory Day", "09.05.24", "Saint Petersburg", 600000, 100}
            //};

            //ТЕСТ №2
            //struct Event events[MAX_EVENT] = {
            //{"Christmas", "07.01.22", "Russia", 232000, 32},
            //{"Wedding", "17.08.20", "Russia", 500000, 32},
            //{"Birthday", "11.10.24", "Russia", 20000, 32},
            //{"Victory Day", "09.05.24", "Russia", 600000, 32}
            //};

            //ТЕСТ №3
            struct Event events[MAX_EVENT] = {
            };

            EventList* NewNode = nullptr;// Ссылка на новую вершину, которая будет вставляться в список (в голову)
            EventList* HeadNow = nullptr;// Список пуст - указатель на "голову" - первый элемент - обнуляется
            for (int i = 0; i < MAX_EVENT; i++)
            {
                NewNode = new EventList;
                NewNode->event.name = events[i].name;
                NewNode->event.date = events[i].date;
                NewNode->event.place = events[i].place;
                NewNode->event.budget = events[i].budget;
                NewNode->event.guests = events[i].guests;
                NewNode->next = HeadNow;
                HeadNow = NewNode;
            }
            do
            {
                std::cout << " " << std::endl;
                std::cout << " ------------------- Т Р Е Т Ь Е   З А Д А Н И Е (ЛИНЕЙНЫЙ СПИСОК) \n" << std::endl;
                std::cout << " 1. Печать линейного списка с начала" << std::endl;
                std::cout << " 2. Печать линейного списка с конца" << std::endl;
                std::cout << " 3. Сортировка элементов в порядке возрастания по атрибуту 'guests' " << std::endl;
                std::cout << " 4. Сортировка элементов в порядке убывания по атрибуту 'place'" << std::endl;
                std::cout << " 5. Добавление новой записи и сортировка по возрастанию атрибута 'guests'" << std::endl;
                std::cout << " 6. Добавление новой записи и сортировка по убыванию атрибута 'place'" << std::endl;
                std::cout << " 7. Поиск элемента по атрибуту 'guests'" << std::endl;
                std::cout << " 8. Поиск элемента по атрибуту 'place'" << std::endl;
                std::cout << " 9. Удаление элемента по атрибуту 'guests'" << std::endl;
                std::cout << " 10. Удаление элемента по атрибуту 'place'" << std::endl;
                std::cout << " 11. Назад" << std::endl;

                cin >> choice;

                switch (choice) {
                case 1: {
                    ListFromFirst(HeadNow);
                    break;
                }
                case 2: {
                    ListFromEnd(HeadNow);
                    break;
                }
                case 3: { //Сортировка элементов в порядке возрастания по атрибуту 'guests'
                    sortListByGuests(HeadNow);
                    ListFromFirst(HeadNow);
                    break;
                }
                case 4: { //Сортировка элементов в порядке убывания по атрибуту 'place'
                    sortListByPlace(HeadNow);
                    ListFromFirst(HeadNow);
                    break;
                }
                case 5: { //Добавление новой записи и сортировка по возрастанию атрибута 'guests'
                    Event newEvents1 = { "Prom", "30.09.23", "Cafe" , 180000, 32 };
                    AddAndSortByGuests(HeadNow, newEvents1);
                    ListFromFirst(HeadNow);
                    break;
                }
                case 6: { //Добавление новой записи и сортировка по убыванию атрибута 'place'
                    Event newEvents2 = { "Russia Day", "12.09.24", "Russia" , 1000000, 100 };
                    AddAndSortByPlace(HeadNow, newEvents2);
                    ListFromFirst(HeadNow);
                    break;
                }
                case 7: { //Поиск элемента по атрибуту 'guests'
                    int purposeGuests = 32;
                    searchByGuests(HeadNow, purposeGuests);
                    break;
                }
                case 8: { //Поиск элемента по атрибуту 'place'
                    string purposePlace = "Kungur";
                    searchByPlace(HeadNow, purposePlace);
                    break;
                }
                case 9: { //Удаление элемента по атрибуту 'guests'
                    int deleteGuests = 32;
                    deleteByGuests(HeadNow, deleteGuests);
                    ListFromFirst(HeadNow);
                    break;
                }
                case 10: { //Удаление элемента по атрибуту 'place'
                    string deletePlace = "Russia";
                    deleteByPlace(HeadNow, deletePlace);
                    ListFromFirst(HeadNow);
                    break;
                }
                case 11: { 
                    break;
                }
                default: {
                    cout << "Неверный ввод. Попробуйте снова.\n";
                }
                }
            } while (choice != 11);
            break;
        }
        case 4: {
            cout << "Программа завершена\n";
            break;
        }
        default: {

            cout << "Неверный ввод. Попробуйте снова.\n";
        }
        }
    } while (answer != 4);

    return 0;
}
