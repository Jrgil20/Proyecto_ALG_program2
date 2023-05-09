*
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
	char Semestre[4];// se debe restringir al rango de I a X
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

void Agregar_Materia(Materias **Nueva_materia);
void Ingresar_codigo( int *codigo,char De[15]);
void Ingresar_Semestre( char *Semestre[4]);
int Existe_codigo(int codigo,Materias **En_Materias);
int validar_numero (char numero[]);
void Modificar_Materia(Materias **materia);
void Consultar_materia(Materias *Las_materias);

int main ()
{
	Materias *Materia=NULL;
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
											printf("\n Materia [%d] \'%s\' %s (%i) : %s \n\n Agregada exitosamente \n",Materia->Codigo_de_la_Materia,Materia->Nombre_de_la_Materia,Materia->Semestre,Materia->Creditos_de_la_Materia,Materia->Descripcion_de_la_Materia);
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
										break;

									case 2://Modificar
										break;

									case 3://Consultar
										break;

									case 4://Eliminar
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
	Materias *Aux; Aux= new Materias; fflush(stdin);
	do
	{
		Ingresar_codigo(&Aux->Codigo_de_la_Materia,"de La Materia");
		/* verificar : que el codigo de la materia sea unico*/
		printf("\nIngrese el nombre de la materia: ");
		gets_s(Aux->Nombre_de_la_Materia);
		/* verificar : que el nombre solo tenga un maximo de 30 carcteres*/
		printf("\nIngrese la Descripcion de la materia: ");
		gets_s(Aux->Descripcion_de_la_Materia);
		/* verificar : que la descripcion tenga un maximo de 100 carcteres*/
		printf("\nIngrese el semestre de la materia: ");
		gets_s(Aux->Semestre);
		/* Ingresar_Semestre(&Aux->Semestre);*/
		printf("\nIngrese las unidades de credito de la materia: ");
		scanf_s("%d",&Aux->Creditos_de_la_Materia);
		/* verificar : que este en el rango {2..5}*/
		Aux->prx=*Nueva_materia;
		*Nueva_materia=Aux;
	}while(false);

}

void Modificar_Materia(Materias **materia)
{
	Materias *Respaldo; Respaldo= *materia; int Elegido;
	Ingresar_codigo(&Elegido," de La materia a modificar");
	while(*materia)
	{
		if (Elegido==(*materia)->Codigo_de_la_Materia)
			break;
		*materia=(*materia)->prx;
	}
	if (Elegido==(*materia)->Codigo_de_la_Materia)
	{
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
					printf("\t Ingrese el nuevo nombre: ");
					gets_s((*materia)->Nombre_de_la_Materia);
					fflush(stdin);
					/* verificar : que el nombre solo tenga un maximo de 30 carcteres*/
					break;
				}
				case 2://Descripcion
					break;

				case 3://Semestre
					break;

				case 4://Creditos
					break;

				default:
					if (opciones_de_Modificacion)
					{
						printf("\n\nEsta opcion no es valida\n");
						system("pause");break;
					}
			}
		}while (opciones_de_Modificacion);
		*materia=Respaldo;
	}
	else
		printf("\n no existe ninguna materia con ese codigo\n");
	system("pause");
}

void Ingresar_codigo( int *codigo,char De[15])
{
	char copia[10];
	int Numero_valido;
	do
	{
		printf("Codigo  %s:",De);
		gets_s(copia);
		Numero_valido=validar_numero(copia);
		*codigo=atoi(copia);
		if( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido)) )	
			printf("\n este codigo no es valido (INGRESE OTRO)\n");
	}while ( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido)) );
	fflush(stdin); 
	*codigo=atoi(copia);
}

int Existe_codigo(int codigo,Materias **En_Materias)
{
	return 0;
}

void Ingresar_Semestre( char *Semestre[4])
{
	char Aux[4];
	do 
	{	printf("\nIngrese el semestre de la materia: ");
		gets_s(Aux);
		
	}while( (Aux != "I")&&(Aux!="II")&&(Aux!="III")&&(Aux != "V")&&(Aux!="V")&&(Aux != "VI")&&(Aux!="VII")&&(Aux!="VIII")&&(Aux != "IX")&&(Aux!="X"));
	*Semestre=Aux;
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
	Materias *consulta=Las_materias;
	while(consulta)
	{
		printf(" -Materia[%d] \"%s\" %s (%i): %s \n\n",consulta->Codigo_de_la_Materia,consulta->Nombre_de_la_Materia,consulta->Semestre,consulta->Creditos_de_la_Materia,consulta->Descripcion_de_la_Materia);
		consulta=consulta->prx;
	}
	system("pause");
}
