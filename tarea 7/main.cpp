//
//  main.cpp
//  tarea 7
//
//  Created by Luis Rivas on 10/04/24.
//

#include <iostream>
using namespace std;

const char *nombre_archivo = "Estudiante.dat";

struct Estudiantes{
    int codigo;
    char nombres[50];
    char apellidos[50];
    int telefono;
};

void leer();
void crear();
void actualizar();
void borrar();

int main(){
    leer();
    //crear();
    //actualizar();
    borrar();
//archivos binarios
    system ("pause");
}

void leer(){
    system ("cls");
    FILE* Estudiante = fopen(nombre_archivo, "rb");
    if (!Estudiante){
        Estudiante = fopen(nombre_archivo, "w+b");
    }
    Estudiantes estudiantes;
    int id=0; //Indice o pocision del registro dentro de nuestro archivo
    fread(&estudiantes,sizeof(Estudiantes),1,Estudiante);
    cout<<"_________________________________________"<<endl;
    cout<<"ID"<<"|"<<"Codigo"<<"|"<<"   Nombres   "<<"|"<<"   Apellidos   "<<"|"<<"   Telefono   "<<endl;
    do{
        cout<<id<<"|"<<estudiantes.codigo<<"|"<<estudiantes.nombres<<"|"<<estudiantes.apellidos<<"|"<<estudiantes.telefono<<endl;
        fread(&estudiantes,sizeof(Estudiantes),1,Estudiante);
        id+=1;
    }while(feof(Estudiante)==0);
    fclose(Estudiante);
}
    
void crear(){
    FILE* Estudiante = fopen(nombre_archivo,"a+b");
    
    char res;
    Estudiantes estudiantes;
    
    do{
        fflush(stdin);
        
        cout<<"Ingrese Codigo: ";
        cin>>estudiantes.codigo;
        cin.ignore();
        
        cout<<"Ingrese Nombres: ";
        cin.getline(estudiantes.nombres, 50);
        cout<<"Ingrese Apellidos: ";
        cin.getline(estudiantes.apellidos, 50);
        
        cout<<"Ingrese telefono: ";
        cin>>estudiantes.telefono;
        
        fwrite(&estudiantes,sizeof(Estudiantes),1,Estudiante);
        
        cout<<"Desea ingresar otro estudiante(s/n): ";
        cin>>res;
    }while(res=='s' || res=='s');
    
    fclose(Estudiante);
    leer();
}

void actualizar(){
    FILE* Estudiante = fopen(nombre_archivo,"r+b");
    
    Estudiantes estudiantes;
    int id=0;
    cout<<"Ingrese el ID que desea modificar: "<<endl;
    cin>>id;
    fseek(Estudiante,id * sizeof(Estudiantes),SEEK_SET);
    
        cout<<"Ingrese Codigo: ";
        cin>>estudiantes.codigo;
        cin.ignore();
        
        cout<<"Ingrese Nombres: ";
        cin.getline(estudiantes.nombres, 50);
        cout<<"Ingrese Apellidos: ";
        cin.getline(estudiantes.apellidos, 50);
        
        cout<<"Ingrese telefono: ";
        cin>>estudiantes.telefono;
        
        fwrite(&estudiantes,sizeof(Estudiantes),1,Estudiante);
    
    fclose(Estudiante);
    leer();
}

void borrar(){
    const char *nombre_archivo_temp = "Estudiante_temp.dat";
    
    FILE* Estudiante_temp = fopen(nombre_archivo_temp, "w+b");
    FILE* Estudiante = fopen(nombre_archivo, "rb");
    Estudiantes estudiantes;
    
    int id=0, id_n=0;
    
    cout<<"Ingrese el ID a eliminar: ";
    cin>>id;
    
    while(fread(&estudiantes, sizeof(Estudiantes),1,Estudiante)){
        if (id_n !=id ){
            fwrite(&estudiantes,sizeof(Estudiantes),1,Estudiante_temp);
        }
        id_n++;
    }
    
    fclose(Estudiante_temp);
    fclose(Estudiante);
    
    Estudiante_temp = fopen(nombre_archivo_temp, "rb");
    Estudiante = fopen(nombre_archivo, "wb");
    while(fread(&estudiantes,sizeof(Estudiantes),1,Estudiante_temp)){
        fwrite(&estudiantes,sizeof(Estudiantes),1,Estudiante);
    }
    fclose(Estudiante);
    fclose(Estudiante_temp);
}
