#include "Graph.h" 
#include <iostream>
#include <queue> // para poder usar cola de prioridad
#include <limits> // poder isar nums miy grnades
#include <iomanip> // frmatear la salida
#include <algorithm> 

Graph::Graph(int n, const std::vector<std::string>& names)
    : n(n), adj(n), node_names(names) {

    // Si no hay suficientes nombres rellenar con nodo i
    if ((int)node_names.size() != n) {
        node_names.resize(n);
        for (int i = 0; i < n; ++i) {
            if (node_names[i].empty()) {
                node_names[i] = "Nodo " + std::to_string(i);
            }
        }
    }
}

void Graph::add_edge(int u, int v, double weight, bool undirected) { //agregar aristas entre u y v
    // Validar los indices para evitar errores
    if (u < 0 || u >= n || v < 0 || v >= n) return;

    adj[u].push_back({v, weight});
    if (undirected) { // doblre sentido
        adj[v].push_back({u, weight});
    }
}

// imprimir el grafo como lista de adyacencia
void Graph::print_graph() const {
    std::cout << "=== Lista de adyacencia ===\n";
    for (int u = 0; u < n; ++u) {
        std::cout << u << " [" << node_names[u] << "] -> "; // print del indice y nombre del nodo
        for (auto &edge : adj[u]) { // recorre los aristas del nodo u
            std::cout << "(" << edge.first << " " << node_names[edge.first]
                      << ", " << edge.second << " km) ";
        }
        std::cout << "\n"; // salto de linea 
    }
    std::cout << "===================================\n\n"; // visualmente mas organizado
}

//implementacion del algoritmo
DijkstraResult Graph::dijkstra(int start, bool animate) const {
    const double INF = std::numeric_limits<double>::infinity(); // INF es infinito

    std::vector<double> dist(n, INF);    // distancias minimas
    std::vector<int> parent(n, -1);      // para volver a construir el camino
    std::vector<bool> visited(n, false); // marca si un nodo ya fue procesado

    using PDI = std::pair<double,int>; // (distancia acumulada, nodo)
    std::priority_queue<PDI, std::vector<PDI>, std::greater<PDI>> pq; // cola de prioridad que saca el par que tenga la menior distancia

    dist[start] = 0.0;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        // Animación
      //mostrar el estado actual despues de visitar u
        if (animate) {
            print_animation_state(dist, visited, u);
            std::cout << "Presiona ENTER para continuar...\n"; // mensaje para el usuario
            std::string dummy; // leer la linea vacia
            std::getline(std::cin, dummy); // esperar a que el usuario presione enter
        }

        // Recorrer aristas desde u
        for (auto &edge : adj[u]) {
            int v = edge.first; // nodo vecino
            double w = edge.second; //peso o distancua de la arista
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return {dist, parent};
}

std::vector<int> Graph::reconstruct_path(int start, int dest,
                                         const std::vector<int>& parent) const {
    std::vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end()); //invertikmos el orden para que quede de start a dest
    if (path.empty() || path.front() != start) {
        path.clear(); // no hay camino válido
    }
    return path;
}

void Graph::print_shortest_path(int start, int dest, //imprime la ruta mas corta y la distancia total
                                const std::vector<int>& parent,
                                const std::vector<double>& dist) const {
    auto path = reconstruct_path(start, dest, parent); // obtenemos el camino mas corto como lista de nodos
    if (path.empty()) {
        std::cout << "No existe camino de " << node_names[start]
                  << " a " << node_names[dest] << ".\n";
        return;
    }

    std::cout << "\nRuta más corta " << node_names[start]
              << " -> " << node_names[dest] << ":\n  ";

    //colorea todo el camino
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << "\033[36m" << node_names[path[i]] << "\033[0m";
        if (i + 1 < path.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << "\n  Distancia total: "
              << std::fixed << std::setprecision(2)
              << dist[dest] << " km\n\n";
}

void Graph::print_animation_state(const std::vector<double>& dist,
                                  const std::vector<bool>& visited,
                                  int current) const {
    const double INF = std::numeric_limits<double>::infinity();

    std::cout << "=============================================\n";
    std::cout << "Nodo actual visitado: \033[33m" << current
              << " [" << node_names[current] << "]\033[0m\n";
//imprime el nodo actual en amarillo con su nombre
    std::cout << "Nodos visitados: ";
    bool alguno = false;
    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            std::cout << "\033[32m" << i << "\033[0m ";
          // imprime el indice del nodo en verde
            alguno = true;
        }
    }
    if (!alguno) {
        std::cout << "(ninguno)";
    }

    std::cout << "\n\nDistancias actuales desde el origen:\n";

    for (int i = 0; i < n; ++i) {
        // Color según el estado
        if (i == current) {
            std::cout << "\033[33m"; // amarillo para el nodo actual
        } else if (visited[i]) {
            std::cout << "\033[32m"; // verde para los ya visitados
        }

        std::cout << "  " << i << " [" << node_names[i] << "]: ";
        if (dist[i] == INF) { // si la distancia sigue siendo infitina
            std::cout << "INF";
        } else {
            std::cout << std::fixed << std::setprecision(2)
                      << dist[i] << " km";
        }

        // Reset de color
        std::cout << "\033[0m\n";
    }
    std::cout << "=============================================\n";
}
