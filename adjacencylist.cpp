#include "adjacencylist.h"

const int DEFAULT_TABLE_SIZE = 10;


using std::cout;
using std::endl;

Vertex::Vertex()
{
	head = nullptr;
}



Vertex::Vertex(Course& newCourse)
{
	courseData.copyCourse(newCourse);
	head = nullptr;
}



Vertex::~Vertex()
{
	// We don't need to deallocate courseData because it was 
	// not dynamically allocated
	Node* currentNode;

	while (head != nullptr)
	{
		currentNode = head;
		head = head->next;
		delete currentNode;
		currentNode = nullptr;
	}
}



Node::Node()
{
	adjacentCourse = nullptr;
	next = nullptr;
}



Node::~Node()
{
	adjacentCourse = nullptr;
	next = nullptr;
}



AdjacencyList::AdjacencyList(const int listSize)
{
	_listSize = listSize;
	_numCoursesAdded = 0;

	initialize();
}



AdjacencyList::~AdjacencyList()
{
	deleteAdjacencyList();
}



int AdjacencyList::deleteAdjacencyList()
{
	int successValue = 0;

	if (_adjacencyList != nullptr)
	{
		delete[] _adjacencyList;
		_adjacencyList = nullptr;
		successValue = 1;
	}

	_numCoursesAdded = 0;

	return successValue;
}



int AdjacencyList::initialize()
{
	int successValue = 0;
	int i;
	_adjacencyList = new Vertex[_listSize];
	Vertex* currentVertex = _adjacencyList;

	// Because there is no remove function, the first item 
	// in the list can't be removed,
	// so checking if it's there will let us know if the list is empty
	if (_adjacencyList != nullptr)
	{
		for (i = 0; i < _listSize; ++i)
		{
			currentVertex->head = nullptr;
			if (currentVertex->head == nullptr)
			{
				successValue = 1;
			}
			++currentVertex;
		}
	}
	
	return successValue;
}



int AdjacencyList::addCourse(const Course& newCourse)
{
	int successValue = 0;

	// If the list is not initialized, initialize the list
	if (_adjacencyList == nullptr)
	{
		successValue = initialize();
	}
	// If the course list is full return an error of -1	
	else if (_numCoursesAdded >= _listSize)
	{
		successValue = -1;
	}
	// Duplicate CRN are not allowed. Check the CRNs in the course list before 
	// attempting to add
	else if (findCRN(newCourse) != 0)
	{
		successValue = -2;
	}
	

	// If the list is now initialized and it isn't full	
	// Add the course to the list
	if ((_numCoursesAdded < _listSize) && (successValue >= 0))
	{
		_adjacencyList[_numCoursesAdded].courseData.copyCourse(newCourse);

		++_numCoursesAdded;
		successValue = 1;
	}

	return successValue;
}



// ** NOTE ** 	I do not check here whether or not a feedback loop of course 
//		prerequisites has been made. If course A is a prerequisite for course
//		B, then course B should not be made a prerequisite for course A.
//		Because this data represents a real structure of
//		prerequisites, this situation should never actually happen, so I have not
//		coded anything to check for or prevent it. It is left up to the
//		client to correctly enter their data, or there will be an infinite
//		loop when the courses are displayed.
// 		
// Because we are listing the classes you can take AFTER taking another course
// (and not the prerequisites for a certain course), the parent will be the prerequisite
// and the child will be the base, even though this is a little unintuitive.
int AdjacencyList::addCourseConnection(const char prerequisiteCRN[], const char baseCRN[])
{
	int successValue = 0;
	int comparisonValue;
	Vertex* prerequisitePtr = nullptr;
	Vertex* basePtr = nullptr;


	comparisonValue = strcmp(prerequisiteCRN, baseCRN);

	// If the prerequisite and base crn match then return failure of -5
	if (comparisonValue != 0)
	{
		if (_numCoursesAdded >= 2)
		{	
			// findCRNs:
			// Returns 1 if both are in the list and pointers are linked to them
			// Returns 0 if neither course is in the list
			// Returns -2 if only the base course doesn't exist
			// Returns -3 if only the prerequisite course doesn't exist
			successValue = findCRNs(prerequisiteCRN, prerequisitePtr, baseCRN, basePtr);

			if (successValue == 1)
			{

				successValue = addCourseConnection(prerequisitePtr->head, basePtr);
			}
		}
		// Otherwise there are not enough nodes to make a connection
		else
		{
			successValue = -4;
		}
	}
	else
	{
		successValue = -5;
	}

	return successValue;
}




// Recursively insert CRN into the adjacentCourse list in sorted ascending order
// because we'd want to see the lower level CRN courses before the upper level ones
int AdjacencyList::addCourseConnection(Node*& currentNode, Vertex* newVertex)
{
	int successValue = 0;
	int comparisonValue;
	Node* newNode;

	// Base case 1: if we're at the end of the list and 
	// currentNode is nullptr
	if (currentNode == nullptr)
	{
		currentNode = new Node;
		currentNode->adjacentCourse = newVertex;
		successValue = 1;
	}
	else
	{
		comparisonValue = currentNode->adjacentCourse->courseData.compareCRN(newVertex->courseData);
		
		// Base case 2: if we're at the right location in the list
		// then our newCourse will be larger than currentNode's course
		if (comparisonValue > 0)
		{
			newNode = new Node;
			newNode->adjacentCourse = newVertex;
			newNode->next = currentNode->next;
			currentNode->next = newNode;
		}
		// Otherwise call the function again on the next node
		else if (comparisonValue < 0)
		{
			successValue = addCourseConnection(currentNode->next, newVertex);
		}
	}

	return successValue;
}



int AdjacencyList::displayCourseList(const char prerequisiteCourse[]) const
{
	int successValue = 0;
	Vertex* prerequisitePtr = nullptr;

	// If the course list has less than 2 entries there can't be connection
	// between two of them.
	if (_numCoursesAdded > 1)
	{
		successValue = findCRN(prerequisiteCourse, prerequisitePtr);

		if (successValue == 1)
		{
			if (prerequisitePtr->head != nullptr)
			{
				successValue = prerequisitePtr->courseData.displayCRN();
				cout << " -> ";
				successValue = displayCourseList(prerequisitePtr->head);
				cout << endl;
			}
			else
			{
				successValue = -1;
			}

		}
	}

	return successValue;
}



// This will have the highest courses displayed first, but it will also
// follow depth-first traversal for the extra credit points
int AdjacencyList::displayCourseList(const Node* currentNode) const
{
	int successValue = 0;

	if (currentNode != nullptr)
	{
		// Base case 1: currentNode is null
		while (currentNode != nullptr)
		{
			// Depth first:
			// For each node go to the postrequisite first,
			successValue = displayCourseList(currentNode->adjacentCourse);
			
			// Then go through the edge list of that vertex until you're
			// out of things to display using tail recursion.

			currentNode = currentNode->next;
		}
	}

	return successValue;
}



int AdjacencyList::displayCourseList(const Vertex* currentVertex) const
{
	int successValue = 0;

	successValue = currentVertex->courseData.displayCRN();

	// Base case 1: currentVertex is null
	if (currentVertex->head != nullptr)
	{
		cout << " -> ";
		successValue = displayCourseList(currentVertex->head);
	}

	return successValue;
}



// isFullFlag returns 0 if the adjacency list is not full and 1 if it is.
int AdjacencyList::isFull()
{
	int isFullFlag = 0;

	if (_numCoursesAdded >= _listSize)
	{
		isFullFlag = 1;
	}

	return isFullFlag;
}



// Returns 0 if course is not found in the list
// Returns 1 if course is found in the list
int AdjacencyList::findCRN(const Course& aCourse) const
{
	int i;
	int successValue = 0;

	for (i = 0; ((successValue != 1) && (i < _numCoursesAdded)); ++i)
	{
		// compareCRN returns 0 if match is found.
		if (_adjacencyList[i].courseData.compareCRN(aCourse) == 0)
		{
			successValue = 1;
		}
	}

	return successValue;
}



int AdjacencyList::findCRN(const char prerequisiteCRN[], Vertex*& prerequisitePtr) const
{
	int i;
	int successValue = 0;

	for (i = 0; ((successValue != 1) && (i < _numCoursesAdded)); ++i)
	{
		if (_adjacencyList[i].courseData.compareCRN(prerequisiteCRN) == 0)
		{
			prerequisitePtr = &_adjacencyList[i];
			successValue = 1;
		}
	}

	return successValue;
}



// Returns 1 if both are found
// Returns 0 if neither course is in the list
// Returns -2 if only the base course doesn't exist
// Returns -3 if only the prerequisite course doesn't exist
int AdjacencyList::findCRNs(const char prerequisiteCRN[], Vertex*& prerequisitePtr,
			    const char baseCRN[], Vertex*& basePtr)
{
	int i = 0;
	int successValue = 0;
	int prerequisiteComparison = 0;
	int baseComparison = 0;

		
	// If both are found successValue = 1
	// If only prerequisite is found (base is still missing), successValue = -2
	// If only base is found (prerequisite is still missing), successValue = -3


	// Only run this if success value is not 1 and we haven't reached the end
	while ((successValue != 1) && (i < _numCoursesAdded))
	{
		// If we already found the prerequisite match earlier... 
		// successValue will be -2
		if (successValue != -2)
		{
			// Compare the CRNs
			prerequisiteComparison = _adjacencyList[i].courseData.compareCRN(prerequisiteCRN);
			// If they match...
			if (prerequisiteComparison == 0)
			{
				// Set the prerequisite poitner to the item
				prerequisitePtr = &_adjacencyList[i];
				
				// If this is the first match found then
				// successValue will still be 0, so just set it to -2
				// to indicate we've found the prerequisite match
				if (successValue == 0)
				{
					successValue = -2;
				}
				// If successValue is -3, then we have found
				// a match for the base earlier, so set it
				// to 1 to indicate we've found them both.
				else if (successValue == -3)
				{
					successValue = 1;
				}
			}
		}

		// If we already found the base match earlier...
		// successValue will be -3
		if (successValue != -3)
		{
			// Compare the CRNs
			baseComparison = _adjacencyList[i].courseData.compareCRN(baseCRN);
			// If they match...
			if (baseComparison == 0)
			{
				// Set the base pointer to the item
				basePtr = &_adjacencyList[i];

				// If this is the first match found then
				// successValue will still be 0, so jut set it to -3
				// to indicate we've found the base match
				if (successValue == 0)
				{
					successValue = -3;
				}
				// If successValue is -2, then we have found
				// a match for the prerequisite earlier, so set it to 1
				// to indicate that we've found them both
				else if (successValue == -2)
				{
					successValue = 1;
				}
			}
		}
		
		++i;
	}

	return successValue;
}
