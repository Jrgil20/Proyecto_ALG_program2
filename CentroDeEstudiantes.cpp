/*
    Nombre:
		MINI PROYECTO 1	
	Objetivo:
		Se desea crear un programa que maneje el control de estudios de un centro educativo.
	Descripcion:
		`En la institución se dictan clases semestralmente, se tienen tres lapsos (1,2,3) anuales, el período corresponde al curso de verano anual.
		`Las materias a dictar están guardadas en el sistema. Se pueden modificar, consultar o eliminar materias. 
		`Cuando se elimina una materia se deben borrar del sistema todos los cursos con esa materia como contenido. 
		`El código de materia es único y no se puede modificar una vez creado.
		`Para registrar un curso deben preexistir la materia (código) y los alumnos (cédula).
		`Un alumno puede solo puede tener aprobada una materia una vez, luego de ello no puede reinscribirla.
		`Puede haber reprobado la materia un máximo de 4 (cuatro) veces. En caso de reprobar ya no puede volver a inscribirse en el instituto.
		`Puede haber retirado la materia infinita cantidad de veces. 
		`El código del curso es único y no puede ser modificado una vez creado.
			-Cuando se elimina un curso, deben borrarse todas sus referencias en el sistema
			-Cuando se elimina un alumno deben borrarse todas sus referencias en el sistema.
			-El sistema debe manejarse en listas dinámicas en memoria principal y almacenarse en memoria secundaria.
		Se tienen tres listas principales:
			*Materias:
				 código dela materia (entero),
				 nombre (hasta 30 caracteres),
				 descripción(máximo 100 caracteres),
				 semestre al que pertenece (I,II, …, X),
				 numero de créditos ( 2 a 5 ).
			*Cursos:
				Código del curso ( entero ),
				código materia, año ( XXXX), 
				Lapso (1..3: indica primer semestre, segundo o verano).
			*Personas:
				Cédula de identidad ( entero largo ),
				nombres y apellidos,
				fecha de nacimiento,
				dirección.
				La cedula es única y no puede ser modificada. 
				Si se elimina una persona en el sistema deben eliminarse todas sus referencias en el sistema.
				Igual mente cada estudiante tiene una lista de los cursos en que ha participado.
				Allí se almacenan: código de curso y la nota correspondiente.
	Características del sistema:
		El sistema tiene un menú principal que tiene tres (03) opciones principales
		+Mantenimiento: (tablas base del sistema)
			-Materias:                             
				*agregar
				*modificar
				*consultar 
				*eliminar.
			-Cursos:
				*agregar, 
				*modificar
				*consultar 
				*eliminar.
			-Personas:
				*agregar
				*modificar
				*consultar 
				*eliminar personas (sin datos de cursos)
		+Control de estudios
			-Alumnos:
				*Agregar 
				*modificar 
				*eliminar alumnos en cursos con sus notas correspondientes.
			-Una persona solo se puede inscribir una vez en cada Curso.
			-No se puede inscribir a un alumno en una materia que ya tenga aprobada. 
            -Se puede modificar la nota en un curso y alumnos dados
		+Consultas:
			- Dado un nombre de curso buscar su código.
			- Dado un nombre de alumno buscar su(s) cédula(s) asociada(s) y demás datos (sinónimos para ubicar la cédula que nos interesa).
			- Dado un año y un lapso ubicar todos los cursos dictados ( nombre de curso, materia, cantidad de alumnos aprobados y reprobados)
			- Dado un código de materia mostrar todos los cursos que la han dictado (nombre de curso, materia, cantidad de alumnos aprobados y reprobados)
			-Dado un código de curso mostrar todos los datos del mismo con la materia y los alumnos con sus notas
			-Dada una materia ( código ) mostrar los alumnos que la han aprobado (cedula, apellido y nombre con su nota )
			-Todos los cursos (con sus alumnos y notas) dictados en un periodo dado.
			-Dada una cedula mostrar todos los cursos con sus notas tomadas por esapersona
*/
/*
	Entrega inicial: 01 de junio 2023 vía módulo 7 (archivo comprimido con todos los fuentesy archivos de datos).
	Grupos de un máximo de 04 (cuatro) personas. (misma sección).
	
	Contenido de la entrega: 
	todo el mantenimiento del sistema (tablas):
		-materias
		-cursos 
		-personas 
		(agregar, modificar y eliminar, así como el almacenamiento y recuperación de la información con archivos).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*estructuras y tipos secundarios*/
typedef int year;	typedef int month;	typedef int day; typedef  int Codigo_curso; typedef int Codigo_Materia;
const  int maxEntero=1294967295;

struct fecha
{
	year yyyy;
	month mm;
	day dd;
};

struct Participacion
{
	Codigo_curso Codigo_del_curso;	
	int nota;
	Participacion *prx;
};

/*Se tienen tres listas principales:*/
struct Materias
{
	Codigo_Materia Codigo_de_la_Materia;
	char Nombre_de_la_Materia[30];
	char Descripcion_de_la_Materia[100];
	int Semestre;
	int Creditos_de_la_Materia;// se debe restringir al rango de 2 a 5
	Materias *prx;
};

struct Cursos
{
	Codigo_curso Codigo_del_curso;
	/*Para registrar un curso deben preexistir la materia (código) */
	Codigo_Materia Codigo_de_la_Materia; 
	year AAAA;
	int lapso;// se debe restringir al rango de 1 a 3
	/*Cuando se elimina un curso, deben borrarse todas sus referencias en el sistema.*/
	Cursos *prx;
};

struct Personas
{
	long int cedula;	// restricion: no se puede modificar
	char nombre_apellido[30];
	fecha Fecha_de_Nacimiento;
	char direccion[40];
	Participacion Record;
	/*Si se elimina una persona en el sistema deben eliminarse todas sus referencias en el sistema.*/
	Personas *prx;

};

/*Rutinas*/

int Verificar_Semestre();
void imprimir_Romano(int Numero);
void Agregar_Materia(Materias **Nueva_materia);
void insertar_MateriaOrdenadamente( Materias **lista, Materias **Nuevo_nodo);
void Agregar_Curso(Cursos **,Materias **Nueva_materia);
void Ingresar_codigo( int *codigo,char De[15], Materias **);
void Ingresar_codigo_curso( int *codigo,char De[15], Cursos **q);
void Ingresar_codigo_aux(int *codigo, char De[15]);
void ingresar_Creditos(int *Rango,int max,int min);
void Ingresar_lapso(int *Rango,int max,int min);
int Existe_codigo(int codigo,Materias **En_Materias);
int Existe_codigo_curso(int codigo,Cursos **En_Cursos);
int validar_numero (char numero[]);
void Modificar_Materia(Materias **materia);
void Modificar_Curso(Cursos **);
void Consultar_materia(Materias *Las_materias);
void Consultar_curso(Cursos *Los_cursos);
void Eliminar_curso_materia (Cursos **Los_cursos, int codigo_mat);
void Eliminar_materia (Materias **Las_materias,Cursos **);
void Eliminar_curso (Cursos **Los_cursos);
void Limitar_Caracteres (char *copia, int max);
void cambio(char c1[]);

int main ()
{
	Materias *Materia=NULL;
	Cursos *Curso =NULL;
	int opciones=0; 

	do
	{//Menu
		system("cls");
		printf("\t MENU\n\n");
		printf(" 1- MANTENIMIENTO\n 2- CONTROL DE ESTUDIOS\n 3- CONSULTAS\n\n 0- SALIR\n\n ");
		scanf_s("%d",&opciones);
		switch(opciones)
		{
			case 1://Mantenimiento del sistema
			{
				int opciones_mantenimiento=0; 
				do
				{//Menu de Mantenimiento del sistema
					system("cls");
					printf("\t Menu de Mantenimiento\n\n");
					printf(" 1- Materias\n 2- Cursos\n 3- Personas\n\n 0- SALIR\n\n ");
					scanf_s("%d",&opciones_mantenimiento);
					switch(opciones_mantenimiento)
					{
						case 1:
						{
							int opciones_mantenimiento_Materias=0; 
							do
							{//Menu de Mantenimiento Materias
								system("cls");
								printf("\t Menu de mantenimiento de materias\n\n");
								printf(" 1- Agregar\n 2- Modificar\n 3- Consultar\n 4- Eliminar\n\n 0- SALIR\n\n ");
								scanf_s("%d",&opciones_mantenimiento_Materias);
								switch(opciones_mantenimiento_Materias)
									{
										case 1://Agregar Materia
										{	
											Agregar_Materia(&Materia); 
											printf("\n Materia [%d] \'%s\' %i (%i) : %s \n\n Agregada exitosamente \n",Materia->Codigo_de_la_Materia,Materia->Nombre_de_la_Materia,Materia->Semestre,Materia->Creditos_de_la_Materia,Materia->Descripcion_de_la_Materia);
											/*lo anteriror es solo una verificacion de datos */system("pause");
											break;
										}

										case 2://Modificar
										{
											Modificar_Materia(&Materia);
											break;
										}
										case 3://Consultar
										{
											Consultar_materia(Materia);
											break;
										}
										case 4://Eliminar
											Eliminar_materia(&Materia,&Curso);
											break;

										default:
											if (opciones_mantenimiento_Materias)
											{
												printf("\n\nEsta opcion no es valida\n");
												system("pause");break;
											}
									}
							}while (opciones_mantenimiento_Materias);
							break;
						}

						case 2:
						{
							int opciones_mantenimiento_Cursos=0; 
							do
							{//Menu de Mantenimiento Cursos
								system("cls");
								printf("\t Menu de mantenimiento de cursos\n\n");
								printf(" 1- Agregar\n 2- Modificar\n 3- Consultar\n 4- Eliminar\n\n 0- SALIR\n\n ");
								scanf_s("%d",&opciones_mantenimiento_Cursos);
								switch(opciones_mantenimiento_Cursos)
								{
									case 1://Agregar
										Agregar_Curso(&Curso,&Materia);
										if(Curso){
										 printf("\n Curso [%d] (%i) (%i) (%i)\n\n Agregado exitosamente \n",Curso->Codigo_del_curso,Curso->Codigo_de_la_Materia,Curso->AAAA,Curso->lapso);
										 system("pause");
										}
										break;

									case 2://Modificar
										Modificar_Curso(&Curso);
										break;

									case 3://Consultar
										Consultar_curso(Curso);
										break;

									case 4://Eliminar
										Eliminar_curso(&Curso);
										break;

									default:
										if (opciones_mantenimiento_Cursos)
										{
											printf("\n\nEsta opcion no es valida\n");
											system("pause");break;
										}
								}
							}while (opciones_mantenimiento_Cursos);
							break;
						}

						case 3:
						{
							int opciones_mantenimiento_Personas=0; 
							do
							{//Menu de Mantenimiento Personas
								system("cls");
								printf("\t Menu de mantenimiento de personas\n\n");
								printf(" 1- Agregar\n 2- Modificar\n 3- Consultar\n 4- Eliminar\n\n 0- SALIR\n\n ");
								scanf_s("%d",&opciones_mantenimiento_Personas);
								switch(opciones_mantenimiento_Personas)
								{
									case 1://Agregar
										break;

									case 2://Modificar
										break;

									case 3://Consultar
										break;

									case 4://Eliminar personas (sin datos de cursos)
										break;

									default:
										if (opciones_mantenimiento_Personas)
										{
											printf("\n\nEsta opcion no es valida\n");
											system("pause");break;
										}
								}
							}while (opciones_mantenimiento_Personas);
							break;
						}	

						default:
							if (opciones_mantenimiento)
							{
								printf("\n\nEsta opcion no es valida\n");
								system("pause");break;
							}
						}
					}while (opciones_mantenimiento);
					break;
				}

			case 2:
			{
				int opciones_control_estudios=0;
				do
				{//Menu Control de Estudios
					system("cls");
					printf("\t Menu Control de Estudios\n\n");
					printf(" 1- Agregar alumnos \n 2- Modificar alumnos \n 3- Eliminar alumnos\n\n 0- SALIR\n\n  ");
					scanf_s("%d",&opciones_control_estudios);
					switch(opciones_control_estudios)
					{
						case 1://Agregar alumnos
							break;

						case 2://Modificar alumnos
							break;

						case 3://eliminar alumnos en cursos con sus notas correspondientes.
							break;

						default:
							if (opciones_control_estudios)
							{
								printf("\n\nEsta opcion no es valida\n");
								system("pause");break;
							}
					}
				}while (opciones_control_estudios);
			}

			case 3:
			{
				int opciones_consultas=0;
				do
				{//Menu Control de Estudios
					system("cls");
					printf("\t Menu Control de Estudios\n\n");
					printf(" \n\n 0- SALIR\n\n  ");
					scanf_s("%d",&opciones_consultas);
					switch(opciones_consultas)
					{
						case 1://Dado un nombre de curso buscar su código.
							break;

						case 2://Dado un nombre de alumno buscar su(s) cédula(s) asociada(s) y demás datos (sinónimos para ubicar la cédula que nos interesa).
							break;

						case 3://Dado un año y un lapso ubicar todos los cursos dictados ( nombre de curso, materia, cantidad de alumnos aprobados y reprobados)
							break;

						case 4: //Dado un código de materia mostrar todos los cursos que la han dictado (nombre de curso, materia, cantidad de alumnos aprobados y reprobados)
							break;

						case 5://Dado un código de curso mostrar todos los datos del mismo con la materia y los alumnos con sus notas
							break;

						case 6://Dada una materia ( código ) mostrar los alumnos que la han aprobado (cedula, apellido y nombre con su nota )
							break;

						case 7://Todos los cursos (con sus alumnos y notas) dictados en un periodo dado.
							break;

						case 8://Dada una cedula mostrar todos los cursos con sus notas tomadas por esa persona
							break;

						default:
							if (opciones_consultas)
							{
								printf("\n\nEsta opcion no es valida\n");
								system("pause");break;
							}
					}
				}while (opciones_consultas);
			}

			default:
				if (opciones)
				{
					printf("\n\nEsta opcion no es valida\n");
					system("pause");break;
				}
		}
	}while (opciones);
	system("pause");
	return 0;
}

void Agregar_Materia(Materias **Nueva_materia)
{
	Materias *Aux= new Materias; fflush(stdin);
	do
	{
		Ingresar_codigo(&Aux->Codigo_de_la_Materia,"de la materia", Nueva_materia);
		/* verificar : que el codigo de la materia sea unico*/
		printf("\nIngrese el nombre de la materia: ");
		fgets(Aux->Nombre_de_la_Materia,30,stdin);
		cambio(Aux->Nombre_de_la_Materia);
		fflush(stdin);
		printf("\nIngrese la Descripcion de la materia: ");
		fgets(Aux->Descripcion_de_la_Materia,100,stdin);
		cambio(Aux->Descripcion_de_la_Materia);
		fflush(stdin);
		Aux->Semestre=Verificar_Semestre();
		fflush(stdin);
		ingresar_Creditos(&Aux->Creditos_de_la_Materia,5,2);
		insertar_MateriaOrdenadamente( Nueva_materia, &Aux);
	}while(false);

}

void insertar_MateriaOrdenadamente( Materias **lista, Materias **Nuevo_nodo)
{
	if (*lista==NULL || (*Nuevo_nodo)->Semestre<(*lista)->Semestre)//mientras el nuevo nodo sea la nueva cabeza
	{
		(*Nuevo_nodo)->prx = *lista;//apunta a lo que apuntaba p
		*lista = *Nuevo_nodo;//hace el nuevo nodo cabeza
	}else
	{
		Materias *aux=*lista;//crea un auxiliar
		while(aux->prx && aux->prx->Semestre <= (*Nuevo_nodo)->Semestre)
			aux=aux->prx;// este avanza hasta encontrar la posicion
		(*Nuevo_nodo)->prx=aux->prx;//enlazamos el nodo a lo que apunta e auxiliar
		aux->prx=*Nuevo_nodo; //enlazamos el auxiliar al nuevo nodo
	}
}

void Agregar_Curso(Cursos **c,Materias **Materia){
	Cursos *Aux=*c;
	if(*Materia){
	 int cod;
	 Ingresar_codigo_aux(&cod,"Codigo de la materia");
     if(Existe_codigo(cod,Materia)){
	  Cursos *Aux= new Cursos;
	  do
	  {
		  printf("\n");
		  Aux->Codigo_de_la_Materia = cod;
		  Ingresar_codigo_curso(&Aux->Codigo_del_curso,"del Curso", c);
		  printf("\n");
		  Ingresar_codigo_aux(&Aux->AAAA,"Ingrese el anio");
		  printf("\n");
		  Ingresar_lapso(&Aux->lapso,3,1);
		  Aux->prx=*c;
		  *c=Aux;
	   }while(false);
	 }
	 else
	 {
		 printf("La materia no existe, por lo que no se creara el curso\n");
		 system("pause");
	 }
	}
	else
	{
		printf("No existen materias, por lo que no se pueden crear cursos\n");
		system("pause");
	}

}

void Modificar_Materia(Materias **materia)
{
	Materias *Respaldo= *materia; int Elegido;
	char copia[10];
	if (*materia){
		Materias *consulta=*materia, *temp=NULL;
		Ingresar_codigo_aux(&Elegido," Codigo de La materia a modificar");
		/*printf("\n\t INSERTE EL CODIGO DE LA MATERIA A MODIFICAR = ");
		scanf_s("%i",&Elegido);*/
		while((Respaldo)&&(Respaldo->Codigo_de_la_Materia != Elegido))
			Respaldo=Respaldo->prx;
		if (!Respaldo){
			printf("\n\tLa materia [%i] no se encuentra\n", Elegido);system("pause");
		}else{
			int opciones_de_Modificacion=0; 
			do
			{//Menu de Mantenimiento Cursos
				system("cls");
				printf("\t Que desea modificar?\n\n");
				printf(" 1- Nombre de la materia\n 2- Descripcion de la materia\n 3- Semestre de la materia\n 4- Creditos de la materia\n\n 0- SALIR\n\n ");
				scanf_s("%d",&opciones_de_Modificacion);
				switch(opciones_de_Modificacion)
				{
					case 1://Nombre
					{
						fflush(stdin);
						printf("\nIngrese el nuevo nombre de la materia: ");
						Limitar_Caracteres(Respaldo->Nombre_de_la_Materia,30);
						fflush(stdin);
						printf("\nNombre de %s modificado exitosamente",Respaldo->Nombre_de_la_Materia); _sleep(500);
						/* verificar : que el nombre solo tenga un maximo de 30 carcteres*/
						break;
					}
					case 2://Descripcion
						fflush(stdin);
						printf("\nIngrese la nueva Descripcion de la materia: ");
						Limitar_Caracteres(Respaldo->Descripcion_de_la_Materia,100);
						fflush(stdin);
						printf("\nDescripcion de %s modificado exitosamente",Respaldo->Nombre_de_la_Materia); _sleep(500);
						break;

					case 3://Semestre
							Respaldo->Semestre=Verificar_Semestre();
							fflush(stdin);
							printf("\nSemestre de %s modificado exitosamente",Respaldo->Nombre_de_la_Materia); _sleep(500);
						break;

					case 4://Creditos
					{
						ingresar_Creditos(&Respaldo->Creditos_de_la_Materia,5,2);
						printf("Creditos de %s modificados exitosamente",Respaldo->Nombre_de_la_Materia); _sleep(500);
						break;
					}
					default:
						if (opciones_de_Modificacion)
						{
							printf("\n\nEsta opcion no es valida\n");
							system("pause");break;
						}
				}
			}while (opciones_de_Modificacion);
			Respaldo = *materia;

		}
	}else{
		printf("\n\tNO HAY MATERIAS PARA MODIFICAR\n");
		system("pause");
	}
}

void Modificar_Curso(Cursos **curso)
{
	Cursos *Respaldo= *curso; int Elegido;
	char copia[10];
	if (*curso){
		Cursos *consulta=*curso, *temp=NULL;
		Ingresar_codigo_aux(&Elegido," Codigo del curso a modificar");
		while((Respaldo)&&(Respaldo->Codigo_del_curso != Elegido))
			Respaldo=Respaldo->prx;
		if (!Respaldo){
			printf("\n\tEl curso [%i] no se encuentra\n", Elegido);system("pause");
		}else{
			int opciones_de_Modificacion=0; 
			do
			{//Menu de Mantenimiento Cursos
				system("cls");
				printf("\t Que desea modificar?\n\n");
				printf(" 1- Anio del curso\n 2- Lapso del curso\n 0- SALIR\n\n ");
				scanf_s("%d",&opciones_de_Modificacion);
				switch(opciones_de_Modificacion)
				{
					case 1://Año
						fflush(stdin);
						Ingresar_codigo_aux(&Respaldo->AAAA,"Ingrese el nuevo anio");
						break;
					case 2://Lapso
						fflush(stdin);
						Ingresar_lapso(&Respaldo->lapso,3,1);
						break;

					default:
						if (opciones_de_Modificacion)
						{
							printf("\n\nEsta opcion no es valida\n");
							system("pause");break;
						}
			}
			}while (opciones_de_Modificacion);
			Respaldo = *curso;

		}
	}else{
		printf("\n\tNO HAY CURSOS PARA MODIFICAR\n");
		system("pause");
	}
}

void Ingresar_codigo( int *codigo,char De[15], Materias **q)
{
	char copia[10];
	int Numero_valido;
	do
	{
		printf("Codigo  %s:",De);
		gets_s(copia);
		Numero_valido=validar_numero(copia);
		*codigo=atoi(copia);
		int z;
			z= Existe_codigo(*codigo,q);
		if( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(z))
			printf("\n Este codigo no es valido (INGRESE OTRO)\n");
	}while ( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(Existe_codigo(*codigo,q)));
	fflush(stdin); 
	*codigo=atoi(copia);
}

void Ingresar_codigo_curso( int *codigo,char De[15], Cursos **q)
{
	char copia[10];
	int Numero_valido;
	do
	{
		printf("Codigo %s:",De);
		gets_s(copia);
		Numero_valido=validar_numero(copia);
		*codigo=atoi(copia);
		int z;
			z= Existe_codigo_curso(*codigo,q);
		if( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(z))
			printf("\n Este codigo no es valido (INGRESE OTRO)\n");
	}while ( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(Existe_codigo_curso(*codigo,q)));
	fflush(stdin); 
	*codigo=atoi(copia);
}

void Ingresar_codigo_aux( int *codigo,char De[20])
{
	char copia[10];
	int Numero_valido;
	do
	{
		system("cls");
		printf("%s:",De);
		fgets(copia,10,stdin);
		cambio(copia);
		Numero_valido=validar_numero(copia);
		*codigo=atoi(copia);
		if( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido)))
			printf("\n Este codigo no es valido (INGRESE OTRO)\n");
	}while ( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido)));
	fflush(stdin); 
	*codigo=atoi(copia);
}

void ingresar_Creditos(int *Rango,int max,int min)
{
	char copia[10];
	int Numero_valido;
	do{
		printf("\nIngrese las unidades de credito de la materia: ");
		fflush(stdin);
		gets_s(copia);
		Numero_valido=validar_numero(copia);
		*Rango=atoi(copia);
		if ((*Rango <min)||(*Rango >max))
			printf("\n El numero de creditos no esta en el ranco aceptado (%i,%i)\n por favor intente denuevo \n",min,max);
	}while ((*Rango<min)||(*Rango >max));
	fflush(stdin); 	
}

void Ingresar_lapso(int *Rango,int max,int min)
{
	char copia[10];
	int Numero_valido;
	do{
		printf("\nIngrese el lapso del curso: ");
		fflush(stdin);
		gets_s(copia);
		Numero_valido=validar_numero(copia);
		*Rango=atoi(copia);
		if ((*Rango <min)||(*Rango >max))
			printf("\n El lapso introducido es invalido (%i,%i)\n por favor intente denuevo \n",min,max);
	}while ((*Rango<min)||(*Rango >max));
	fflush(stdin); 	
}

int Existe_codigo(int codigo,Materias **En_Materias)
{
	if(*En_Materias){
		if((*En_Materias)->prx){
            Materias *aux=*En_Materias;
			while(aux){
				if(aux->Codigo_de_la_Materia == codigo)
					return 1;
				else
					aux=aux->prx;}
			return 0;	
 		}
		else{
			Materias *aux=*En_Materias;
			if(aux->Codigo_de_la_Materia == codigo)
				return 1;
			else
				return 0;
		}
	}
	else
		return 0;
}

int Existe_codigo_curso(int codigo,Cursos **En_Cursos)
{
	if(*En_Cursos){
		if((*En_Cursos)->prx){
            Cursos *aux=*En_Cursos;
			while(aux){
				if(aux->Codigo_del_curso == codigo)
					return 1;
				else
					aux=aux->prx;}
			return 0;	
 		}
		else{
			Cursos *aux=*En_Cursos;
			if(aux->Codigo_del_curso == codigo)
				return 1;
			else
				return 0;
		}
	}
	else
		return 0;
}

int Verificar_Semestre()
{// lee romanos devuelve entero
	char aux[5];
	do
	{
		printf("\nIngrese el semestre de la materia: ");
		fflush(stdin);
		fgets(aux,4,stdin);
		cambio(aux);
		if (aux[0]=='\0')printf("Por favor ingrese un semestre \n");
		if (((aux[0]=='I')||(aux[0]=='i'))&&(aux[1]=='\0')){ return 1;}
		if (((aux[0]=='I')||(aux[0]=='i'))&&((aux[1]=='I')||(aux[1]=='i'))&&(aux[2]=='\0')){ return 2;}
		if (((aux[0]=='I')||(aux[0]=='i'))&&((aux[1]=='I')||(aux[1]=='i'))&&((aux[2]=='I')||(aux[2]=='i'))&&(aux[3]=='\0')){ return 3;}
		if (((aux[0]=='I')||(aux[0]=='i'))&&((aux[1]=='V')||(aux[1]=='v'))&&(aux[2]=='\0')){ return 4;}
		if (((aux[0]=='V')||(aux[0]=='v'))&&(aux[1]=='\0')){ return 5;}
		if (((aux[0]=='V')||(aux[0]=='v'))&&((aux[1]=='I')||(aux[1]=='i'))&&(aux[2]=='\0')){ return 6;}
		if (((aux[0]=='V')||(aux[0]=='v'))&&((aux[1]=='I')||(aux[1]=='i'))&&((aux[2]=='I')||(aux[2]=='i'))&&(aux[3]=='\0')){ return 7;}
		if (((aux[0]=='V')||(aux[0]=='v'))&&((aux[1]=='I')||(aux[1]=='i'))&&((aux[2]=='I')||(aux[2]=='i'))&&((aux[3]=='I')||(aux[3]=='i'))&&(aux[4]=='\0')){ return 8;}
		if (((aux[0]=='I')||(aux[0]=='i'))&&((aux[1]=='X')||(aux[1]=='x'))&&(aux[2]=='\0')){ return 9;}
		if (((aux[0]=='X')||(aux[0]=='x'))&&(aux[1]=='\0')){return 10;}
		fflush(stdin);
	}while(true);
}

void imprimir_Romano(int Numero)
{// dado un numero lo imprime en romano

	switch (Numero) 
	{
		case 1: printf ("I"); break;
		case 2: printf ("II"); break;
		case 3: printf ("III"); break;
		case 4: printf ("IV"); break;
		case 5: printf ("V"); break;
		case 6: printf ("VI"); break;
		case 7: printf ("VII"); break;
		case 8: printf ("VIII"); break;
		case 9: printf ("IX"); break;
		case 10: printf ("X"); break;
		default: break;
	}
}

int validar_numero (char numero[])	
{/*Funcion que nos permite validar dado un string, saber si tiene solo numeros*/
	int i;
	for(i=0;i<strlen(numero);i++)
	{
		char letra=numero[i];
		if (isdigit(letra))
			continue;
		return 0;
	}
	return true;
}

void Consultar_materia(Materias *Las_materias)
{
	if(Las_materias){
	 Materias *consulta=Las_materias;
	 while(consulta)
	 { 
		printf(" -Materia[%d] \"%s\" %i (%i): %s \n\n",consulta->Codigo_de_la_Materia,consulta->Nombre_de_la_Materia,consulta->Semestre,consulta->Creditos_de_la_Materia,consulta->Descripcion_de_la_Materia);
		consulta=consulta->prx;
	 }
	 system("pause");
	}
	else
	{
		printf("No hay materias para consultar\n");system("pause");
	}
}

void Consultar_curso(Cursos *Los_cursos)
{
	if(Los_cursos){
	 Cursos *consulta=Los_cursos;
	 while(consulta)
	 { 
		printf("\n Curso [%d] (%i) (%i) (%i)\n\n",consulta->Codigo_del_curso,consulta->Codigo_de_la_Materia,consulta->AAAA,consulta->lapso);
		consulta=consulta->prx;
	 }
	 system("pause");
	}
	else
	{
		printf("No hay cursos para consultar\n");system("pause");
	}
}

void Eliminar_materia (Materias **Las_materias, Cursos **El_curso)
{
	char copia[10];
	int codigo_mat,cont=0;

	if (*Las_materias){
		Materias *consulta=*Las_materias, *temp=NULL;
		Ingresar_codigo_aux(&codigo_mat,"Codigo de materia a eliminar");
		if(*El_curso)
			Eliminar_curso_materia(El_curso,codigo_mat);
		if ((consulta->Codigo_de_la_Materia) == codigo_mat){
			temp = *Las_materias;
			*Las_materias = (*Las_materias)->prx;
			delete temp;
		}
		else{
			while(consulta->prx)
			{
				if (consulta->prx->Codigo_de_la_Materia == codigo_mat){
					temp = consulta->prx;
					consulta->prx = temp->prx;
					delete temp;
					cont +=1;
					printf("\n\tMATERIA ELIMINADA CORRECTAMENTE!\n"); system("pause");
				}
				else
					consulta = consulta->prx;

			}
			if(cont != 1)
			 printf("\n\tLa materia [%i] no se encuentra\n", codigo_mat);
		}
	}else{
		printf("\n\tNO HAY MATERIAS PARA ELIMINAR\n");
		system("pause");
	}
}

void Eliminar_curso (Cursos **Los_cursos)
{
	char copia[10];
	int codigo_mat,cont=0;

	if (*Los_cursos){
		Cursos *consulta=*Los_cursos, *temp=NULL;
		Ingresar_codigo_aux(&codigo_mat,"Codigo del curso a eliminar");
		if ((consulta->Codigo_del_curso) == codigo_mat){
			temp = *Los_cursos;
			*Los_cursos = (*Los_cursos)->prx;
			delete temp;
		}
		else{
			while(consulta->prx)
			{
				if (consulta->prx->Codigo_del_curso == codigo_mat){
					temp = consulta->prx;
					consulta->prx = temp->prx;
					delete temp;
					cont +=1;
					printf("\n\tCURSO ELIMINADO CORRECTAMENTE!\n"); system("pause");
				}
				else
					consulta = consulta->prx;

			}
			if(cont != 1)
			 printf("\n\tEl curso [%i] no se encuentra\n", codigo_mat);
		}
	}else{
		printf("\n\tNO HAY CURSOS PARA ELIMINAR\n");
		system("pause");
	}
}

void Eliminar_curso_materia (Cursos **Los_cursos, int codigo_mat)
{
	char copia[10];
	if (*Los_cursos){
		Cursos *consulta=*Los_cursos, *temp=NULL;
		if ((consulta->Codigo_de_la_Materia) == codigo_mat){
			temp = *Los_cursos;
			*Los_cursos = (*Los_cursos)->prx;
			delete temp;
		}
		else{
			while(consulta->prx)
			{
				if (consulta->prx->Codigo_de_la_Materia == codigo_mat){
					temp = consulta->prx;
					consulta->prx = temp->prx;
					delete temp;
				}
				else
					consulta = consulta->prx;

			}
		}
	}
}

void Limitar_Caracteres (char *copia, int max){
	int z=max;
	do{
		fflush(stdin);
		scanf_s (" %[^\n]s",&*copia);
		if (!(strlen(copia)>0)||!(strlen(copia)<=z)){
			printf(" LA CADENA DEBE SER MENOR A %i Y MAYOR A 0 CARACTERES \n", max);
			printf(" INGRESE DE NUEVO = ");
		}
	} while (!(strlen(copia)>0)||!(strlen(copia)<=z));
	printf  ("\n");
	fflush(stdin);
}	

void cambio(char c1[]){
	int i;
	for(i=0;i<strlen(c1);i++)
		if(c1[i] == '\n')
			c1[i] = '\0';
}