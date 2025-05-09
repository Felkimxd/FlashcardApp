# FlashcardApp

A flashcard application developed in C++ with SQLite as database.

## Description

FlashcardApp is a study tool that allows users to create, manage and review flashcards. Each card contains a question and its corresponding answer, organized by subjects.

## Features

- ✅ Create new flashcards with question, answer and subject
- 📖 View all stored flashcards
- ✏️ Edit existing flashcards
- 🗑️ Delete flashcards
- 💾 Persistent storage using SQLite

## System Requirements

- C++20 or higher
- SQLite3
- CMake 3.10 or higher
- C++20 compatible compiler (like G++)

## Installation

1. Clone the repository:
```bash
git clone https://github.com/your-username/FlashcardApp.git
cd FlashcardApp
```

2. Create and enter the build directory:
```bash
mkdir build
cd build
```

3. Build the project:
```bash
cmake ..
cmake --build .
```

## Usage

Run the application from the build directory:
```bash
./FlashcardApp
```

The program will display a menu with the following options:
1. Add Flashcard
2. Show Flashcards
3. Delete Flashcard
4. Edit Flashcard
5. Exit

## Project Structure

```
FlashcardApp/
├── include/
│   ├── database.h
│   ├── flashcard.h
│   └── ...
├── src/
│   ├── main.cpp
│   ├── database.cpp
│   ├── flashcard.cpp
│   └── ...
├── external/
│   └── sqlite/
├── archives/
│   └── data/
└── CMakeLists.txt
```

## Technologies Used

- C++ for main logic
- SQLite3 for database
- CMake as build system

## Project Status

The project is in active development. Implemented features:
- ✅ Basic CRUD system for flashcards
- ✅ Command line interface
- ✅ SQLite integration

Upcoming features:
- [ ] Score system
- [ ] Quiz mode
- [ ] Graphical interface
- [ ] Gamification

## Contributing

Contributions are welcome. Please feel free to:
1. Fork the project
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

## Authors
- Felipe Quilumbango
