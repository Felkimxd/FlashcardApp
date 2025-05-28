# Study_Duel

A flashcard application with battle mode developed in C++ using SQLite as database.

## Description

Study_Duel is a study tool that combines traditional flashcard system with gamification elements. Create your flashcards, organize them in decks and use them for both traditional study and knowledge battles.

## Features

### Flashcard System
- ✨ Create new flashcard decks
- 📝 Add/Edit/Delete flashcards
- ⏱️ Estimated time per flashcard
- 📊 Adaptive grading system

### Study Modes
- 📚 Traditional Study Mode
  - Flashcard review
  - Immediate feedback
  - Progress tracking
- ⚔️ Battle Mode
  - HP system
  - Speed bonuses
  - Cumulative scoring
  - Answer-based damage

## System Requirements

- C++20 or higher
- SQLite3
- CMake 3.10 or higher
- C++20 compatible compiler (like G++)
- Windows (for specific console functions)

## Installation

1. Clone the repository:
```bash
git clone https://github.com/your-username/Study_Duel.git
cd Study_Duel
```

2. Create and enter build directory:
```bash
mkdir build
cd build
```

3. Compile the project:
```bash
cmake ..
cmake --build .
```

## Usage

1. Run the application:
```bash
./Study_Duel
```

2. Create or select a deck
3. Choose study mode:
   - Traditional study session
   - Battle mode

## Project Structure

```
Study_Duel/
├── include/               # Header files
│   ├── database.h        # Database management
│   ├── flashcard.h       # Flashcard class
│   ├── gamification.h    # Battle system
│   └── studySession.h    # Study mode
├── src/                  # Source code
│   ├── main.cpp
│   ├── database.cpp
│   ├── flashcard.cpp
│   ├── gamification.cpp
│   └── studySession.cpp
├── external/             # External dependencies
│   └── sqlite/
├── archives/            # Data files
│   └── data/
└── CMakeLists.txt
```

## Technical Features

- Adaptive grading algorithm
- Battle system with game mechanics
- Data persistence with SQLite
- Console interface with UTF-8 support

## Project Status

Implemented features:
- ✅ CRUD for flashcards and decks
- ✅ Traditional study mode
- ✅ Battle mode
- ✅ Scoring system

Upcoming features:
- [ ] Graphical interface
- [ ] Multiplayer mode
- [ ] Detailed statistics
- [ ] Export/Import decks
- [ ] Users Registers
- [ ] Enhance Gamification Mode, adding RPG essence

## Contributing

Contributions are welcome. Please:
1. Fork the project
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

## Author
- Felipe Quilumbango

## License
This project is under the MIT License