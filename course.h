#include <iostream>
#include <cstring>
#include "utilities.h"


// Class struct
class Course
{
public:
	
	// Default constructor
	Course();



	// Constructor with Course argument
	/*
		INPUT:	- aCourse - Course object - The created course will have the details
						    of the argument course
	*/
	Course(const Course& aCourse);



	// Constructor with detail arguments
	/*
		INPUT:	- courseName - cstring - the name of the course
			- CRN - ctstring - the course reference number
			- description - the course description
			- credits - int - the number of credits the course is worth
	*/
	Course(const char courseName[],
		const char CRN[],
		const char description[],
		const int credits);



	// Destructor
	~Course();



	// Create a course object
	/*
		INPUT:	- newCourse - Course object - course whose details to copy
						      into the calling course

		OUTPUT:	- returns int - 0 for faiulre, 1 for success
	*/
	int createCourse(const Course& newCourse);
	


	// Create a course object
	/*
		INPUT:	- courseName - cstring - name of the course being created
			- CRN - cstring - course reference number
			- description - cstring - description of the course
			- credits - int - number of credits the course is worth

		OUTPUT:	- returns int - 0 for failure, 1 for success
	*/
	int createCourse(const char courseName[],
				const char CRN[],
				const char description[],
				const int credits);



	// Copies the details of the argument course into the calling course
	/*
		INPUT:	- sourceCourse - Course object - the object that you want to copy
							 the details of

		OUTPUT:	- returns int - 0 for failure, 1 for success
	*/
	int copyCourse(const Course& sourceCourse);



	// Displays the CRN of the calling course
	/*
		OUTPUT:	- returns int - 0 for failure, 1 for success
	*/
	int displayCRN() const;



	// Displays the details of the course
	/*
		OUTPUT:	- returns int - 0 for failure, 1 for success
	*/
	int displayCourse() const;



	// Compare the calling course's CRN against the argument course's CRN
	/*
		INPUT:	- aCourse - Course object - the course object to compare against

		OUTPUT:	- returns int
				- will be negative if the argument CRN is lower
				- will be 0 if the argument CRN is equal
				- will be positive if the argument CRN is higher
	*/
	int compareCRN(const Course& aCourse) const;



	// Compare the calling coure's CRN against the argument cstring
	/*
		INPUT:	- CRN - cstring - the cstring to compare against

		OUTPUT:	- returns int 
				- will be negative if the argument CRN is lower
				- will be 0 if the argument CRN is equal
				- will be positive if the argument CRN is higher
	*/
	int compareCRN(const char CRN[]) const;


private:
	char* 	_courseName;	// name of the course
	char*	_CRN;		// course reference number
	char*	_description;	// description of the course
	int	_credits;	// number of credits the course is worth



	// Delets and deallocates the private data members of a class
	/*
		OUTPUT:	- returns int - 0 for failure, 1 for success
	*/
	int deleteCourse();
};
