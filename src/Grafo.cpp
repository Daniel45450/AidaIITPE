#include "Grafo.h"

//Implementacio de Arco()

template <typename T> Grafo<T>::Arco::Arco()
{
    //Arco vacio
}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C& costo)
{
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename T> int Grafo<T>::Arco::devolver_adyacente() const
{
    return this->vertice;
}

template <typename C> const C& Grafo<C>::Arco::devolver_costo() const
{
    return this->costo;
}

template <typename C> void Grafo<C>::Arco::modificar_costo(const C& costo) {
    this->costo = costo;
}

template <typename T> bool Grafo<T>::Arco::operator ==(const Arco & otroArco)
{
    if(this->devolver_adyacente() == otroArco.devolver_adyacente()) return true;
    return false;
}

//Fin Arco()

//Comienzo Grafo()

template <typename T> Grafo<T>::Grafo()
{
    //ctor
}

template <typename T> Grafo<T>::Grafo(bool dirigido)
{
    this->dirigido = dirigido; //Es dirigido?
}

template <typename T> Grafo<T>::~Grafo()
{
    //dtor
}

template <typename T> Grafo<T>::Grafo(const Grafo& otroGrafo)
{

}

template<typename T> Grafo<T>& Grafo<T>::operator=(const Grafo& otroGrafo)
{
    return *this;
}

template<typename T> bool Grafo<T>::esta_vacio() const
{
    return this->vertices.empty();
}

template<typename T> int Grafo<T>::devolver_longitud() const
{
    return this->vertices.size();
}

template<typename T> bool Grafo<T>::existe_vertice(int vertice) const
{
    typename map<int, list<Arco>>::const_iterator it = this->vertices.find(vertice);
    if(it != this->vertices.end()) return true;
    return false;
}

template<typename T> bool Grafo<T>::existe_arco(int origen, int destino) const
{
    typename map<int, list<Arco>>::const_iterator it_vertices = this->vertices.find(origen);

    if(it_vertices != this->vertices.end()) {
        typename list<Arco>::const_iterator it_arcos = it_vertices->second.begin();
        if(it_arcos != it_vertices->second.end()) {
            while(it_arcos != it_vertices->second.end() && it_arcos->devolver_adyacente() != destino) {
                it_arcos++;
            }
        }
        if(it_arcos != it_vertices->second.end()) {
            return true;
        }
    }
    return false;
}

template<typename C>const C& Grafo<C>::costo_arco(int origen, int destino) const
{
    typename map<int, list<Arco>>::const_iterator it_vertices = this->vertices.find(origen);

    if(it_vertices != this->vertices.end()) {
        typename list<Arco>::const_iterator it_arcos = it_vertices->second.begin();
        while(it_arcos != it_vertices->second.end() && it_arcos->devolver_adyacente() != destino) {
            it_arcos++;
        }
        if(it_arcos != it_vertices->second.end()) {
            return it_arcos->devolver_costo();
        }
    }
    return -1; //-1 no encontro el arco
}

template<typename T> void Grafo<T>::devolver_vertices(list<int>& vertices) const
    /*
        O(v): hace un recorrido por todas las keys del map
        v = vertices
    */
{
    typename map<int, list<Arco>>::const_iterator it_vertices = this->vertices.begin();
    while(it_vertices != this->vertices.end()) {
        vertices.push_back(it_vertices->first); //o(1)
        it_vertices++;
    }
}

template<typename T> void Grafo<T>::devolver_adyacentes(int origen, list<Arco>& adyacentes) const
/*
    O(e): por definicion en la liberia, el operador = tiene complejidad lineal, el peor caso es tener un grafo fuertemente conexo
    entonces e representa el conjunto de todos los arcos.
*/
{
    typename map<int, list<Arco>>::const_iterator it_vertices = this->vertices.find(origen);

    adyacentes = it_vertices->second; // O(e)
}

template<typename T>void Grafo<T>::agregar_vertice(int vertice)
{
    list<Arco> arcos;
    this->vertices.insert(std::pair<int, list<Arco>>(vertice, arcos));
}

template<typename T> void Grafo<T>::eliminar_vertice(int vertice)
{

    typename map<int, list<Arco>>::iterator it_eliminar = this->vertices.find(vertice);

    if(it_eliminar != this->vertices.end()) { //Si el vertice existe borro los arcos asociados a el desde los otros vertices
        typename map<int, list<Arco>>::iterator it_vertices = this->vertices.begin();
        while(it_vertices != this->vertices.end()) {    //debo eliminar los arcos asociados al vertice
            if(it_vertices != it_eliminar) {
                    if(existe_arco(it_vertices->first, it_eliminar->first)) {
                       eliminar_arco(it_vertices->first, it_eliminar->first);
                    }
            }
            it_vertices++;
        }
    }

    this->vertices.erase(it_eliminar);
}

template<typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C& costo)
{
    typename map<int, list<Arco>>::iterator it_vertices = this->vertices.find(origen);

    if(it_vertices != this->vertices.end()) {
        typename list<Arco>::iterator it_Arco = it_vertices->second.begin();
        while(it_Arco != it_vertices->second.end() && it_Arco->devolver_adyacente() != destino) {
            it_Arco++;
        }
        if(it_Arco != it_vertices->second.end()) {
            it_Arco->modificar_costo(costo);
        }
    }
}

template<typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C& costo)
{
    if(!existe_arco(origen, destino)) {
        typename map<int, list<Arco>>::iterator it_vertices = this->vertices.find(origen);
        Arco a(destino, costo);
        it_vertices->second.push_back(a);
    }
}

template<typename T> void Grafo<T>::eliminar_arco(int origen, int destino)
{
    typename map<int,list<Arco>>::iterator it_vertices = this->vertices.find(origen);
    Arco a(destino, 0);
    it_vertices->second.remove(a);
}

template<typename T> void Grafo<T>::vaciar()
{
    this->vertices.clear();
}

template class Grafo<int>;
