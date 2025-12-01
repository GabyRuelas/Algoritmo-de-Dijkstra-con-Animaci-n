#ifndef GRAPH_H
#define GRAPH_H

#include <vector>   // para usar vectores dinámicos
#include <string>   // para usar std::string
#include <utility>  // para usar std::pair

// dist[i]= distancia min desde el origen hasta el nodo i
// parent[i] =nodo "padre" 

struct DijkstraResult {
    std::vector<double> dist;
    std::vector<int> parent;
};

class Graph { // representa el grafo con sus nodos y caminos
public:
    // Crea un grafo con n nodos
    Graph(int n, const std::vector<std::string>& names = {});

    // Agrega una arista entre u y v con cierto peso (distancia
    // Si undirected = true, el camino va en dos sentidos

    void add_edge(int u, int v, double weight, bool undirected = true);
    // Imprime el grafo como lista de adyacencia
    void print_graph() const;

 // Si animate = true, muestralos nodos visitadps
    DijkstraResult dijkstra(int start, bool animate = false) const;

    // Imprime la ruta más corta
    void print_shortest_path(int start, int dest,
                             const std::vector<int>& parent,
                             const std::vector<double>& dist) const;

    // Return de losnombres de ls nodos
    const std::vector<std::string>& names() const { return node_names; }

private:
    int n; // numde nodos
    // Lista de adyacencia y guardamos (vecino, peso)
    std::vector<std::vector<std::pair<int,double>>> adj;
    std::vector<std::string> node_names; // nombres de los lugares

    // Vuelve a construir el camino mas corot
    std::vector<int> reconstruct_path(int start, int dest,
                                      const std::vector<int>& parent) const;

    // Para la animacion se imprime el estado actual
    void print_animation_state(const std::vector<double>& dist,
                               const std::vector<bool>& visited,
                               int current) const;
};

#endif // GRAPH_H
