#ifndef DS_SEM4_LAB5_EMPIRE_H
#define DS_SEM4_LAB5_EMPIRE_H

#include <stdexcept>
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;

#include <vector>
using std::vector;
#include <set>
#include <algorithm>

using std::set;

constexpr static int CAPITAL = 0;

enum Planet {
    SELF,
    TELEPORT,
    NONE
};

class Empire {
private:
    int planetsCount;
    int teleportsCount;

    vector<vector<Planet>> empireGraph;

    static bool setContainsPlanet(const set<int>& planets, const int targetPlanet) {
        return std::any_of(planets.begin(), planets.end(),
                           [targetPlanet](int planet) { return planet == targetPlanet; });
    }
    static int toPlanet(int planet) {
        return planet - 1;
    }
    void placeTeleport(int a, int b) {
        empireGraph[a-1][b-1] = TELEPORT;
    }
    void validateFields() const {
        if (planetsCount < 2 || planetsCount > 105) {
            throw std::invalid_argument("Planets count must be at least 2 and at most 105");
        }
        if (teleportsCount < 2 || teleportsCount > 2*105) {
            throw std::invalid_argument("Teleports count must be at least 2 and at most 2*105");
        }
    }
    static auto createGraph(const int size) {
        return vector<vector<Planet>>(size, vector<Planet>(size, NONE));
    }

    bool isPlanetReachable(int planetFrom, const int targetPlanet, set<int>& visited) const {
        visited.insert(planetFrom);
        if (planetFrom == targetPlanet) {
            return false;
        }
        if (empireGraph[planetFrom][targetPlanet] == TELEPORT) {
            return true;
        }
        for (int planet = 0; planet < planetsCount; ++planet) {
            if (planet == planetFrom || setContainsPlanet(visited, planet)) {
                continue;
            }
            if (empireGraph[planetFrom][planet] == TELEPORT) {
                return isPlanetReachable(planet, targetPlanet, visited);
            }
        }
        return false;
    }
    [[nodiscard]] bool isPlanetReachable(int planetFrom, const int targetPlanet) const {
        set<int> visited;
        return isPlanetReachable(planetFrom, targetPlanet, visited);
    }

    int performCalculations() {
        set<int> unreachablePlanets;
        for (int planet = 2; planet <= planetsCount; ++planet) {
            if (!isPlanetReachable(CAPITAL, toPlanet(planet))) {
                unreachablePlanets.insert(planet);
            }
        }
        if (unreachablePlanets.empty()) {
            return 0;
        }
        else {
            recc(empireGraph, unreachablePlanets, {}, CAPITAL, 0);
        }
    }
    int recc(vector<vector<Planet>> empire, set<int> unreachablePlanets, set<std::pair<int, int>> triedTeleports, int from, int count) {
       //TODO might impl something like backtracking here, trying to place a teleport on each spot
    }

public:
    Empire() = default;
    Empire(int planetsCount, int teleportsCount) {

        this->planetsCount = planetsCount;
        this->teleportsCount = teleportsCount;
        empireGraph.resize(planetsCount);
    };

    void input() {
        int n, m;
        cout << "Enter the planets count (n) and teleports count (m): ";
        cin >> n >> m;

        this->planetsCount = n;
        this->teleportsCount = m;
        validateFields();

        cout << "Place teleports, where 'ai' - planet from, 'bi' - planet to: ";
        int i = 0;
        while (i < teleportsCount) {
            int a, b;
            cin >> a >> b;
            if (a < 1 || a > planetsCount || b < 1 || b > planetsCount) {
                cerr << "Planets must be in range from 1 to " << planetsCount << "\n";
                continue;
            }
            if (a == b) {
                cerr << "Planets must be different\n";
                continue;
            }
            placeTeleport(a, b);
            i++;
        }
        for (int j = 0; j < planetsCount; ++j) {
            empireGraph[j][j] = SELF; // no teleport to itself
        }
    }
    void test() {
        this->planetsCount = 6;
        this->teleportsCount = 4;
        this->empireGraph = createGraph(planetsCount);

        placeTeleport(3, 1);
        placeTeleport(4, 6);
        placeTeleport(1, 2);
        placeTeleport(4, 5);

        performCalculations();
    }
};

#endif //DS_SEM4_LAB5_EMPIRE_H
