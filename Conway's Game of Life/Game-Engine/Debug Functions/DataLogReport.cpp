/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "DataLogReport.hpp"

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
	void dataLog::generateLogReport(const dataLog::ReportType& logTag, const std::string& message)
	{
		// define the name of the log report
		// get current time
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		// convert to time_t (c-style)
		std::time_t time = std::chrono::system_clock::to_time_t(now);
		// convert to easy-to-use time struct
		std::tm timeInfo;
		localtime_s(&timeInfo, &time);

		// get the date and time components
		int year = timeInfo.tm_year + 1900;		// Years since 1900
		int month = timeInfo.tm_mon + 1;		// Months (0-11)
		int day = timeInfo.tm_mday;				// Day of the month (1-31)
		int hour = timeInfo.tm_hour;			// Hours (0-23)
		int minute = timeInfo.tm_min;			// Minutes (0-59)
		int second = timeInfo.tm_sec;			// Seconds (0-59)

		// generate file name
		std::string reportType = dataLog::getReportTypeString(logTag);
		std::string filename = "Log Report_" + std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + "_" + \
			std::to_string(hour) + "-" + std::to_string(minute) + "." + std::to_string(second) + "_" + reportType + ".txt";

		// open the file
		std::cout << filename << std::endl;
		std::ofstream file(filename, std::ios::out);

		if (file.is_open()) {
			// output the data to the file
			file << "================= Begin Log Report =================" << std::endl;
			file << "Date (YYYY/MM/DD): " << year << "/" << month << "/" << day << std::endl;
			file << "Time (24hr:min:sec): " << hour << ":" << minute << ":" << second << std::endl;
			file << "Report Type: " << reportType << std::endl;
			file << "Additional Information:" << std::endl;
			file << message << std::endl;
			file << "================== End Log Report ==================" << std::endl << std::endl;

			// output a confirmation of log creation
			std::cout << "[" << reportType << "] Report Successfully Generated" << std::endl;
		}
		else
		{
			std::cout << "Failed to generate report file" << std::endl;
		}
	}



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
	std::string dataLog::getReportTypeString(const dataLog::ReportType& logTag)
	{
		// define output
		std::string output;

		switch (logTag)
		{
		case dataLog::ReportType::DEBUG:
			output = "Debug";
			break;
		case dataLog::ReportType::TEST:
			output = "Test";
			break;
		default:
			output = "TypeUndefine";
			break;
		}

		return output;
	}





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

