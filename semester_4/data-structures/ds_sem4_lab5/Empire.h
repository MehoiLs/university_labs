#ifndef DS_SEM4_LAB5_EMPIRE_H
#define DS_SEM4_LAB5_EMPIRE_H

#include <stdexcept>
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;

#include <vector>
#include <stack>
using std::vector;
using std::stack;

#include <algorithm>

constexpr static int CAPITAL = 0;

class Empire {
private:
    int planetsCount;
    int teleportsCount;

    vector<vector<int>> empireGraph;
    vector<vector<int>> transportedEmpireGraph;

    void placeTeleport(int a, int b) {
        empireGraph[a - 1][b - 1] = 1;
        transportedEmpireGraph[b - 1][a - 1] = 1;
    }
    void init() {
        this->empireGraph = vector<vector<int>>(planetsCount, vector<int>(planetsCount, 0));
        this->transportedEmpireGraph = vector<vector<int>>(planetsCount, vector<int>(planetsCount, 0));
    }
    void validateFields() const {
        if (planetsCount < 2 || planetsCount > 105) {
            throw std::invalid_argument("Planets count must be at least 2 and at most 105");
        }
        if (teleportsCount < 2 || teleportsCount > 2*105) {
            throw std::invalid_argument("Teleports count must be at least 2 and at most 2*105");
        }
    }

    /**
     * Depth-first search for the main graph. It fills the stack with the topologicalOrder of vertices and also
     * marks them as visited.
     *
     * @param currentPlanet - current vertex (planet)
     * @param visited - vector of visited vertices (planets)
     * @param topologicalOrder - stack of vertices (planets) in topological order
     */
    void topologicalSortDFS(int currentPlanet, vector<bool>& visited, stack<int>& topologicalOrder) const {
        visited[currentPlanet] = true;
        for (int planetTo = 0; planetTo < planetsCount; ++planetTo) {
            if (empireGraph[currentPlanet][planetTo] && !visited[planetTo]) {
                topologicalSortDFS(planetTo, visited, topologicalOrder);
            }
        }
        topologicalOrder.push(currentPlanet);
    }

    /**
     * Depth-first search for the transported graph. It marks the vertices with the same componentColors if they are connected.
     *
     * @param currentPlanet - current vertex
     * @param componentColors - vector of colors for each vertex
     * @param currentComponent - current componentColors
     */
    void markSCComponentsDFS(int currentPlanet, vector<int>& componentColors, int currentComponent) const {
        componentColors[currentPlanet] = currentComponent;
        for (int planetTo = 0; planetTo < planetsCount; ++planetTo) {
            if (transportedEmpireGraph[currentPlanet][planetTo] && componentColors[planetTo] == -1) {
                markSCComponentsDFS(planetTo, componentColors, currentComponent);
            }
        }
    }

    /**
     * Main function that performs the calculations.
     * @return count of required teleports to build
     */
    int performCalculations() {
        vector<bool> visitedPlanets(planetsCount, false);
        stack<int> topologicalOrder;

        // First DFS to build an order of traversal between planets
        for (int planet = 0; planet < planetsCount; planet++) {
            if (!visitedPlanets[planet]) {
                topologicalSortDFS(planet, visitedPlanets, topologicalOrder);
            }
        }

        vector<int> color(planetsCount, -1); // Stores the colors of the connected components
        int currentComponent = 0;

        // Second DFS to find the component
        while (!topologicalOrder.empty()) {
            int planet = topologicalOrder.top();
            topologicalOrder.pop();
            if (color[planet] == -1) {
                markSCComponentsDFS(planet, color, currentComponent++);
            }
        }

        vector<bool> isSourceComponent(currentComponent, true); // Stores the components that are sources
        for (int i = 0; i < planetsCount; i++) {
            for (int to = 0; to < planetsCount; ++to) {
                if (empireGraph[i][to] && color[i] != color[to]) {
                    isSourceComponent[color[to]] = false;
                }
            }
        }
        isSourceComponent[color[CAPITAL]] = false; // The capital is not a source
        int requiredTeleports = 0;
        for (bool source : isSourceComponent) {
            if (source) { // If the component is a source, then we need to build a teleport
                requiredTeleports++;
            }
        }

        return requiredTeleports;
    }

public:
    Empire(): planetsCount(2), teleportsCount(2) {
        init();
    }
    Empire(int planetsCount, int teleportsCount) {
        this->planetsCount = planetsCount;
        this->teleportsCount = teleportsCount;
        init();
    }

    /**
     * Manual input of planets and teleports count and teleports placement.
     */
    void input() {
        int n, m;
        cout << "Enter the planets count (n) and teleports count (m): ";
        cin >> n >> m;

        this->planetsCount = n;
        this->teleportsCount = m;
        validateFields();
        init();

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
    }

    /**
     * Automatic test with predefined values, mentioned in the task.
     */
    void test() {
        this->planetsCount = 6;
        this->teleportsCount = 4;
        init();

        placeTeleport(3, 1);
        placeTeleport(4, 6);
        placeTeleport(1, 2);
        placeTeleport(4, 5);

        int result = performCalculations();
        cout << "Required additional teleports: " << result << "\n";
    }
};

#endif //DS_SEM4_LAB5_EMPIRE_H
