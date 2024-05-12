#ifndef DS_SEM4_LAB3_TICTACTOEWINPOSSIBILITYCALCULATOR_H
#define DS_SEM4_LAB3_TICTACTOEWINPOSSIBILITYCALCULATOR_H

#include "TicTacToeField.h"
using TicTacToeFieldState::ZERO;
using TicTacToeFieldState::CROSS;
using TicTacToeFieldState::EMPTY;

#include <queue>
using std::queue;

//TODO REMOVE
#include <thread>
#include <chrono>

/** Реализация задачи.
 *
 * @author MehoiLs (Dorokhov Mikhail)
 */
class TicTacToeWinPossibilityCalculator : private TicTacToeField {
private:
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

    template <typename T>
    static queue<T> toQueue(const vector<T>& vec) {
        queue<T> q;
        for (const auto& el : vec) {
            q.push(el);
        }
        return q;
    }

    static void performFillFieldUntilWinSpotIsFound(
            vector<vector<TicTacToeFieldState>> field,
            queue<Coordinates> emptySpots,
            const TicTacToeFieldState& targetPlayer,
            const TicTacToeFieldState& currentPlayer,
            const int winChainLength
    ) {
        if (emptySpots.empty()) {
            return;
        }

        const auto pos = emptySpots.front();
        emptySpots.pop();

        field[pos.y][pos.x] = currentPlayer;
        const auto actualEmptySpots = toQueue(collectEmptySpots(field));

        //TODO REMOVE 'sleep_for'
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cerr << "Placing " << stateToString(currentPlayer) << " at (" << pos.x << ", " << pos.y << ")\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        printFieldWithGivenPos(field, pos.x, pos.y);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        cout << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        if (isGivenPosWinnable(field, currentPlayer, winChainLength, pos.x, pos.y)) {
            if (currentPlayer == targetPlayer) {
                cout << "The player " << stateToString(targetPlayer) << " CAN WIN by filling the spot at (" << pos.x
                     << ", " << pos.y << ").\n\n";
            } else {
                cerr << "The player " << stateToString(targetPlayer) << " WILL LOSE if the player "
                     << stateToString(currentPlayer) << " fills the spot at (" << pos.x << ", " << pos.y
                     << ").\n\n";
            }
            field[pos.y][pos.x] = EMPTY;


            //TODO I have to find out how do I handle terminating the recursion correctly here.
            //  It does check all the empty spots, but it does not stop after finding all of them.
            
            performFillFieldUntilWinSpotIsFound(field, emptySpots, targetPlayer,
                                                currentPlayer, winChainLength);
        } else {
            performFillFieldUntilWinSpotIsFound(field, actualEmptySpots, targetPlayer,
                                                getOtherPlayer(currentPlayer), winChainLength);
        }
    }

    /** Метод (основной), проверяющий вероятность победы текущего игрока.
     * Выводит в консоль результат анализа.
     *
     * @param field - игровое поле
     * @param player - игрок, для которого осуществляется проверка
     * @param winChainLength - длина выигрышной комбинации
     */
    //TODO - this have to be BACKTRACKING. Can it be considered as one rn?
    //TODO Ремарка: возможно стоит прикрутить рекурсию к списку пустых позиций, последовательно эти позиции заполнять в поле
    //  и проверять, является ли результат заполнения выигрышным для той или иной стороны.
    static void calculateWinPossibility(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& player,
            const int winChainLength
    ) {
        if (isGameFinished(field, winChainLength)) {
            cerr << "The game has been finished.\n";
            return;
        }
        const auto otherPlayer = getOtherPlayer(player);
        const auto currentPlayer = getCurrentTurn(field);
        const auto emptySpots = collectEmptySpots(field);
        if (emptySpots.empty()) {
            cerr << "The field does not have any empty spots, hence the game has been finished.\n";
            return;
        }

        auto emptySpotsQueue = toQueue(emptySpots);
        performFillFieldUntilWinSpotIsFound(field, emptySpotsQueue, player, currentPlayer, winChainLength);
//        for (int i = 0; i < emptySpots.size(); ++i) {
//            performFillFieldUntilWinSpotIsFound(field, emptySpotsQueue, player, currentPlayer, winChainLength);
//            emptySpotsQueue.pop();
//        }
    }

public:
    static void tests() {
        test1();
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
        printField(field);
        calculateWinPossibility(field, CROSS, WIN_CHAIN_LENGTH);
    }
    static void test2() {
        const int WIN_CHAIN_LENGTH = 3;
        vector<vector<TicTacToeFieldState>> field = {
                {CROSS, ZERO,  ZERO   },  // X 0 0
                {CROSS, CROSS, EMPTY  },  // X X -
                {EMPTY, EMPTY, ZERO   },  // - - 0
        };
        printField(field);
        calculateWinPossibility(field, CROSS, WIN_CHAIN_LENGTH);
    }

    static void createOwnFieldAndPerformCalculations() {
        auto fieldInfo = input();
        printField(fieldInfo.field);
        auto currentPlayer = getCurrentTurn(fieldInfo.field);
        calculateWinPossibility(fieldInfo.field, currentPlayer, fieldInfo.winChainLength);
    }
};

#endif //DS_SEM4_LAB3_TICTACTOEWINPOSSIBILITYCALCULATOR_H
