#include "Servicios.h"
#include "set"

#include "iostream"


template <typename C> void dfs_forest(const Grafo<C> & grafo, int origen, list<int> & resultado)
{
    set<int> visitados;
    list<int> vertices;
    grafo.devolver_vertices(vertices);
    list<int>::iterator it_vertices = vertices.begin();
    while(it_vertices != vertices.end()) {
        if(visitados.find(*it_vertices) != visitados.end()) { //no esta visitado a si q llamo a dfs
           //llamo dfs
        }
        cout << *it_vertices << endl;
        it_vertices++;
    }
}

template <typename C> void dfs(const Grafo<C> & grafo, int origen, list<int> & resultado, set<int> & visitados)
{
    resultado.push_back(origen);
    list<typename Grafo<C>::Arco> adyacentes;
    grafo.devolver_adyacentes(adyacentes);
    typename list<typename Grafo<C>::Arco>::iterator it_ady = adyacentes.begin();
    while(it_ady != adyacentes.end()) {
        if(visitados.find(*it_ady) != visitados.end()) {
            dfs(grafo, resultado, visitados);
        }
        it_ady++;
    }
    visitados.insert(origen);
}

template <typename C> void bfs_forest(const Grafo<C> & grafo, int origen, list<int> & resultado);

template <typename C> void caminos(const Grafo<C> & grafo, int origen, int destino, int longitud, list<list<int> > & caminos);
