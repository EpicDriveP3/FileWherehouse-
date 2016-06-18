/* 
 * File:   ArbolBS.cpp
 * Author: ellioth
 * 
 * Created on June 10, 2016, 11:11 AM
 */

#include "ArbolBS.h"

/**
 * constructor de la clase, este recibe en una 
 * cantidad entera la cantidad de llaves que se quiere tener.
 * @param pKeys dato tipo entero que es la cantidad 
 */
template<class Dp>
ArbolBS<Dp>::ArbolBS(int pKeys) {
    if(pKeys<DOS || (pKeys%DOS!=0)){
        _keys=pKeys;
        _root=NULL;
    }
    else
        error("Datos incorrecto para arbol\0");
}

/**
 * destructor de la clase
 */
template<class Dp>
ArbolBS<Dp>::~ArbolBS() {    
}

/**
 * metodo para realizar inserciones en el arbol, recibe 
 * el dato que se va a querer ingresar.
 * @param pData es el dato que se recibe, este tiene que 
 * coincidir con el tipo de dato que se tiene.
 */
template<class Dp>
void ArbolBS<Dp>::insertData(Dp pData) {
    ///la raiz no existe
    if(_root==NULL){
        _root= (NodoBTree<Dp>*)malloc(sizeof(NodoBTree<Dp>));
        _root->_Keys=_keys;
        _root->_datas=(Dp*)malloc(sizeof(Dp)*_keys);
        _root->_Sons=NULL;
        _root->_father=NULL;
        _root->_datas[CERO]=pData;
        _root->_NOfDatas++;
        return;
    }
    ///el nodo aun no va a reventar
    else if(_root->_NOfDatas<_keys){
        if (_root->_Sons==NULL){
            desplacementNode(_root,pData);
            return;
        }
        int i=0;
        for(; i<_root->_NOfDatas; i++){
            if(memcmp(&pData, &_root->_datas[i],sizeof(Dp))<CERO)
                break;
        }
        insertHelper(_root->_Sons[i],_root, pData);
        return;
        
    }
    ///el nodo ocupa reventar
    cout<<"va a reventar el nodo"<<endl;
    _root=breakNode(_root);
    cout<<"nodo reventado"<<endl;
    int i=0;
    for(; i<_root->_NOfDatas; i++){
        if(memcmp(&pData, &_root->_datas[i],sizeof(Dp))<CERO)
            break;
    }
    insertHelper(_root->_Sons[i],_root, pData);
    return;
    
}

/**
 * metodo para hacer el metodo que le ayuda a hacer las insericones
 * cuando se empieza a ocupar recursividad para acceder a los otros datos. 
 * @param pNodo recibe el puntero del nodo del nodo al cual se le va a 
 * ingresar el dato.
 * @param pPadre recibe el puntero del padre de este nodo.
 * @param pDato dato que se quiere ingresar.
 */
template<class Dp>
void ArbolBS<Dp>::insertHelper(NodoBTree<Dp>* pNodo, NodoBTree<Dp>* pPadre,
        Dp pDato){
    int i=0; bool flag=false;
    ///caso para que saber si se ocupa que el nodo reviente o no
    if(pNodo->_NOfDatas<_keys){
        ///caso por si se ocupa que se haga un desplazamiento de los
        ///datos e ingresar el dato.
        if (pNodo->_Sons==NULL){
            bool ifExists=false;
            for(int i=0; i<pNodo->_NOfDatas; i++){
                if(memcmp(&pDato, &pNodo->_datas[i],sizeof(Dp))==CERO){
                    ifExists=true;
                    break;
                }
            }
            if(ifExists)
                return;
            desplacementNode(pNodo,pDato);
            return;
        }
        ///caso en el que se tiene si el nodo esta con hijos
        for(; i<pNodo->_NOfDatas; i++){
            if(memcmp(&pDato, &pNodo->_datas[i],sizeof(Dp))<CERO)
                break;
        }
        insertHelper(pNodo->_Sons[i],pNodo->_father, pDato);
        return;
    }
    //rompemos el nodo
    cout<<"entra a romper el nodo"<<endl;
    pNodo=breakNode(pNodo);
    cout<<"termina"<<endl;
    //buscamos en que posicion vamos a recursionar para ingresar el dato
    for(; i<pNodo->_NOfDatas; i++){
        if(memcmp(&pDato, &pNodo->_datas[i],sizeof(Dp))<CERO){
            break;
        }
    }
    insertHelper(pNodo->_Sons[i], pNodo, pDato);
    return;
}

/**
 * cuando este metodo es invocado provoca un rompimiento del nodo, 
 * este metodo permite que cuando el nodo ya este lleno este reviente 
 * y pase los datos a los hijos.
 * @param pNodo nodo al cual queremos hacer reventar.
 */
template<class Dp>
NodoBTree<Dp>* ArbolBS<Dp>::breakNode(NodoBTree<Dp>* pNodo) {
    int middle=_keys/DOS;
    ///se revisa que el nodo no tenga padre para romperlo
    if(pNodo->_father==NULL){
        cout<<"prueba1"<<endl;
        //fase para cuando no se tienen hijos, como se va a comportar
        //para realizar el quiebre del hijo
        if(pNodo->_Sons==NULL){
            /**
             * se crean los hijos y a estos se les asignan el padre.
             * se establecen a que seran los nuevos hijos, se llenan
             * desde el inicio hasta antes de la mitad y el otro hijo 
             * desde la mitad + uno para saltarse la mitad.
             * se borra el contenido del nodo actual y se llena con el 
             * dato medio.
             */
            pNodo->_Sons=(NodoBTree<Dp>**)malloc(sizeof(NodoBTree<Dp>*)*(_keys+UNO));
            for(int i=0; i<_keys+UNO; i++){
                pNodo->_Sons[i]=(NodoBTree<Dp>*)malloc(sizeof(NodoBTree<Dp>));
                pNodo->_Sons[i]->_Keys=_keys;
                pNodo->_Sons[i]->_NOfDatas=0;
                pNodo->_Sons[i]->_Sons=NULL;
                pNodo->_Sons[i]->_datas=(Dp*)malloc(_keys*sizeof(Dp));
                pNodo->_Sons[i]->_father=pNodo;
            }
            NodoBTree<Dp>* pHijoIzq=pNodo->_Sons[CERO];
            NodoBTree<Dp>* pHijoDer=pNodo->_Sons[UNO];
            for(int i=0; i<middle; i++)
                desplacementNode(pHijoIzq,pNodo->_datas[i]);
            for(int i=middle+UNO; i<_keys; i++)
                desplacementNode(pHijoDer,pNodo->_datas[i]);
            Dp Dato= pNodo->_datas[middle];
            //free(pNodo->_datas);
            pNodo->_datas=(Dp*)malloc(sizeof(Dp)*_keys);
            pNodo->_NOfDatas=0;
            desplacementNode(pNodo,Dato);
            pNodo->_datas[CERO]=Dato;
            pNodo->_NOfDatas=UNO;
            return pNodo;
        }
        /**
         * caso para cuando se quiere reventar pero si se tienen 
         * hijos. se crean los hijos izquierdo y derecho. se crean los 
         * espacios de los hijos. se empiezan a llenar los hijos con los 
         * datos del arreglo menos la mitad, que se excluye. se redireccionan
         * los hijos del nodo hacia los hijos izq y derecho. se guardara
         * el dato que es el medio. se liberan los datos de los hijos 
         * y la informacion interna del nodo. se crea los nuevos espacios
         * para los hijos y los datos, y se emiezan a incializar los 
         * espacios de los hijos y a establecerles los padres. se establece 
         * el hijo izq y el hijo derecho del nuevo nodo, se ingresa el dato 
         * al nodo y se reinicia el contador de datos internos.
         */
        NodoBTree<Dp>* pHijoIzq=(NodoBTree<Dp>*)malloc(sizeof(NodoBTree<Dp>));
        pHijoIzq->_Keys=_keys;
        pHijoIzq->_datas=(Dp*)malloc(sizeof(Dp)*_keys);
        pHijoIzq->_Sons=(NodoBTree<Dp>**)malloc(sizeof(NodoBTree<Dp>*)*(_keys+UNO));
        pHijoIzq->_father=pNodo;
        NodoBTree<Dp>* pHijoDer=(NodoBTree<Dp>*)malloc(sizeof(NodoBTree<Dp>));
        pHijoDer->_Keys=_keys;
        pHijoDer->_datas=(Dp*)malloc(sizeof(Dp)*_keys);
        pHijoDer->_Sons=(NodoBTree<Dp>**)malloc(sizeof(NodoBTree<Dp>*)*(_keys+UNO));
        pHijoDer->_father=pNodo;
        for(int i=0; i<middle; i++)
            desplacementNode(pHijoIzq,pNodo->_datas[i]);
        for(int i=middle+UNO; i<pNodo->_NOfDatas; i++)
            desplacementNode(pHijoDer,pNodo->_datas[i]);
        for(int i=0; i<=middle; i++){
            pHijoIzq->_Sons[i]=pNodo->_Sons[i];
            pHijoIzq->_Sons[i]->_father=pHijoIzq;
        }
        for(int i =middle+UNO,j=0; i <=_keys; i++,j++){
            pHijoDer->_Sons[j]=pNodo->_Sons[i];
            pHijoDer->_Sons[j]->_father=pHijoDer;
        }
        Dp Dato= pNodo->_datas[middle];
        pNodo->_datas=(Dp*)malloc(sizeof(Dp)*_keys);
        pNodo->_Sons=(NodoBTree<Dp>**)malloc(sizeof(NodoBTree<Dp>*)*(_keys+UNO));
        for(int i=DOS; i<_keys+UNO; i++){
            pNodo->_Sons[i]=(NodoBTree<Dp>*)malloc(sizeof(NodoBTree<Dp>));
            pNodo->_Sons[i]->_NOfDatas=0;
            pNodo->_Sons[i]->_father=pNodo;
        }
        //free(pNodo->_datas);
        //free(pNodo->_Sons);
        pNodo->_Sons[CERO]=pHijoIzq;
        pNodo->_Sons[UNO]=pHijoDer;
        pNodo->_datas[CERO]=Dato;
        pNodo->_NOfDatas=UNO;
        return pNodo;
    }
    cout<<"prueba2"<<endl;
    ///fase para cuando se tiene un padre
    if(pNodo->_Sons==NULL){
        cout<<"prueba3"<<endl;
        /**
         * esta fase es para cuando se ocupa reventar un nodo con padre pero
         * sin hijos. se crea el apuntador al padre y los hijos nuevos que se
         * van a usar, se le dirigen al nuevo padre los nuevos hijos. 
         * se ingresa el dato medio al padre y los datos restantes a los hijos
         * nuevos, se saca la posicion del dato medio en el padre y alrededor
         * del dato medio se ingresan los nuevos hijos.
         */
        NodoBTree<Dp>* padre=pNodo->_father;
        NodoBTree<Dp>* HijoIzq= (NodoBTree<Dp>*)malloc(sizeof(NodoBTree<Dp>));
        HijoIzq->_datas=(Dp*)malloc(sizeof(Dp)*_keys);
        HijoIzq->_Keys=_keys;
        HijoIzq->_Sons=NULL;
        HijoIzq->_father=padre;
        NodoBTree<Dp>* HijoDer= (NodoBTree<Dp>*)malloc(sizeof(NodoBTree<Dp>));
        HijoDer->_datas=(Dp*)malloc(sizeof(Dp)*_keys);
        HijoDer->_Keys=_keys;
        HijoDer->_Sons=NULL;
        HijoDer->_father=padre;
        desplacementNode(padre,pNodo->_datas[middle]);
        for(int i=0; i<middle; i++)
            desplacementNode(HijoIzq,pNodo->_datas[i]);
        for(int i =middle+UNO; i <_keys; i++){
            cout<<i<<endl;
            desplacementNode(HijoDer,pNodo->_datas[i]);
        }
        int i=0;
        for(; i<padre->_NOfDatas; i++){
            if(memcmp(&pNodo->_datas[middle], &padre->_datas[i],sizeof(Dp))==CERO){
                break;
            }
        }
        padre->_Sons[i]=HijoIzq;
        padre->_Sons[i+UNO]=HijoDer;
        pNodo->_father=NULL;
        pNodo->_Sons=NULL;
        //free(pNodo);
        return padre;
    }
    cout<<"4"<<endl;
    /**
     * seccion usada para cuando aparte de tener un padre se tienen hijos.
     * se crea el puntero del padre y los nuevos hijos, se inicializa todo en 
     * los hijos, se le refencia el nuevo padre. se le ingresa al padre el 
     * dato medio. se le ingresa la mitad exclusiva al hijo izq y se le 
     * establecen la mitad de los hijos, para el hijo derecho se le ingresa 
     * el los datos de la mitad + uno y se le insertar la otra mitad de los 
     * hijos del nodo, se encuentra la posicion del dato medio en el padre y 
     * se le establecen los hijos nuevos alrededor del dato medio y se libera 
     * al nodo.
     */
    NodoBTree<Dp>* padre=pNodo->_father;
    NodoBTree<Dp>* HijoIzq= (NodoBTree<Dp>*)malloc(sizeof(NodoBTree<Dp>));
    HijoIzq->_datas=(Dp*)malloc(sizeof(Dp)*_keys);
    HijoIzq->_Keys=_keys;
    HijoIzq->_Sons=(NodoBTree<Dp>**)malloc(sizeof(NodoBTree<Dp>*)*(_keys+UNO));
    HijoIzq->_father=padre;
    NodoBTree<Dp>* HijoDer= (NodoBTree<Dp>*)malloc(sizeof(NodoBTree<Dp>));
    HijoDer->_datas=(Dp*)malloc(sizeof(Dp)*_keys);
    HijoDer->_Keys=_keys;
    HijoDer->_Sons=(NodoBTree<Dp>**)malloc(sizeof(NodoBTree<Dp>*)*(_keys+UNO));
    HijoDer->_father=padre;
    desplacementNode(padre,pNodo->_datas[middle]);
    for(int i=0; i<middle; i++)
        desplacementNode(HijoIzq,pNodo->_datas[i]);
    for(int i=0; i<=middle; i++){
        HijoIzq->_Sons[i]=pNodo->_Sons[i];
        HijoIzq->_Sons[i]->_father=HijoIzq;
    }
    for(int i =middle+UNO; i <_keys; i++) 
        desplacementNode(HijoDer,pNodo->_datas[i]);
    for(int i =middle+UNO,j=0; i <=_keys; i++,j++){
        HijoDer->_Sons[j]=pNodo->_Sons[i];
        HijoDer->_Sons[j]->_father=HijoDer;
    }
    int i=0;
    for(; i<padre->_NOfDatas; i++){
        if(memcmp(&pNodo->_datas[middle], &padre->_datas[i],sizeof(Dp))==CERO){
            break;
        }
    }
    padre->_Sons[i]=HijoIzq;
    padre->_Sons[i+UNO]=HijoDer;
    pNodo->_father=NULL;
    pNodo->_Sons=NULL;
    //free(pNodo);
    return padre;
}

/**
 * metodo para relaizar un desplazamiento de los datos en el nodos
 * para realizar una insercion, realizar una insercion entera cuando es 
 * invocada.
 * @param pNodo nodo al cual se le realizara el desplazamiento.
 * @param pDato dato al cual afectara al nodo para entrar al nodo.
 */
template<class Dp>
void ArbolBS<Dp>::desplacementNode(NodoBTree<Dp>* pNodo, Dp pDato) {
    int i=0;
    for(; i<pNodo->_NOfDatas; i++){
        if(memcmp(&pDato, &pNodo->_datas[i],sizeof(Dp))<CERO)
            break;
    }
    for(int j=pNodo->_NOfDatas;i<j;j--){
        pNodo->_datas[j]=pNodo->_datas[j-UNO];
        if(pNodo->_Sons!=NULL)
                pNodo->_Sons[j+UNO]=pNodo->_Sons[j];
    }
    pNodo->_datas[i]=pDato;
    pNodo->_NOfDatas++;
}

/**
 * cuando este metodo se invoca provoca un borrado en el arbol del 
 * dato que se le haya especificado.
 * @param pData dato que se va a borrar del arbol.
 */
template<class Dp>
void ArbolBS<Dp>::borrarData(Dp pData) {
    
}

/**
 * 
 */
template<typename Dp>
void ArbolBS<Dp>::deleteHelper(NodoBTree<Dp>* pNodo, NodoBTree<Dp>* pPadre,
        Dp pDato) {

}

/**
 * cuando se invoca en el campo este metodo provoca que tu arbol 
 * busque si existe algun dato ingual al que le ingresastes.
 * @param pData recibe un dato del tipo especificado para el arbol.
 * @return retorna un dato tipo verdadero o falso si existe o no el 
 * dato.
 */
template<class Dp>
bool ArbolBS<Dp>::findData(Dp pData) {
    ///verifica que no tenga hijos la raiz
    if(_root->_Sons==NULL){
        ///busca dentro del nodo si existe el dato
        int i=0;bool flag;
        for(; i<_root->_NOfDatas; i++)
            if(memcmp(&pData, &_root->_datas[i],sizeof(Dp))==CERO){
                cout<<"find it"<<endl;
                flag=true;
                break;
            }
        return flag;
        
    }
    ///si tiene hijos recursiona
    return findHelper(_root,pData);
}

/**
 * metodo recursivo para ir buscando en los hijos.
 * @param pNodo parametro que recibe del nodo que queremos analizar.
 * @param pDato parametro del dato que queremos buscar en el arbol.
 */
template<class Dp>
bool ArbolBS<Dp>::findHelper(NodoBTree<Dp>* pNodo, Dp pDato) {
    ///verifica si existe el hijo dentro del nodo
    int i=0;bool flag;
    for(; i<pNodo->_NOfDatas; i++)
        if(memcmp(&pDato, &pNodo->_datas[i],sizeof(Dp))==CERO){
            flag=true;
            break;
        }
    ///retorna una verdadero si existe el dato
    if(flag)
        return flag;
    ///si ya no tiene hijos se dice que el dato ya existe ya que no quedan datos
    ///por revisar.
    if(pNodo->_Sons==NULL)
        return false;
    ///verifica en que hijo recursionar y realiza esta misma.
    i=0;
    for(; i<pNodo->_NOfDatas; i++){
        if(memcmp(&pDato, &pNodo->_datas[i],sizeof(Dp))<CERO)
            break;
    }
    return findHelper(pNodo->_Sons[i],pDato );
}

/**
 * metodo para imprimir todos los objetos del arbol
 */
template<typename Dp>
void ArbolBS<Dp>::printTree() {
    if(_root==NULL)
        return;
    printTreeHelper(_root,CERO);
}

/**
 * metodo de ayuda par ir recursionando hasta imprimir todos los objetos
 * del arbol
 */
template<typename Dp>
void ArbolBS<Dp>::printTreeHelper(NodoBTree<Dp>* pNodo, int pNodoNumber) {
    if(pNodo==NULL)
        return;
    if(pNodo->_Sons!=NULL){
        for(int i=0; i<pNodo->_NOfDatas+UNO;i++)
            printTreeHelper(pNodo->_Sons[i],pNodoNumber+(i+UNO));
    }
    cout<<"----------nodo---------"<<pNodoNumber<<endl;
    for(int i=0; i<pNodo->_NOfDatas; i++)
        cout<<pNodo->_datas[i]<<" - ";
    cout<<"\n";
}

///instanceacion explicita
template class ArbolBS<int>;
template class ArbolBS<float>;
template class ArbolBS<double>;
template class ArbolBS<string>;
template class ArbolBS<char*>;
