#include <iostream>
#include <fstream>

using namespace std;

int mayor_pos(int vec[], int dim)
{
	int may = vec[0];
	int imay = 0;

	for (int i = 1; i < dim; i++)
		if (vec[i] > may) {
			may = vec[i];
			imay = i;
		}
	return imay;
}

void bubble_sort(float v[],int vp[], int dim)
{
	float temp, temp2;
    int i, j;
	for (i = 0; i < dim - 1 ; ++i) {
		for (j = 0 ; j < dim - 1 ; j++) {
			if (v[j] > v[j+1]) {
				temp = v[j+1];
				v[j+1] = v[j];
				v[j] = temp;
                temp2 = vp[j+1];
				vp[j+1] = vp[j];
				vp[j] = temp2;
			}
		}
	}
}

int main()
{
	const int cantcli {8}; //sólo por prolijidad
    const int cantprod {5};
    float kgtotales [cantcli] [cantprod] {0}; //para punto 1
    string cli[cantcli]; 
    string prod[cantprod]; 
    int auxcli[8] {0}; //auxiliar para contar y no alterar vector de nombres

    float kmtotales [cantcli] [cantprod] {0}; //para punto 2
    float vec_orden [cantprod] {0}; // aux para punto 3
    int entregas [cantprod] {0}; // para punto 3

    //cargo 2 de nombres por separado (mayor comodidad) 
    ifstream nombres;
    nombres.open ("Nombres.txt");
    if (!nombres) {
		cout << "Error al tratar de abrir el archivo para lectura" << endl;
		return 1;
	}
 
    for (int i = 0; i < cantcli && nombres >> cli[i]; ++i);
    for (int i = 0; i < cantprod && nombres >> prod[i]; ++i);

    nombres.close();
    
    //punto 1:
	ifstream datos; 
	datos.open("Datos.txt");
	if (!datos) {
		cout << "Error al tratar de abrir el archivo para lectura" << endl;
		return 1;
	}
    
    int jcli, jprod;
    float jkg, jkm;
    while (datos >> jcli >> jprod >> jkg >> jkm){ 
        kgtotales [jcli] [jprod] += jkg; // punto 1 
        kmtotales [jcli] [jprod] += jkm; // punto 2  
        entregas [jprod]++; //punto 3 
    }

    datos.close();

    int k {0};
    for (int i = 0; i < cantcli; ++i) {
        cout << cli[i] << ":";
        for (int j = 0; j < cantprod; ++j) {
            if (kgtotales [i][j] > 13000) {  
                cout << "   " << prod[j]; //si cumple lo muestro y
                auxcli[i]= ++k; //cuento por cliente (para punto 2)
            }      
        }
        cout << "." << endl;
        k = 0;
    }
    cout << endl;

    //punto 2; hallo la posicion del mayor
    int imay = mayor_pos(auxcli, 8);
    //imay me retorna "1", el codigo de "Bi" en este caso, que es el elegido
    //cargo en un vector porque no creo poder ordenar una columna de matriz
    for (int j = 0; j < cantprod; ++j){
        vec_orden[j] = kmtotales[imay][j];
    }
    
    //debo ordenarlo ascendente, disculpe vulgaridades no tuve otro remedio 
    int vec_pos[5] {0, 1, 2, 3, 4}; // auxiliar que me vi obligado a hacer 
    bubble_sort (vec_orden, vec_pos, 5);
    /* uso el vec_pos que sigue a la par los movimientos del vec_orden, 
        para no perder los indices del vector de strings */
    for (int i = 0; i < cantprod; ++i){
        cout << prod [vec_pos[i]] << ": " << vec_orden[i] << endl ; 
    } 
    cout << endl;
    
    //punto 3, muestro el último porque ya estaba ordenado 
    cout << "El tipo de mayor kilometraje en " << entregas[vec_pos[4]] 
        << " entregas, fue " << prod[vec_pos[4]] << endl ;  
    
	return 0;
}
