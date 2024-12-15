#include <iostream>
#include <cstdint>

// Win Check
inline bool hasWon(uint64_t b) {
    uint64_t m = b & (b >> 1);       // Horizontal (-) Check
    if (m & (m >> 2)) return true;
    m = b & (b >> 6);                // Diagonal (\) Check
    if (m & (m >> 12)) return true;
    m = b & (b >> 7);                // Vertical (|) Check
    if (m & (m >> 14)) return true;
    m = b & (b >> 8);                // Anti-Diagonal (/) Check
    if (m & (m >> 16)) return true;
    return false;
}

struct ConnectFour {
    uint64_t playerBoards[2];
    uint8_t heights[7];
    static constexpr int WIDTH = 7;
    static constexpr int HEIGHT = 6;

    // Constructor to init board
    ConnectFour() : playerBoards{0, 0}, heights{0, 0, 0, 0, 0, 0, 0} {}

    // Make move for given player (1 or 2) in specified column (0-based)
    inline void move(int player, int col) {
        uint8_t currentHeight = heights[col];
        uint64_t moveBit = 1ULL << (col * 7 + currentHeight);
        playerBoards[player - 1] |= moveBit;
        heights[col]++;
    }

    // Check if specified player wins
    inline bool checkWin(int player) const { return hasWon(playerBoards[player - 1]); }

    // Check if specified column is full
    inline bool columnFull(int col) const {  return heights[col] >= HEIGHT; }

    // Print board to console
    void print() const {
        char buffer[256];
        int pos = 0;

        // Headers
        for (int c = 1; c <= WIDTH; ++c) { pos += std::sprintf(buffer + pos, "| %d ", c); }
        pos += std::sprintf(buffer + pos, "|\n");

        // Board Rows
        for (int r = HEIGHT - 1; r >= 0; --r) {
            for (int c = 0; c < WIDTH; ++c) {
                uint64_t mask = 1ULL << (c * 7 + r);
                pos += std::sprintf(buffer + pos, "| %c ",
                    (playerBoards[0] & mask) ? 'X' :
                    (playerBoards[1] & mask) ? 'O' : ' ');
            }
            pos += std::sprintf(buffer + pos, "|\n");
        }
        pos += std::sprintf(buffer + pos, "\n");
        
        // Output the buffer
        std::cout.write(buffer, pos);
    }
};

int main() {
    ConnectFour board;
    board.print();

    int player = 1;
    while (true) {
        int column;
        std::cout << "Player " << player << " move: ";
        std::cin >> column;

        // Validate the move
        if (column <= 0 || column > ConnectFour::WIDTH || board.columnFull(column - 1)) {
            std::cout << "Invalid move. Try again.\n";
            continue;
        }

        // Make the move and print the board
        board.move(player, column - 1);
        board.print();

        // Check for a win
        if (board.checkWin(player)) {
            std::cout << "Player " << player << " wins!\n";
            break;
        }

        // Switch player (1 <-> 2)
        player ^= 3;
    }

    return 0;
}