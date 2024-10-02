#ifndef DS_SEM4_LAB3_TICTACTOEFIELD_H
#define DS_SEM4_LAB3_TICTACTOEFIELD_H

#include <iostream>
#include <utility>
#include <vector>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::vector;

constexpr int MAX_FIELD_OUTPUT_SIZE = 16;

enum TicTacToeFieldState {
    ZERO,
    CROSS,
    EMPTY
};

struct Coordinates {
    int x;
    int y;
    Coordinates(): x(0), y(0) {}
    Coordinates(const int x, const int y): x(x), y(y) {}
    std::string toString() const { return "{" + std::to_string(x) + "; " + std::to_string(y) + "}"; }
};

/**
 * Структура, содержащая информацию о поле.
 * Используется для передачи информации о поле между методами или классами.
 *
 * @author MehoiLs (Dorokhov Mikhail)
 */
struct FullFieldInfo {
    vector<vector<TicTacToeFieldState>> field;
    const int winChainLength;
    FullFieldInfo(const vector<vector<TicTacToeFieldState>>& field, const int winChainLength)
    : field(field), winChainLength(winChainLength) {}
};

constexpr TicTacToeFieldState FIRST_PLAYER = CROSS;
constexpr TicTacToeFieldState SECOND_PLAYER = ZERO;
static_assert(FIRST_PLAYER != SECOND_PLAYER && FIRST_PLAYER != EMPTY && SECOND_PLAYER != EMPTY);

constexpr bool DISABLED_ASSERTION = false; // Set to true to disable assertions of the field correctness

/**
 * Базовый класс Крестиков-Ноликов.
 * Содержит основную логику, необходимую для решения:
 * <p> - валидация позиций
 * <p> - валидация поля
 * <p> - получения текущей очереди
 * <p> - подсчёт комбинация на горизонтали, вертикали и диагоналях
 * <p> - ввод поля с клавиатуры
 * <p> - вывод поля на экран
 *
 * @author MehoiLs (Dorokhov Mikhail)
 */
class TicTacToeField {
protected:
    // Additional
    /**
     * Получить другого игрока.
     *
     * @param currentPlayer текущий игрок
     * @return другой игрок
     */
    static TicTacToeFieldState getOtherPlayer(TicTacToeFieldState currentPlayer) {
        return (currentPlayer == CROSS) ? ZERO : CROSS;
    }
    /**
     * Проверяет, находится ли данная позиция в пределах поля.
     *
     * @param x координата x
     * @param y координата y
     * @param fieldSize размер поля
     * @return true, если позиция находится в пределах поля
     */
    static bool isGivenPosWithinBounds(const int x, const int y, const int fieldSize) {
        return (x >= 0 && y >= 0 && x < fieldSize && y < fieldSize);
    }
    /**
     * Бросает исключение если позиция находится вне поля.
     * @see isGivenPosWithinBounds
     */
    static void assertSingleFieldEntry(const int x, const int y, const int fieldSize) {
        if (isGivenPosWithinBounds(x, y, fieldSize)) {
            throw std::invalid_argument("The field entry is out of bounds.");
        }
    }
    /**
     * Преобразует состояние поля в строку.
     *
     * @param state состояние поля
     * @return строковое представление состояния поля
     */
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
    /**
     * Создаёт поле заданного размера.
     *
     * @param fieldSize размер поля
     * @return поле заданного размера
     */
    static auto createField(const int fieldSize) {
        return vector<vector<TicTacToeFieldState>>(fieldSize, vector<TicTacToeFieldState>(fieldSize, EMPTY));
    }
    /**
     * Заполняет поле с клавиатуры.
     *
     * @param fieldSize размер поля
     * @param field поле
     */
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
    /**
     * Выводит поле на экран.
     *
     * @param field поле
     */
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
    /**
     * Выводит поле на экран с выделенной позицией.
     *
     * @param field поле
     * @param x координата x
     * @param y координата y
     */
    static void printFieldWithGivenPos(const vector<vector<TicTacToeFieldState>>& field,
                                       const int x, const int y) {
        if (field.size() > MAX_FIELD_OUTPUT_SIZE) {
            cerr << "The field is too large to be displayed.";
            cerr << "Maximum field size is " << MAX_FIELD_OUTPUT_SIZE << "x" << MAX_FIELD_OUTPUT_SIZE << endl;
            return;
        }
        for (int i = 0; i < field.size(); ++i) {
            for (int j = 0; j < field.size(); ++j) {
                bool isGivenPos = (i == y && j == x);
                if (field[i][j] == CROSS) {
                    !isGivenPos ? cout << "X " : cout << "X<";
                } else if (field[i][j] == ZERO) {
                    !isGivenPos ? cout << "0 " : cout << "0<";
                } else {
                    !isGivenPos ? cout << "- " : cout << "-<";
                }
            }
            cout << endl;
        }
    }
    /**
     * Получает текущего игрока.
     *
     * @param field поле
     * @return текущий игрок
     */
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
    /**
     * Проверяет, является ли поле правильным
     *
     * @param field поле
     * @param player текущий игрок
     * @param x координата x
     * @param y координата y
     * @param winChainLength длина выигрышной цепочки
     * @return true, если поле выигрышное
     */
    static void assertFieldIsCorrect(const int countX, const int count0) {
        if (DISABLED_ASSERTION) return;
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

    // Combo Calculations
    static int calculateHorizontalCombo(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& player,
            const int x, const int y,
            const bool ignoreEmptySpots = false
    ) {
        if ((field[y][x] != player && field[y][x] != EMPTY) ||
                (ignoreEmptySpots && field[y][x] == EMPTY)) return 0;
        int horCombo = 1;
        int leftX = x, rightX = x;
        while (--leftX >= 0) {
            if (field[y][leftX] == player) {
                horCombo++;
            } else {
                break;
            }
        }
        while (++rightX < field.size()) {
            if (field[y][leftX] == player) {
                horCombo++;
            } else {
                break;
            }
        }
        return horCombo;
    }
    static int calculateVerticalCombo(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& player,
            const int x, const int y,
            const bool ignoreEmptySpots = false
    ) {
        if ((field[y][x] != player && field[y][x] != EMPTY) ||
            (ignoreEmptySpots && field[y][x] == EMPTY)) return 0;
        int verCombo = 1;
        int upY = y, downY = y;
        while (--upY >= 0) {
            if (field[upY][x] == player) {
                verCombo++;
            } else {
                break;
            }
        }
        while (++downY < field.size()) {
            if (field[downY][x] == player) {
                verCombo++;
            } else {
                break;
            }
        }
        return verCombo;
    }
    static int calculateRevDiagonalCombo(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& player,
            const int x, const int y,
            const bool ignoreEmptySpots = false
    ) {
        if ((field[y][x] != player && field[y][x] != EMPTY) ||
            (ignoreEmptySpots && field[y][x] == EMPTY)) return 0;
        const auto fieldSize = field.size();
        int revDiagCombo = 1;
        // reverse diagonal
        int upY = y, downY = y;
        int leftX = x, rightX = x;
        while (--upY >= 0 && ++rightX < fieldSize) { // up-right
            if (field[upY][rightX] == player) {
                revDiagCombo++;
            } else {
                break;
            }
        }
        while (++downY < fieldSize && --leftX >= 0) { // down-left
            if (field[downY][leftX] == player) {
                revDiagCombo++;
            } else {
                break;
            }
        }
        return revDiagCombo;
    }
    static int calculateMainDiagonalCombo(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& player,
            const int x, const int y,
            const bool ignoreEmptySpots = false
    ) {
        if ((field[y][x] != player && field[y][x] != EMPTY) ||
            (ignoreEmptySpots && field[y][x] == EMPTY)) return 0;
        const auto fieldSize = field.size();
        int mainDiagCombo = 1;
        // main diagonal
        int upY = y, downY = y;
        int leftX = x, rightX = x;
        while (--upY >= 0 && --leftX >= 0) { // up-left
            if (field[upY][leftX] == player) {
                mainDiagCombo++;
            } else {
                break;
            }
        }
        while (++downY < fieldSize && ++rightX < fieldSize) { // down-right
            if (field[downY][rightX] == player) {
                mainDiagCombo++;
            } else {
                break;
            }
        }
        return mainDiagCombo;
    }

public:
    /**
     * Ввод поля с клавиатуры.
     *
     * @return поле
     */
    static FullFieldInfo input() {
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
            field[y-1][x-1] = state;
        }
        cout << "The field you've entered:\n";
        printField(field);
        cout << endl;

        return {field, winChainLength};
    }
};

#endif //DS_SEM4_LAB3_TICTACTOEFIELD_H
