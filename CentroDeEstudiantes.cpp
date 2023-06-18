/*Gabriel Castellano C.I:28059781,Jesus Gil C.I:30175126,Andres Guilarte C.I:30246084*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*estructuras y tipos secundarios*/
typedef int year;	typedef int month;	typedef int day; typedef  int Codigo_curso; typedef int Codigo_Materia; const int maxEntero=1294967295;

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
	Codigo_Materia Codigo_de_la_Materia;//no se puede repetir
	char Nombre_de_la_Materia[30];//no debe estar vacio
	char Descripcion_de_la_Materia[100];//no debe estar vacio
	int Semestre;// se debe restringir al rango de 1 a 10
	char SemestreEnRomano[5];// se debe restringir al rango de I a X
	int Creditos_de_la_Materia;// se debe restringir al rango de 2 a 5
	Materias *prx;
};

struct Cursos
{/*Cuando se elimina un curso, deben borrarse todas sus referencias en el sistema.*/
	Codigo_curso Codigo_del_curso;/*Para registrar un curso deben preexistir la materia */
	Codigo_Materia Codigo_de_la_Materia; //debe existir previamente
	year AAAA;//se restringe de 1900 a 2100
	int lapso;// se debe restringir al rango de 1 a 3
	Cursos *prx;
};

struct Personas
{/*Si se elimina una persona en el sistema deben eliminarse todas sus referencias en el sistema.*/
	long int cedula;// restricion: no se puede modificar
	char nombre_apellido[30];
	fecha Fecha_de_Nacimiento;
	char direccion[40];
	Participacion *Record;	
	Personas *prx;
};

/*Rutinas*/
void Encabezado (char Menu[]);
int Verificar_Semestre();
void Semestre_Romano(int,Materias**);
void Agregar_Materia(Materias**);
void insertar_MateriaOrdenadamente(Materias**,Materias**);
void Agregar_Curso(Cursos**,Materias**);
void insertar_CursoOrdenadamente(Cursos**,Cursos**);
void Agregar_Persona(Personas**);
void insertar_PersonaOrdenadamente(Personas**,Personas**);
int DentrodeRango(int*,int,int);
void ingresarDato(int*,char De[20],int,int);
void Ingresar_codigo(int*,char De[15], Materias**);
void Ingresar_codigo_curso(int*,char De[15],Cursos**);
void Ingresar_cedula(long int*,char De[15],Personas**);
void Ingresar_Fecha(year*,month*,day *);
int Existe_codigo(int,Materias**);
int Existe_codigo_curso(int,Cursos**);
int Existe_cedula(long int,Personas**);
int validar_numero (char numero[]);
void Modificar_Materia(Materias**);
void Modificar_Curso(Cursos**);
void Modificar_Persona(Personas**);
void Consultar_materia(Materias*);
void Consultar_curso(Cursos*);
void Consultar_Personas(Personas*);
void Eliminar_curso_materia (Cursos**,int);
void Eliminar_materia (Materias**,Cursos **);
void Eliminar_curso (Cursos**);
void Eliminar_persona(Personas**);
void Agregar_nota(Personas **, int,int);
void Agregar_Curso_persona(Personas *,Cursos *,Materias *);
int Regresa_cod_mat(Cursos *, int x);
int Inscribe_o_no(Cursos *, Participacion *);
void C_NombreMateria(Materias* ,Cursos* );
void c_Materia(Materias*,Cursos*,Personas*);
void c_CursosDe(Materias*,Cursos*,Personas*);
void C_NombreAlumno(Personas*);
void C_Aprobados(Personas*,Cursos*);
void C_Cursos(Materias* ,Cursos*,Personas*);
void C_CursosPeriodo(Cursos*,Personas*);
void C_Alumno(Personas*);
int isdigit(char);
int bisiesto (year);
int LimitarCaracteres (char*,int);
int compararCadenas(char*,char*);
void cambio(char c1[]);
int verificarRuta(char);
void HM();
void HC();
void HP();
void FormatoFecha(fecha);
void FormatoMateria(Materias*);
void FormatoCurso(Cursos*);
void FormatoPersona(Personas*,int);
void calificaciones(Participacion* calificacion);
int Exportar_Materias(Materias*,char ruta[]);
int Exportar_Cursos(Cursos*,char ruta[]);
int Exportar_Personas(Personas*,char ruta[]);
int Importar_Materias(Materias**,char ruta[]);
int Importar_Cursos(Cursos**,Materias*,char ruta[]);
int Importar_Personas(Personas**,char ruta[]);

int main ()
{
	Materias *Materia=NULL;Cursos *Curso =NULL;Personas *Persona=NULL;
	 char Ruta[150]=""; char Nuevaruta[4]; char UbicacionMenu[80]="MENU PRINCIPAL";

	printf("\n\tDesea cambiar la ruta de los ficheros?");
	fgets(Nuevaruta,4,stdin);cambio(Nuevaruta);fflush(stdin);
	if (Nuevaruta[0]=='Y'||Nuevaruta[0]=='y'||Nuevaruta[0]=='S'||Nuevaruta[0]=='s')
	{
		do{
			printf("\nIngrese la Nueva ruta (disco:/carpeta/): ");
			fgets(Ruta,130,stdin);cambio(Ruta);fflush(stdin);
			if (!strcmp(Ruta,""))printf("\nDebe haber una ruta Y ");
			if (validar_numero(Ruta))printf("\tla ruta no debe ser numerica\n");
		}while(!strcmp(Ruta,"")||validar_numero(Ruta));
	}

	if (Importar_Materias(&Materia,Ruta));else {printf("no se pudo importar el archivo de Materias\n");system("pause");}
	if (Importar_Cursos(&Curso,Materia,Ruta));else {printf("no se pudo importar el archivo de cursos\n");system("pause");}
	if (Importar_Personas(&Persona,Ruta));else {printf("no se pudo importar el archivo de personas\n");system("pause");}

	char opciones[3];
	opciones[0]='0'; 
	do
	{//Menu
		system("cls");
		Encabezado(UbicacionMenu);
		printf("Ruta = %s \n", UbicacionMenu);
		printf("\n 1- MANTENIMIENTO\n 2- CONTROL DE ESTUDIOS\n 3- CONSULTAS\n\n 0- SALIR\n\n Escriba su opcion (0-3) = ");
		fflush(stdin);fgets(opciones,2,stdin);cambio(opciones);fflush(stdin);
		switch(opciones[0])
		{
			case '1'://Mantenimiento del sistema
			{
				char opciones_mantenimiento[3];
				opciones_mantenimiento[0]='0';  
				do
				{//Menu de Mantenimiento del sistema
					system("cls");
					Encabezado("MENU DE MANTENIMIENTO");char UbicacionMenu[80]="MENU PRINCIPAL/";strcat(UbicacionMenu, "MANTENIMIENTO/");
					printf("Ruta = %s \n", UbicacionMenu);
					printf("\n 1- Materias\n 2- Cursos\n 3- Personas\n\n 0- SALIR\n\n Escriba su opcion (0-3) = ");
					fflush(stdin);fgets(opciones_mantenimiento,2,stdin);cambio(opciones_mantenimiento);fflush(stdin);
					switch(opciones_mantenimiento[0])
					{
						case '1':
						{
							char opciones_mantenimiento_Materia[3];
							opciones_mantenimiento_Materia[0]='0';  
							do
							{//Menu de Mantenimiento Materias
								system("cls");
								Encabezado("MENU DE MANTENIMIENTO DE MATERIAS");char UbicacionMenu[80]="MENU PRINCIPAL/"; strcat(UbicacionMenu, "MANTENIMIENTO/MATERIAS");
								printf("Ruta = %s \n", UbicacionMenu);
								printf("\n 1- Agregar\n 2- Modificar\n 3- Consultar\n 4- Eliminar\n\n 0- SALIR\n\n Escriba su opcion (0-4) = ");
								fflush(stdin);fgets(opciones_mantenimiento_Materia,2,stdin);cambio(opciones_mantenimiento_Materia);fflush(stdin);
								switch(opciones_mantenimiento_Materia[0])
									{
										case '1'://Agregar Materia	
											Agregar_Materia(&Materia); break;

										case '2'://Modificar
											Modificar_Materia(&Materia);break;
										
										case '3'://Consultar
											Consultar_materia(Materia);break;
										
										case '4'://Eliminar
											Eliminar_materia(&Materia,&Curso);break;

										default:
											if (opciones_mantenimiento_Materia[0]!='0')
											{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
									}
							}while (opciones_mantenimiento_Materia[0]!='0');
							if (Exportar_Materias(Materia,Ruta));
							else printf("\t se genero un error al exportar las materias, no se guardo en memoria secundaria\n");
							break;
						}
						case '2':
						{
							char opciones_mantenimiento_Cursos[3];
							opciones_mantenimiento_Cursos[0]='0';  
							do
							{//Menu de Mantenimiento Cursos
								system("cls");
								Encabezado("MENU DE MANTENIMIENTO DE CURSOS");char UbicacionMenu[80]="MENU PRINCIPAL/"; strcat(UbicacionMenu, "MANTENIMIENTO/CURSOS");
								printf("Ruta = %s \n", UbicacionMenu);
								printf("\n 1- Agregar\n 2- Modificar\n 3- Consultar\n 4- Eliminar\n\n 0- SALIR\n\n Escriba su opcion (0-4) = ");
								fflush(stdin);fgets(opciones_mantenimiento_Cursos,2,stdin);cambio(opciones_mantenimiento_Cursos);fflush(stdin);
								switch(opciones_mantenimiento_Cursos[0])
								{
									case '1'://Agregar
										Agregar_Curso(&Curso,&Materia);break;

									case '2'://Modificar
										Modificar_Curso(&Curso);break;

									case '3'://Consultar
										Consultar_curso(Curso);break;

									case '4'://Eliminar
										Eliminar_curso(&Curso);break;

									default:
										if (opciones_mantenimiento_Cursos[0]!='0')
										{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
								}
							}while (opciones_mantenimiento_Cursos[0]!='0');
							if (Exportar_Cursos(Curso,Ruta));
							else printf("\t se genero un error al exportar los cursos, no se guardo en memoria secundaria\n");
							break;
						}
						case '3':
						{
							char opciones_mantenimiento_Personas[3];
							opciones_mantenimiento_Personas[0]='0'; 
							do
							{//Menu de Mantenimiento Personas
								system("cls");
								Encabezado("MENU MANTENIMIENTO DE PERSONAS");char UbicacionMenu[80]="MENU PRINCIPAL/"; strcat(UbicacionMenu, "MANTENIMIENTO/PERSONAS");
								printf("Ruta = %s \n", UbicacionMenu);
								printf("\n 1- Agregar\n 2- Modificar\n 3- Consultar\n 4- Eliminar\n\n 0- SALIR\n\n Escriba su opcion (0-4) = ");
								fflush(stdin);fgets(opciones_mantenimiento_Personas,2,stdin);cambio(opciones_mantenimiento_Personas);fflush(stdin);
								switch(opciones_mantenimiento_Personas[0])
								{
									case '1'://Agregar
										Agregar_Persona(&Persona);
										break;

									case '2'://Modificar
										Modificar_Persona(&Persona);
										break;

									case '3'://Consultar
										Consultar_Personas(Persona);
										break;

									case '4':
										Eliminar_persona(&Persona);
										break;

									default:
										if (opciones_mantenimiento_Personas[0]!='0')
										{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
								}
							}while (opciones_mantenimiento_Personas[0]!='0');
							if (Exportar_Personas(Persona,Ruta));
							else printf("\t se genero un error al exportar las personas, no se guardo en memoria secundaria\n");
							break;
						}	
						default:
							if (opciones_mantenimiento[0]!='0')
							{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
						}
					}while (opciones_mantenimiento[0]!='0');
					break;
				}

			case '2':
			{
				char opciones_control_estudios[3]; 
				opciones_control_estudios[0]='0';
				do
				{//Menu Control de Estudios
					system("cls");
					Encabezado("MENU CONTROL DE ESTUDIOS");char UbicacionMenu[80]="MENU PRINCIPAL/"; strcat(UbicacionMenu, "CONTROL DE ESTUDIOS/");
					printf("Ruta = %s \n", UbicacionMenu);
					printf(" 1- Agregar alumnos \n 2- *Modificar alumnos \n 3- *Eliminar alumnos\n\n 0- SALIR\n\n Escriba su opcion (0-3) =  ");
					fflush(stdin);fgets(opciones_control_estudios,2,stdin);cambio(opciones_control_estudios);fflush(stdin);
					switch(opciones_control_estudios[0])
					{
						case '1'://Agregar alumnos
							Agregar_Curso_persona(Persona,Curso,Materia);
							break;

						case '2'://Modificar alumnos
							break;

						case '3'://eliminar alumnos en cursos con sus notas correspondientes.
							break;

						default:
							if (opciones_control_estudios[0]!='0')
							{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
					}
					if (Exportar_Personas(Persona,Ruta));
					else 
						printf("\t se genero un error al exportar las personas, no se guardo en memoria secundaria\n");
					
				}while (opciones_control_estudios[0]!='0');
				break;
		}

			case '3':
			{
				char opciones_consultas[3];
				opciones_consultas[0]='0';
				do
				{//Menu Reportes
					system("cls");
					Encabezado("MENU DE REPORTES");char UbicacionMenu[80]="MENU PRINCIPAL/"; strcat(UbicacionMenu, "REPORTES/");
					printf("Ruta = %s \n", UbicacionMenu);
					printf(" \n\n 1-Buscar codigos por nombre\n 2-Buscar cedula por nombre\n 3-cursos de cierto a%co y lapso\n 4-Datos de Materia \n 5-Todos los cursos \n 6-Alumnos aprobados en una materia \n 7-Cursos de un periodo \n 8-Notas por cedula\n 0- SALIR\n\n  ",164);
					fflush(stdin);fgets(opciones_consultas,2,stdin);cambio(opciones_consultas);fflush(stdin);
					switch(opciones_consultas[0])
					{
						case '1'://Dado un nombre de curso(materia ya que los cursos no tienen nombre) buscar su c�digo.
							printf("\n\tDado un nombre de materia buscar sus codigos asociados\n\n");
							C_NombreMateria(Materia,Curso);
							break;

						case '2'://Dado un nombre de alumno buscar su(s) c�dula(s) asociada(s) y dem�s datos (sin�nimos para ubicar la c�dula que nos interesa).
							printf("\n\tDado un nombre Buscar Cedulas asociadas\n\n");
							C_NombreAlumno(Persona);
							break;

						case '3'://Dado un anyo y un lapso ubicar todos los cursos dictados ( nombre de curso, materia, cantidad de alumnos aprobados y reprobados)
							printf("\n\tDado un a%co(AAAA) y lapso mostrar cursos \n\n",164);
							c_CursosDe(Materia,Curso,Persona);
							break;

						case '4': //Dado un codigo de materia mostrar todos los cursos que la han dictado (nombre de curso, materia, cantidad de alumnos aprobados y reprobados)
							printf("\n\tDada una materia se muestran todos sus datos relacionados \n\n");
							c_Materia(Materia,Curso,Persona);
							break;

						case '5'://Dado un codigo de curso mostrar todos los datos del mismo con la materia y los alumnos con sus notas
							printf("\n\tTodos los cursos con Materia, Personas y notas \n\n");			
							C_Cursos(Materia,Curso,Persona);
							break;

						case '6'://Dada una materia ( codigo ) mostrar los alumnos que la han aprobado (cedula, apellido y nombre con su nota )
							printf("\n\tDada Materia mostrar alumnos aprobados \n\n");
							C_Aprobados(Persona,Curso);
							system("Pause");
							break;

						case '7'://Todos los cursos (con sus alumnos y notas) dictados en un periodo dado.
							printf("\n\ttTodos los cursos De un periodo Con Personas y notas \n\n");
							C_CursosPeriodo(Curso,Persona);
							break;

						case '8'://Dada una cedula mostrar todos los cursos con sus notas tomadas por esa persona
							printf("\n\tDada una cedula mostrar Datos con cursos y notas \n\n");
							C_Alumno(Persona);
							break;

						default:
							if (opciones_consultas[0]!='0')
								{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
					}
				}while (opciones_consultas[0]!='0');
				break;
			}

			default:
				if (opciones[0]!='0')
					{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
		}
	}while (opciones[0]!='0');
	system("pause");
	return 0;
}

void Encabezado (char Menu[40])
{printf ("\n\t %s\n\n", Menu);}

void Agregar_Materia(Materias **Lista_materia)
{/*Crea un nodo llamado aux y lo ingresa en la lista de materias*/
	Materias *Aux= new Materias; fflush(stdin);
	Ingresar_codigo(&Aux->Codigo_de_la_Materia,"de la materia",Lista_materia);
	do{
		printf("\nIngrese el nombre de la materia: ");fflush(stdin);
		fgets(Aux->Nombre_de_la_Materia,30,stdin);cambio(Aux->Nombre_de_la_Materia);fflush(stdin);
		if (!strcmp(Aux->Nombre_de_la_Materia,""))
			printf("\nLa materia debe tener un nombre ");
		else
			if (validar_numero(Aux->Nombre_de_la_Materia))
				printf("\tAdvertencia: El nombre de la materia es Numerico\n");
	}while(!strcmp(Aux->Nombre_de_la_Materia,""));
	do{
		printf("\nIngrese la Descripcion de la materia: ");
		fgets(Aux->Descripcion_de_la_Materia,100,stdin);cambio(Aux->Descripcion_de_la_Materia);fflush(stdin);
		if (!strcmp(Aux->Descripcion_de_la_Materia,""))
			printf("\nDebe haber una descripcion ");
		else
			if (validar_numero(Aux->Descripcion_de_la_Materia))
				printf("\tAdvertencia: la descripcion de la materia es Numerica\n");
	}while(!strcmp(Aux->Descripcion_de_la_Materia,""));
	Aux->Semestre=Verificar_Semestre();
	Semestre_Romano(Aux->Semestre,&Aux);fflush(stdin);
	ingresarDato(&Aux->Creditos_de_la_Materia,"Creditos de la materia",5,2);
	insertar_MateriaOrdenadamente( Lista_materia, &Aux);
	printf("\n  Se agrego a : \n");HM();FormatoMateria(Aux);system("Pause");
}

void insertar_MateriaOrdenadamente( Materias **lista, Materias **Nuevo_nodo)
{/*Inserta el nodo materia de manera ordenada en la lista ordenada*/
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

void Agregar_Curso(Cursos **c,Materias **Materia)
{/*Dado un codigo de materia  permite Ingresar un curso*/
	Cursos *Aux=*c;int cod;
	if(*Materia)
	{/*si existen materias procede a generar*/
		ingresarDato(&cod,"Codigo de la materia",maxEntero,1);
		if(Existe_codigo(cod,Materia))
		{
			Cursos *Aux= new Cursos;printf("\n");
			Aux->Codigo_de_la_Materia = cod;
			Ingresar_codigo_curso(&Aux->Codigo_del_curso,"del Curso", c);printf("\n");
			ingresarDato(&Aux->AAAA,"anio del curso",2100,1900);printf("\n");
			ingresarDato(&Aux->lapso,"lapso del curso",3,1);
			insertar_CursoOrdenadamente(c,&Aux);
			printf("\n  Se agrego a : \n");HC();FormatoCurso(Aux);system("Pause");
		}else
			{printf("La materia no existe, por lo que no se creara el curso\n");system("Pause");}
	}else
		{printf("No existen materias, por lo que no se pueden crear cursos\n");system("Pause");}
}

void insertar_CursoOrdenadamente( Cursos **lista, Cursos **Nuevo_nodo)
{/*Inserta el nodo materia de manera ordenada en la lista ordenada*/
	if (*lista==NULL || (*Nuevo_nodo)->lapso<(*lista)->lapso)//mientras el nuevo nodo sea la nueva cabeza
	{
		(*Nuevo_nodo)->prx = *lista;//apunta a lo que apuntaba p
		*lista = *Nuevo_nodo;//hace el nuevo nodo cabeza
	}else
	{
		Cursos *aux=*lista;//crea un auxiliar
		while(aux->prx && aux->prx->lapso <= (*Nuevo_nodo)->lapso)
			aux=aux->prx;// este avanza hasta encontrar la posicion
		(*Nuevo_nodo)->prx=aux->prx;//enlazamos el nodo a lo que apunta e auxiliar
		aux->prx=*Nuevo_nodo; //enlazamos el auxiliar al nuevo nodo
	}
}

void Agregar_Persona(Personas **Nueva_persona)
{
	Personas *aux=new Personas;
	Ingresar_cedula(&aux->cedula,"del estudiante",Nueva_persona);
	do{
		printf("\n Ingrese nombre y apellido de la persona: ");
		fflush(stdin);fgets(aux->nombre_apellido,40,stdin);cambio(aux->nombre_apellido);fflush(stdin);
		if (!strcmp(aux->nombre_apellido,""))
			printf("\nLa Persona debe tener un nombre ");
		else
			if (validar_numero(aux->nombre_apellido))
				printf("\t El nombre de la Persona es Numerico\n");
	}while(!strcmp(aux->nombre_apellido,"")||validar_numero(aux->nombre_apellido));
	Ingresar_Fecha(&aux->Fecha_de_Nacimiento.yyyy,&aux->Fecha_de_Nacimiento.mm,&aux->Fecha_de_Nacimiento.dd);
	do{
		printf("\n Ingrese la direccion: ");
		fflush(stdin);fgets(aux->direccion,40,stdin);cambio(aux->direccion);fflush(stdin);
		if (!strcmp(aux->direccion,""))
			printf("\nLa direccion debe tener un nombre ");
		else
			if (validar_numero(aux->direccion))
				printf("advertencia: la direcion es Numerica\n");
	}while(!strcmp(aux->direccion,""));
	aux->Record = NULL;
	insertar_PersonaOrdenadamente(Nueva_persona,&aux);
	printf("\n  Se agrego a : \n");HP();FormatoPersona(aux,false);system("Pause");
}

void insertar_PersonaOrdenadamente( Personas **lista, Personas **Nuevo_nodo)
{
	if (*lista==NULL || (*Nuevo_nodo)->cedula<(*lista)->cedula)//mientras el nuevo nodo sea la nueva cabeza
	{
		(*Nuevo_nodo)->prx = *lista;//apunta a lo que apuntaba p
		*lista = *Nuevo_nodo;//hace el nuevo nodo cabeza
	}else
	{
		Personas *aux=*lista;//crea un auxiliar
		while(aux->prx && aux->prx->cedula <= (*Nuevo_nodo)->cedula)
			aux=aux->prx;// este avanza hasta encontrar la posicion
		(*Nuevo_nodo)->prx=aux->prx;//enlazamos el nodo a lo que apunta e auxiliar
		aux->prx=*Nuevo_nodo; //enlazamos el auxiliar al nuevo nodo
	}
}

void Modificar_Materia(Materias **materia)
{/*Verificar*/
	Materias *Respaldo= *materia; int Elegido;
	if (*materia)
	{
		Materias *consulta=*materia, *temp=NULL;
		ingresarDato(&Elegido," Codigo de La materia a modificar",maxEntero,1);
		while((Respaldo)&&(Respaldo->Codigo_de_la_Materia != Elegido))
			Respaldo=Respaldo->prx;
		if (!Respaldo)
		{printf("\n\tLa materia [%i] no se encuentra\n", Elegido);system("pause");}
		else
		{
			char opciones_de_Modificacion[3];
			opciones_de_Modificacion[0]=0;	
			do
			{//Menu de Mantenimiento Cursos
				system("cls");printf("\t Que desea modificar?\n\n");
				printf(" 1- Nombre de la materia\n 2- Descripcion de la materia\n 3- Semestre de la materia\n 4- Creditos de la materia\n\n 0- SALIR\n\n Escriba su opcion (0-4) =  ");
				fflush(stdin);fgets(opciones_de_Modificacion,2,stdin);cambio(opciones_de_Modificacion);fflush(stdin);
				switch(opciones_de_Modificacion[0])
				{
					case '1'://Nombre
						do{
							printf("\nIngrese el nuevo nombre de la materia: ");fflush(stdin);
							fflush(stdin);fgets(Respaldo->Nombre_de_la_Materia,30,stdin);cambio(Respaldo->Nombre_de_la_Materia);fflush(stdin);
							if (!strcmp(Respaldo->Nombre_de_la_Materia,""))
								printf("\nLa materia debe tener un nombre ");
							else
								if (validar_numero(Respaldo->Nombre_de_la_Materia))
									printf("\tAdvertencia: El nombre de la materia es Numerico\n");
						}while(!strcmp(Respaldo->Nombre_de_la_Materia,""));						
						printf("\nNombre de [%s] modificado  ",Respaldo->Nombre_de_la_Materia);system("Pause");
						break;
					
					case '2'://Descripcion
						do{
							printf("\nIngrese la nueva Descripcion de la materia: ");
							fflush(stdin);fgets(Respaldo->Descripcion_de_la_Materia,100,stdin);cambio(Respaldo->Descripcion_de_la_Materia);fflush(stdin);fflush(stdin);
							if (!strcmp(Respaldo->Descripcion_de_la_Materia,""))
								printf("\nDebe haber una descripcion ");
							else
								if (validar_numero(Respaldo->Descripcion_de_la_Materia))
									printf("\tAdvertencia: la descripcion de la materia es Numerica\n");
						}while(!strcmp(Respaldo->Descripcion_de_la_Materia,""));
						printf("\nDescripcion de [%s] modificado a [%s]  ",Respaldo->Nombre_de_la_Materia,Respaldo->Descripcion_de_la_Materia);system("Pause");
						break;

					case '3'://Semestre
						Respaldo->Semestre=Verificar_Semestre();fflush(stdin);
						Semestre_Romano(Respaldo->Semestre,&Respaldo);fflush(stdin);
						printf("\nSemestre de [%s] modificado a [%s]  ",Respaldo->Nombre_de_la_Materia,Respaldo->SemestreEnRomano);system("Pause");
						break;

					case '4'://Creditos
						ingresarDato(&Respaldo->Creditos_de_la_Materia,"ingrese los creditos ",5,2);
						printf("Creditos de [%s] modificados a [%i]  ",Respaldo->Nombre_de_la_Materia, Respaldo->Creditos_de_la_Materia);system("Pause");
						break;
					
					default:
						if (opciones_de_Modificacion[0]!='0')
							{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
				}
			}while (opciones_de_Modificacion[0]!='0');
			Respaldo = *materia;
		}
	}else
	 {printf("\n\tNO HAY MATERIAS PARA MODIFICAR\n");system("pause");}
}

void Modificar_Curso(Cursos **curso)
{
	Cursos *Respaldo= *curso; int Elegido;
	if (*curso)
	{
		Cursos *consulta=*curso, *temp=NULL;
		ingresarDato(&Elegido," Codigo del curso a modificar",maxEntero,1);
		while((Respaldo)&&(Respaldo->Codigo_del_curso != Elegido))
			Respaldo=Respaldo->prx;
		if (!Respaldo)
		{printf("\n\tEl curso [%i] no se encuentra\n", Elegido);system("pause");}
		else
		{
			char opciones_de_Modificacion[3];
			opciones_de_Modificacion[0]=0;	
			do{//Menu de Mantenimiento Cursos
				system("cls");
				printf("\t Que desea modificar?\n\n");
				printf(" 1- Anio del curso\n 2- Lapso del curso\n 0- SALIR\n\n Escriba su opcion (0-2) = ");
				fflush(stdin);fgets(opciones_de_Modificacion,2,stdin);cambio(opciones_de_Modificacion);fflush(stdin);
				switch(opciones_de_Modificacion[0])
				{
					case '1'://Anio
						ingresarDato(&Respaldo->AAAA,"Ingrese el nuevo anio",maxEntero,1);
						printf("Se modifico el anio de %i  ",Respaldo->Codigo_del_curso);
						system("Pause");
						break;

					case '2'://Lapso
						ingresarDato(&Respaldo->lapso, "Lapso",3,1);
						printf("Se modifico el lapso de %i  ",Respaldo->Codigo_del_curso);
						system("Pause");
						break;
					
					default:
						if (opciones_de_Modificacion[0]!='0')
							{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
				}
			}while (opciones_de_Modificacion[0]!='0');
			Respaldo = *curso;
		}
	}else
	{printf("\n\tNO HAY CURSOS PARA MODIFICAR\n");system("pause");}
}

void Modificar_Persona(Personas **persona)
{
	Personas *Respaldo= *persona; int Elegido;
	if (*persona)
	{
		Personas *consulta=*persona, *temp=NULL;
		ingresarDato(&Elegido," Cedula del estdiante a modificar",maxEntero,1);
		while((Respaldo)&&(Respaldo->cedula != Elegido))
			Respaldo=Respaldo->prx;
		if (!Respaldo)
			{printf("\n\tEl estudiante de cedula [%i] no se encuentra\n", Elegido);system("pause");}
		else
		{
			char opciones_de_Modificacion[3];
			opciones_de_Modificacion[0]=0;	
			do{//Menu de Mantenimiento Cursos
				system("cls");
				printf("\t Que desea modificar?\n\n");
				printf(" 1- Nombre y apellido\n 2- Fecha de nacimiento\n 3- Direccion\n 0- SALIR\n\n Escriba su opcion (0-3) = ");
				fflush(stdin);fgets(opciones_de_Modificacion,2,stdin);cambio(opciones_de_Modificacion);fflush(stdin);
				switch(opciones_de_Modificacion[0])
				{
					case '1'://Nombre y apellido
						do{
							printf("\n Ingrese el nuevo nombre nombre y apellido de la persona: ");
							fflush(stdin);fgets(Respaldo->nombre_apellido,40,stdin);cambio(Respaldo->nombre_apellido);fflush(stdin);
							if (!strcmp(Respaldo->nombre_apellido,""))
								printf("\nLa Persona debe tener un nombre ");
							else
								if (validar_numero(Respaldo->nombre_apellido))
									printf("\t El nombre de la Persona es Numerico\n");
						}while(!strcmp(Respaldo->nombre_apellido,"")||validar_numero(Respaldo->nombre_apellido));
						printf("\nNombre de [%i] modificado a [%s]  ",Respaldo->cedula, Respaldo->nombre_apellido);system("Pause");
						fflush(stdin);
						break;

					case '2'://Fecha de nacimiento
						Ingresar_Fecha(&Respaldo->Fecha_de_Nacimiento.yyyy,&Respaldo->Fecha_de_Nacimiento.mm,&Respaldo->Fecha_de_Nacimiento.dd);
						printf("\nFecha de nacimiento de [%i] modificado  ",Respaldo->cedula);system("Pause");
						break;

					case '3'://Direccion
						do{
							printf("\nIngrese la nueva direccion: ");
							fflush(stdin);fgets(Respaldo->direccion,40,stdin);cambio(Respaldo->direccion);fflush(stdin);
							if (!strcmp(Respaldo->direccion,""))
								printf("\nLa direccion debe tener un nombre ");
							else
								if (validar_numero(Respaldo->direccion))
									printf("advertencia: la direcion es Numerica\n");
						}while(!strcmp(Respaldo->direccion,""));
						printf("\nDireccion de [%i] modificado a [%s]  ",Respaldo->cedula, Respaldo->direccion);system("Pause");
						break;

					default:
						if (opciones_de_Modificacion[0]!='0')
							{printf("\n\nEsta opcion no es valida\n");system("pause");break;}
				}
			}while (opciones_de_Modificacion[0]!='0');
			Respaldo = *persona;
		}
	}else
		{printf("\n\tNO HAY PERSONAS PARA MODIFICAR\n");system("pause");}
}

void Ingresar_codigo( int *codigo,char De[15], Materias **q)
{
	char copia[10];int Numero_valido;
	do
	{
		printf("Codigo  %s:",De);fflush(stdin);
		gets_s(copia);fflush(stdin); 
		Numero_valido=validar_numero(copia);
		*codigo=atoi(copia);
		int z= Existe_codigo(*codigo,q);
		if( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(z))
			printf("\n Este codigo no es valido (INGRESE OTRO)\n");
	}while ( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(Existe_codigo(*codigo,q)));
	*codigo=atoi(copia);
}

void Ingresar_codigo_curso( int *codigo,char De[15], Cursos **q)
{
	char copia[10];int Numero_valido;
	do
	{
		printf("Codigo %s:",De);
		fflush(stdin);gets_s(copia);fflush(stdin); 
		Numero_valido=validar_numero(copia);
		*codigo=atoi(copia);
		int z= Existe_codigo_curso(*codigo,q);
		if( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(z))
			printf("\n Este codigo no es valido (INGRESE OTRO)\n");
	}while ( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(Existe_codigo_curso(*codigo,q)));
	*codigo=atoi(copia);
}

void Ingresar_cedula( long int *codigo,char De[15], Personas **q)
{
	char copia[10];int Numero_valido;
	do
	{
		printf("Cedula %s:",De);
		fflush(stdin);gets_s(copia);fflush(stdin); 
		Numero_valido=validar_numero(copia);
		*codigo=atol(copia);
		int z= Existe_cedula(*codigo,q);
		if( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(z))
			printf("\n Esta cedula no es valida (INGRESE OTRO)\n");
	}while ( (*codigo>=maxEntero) || (*codigo<=0) || (!(Numero_valido))||(Existe_cedula(*codigo,q)));
	*codigo=atol(copia);
}

int DentrodeRango(int *Valor,int mayor,int menor)
{
	if (*Valor>mayor||*Valor<menor)
		return 0;
	else 
		return 1;
}

void ingresarDato(int *Dato,char De[20],int vMax,int vmin)
{
	char copia[10];int Numero_valido;
	do
	{
		printf("\n%s:",De);fflush(stdin); 
		fgets(copia,10,stdin);cambio(copia);fflush(stdin); 
		Numero_valido=validar_numero(copia);
		*Dato=atoi(copia);
		if( !DentrodeRango(Dato,vMax,vmin)|| (!(Numero_valido)))
			{
				printf("\n Este dato no es valido (INGRESE OTRO)");
				if (!DentrodeRango(Dato,vMax,vmin))
					printf("\n No esta dentro del rango(%i,%i)",vmin,vMax);
			}
	}while ( !DentrodeRango(Dato,vMax,vmin) || (!(Numero_valido)));
	*Dato=atoi(copia);
}

void Ingresar_Fecha(year *YY,month *MM,day *dd)
{
	ingresarDato(YY," anio de nacimiento",2100,1900);
	ingresarDato(MM," mes de nacimiento",12,1);
	if(*MM==2)
		if (bisiesto(*YY))
			ingresarDato(dd," Dia de nacimiento",29,1);
		else
			ingresarDato(dd," Dia de nacimiento",28,1);
	else 
		if (*MM==4||*MM==6||*MM==9||*MM==11)
			ingresarDato(dd," Dia de nacimiento",30,1);
		else
			ingresarDato(dd," Dia de nacimiento",31,1);
}

int Existe_codigo(int codigo,Materias **En_Materias)
{
	if(*En_Materias)
	{
		if((*En_Materias)->prx)
		{
            Materias *aux=*En_Materias;
			while(aux)
			{/**/
				if(aux->Codigo_de_la_Materia == codigo)
					return 1;
				else 
					aux=aux->prx;
			}
			return 0;	
 		}else
		 {/**/
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
	if(*En_Cursos)
	{
		if((*En_Cursos)->prx)
		{
            Cursos *aux=*En_Cursos;
			while(aux)
			{/**/
				if(aux->Codigo_del_curso == codigo)
					return 1;
				else 
					aux=aux->prx;
			}
			return 0;	
 		}else
		 {/**/
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

int Existe_cedula(long int codigo,Personas **En_Personas)
{
	if(*En_Personas)
	{
		if((*En_Personas)->prx)
		{
            Personas *aux=*En_Personas;
			while(aux)
			{/**/
				if(aux->cedula == codigo)
					return 1;
				else 
					aux=aux->prx;
			}
			return 0;	
 		}else
		 {/**/
			Personas *aux=*En_Personas;
			if(aux->cedula == codigo)
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
	do{/*Ciclo infinito hasta que retorne algun valor*/
		printf("\nIngrese el semestre de la materia: ");
		fflush(stdin);fgets(aux,4,stdin);cambio(aux);
		if (aux[0]=='\0')printf("Por favor ingrese un semestre \n");
		if (((aux[0]=='I')||(aux[0]=='i'))&&(aux[1]=='\0'))
			return 1;
		if (((aux[0]=='I')||(aux[0]=='i'))&&((aux[1]=='I')||(aux[1]=='i'))&&(aux[2]=='\0'))
			return 2;
		if (((aux[0]=='I')||(aux[0]=='i'))&&((aux[1]=='I')||(aux[1]=='i'))&&((aux[2]=='I')||(aux[2]=='i'))&&(aux[3]=='\0'))
			return 3;
		if (((aux[0]=='I')||(aux[0]=='i'))&&((aux[1]=='V')||(aux[1]=='v'))&&(aux[2]=='\0'))
			return 4;
		if (((aux[0]=='V')||(aux[0]=='v'))&&(aux[1]=='\0'))
			return 5;
		if (((aux[0]=='V')||(aux[0]=='v'))&&((aux[1]=='I')||(aux[1]=='i'))&&(aux[2]=='\0'))
			return 6;
		if (((aux[0]=='V')||(aux[0]=='v'))&&((aux[1]=='I')||(aux[1]=='i'))&&((aux[2]=='I')||(aux[2]=='i'))&&(aux[3]=='\0'))
			return 7;
		if (((aux[0]=='V')||(aux[0]=='v'))&&((aux[1]=='I')||(aux[1]=='i'))&&((aux[2]=='I')||(aux[2]=='i'))&&((aux[3]=='I')||(aux[3]=='i'))&&(aux[4]=='\0'))
			return 8;
		if (((aux[0]=='I')||(aux[0]=='i'))&&((aux[1]=='X')||(aux[1]=='x'))&&(aux[2]=='\0'))
			return 9;
		if (((aux[0]=='X')||(aux[0]=='x'))&&(aux[1]=='\0'))
			return 10;
		printf(" El semestre ingresado no es valido, intente denuevo");	fflush(stdin);
	}while(true);
}

void Semestre_Romano(int Numero,Materias **Nodo)
{// dado un numero del 1 al 10, lo convierte en romano
	switch (Numero) 
	{
		case 1: 
			strcpy((*Nodo)->SemestreEnRomano,"I"); 
			break;
		case 2: 
			strcpy((*Nodo)->SemestreEnRomano,"II"); 
			break;
		case 3: 
			strcpy((*Nodo)->SemestreEnRomano,"III");
			break;
		case 4: 
			strcpy((*Nodo)->SemestreEnRomano,"IV"); 
			break;
		case 5: 
			strcpy((*Nodo)->SemestreEnRomano,"V");
			break;
		case 6: 
			strcpy((*Nodo)->SemestreEnRomano,"VI"); 
			break;
		case 7: 
			strcpy((*Nodo)->SemestreEnRomano,"VII"); 
			break;
		case 8: 
			strcpy((*Nodo)->SemestreEnRomano,"VIII");
			break;
		case 9: 
			strcpy((*Nodo)->SemestreEnRomano,"IX"); 
			break;
		case 10: 
			strcpy((*Nodo)->SemestreEnRomano,"X");
			break;
		default: 
			break;
	}
}

int validar_numero (char numero[])	
{/*Funcion que nos permite validar dado un string, saber si tiene solo numeros*/
	for(int i=0;unsigned(i)<strlen(numero);i++)
	{/*para cada caracter del string verificar si es un digito decimal*/
		char letra=numero[i];
		if (isdigit(letra))
			continue;
		return false;
	}
	return true;
}

void Consultar_materia(Materias *Las_materias)
{
	if(Las_materias)
	{/*Debe haber algo que consultar*/
		char opciones_Consulta[3];
		opciones_Consulta[0]=0;
		do
		{
			Materias *consulta=Las_materias;system("cls");					
			printf("\t Consultar\n\n");
			printf(" 1- Todas las materias\n 2- Materias Del Semestre \n 3- Nombres que coinciden\n 4- Codigo \n\n 0- SALIR\n\n Escriba su opcion (0-4) = ");
			fflush(stdin);fgets(opciones_Consulta,2,stdin);cambio(opciones_Consulta);fflush(stdin);
			switch(opciones_Consulta[0])
			{
				case '1':
					HM();
					while(consulta)
						{ FormatoMateria(consulta);consulta=consulta->prx;}
					system("pause"); 
					break;

				case '2':
					int x,cont;x=Verificar_Semestre();cont=0;
					HM();
					while(consulta)
					{ /*imprime los datos del nodo de la materia y pasa al siguiente nodo*/
						if (x==consulta->Semestre)
							{FormatoMateria(consulta);cont++;}
						consulta=consulta->prx;
					}
					if (!cont)
						printf("\n\tNo hay materias de dicho semestre\n\n");
					system("pause"); 
					break;

				case '3':
					char nombre[30];int Mats;Mats=0;
					printf("\n\tIngrese el nombre a buscar:");
					fflush(stdin);fgets(nombre,30,stdin);cambio(nombre);fflush(stdin);
					while(consulta)
					{ /*imprime los datos del nodo de la materia y pasa al siguiente nodo*/
						if (strstr(strupr(consulta->Nombre_de_la_Materia),strupr(nombre))!=NULL)
							{FormatoMateria(consulta);Mats++;}
						consulta=consulta->prx;
					}
					if (!Mats)
						printf("\n\t No hay materias con nombres que coincidan\n");
					system("pause");
					break;

				case '4':
					int y;ingresarDato(&y,"Codigo a consultar",maxEntero,1);
					HM();
					while(consulta)
					{ /*imprime los datos del nodo de la materia y pasa al siguiente nodo*/
						if (y==consulta->Codigo_de_la_Materia)
							FormatoMateria(consulta);
						consulta=consulta->prx;
					}
					system("pause"); 
					break;

				default:
					if (opciones_Consulta[0]!='0')
						{printf("\n\nEsta opcion no es valida\n");system("pause");}
					break;
			}
		}while (opciones_Consulta[0]!='0');
	}else
		{printf("No hay materias para consultar\n");system("pause");}
}

void C_NombreMateria(Materias* consulta,Cursos* CursosAsociado)
{
	char nombre[30];int cont=0;
	printf("\n\tIngrese el nombre a buscar:");
	fflush(stdin);fgets(nombre,30,stdin);cambio(nombre);fflush(stdin);
	HM();
	while(consulta)
	{ /*imprime los datos del nodo de la materia y pasa al siguiente nodo*/
		if (strstr(strupr (consulta->Nombre_de_la_Materia),strupr (nombre))!=NULL)
		{
			FormatoMateria(consulta);int cont2=0;
			printf("\tCursos asociados a %s:\n\n",consulta->Nombre_de_la_Materia);HC();
			while(CursosAsociado)
			{
				if(consulta->Codigo_de_la_Materia==CursosAsociado->Codigo_de_la_Materia)
					{FormatoCurso(CursosAsociado);cont2++;}
				CursosAsociado=CursosAsociado->prx;
			}
			if (!cont2)
				printf("\tNingun curso fue asociado a esta materia\n\n");
			cont++;
		}
		consulta=consulta->prx;
	}
	if (!cont)
		printf("\n\t No hay materias con nombres que coincidan\n");
	system("pause"); 
}

void Consultar_curso(Cursos *Los_cursos)
{
	if(Los_cursos)
	{
		char opciones_Consulta[5];
		opciones_Consulta[0]='0';
		do
		{
			 Cursos *consulta=Los_cursos;;system("cls");					
			printf("\t consultar\n\n");
			printf(" 1- Todas los cursos\n 2- Cursos de cierto año \n 3- Cursos de cierto lapso\n 4- Cursos de cierta materia\n 5- Curso especifico \n\n 0- SALIR\n\n Escriba su opcion (0-5) = ");
			fflush(stdin);fgets(opciones_Consulta,2,stdin);cambio(opciones_Consulta);fflush(stdin);
			switch(opciones_Consulta[0])
			{
				case '1':
					HC();
					while(consulta)
						{FormatoCurso(consulta);consulta=consulta->prx;}
					system("pause"); 
					break;

				case '2':
					int AAAA;ingresarDato(&AAAA,"Ingrese el anio",2100,1900);
					HC();
					while(consulta)
					{ 
						if (AAAA==consulta->AAAA)
							FormatoCurso(consulta);
						consulta=consulta->prx;
					}
					system("pause"); 
					break;

				case '3':
					int Lapso;ingresarDato(&Lapso,"Ingrese el Lapso",3,1);
					HC();
					while(consulta)
					{ 
						if (Lapso==consulta->lapso)
							FormatoCurso(consulta);
						consulta=consulta->prx;
					}
					system("pause"); 
					break;

				case '4':
					int Codigo;ingresarDato(&Codigo,"Codigo de la materia",maxEntero,1);
					while(consulta)
					{ 
						if (Codigo==consulta->Codigo_de_la_Materia)
							FormatoCurso(consulta);
						consulta=consulta->prx;
					}
					system("pause"); 
					break;

				case '5':
					int CodigoC;ingresarDato(&CodigoC,"Codigo del curso",maxEntero,1);
					HC();
					while(consulta)
					{ 
						if (CodigoC==consulta->Codigo_del_curso)
							FormatoCurso(consulta);
						consulta=consulta->prx;
					}
					system("pause"); 
					break;

				default:
					if (opciones_Consulta[0]!='0')
						{printf("\n\nEsta opcion no es valida\n");system("pause");}
					break;
			}
		}while (opciones_Consulta[0]!='0');
	}else
		{printf("No hay cursos para consultar\n");system("pause");}
}

void Consultar_Personas(Personas *Las_personas)
{
	if(Las_personas)
	{/*Debe haber algo que consultar*/
		char opciones_Consulta[10];
		opciones_Consulta[0]='0';
		do
		{
			int cont =0;
			Personas *consulta=Las_personas;system("cls");					
			printf("\t consultar\n\n");
			printf(" 1- Todas las personas\n 2- Nombres que coinciden\n 3- Cedula \n\n 0- SALIR\n\n Escriba su opcion (0-3) = ");
			fflush(stdin);fgets(opciones_Consulta,2,stdin);cambio(opciones_Consulta);fflush(stdin);
			switch(opciones_Consulta[0])
			{
				case '1':
					HP();
					while(consulta)
						{FormatoPersona(consulta,true);consulta=consulta->prx;}
					system("pause"); 
					break;

				case '2':
					char nombre[40];
					printf("Introduzca el nombre a consultar: ");
					fflush(stdin);fgets(nombre,40,stdin);cambio(nombre);fflush(stdin);HP();
					while(consulta)
					{ /*imprime los datos del nodo de la persona y pasa al siguiente nodo*/
						if (strstr(strupr(consulta->nombre_apellido),strupr(nombre))!=NULL)
							{FormatoPersona(consulta,false);cont++;}	
						consulta=consulta->prx;
					}
					if(!cont)
						printf("No hay ningun estudiante con ese nombre\n");
					system("pause"); 
					break;

				case '3':
					C_NombreAlumno(consulta);
					break; 

				default:
					if (opciones_Consulta[0] !='0')
						{printf("\n\nEsta opcion no es valida\n");system("pause");}
					break;
			}
		}while (opciones_Consulta[0] !='0');

	}
	else
		{printf("No hay personas para consultar\n");system("pause");}
}

void C_NombreAlumno(Personas*consulta)
{
	char nombre[40];int cont =0;
	printf("\n\tIntroduzca el nombre a consultar: ");
	fflush(stdin);fgets(nombre,40,stdin);cambio(nombre);fflush(stdin);
	HP();
	while(consulta)
	{ /*imprime los datos del nodo de la persona y pasa al siguiente nodo*/
		if (strstr(strupr(consulta->nombre_apellido),strupr(nombre))!=NULL)
			{FormatoPersona(consulta,false);cont++;}	
		consulta=consulta->prx;
	}
	if(!cont)
	printf("No hay ningun estudiante con ese nombre\n");
	system("pause"); 
}

void c_Materia(Materias*M,Cursos*cursosDados,Personas*PersonasInscritas)
{
	Personas *Aux;Participacion *Inscritoencurso; int CodigoDado,cursosdelamateria=0,Inscritos=0,Aprobados=0;
	ingresarDato(&CodigoDado,"Codido de la materia",maxEntero,0);
	while (M && M->Codigo_de_la_Materia!=CodigoDado)
		M=M->prx;
	if(M)
	{
		printf("\n\tMateria=\n\n");
		FormatoMateria(M);
		printf("\tCursos=\n\n");
		while (cursosDados)
		{
			if(cursosDados->Codigo_de_la_Materia==M->Codigo_de_la_Materia)
			{
				FormatoCurso(cursosDados);cursosdelamateria++;
				Aux=PersonasInscritas;
				while(Aux)
				{
					Inscritoencurso=Aux->Record;
					while(Inscritoencurso)
					{
						if(Inscritoencurso->Codigo_del_curso==cursosDados->Codigo_del_curso)
						{
							Inscritos++;
							if(Inscritoencurso->nota>9)
								Aprobados++;
						}
						Inscritoencurso=Inscritoencurso->prx;
					}
					Aux=Aux->prx;
				}
			}
			cursosDados=cursosDados->prx;
		}
		if(!cursosdelamateria)
			printf("\n\tEsta Materia no tiene cursos asociados\n\n");
		if(Inscritos)
			printf("\n\t *Inscritos: %i, *Aprobados: %i, *Reprobados: %i\n\n\n",Inscritos,Aprobados,Inscritos-Aprobados);
		else
			printf("\n\t esta Materia no tiene personas inscritas\n\n");
	}
	else
		printf("\n\tLa materia solicitada no se encuentra registrada\n\n");
	system("Pause");
}

void c_CursosDe(Materias*Mats,Cursos*cursosDados,Personas*PersonasInscritas)
{
	Personas *Aux;Participacion *Inscritoencurso; int CursosDeLaFecha=0,Inscritos,Aprobados,AAAA,lapso;
	ingresarDato(&AAAA,"AAAA: ",2100,1900);
	ingresarDato(&lapso,"Lapso: ",3,1);
	printf("\n\tCursos del lapso %i en %i:\n\n\n",lapso,AAAA);
	while (cursosDados)
	{
		if(cursosDados->AAAA==AAAA && cursosDados->lapso==lapso)
		{
			Materias *M=Mats;
			HC();CursosDeLaFecha++;
			FormatoCurso(cursosDados);
			if (M)
				while (M)
				{
					if(M->Codigo_de_la_Materia==cursosDados->Codigo_de_la_Materia)
					{	
						printf("\tMateria del curso=\n\n");FormatoMateria(M);
						break;
					}
					M=M->prx;
				}
			Aux=PersonasInscritas;
			Inscritos=0;Aprobados=0;
			while(Aux)
			{
				Inscritoencurso=Aux->Record;
				while(Inscritoencurso)
				{
					if(Inscritoencurso->Codigo_del_curso==cursosDados->Codigo_del_curso)
					{
						Inscritos++;
						if(Inscritoencurso->nota>9)
							Aprobados++;
					}
					Inscritoencurso=Inscritoencurso->prx;
				}
				Aux=Aux->prx;
			}
			printf("\n\t *Inscritos: %i *Aprobados: %i *Reprobados: %i\n\n\n",Inscritos,Aprobados,Inscritos-Aprobados);
		}
	cursosDados=cursosDados->prx;
	}
	if (CursosDeLaFecha==0)
		printf("\tNo hay cursos en la fecha solicitada\n\n");
	system("Pause");
}

void C_Aprobados(Personas* aprobado,Cursos* Cursomateria)
{//Dada una materia ( c�digo ) mostrar los alumnos que la han aprobado (cedula, apellido y nombre con su nota )
	int CodigoIngresado,Aprobados=0;
	ingresarDato(&CodigoIngresado,"\t Codigo de la materia",maxEntero,0);
	while (Cursomateria)
	{
		if(Cursomateria->Codigo_de_la_Materia==CodigoIngresado)
		{
			while(aprobado)
			{
				Participacion *Aux=aprobado->Record;
				while (Aux)
				{
					if (Aux->Codigo_del_curso==Cursomateria->Codigo_del_curso)
					{
						if(Aux->nota>9)
						{
							FormatoPersona(aprobado,false);
							Aprobados++;
						}
					}
					Aux=Aux->prx;
				}
				aprobado=aprobado->prx;
			}
			if (Aprobados)
				printf("\n\tTotal de aprobados %i\n\n",Aprobados);
			else
				printf("\n\tNo hubo aprobados en esta maetria\n\n");
			return;
		}
		Cursomateria=Cursomateria->prx;
	}
	printf("\n\tNo Existe dicha materia\n\n");
}

void C_Cursos(Materias* Mats,Cursos*cursosDados,Personas*PersonasInscritas)
{//Todos los cursos (con sus alumnos y notas) 
	Personas *Aux;Participacion *Inscritoencurso; int Inscritos;
	while (cursosDados)
	{
		Materias *M=Mats;
		printf("\tCurso=\n\n");
		FormatoCurso(cursosDados);
		if (M)
			while (M)
			{
				if(M->Codigo_de_la_Materia==cursosDados->Codigo_de_la_Materia)
				{	
					printf("\tMateria del curso=\n\n");FormatoMateria(M);
					break;
				}
				M=M->prx;
			}
		Aux=PersonasInscritas;
		Inscritos=0;
		printf("\tPersonas del curso=\n\n");
		while(Aux)
		{
			Inscritoencurso=Aux->Record;
			while(Inscritoencurso)
			{
				if(Inscritoencurso->Codigo_del_curso==cursosDados->Codigo_del_curso)
				{
					Inscritos++;
					FormatoPersona(Aux,false);
					printf("\t Nota: %i\n\n",Inscritoencurso->nota);
				}
				Inscritoencurso=Inscritoencurso->prx;
			}
			Aux=Aux->prx;
		}
		if(Inscritos)
			printf("\n\t *Total de inscritos: %i\n\n\n",Inscritos);
		else
			printf("\t este curso no tiene personas inscritas\n\n");
	cursosDados=cursosDados->prx;
	}
	system("Pause");
}

void C_CursosPeriodo(Cursos*cursosDados,Personas*PersonasInscritas)
{
	Personas *Aux;Participacion *Inscritoencurso; int Inscritos,ComienzoDelPeriodo,FinDelPeriodo,DelPeriodo=0;
	ingresarDato(&ComienzoDelPeriodo,"Comienzo Del periodo",2100,1900);
	ingresarDato(&FinDelPeriodo,"Fin Del periodo",2100,1900);
	while (cursosDados)
	{
		if(cursosDados->AAAA>=ComienzoDelPeriodo && cursosDados->AAAA<=FinDelPeriodo)
		{
			DelPeriodo++;
			printf("\tCurso=\n\n");
			FormatoCurso(cursosDados);
			Aux=PersonasInscritas;
			Inscritos=0;
			printf("\tPersonas del curso=\n\n");
			while(Aux)
			{
				Inscritoencurso=Aux->Record;
				while(Inscritoencurso)
				{
					if(Inscritoencurso->Codigo_del_curso==cursosDados->Codigo_del_curso)
					{
						Inscritos++;
						FormatoPersona(Aux,false);
						printf("\t Nota: %i\n\n",Inscritoencurso->nota);
					}
					Inscritoencurso=Inscritoencurso->prx;
				}
				Aux=Aux->prx;
			}
			if(Inscritos)
				printf("\n\t *Total de inscritos: %i\n\n\n",Inscritos);
			else
				printf("\t este curso no tiene personas inscritas\n\n");
		}
		cursosDados=cursosDados->prx;
	}
	if (DelPeriodo==0)
	{
		printf("\n\tNo hay cursos en este periodo\n\n");
	}
	system("Pause");
}

void C_Alumno(Personas* consulta)
{//Dada una cedula mostrar todos los cursos con sus notas tomadas por esa persona
	int CedulaIngresada;
	ingresarDato(&CedulaIngresada,"\t cedula de la persona",maxEntero,0);
	while(consulta && consulta->cedula<CedulaIngresada)
		consulta=consulta->prx;
	if (consulta->cedula==CedulaIngresada)
	{
		printf("\t%s",consulta->nombre_apellido);
		calificaciones(consulta->Record);
	}
	else
		printf("\tNo existe registro de dicha persona");
	system("Pause");
}

void Eliminar_materia (Materias **Las_materias, Cursos **El_curso)
{
	int codigo_mat,cont=0;
	if (*Las_materias)
	{
		Materias *consulta=*Las_materias, *temp=NULL;
		ingresarDato(&codigo_mat,"Codigo de materia a eliminar",maxEntero,1);
		if(*El_curso)
			Eliminar_curso_materia(El_curso,codigo_mat);
		if ((consulta->Codigo_de_la_Materia) == codigo_mat)
		{
			temp = *Las_materias;
			*Las_materias = (*Las_materias)->prx;
			delete temp;
		}else
		{
			while(consulta->prx)
			{
				if (consulta->prx->Codigo_de_la_Materia == codigo_mat)
				{
					temp = consulta->prx;
					consulta->prx = temp->prx;
					delete temp;
					cont ++;
					printf("\n\tMATERIA ELIMINADA CORRECTAMENTE!\n");
					system("pause");
				}
				else
					consulta = consulta->prx;
			}
			if(cont != 1)
			 printf("\n\tLa materia [%i] no se encuentra\n", codigo_mat);
		}
	}else
		{printf("\n\tNO HAY MATERIAS PARA ELIMINAR\n");system("pause");}
}

void Eliminar_curso (Cursos **Los_cursos)
{
	int codigo_mat,cont=0;
	if (*Los_cursos)
	{
		Cursos *consulta=*Los_cursos, *temp=NULL;
		ingresarDato(&codigo_mat,"Codigo del curso a eliminar",maxEntero,1);
		if ((consulta->Codigo_del_curso) == codigo_mat)
		{
			temp = *Los_cursos;
			*Los_cursos = (*Los_cursos)->prx;
			delete temp;
		}else
		{
			while(consulta->prx)
			{
				if (consulta->prx->Codigo_del_curso == codigo_mat)
				{
					temp = consulta->prx;
					consulta->prx = temp->prx;
					delete temp;
					cont +=1;
					printf("\n\tCURSO ELIMINADO CORRECTAMENTE!\n");
					system("pause");
				}
				else
					consulta = consulta->prx;
			}
			if(cont != 1)
				printf("\n\tEl curso [%i] no se encuentra\n", codigo_mat);
		}
	}
	else
		{printf("\n\tNO HAY CURSOS PARA ELIMINAR\n");system("pause");}
}

void Eliminar_persona (Personas **Las_personas)
{
	int codigo_per,cont=0;
	if (*Las_personas)
	{
		Personas *consulta=*Las_personas, *temp=NULL;
		ingresarDato(&codigo_per,"Cedula del estudiante a eliminar",maxEntero,1);
		if ((consulta->cedula) == codigo_per)
		{
			while(consulta->Record)
			{
				Participacion *aux2=consulta->Record;
				consulta->Record=consulta->Record->prx;
				delete aux2;
			}
			temp = *Las_personas;
			*Las_personas = (*Las_personas)->prx;
			delete temp;
		}else
		{
			while(consulta->prx)
			{
				if (consulta->prx->cedula == codigo_per)
				{
					while(consulta->Record)
					{
						Participacion *aux2=consulta->Record;
						consulta->Record=consulta->Record->prx;
						delete aux2;
					}
					temp = consulta->prx;
					consulta->prx = temp->prx;
					delete temp;
					cont +=1;
					printf("\n\tPERSONA ELIMINADA CORRECTAMENTE!\n");
					system("pause");
				}
				else
					consulta = consulta->prx;
			}
			if(cont != 1)
				printf("\n\tEl estudiante de cedula [%i] no se encuentra\n", codigo_per);
		}
	}else
		{printf("\n\tNO HAY PERSONAS PARA ELIMINAR\n");system("pause");}
}

void Eliminar_curso_materia (Cursos **Los_cursos, int codigo_mat)
{
	if (*Los_cursos)
	{
		Cursos *consulta=*Los_cursos, *temp=NULL;
		if ((consulta->Codigo_de_la_Materia) == codigo_mat)
		{
			temp = *Los_cursos;
			*Los_cursos = (*Los_cursos)->prx;
			delete temp;
			Eliminar_curso_materia (Los_cursos, codigo_mat);
		}else
		{
			while(consulta->prx)
			{
				if (consulta->prx->Codigo_de_la_Materia == codigo_mat)
				{
					temp = consulta->prx;
					consulta->prx = temp->prx;
					delete temp;
				}else
					consulta = consulta->prx;
			}
		}
	}
}

int Inscribe_o_no(Cursos *c,Participacion *p){
	if(p){
	 int cont=0;
	 while(p){
		 int n=Regresa_cod_mat(c,p->Codigo_del_curso);
		  Participacion *q=p->prx;
		 if(p->nota <= 9)
			 cont+=1;
		 while(q){
			 if((n == Regresa_cod_mat(c,q->Codigo_del_curso))&&(q->nota <= 9))
			   cont+=1;
			 q=q->prx;
		 }
		 if(cont>4)
			 break;
		 else
		 {
			 cont=0;
			 p=p->prx;
		 }
	 }
	 if (cont<=4)
		 return 1;
	 else
	  return 0;
	 }
	else
		return 1;
}

int Regresa_cod_mat(Cursos *c, int x){
	while((c)&&(c->Codigo_del_curso != x)){
     c=c->prx;
	}
	if(c)
		return c->Codigo_de_la_Materia;
	else
	 return 0;
}

void Agregar_nota(Personas **p, int n,int c){
	Participacion *aux=new Participacion;
	aux->Codigo_del_curso=c;
	aux->nota=n;
	aux->prx=(*p)->Record;
	(*p)->Record=aux;
}

void Agregar_Curso_persona(Personas *Listaper, Cursos *listacur, Materias *listamat)
{
	if((Listaper)&&(listamat)&&(listacur))
	{
		int cod=0;
		ingresarDato(&cod,"Cedula del estudiante a agregar al curso",maxEntero,1);
		while((Listaper)&&(Listaper->cedula != cod))
			Listaper=Listaper->prx;
		if(Listaper)
		{
			int nota=0,codicur=0,Registrado;
			Registrado=Inscribe_o_no(listacur,Listaper->Record);
			if(Registrado){
			ingresarDato(&codicur,"Codigo del curso",maxEntero,1);
			Cursos *Copia=listacur;Participacion *AUX=Listaper->Record;int ExisteCurso=0,Aprobado=0,RegistradoEnCurso=0;
			ExisteCurso=Regresa_cod_mat(listacur,codicur);
			if(ExisteCurso)
			{
				while(AUX)
				{
					while (Copia)
					{
						if(AUX->Codigo_del_curso==Copia->Codigo_del_curso)
							if(Copia->Codigo_de_la_Materia==ExisteCurso)
							{
								if(AUX->nota>9)
									Aprobado++;
							}
						Copia=Copia->prx;
					}
					if(AUX->Codigo_del_curso==codicur)
						RegistradoEnCurso++;
					AUX=AUX->prx;
				}
				if (RegistradoEnCurso)
					printf("\n\tEste Estudiante ya fue registrado en el curso, no se puede registrar nuevamente\n\n");
				else
				{
					if(!Aprobado)
					{
							ingresarDato(&nota,"Nota del estudiante en el curso",20,1);
							Agregar_nota(&Listaper,nota,codicur);
							printf("Estudiante de cedula: [%i] fue agregado a: CURSO[%i] con la nota:(%i/20 pts)\n",Listaper->cedula,Listaper->Record->Codigo_del_curso,Listaper->Record->nota);	
					}else
						printf("\n\tEsta Persona ya aprobo esta materia en otro curso\n\n");
				}
			}
			else
				printf("El curso no existe\n");
		 }else
				{
					printf("Esta persona reprobo mas de 4 veces una materia\n");
					printf("Por lo que ya no puede ser inscrito en el instituto\n");
				}
		}else
            printf("Esa persona no se encuentra en el sistema\n");
	}else
		printf("No se cumplen las condiciones para registrar a una persona en un curso\n");
	system("pause");
}

int isdigit(char c)
{
	if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
		return 1;
	return 0;
}

int bisiesto (year Y)
{
	if (Y%4)
		if(Y%100)
			if(Y%400)
				return 0;
			else
				return 1;
		else
			return 0;
	else
		return 1;
}

int LimitarCaracteres (char *copia, int max)
{		
		if (!(strlen(copia)>0)||!(strlen(copia)<=unsigned(max)))
			return 0;
		else 
			return 1;
}	

void cambio(char c1[])
{// // evita salto de linea luego de un fgets y cambia las comas por punto para evitar errores en los archivos
	for(int i=0;unsigned(i)<strlen(c1);i++)
		if(c1[i] == '\n')
			c1[i] = '\0';
		else 
			if(c1[i]==',')
				c1[i]='.';
}

void HM()
{printf("\n\tCodigo | \"Materia\" | Semestre | Creditos | Descripcion \n\n");}

void HC()
{printf("\n\t Materia | Curso | (Lapso) | AAAA\n\n");}

void HP()
{printf("\n\tNombre\t\t| Cedula | (dd/mm/aaaa) | Direccion\n\n");}

void FormatoFecha(fecha F)
{
	printf("(%i",F.dd);
	if (F.mm==1)
		printf("/ene");
	else
		if (F.mm==2)
			printf("/feb");
		else
			if (F.mm==3)
				printf("/marz");
			else
				if (F.mm==4)
					printf("/abr");
				else
					if (F.mm==5)
						printf("/may");
					else
						if (F.mm==6)
							printf("/jun");
						else
							if (F.mm==7)
								printf("/jul");
							else
								if (F.mm==8)
									printf("/agos");
								else
									if (F.mm==9)
										printf("/sep");
									else
										if (F.mm==10)
											printf("/oct");
									else
										if (F.mm==11)
											printf("/nov");
										else
											if (F.mm==12)
												printf("/dic");
	printf("/%i)",F.yyyy);
}

void FormatoMateria(Materias* Nodo)
{printf("\t[%d] \"%s\"    %s   (%i)   : %s \n\n",Nodo->Codigo_de_la_Materia,Nodo->Nombre_de_la_Materia,Nodo->SemestreEnRomano,Nodo->Creditos_de_la_Materia,Nodo->Descripcion_de_la_Materia);}

void FormatoCurso(Cursos* Nodo)
{printf("\t [%d]   \"%i\"   (%i):    %i \n\n",Nodo->Codigo_de_la_Materia,Nodo->Codigo_del_curso,Nodo->lapso,Nodo->AAAA);}

void FormatoPersona(Personas* Nodo,int todo)
{
	printf("\t%s\tC.I:%i  ",Nodo->nombre_apellido,Nodo->cedula);FormatoFecha(Nodo->Fecha_de_Nacimiento);printf(" [%s]",Nodo->direccion);
	if (todo)
		calificaciones(Nodo->Record);
	else
		printf("\n\n");
}

void calificaciones(Participacion* calificacion)
{if (calificacion!=NULL)
		{
			Participacion* inscripcion=calificacion;
			printf("\n\t    inscrito en [Curso] (nota)\n");
			while (inscripcion)
			{
				printf("\t\t\t[%d] (%i/20)\n",inscripcion->Codigo_del_curso,inscripcion->nota);
				inscripcion=inscripcion->prx;
			}printf("\n");
		}
		else
			printf("\n\t sin inscripciones\n\n");}

int Exportar_Materias(Materias *nodos,char ruta[])
{/* Exporta en un archivo el contenido de las materias*/
	FILE *Nuevo_archivo = NULL;;char rutaMat[100];
	strcpy(rutaMat,ruta);strcat(rutaMat,"ArchivoMaterias.txt");
	Nuevo_archivo = fopen(rutaMat,"w");/*Abre el archivo creado*/
	if(Nuevo_archivo == NULL ) 
		{printf("No fue posible abrir el archivo\n");return 0;}
	while (nodos)
		{fprintf (Nuevo_archivo,"%i,%s,%i,%i,%s\n",nodos->Codigo_de_la_Materia,nodos->Nombre_de_la_Materia,nodos->Creditos_de_la_Materia,nodos->Semestre,nodos->Descripcion_de_la_Materia);nodos=nodos->prx;}
	fclose(Nuevo_archivo);return 1;
}

int Exportar_Cursos(Cursos *nodos,char ruta[])
{/* Exporta en un archivo el contenido de los cursos*/
	FILE *Nuevo_archivo = NULL;char rutaCur[100];
	strcpy(rutaCur,ruta);strcat(rutaCur,"ArchivoCursos.txt"); 
	Nuevo_archivo = fopen(rutaCur,"w");
	if(Nuevo_archivo == NULL ) 
		{printf("No fue posible abrir el archivo\n");return 0;}
	while (nodos)
		{fprintf (Nuevo_archivo,"%i,%i,%i,%i\n",nodos->Codigo_de_la_Materia,nodos->Codigo_del_curso,nodos->lapso,nodos->AAAA);nodos=nodos->prx;}
	fclose(Nuevo_archivo);return 1;
}

int Exportar_Personas(Personas *nodos,char ruta[])
{/* Exporta en un archivo el contenido de las persdonas*/
	FILE *Nuevo_archivo = NULL;;char rutaPer[100];
	strcpy(rutaPer,ruta);strcat(rutaPer,"ArchivoPersonas.txt");
	Nuevo_archivo = fopen(rutaPer,"w");
	if(Nuevo_archivo == NULL ) 
		{printf("No fue posible abrir el archivo\n");return 0;}
	while (nodos)
	{
		fprintf (Nuevo_archivo,"%i,%s,%i,%i,%i,%s",nodos->cedula,nodos->nombre_apellido,nodos->Fecha_de_Nacimiento.yyyy,nodos->Fecha_de_Nacimiento.mm,nodos->Fecha_de_Nacimiento.dd,nodos->direccion);
		if (nodos->Record!=NULL)
		{
			Participacion *aux=nodos->Record;
			while (aux)
			{
				fprintf(Nuevo_archivo,",%i,%i",aux->Codigo_del_curso,aux->nota);
				aux=aux->prx;
			}
		}
		fprintf(Nuevo_archivo,",0\n");
		nodos=nodos->prx;
	}
	fclose(Nuevo_archivo);return 1;
}

int Importar_Materias(Materias **nodos,char ruta[])
{
	FILE *Archivo_entrada = NULL;char linea[150];char *Elemento;char rutaMat[100];
	strcpy(rutaMat,ruta);strcat(rutaMat,"ArchivoMaterias.txt");
	Archivo_entrada= fopen(rutaMat,"r");
	if(Archivo_entrada == NULL ) 
		{printf("No fue posible abrir el archivo\n");return 0;}
	rewind(Archivo_entrada);printf("\n  Importar a:\n\n");HM();
    while (fgets(linea, sizeof(linea), Archivo_entrada)) 
	{// Lee cada línea del archivo y lo convierte en un nodo completo
		Materias *Nuevo_nodo= new Materias; int error=0;
        Elemento = strtok(linea, ",");      
		if ( atoi(Elemento)>=maxEntero || atoi(Elemento)<=0 || !validar_numero(Elemento) || Existe_codigo(atoi(Elemento),nodos) ) 
			error++;
		else 
			Nuevo_nodo->Codigo_de_la_Materia=atoi(Elemento);
		
		Elemento = strtok(NULL, ",");cambio(Elemento);
		if (LimitarCaracteres (Elemento, 30))
			strcpy(Nuevo_nodo->Nombre_de_la_Materia,Elemento);
		else 
			error++;	
		
		Elemento = strtok(NULL, ",");
		if ((atoi(Elemento) <2)||(atoi(Elemento) >5)) 
			error++;
		else
			Nuevo_nodo->Creditos_de_la_Materia=atoi(Elemento);
		
		Elemento = strtok(NULL, ",");
		if ((atoi(Elemento) <1)||(atoi(Elemento) >10))
			error++;	
		else 
			{Nuevo_nodo->Semestre=atoi(Elemento);Semestre_Romano(Nuevo_nodo->Semestre,&Nuevo_nodo);}
		
		Elemento = strtok(NULL, ",");cambio(Elemento);
		if (LimitarCaracteres (Elemento, 100))
			strcpy(Nuevo_nodo->Descripcion_de_la_Materia,Elemento);
		else
			error++;
		
		if(error)
			printf("Errores en el nodo: %i\n",error);
		else 
			{insertar_MateriaOrdenadamente(nodos, &Nuevo_nodo);FormatoMateria(Nuevo_nodo);}
		Elemento = strtok(NULL, ",");
	}
	system("pause");fclose(Archivo_entrada);return 1;
} 

int Importar_Cursos(Cursos **nodos,Materias *materia,char ruta[])
{
	FILE *Archivo_entrada = NULL;char linea[150];char *Elemento;char rutaCur[100];
	strcpy(rutaCur,ruta);strcat(rutaCur,"ArchivoCursos.txt"); 
	Archivo_entrada = fopen(rutaCur,"r");/*Abre el archivo creado*/
	if(Archivo_entrada == NULL ) 
		{printf("No fue posible abrir el archivo\n");return 0;}
	rewind(Archivo_entrada);printf("\n  Importar a:\n\n");HC();
    while (fgets(linea, sizeof(linea), Archivo_entrada)) 
	{// Lee cada línea del archivo y lo convierte en un nodo completo
		Cursos *Nuevo_nodo= new Cursos; int error=0;
        Elemento = strtok(linea, ",");      
		if ( atoi(Elemento)>=maxEntero ||atoi(Elemento)<=0 || !validar_numero(Elemento)||!Existe_codigo(atoi(Elemento),&materia) ) 
			error++;
		else
			Nuevo_nodo->Codigo_de_la_Materia=atoi(Elemento);

		Elemento = strtok(NULL, ",");
		if ( atoi(Elemento)>=maxEntero || atoi(Elemento)<=0 || !(validar_numero(Elemento)) ) 
			error++;
		else 
			Nuevo_nodo->Codigo_del_curso=atoi(Elemento);

		Elemento = strtok(NULL, ",");
		if (atoi(Elemento)<1||atoi(Elemento)>3) 
			error++;
		else
			Nuevo_nodo->lapso=atoi(Elemento);

		Elemento = strtok(NULL, ",");cambio(Elemento);
		if (atoi(Elemento)<1900||atoi(Elemento)>2100) 
			error++;
		else
			Nuevo_nodo->AAAA=atoi(Elemento);

		if(error)
			printf("Errores en el nodo: %i\n",error);
		else 
			{insertar_CursoOrdenadamente(nodos,&Nuevo_nodo); FormatoCurso(Nuevo_nodo);}
		Elemento = strtok(NULL, ",");
	}
	system("pause");fclose(Archivo_entrada);return 1;
}

int Importar_Personas(Personas **nodos,char ruta[])
{
	FILE *Archivo_entrada = NULL;char linea[150];char *Elemento;char rutaPer[100];
	strcpy(rutaPer,ruta);strcat(rutaPer,"ArchivoPersonas.txt");
	Archivo_entrada = fopen(rutaPer,"r");
	if(Archivo_entrada == NULL ) 
		{printf("No fue posible abrir el archivo\n");return 0;}
	rewind(Archivo_entrada);printf("\n  Importar a:\n\n");HP();
    while (fgets(linea, sizeof(linea),Archivo_entrada)) 
	{// Lee cada línea del archivo y lo convierte en un nodo completo
		Personas *Nuevo_nodo= new Personas; int error=0;
        Elemento = strtok(linea, ",");      
		if ( atoi(Elemento)>=maxEntero ||atoi(Elemento)<=0 || !validar_numero(Elemento) ) 
			error++;
		else
			Nuevo_nodo->cedula=atoi(Elemento);
		
		Elemento = strtok(NULL, ",");cambio(Elemento);
		if (LimitarCaracteres (Elemento, 30))
			strcpy(Nuevo_nodo->nombre_apellido,Elemento);
		else 
			error++;	
		
		Elemento = strtok(NULL, ",");cambio(Elemento);
		if (atoi(Elemento)<1900||atoi(Elemento)>2100) 
			error++;
		else
			Nuevo_nodo->Fecha_de_Nacimiento.yyyy=atoi(Elemento);
		
		Elemento = strtok(NULL, ",");cambio(Elemento);
		if (atoi(Elemento)<1||atoi(Elemento)>12) 
			error++;
		else
			{Nuevo_nodo->Fecha_de_Nacimiento.mm=atoi(Elemento);}
		
		Elemento = strtok(NULL, ",");cambio(Elemento);
		if (atoi(Elemento)<1||atoi(Elemento)>31) 
			error++;
		else
			Nuevo_nodo->Fecha_de_Nacimiento.dd=atoi(Elemento);
		
		Elemento = strtok(NULL, ",");cambio(Elemento);		
		if (LimitarCaracteres (Elemento, 40))
			strcpy(Nuevo_nodo->direccion,Elemento);
		else 
			error++;	
		
		Elemento = strtok(NULL, ",");cambio(Elemento);		
		if (Elemento[0]=='0')
			Nuevo_nodo->Record=NULL;
		else 
		{	
			Nuevo_nodo->Record=NULL;
			while((Elemento[0]!='0'))
			{
				
				Participacion* NuevaInscripcion= new Participacion;
				if ( atoi(Elemento)>=maxEntero ||atoi(Elemento)<=0 || !validar_numero(Elemento) ) 
					error++;/*Validar que exista el curso*/
				else
				NuevaInscripcion->Codigo_del_curso=atoi(Elemento);

				Elemento = strtok(NULL, ",");cambio(Elemento);
				if ( atoi(Elemento)>=20||atoi(Elemento)<=0 || !validar_numero(Elemento) ) 
					error++;
				else
					NuevaInscripcion->nota=atoi(Elemento);
				
				NuevaInscripcion->prx=Nuevo_nodo->Record;
				Nuevo_nodo->Record=NuevaInscripcion;
				Elemento = strtok(NULL, ",");cambio(Elemento);
			}
		}
		if(error)
			printf("%i Errores en el nodo\n",error);
		else 
			{insertar_PersonaOrdenadamente(nodos,&Nuevo_nodo);FormatoPersona(Nuevo_nodo,true);}
		Elemento = strtok(NULL, ",");
	}
	system("pause");fclose(Archivo_entrada);return 1;
}
