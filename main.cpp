
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Placeholder for infinity

vector<int> dijkstra(int n, int origen, const vector<vector<pair<int, int>>> &grafo, vector<int> &prev) {
    vector<int> distancias(n, INF);
    distancias[origen] = 0;

    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,origen});

    while(!pq.empty()) {
        int distancias_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();

        if(distancias_actual > distancias[nodo_actual]) continue;

        for(auto &vecino : grafo[nodo_actual]) {
            int siguiente = vecino.first;
            int peso = vecino.second;

            if(distancias[nodo_actual] + peso < distancias[siguiente]) {
                distancias[siguiente] = distancias[nodo_actual] + peso;
                prev[siguiente] = nodo_actual;
                pq.push({distancias[siguiente], siguiente});
            }
        }
    }

    return distancias;
}

vector<int> reconstruirCamino(int inicio, int fin, const vector<int>& prev) {
    vector<int> camino;
    for (int at = fin; at != -1; at = prev[at])
        camino.push_back(at);

    // Invertir el vector manualmente sin <algorithm>
    int start = 0, end = camino.size() - 1;
    while (start < end) {
        swap(camino[start], camino[end]);
        start++;
        end--;
    }

    if (camino[0] == inicio)
        return camino;
    return {};
}

int main() {
    int n = 4; // Número de nodos

    vector<vector<pair<int,int>>> grafo(n); // Inicializar grafo

    // Agregar aristas con sus pesos
    grafo[0].push_back({1, 211});
    grafo[1].push_back({0, 211});
    grafo[1].push_back({2, 157});
    grafo[2].push_back({1, 157});
    grafo[2].push_back({3, 206});
    grafo[3].push_back({2, 206});
    grafo[3].push_back({0, 153});
    grafo[0].push_back({3, 153});

    int origen, destino;
    while (true) {
        cout << "Ingrese el nodo de inicio (0-3): ";
        cin >> origen;
        if (origen >= 0 && origen < n) break;
        cout << "Ese nodo no existe, por favor reintentar.\n";
    }
    while (true) {
        cout << "Ingrese el nodo de destino (0-3): ";
        cin >> destino;
        if (destino >= 0 && destino < n) break;
        cout << "Ese nodo no existe, por favor reintentar.\n";
    }

    vector<int> prev(n, -1);
    vector<int> distancias = dijkstra(n, origen, grafo, prev);
    vector<int> camino = reconstruirCamino(origen, destino, prev);

    cout << "La distancia más corta de " << origen << " a " << destino << ":\n";
    cout << "Camino elegido: ";
    for (int v : camino)
        cout << v << " ";
    cout << "\nDistancia total: " << distancias[destino] << " metros\n";
    cout << "Pasos tomados: " << camino.size() - 1 << "\n";

    return 0;
}
