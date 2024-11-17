#include <iostream>
#include <memory>

template <typename T>
class Node {
public:
    T data;                        // Данные узла
    std::shared_ptr<Node<T>> next; // Указатель на следующий узел

    Node(T val) : data(val), next(nullptr) {} // Конструктор
};

template <typename T>
class LinkedList {
private:
    std::shared_ptr<Node<T>> head; // Указатель на первый узел
    std::shared_ptr<Node<T>> tail; // Указатель на последний узел
    size_t list_size;              // Размер списка

public:
    LinkedList() : head(nullptr), tail(nullptr), list_size(0) {} // Конструктор

    // Метод добавления элемента в начало списка
    void push_front(T val) {
        auto newNode = std::make_shared<Node<T>>(val);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = head; // Если список был пуст, обновляем tail
        }
        list_size++;
    }

    // Метод добавления элемента в конец списка
    void push_back(T val) {
        auto newNode = std::make_shared<Node<T>>(val);
        if (tail) {
            tail->next = newNode;
        }
        else {
            head = newNode; // Если список был пуст, обновляем head
        }
        tail = newNode;
        list_size++;
    }

    // Метод удаления элемента из начала списка
    void pop_front() {
        if (is_empty()) {
            std::cout << "Список пуст. Невозможно удалить элемент." << std::endl;
            return;
        }
        head = head->next;
        if (head == nullptr) {
            tail = nullptr; // Если список стал пустым
        }
        list_size--;
    }

    // Метод удаления элемента из конца списка
    void pop_back() {
        if (is_empty()) {
            std::cout << "Список пуст. Невозможно удалить элемент." << std::endl;
            return;
        }

        if (head == tail) {
            head = tail = nullptr; // Если в списке был только один элемент
        }
        else {
            auto current = head;
            while (current->next != tail) {
                current = current->next;
            }
            current->next = nullptr;
            tail = current; // Обновляем tail
        }
        list_size--;
    }

    // Метод поиска элемента по значению
    std::shared_ptr<Node<T>> find(T val) {
        auto current = head;
        while (current != nullptr) {
            if (current->data == val) {
                return current; // Элемент найден
            }
            current = current->next;
        }
        return nullptr; // Элемент не найден
    }

    // Метод удаления элемента по значению
    bool remove(T val) {
        if (is_empty()) {
            return false;
        }

        // Удаление первого узла
        if (head->data == val) {
            pop_front();
            return true;
        }

        auto current = head;
        while (current->next != nullptr) {
            if (current->next->data == val) {
                current->next = current->next->next;
                if (current->next == nullptr) {
                    tail = current; // Обновляем tail, если удаляем последний элемент
                }
                list_size--;
                return true; // Элемент был найден и удален
            }
            current = current->next;
        }
        return false; // Элемент не найден
    }

    // Метод печати списка
    void print() {
        auto current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl; // Конец списка
    }

    // Метод проверки списка на пустоту
    bool is_empty() const {
        return head == nullptr;
    }

    // Метод получения размера списка
    size_t size() const {
        return list_size;
    }

    // Деструктор не требуется, так как используются умные указатели
};

// Пример использования
int main() {
    LinkedList<int> list;

    // Добавление элементов
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    list.push_back(4);
