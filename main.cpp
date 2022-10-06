#include "Grafo.h"
#include "Servicios.h"

#include "iostream"

using namespace std;

template <typename C> ostream & operator << (ostream & salida, const Grafo<C> & grafo);
void imprimir_caminos(const list<list<int>> & lista_caminos);
void imprimir_orden(const list<int> & orden);

int main(int argc, char **argv)
{
	Grafo<int> g;

	g.agregar_vertice(1);
	g.agregar_vertice(2);
	g.agregar_vertice(3);
	g.agregar_vertice(4);
	g.agregar_vertice(5);
	g.agregar_vertice(6);
	g.agregar_vertice(7);

	// Luego los arcos
	g.agregar_arco(1, 2, 82);
	g.agregar_arco(1, 3, 65);
	g.agregar_arco(1, 4, 17);
	g.agregar_arco(2, 6, 22);
	g.agregar_arco(3, 5, 35);
	g.agregar_arco(4, 7, 64);
	g.agregar_arco(5, 6, 55);

	int opt = 0;

	do {
        list<int> orden;
        list<list<int>> lista_caminos;
        int origen, destino, limite;
        cout << "\n" << endl;
        cout << "----- TPE AIDA II -----" << endl;
        cout << "\n" << endl;
        cout << "1. Imprimir grafo" << endl;
        cout << "2. Orden DFS_FOREST" << endl;
        cout << "3. Orden BFS_FOREST" << endl;
        cout << "4. Busqueda de caminos" << endl;
        cout << "5. Salir" << endl;
        cout << "\n" << endl;
        cout << "Ingresa una opcion: ";
        cin >> opt;
        switch(opt)
        {
            case 1:
                cout << "Estructura del grafo:\n" << g << "\n";
            break;
            case 2:
               dfs_forest(g, orden);
               imprimir_orden(orden);
            break;
            case 3:
                bfs_forest(g, orden);
                imprimir_orden(orden);
            break;
            case 4:
                cout << "Ïngresa el origen: ";
                cin >> origen;
                cout << "Ingresa el destino: ";
                cin >> destino;
                cout << "Ingresa el limite: ";
                cin >> limite;
                caminos(g, origen, destino, limite, lista_caminos);
                imprimir_caminos(lista_caminos);
            break;
        }
	} while(opt != 5);
	return 0;
}

void imprimir_orden(const list<int> & orden)
{
    list<int>::const_iterator it_orden = orden.begin();
    cout << "\n" << endl;
    while(it_orden != orden.end()) {
        cout << *it_orden << " ";
        it_orden++;
    }
}

void imprimir_caminos(const list<list<int>> & lista_caminos)
{
    list<list<int>>::const_iterator it_lista = lista_caminos.begin();
    list<int>::const_iterator it_camino;
    cout << "\n" << endl;
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
}

template <typename C> ostream & operator << (ostream & salida, const Grafo<C> & grafo)
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
