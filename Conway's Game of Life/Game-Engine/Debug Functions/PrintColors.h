/*****************************************************************************
**************
* Programmer: Conner Howard
* File: Print Colors
* Date: 09/13/2023
* Description: list of printf coloring functions
* Supported Colors:
*	- Black
*	- Red
* 	- Green
* 	- Yellow
* 	- Blue
* 	- Purple
* 	- Cyan
* 	- White
*	- Reset
******************************************************************************
*************/
#ifndef PRINT_COLORS_HPP
#define PRINT_COLORS_HPP

#include <stdio.h>

namespace PrintfColor
{
	/* Function Name: Reset Color
	* Description: Sets the printf() color back to default output color
	* Inputs: none
	* Preconditions: (Prefered) another color previously called
	* Outputs: Changes the color of the printf() output to normal
	* Returns: none
	* Postconditions: none
	*/
	inline void reset()
	{
		printf("\033[0m");
	};

	/* Function Name: Set Color Black
	* Description: Sets following printf() outputs to color [BLACK]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [BLACK]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void black()
	{
		printf("\033[0;30m");
	};


	/* Function Name: Set Color Red
	* Description: Sets following printf() outputs to color [RED]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [RED]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void red()
	{
		printf("\033[0;31m");
	};

	/* Function Name: Set Color Green
	* Description: Sets following printf() outputs to color [GREEN]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [GREEN]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void green()
	{
		printf("\033[0;32m");
	};

	/* Function Name: Set Color Yellow
	* Description: Sets following printf() outputs to color [YELLOW]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [YELLOW]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void yellow()
	{
		printf("\033[33;1m");
	};

	/* Function Name: Set Color Blue
	* Description: Sets following printf() outputs to color [BLUE]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [BLUE]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void blue()
	{
		printf("\033[0;34m");
	};

	/* Function Name: Set Color Purple
	* Description: Sets following printf() outputs to color [PURPLE]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [PURPLE]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void purple()
	{
		printf("\033[0;35m");
	};

	/* Function Name: Set Color Cyan
	* Description: Sets following printf() outputs to color [CYAN]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [CYAN]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void cyan()
	{
		printf("\033[0;36m");
	};

	/* Function Name: Set Color White
	* Description: Sets following printf() outputs to color [WHITE]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [WHITE]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void white()
	{
		printf("\033[0;37m");
	};

	/* Function Name: Set Color Gray
	* Description: Sets following printf() outputs to color [GRAY]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [GRAY]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void gray()
	{
		printf("\033[30;1m");
	};

	/* Function Name: Set Color Orange
	* Description: Sets following printf() outputs to color [ORANGE]
	* Inputs: none
	* Preconditions: none
	* Outputs: any following prinf() calls will have color [ORANGE]
	* Returns: none
	* Postconditions: call printf()
	*/
	inline void orange()
	{
		printf("\033[31;1m");
	};

	/* Function Name: Avaliable Colors
	* Description: Prints a sample of all avaliable color commands
	* Inputs: none
	* Preconditions: none
	* Outputs: Shows all calls with their applied color
	* Returns: none
	* Postconditions:
	*/
	inline void avaliableColors()
	{
		printf("- Avaliable Colors -\n");
		printf("( all calls require 'PrintfColor::' namespace)\n");
		PrintfColor::white();
		printf("white() \n");
		PrintfColor::gray();
		printf("gray()\n");
		PrintfColor::black();
		printf("black() \n");
		PrintfColor::blue();
		printf("blue()\n");
		PrintfColor::cyan();
		printf("cyan()\n");
		PrintfColor::green();
		printf("green()\n");
		PrintfColor::orange();
		printf("orange()\n");
		PrintfColor::purple();
		printf("purple()\n");
		PrintfColor::red();
		printf("red()\n");
		PrintfColor::yellow();
		printf("yellow()\n");
		PrintfColor::reset();
		printf("reset()\n");
		

		printf("----- end -----\n");
	};

}

#endif