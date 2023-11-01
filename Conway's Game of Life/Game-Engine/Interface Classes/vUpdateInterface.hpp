/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef VIRTUAL_UPDATE_INTERFACE_HPP
#define VIRTUAL_UPDATE_INTERFACE_HPP



class UpdateInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	UpdateInterface()
	{
		this->mNeedUpdate = true;
	}

	// copy constructor
	UpdateInterface(const UpdateInterface& copy)
	{
		this->mNeedUpdate = copy.mNeedUpdate;
	}

	// copy assingment operator
	UpdateInterface& operator=(const UpdateInterface& rhs)
	{
		this->mNeedUpdate = rhs.mNeedUpdate;
	}

	// destructor
	virtual ~UpdateInterface() {}


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //




	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Virtual Update Function
	* Description: Neccessary update function. It is self contained and handles
	* Inputs:
	* Outputs:
	*/
	virtual void update() = 0;

protected:
	bool mNeedUpdate = true;
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