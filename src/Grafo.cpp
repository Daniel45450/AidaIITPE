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
    //O(1) accede directamente, operacion elemental
    return this->vertice;
}

template <typename C> const C& Grafo<C>::Arco::devolver_costo() const
{
    //O(1) accede directamente, operacion elemental
    return this->costo;
}

template <typename C> void Grafo<C>::Arco::modificar_costo(const C& costo) {
    //O(1) accede directamente, operacion elemental
    this->costo = costo;
}

template <typename T> bool Grafo<T>::Arco::operator ==(const Arco & otroArco)
{
    //O(1) comparacion entre operaciones de orden cte
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
    //O(1): https://cplusplus.com/reference/map/map/empty/
    return this->vertices.empty();
}

template<typename T> int Grafo<T>::devolver_longitud() const
{
    // O(1): https://cplusplus.com/reference/map/map/size/
    return this->vertices.size();
}

template<typename T> bool Grafo<T>::existe_vertice(int vertice) const
{
    // n = cantidad de vertices
    //O(log(n))
    typename map<int, list<Arco>>::const_iterator it = this->vertices.find(vertice); //log(n) https://cplusplus.com/reference/map/map/find/
    if(it != this->vertices.end()) return true; //O(1)
    return false;
}

template<typename T> bool Grafo<T>::existe_arco(int origen, int destino) const
{
    //Complejidad: 1) Busca el vertice origen, list no tiene metodo find, entonces busco linealmente el arco con un costo O(e), por lo tanto resulta en
    //O(max(e, log(n)); e = cantidad arcos, n = cantidad de vertices
    typename map<int, list<Arco>>::const_iterator it_vertices = this->vertices.find(origen); //log(n)

    if(it_vertices != this->vertices.end()) {
        typename list<Arco>::const_iterator it_arcos = it_vertices->second.begin(); //log(e) e= cantidad de arcos
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
    //Complejidad: 1) Busca el vertice origen, list no tiene metodo find, entonces busco linealmente el arco con un costo O(e), por lo tanto resulta en
    //O(max(e, log(n)); e = cantidad arcos, n = cantidad de vertices
    typename map<int, list<Arco>>::const_iterator it_vertices = this->vertices.find(origen); // log(n)

    if(it_vertices != this->vertices.end()) {
        typename list<Arco>::const_iterator it_arcos = it_vertices->second.begin();
        while(it_arcos != it_vertices->second.end() && it_arcos->devolver_adyacente() != destino) { //O(e)
            it_arcos++;
        }
        if(it_arcos != it_vertices->second.end()) {
            return it_arcos->devolver_costo(); //o(1)
        }
    }
    return -1; //-1 no encontro el arco
}

template<typename T> void Grafo<T>::devolver_vertices(list<int>& vertices) const
    /*
        O(n): hace un recorrido por todas las keys del map
        n = vertices
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
    O(max(log(n), e): por definicion en la liberia, el operador = tiene complejidad lineal, el peor caso es tener un grafo fuertemente conexo
    entonces e representa el conjunto de todos los arcos.
*/
{
    typename map<int, list<Arco>>::const_iterator it_vertices = this->vertices.find(origen);//log(n)

    adyacentes = it_vertices->second; // O(e)
}

template<typename T>void Grafo<T>::agregar_vertice(int vertice)
//O(log(n))
{
    list<Arco> arcos;
    this->vertices.insert(std::pair<int, list<Arco>>(vertice, arcos)); //log(n) https://cplusplus.com/reference/map/map/insert/
}

template<typename T> void Grafo<T>::eliminar_vertice(int vertice)
//Recorro todo los vertices y por c/u los arcos asociados por lo tanto O(ne);
{

    typename map<int, list<Arco>>::iterator it_eliminar = this->vertices.find(vertice); //log(n)

    if(it_eliminar != this->vertices.end()) { //Si el vertice existe borro los arcos asociados a el desde los otros vertices
        typename map<int, list<Arco>>::iterator it_vertices = this->vertices.begin();
        while(it_vertices != this->vertices.end()) {    //debo eliminar los arcos asociados al vertice
            if(it_vertices != it_eliminar) {
                    if(existe_arco(it_vertices->first, it_eliminar->first)) {// O(max(e, log(n))
                       eliminar_arco(it_vertices->first, it_eliminar->first); //O(e)
                    }
            }
            it_vertices++;
        }
    }

    this->vertices.erase(it_eliminar);
}

template<typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C& costo)
{
    //Find: O(log(n)) + recorrer todo los adyacentes: O(e), complejidad final: O(max(log(n), e))
    typename map<int, list<Arco>>::iterator it_vertices = this->vertices.find(origen); //O(log(n))

    if(it_vertices != this->vertices.end()) {
        typename list<Arco>::iterator it_Arco = it_vertices->second.begin();
        while(it_Arco != it_vertices->second.end() && it_Arco->devolver_adyacente() != destino) { //O(e)
            it_Arco++;
        }
        if(it_Arco != it_vertices->second.end()) {
            it_Arco->modificar_costo(costo);
        }
    }
}

template<typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C& costo)
{
    //find en map -> O(log(n)) n= vertices
    //Complejidad: O(max(log(n)),e))
    if(!existe_arco(origen, destino)) { //O(max(log(n), e))
        typename map<int, list<Arco>>::iterator it_vertices = this->vertices.find(origen); //O(log(n))
        Arco a(destino, costo);
        it_vertices->second.push_back(a); //O(1)
    }
}

template<typename T> void Grafo<T>::eliminar_arco(int origen, int destino)
 //Busco el vertice en un tiempo 0(log(n)) luego hago un remove en una lista, que tiene complejidad O(e), ya que recorre todo los arcos, si es el peor caso tiene e arcos
    // resulta en O(e)
{
    typename map<int,list<Arco>>::iterator it_vertices = this->vertices.find(origen); //log(n)
    Arco a(destino, 0);
    it_vertices->second.remove(a); //O(e) https://cplusplus.com/reference/list/list/remove/
}

template<typename T> void Grafo<T>::vaciar()
{
    //se recorren todas las key O(n) y por cada key se elimina su valor: eliminar lista O(e)
    //Complejidad: O(ne)
    this->vertices.clear();
}

template class Grafo<int>;
