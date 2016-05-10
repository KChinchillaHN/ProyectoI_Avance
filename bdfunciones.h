#ifndef BDFUNCIONES_H
#define BDFUNCIONES_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

/* Super Block     = 20 Bytes
 * Bloque Tablas H = 12 Bytes
 * Bloque Tablas I = 27 Bytes
 * Bloque Campos H = 30 Bytes
 * Bloque Campos I = 13 Bytes
 * Bloque Regist H = 16 Bytes
 * Bloque Regist I = ?  Bytes
 */

struct superBlock{   // Struct para leer el Super Block.
    int bloqueLibre;   // Indicador del siguiente bloque libre.
    int tamBloques;    // Indicador del tamano de los bloques.
    int numBloques;    // Indicador del numero de bloques.
    int pBloqTablas;   // Primer bloque con las tablas de la BD
    int uBloqTablas;   // Ultimo bloque con las tablas de la BD
};

struct bloqHTB{    // Struct para leer la metadata de los bloques de tipo Tabla
    int numTB;       // Numero de Tablas en el Bloque
    int bloqSigTB;   // Siguiente Bloque con informacion de Tablas
    int bloqAntTB;   // Bloque Anterior con informacion de Tablas
};

struct bloqITB{         // Struct para leer los registros de tipo Tabla
    int numCampos;        // Numero de Campos dentro de la Tabla
    int pBloqCampos;      // Primer Bloque con los campos de la Tabla
    int uBloqCampos;      // Ultimo Bloque con los campos de la Tabla
    int pBloqRegistros;   // Primer Bloque con los Registros de la Tabla
    int uBloqRegistros;   // Ultimo Bloque con los Registros de la Tabla
    char nombTabla[15];   // Nombre de la Tabla
};

struct bloqHCM{         // Struct para leer la metadata de los bloques de tipo Campo
    int numCM;          // Numero de Campos en el Bloque
    int bloqTB;           // Numero del bloque de TB que pertenecen los Campos
    int bloqSigCM;        // Siguiente Bloque con informacion de Campos
    int bloqAntCM;        // Bloque Anterior con informacion de Campos
};

struct bloqICM{         // Struct para leer los registros de tipo Tabla
    char nombCampo[10];   // Nombre de la Tabla
    char tipoCampo[3];    // Tipo de Campo
};

struct bloqHRG{    // Struct para leer la metadata de los bloques de tipo BD
    int numRG;       // Numero de Registros en el bloque
    int bloqCM;      // Numero del Bloque de Campos que pertenecen los Registros
    int bloqSigRG;   // Bloque Siguiente con Registros
    int bloqAntRG;   // Bloque Anterior con Registros
};

struct bloqIRG{   // Struct para leer la metadata de los bloques de tipo BD
    int tamReg;     // Tamano del Registros
    char *buffer;   // Registros de una Tabla Separados por '-'
};

class bdfunciones
{
public:
    bdfunciones();
    // Imprimir Menus
    void menuPrincipal(); // Imprime el menu principal.
    void menuBaseDatos(); // Imprime el menu de Base de Datos.
    void menuTablas(); // Imprime el menu de Tablas.

    //Imprimir Datos
    void imprimirTablas();

    //Funcionaes Generales
    int crearBaseDatos();
    int getBloqueLibre();

    int crearTabla(string nomTabla, int numCampos, string listCampos[]);

};


#endif // BDFUNCIONES_H
