#ifndef DS_SEM4_LAB3_TICTACTOEWINPOSSIBILITYCALCULATOR_H
#define DS_SEM4_LAB3_TICTACTOEWINPOSSIBILITYCALCULATOR_H

#include "TicTacToeField.h"
using TicTacToeFieldState::ZERO;
using TicTacToeFieldState::CROSS;
using TicTacToeFieldState::EMPTY;

#include <queue>
using std::queue;

/** Реализация задачи.
 *
 * @author MehoiLs (Dorokhov Mikhail)
 */
class TicTacToeWinPossibilityCalculator : private TicTacToeField {
private:
    static const bool LOGGING_ON = true; // флаг, показывающий, включено ли логирование

    /** Метод, проверяющий, является ли данная позиция выигрышной.
     *
     * @param field - игровое поле
     * @param currentPlayer - текущий игрок (для которого производится проверка)
     * @param winChainLength - длина выигрышной комбинации
     * @param x - координата (горизонталь)
     * @param y - координата (вертикаль)
     * @param ignoreEmptySpots - игнорирование EMPTY ячеек. Используется для проверки, закончилась ли игра
     * @return true - если данная позиция выигрышная; false - иначе
     */
    static bool isGivenPosWinnable(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& currentPlayer,
            const int winChainLength,
            const int x, const int y,
            const bool ignoreEmptySpots = false
    ) {
        // if current pos is not current player's (or is not EMPTY if we `ignoreEmptySpots`) => return
        if ((field[y][x] != currentPlayer && field[y][x] != EMPTY) &&
            !(ignoreEmptySpots && field[y][x] == EMPTY)) return false;
        // try horizontal combo
        const auto horCombo = calculateHorizontalCombo(field, currentPlayer, x, y, ignoreEmptySpots);
        if (horCombo >= winChainLength) {
            return true;
        }
        // try vertical combo
        const auto verCombo = calculateVerticalCombo(field, currentPlayer, x, y, ignoreEmptySpots);
        if (verCombo >= winChainLength) {
            return true;
        }
        // try diagonal combo
        const auto mainDiagCombo = calculateMainDiagonalCombo(field, currentPlayer, x, y, ignoreEmptySpots);
        const auto revDiagCombo = calculateRevDiagonalCombo(field, currentPlayer, x, y, ignoreEmptySpots);
        if (mainDiagCombo >= winChainLength || revDiagCombo >= winChainLength) {
            return true;
        }
        // no combo => pos is not winnable
        return false;
    }

    /** Метод, собирающий все пустые пары координат в вектор.
     *
     * @param field - игровое поле
     * @return все пустые пары координат
     */
    static vector<Coordinates> collectEmptySpots(const vector<vector<TicTacToeFieldState>>& field) {
        vector<Coordinates> emptyCords;
        const int fieldSize = field.size();
        for (int y = 0; y < fieldSize; ++y) {
            for (int x = 0; x < fieldSize; ++x) {
                if (field[y][x] == EMPTY) {
                    emptyCords.emplace_back(x, y);
                }
            }
        }
        return emptyCords;
    }

    /** Метод, проверяющий, закончилась ли игра.
     *
     * @param field - игровое поле
     * @param winChainLength - длина выигрышной комбинации
     * @return true - если игра завершилась; false - иначе
     */
    //TODO - this might be optimized. rn it looks like it's not. :(
    static bool isGameFinished(const vector<vector<TicTacToeFieldState>>& field, const int winChainLength) {
        const auto fieldSize = field.size();
        for (int y = 0; y < fieldSize; ++y) {
            for (int x = 0; x < fieldSize; ++x) {
                if (isGivenPosWinnable(field, CROSS, winChainLength, x, y, true) ||
                        isGivenPosWinnable(field, ZERO, winChainLength, x, y, true)) {
                    return true;
                }
            }
        }
        return false;
    }

    /** Метод, преобразующий вектор в очередь.
     *
     * @tparam T - тип элементов в векторе
     * @param vec - вектор
     * @return очередь
     */
    template <typename T>
    static queue<T> toQueue(const vector<T>& vec) {
        queue<T> q;
        for (const auto& el : vec) {
            q.push(el);
        }
        return q;
    }

    /** Метод, заполняющий игровое поле до тех пор, пока не будет найдена выигрышная позиция.
     *
     * @param field - игровое поле
     * @param emptySpots - очередь пустых клеток
     * @param targetPlayer - игрок, для которого осуществляется проверка
     * @param currentPlayer - текущий игрок
     * @param winChainLength - длина выигрышной комбинации
     * @param foundLoseCase - флаг, показывающий, был ли найден случай, когда текущий игрок проигрывает
     */
    static void performFillFieldUntilWinSpotIsFound(
            vector<vector<TicTacToeFieldState>> field,
            queue<Coordinates> emptySpots,
            const TicTacToeFieldState& targetPlayer,
            const TicTacToeFieldState& currentPlayer,
            const int winChainLength,
            bool &foundLoseCase
    ) {
        if (emptySpots.empty()) {
            return;
        }

        /**
         * Достаём первую пустую клетку из очереди и заполняем её текущим игроком.
         * Затем высчитываем все оставшиеся пустые клетки и добавляем их в очередь.
         */
        const auto pos = emptySpots.front();
        emptySpots.pop();

        field[pos.y][pos.x] = currentPlayer;
        const auto actualEmptySpots = toQueue(collectEmptySpots(field));

        if (LOGGING_ON) {
            cerr << "Placing " << stateToString(currentPlayer) << " at (" << pos.x << ", " << pos.y << ")\n";
            printFieldWithGivenPos(field, pos.x, pos.y);
            cout << endl;
        }

        /**
         * Проверяем, является ли данная позиция выигрышной.
         * Если нет - помечаем `foundLoseCase` как true и продолжаем рекурсию.
         *
         * ПРИМЕЧАНИЕ: вообще, это можно использовать как терминальный шаг для рекурсии.
         * Т.е. как только  `foundLoseCase` станет true, можно просто выйти из рекурсии
         * (стоит добавить проверку в начало:
         * @code
         * if (foundLoseCase) return;
         * @endcode)
         * Но в данном случае, я решил оставить рекурсию, чтобы показать, что можно использовать
         * рекурсию для поиска всех возможных вариантов.
         */
        if (isGivenPosWinnable(field, currentPlayer, winChainLength, pos.x, pos.y)) {
            if (currentPlayer == targetPlayer) {
                if (LOGGING_ON) cout << "The player " << stateToString(targetPlayer) << " CAN WIN by filling the spot at (" << pos.x
                     << ", " << pos.y << ").\n\n";
            } else {
                if (LOGGING_ON) cerr << "The player " << stateToString(targetPlayer) << " WILL LOSE if the player "
                     << stateToString(currentPlayer) << " fills the spot at (" << pos.x << ", " << pos.y
                     << ").\n\n";
                foundLoseCase = true;
            }
            field[pos.y][pos.x] = EMPTY;

            performFillFieldUntilWinSpotIsFound(field, emptySpots, targetPlayer,
                                                currentPlayer, winChainLength, foundLoseCase);
        } else {
            performFillFieldUntilWinSpotIsFound(field, actualEmptySpots, targetPlayer,
                                                getOtherPlayer(currentPlayer), winChainLength, foundLoseCase);
        }
    }

    /** Метод (основной), проверяющий вероятность победы текущего игрока.
     * Выводит в консоль результат анализа.
     *
     * @param field - игровое поле
     * @param player - игрок, для которого осуществляется проверка
     * @param winChainLength - длина выигрышной комбинации
     */
    static void calculateWinPossibility(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& player,
            const int winChainLength
    ) {
        if (isGameFinished(field, winChainLength)) {
            cerr << "The game has been finished.\n";
            return;
        }
        const auto currentPlayer = getCurrentTurn(field);
        const auto emptySpots = collectEmptySpots(field);
        if (emptySpots.empty()) {
            cerr << "The field does not have any empty spots, hence the game has been finished.\n";
            return;
        }

        /**
         * Перебор всех пустых клеток и заполнение их текущим игроком.
         * Таким образом, мы создаём для рекурсии очередь с одним элементом (start-spot)
         * и запускаем рекурсивный метод, который будет заполнять все оставшиеся клетки.
         *
         * @param foundLoseCase - флаг, показывающий, был ли найден случай, когда текущий игрок проигрывает
         * */
        bool foundLoseCase = false;
        auto emptySpotsQueue = toQueue(emptySpots);
        while(!emptySpotsQueue.empty()) {
            auto cords = emptySpotsQueue.front();
            auto q = queue<Coordinates>();
            q.push(cords);
            performFillFieldUntilWinSpotIsFound(field, q, player, currentPlayer, winChainLength, foundLoseCase);
            emptySpotsQueue.pop();
        }

        if (foundLoseCase) {
            cerr << "The player " << stateToString(player) << " has a possibility to lose.\n";
        } else {
            cout << "The player " << stateToString(player) << " always wins. \n";
        }
    }

public:
    static void tests() {
        cout << "Running tests...\n" << "[TEST 1]: ";
        test1();
        cout << "[TEST 2]: ";
        test2();
    }
    static void test1() {
        const int WIN_CHAIN_LENGTH = 3;
        vector<vector<TicTacToeFieldState>> field = {
                {CROSS, ZERO,   EMPTY,  CROSS,  ZERO    },  // - 0 - - 0
                {EMPTY, ZERO,   CROSS,  EMPTY,  CROSS   },  // - 0 X - X
                {CROSS, EMPTY,  CROSS,  ZERO,   CROSS   },  // X - X 0 X
                {CROSS, ZERO,   EMPTY,  EMPTY,  ZERO    },  // X 0 - - 0
                {EMPTY, CROSS,  ZERO,   EMPTY,  ZERO    }   // - X X - 0
        };
        if (LOGGING_ON) {
            printField(field);
        }
        calculateWinPossibility(field, CROSS, WIN_CHAIN_LENGTH);
    }
    static void test2() {
        const int WIN_CHAIN_LENGTH = 3;
        vector<vector<TicTacToeFieldState>> field = {
                {CROSS, ZERO,  EMPTY  },  // X 0 -
                {CROSS, CROSS, EMPTY  },  // X X -
                {EMPTY, ZERO,  ZERO   },  // - 0 0
        };
        if (LOGGING_ON) {
            printField(field);
        }
        calculateWinPossibility(field, CROSS, WIN_CHAIN_LENGTH);
    }

    /**
     * Метод, создающий игровое поле и запускающий анализ.
     * Использовать для ручной проверки.
     */
    static void createOwnFieldAndPerformCalculations() {
        auto fieldInfo = input();
        printField(fieldInfo.field);
        auto currentPlayer = getCurrentTurn(fieldInfo.field);
        calculateWinPossibility(fieldInfo.field, currentPlayer, fieldInfo.winChainLength);
    }
};

#endif //DS_SEM4_LAB3_TICTACTOEWINPOSSIBILITYCALCULATOR_H
