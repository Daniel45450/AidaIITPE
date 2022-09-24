#ifndef SERVICIOS_H_INCLUDED
#define SERVICIOS_H_INCLUDED
#include "Grafo.h"

template <typename C> void dfs_forest(const Grafo<C> & grafo, list<int> & orden);

template <typename C> void bfs_forest(const Grafo<C> & grafo, list<int> & orden);

template <typename C> void caminos(const Grafo<C> & grafo, int origen, int destino, int longitud, list<list<int> > & caminos);

#endif // SERVICIOS_H_INCLUDED
