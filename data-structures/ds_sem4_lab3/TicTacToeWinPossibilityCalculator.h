#ifndef DS_SEM4_LAB3_TICTACTOEWINPOSSIBILITYCALCULATOR_H
#define DS_SEM4_LAB3_TICTACTOEWINPOSSIBILITYCALCULATOR_H

#include "TicTacToeField.h"
using TicTacToeFieldState::ZERO;
using TicTacToeFieldState::CROSS;
using TicTacToeFieldState::EMPTY;

vector<vector<TicTacToeFieldState>> TEST_FIELD = {
        {EMPTY, ZERO,   EMPTY,  CROSS,  ZERO    },  // - 0 - - 0
        {EMPTY, ZERO,   CROSS,  CROSS,  EMPTY   },  // - 0 X X -
        {CROSS, ZERO ,  CROSS,  ZERO,   CROSS   },  // X 0 X 0 X
        {CROSS, ZERO,   EMPTY,  EMPTY,  ZERO    },  // X 0 - - 0
        {EMPTY, CROSS,  CROSS,  EMPTY,  ZERO    }   // - X X - 0
};

class TicTacToeWinPossibilityCalculator : private TicTacToeField {
private:
    static bool isGivenPosWinnable(
            const vector<vector<TicTacToeFieldState>>& field,
            const TicTacToeFieldState& currentPlayer,
            const int winChainLength,
            const int x, const int y,
            const bool ignoreEmptySpots = false
    ) {
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
        const auto currentTurn = getCurrentTurn(field);
        const auto emptySpots = collectEmptySpots(field);
        if (emptySpots.empty()) {
            cerr << "The field does not have any empty spots, hence the game has been finished.\n";
            return;
        }

        // we need to calculate how many 'win spots' does current player have.
        vector<Coordinates> currentPlayerWinSpots;
        for (auto &pos : emptySpots) {
            if (isGivenPosWinnable(field, player, winChainLength, pos.x, pos.y)) {
                currentPlayerWinSpots.emplace_back(pos.x, pos.y);
            }
        }

        // we need to calculate how many 'win spots' does OTHER player have.
        vector<Coordinates> otherPlayerWinSpots;
        for (auto &pos : emptySpots) {
            if (isGivenPosWinnable(field, otherPlayer, winChainLength, pos.x, pos.y)) {
                otherPlayerWinSpots.emplace_back(pos.x, pos.y);
            }
        }

        if (currentPlayerWinSpots.empty()) {
            cerr << "Current player cannot win, since they don't have any 'win spots'.\n";
            return;
        } else if (currentPlayerWinSpots.size() == 1 && currentTurn != player) {
            if (emptySpots.size() == 1) {
                cerr << "Current player cannot win, since they have only one 'win spot' (the only empty spot on the field) "
                        "and current turn is going to be made by other player who can only place a " +
                        stateToString(otherPlayer) + " on the only 'win spot', which is: " +
                        currentPlayerWinSpots[0].toString() + ".\n";
            } else {
                cout << "Current player can win, but only if the other player decides to place a " +
                stateToString(otherPlayer) + " on an any other spot but " + currentPlayerWinSpots[0].toString() + ".\n";
            }
            return;
        } else if (currentPlayerWinSpots.size() == 1 && currentTurn == player) {
            cout << "Current player CAN win, since they have 1 'win spot' (" + currentPlayerWinSpots[0].toString() + ").\n";
            if (emptySpots.size() == 1) {
                cout << "Therefore, current player ALWAYS wins, since they only have one spot to make a move on and it's their turn.\n";
            } else {
                cerr << "However, current player WILL NOT ALWAYS win, since there are more than 1 empty spots "
                        "on the field. Thus, if they decide to place a " + stateToString(otherPlayer) +
                        "on any other spot but the given, they won't win on this turn.";
            }
            return;
        } else if (currentPlayerWinSpots.size() > 1 && currentTurn == player) {
            cout << "Current player ALWAYS wins, since they have more than 1 'win spots' and it's their turn.\n";
        } else if (currentPlayerWinSpots.size() > 1 && currentTurn != player) {
            if (otherPlayerWinSpots.empty()) {
                cout << "Current player ALWAYS wins, since they have more than 1 'win spots' and the other player "
                        "cannot win on the current turn.\n";
            } else {
                cerr << "Current player WILL NOT ALWAYS win. They do have more than 1 'win spots', but so do "
                        "the other player, whose turn is the current. Thus, if the other player places a " +
                        stateToString(otherPlayer) + " on any of the given spots: ";
                for (auto &spot : otherPlayerWinSpots) {
                    cerr << spot.toString() + " ";
                }
                cerr << "- they will win.";
            }
        }


    }

public:
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
                {EMPTY, CROSS, ZERO   },  // - X 0
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
