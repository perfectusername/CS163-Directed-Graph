#include "course.h"



// Vertex struct
struct Vertex
{
	// Default constructor
	Vertex();



	// Constructor with arguments
	/*
		INPUT:	- newCourse - Course object - a course object to create a vertex with
	*/
	Vertex(Course& newCourse);



	// Destructor
	~Vertex();

	Course courseData; // The course's data
	struct Node* head; // A pointer to the beginning of the LLL of nodes
			   // which contains the list of courses which this 
			   // course is a prerequisite for
};



struct Node
{
	// Default constructor
	Node();



	// Destructor
	~Node();

	Vertex* adjacentCourse; // A vertex pointer to the vertex with another course
	Node* next;		// A node pointer to the next base course in this LLL
};



class AdjacencyList
{
public:
	// Adjust the listSize to accommodate for the number of courses
	// Constructor
	/*
		INPUT:	- listSize - int - the maximum number of courses you can add
					   (you can adjust that value here to change)
	*/
	AdjacencyList(const int listSize = 5);



	// Destructor
	~AdjacencyList();



	// Add a course to the adjacency list
	/*
		INPUT:	- newCourse - Course object - a course object to add to the list

		OUTPUT:	- returns int
				-  1 - success
				-  0 - general failure
				- -1 - failure - if the adjacency list is full
				- -2 - failure - if the CRN already exists in the list
	*/
	int addCourse(const Course& newCourse);



	// Because the requirements ask us to display the courses you can 
	// take AFTER taking a certain course, (instead of listing the
	// prerequisites for a course) the parent of the connection 
	// is actually the prerequisiteCRN and the child is the baseCRN
	//
	// Add a connection between courses
	/*
		INPUT:	- prerequisiteCRN - cstring - the CRN of the prerequisite course
			- baseCRN - cstring - the CRN of the base course

		OUTPUT:	- returns int
				-  1 - success
				-  0 - failure - neither base nor prerequisite crn's exist
				- -2 - failure - the base CRN does not exist
				- -3 - failure - the prerequisite CRN does not exist
				- -4 - failure - the list doesn't have enough entries to make a connection
				- -5 - failure - the CRN is being added as its own
	*/
	int addCourseConnection(const char prerequisiteCRN[], const char baseCRN[]);



	// *** Uses a depth-first algorithm ***
	// Display the CRNs of the courses you can take after a certain course is taken
	/*
		INPUT:	- prerequisiteCourse - cstring - the CRN of the prerequisite course

		OUTPUT:	- returns int
				-  1 - success
				-  0 - failure - if the list is empty or there is only 1 entry
				- -1 - failure - if the entry of the CRN has no prerequisites
	*/
	int displayCourseList(const char prerequisiteCourse[]) const;



	// Delete the entire adjacency list and deallocate dynamic memory
	/*
		OUTPUT:	- returns int
				- 0 for failure, 1 for success
	*/
	int deleteAdjacencyList();



	// Checks if the adjacency list is full
	/*
		OUTPUT:	- returns int
				- 0 - the adjacencylist is not full
				- 1 - the adjacencylist is full
	*/
	int isFull();

private:
	Vertex* _adjacencyList;   // a pointer to adjacency list (an array of vertex pointers)
	int	_listSize;	  // the maximum number of objects that can be added to the list
	int	_numCoursesAdded; // the number of courses that have been added to the list


	// Initialize the pointers to null for the class data members
	/*
		OUTPUT:	- returns int - 0 for failure, 1 for success
	*/
	int initialize();



	// Recursively add base course to some course's prerequisites
	/*
		INPUT:	- currentPrerequisiteNode - Node pointer - a node pointer to current prerequisite node
			- newCourse - Vertex pointer - a vertex pointer to the current course vertex

		OUTPUT:	- returns int - 0 for failure, 1 for success

	*/
	int addCourseConnection(Node*& currentPrerequisiteNode, Vertex* newCourse);



	// *** Uses a depth-first algorithm ***
	// Recursively display the list of course bases for the prerequisite
	/*
		INPUT:	- currentNode - Node pointer - pointer to the current Node being displayed

		OUTPUT:	- returns int - 0 for failure, 1 for success
	*/
	int displayCourseList(const Node* currentNode) const;



	// *** Uses a depth-first algorithm ***
	// Recursively display the list of course bases for the prerequisite
	/*
		INPUT:	- currentVertex - Vertex pointer - pointer to the current Vertex being displayed

		OUTPUT: - returns int - 0 for failure, 1 for success
	*/
	int displayCourseList(const Vertex* currentVertex) const;



	// Check to see if a CRN already exists in the course list
	/*
		INPUT:	- aCourse - Course object - a course whose CRN will be looked for in the list

		OUTPUT:	- returns int
				- 0 - the CRN is not in the list
				- 1 - the CRN is in the list
	*/
	int findCRN(const Course& aCourse) const;



	// Recursively check to see if a CRN already exists in the course list and sets a pointer to it
	/*
		INPUT:	- prerequisiteCRN - cstring - the crn to look for in the list
			- prerequisitePtr - Vertex pointer - the pointer to the Vertex containing the
							  matching CRN

		OUTPUT:	- returns int
				- 0 - the CRN is not in the list
				- 1 - the CRN is in the list
	*/
	int findCRN(const char prerequisiteCRN[], Vertex*& prerequisitePtr) const;



	// Recursively check to see if a pair of CRNs is in the course list and if they are
	// to return the pointer to each of them.
	/*
		INPUT:	- prerequisiteCRN - cstring - prerequisite CRN to search for
			- prerequisitePtr - Vertex pointer - pointer to the vertex for that course
			- baseCRN - cstring - base course CRN to search for
			- basePtr - Vertex pointer - poitner to the vertex for that course

		OUTPUT:	- returns int
				-  1 - success - both CRNs were found
				-  0 - failure - neither CRN were in the list
				- -2 - failure - base CRN is not in the list
				- -3 - failure - prerequisite CRN is not in the list
	*/
	int findCRNs(const char prerequisiteCRN[], Vertex*& prerequisitePtr, const char baseCRN[], Vertex*& basePtr);
};