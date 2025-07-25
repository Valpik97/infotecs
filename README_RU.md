# Библиотека логирования и демонстрационное приложение

## Описание
C++17 библиотека логирования (статическая/динамическая) и многопоточное консольное приложение. Логирование сообщений с уровнями (Error, Warning, Info) в файл. Потокобезопасно, чистая сборка через CMake.

---

## Требования
- Компилятор с поддержкой C++17
- CMake >= 3.10
- GCC (Linux) или MinGW/MSVC (Windows)

---

## Инструкция по сборке

### Linux (GCC)
1. Установите зависимости:
   ```sh
   sudo apt update && sudo apt install build-essential cmake
   ```
2. Клонируйте репозиторий и перейдите в папку проекта:
   ```sh
   git clone <your_repo_url>
   cd Bibl
   ```
3. Создайте папку для сборки и настройте проект:
   - **Динамическая библиотека:**
     ```sh
     mkdir build && cd build
     cmake -DUSE_SHARED=ON .. -DCMAKE_BUILD_TYPE=Release
     ```
   - **Статическая библиотека:**
     ```sh
     mkdir build && cd build
     cmake -DUSE_SHARED=OFF .. -DCMAKE_BUILD_TYPE=Release
     ```
4. Сборка:
   ```sh
   make
   ```

### Windows (MinGW или MSVC)
1. Установите CMake и компилятор C++17 (MinGW или MSVC).
2. Клонируйте репозиторий и перейдите в папку проекта:
   ```sh
   git clone <your_repo_url>
   cd Bibl
   ```
3. Создайте папку для сборки и настройте проект:
   - **Динамическая библиотека:**
     ```sh
     mkdir build
     cd build
     cmake -DUSE_SHARED=ON .. -G "MinGW Makefiles"
     ```
   - **Статическая библиотека:**
     ```sh
     mkdir build
     cd build
     cmake -DUSE_SHARED=OFF .. -G "MinGW Makefiles"
     ```
4. Сборка:
   ```sh
   mingw32-make
   ```

---

## Как использовать приложение
1. **Соберите проект** как указано выше.
2. **Запустите приложение:**
   - В Linux:
     ```sh
     ./app/logger_app <logfile> [default_level]
     ```
   - В Windows:
     ```sh
     app\logger_app.exe <logfile> [default_level]
     ```
   - `<logfile>`: путь к файлу лога (например, `log.txt`)
   - `[default_level]`: (необязательно) `error`, `warning` или `info` (по умолчанию: `info`)
3. **Взаимодействие:**
   - Введите сообщение (или `exit` для выхода)
   - Введите уровень (`error`, `warning`, `info`) или нажмите Enter для уровня по умолчанию
   - Повторяйте по необходимости

--- 