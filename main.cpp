#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include "Graph.h"

// grafo de 15 nodos de lugares de gdl con distancias aproximadas
Graph build_sample_graph_15() {
    std::vector<std::string> names = {
        "La Minerva",             // 0
        "Catedral GDL",           // 1
        "Expo Guadalajara",       // 2
        "Estadio Jalisco",        // 3
        "Tlaquepaque Centro",     // 4
        "Andares",                // 5
        "Tec GDL",                // 6
        "Plaza del Sol",          // 7
        "Parque Metropolitano",   // 8
        "Centro Zapopan",         // 9
        "San Juan de Dios",       // 10
        "Plaza Galerías",         // 11
        "Auditorio Telmex",       // 12
        "Aeropuerto GDL",         // 13
        "Museo de las Artes"      // 14
    };

    Graph g(15, names);

    //dist aproximadas en kilometros
    g.add_edge(0, 1, 3.9);   // Minerva-Catedral
    g.add_edge(0, 2, 2.4);   // Minerva-Expo
    g.add_edge(0, 5, 4.3);   // Minerva Andares
    g.add_edge(0, 7, 3.0);   // Minerva-Plaza del Sol

    g.add_edge(1, 3, 5.2);   // CatedralEstadio
    g.add_edge(1, 4, 6.8);   // Catedral-Tlaquepaque
    g.add_edge(1, 10, 1.5);  // Catedral-San Juan de Dios
    g.add_edge(1, 14, 2.0);  // Catedral-Museo de las Artes

    g.add_edge(2, 7, 2.0);   // Expo-Plaza del Sol
    g.add_edge(2, 6, 7.1);   // Expo-Tec gdl

    g.add_edge(7, 6, 5.0);   // Plaza del Sol-Tec gdl

    g.add_edge(5, 9, 5.0);   // Andares-Centro Zapopan
    g.add_edge(8, 5, 3.0);   // Parque Metropolitano-Andares

    g.add_edge(9, 11, 4.0);  // Centro Zapopan-Galerías
    g.add_edge(11, 12, 2.5); // Galerías-Auditorio Telmex

    g.add_edge(3, 10, 4.0);  // Estadio- San Juan de Dios

    g.add_edge(10, 4, 4.0);  // San Juan de Dios-Tlaquepaque
    g.add_edge(4, 13, 14.0); // Tlaquepaque-Aeropuerto

    g.add_edge(6, 14, 4.0);  // Tec gdl-Museo de las Artes

    return g;
}

int main() {
    Graph g = build_sample_graph_15();

    std::cout << "==== Grafo de Guadalajara (15 nodos)====\n\n";
    g.print_graph();

    // mostrar lista de nodos
    const auto& names = g.names();
    std::cout << "Nodos disponibles:\n";
    for (int i = 0; i < (int)names.size(); ++i) {
        std::cout << i << " -> " << names[i] << "\n";
    }
    std::cout << "\n";

    int start, dest;
    std::cout << "Elige el indice del nodo origen: ";
    std::cin >> start;
    std::cout << "Elige el indice del nodo destino: ";
    std::cin >> dest;

    // alidar que los indices sean correctos
    if (start < 0 || start >= (int)names.size() ||
        dest   < 0 || dest   >= (int)names.size()) {
        std::cout << "Indices invalidos. Terminando programa.\n";
        return 0;
    }

    // limiar buffer 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nIniciando algoritmo de Dijkstra desde ["
              << names[start] << "]...\n\n";

    //ejecutar Dijkstra con animacionpaso a paso 
    auto res = g.dijkstra(start, true);

    //distancias finales
    std::cout << "\n=== Distancias mínimas desde ["
              << names[start] << "] ===\n";
    for (int i = 0; i < (int)res.dist.size(); ++i) {
        std::cout << "A " << names[i] << ": "
                  << std::fixed << std::setprecision(2)
                  << res.dist[i] << " km\n";
    }

    //mostrar la ruta mas corta
    std::cout << "\n=== Ruta más corta===\n";
    g.print_shortest_path(start, dest, res.parent, res.dist);

    return 0;
}
