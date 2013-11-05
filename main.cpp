//
//  main.cpp
//  BSTinaMatrix
//
//  Created by Gustavo Ferrufino on 11/3/13.
//  Copyright (c) 2013 Gustavo Ferrufino. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
#include <iomanip>

int matrix[100][100];
int dimensions;
int rows, columns;
int preOrderConverso[100];
int Inorder[100];

template <class T>
class NodoArbol
{ public:
    T info;
    NodoArbol<T> *izq, *der;
    NodoArbol() { izq = der = NULL; }
    NodoArbol(T dato) { info = dato; izq = der = NULL; }
    
};

template <class T>
class ABB
{
private:
    NodoArbol<T> *raiz;
    
public:
    
    ABB() { raiz = NULL; }
    void inserta (T dato);
    void despliega() { inorden(raiz); }
    int cuenta () { return contar(raiz); }
    int altura () { return niveles(raiz); }
    bool existe( int dato){ return checar( raiz, dato);}
    void vaciar();
    

    int getRaiz(){return raiz->info;}

    double comparar (int comparaciones){ return promedioComparaciones(raiz ,comparaciones);}
    int borrar(){libera(raiz);}
    ~ABB() { libera(raiz); }
    
};



template <class T>
void libera (NodoArbol<T>* raiz)
{
    if (raiz != NULL)
    {
        libera(raiz->der);
        
        libera(raiz->izq);
        
        delete(raiz);
    }
}
template <class T>
double promedioComparaciones (NodoArbol<T>* raiz, int comparaciones)
{
    if (raiz != NULL) {
        return (
                comparaciones
                + promedioComparaciones(raiz->izq, comparaciones+1)
                + promedioComparaciones(raiz->der, comparaciones+1)
                );
    }else{
        return 0;
    }
}

template <class T>
void inorden (NodoArbol<T>* raiz)
{
    if (raiz != NULL)
    {
        cout << raiz->info <<" ";
        inorden(raiz->der);
        inorden(raiz->izq);
      
        
    }
}

template <class T>
int contar (NodoArbol<T>* raiz)
{
   
        
    if (raiz == NULL)
        return 0;
    
    return(1+contar(raiz->izq)+contar(raiz->der));
    
}

template <class T>
int niveles (NodoArbol<T>* raiz)
{
    int altizq, altder;
    if (raiz == NULL)
        return 0;
    altizq = niveles(raiz->izq);
    altder = niveles(raiz->der);
    return(1+ (altizq>altder? altizq : altder));
}

template <class T>
void ABB<T>::inserta (T valor)
{
    NodoArbol<T> *NuevoNodo = new NodoArbol<T>(valor);
    NodoArbol<T> *actual = raiz, *anterior = NULL;
    while (actual != NULL)
    {
        anterior=actual;
        actual=(actual->info>valor? actual->izq: actual->der);
    }
    if (anterior==NULL)
        raiz = NuevoNodo;
    
    
    
    else{
        if (anterior->info > valor)
            anterior->izq = NuevoNodo;
        else
            anterior->der = NuevoNodo;
    }
}
template <class T>
void ABB<T>::vaciar(){//vacia y despliega datos
    
    
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions ; j++)
        {
            //cout<<matriz[i][j];//DEBUG
            matrix[i][j]=0;
            
        }
        //cout<<endl;//DEBUG
    }
    
    
}
template <class T>
bool checar ( NodoArbol<T> *raiz, int dato){
    
        if(raiz == NULL)return false;
    
        else if(dato == raiz->info) return true;
    
   return dato < raiz->info? checar(raiz->izq, dato) : checar(raiz->der, dato);
    
}



int main()
{
    
    ABB<int> arbol;
    int numcase=1;
    cin>>dimensions;
    rows= columns = dimensions-1;
	while(dimensions != -1){
        
		for(int r=0; r < dimensions; r++){
			for (int c = 0; c < dimensions; c++)
			{
				cin>>matrix[r][c];
			}
            
		}
        
        for (int i=dimensions-1; 0<=i; i--) {
            for (int j=0; j<dimensions; j++) {
                if (!(arbol.existe(matrix[j][i])) && (matrix[j][i]!= 0)) {
                     arbol.inserta(matrix[j][i]);
                }
               
              
            }
        }
        //arbol.despliega();
        cout<<"Case "<<numcase<<":"<<endl;
        cout<<"The height of the BST is: "<<arbol.altura()<<endl;
        int numNodos = arbol.cuenta();
        double numComp = arbol.comparar(1);
        double ans= numComp/numNodos;
       
        cout<<"The average of the search in the BST is: "<<setprecision(3)<<ans <<endl;
        
        arbol.vaciar();
        //arbol.borrar();
		cin>>dimensions;
		numcase++;
	}
    
}