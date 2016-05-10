#include "bdfunciones.h"
#include <cstring>
#include <math.h>
#include <stdio.h>
#include <fstream>

FILE *f[5]; // 0-BDFile 1-BDFile_Tablas 2-BDFile_Campos 3-BDFile_Registros
int bloqLibre=0,
    block_size=512,
    block_count=2048,
    pos=0;
bdfunciones bdfunc;
struct bloqHTB bHTB;
struct bloqITB bITB;
struct bloqHCM bHCM;
struct bloqICM bICM;
struct bloqHRG bHRG;
struct bloqIRG bIRG;

bdfunciones::bdfunciones()
{

}

void bdfunciones::menuPrincipal(){
    int opcPri;
    string opcion="OK";
    cout<<" * * * * * * * * * * * * * * * * * * * * * * \n";
    cout<<" * Menu de Mantenimiento de Base de Datos  * \n";
    cout<<" * * * * * * * * * * * * * * * * * * * * * * \n\n";
    cout<<"1. Ver Base de datos disponibles. \n";
    cout<<"2. Mantenimiento de Base de Datos. \n";
    cout<<"3. Salir del Sistema \n\n";
    while(opcion=="OK"){
        cout<<"Ingrese un numero: ";
        cin>>opcPri;
        if(opcPri>=1 && opcPri<=3){
            opcion=="NOOK";
            switch(opcPri){
                case 1:
                    cout << "Es 1 \n";
                    menuBaseDatos();
                break;
                case 2:
                    cout << "Es 2 \n";
                break;
                case 3:
                exit(1);
            }
        }
        if(cin.fail()){
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Recuerde que debe de ingresar valores numericos.\n";
        }
    }
}

void bdfunciones::menuBaseDatos(){
    int opcPri;
    string opcion="OK";
    cout<<" * * * * * * * * * * * * * * * * * * * * * * \n";
    cout<<" * Menu de Visualizacion de Base de Datos  * \n";
    cout<<" * * * * * * * * * * * * * * * * * * * * * * \n\n";
    cout<<"1. BDKevin \n";
    cout<<"2. Regresar al Menu Principal \n";
    cout<<"3. Salir del Sistema \n\n";
    while(opcion=="OK"){
        cout<<"Ingrese un numero: ";
        cin>>opcPri;
        if(opcPri>=1 && opcPri<=3){
            opcion=="NOOK";
            switch(opcPri){
                case 1:
                    menuTablas();
                break;
                case 2:
                    cout << "Es 2 \n";
                    menuPrincipal();
                break;
                case 3:
                exit(1);
            }
        }
        if(cin.fail()){
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Recuerde que debe de ingresar valores numericos.\n";
        }
    }
}

void bdfunciones::menuTablas(){
    int opcPri;
    string opcion="OK";
    cout<<" * * * * * * * * * * * * * * * * * * * * * * \n";
    cout<<" * Menu de Visualizacion de Base de Datos  * \n";
    cout<<" * * * * * * * * * * * * * * * * * * * * * * \n\n";
    cout<<"1. Ver Tablas Disponibles \n";
    cout<<"2. Regresar al Menu de Base de Datos \n";
    cout<<"3. Regresar al Menu Principal \n";
    cout<<"4. Salir del Sistema \n\n";
    while(opcion=="OK"){
        cout<<"Ingrese un numero: ";
        cin>>opcPri;
        if(opcPri>=1 && opcPri<=4){
            opcion=="NOOK";
            switch(opcPri){
                case 1:
                    cout << "Es 1 \n";
                break;
                case 2:
                    cout << "Es 2 \n";
                    menuBaseDatos();
                break;
                case 3:
                    cout << "Es 3 \n";
                    menuPrincipal();
                break;
                case 4:
                exit(1);
                break;
            }
        }
        if(cin.fail()){
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Recuerde que debe de ingresar valores numericos.\n";
        }
    }
}

int bdfunciones:: getBloqueLibre(){
    int returnBloque;
    rewind(f[0]);
    fscanf(f[0],"%i",&bloqLibre);
    if(bloqLibre>2048){
        return -1; // Todos los bloques se encuentran Llenos
    }
    returnBloque = bloqLibre;
    bloqLibre+=1;
    rewind(f[0]);
    fprintf(f[0],"%i",bloqLibre);
    return returnBloque;
}

int bdfunciones::crearTabla(string nomTabla, int numCampos, string listCampos[])
{
    int i, getBloqueL, pos;
    f[0]=fopen("BDFile.dat","w"); //Creo el archivo maestro de las BD.
    if(f[0]==NULL){
        return -1; // Error al abrir el archivo.
    }
    getBloqueL=getBloqueLibre();
    if(getBloqueL==-1){
        return -2; // Todos los bloques se encuentran llenos.
    }
    pos=12+(getBloqueL*512);
    fseek(f[0],pos,SEEK_SET);
}

int bdfunciones::crearBaseDatos(){
    int i, getBloqueL, pos, pBloqTB=0, uBloqTB=NULL;
    char *buffer=(char*)malloc(block_size);
    if(buffer==NULL){
        return -2; // No se ha podido reservar el espacio de memoria.
    }
    //Crear Archivo de Gestor de Base de Datos
    f[0]=fopen("BDFile.dat","w"); //Creo el archivo maestro de las BD.
    if(f[0]==NULL){
        return -1; // Error al abrir el archivo.
    }

    //Ingreso la Metadata del Archivo (SuperBlock)
    fprintf(f[0],"%i",bloqLibre); // Indicador del siguiente bloque Libre
    fprintf(f[0],"%i",block_size); // Tamano de los Bloques
    fprintf(f[0],"%i",block_count); // Numero de Bloques
    fprintf(f[0],"%i",pBloqTB); // Numero de Bloques
    fprintf(f[0],"%i",uBloqTB); // Numero de Bloques

    //Crear los bloques del Archivo
    memset(buffer,'*',block_size);
    for(i=0 ; i<block_count; i++){
        fwrite(buffer,(sizeof(char)),block_size,f[0]);
    }
    free(buffer);

    // Variables utilizadas en la lectura del archivo
    int numTablas, tamReg, numTBCM, numTBRG;
    char *bufferReg;

    //Ingreso de las Tablas prediseñadas
    getBloqueL=getBloqueLibre();
    if(getBloqueL==-1){
        return -2; // Todos los bloques se encuentran llenos.
    }
    f[1]=fopen("BDFile_Tablas.txt","r");
    if(f[1]==NULL){
        return -1; // Error al abrir el archivo.
    }
    fscanf(f[1],"%i",&bHTB.numTB);
    fgetc(f[1]);
    bHTB.bloqAntTB=-1;
    bHTB.bloqSigTB=-1;
    pos=20+(getBloqueL*512);
    fseek(f[0],pos,SEEK_SET);
    fwrite(&bHTB,sizeof(bloqHTB),1,f[0]); // Ingreso de Bloque de Header
    for(int i=0;i<bHTB.numTB;i++){
        fscanf(f[1],"%i",&bITB.numCampos);
        fread(bITB.nombTabla,1,15,f[1]);
        bITB.pBloqCampos=i+1;                // Tabla 1 2 3 4 5
        bITB.uBloqCampos=i+1;
        bITB.pBloqRegistros=i+bHTB.numTB+1;  // Campo 6 7 8 9 10
        bITB.uBloqRegistros=i+bHTB.numTB+1;
        fwrite(&bITB,sizeof(bloqITB),1,f[0]);
    }
    fclose(f[1]);

    //Ingreso de los Campos predisenados
    f[2]=fopen("BDFile_Campos.txt","r");
    if(f[2]==NULL){
        return -1; // Error al abrir el archivo.
    }
    fscanf(f[2],"%i",&numTBCM);
    fgetc(f[2]);
    for(int i=0; i<numTBCM;i++){
        getBloqueL=getBloqueLibre();
        pos=20+(getBloqueL*512);
        fseek(f[0],pos,SEEK_SET);
        if(getBloqueL==-1){
            return -2; // Todos los bloques se encuentran llenos.
        }
        fscanf(f[2],"%i",&bHCM.numCM);
        bHCM.bloqAntCM=NULL;
        bHCM.bloqSigCM=NULL;
        bHCM.bloqTB=0;
        fwrite(&bHCM,sizeof(bloqHCM),1,f[0]);
        for(int k=0;k<bHCM.numCM;k++){
            fread(bICM.nombCampo,1,10,f[2]);
            fread(bICM.tipoCampo,1,3,f[2]);
            fwrite(&bICM,sizeof(bloqICM),1,f[0]);
            cout << "NomCampo: " << bICM.nombCampo << "\n";
            cout << "TipoCampo: " << bICM.tipoCampo << "\n";
        }
    }
    fclose(f[2]);

    //Ingreso de los Registros predisenados
    f[3]=fopen("BDFile_Registros.txt","r");
    if(f[3]==NULL){
        return -1; // Error al abrir el archivo.
    }
    fscanf(f[3],"%i",&numTBRG);
    fgetc(f[3]);
    cout << "numTBRG: "<<numTBRG <<"\n";

    for(int i=0; i<numTBRG;i++){
        fscanf(f[3],"%i",&bHRG.numRG);
        fgetc(f[3]);
        getBloqueL=getBloqueLibre();
        pos=20+(getBloqueL*512);
        fseek(f[0],pos,SEEK_SET);
        if(getBloqueL==-1){
            return -2; // Todos los bloques se encuentran llenos.
        }
        bHRG.bloqAntRG=NULL;
        bHRG.bloqSigRG=NULL;
        bHRG.bloqCM=i+1;
        fwrite(&bHRG,sizeof(bloqHRG),1,f[0]);
        cout << "numRG: "<<bHRG.numRG <<"\n";
        for(int k=0; k<bHRG.numRG;k++){
            fscanf(f[3],"%i",&bIRG.tamReg);
            bIRG.buffer=(char*)malloc(bIRG.tamReg);
            fread(bIRG.buffer,1,bIRG.tamReg,f[3]);
            fwrite(&bIRG,sizeof(bloqIRG),1,f[0]);
            cout << "TamReg: " << bIRG.tamReg << "\n";
            cout << "Buffer: " << bIRG.buffer << "\n";
            free(bIRG.buffer);
            }
        }
    fclose(f[3]);







    /////////////////////////////////////////////////////////////////////////////////////////////////////////


    /*

    f[2]=fopen("BDFile_Tablas.txt","r");
    if(f[2]==NULL){
        return -1; // Error al abrir el archivo.
    }
    rewind(f[2]);
    for(int i=0;i<numTablas;i++){
        fscanf(f[2],"%i",&bITB.numCampos);
        fread(bITB.nombTabla,1,15,f[2]);
        bITB.pBloqRegistros=1+1+i;
        fwrite(&bITB,sizeof(bloqITB),1,f[0]); // Ingreso de Bloque de Header
        for(int k=0;k<bITB.numCampos;k++){
            fread(bICM.nombCampos,1,10,f[2]);
            fread(bICM.tipoCampos,1,3,f[2]);
            fwrite(&bICM,sizeof(bloqICM),1,f[0]); // Ingreso de Bloque de Header
        }
    }
    getBloqueL=getBloqueLibre();
    if(getBloqueL==-1){
        return -2; // Todos los bloques se encuentran llenos.
    }
    pos=12+(getBloqueL*512);
    fseek(f[0],pos,SEEK_SET);

    f[3]=fopen("BDFile_RegEmpleado.txt","r");
    if(f[3]==NULL){
        return -1; // Error al abrir el archivo.
    }

    fscanf(f[3],"%i",&bHRG.numRG);
    bHRG.bloqAntRG=2;
    bHRG.bloqSigRG=-1;
    fwrite(&bHRG,sizeof(bloqHRG),1,f[0]);
    for(int i=0;i<bHRG.numRG;i++){
        fgetc(f[3]);
        fscanf(f[3],"%i",&tamReg);
        tamReg+=1;
        bufferReg = ((char*)malloc(tamReg));
        fread(bufferReg,1,tamReg,f[3]);
        fwrite(bufferReg,sizeof(char),tamReg,f[0]);
    }
    free(bufferReg);
    fclose(f[3]);
    getBloqueL=getBloqueLibre();
    if(getBloqueL==-1){
        return -2; // Todos los bloques se encuentran llenos.
    }
    pos=12+(getBloqueL*512);
    fseek(f[0],pos,SEEK_SET);

    f[4]=fopen("BDFile_RegPlanilla.txt","r");
    if(f[4]==NULL){
        return -1; // Error al abrir el archivo.
    }

    fscanf(f[4],"%i",&bHRG.numRG);
    bHRG.bloqAntRG=2;
    bHRG.bloqSigRG=-1;
    fwrite(&bHRG,sizeof(bloqHRG),1,f[0]);
    for(int i=0;i<bHRG.numRG;i++){
        fgetc(f[4]);
        fscanf(f[4],"%i",&tamReg);
        tamReg+=1;
        bufferReg = ((char*)malloc(tamReg));
        fread(bufferReg,1,tamReg,f[4]);
        fwrite(bufferReg,sizeof(char),tamReg,f[0]);
    }
    free(bufferReg);
    fclose(f[4]);

    fclose(f[0]);
    */
    return 0; // El proceso se llevo a cabo con exito.

    }


























