#include "Servicios.h"
#include "set"

#include "iostream"


template <typename C> void dfs_forest(const Grafo<C> & grafo, list<int> & orden)
{
    set<int> visitados;
    list<int> vertices;
    grafo.devolver_vertices(vertices);
    list<int>::iterator it_vertices = vertices.begin();
    while(it_vertices != vertices.end()) {
        if(visitados.find(*it_vertices) == visitados.end()) { //no esta visitado a si q llamo a dfs
           dfs(grafo, *it_vertices, orden, visitados);
        }
        it_vertices++;
    }
}

template <typename C> void dfs(const Grafo<C> & grafo, int origen, list<int> & orden, set<int> & visitados)
{
    orden.push_back(origen);
    list<typename Grafo<C>::Arco> adyacentes;
    grafo.devolver_adyacentes(origen, adyacentes);
    typename list<typename Grafo<C>::Arco>::iterator it_ady = adyacentes.begin();
    while(it_ady != adyacentes.end()) {
        if(visitados.find(it_ady->devolver_adyacente()) == visitados.end()) {
            dfs(grafo, it_ady->devolver_adyacente(), orden, visitados);
        }
        it_ady++;
    }
    visitados.insert(origen);
}

template <typename C> void bfs_forest(const Grafo<C> & grafo, list<int> & orden)
{
    set<int> visitados;
    list<int> vertices;
    grafo.devolver_vertices(vertices);
    list<int>::iterator it_vertices = vertices.begin();
    while(it_vertices != vertices.end()) {
        if(visitados.find(*it_vertices) == visitados.end()) {
            bfs(grafo, *it_vertices, orden, visitados);
        }
        it_vertices++;
    }
}

template <typename C> bfs(const Grafo<C> & grafo, int origen, list<int> & orden, set<int> & visitados)
{
    orden.push_back(origen);
    list<typename Grafo<C>::Arco> adyacentes;
    grafo.devolver_adyacentes(origen, adyacentes);
    typename list<typename Grafo<C>::Arco>::iterator it_adyacentes = adyacentes.begin();
    while(it_adyacentes != adyacentes.end()) {
        orden.push_back(it_adyacentes->devolver_adyacente());
        visitados.insert(it_adyacentes->devolver_adyacente());
        it_adyacentes++;
    }
}

template <typename C> void caminos(const Grafo<C> & grafo, int origen, int destino, int longitud, list<list<int> > & caminos);

template void dfs_forest<int>(const Grafo<int> & grafo, list<int> & orden);
template void bfs_forest<int>(const Grafo<int> & grafo, list<int> & orden);
