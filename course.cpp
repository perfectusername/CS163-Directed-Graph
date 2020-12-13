#include "course.h"


using std::endl;
using std::cout;

Course::Course()
{
	_courseName = nullptr;
	_CRN = nullptr;
	_description = nullptr;
	_credits = 0;
}


Course::Course(const Course& newCourse)
{
	_courseName = nullptr;
	_CRN = nullptr;
	_description = nullptr;
	_credits = 0;

	createCourse(newCourse._courseName,
			newCourse._CRN,
			newCourse._description,
			newCourse._credits);
}



Course::Course(const char courseName[], 
		const char CRN[], 
		const char description[], 
		const int credits)
{
	createCourse(courseName, CRN, description, credits);
}



Course::~Course()
{
	deleteCourse();
}



int Course::deleteCourse()
{
	int successValue = 0;

	if (_courseName != nullptr)
	{
		delete[] _courseName;
		_courseName = nullptr;
	}

	if (_CRN != nullptr)
	{
		delete[] _CRN;
		_CRN = nullptr;
	}

	if (_description != nullptr)
	{
		delete[] _description;
		_description = nullptr;
	}

	if ((_courseName == nullptr) && (_CRN == nullptr) && (_description == nullptr))
	{
		successValue = 1;
	}

	return successValue;
}



int Course::createCourse(const char courseName[], const char CRN[], const char description[], const int credits)
{
	int successValue = 0;

	successValue = deleteCourse();

	if (successValue == 1)
	{
		_courseName = new char[strlen(courseName) + 1];
		strcpy(_courseName, courseName);

		_CRN = new char[strlen(CRN) + 1];
		strcpy(_CRN, CRN);

		_description = new char[strlen(description) + 1];
		strcpy(_description, description);

		_credits = credits;

		successValue = 1;
	}

	return successValue;
}



int Course::createCourse(const Course& sourceCourse)
{
	return createCourse(sourceCourse._courseName,
				sourceCourse._CRN,
				sourceCourse._description,
				sourceCourse._credits);
}



int Course::copyCourse(const Course& sourceCourse)
{
	int successValue = 0;

	successValue = deleteCourse();

	if (successValue == 1)
	{
		successValue = createCourse(sourceCourse);
	}

	return successValue;
}



int Course::displayCRN() const
{
	int successValue = 0;

	if (_CRN != nullptr)
	{
		cout << _CRN;
		successValue = 1;
	}

	return successValue;
}



int Course::displayCourse() const
{
	int successValue = 0;

	if ((_courseName != nullptr) && (_CRN != nullptr) && (_description != nullptr))
	{
		cout << "Course name: " << _courseName << endl;
		cout << "CRN: " << _CRN << endl;
		cout << "Course Description: " << _description << endl;
		cout << _credits << " credits" << endl;
		cout << endl;

		successValue = 1;
	}

	return successValue;
}



int Course::compareCRN(const Course& aCourse) const
{
	return strcmp(aCourse._CRN, _CRN);
}



int Course::compareCRN(const char CRN[]) const
{
	return strcmp(CRN, _CRN);
}
