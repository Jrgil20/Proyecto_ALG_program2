# CentroDeEstudiantes

## Project Overview and Purpose

The `CentroDeEstudiantes` project is designed to manage student records, courses, and subjects. It provides functionalities to add, modify, and delete records for students, courses, and subjects. The project aims to facilitate the management of student information and academic records in an educational institution.

## Structures

### Materias

The `Materias` structure represents a subject in the educational institution. It includes the following fields:
- `Codigo_de_la_Materia`: Unique code for the subject.
- `Nombre_de_la_Materia`: Name of the subject.
- `Descripcion_de_la_Materia`: Description of the subject.
- `Semestre`: Semester in which the subject is offered.
- `SemestreEnRomano`: Semester in Roman numerals.
- `Creditos_de_la_Materia`: Number of credits for the subject.

### Cursos

The `Cursos` structure represents a course in the educational institution. It includes the following fields:
- `Codigo_del_curso`: Unique code for the course.
- `Codigo_de_la_Materia`: Code of the subject associated with the course.
- `AAAA`: Year in which the course is offered.
- `lapso`: Term in which the course is offered.

### Personas

The `Personas` structure represents a person (student) in the educational institution. It includes the following fields:
- `cedula`: Unique identification number for the person.
- `nombre_apellido`: Name and surname of the person.
- `Fecha_de_Nacimiento`: Date of birth of the person.
- `direccion`: Address of the person.
- `Record`: Pointer to the participation records of the person.

### Participacion

The `Participacion` structure represents the participation of a person in a course. It includes the following fields:
- `Codigo_del_curso`: Code of the course in which the person is participating.
- `nota`: Grade obtained by the person in the course.
- `status`: Status of the person's participation in the course.
- `prx`: Pointer to the next participation record.

## Main Functions

### Adding Records

The project provides functions to add records for subjects, courses, and persons. These functions include:
- `Agregar_Materia`: Adds a new subject to the list of subjects.
- `Agregar_Curso`: Adds a new course to the list of courses.
- `Agregar_Persona`: Adds a new person to the list of persons.

### Modifying Records

The project provides functions to modify records for subjects, courses, and persons. These functions include:
- `Modificar_Materia`: Modifies the details of an existing subject.
- `Modificar_Curso`: Modifies the details of an existing course.
- `Modificar_Persona`: Modifies the details of an existing person.

### Deleting Records

The project provides functions to delete records for subjects, courses, and persons. These functions include:
- `Eliminar_materia`: Deletes an existing subject and its associated courses.
- `Eliminar_curso`: Deletes an existing course and its references in the system.
- `Eliminar_persona`: Deletes an existing person and their references in the system.

## Other Key Functions

The project also includes other key functions to manage and query the records. These functions include:
- `Consultar_materia`: Queries and displays the details of subjects.
- `Consultar_curso`: Queries and displays the details of courses.
- `Consultar_Personas`: Queries and displays the details of persons.
- `C_NombreMateria`: Searches for subjects by name and displays their associated courses.
- `C_NombreAlumno`: Searches for persons by name and displays their details.
- `c_Materia`: Displays the details of a subject and its associated courses.
- `c_CursosDePeriodo`: Displays the courses offered in a specific term.
- `C_Aprobados`: Displays the persons who have passed a specific subject.
- `C_Cursos`: Displays all courses and their associated persons and grades.
- `C_CursosDeAnyoLapso`: Displays the courses offered in a specific year and term.
- `C_Alumno`: Displays the courses and grades of a specific person.
