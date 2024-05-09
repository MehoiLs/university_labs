#ifndef DS_SEM4_LAB3_TICTACTOEWINCALCULATOR_H
#define DS_SEM4_LAB3_TICTACTOEWINCALCULATOR_H

#include <iostream>
#include <vector>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::vector;

constexpr int MAX_FIELD_OUTPUT_SIZE = 16;

enum TicTacToeFieldState {
    EMPTY,
    CROSS,
    ZERO
};

constexpr TicTacToeFieldState FIRST_PLAYER = CROSS;
constexpr TicTacToeFieldState SECOND_PLAYER = ZERO;
static_assert(FIRST_PLAYER != SECOND_PLAYER && FIRST_PLAYER != EMPTY && SECOND_PLAYER != EMPTY);

class TicTacToeWinCalculator {
private:
    // Additional
    static void assertSingleFieldEntry(const int x, const int y, const int fieldSize) {
        if (x < 1 || x > fieldSize || y < 1 || y > fieldSize) {
            throw std::invalid_argument("The field entry is out of bounds.");
        }
    }
    static std::string stateToString(const TicTacToeFieldState state) {
        if (state == CROSS) {
            return "X";
        } else if (state == ZERO) {
            return "0";
        } else {
            return "-";
        }
    }
    // Field
    static auto createField(const int fieldSize) {
        return vector<vector<TicTacToeFieldState>>(fieldSize, vector<TicTacToeFieldState>(fieldSize, EMPTY));
    }
    static void autoFillFromConsole(const int fieldSize, vector<vector<TicTacToeFieldState>>& field) {
        TicTacToeFieldState state;
        char c;
        for (int i = 0; i < fieldSize; ++i) {
            for (int j = 0; j < fieldSize; ++j) {
                cout << i+1 << "x" << j+1 << ":";
                cin >> c;
                if (c == 'X') {
                    state = CROSS;
                } else if (c == '0') {
                    state = ZERO;
                } else {
                    state = EMPTY;
                }
                field[i][j] = state;
            }
        }
    }
    static void printField(const vector<vector<TicTacToeFieldState>>& field) {
        if (field.size() > MAX_FIELD_OUTPUT_SIZE) {
            cerr << "The field is too large to be displayed.";
            cerr << "Maximum field size is " << MAX_FIELD_OUTPUT_SIZE << "x" << MAX_FIELD_OUTPUT_SIZE << endl;
            return;
        }
        for (const auto &row : field) {
            for (const auto &cell : row) {
                if (cell == CROSS) {
                    cout << "X ";
                } else if (cell == ZERO) {
                    cout << "0 ";
                } else {
                    cout << "- ";
                }
            }
            cout << endl;
        }
    }
    /** Returns the current turn of the player.
     *
     * @return Player who
     * */
    static TicTacToeFieldState getCurrentTurn(const vector<vector<TicTacToeFieldState>>& field) {
        int countX = 0, count0 = 0;
        for (const auto &row : field) {
            for (const auto &cell : row) {
                if (cell == TicTacToeFieldState::CROSS) {
                    countX++;
                } else if (cell == TicTacToeFieldState::ZERO) {
                    count0++;
                }
            }
        }
        assertFieldIsCorrect(countX, count0);
        if (countX == count0) {
            return FIRST_PLAYER;
        } else {
            return SECOND_PLAYER;
        }
    }
    static void assertFieldIsCorrect(const int countX, const int count0) {
        if (FIRST_PLAYER == CROSS) {
            if (countX > count0 + 1) {
                throw std::invalid_argument("The field is invalid (too many Xs).");
            } else if (count0 > countX) {
                throw std::invalid_argument("The field is invalid (too many 0s).");
            }
        }
        else {
            if (countX + 1 < count0) {
                throw std::invalid_argument("The field is invalid (too many 0s).");
            } else if (countX > count0) {
                throw std::invalid_argument("The field is invalid (too many Xs).");
            }
        }
    }

    static int performBacktrackingCalculateCombinationsRD(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& currentTurn,
            const int winChainLength,
            const int calculationBorder,
            int currentLength = 1,
            int x = 0,
            int y = 0,
            const bool isDiagonal = true
    ) {
        const bool shouldIncludeDiagonal = (y < calculationBorder);
        const auto fieldSize = field.size();
        if (x >= fieldSize || y >= fieldSize) {
            return 0; // Reached border => ROLLBACK
        }
        if (currentTurn != field[y][x]) {
            return 0; // Reached other player's symbol/empty cell => ROLLBACK
        }
        if (currentLength == winChainLength) {
            return 1; // Found combination => ROLLBACK with 1
        }
        if ((x + 1) == calculationBorder) {
            return 0; // Reached calc border => ROLLBACK
        }

        int diagonalCount = 0;
        if (shouldIncludeDiagonal && isDiagonal) {
            diagonalCount = performBacktrackingCalculateCombinationsRD(
                    field, currentTurn, winChainLength, calculationBorder,
                    currentLength+1, x+1, y+1, true
            );
        }
        int rightCount = 0;
        //fixme - full rollback (perhaps RD should be 2 separate funcs: Right & Down)
        rightCount = performBacktrackingCalculateCombinationsRD(
                field, currentTurn, winChainLength, calculationBorder,
                currentLength + 1, x + 1, y, false
        );
        // Not using accumulator, consider this a new start-point
        int movedRightCount = 0;
        if (x <= calculationBorder) {
            movedRightCount = performBacktrackingCalculateCombinationsRD(
                    field, currentTurn, winChainLength, calculationBorder,
                    1, x+1, y, true
            );
        }
        int movedDownCount = 0;
        if (y < fieldSize) {
            movedDownCount = performBacktrackingCalculateCombinationsRD(
                    field, currentTurn, winChainLength, calculationBorder,
                    1, x, y+1, true
            );
        }
        return rightCount + diagonalCount + movedRightCount + movedDownCount;
    }

    static int performBacktrackingCalculateCombinationsUR(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& currentTurn,
            const int winChainLength,
            const int calculationBorderHor,
            const int calculationBorderVer,
            int currentLength,
            int x,
            int y,
            const bool isDiagonal
    ) {
        const bool shouldIncludeDiagonal = (x < calculationBorderVer);
        const auto fieldSize = field.size();
        if (x >= fieldSize || y <= 0) {
            return 0; // Reached border => ROLLBACK
        }
        if (currentTurn != field[y][x]) {
            return 0; // Reached other player's symbol/empty cell => ROLLBACK
        }
        if (currentLength == winChainLength) {
            return 1; // Found combination => ROLLBACK with 1
        }
        if ((y + 1) == calculationBorderHor) {
            return 0; // Reached calc border => ROLLBACK
        }

        int diagonalCount = 0;
        if (shouldIncludeDiagonal && isDiagonal) {
            diagonalCount = performBacktrackingCalculateCombinationsUR(
                    field, currentTurn, winChainLength, calculationBorderHor, calculationBorderVer,
                    currentLength+1, x+1, y-1, true
            );
        }
        int upCount = 0;
        //fixme - full rollback (perhaps UR should be 2 separate funcs: Up & Right)
        upCount = performBacktrackingCalculateCombinationsUR(
                field, currentTurn, winChainLength, calculationBorderHor, calculationBorderVer,
                currentLength + 1, x, y - 1, false
        );
        // Not using accumulator, consider this a new start-point
        int movedRightCount = 0;
        if (x < fieldSize) {
            movedRightCount = performBacktrackingCalculateCombinationsUR(
                     field, currentTurn, winChainLength, calculationBorderHor, calculationBorderVer,
                     1, x+1, y, true
             );
        }
        int movedUpCount = 0;
        if (y >= calculationBorderHor) {
            movedUpCount = performBacktrackingCalculateCombinationsUR(
                    field, currentTurn, winChainLength, calculationBorderHor, calculationBorderVer,
                    1, x, y-1, true
            );
        }
        return upCount + diagonalCount + movedRightCount + movedUpCount;
    }

    static int performBacktrackingCalculateCombinations(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& currentTurn,
            const int winChainLength
    ) {
        const int fieldSize = field.size();
        const int calcBorderRD = fieldSize - winChainLength + 1;
        const int calcBorderURHor = winChainLength;
        const int calcBorderURVer = calcBorderRD;

        const int countRD = performBacktrackingCalculateCombinationsRD(
                field, currentTurn, winChainLength, calcBorderRD,
                1, 0, 0, true
        );
        const int countUR = performBacktrackingCalculateCombinationsUR(
                field, currentTurn, winChainLength, calcBorderURHor, calcBorderURVer,
                1, 0, (fieldSize - 1), true
        );
        return countRD + countUR;
    }

public:

    static int performCalculations(const vector<vector<TicTacToeFieldState>>& field, const int winChainLength) {
        const auto currentTurn = getCurrentTurn(field);
        cout << "The current player is: " << stateToString(currentTurn) << endl;
        cout << "The length of the winning chain is: " << winChainLength << endl;

        return performBacktrackingCalculateCombinations(field, currentTurn, winChainLength);
    }
    static void input() {
        int fieldSize, winChainLength; // "N", "M"
        cerr << "We will consider that " <<  stateToString(FIRST_PLAYER)  << " is the first player and "
            << stateToString(SECOND_PLAYER) << " is the second player.";
        cout << endl;
        cout << "Please, input the size of the field (n): ";
        cin >> fieldSize;
        if (fieldSize < 3) {
            throw std::invalid_argument("The field size cannot be less than 3.");
        }

        cout << "Please, input the length of the winning chain (m): ";
        cin >> winChainLength;
        if  (winChainLength < 3) {
            throw std::invalid_argument("The length of the winning chain cannot be less than 3.");
        }
        if (fieldSize < winChainLength) {
            throw std::invalid_argument("The length of the winning chain cannot be greater than the field size.");
        }
        cout << endl;

        cout << "Please, input the field, according to the instructions:\n";
        cout << "\t <number>x<number>:X \t - to place a cross\n";
        cout << "\t <number>x<number>:0 \t - to place a zero\n";
        cout << "\t <number>x<number>:E \t - to place an empty cell\n";
        cout << "\t EXIT \t\t\t - to stop filling the field and proceed to the calculation.\n";
        cout << "Example: \"1x1:X\" - will place X in the top left corner of the field (1x1).\n\n";
        cout << "There is also an \"Auto Input\" option which allows to fill in the whole field. Usage:\n";
        cout << "\t AUTO \t\t\t  - to fill in the whole field\n";
        cout << endl;
        cout << "Waiting for the input...\n";

        auto field = createField(fieldSize);
        std::string input;
        while (input != "EXIT") {
            cin >> input;
            if (input == "EXIT") {
                break;
            }
            if (input == "AUTO") {
                autoFillFromConsole(fieldSize, field);
                break;
            }
            int x, y;
            TicTacToeFieldState state;

            std::string accumulator;
            for (auto &c : input) {
                if (c == 'x') {
                    x = std::stoi(accumulator);
                    accumulator.clear();
                } else if (c == ':' || c == ' ') {
                    y = std::stoi(accumulator);
                    accumulator.clear();
                } else if (c == 'X') {
                    state = CROSS;
                } else if (c == '0') {
                    state = ZERO;
                } else if (c == 'E') {
                    state = EMPTY;
                } else {
                    accumulator += c;
                }
            }
            assertSingleFieldEntry(x, y, fieldSize);
            field[x-1][y-1] = state;
        }
        cout << "The field you've entered:\n";
        printField(field);
        cout << endl;

        int result = performCalculations(field, winChainLength);
        cout << "The number of winning combinations is: " << result << endl;
    }
    static void test() {
        const int WIN_CHAIN_LENGTH = 3;
        vector<vector<TicTacToeFieldState>> field = {
                {CROSS, ZERO,   ZERO,   ZERO,   ZERO    },  // X 0 0 0 0
                {CROSS, CROSS,  ZERO,   ZERO,   EMPTY   },  // X X 0 0 X
                {CROSS, ZERO,   CROSS,  ZERO,   CROSS   },  // X 0 X 0 X
                {CROSS, CROSS,  ZERO,   CROSS,  ZERO    },  // X X 0 X 0
                {CROSS, CROSS,  ZERO,   ZERO,   CROSS   }   // X X 0 0 X
        };

        int result = performCalculations(field, WIN_CHAIN_LENGTH);
        cout << "The number of winning combinations is: " << result << endl;
    }
};

#endif //DS_SEM4_LAB3_TICTACTOEWINCALCULATOR_H
