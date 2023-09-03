# search_engine
# Проект Search

Этот проект представляет собой инструмент для поиска файлов, позволяющий искать конкретную фразу в файлах в выбранной директории. Он будет рекурсивно искать файлы в выбранной директории и ее поддиректориях, собирая пути файлов, которые содержат указанную фразу.

## Требования

- Компилятор C++ с поддержкой C++17
- CMake (версия 3.15 или выше)
- Make (необязательно, для сборки с Make)

## Начало работы

1. Склонируйте репозиторий:
git clone https://github.com/Vlad1kavkaz/saerch_engine.git


2. Соберите проект:
cd search-engine
mkdir build
cd build
cmake ..
make

3. Запустите программу:
./search


## Использование

1. Введите фразу для поиска по запросу программы.

2. Введите директорию для поиска по запросу программы. Программа будет рекурсивно искать в выбранной директории и всех ее поддиректориях.

3. Программа выведет список файлов, содержащих указанную фразу.

## Пример работы программы и параметров входынх данных
```
Enter phrase to search:class Sotrudnic
 Enter the directory to search in:C:\\Users\\28218\\CLionProjects
 Program finished successfully.
Results have been saved to 'output.txt'.
Do you want to open a specific file? (y/n):y
 [0] C:/Users/28218/CLionProjects/lb4/Sotrudnic.h
[1] C:/Users/28218/CLionProjects/lb5/Sotrudnic.h
Enter the number of the file to open:0
 Please select your operating system:
1. Windows
2. macOS
3. Linux
Choice:1
 File opened successfully
```
Обратите внимание, что путь к директории надо указывать в правильном для вашей системы формате
