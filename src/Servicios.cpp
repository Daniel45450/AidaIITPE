#include "Servicios.h"
#include "set"

#include "iostream"


template <typename C> void dfs_forest(const Grafo<C> & grafo, list<int> & orden)
    /*
      se consulta si cada vertice es visitado O(nlog(n)) y por c/u se llama a dfs resultando en
      O(nelog(n)^2)
    */
{
    set<int> visitados;
    list<int> vertices;
    grafo.devolver_vertices(vertices); //O(n)
    list<int>::iterator it_vertices = vertices.begin();
    while(it_vertices != vertices.end()) { //O(v)
        if(visitados.find(*it_vertices) == visitados.end()) { // O(log(n))//no esta visitado a si q llamo a dfs
           dfs(grafo, *it_vertices, orden, visitados); //O(elog(n))
        }
        it_vertices++;
    }
}

template <typename C> void dfs(const Grafo<C> & grafo, int origen, list<int> & orden, set<int> & visitados)
/*
    O(elog(n)): en el peor de los casos se recorren todos los arcos del grafo y por cada uno se comprueba si fue visitado el vertice adyacente,
     el metodo find() de set pertenece a O(log(n)), ya que en el peor caso tendra todo los vertices almacenados
*/
{
    orden.push_back(origen);
    visitados.insert(origen);
    list<typename Grafo<C>::Arco> adyacentes;
    grafo.devolver_adyacentes(origen, adyacentes); //O(max(log(n), e) e= arcos
    typename list<typename Grafo<C>::Arco>::iterator it_ady = adyacentes.begin();
    while(it_ady != adyacentes.end()) { //O(e)
        if(visitados.find(it_ady->devolver_adyacente()) == visitados.end()) { //O(log(n))
            dfs(grafo, it_ady->devolver_adyacente(), orden, visitados);
        }
        it_ady++;
    }
}

template <typename C> void bfs_forest(const Grafo<C> & grafo, list<int> & orden)
/*
    Recorro todo los vertices O(n) * O(log(n)) comprobar si los vertices estan visitados * O(elog(n)) BFS
    RESULTA EN O(nelog(n))^2
*/
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
/*
    O(elog(n)) por cada vertice recorro sus adyacentes y compruebo si ya los visite.
*/
{
    orden.push_back(origen); //O(1)
    visitados.insert(origen); //O(log(n))
    list<int> fila;
    fila.push_back(origen); // agrego a la fila para controlar el orden //O(1)
    list<typename Grafo<C>::Arco> adyacentes;
    while(!fila.empty()) {
        grafo.devolver_adyacentes(*fila.begin(), adyacentes); //tengo que recuperar el primer elemento que entro y sacarlo para respetar la estructura de fila
        typename list<typename Grafo<C>::Arco>::iterator it_adyacentes = adyacentes.begin();
        while(it_adyacentes != adyacentes.end()) { //O(e)
            if(visitados.find(it_adyacentes->devolver_adyacente()) == visitados.end()) { // si no explore ese vertice lo exploro //O(log(n))
                orden.push_back(it_adyacentes->devolver_adyacente());
                visitados.insert(it_adyacentes->devolver_adyacente());
                fila.push_back(it_adyacentes->devolver_adyacente()); //agrego al final para respetar la prioridad en la fila
            }
            it_adyacentes++;
        }
        fila.pop_front(); // elimino el primer elemento
    }
}

//  NO FUNCIONA SI HAY CICLOS, INTENTO SOLUCION NUEVA CON BACKTRACKING
template <typename C> void dfs_caminos(const Grafo<C> & g, int origen, int destino, int limite, list<int> & camino, list<list<int>> & caminos, set<int> & visitados)
{
    camino.push_back(origen);
    visitados.insert(origen);
    if(origen == destino) {
        caminos.push_back(camino);
    } else
    {
        list<typename Grafo<C>::Arco> adyacentes;
        g.devolver_adyacentes(origen, adyacentes);
        typename list<typename Grafo<C>::Arco>::iterator it_adyacentes = adyacentes.begin();
        while(it_adyacentes != adyacentes.end()) {
            if(visitados.find(it_adyacentes->devolver_adyacente()) == visitados.end()) {
                dfs_caminos(g, it_adyacentes->devolver_adyacente(), destino, limite, camino, caminos, visitados);
            }
            it_adyacentes++;
        }
    }
    visitados.erase(origen);
    camino.pop_back();
}

template <typename C> backtracking_caminos(const Grafo<C> & g, int origen, int destino, int limite, int long_actual, list<int> camino, list<list<int>> & caminos)
{
    if(long_actual <= limite) {
        camino.push_back(origen);
        if(origen == destino) {
            caminos.push_back(camino);
        } else {
            list<typename Grafo<C>::Arco> adyacentes;
            g.devolver_adyacentes(origen, adyacentes);
            typename list<typename Grafo<C>::Arco>::iterator it_adyacentes = adyacentes.begin();
            while(it_adyacentes != adyacentes.end()) {
                backtracking_caminos(g, it_adyacentes->devolver_adyacente(), destino, limite, long_actual +1, camino, caminos);
                it_adyacentes++;
            }
        }
    }
}

template <typename C> void caminos(const Grafo<C> & grafo, int origen, int destino, int limite, list<list<int> > & caminos)
{
    list<int> camino;
    set<int> visitados;
    //dfs_caminos(grafo, origen, destino, limite, camino, caminos, visitados);
    backtracking_caminos(grafo, origen, destino, limite, 0, camino, caminos);
}


template void dfs_forest<int>(const Grafo<int> & grafo, list<int> & orden);
template void bfs_forest<int>(const Grafo<int> & grafo, list<int> & orden);
template void caminos<int>(const Grafo<int> & grafo, int origen, int destino, int limite, list<list<int>> & caminos);
