/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef TICK_CLOCK_HPP
#define TICK_CLOCK_HPP

#include <iostream>

#include "SFML/Graphics.hpp"


class TickClock
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	TickClock(const unsigned TicksPerSecond = 10)
	{
		this->mTicksPerSecond = TicksPerSecond;
		this->mSecPerTick = 1.0 / TicksPerSecond;
		this->mDeltaT = 0;
	};

	// copy constructor
	TickClock(const TickClock& copy)
	{
		this->mTicksPerSecond = copy.mTicksPerSecond;
		this->mSecPerTick = copy.mSecPerTick;
		this->mDeltaT = copy.mDeltaT;
	}

	// copy assignment operator
	TickClock& operator=(const TickClock& rhs)
	{
		this->mTicksPerSecond = rhs.mTicksPerSecond;
		this->mSecPerTick = rhs.mSecPerTick;
		this->mDeltaT = rhs.mDeltaT;
	}

	// destructor
	~TickClock()
	{
		// nothing for now
	};


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters
	void setTicksPerSecond(const unsigned& newTicksPerSecond)
	{
		// update Ticks per Second, then update Fraction of seconds per tick
		this->mTicksPerSecond = newTicksPerSecond;
		this->mSecPerTick = 1.0 / newTicksPerSecond;
	}


	// getters
	// check the currently set number of ticks in a second
	inline unsigned getTicksPerSeconds() const
	{
		return this->mTicksPerSecond;
	}
	// dev tool for checking correct calculations are being made
	inline float getSecondsPerTick() const
	{
		return this->mSecPerTick;
	}


	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Update Tick Clock
	* Description: Updates the deltaT since last call and sets a flag to determine if a tick update
	*	should be preformed due to this update. When calculating deltaT, only accounts for one tick at
	*	a time. This means that if a long time has passed since updates, it will return true for multiple
	*	calls. Hence the precondition
	* Precondition: Any time that this function is called should involve a loop to clear it of all
	*	ticks. This allows the program to run indipendent of framerate
	* Inputs: none
	* Outputs: True if an update is needed, false otherwise.
	*/
	bool update()
	{
		// define variables
		bool result = false;

		// update the delta figure
		mDeltaT += mClock.getElapsedTime().asSeconds();

		// check if enough time has passed to trigger a tick
		if (mDeltaT >= mSecPerTick)
		{
			// remove one tick unit of time from delta and return true
			mDeltaT = mDeltaT - mSecPerTick;

			result = true;
		}
		
		// reset the clock for the next loop
		this->mClock.restart();

		return result;
	}


private:
	unsigned mTicksPerSecond;	// Number of Ticks in a second
	float mSecPerTick;			// Fraction of a second that each tick represents
	float mDeltaT;				// cummulative time in seconds. Generated by applying differences between update calls.

	sf::Clock mClock;			// internal clock for generating tick readout

	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //



};

// --------------------------------------------------------------------------------------------- //
//									non - Member Functions
// --------------------------------------------------------------------------------------------- //


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

#endif