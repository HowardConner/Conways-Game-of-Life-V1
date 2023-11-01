/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* File: Master Header File
* Date: Contains all necessary libraries and helful boilerplate for the project
* Description:
******************************************************************************
*************/
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"


using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;

using sf::Vector2f;

namespace BP
{

	/* Function Name: String Tokenizer
	* Description: Takes and inputed string and returns a string type token up to a delimiter or end
	*	of the string. Will modify and delete the returned elements from the source string
	* Inputs: Reference to string, Delim char
	* Preconditions:
	* Outputs: string from beginning of scorce to delim or end of string, whichever comes first,
	*	modified source string that has the above removed from it (including delim)
	* Returns: string from beginning of scorce to delim or end of string, whichever comes first.
	*	If delim found, removes the delim char
	* Postconditions:
	*/
	static std::string stringTok(std::string &source, const std::string &delim)
	{
		// define variables
		size_t pos = 0;
		std::string token;

		// locate the first delim
		pos = source.find(delim);

		if (pos == std::string::npos)
		{
			// delim not found, return whole string and axe the source
			token = source;
			source.erase();
		}
		else
		{
			// delim found, generate temp substring
			token = source.substr(0, pos);
			source.erase(0, pos + delim.length());
		}

		return token;
	};

	/* Function Name: Add Rect Shape Outline
	* Description: Adds Outline to rectangle shape of the designated weight and color.
	*	resizes shape to fit in original area
	* Inputs: shape to modify, weight of outline, color of outline
	* Preconditions: none
	* Outputs: output RectangleShape modified with outline
	* Returns: none
	* Postconditions:
	*/
	static void addRectOutline(sf::RectangleShape& output, const unsigned& weight, const sf::Color& outlineColor = sf::Color::Black)
	{
		// apply outline color and weight
		output.setOutlineThickness(weight);
		output.setOutlineColor(outlineColor);

		// recenter shape with new outline
		// remove the area now occupied by the outline
		output.setSize(sf::Vector2f(output.getSize().x - 2 * weight, output.getSize().y - 2 * weight));
		// move position slightly to accout for new area on top and left sides
		output.setPosition(sf::Vector2f(output.getPosition().x + weight, output.getPosition().y + weight));
	}

	/* Function Name: Remove Outline from Rectangle Shape
	* Description: Removes any outlines of supplied shape and fixes size
	* Inputs: shape to have its outline removed
	* Preconditions: shape has outline applied
	* Outputs: output RectangleShape without outline
	* Returns: none
	* Postconditions: none
	*/
	static void removeRectOutline(sf::RectangleShape& output)
	{
		// guard code
		if (output.getOutlineThickness() != 0.0)
		{
			// shape has outline applied
			// record outline weight
			float weight = output.getOutlineThickness();

			// resize to account for not having a boarder
			output.setSize(sf::Vector2f(output.getSize().x + 2 * weight, output.getSize().y + 2 * weight));
			// move shape to account for no longer having an outline
			output.setPosition(sf::Vector2f(output.getPosition().x - weight, output.getPosition().y - weight));

			// remove outline
			output.setOutlineThickness(0.0);
		}
	}
}
