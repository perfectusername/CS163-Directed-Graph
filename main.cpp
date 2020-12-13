#include "adjacencylist.h"

using namespace std;

// Function prototypes
void userInterface(); // User interface
void mainMenuContent(char& input); // Menu options

void addCourseUI(AdjacencyList& anAdjacencyList);
void addCourseConnectionUI(AdjacencyList& anAdjacencyList);
void displayCourseListUI(AdjacencyList& anAdacencyList);
void deleteAdjacencyListUI(AdjacencyList& anAdjacencyList);

void testingUI(AdjacencyList& anAdjacencyList);



int main()
{
	userInterface();

	return 0;
}



// User interface
void userInterface()
{
        AdjacencyList*	anAdjacencyList = new AdjacencyList;
        char	input;

        input = '\0';

        while (quitCheck(input) != true)
        {
                mainMenuContent(input);
                if (quitCheck(input) != true)
                {
                        switch (input)
                        {
                        case '1':
				addCourseUI(*anAdjacencyList);
                                break;
                        case '2':
				addCourseConnectionUI(*anAdjacencyList);
                                break;
                        case '3':
				displayCourseListUI(*anAdjacencyList);
                                break;
			case '4':
				deleteAdjacencyListUI(*anAdjacencyList);
				break;
                        default:
                                cout << "Invalid input. Please try again." << endl << endl;
                        }
                }
        }
	delete anAdjacencyList;
}



// Menu and input
void mainMenuContent(char& input)
{
      char prompt[MAX_CHAR];

	cout << "=========================================================" << endl << endl;
	cout << "Enter a number or 'q' to quit" << endl;
	cout << endl;
	strcpy(prompt, "1. Add a Course\n2. Insert a connection between two course verticies.\n3. Display all of the courses that can be taken after an entered course.\n4. Remove all courses\nq. Quit\n\nPlease enter your menu choice: ");

        takeInput(input, prompt);
	cout << endl << endl;
	cout << "=========================================================" << endl << endl;
}



// Add Alert
void addCourseUI(AdjacencyList& anAdjacencyList)
{
	int	successFlag = 0;

	char 	courseName[MAX_CHAR];
	char	CRN[MAX_CHAR];
	char	description[MAX_CHAR];
	int	credits = 0;
	char	prompt[MAX_CHAR];
	
	Course	courseBuffer;

	if (anAdjacencyList.isFull() != 1)
	{
		strcpy(prompt, "Enter the course name: ");
		takeInput(courseName, prompt);
		
		strcpy(prompt, "Enter the CRN (course reference number): ");
		takeInput(CRN, prompt);

		strcpy(prompt, "Enter a description for the course: ");
		takeInput(description, prompt);

		strcpy(prompt, "Enter the number of credits for the course: ");
		takeInput(credits, prompt);

		courseBuffer.createCourse(courseName, CRN, description, credits);

		successFlag = anAdjacencyList.addCourse(courseBuffer);

		if (successFlag == 1)
		{
			cout << endl << "Add successful!!" << endl << endl;
		}
		else if (successFlag <= 0)
		{
			cout << endl << "Add failed. ";

			if (successFlag == -1)
			{
				cout << "Class list is full." << endl << endl;
			}
			else if (successFlag == -2)
			{
				cout << "CRN already exists in class list." << endl << endl;
			}
		
		}
	}
	else
	{
		cout << "Add failed. Class list is full." << endl << endl;
	}
}



// Search by name
void addCourseConnectionUI(AdjacencyList& anAdjacencyList)
{
	int	successFlag = 0;

	char	prerequisiteCourse[MAX_CHAR];
	char	baseCourse[MAX_CHAR];
	char	prompt[MAX_CHAR];
	
	strcpy(prompt, "Enter the CRN of the course that you want to add a prerequisite to: ");
	takeInput(baseCourse, prompt);

	strcpy(prompt, "Enter the CRN of the prerequisite course: ");
	takeInput(prerequisiteCourse, prompt);

	// 1 for success
	// -2 if base course doesn't exist
	// -3 if prerequisite course doesn't exist
	// 0 if neither courses exist
	successFlag = anAdjacencyList.addCourseConnection(prerequisiteCourse, baseCourse);

	if (successFlag <= 0)
	{
		cout << endl;
		cout << "Adding prerequisite failed." << endl;
		
		if (successFlag == -5)
		{
			cout << "Cannot set a course as its own prerequisite." << endl;
		}
		if (successFlag == -4)
		{
			cout << "Not enough items in the course list.";
			cout << "Must have added at least 2 courses." << endl;
		}	
		if (successFlag == -3)
		{
			cout << "The prerequisite CRN \"";
			cout << prerequisiteCourse << "\" does not exist." << endl;
		}
		if (successFlag == -2)
		{
			cout << "The base CRN \"";
			cout << baseCourse << "\"does not exist." << endl;
		}
		if (successFlag == 0)
		{
			cout << "Both the prerequisite and base CRNs do not exist." << endl;
		}
		cout  << endl;
	}
	else
	{
		cout << endl;
		cout << "Success!!" << endl;
		cout << "Course " << baseCourse << " added as a base for course " << prerequisiteCourse;
		cout << endl;
	
	}
}




void displayCourseListUI(AdjacencyList& anAdjacencyList)
{
	int	successFlag = 0;
	char	prerequisiteCourse[MAX_CHAR];
	char	prompt[MAX_CHAR];
	
	strcpy(prompt, "Enter a course CRN to see what courses you can take after it's completed: ");
	takeInput(prerequisiteCourse, prompt);
	
	successFlag = anAdjacencyList.displayCourseList(prerequisiteCourse);

	if (successFlag == 0)
	{
		cout << endl;
		cout << "Error. That course CRN does not exist." << endl;
		cout << endl;
	}
	else if (successFlag == -1)
	{
		cout << endl;
		cout << "Error. That course CRN is not a prerequisite for any other courses." << endl;
		cout << endl;
	}
}



void deleteAdjacencyListUI(AdjacencyList& anAdjacencyList)
{
	int	successFlag = 0;
	
	successFlag = anAdjacencyList.deleteAdjacencyList();

	if (successFlag == 0)
	{
		cout << endl;
		cout << "Remove failed. Course list is already empty.";
		cout << endl;
	}
	if (successFlag == 1)
	{
		cout << "Success!! Course list cleared.";
		cout << endl << endl;
	}
}
