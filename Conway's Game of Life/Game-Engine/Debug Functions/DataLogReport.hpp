/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef DATA_LOG_REPORT_HPP
#define DATA_LOG_REPORT_HPP

#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <fstream>

namespace dataLog
{
	// --------------------------------------------------------------------------------------------- //
	//									Log Types Enum
	// --------------------------------------------------------------------------------------------- //
	enum ReportType {
		DEBUG = 1,
		TEST
	};


	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* Function Name: Generate Log Report
	* Description: Creates a "LogReports.txt" if not found, then generates a message depending on the
	*	ReportType specifier. Always includes the date and time of the generated log report
	* Inputs: Enum of report type, string of optional content for added contexted of reason for log
	*	report
	* Preconditions:
	* Outputs: Generates a Log.txt file or appends to the existing one
	* Returns:
	* Postconditions:
	*/
	void generateLogReport(const ReportType& logTag, const std::string& message);



	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* Function Name: Get String of Report Type
	* Description: Generates a string corresponding to the Report Type variable
	* Inputs: the log type to get string for
	* Preconditions:
	* Outputs: string conversion of the report type enum
	* Returns: string conversion of the report type enum
	* Postconditions:
	*/
	std::string getReportTypeString(const ReportType& logTag);





	/* mFunction Name:
	* Description:
	* Inputs:
	* Outputs:
	*/


	/* Function Name:
	* Description:
	* Inputs:
	* Preconditions:
	* Outputs:
	* Returns:
	* Postconditions:
	*/
};

#endif // !LOG_REPORT_HPP