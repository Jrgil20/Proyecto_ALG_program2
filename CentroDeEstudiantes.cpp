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

/*estructuras y tipos secundarios*/
typedef int year;	typedef int month;	typedef int day; typedef int Codigo_curso; typedef int Codigo_Materia;

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
	/*Si se elimina una persona en el sistema deben eliminarse todas sus referencias en el sistema.*/
	Personas *prx;
};

int main ()
{
	Personas AlumnoA= {28073553,"J",{2002,8,16},"los teques",NULL};
	Materias Calculo2={30125,"calculo","Geometria analitica y derivacion","II",5,NULL};
	Cursos geometria_analitica={1225,Calculo2.Codigo_de_la_Materia,2020,3,NULL};

	printf("%i",AlumnoA.Fecha_de_Nacimiento.yyyy);
	printf("%i",Calculo2.Codigo_de_la_Materia);
	printf("%i",geometria_analitica.Codigo_de_la_Materia);
	system("pause");
	return 0;
}

