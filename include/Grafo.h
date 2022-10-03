#ifndef GRAFO_H
#define GRAFO_H

#include <list>
#include <map>

using namespace std;

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolver_adyacente() const; // O(1)
		const C & devolver_costo() const; //0(1)
		void modificar_costo(const C & costo); //O(1)
		bool operator == (const Arco & otroArco); //O(1)
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(bool dirigido);
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool esta_vacio() const; //O(1)

	// Indica la cantidad de vértices del grafo
	int devolver_longitud() const; //O(1)

	bool existe_vertice(int vertice) const; //O(log(n))

	bool existe_arco(int origen, int destino) const; //O(max(e, log(n))

	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(int origen, int destino) const; //O(max(e, log(n))

	void devolver_vertices(list<int> & vertices) const; //O(n)

	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const; //O(max(log(n), e)

	void agregar_vertice(int vertice);//O(log(n))

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice); //O(ne)

	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(int origen, int destino, const C & costo); //O(max(log(n), e)

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregar_arco(int origen, int destino, const C & costo); //O(max(log(n), e)

	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino); //O(e)

	void vaciar(); //O(ne)

private:
    map<int, list<Arco>> vertices;
    bool dirigido = false;

}; // class Grafo

#endif // GRAFO_H
