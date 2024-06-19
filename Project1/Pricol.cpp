#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include <iostream>
#include <vector>
#include <thread>

// Класс MergeSort
class MergeSort {
public:
    void Sort(std::vector<int>& array) {
        if (array.size() > 1) {
            int mid = array.size() / 2;
            std::vector<int> left(array.begin(), array.begin() + mid);
            std::vector<int> right(array.begin() + mid, array.end());

            // Рекурсивная сортировка каждой половины
            Sort(left);
            Sort(right);

            // Слияние отсортированных половин
            Merge(array, left, right);
        }
    }

private:
    void Merge(std::vector<int>& array, const std::vector<int>& left, const std::vector<int>& right) {
        size_t i = 0, j = 0, k = 0;

        // Слияние двух половин в один массив
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                array[k++] = left[i++];
            }
            else {
                array[k++] = right[j++];
            }
        }

        // Копирование оставшихся элементов
        while (i < left.size()) {
            array[k++] = left[i++];
        }
        while (j < right.size()) {
            array[k++] = right[j++];
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<int> array(10);
    // Ввод массива пользователем
    std::cout << "Введите 10 целых чисел: ";
    for (int i = 0; i < 10; ++i) {
        std::cin >> array[i];
    }

    // Создание экземпляра класса MergeSort
    MergeSort mergeSort;

    // Создание анонимной функции для сортировки массива
    auto sortFunction = [&mergeSort](std::vector<int>& array) {
        mergeSort.Sort(array);
        };

    // Создание и запуск потока для сортировки
    std::thread mergeSortThread(sortFunction, std::ref(array));

    // Ожидание завершения сортировки
    mergeSortThread.join();

    // Вывод отсортированного массива
    std::cout << "Отсортированный массив: ";
    for (const auto& num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
