#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

const int maxEntero=32767; // maximo numero para un ENTERO

typedef struct fecha{
	int anio;
	int mes;
	int dia;
} Fecha;

typedef struct materias{
	int codigoMat;
	char nombreMat[30];
	char descripcion[100];
	char semestre[3]; //DEL 1 AL 10 EN NUMEROS ROMANOS
	int creditos; //DE 2 A 5
	materias *prx;
} Materias;

typedef struct cursos{
	int codigocurso;
	materias codigoMat;
	fecha anio; 
	int lapso; // DE 1 A 3
	cursos *prx;
} Cursos;

typedef struct personas{
	long int cedula;	// NO SE PUEDE MODIFICAR
	char nombre_apellido[30];
	fecha fecha;
	char direccion[40];
	Materias *prx;
	Cursos *aba;
	personas *sig;
} Personas;

//DECLARACION DE FUNCIONES

void introduciropcion(int *opcion);
int validar_num (char numero[]);
void AgregaMateria (Materias **p);
void ingcodigo(int *codigo);
void ingnombre(char *Matnombre);
void ingDescripcion(char *Matdescripcion);
Materias *buscarMateria(Materias *mat, int codigo, char nombre[]);
void  BloqMayus ( char s[] );
void ingCredito(int *credito);

int main (){
	Materias *mat = NULL;
	Cursos *cur = NULL;
	Personas *per = NULL;

	int op, aux, aux2;
	do {
		printf("\t MENU\n\n");

		printf(" 1- MANTENIMIENTO\n 2- CONTROL DE ESTUDIOS\n 3- CONSULTAS\n\n 0- SALIR\n\n ");

		fflush(stdin);
		introduciropcion(&op);

		system("cls");
		switch (op) {

			//MENU MANTENIMIENTO
			case 1:
				do {
					printf("\n\tMANTENIMIENTO\n\n");
					printf(" 1- MATERIAS\n 2- CURSOS\n 3- PERSONAS\n\n 0- VOLVER\n\n ");
					fflush(stdin);
					introduciropcion(&aux);
					system("cls");
					switch (aux){
						case 0:
							break;
						//MENU MATERIAS
						case 1:
							do {
								printf("\n\tMATERIAS \n\n");
								printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
								fflush(stdin);
								introduciropcion(&aux2);
								system("cls");
								switch (aux2){
									case 0:
										break;
									//Agregar Materia
									case 1: printf("\n\tAGREGAR\n\n");
											AgregaMateria(&mat);
											fflush(stdin);

											printf("\n\n\tMATERIA AGREGADA CON EXITO!!!\n\n");
											system("cls");
											break;
									//Modificar Materia
									case 2 : printf("\n\tMODIFICAR\n\n");
											break;
									//Consultar Materia
									case 3: printf("\n\tCONSULTAR\n\n");
											/*if (materias) 
												printf("\ntHOLA");
											else 
												printf(" NO EXISTE NINGUNA MATERIA EN EL SISTEMA \n\n");*/
										break;
									//Eliminar Materia
									case 4: printf("\n\tELIMINAR\n\n");
											/*if (materias)
												printf("\ntHOLA");
											else 
												printf(" NO EXISTE NINGUNA MATERIA EN EL SISTEMA\n\n");*/
											break;
									default:
										printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
										Sleep(1000);
								}
							}while(aux2!=0);
							break;
						//MENU CURSOS
						case 2 :
							do {
								printf("\n\tCURSOS \n\n");
								printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
								fflush(stdin);
								introduciropcion(&aux2);
								system("cls");
								switch (aux2){
									case 0:
										break;
									//Agregar Curso
									case 1: printf("\n\tAGREGAR\n\n");
											break;
									//Modificar Curso
									case 2 : printf("\n\tMODIFICAR\n\n");
											break;
									//Consultar Curso
									case 3: printf("\n\tCONSULTAR\n\n");
											/*if (cursos) {
											} else printf(" NO EXISTE NINGUN CURSO EN EL SISTEMA \n\n");*/
										break;
									//Eliminar Curso
									case 4: printf("\n\tELIMINAR\n\n");
											/*if (cursos)
											{
											} else printf(" NO EXISTE NINGUN CURSO EN EL SISTEMA\n\n");*/
											break;
									default:
										printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
										Sleep(1000);
								}
							}while(aux2!=0);
							break;
						//MENU PERSONAS
						case 3: 
							do {
								printf("\n\tPERSONAS \n\n");
								printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
								fflush(stdin);
								introduciropcion(&aux2);
								system("cls");
								switch (aux2){
									case 0:
										break;
									//Agregar Persona
									case 1: printf("\n\tAGREGAR\n\n");
											break;
									//Modificar Persona
									case 2 : printf("\n\tMODIFICAR\n\n");
											break;
									//Consultar Persona
									case 3: printf("\n\tCONSULTAR\n\n");
											/*if (personas) {
											} else printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA \n\n");*/
										break;
									//Eliminar Materia
									case 4: printf("\n\tELIMINAR\n\n");
											/*if (personas)
											{
											} else printf(" NO EXISTE NINGUNA PERSONAS EN EL SISTEMA\n\n");*/
											break;
									default:
										printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
										Sleep(1000);
								}
							}while(aux2!=0);
								
							break;
						
						default:
							printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
					}    // Fin del Switch del menu de MANTENIMIENTO
					if (aux !=0)
						{
						system("pause");
		    			system("cls");
						}

				}while(aux !=0);
				break;

				//MENU CONTROL DE ESTUDIOS
				/////////////////////////////////////////////////////////////////////////////////
				case 2:
					do {
						printf("\n\tCONTROL DE ESTUDIOS \n\n");
						printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
						fflush(stdin);
						introduciropcion(&aux2);
						system("cls");
						switch (aux2){
							case 0:
								break;
							//Agregar Persona
							case 1: printf("\n\tAGREGAR\n\n");
									break;
							//Modificar Persona
							case 2 : printf("\n\tMODIFICAR\n\n");
									break;
							//Consultar Persona
							case 3: printf("\n\tCONSULTAR\n\n");
									/*if (personas) {
									} else printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA \n\n");*/
								break;
							//Eliminar Persona
							case 4: printf("\n\tELIMINAR\n\n");
									/*if (personas)
									{
									} else printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA\n\n");*/
									break;
							default:
								printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
								system("pause");
						}
					}while(aux2!=0);	

					break;
				//MENU CONSULTA
				/////////////////////////////////////////////////////////////////////////////////
				case 3:
					do {
						printf("\n\t\t MENU DE CONSULTA \n\n");
						printf("\t 1- DADO UN NOMBRE DE CURSO, BUSCA SU CODIGO\n");
						printf("\t 2- DADO UN NOMBRE DE ALUMNO, BUSCAR SU CEDULA ASOCIADA Y DATOS\n");
						printf("\t 3- DADO UN ANIO Y UN LAPSO, UBICAR TODOS LOS CURSOS DICTADOS \n");
						printf("\t 4- DADO UN CODIGO DE MATERIA, MOSTRAR TODOS LOS CURSOS QUE LA HAN DICTADO\n");
						printf("\t 5- DADO UN CODIGO DE CUROS, MOSTRAR TODOS LOS DATOS DEL MISMO\n");
						printf("\t 6- DADA UNA MATERIA, MOSTRAR TODOS LOS ALUMNOS QUE HAN APROBADO\n");
						printf("\t 7- TODOS LOS CURSOS DICTADOS EN UN PERIODO DADO\n");
						printf("\t 8- DADA UNA CEDULA, MOSTRAR TODOS LOS CURSOS CON SUS NOTAS TOMADAS POR ESA PERSONA\n");
						fflush(stdin);
						introduciropcion(&aux2);
						system("cls");
						switch (aux2){
							case 0:
								break;
							//Agregar Persona
							case 1: printf("\n\tAGREGAR\n\n");
									break;
							//Modificar Persona
							case 2 : printf("\n\tMODIFICAR\n\n");
									break;
							//Consultar Persona
							case 3: printf("\n\tCONSULTAR\n\n");
									/*if (personas) {
									} else printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA \n\n");*/
								break;
							//Eliminar Materia
							case 4: printf("\n\tELIMINAR\n\n");
									/*if (personas)
									{
									} else printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA\n\n");*/
									break;
							default:
								printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
								system("pause");
						}
					}while(aux2!=0);	

					break;
				/////////////////////////////////////////////////////////////////////////////////
				default:
						if (op != 0)
						{
							printf(" DEBE ELEGIR UNA OPCION VALIDA ");
							Sleep(1000);
						}
					}
					system("cls");

				}while(op !=0); // FIN DEL SWITCH DEL MENU PRINCIPAL
				/////////////////////////////////////////////////////////////////////////////////

				printf("\n HASTA PRONTO!!!\n");
				Sleep(1000);
				return 0;

}

// FUNCIONES Y PROCEDIMIENTOS

/*Funcion para validar que la opcion ingresada por el usuario es mayor que 1 y no contiene letras*/
void introduciropcion(int *opcion) {
	char copia[20];
	int valn;
	fflush(stdin);
	do{
		printf("\n INTRODUZCA NUMERO DE OPCION -> ");
		scanf  ("%s",&copia);
		valn=validar_num(copia);
		if ((strlen(copia)>1)||(valn!=0))
			printf("\n DEBE INGRESAR UN NUMERO QUE SE ENCUENTRE ENTRE LAS OPCIONES \n ");
	} while ((strlen(copia)>1)||(valn!=0));
	*opcion=atoi(copia);
	fflush(stdin);
}

/*Funcion que nos permite validar dado un string, saber si tiene solo numeros o contiene letras*/
int validar_num (char numero[])	{
	int i=0, sw=0,j;
	j=strlen(numero);
	while((i<j)&&(sw==0)){
		if(isdigit(numero[i])!=0){
			i++;
		}else
			sw=1;
		
	}
	return sw;
}

void AgregaMateria (Materias **mat){
	Materias *ax;
	ax = new Materias;
	fflush(stdin);
	do{
		printf(" INTRODUZCA EL CODIGO DE LA MATERIA : ");
		ingcodigo(&ax->codigoMat);
		if (buscarMateria(*mat, ax->codigoMat, ax->nombreMat) != NULL) {//Se valida que el codigo de la Materia sea unico
			printf("\n EL CODIGO INTRODUCIDO YA SE ENCUENTRA EN EL SISTEMA \n");
			Sleep(1); printf("\n\n");
		}
	}	while (buscarMateria(*mat, ax->codigoMat, ax->nombreMat) != NULL);
	printf("\n");
	printf (" INTRODUZCA EL NOMBRE DE LA MATERIA [30 CARACTERES]: ");
	ingnombre(ax->nombreMat);
	printf (" INTRODUZCA UNA BREVE DESCRIPCION DE LA MATERIA [100 CARACTERES]: ");
	ingDescripcion(ax->descripcion);
	fflush(stdin);
	printf (" INTRODUZCA LAS UNIDADES CREDITO [2-5]: ");
	ingCredito(&ax->creditos);

	ax->prx = NULL;
	printf(" %i -- %s -- %s -- %i\n\n", ax->codigoMat , ax->nombreMat, ax->descripcion, ax->creditos);
	system("pause");
	if (mat==NULL) {
		*mat = ax;
	}else {
		ax->prx = *mat;
		*mat = ax;
	}
}


void ingcodigo(int *codigo){
	char copia[5];
	int valn;
	do{
		scanf("%s",&copia);
		valn=validar_num(copia);
		*codigo=atoi(copia);
		if((*codigo>=maxEntero)||(*codigo==0)||(valn!=0)){
			printf("\n EL NUMERO INGRESADO NO ES VALIDO (INGRESE OTRO): ");
		}
	}while ((*codigo>=maxEntero)||(*codigo==0)||(valn!=0));
	fflush(stdin);
	*codigo=atoi(copia);
}

/*funcion para validar que el nombre no excede la cantidad de 30 caracteres*/
void ingnombre(char *Matnombre) {
	do{
		fflush(stdin);
		scanf (" %[^\n]s",&*Matnombre);
		if (!(strlen(Matnombre)<=30))
			printf(" LA CADENA DEBE SER MENOR A 30 CARACTERES: ");
		} while (!(strlen(Matnombre)<=30));
		BloqMayus(Matnombre);
		printf  (" \n");
		fflush(stdin);
}

/*funcion para validar que la descripcion no excede la cantidad de 100 caracteres*/
void ingDescripcion(char *Matdescripcion) {
	do{
		fflush(stdin);
		scanf (" %[^\n]s",&*Matdescripcion);
		if (!(strlen(Matdescripcion)<=100))
			printf(" LA CADENA DEBE SER MENOR A 100 CARACTERES: ");
		} while (!(strlen(Matdescripcion)<=100));
		BloqMayus(Matdescripcion);
		printf  (" \n");
		fflush(stdin);
}

Materias *buscarMateria(Materias *mat, int codigo, char nombre[]) {
	Materias *temp = mat;
	for ( ; temp ; temp=temp->prx) {
		if (codigo == 0) {
			if (strcmp(temp->nombreMat, nombre)==0) return temp; //Se encontro una materia con el mismo nombre
		} else {
			if (temp->codigoMat == codigo)  return temp;	//Se encontro una materia con el mismo codigo
		}		      
	}
	return NULL;
}

/*Rutina que convierte todas las letras de un string en mayusculas*/
void  BloqMayus ( char s[] ){
	int i;
	for (i = 0; s[i]!='\0'; i++){
		if(s[i] >= 'a' && s[i] <= 'z')
			{
			s[i] = s[i] - 32;
			}
	}
}

/*funcion para validar las unidades credito de la materia*/
void ingCredito(int *credito){
	char copiacredito[5];
	int valn;
	bool ver = false;
	do {
		fflush(stdin);
		scanf ("%s",&copiacredito);
		valn=validar_num(copiacredito);
		if ((strlen(copiacredito)<1)||(valn!=0)) {
		}	else if ((atoi(copiacredito)>1) && (atoi(copiacredito)<6)){
			*tipo=atoi(copiacredito);
			ver = true;
			}
			if (ver==false)
				printf(" \n OPCION INVALIDA, INGRESE DE NUEVO -> ");
	} while (ver == false);
		fflush(stdin);
}
