/*****************************************************************************
**************
* Programmer: Conner Howard
* Project:
* Date:
* Description: 
******************************************************************************
*************/
#ifndef VECTOR_GRID_HPP
#define VECTOR_GRID_HPP

#include <iostream>
#include <array>
#include <algorithm>

using std::array;


/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/
template <class U>
U* newArray(const size_t& X, const size_t& Y, const U& defaultData)
{
	// define variables
	short count = 0;
	U* pMem = nullptr;

	// loop until you get a pointer or timeout
	while (pMem == nullptr && count < 20)
	{
		// allocate new pointer
		pMem = new U[X * Y];

		count++;
	}

	if (pMem != nullptr)
	{
		for (count = 0; count < (X * Y); count++)
		{
			pMem[count] = defaultData;
		}
	}

	return pMem;
}

///* Function Name:
//* Description:
//* Inputs:
//* Preconditions:
//* Outputs:
//* Returns:
//* Postconditions:
//*/
//template <class U>
//inline void deleteArray(const U* inArray)
//{
//	// free the original array
//	delete[] inArray;
//}

template <class U>
inline void copyArray(const U* src, U* dest, const unsigned& maxIndex)
{
	for (unsigned index = 0; index < maxIndex; index++)
	{
		dest[index] = src[index];
	}
}


template <class T>
class Vector_Grid
{
public:
	struct size_t_pair
	{
		size_t x;
		size_t y;
	};
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	/* Precondition:
	*	Type <T> must support overloaded == operator (comparison)
	*	Type <T> must support overloaded = operator  (assignment)
	*/
	Vector_Grid(const T& nullData);

	// copy constructor
	Vector_Grid(const Vector_Grid& copy);

	// copy assignment
	Vector_Grid& operator=(const Vector_Grid& lhs);

	// destructor
	~Vector_Grid();


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters
	// redefine the size of the array, Dimensions: (X, Y)
	inline void setSize(const size_t& sizeX, const size_t& sizeY);
	// Access specifice sell to set data
	void set(const T& newData, const size_t& whereX, const size_t& whereY);
	// sets all data in vector to the "newData"
	void setAll(const T& newData);
	// Access and override current NullData
	void setNullData(const T& newNullData);

	// getters
	// access at (x,y)
	inline T& at(const size_t& whereX, const size_t& whereY) const;
	// access at (x,y)
	inline T& operator()(const size_t& whereX, const size_t& whereY) const;
	// access via index operator (index)
	inline T& operator()(const size_t& index) const;
	// remove element (replace with nullData) at (x,y)
	inline T remove(const size_t& whereX, const size_t& whereY);
	// get the current value of the NullData
	inline const T& getNullData() const;
	// returns the size of the array in (x,y) dimensional values
	inline typename size_t_pair size() const;
	// get the total length of the 1d array
	inline size_t getLength() const;
	// returns the value of number of full cells (index length)
	inline size_t getIndexCount() const;
	// returns the memory size of array (in bytes)
	inline unsigned sizeofArray() const;

	// checks
	// is list empty
	inline bool empty() const;
	// is cell considered empty (equal to null data)
	inline bool empty(const size_t& whereX, const size_t& whereY) const;
	// Is point in bounds of grid
	inline bool isInArray(const size_t& whereX, const size_t& whereY) const;

	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* Function Name: Copy array
	* Description: copies the data from src to dest, resizing dest as needed.
	*	if dest is larger, shrinks it, if dest is smaller, grows it
	* Inputs: src arrGrid, destination arrGrid
	* Preconditions:
	* Outputs: none
	* Returns: none
	* Postconditions:
	*/
	void copyArrayData(const Vector_Grid<T>& src);

	/* Function Name: Fill Array with Data
	* Description: Fills entire array with the supplied newData, overwriting any
	*	previous values. Does not modify the nullData Set.
	* Inputs: New data to overwrite the array
	* Preconditions: none
	* Outputs: array filled with newData
	* Returns: none
	* Postconditions:
	*/
	void fill(const T& newData);

	/* Function Name: Clear Array
	* Description: Sets all array values to the NullData set. Action discards all
	*	overwritten data
	* Inputs: none
	* Preconditions:
	* Outputs: array_grid now set entirely to NullData
	* Returns: none
	* Postconditions:
	*/
	void clear();

private:
	size_t_pair mSize;
	size_t mCurrentlyOccupied;
	T mNullData;
	T* mData = nullptr;
	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: resize array
	* Description: resizes the array off of the given new size. keeps data depending on the chosen option
	*	default deletes the data on a resize
	* Inputs: new index count size of the array, T/F to copy the old data over or to wipe it
	* Outputs: none
	*/
	void resize(const size_t_pair& newSize, const bool& clear = false);


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


// --------------------------------------------------------------------------------------------- //
// --------------------------------------------------------------------------------------------- //
//										Function Definitions
// --------------------------------------------------------------------------------------------- //
// --------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //
// constructor
template <class T>
Vector_Grid<T>::Vector_Grid(const T& nullData) : mNullData(nullData)
{
	this->mSize.x = 0;
	this->mSize.y = 0;
	this->mCurrentlyOccupied = 0;
}

// copy constructor
template <class T>
Vector_Grid<T>::Vector_Grid(const Vector_Grid& copy) : mNullData(copy.mNullData)
{
	this->mSize.x = copy.mSize.x;
	this->mSize.y = copy.mSize.y;
	this->mCurrentlyOccupied = copy.mCurrentlyOccupied;

	this->copyArrayData(copy);
}

// copy assignment
template <class T>
Vector_Grid<T>& Vector_Grid<T>::operator=(const Vector_Grid& lhs)
{
	this->mSize.x = lhs.mSize.x;
	this->mSize.y = lhs.mSize.y;
	this->mCurrentlyOccupied = lhs.mCurrentlyOccupied;
	this->mNullData = lhs.mNullData;

	this->copyArrayData(lhs);
}

// destructor
template <class T>
Vector_Grid<T>::~Vector_Grid()
{
	// free the data if its not in use
	if (this->mData != nullptr)
	{
		delete[] this->mData;
	}
}

// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// setters
template <class T>
inline void Vector_Grid<T>::setSize(const size_t& sizeX, const size_t& sizeY)
{
	// call resize
	resize({ sizeX, sizeY }, false);
}

template <class T>
void Vector_Grid<T>::set(const T& newData, const size_t& whereX, const size_t& whereY)
{
	if (at(whereX, whereY) == this->mNullData)
	{
		this->mCurrentlyOccupied++;
	}
	at(whereX, whereY) = newData;
}

// Set all data in array to newData
template <class T>
void Vector_Grid<T>::setAll(const T& newData)
{
	for (int index = 0; index < getLength(); index++)
	{
		this->mData = newData;
	}
}

template <class T>
void Vector_Grid<T>::setNullData(const T& newNullData)
{
	// replace all old null data with new null data
	for (int index = 0; index < this->getIndexCount(); index++)
	{
		if (this->mData[index] == this->mNullData)
		{
			// has null data, replace with new
			this->mData[index] = newNullData;
		}
	}

	// overwrite current null data
	this->mNullData = newNullData;
}

// getters
template <class T>
inline T& Vector_Grid<T>::at(const size_t& whereX, const size_t& whereY) const
{
	return this->mData[whereY * mSize.x + whereX];
}

template <class T>
inline T& Vector_Grid<T>::operator()(const size_t& whereX, const size_t& whereY) const
{
	return at(whereX, whereY);
}


template <class T>
inline T& Vector_Grid<T>::operator()(const size_t& index) const
{
	return this->mData[index];
}


template <class T>
inline T Vector_Grid<T>::remove(const size_t& whereX, const size_t& whereY)
{
	// check data and make return value
	T temp = this->at(whereX, whereY);
	if (temp != this->mNullData)
	{
		this->mCurrentlyOccupied--;
		at(whereX, whereY) = this->mNullData;
	}

	// return result
	return temp;
}

template <class T>
inline const T& Vector_Grid<T>::getNullData() const
{
	return this->mNullData;
}

template <class T>
inline typename Vector_Grid<T>::size_t_pair Vector_Grid<T>::size() const
{
	return this->mSize;
}

template <class T>
inline size_t Vector_Grid<T>::getLength() const
{
	return this->mSize.x * mSize.y;
}

template <class T>
inline size_t Vector_Grid<T>::getIndexCount() const
{
	return this->mSize.x * this->mSize.y;
}

template <class T>
inline unsigned Vector_Grid<T>::sizeofArray() const
{
	return this->mSize.x * this->mSize.y * sizeof this->mNullData;
}

// checks
template <class T>
bool Vector_Grid<T>::empty() const								// is list empty
{
	return mCurrentlyOccupied == 0;
}

template <class T>
bool Vector_Grid<T>::empty(const size_t& whereX, const size_t& whereY) const	// is cell considered empty
{
	return this->at(whereX, whereY) == this->mNullData;
}

template <class T>
bool Vector_Grid<T>::isInArray(const size_t& whereX, const size_t& whereY) const
{
	return whereX < this->mSize.x && whereY < this->mSize.y;
}

// --------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/* Function Name: Copy array
* Description: copies the data from src to dest, resizing dest as needed.
*	if dest is larger, shrinks it, if dest is smaller, grows it
* Inputs: src arrGrid, destination arrGrid
* Preconditions:
* Outputs: none
* Returns: none
*/
template <class T>
void Vector_Grid<T>::copyArrayData(const Vector_Grid<T>& src)
{
	// check array needs resizing
	if (src.mSize.x != this->mSize.x || src.mSize.y != this->mSize.y || this->mData == nullptr)
	{
		this->resize(src.mSize, true);
	}

	// copy array data
	copyArray(src.mData, this->mData, (mSize.y * mSize.x));
}

/* Function Name: Fill Array with Data
* Description: Fills entire array with the supplied newData, overwriting any
*	previous values. Does not modify the nullData Set.
* Inputs: New data to overwrite the array
* Preconditions: none
* Outputs: array filled with newData
* Returns: none
* Postconditions:
*/
template <class T>
void Vector_Grid<T>::fill(const T& newData)
{
	// iterate through list and overwrite the data
	for (int index = 0; index < this->getIndexCount(); index++)
	{
		this->mData[index] = newData;
	}

	// check if data is nullData. If so, set to zero
	if (newData == this->mNullData)
	{
		this->mCurrentlyOccupied = 0;
	}
	//	otherwise set to the size of the array
	else
	{
		this->mCurrentlyOccupied = this->getIndexCount();
	}
}

/* Function Name: Clear Array
* Description: Sets all array values to the NullData set. Action discards all
*	overwritten data
* Inputs: none
* Preconditions:
* Outputs: array_grid now set entirely to NullData
* Returns: none
* Postconditions:
*/
template <class T>
void Vector_Grid<T>::clear()
{
	// simply calls fill but supplies the nullData values
	this->fill(this->mNullData);
}


// --------------------------------------------------------------------------------------------- //
//								  PRIVATE   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: resize array
* Description: resizes the array off of the given new size. keeps data depending on the chosen option
*	default deletes the data on a resize
* Inputs: new index count size of the array, T/F to copy the old data over or to wipe it
* Outputs: none
*/
template <class T>
void Vector_Grid<T>::resize(const size_t_pair& newSize, const bool& clear)
{
	// generate new array
	// create the new array
	T* pMem = newArray<T>(newSize.x, newSize.y, this->mNullData);

	// copy data if requested
	if (clear == false && this->mData != nullptr)
	{
		// copy the data from this to pMem
		copyArray(this->mData, pMem, static_cast<const unsigned>(mSize.y * mSize.x));

		// now clear the old data and pin the new
		delete[] this->mData;
		this->mData = pMem;
	}
	// otherwise, just pin the new data
	else
	{
		// discarding data (if any) and replacing with blank
		if (this->mData != nullptr)
		{
			// note this does not work great with pointers
			delete[] this->mData;
		}

		// attach new data
		this->mData = pMem;
	}

	// set new size
	this->mSize = newSize;
}






// --------------------------------------------------------------------------------------------- //
//									non - Member Functions
// --------------------------------------------------------------------------------------------- //


#endif