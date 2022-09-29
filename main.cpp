#include "Grafo.h"
#include "Servicios.h"

#include "iostream"

using namespace std;

template <typename C>
ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
	// Recorremos todos los vertices
	list<int> vertices;
	grafo.devolver_vertices(vertices);
	list<int>::iterator v = vertices.begin();
	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list<typename Grafo<C>::Arco> adyacentes;
		grafo.devolver_adyacentes(*v, adyacentes);
		typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "    " << *v << "-> " << ady->devolver_adyacente() << " (" << ady->devolver_costo() << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}

int main(int argc, char **argv)
{
	Grafo<int> g;

	// Cargamos un grafo dirigido
	// Primero los vértices
	g.agregar_vertice(1);
	g.agregar_vertice(2);
	g.agregar_vertice(3);
	g.agregar_vertice(4);
	g.agregar_vertice(5);
	//g.agregar_vertice(6);
	//g.agregar_vertice(7);

	// Luego los arcos
	g.agregar_arco(1, 5, 1);
	g.agregar_arco(1, 4, 1);
	g.agregar_arco(2, 5, 1);
	g.agregar_arco(2, 3, 2);
	g.agregar_arco(3, 4, 3);
	g.agregar_arco(5, 2, 4);
	g.agregar_arco(5, 4, 5);
	/*g.agregar_arco(1, 2, 1);
	g.agregar_arco(2, 5, 1);
	g.agregar_arco(2, 3, 1);
	g.agregar_arco(3, 6 , 1);
	g.agregar_arco(4, 5, 1);
	g.agregar_arco(5, 6, 1);
	g.agregar_arco(6, 7, 1);
	g.agregar_arco(5, 3, 1);*/

	// Mostramos el grafo
	cout << "Estructura del grafo:\n" << g << "\n";


	list<int> orden;
    //dfs_forest(g, orden);
    //bfs_forest(g, orden);
    list<list<int>> lista_caminos;
    caminos(g, 1, 4, 5, lista_caminos);
    //list<int>::iterator it_orden = orden.begin();
    /*while(it_orden != orden.end()) {
        cout << *it_orden << " ";
        it_orden++;
    }*/

    list<list<int>>::iterator it_lista = lista_caminos.begin();
    list<int>::iterator it_camino;
    while(it_lista != lista_caminos.end()) {
        cout << "camino: " << endl;
        it_camino = it_lista->begin();
        while(it_camino != it_lista->end()) {
            cout << *it_camino << " ";
            it_camino++;
        }
        cout << "\n";
        it_lista++;
    }
	return 0;
}
