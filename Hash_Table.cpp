#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <list>
using namespace std;

class Passenger
{
    string name;
    string gender;
    int seat_number;

public:
    Passenger(string name = "Undefined", int seat_number = 0, string gender = "Undefined") {
        this->name = name;
        this->seat_number = seat_number;
        this->gender = gender;

    }

    ~Passenger() {
    }

    string getName() {
        return name;
    }

    string getGender() {
        return gender;
    }

    int getSeatNumber() {
        return seat_number;
    }

    void setName(Passenger rv) {
        this->name = rv.name;
    }

    void setGender(Passenger rv) {
        this->gender = rv.gender;
    }

    void setSeatNumber(Passenger rv) {
        this->seat_number = rv.seat_number;
    }

    Passenger& operator = (const Passenger& rv) {
        name = rv.name;
        seat_number = rv.seat_number;
        gender = rv.gender;
        return *this;
    }
    
    void print_passenger() {
        cout << "Name: " << name << "; Gender: " << gender << "; Seat Number: " << seat_number << ".";
    }
};


class HashTable 
{
private:
    vector<list<pair<int, Passenger>>>table; // Вектор для хранения данных

    size_t capacity; // Размер таблицы

    size_t help_hash_f1(const int& key) {
        return key % capacity;
    }

    size_t help_hash_f2(const int& key) {
        return (2 * key + 1) % capacity;
    }
    size_t hashFunction(const int& key)
    {
        for (int i = 0; i < capacity; ++i) {
            return (help_hash_f1(key) + i * help_hash_f2(key)) % capacity;
        }
    } // Хэш-функции

    
    size_t getIndex(const int& key) // Функция для получения индекса по ключу
    {
        return hashFunction(key);
    }


public:
    // Конструктор
    HashTable(size_t default_capacity = 10) {
        capacity = default_capacity;
        table.resize(capacity);
        cout << "HashTable is created" << endl;
    }
    //Деструктор
    ~HashTable()
    {
        clear();
        cout << "HashTable is deleted" << endl;
    }

    int count = 0;

    // Основные операции
    void insert(const int& key, const Passenger& value) // Вставка элемента
    {
        size_t index = getIndex(key);

        for (auto& pair : table[index]) {
            if (pair.first == key) {
                break;
            }
        }
        ++count;
        table[index].emplace_back(key,value);
    }

    bool remove(const int& key) { // Удаление элемента
        size_t index = getIndex(key);

        for (auto& pair : table[index]) {
            if (pair.first == key) {
                auto iter = table.cbegin();
                table.erase(iter + index);
                table.resize(capacity);
                count = count - 1;
                return true;
            }
            return false;
        }
        
    }

    bool find(const int& key, Passenger& lv) // Поиск элемента
    {
        size_t index = getIndex(key);

        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                Passenger x = pair.second;
                lv.setName(x);
                lv.setSeatNumber(x);
                lv.setGender(x);
                return true;
            }
            return false;
        }
    }

    void clear() {
        for (int i = 0; i < capacity; ++i) { // Очистка таблицы
            auto iter = table.cbegin();
            table.erase(iter + 0);
        }
        table.resize(capacity);
    }
    

    // Дополнительные методы

    size_t size() const { // Количество элементов в таблице
        if (count < 0) return 0;
        return count;
    } 

    bool isEmpty() const { // Проверка на пустоту
        if (count<0) {
            return true;
        }
        return false;
    }

    void print() const // Вывод таблицы
    {
        for (int i = 0; i < capacity; ++i) {
            cout << i << ": ";
            
            for (const auto& pair : table[i]) {
                Passenger x = pair.second;
                x.print_passenger();
            }
            cout << endl;
        }
    }

};

int main()
{
    HashTable hash(13);
    Passenger Gleb_Ivanov("Gleb", 12, "M");
    Passenger Kate_Ivanova("Kate", 13, "F");
    Passenger Alex_Petrov("Alex", 1, "M");
    Passenger Misha_Romanov("Misha", 8, "M");
    Passenger Person;
    hash.insert(1, Gleb_Ivanov);
    hash.insert(2, Kate_Ivanova);
    hash.insert(10, Alex_Petrov);
    hash.insert(20, Misha_Romanov);
    
    hash.print();
    if (hash.find(2, Person)) {
        cout << endl << "Person is found: ";
        Person.print_passenger();
    }
    else {
        cout << endl << "Person isn't found." << endl;
    }

    if (hash.find(11, Person)) {
        cout << endl << "Person is found: ";
        Person.print_passenger();
    }
    else {
        cout << endl << "Person isn't found." << endl;
    }

    if (hash.isEmpty()) {
        cout << "Hash Table is empty." << endl;
    }
    else {
        cout << "Hash Table isn't empty." << endl;
    }

    cout << "Count: " << hash.size() << endl;

    hash.remove(2);

    hash.print();
    cout << "Count: " << hash.size() << endl;

    return 0;
}
