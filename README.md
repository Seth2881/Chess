# C++ Chess Core & Bitboard Engine

A modern C++ chess engine project focused on low-level board state representation, bitboard attack generation, and Object-Oriented piece management. Built to sharpen C++ system programming and algorithmic problem-solving skills, with future goals of engine integration and visual UI rendering.

---

## 🌟 Key Features

* **Bitboard Attack Generation:** Uses 64-bit integer (`uint64_t`) bitmasks and bitwise operations (`<<`, `>>`, `&`, `|`, `^`) to generate attack maps for Rooks, Bishops, Queens, Knights, Kings, and Pawns.
* **FEN (Forsyth–Edwards Notation) Parser:** Parses standard FEN strings into active game states (piece placement, active color, castling rights, en passant targets, halfmove clock, fullmove number).
* **Object-Oriented Architecture:** Base polymorphic `Piece` class leveraging `std::unique_ptr` dynamic dispatch alongside modern C++ features (`std::views::split`, `std::ranges::to`).
* **Bitwise State Encoding:** Encodes piece types and colors efficiently using 5-bit flags (e.g., `0b01000` for White, `0b10000` for Black, `0b001` for Pawn).

---

## 📂 Project Structure

```text
Chess-cpp/
├── chessboard/
│   ├── img_board/               # UI textures for board representation
│   │   ├── Dark_green_square.jpg
│   │   ├── Light_gray_square.jpg
│   │   └── select_square.webp
│   └── board.cpp                # Board class, FEN parsing, and game initialization
├── pieces/
│   ├── Chess_pieces_sprite.png  # Piece sprite sheet
│   ├── bitboards.cpp            # Bitwise calculations & attack pattern functions
│   └── pieces.cpp               # Polymorphic Piece class & individual piece implementations
├── main.cpp                     # Entry point
└── README.md                    # Project documentation
```

---

## 🛠 Tech Stack & Requirements

* **Language:** Modern C++ (C++20 / C++23)
* **Compiler:** MSVC (Visual Studio), GCC, or Clang supporting C++20 ranges and views
* **Dependencies:**
  * C++ Standard Library (`<iostream>`, `<vector>`, `<bitset>`, `<memory>`, `<ranges>`)
  * Raylib *(configured for upcoming visual frontend)*

---

## 🚀 Building & Running

### Using MSVC / Visual Studio Code

1. Ensure a C++ compiler with C++20 support is available.
2. Compile and link the main entry point:
   ```bash
   g++ -std=c++20 main.cpp -o chess_app
   ```

---

## 🗺️ Roadmap & Future Plans and possibilities
* **Refactor #include** ".cpp" include chains into proper .hpp/.cpp header separations.

* **Complete CMake build configuration** across cross-platform compilers.

* **Finish move validation logic** (pin checks, legal check/checkmate detection).

* **store each piece move :** store 64 bitboards for each pieces reducing calculation time.

* **Implement a full Raylib 2D GUI** for visual playability.

* **Develop a custom Chess AI/Bot** (Minimax search with Alpha-Beta pruning).

* **Explore engine migration/port** to C# with Unity/Godot for 2D/3D rendering.

* **Explore a mobile app** option, combining C++ backend logic with Kotlin Jetpack Composer UI Tools.

*  **Completely restructure** the project to use more efficiently CLasses (not losing bitboards advantages).

---

## 👤 Author
### Seth (***@Seth2881***)
