/*****************************************************************************
**************
* Programmer: Conner Howard
* File: Simple Tile Bitflags
* Date: 06/06/2023
* Description: Simple Bit Flag implimentation that uses at most 8 flag markers to
*	represent a tile
* Credit: Dieter Tack, https://dietertack.medium.com/using-bit-flags-in-c-d39ec6e30f08
******************************************************************************
*************/
#ifndef OBJECT_FLAGS_HPP
#define OBJECT_FLAGS_HPP

#include <iostream>


	enum class Tile_Flag
	{
		UNIVERSAL = 1 << 0,
		Path = 1 << 1,
		Wall = 1 << 2,
		//Flag4 = 1 << 3,
		//Flag5 = 1 << 4,
		//Flag6 = 1 << 5,
		//Flag7 = 1 << 6,
		//Flag8 = 1 << 7
	};

	enum class Template_Flag
	{
		Update = 1 << 0,
		Flag2 = 1 << 1,
		Flag3 = 1 << 2,
		Flag4 = 1 << 3,
		Flag5 = 1 << 4,
		Flag6 = 1 << 5,
		Flag7 = 1 << 6,
		Flag8 = 1 << 7
	};


// Flag variable that holds a number of flags equal to the bit size
//		uint8_t = 8 flags max
//		uint32_t = 32 flags max
template <typename Enum>
class Flag_8  {
public:
	/* mFunction Name: Set Flag
	* Description: Sets the Bit_Flag to the indicated input flag
	* Inputs: flag to set to true
	* Outputs: none
	*/
	inline void SetFlag(const Enum& flag)
	{
		// using bit OR, we can set the current flagState to true
		//	by passing the corresponding state we want to be true
		//	  00000000
		//	| 00000100
		//	= 00000100
		mFlagState |= (int)flag;
	}

	/* mFunction Name: Unset Flag
	* Description: Sets the indicated flag to false
	* Inputs: flag to set to false
	* Outputs: none
	*/
	inline void UnsetFlag(const Enum& flag)
	{
		// By inversing the flag's bits and then taking the bit AND,
		//	it assures that the current states of the othere flags are perserved
		//	and that the inputed flag gets set to false in the FlagState variable
		//	   00000100 -> We get Flag3 as input to unset
		//	~= 11111011 -> We flip all the bits of Flag3
		//	then...
		//	   00010110
		//	&  11111011
		//	=  00010010
		mFlagState &= ~(int)flag;
	}

	/* mFunction Name: Flip Flag
	* Description: Flip the state of the input flag. If it is true, it becomes false,
	*	and vice versa
	* Inputs: flag to flip
	* Outputs: none
	*/
	inline void FlipFlag(const Enum& flag)
	{
		// Using the XOR operation, the bits of the flagState variable are maintained
		//	except where the match: at the bit of the inputed flag
		//    00010110
		//  ^ 00000100
		//  = 00010010
		mFlagState ^= (int)flag;
	}

	/* mFunction Name: Has Flag
	* Description: Checks the flags for the indicated flag. Returns true if it has
	*	that flag, false otherwise
	* Inputs: Flag to check if active
	* Outputs: true if flag is set(true), false if not
	*/
	inline bool HasFlag(const Enum& flag) const
	{
		// By using bitwise AND with the flag and the FlagState, the only bit that is 
		//	maintianed is the shared bit, if the flag was set. If it wasn't, the result
		//	will be 0, which will not equal the value of the flag in the lookup table
		return ( mFlagState & (int)flag ) == (int)flag;
	}

	/* mFunction Name: Check Multi Flags
	* Description: Checks multiple flags at once. If at least one of them is true, returns
	*	true. Otherwise, returns false. Multiple flags can be combines by using "|":
	*		"Flag_Table::Flag1 | Flag_Table::Flag2"
	* Inputs:
	* Outputs:
	*/
	inline bool HasMultiFlag(const Enum& multiFlag) const
	{
		// By combining multiple flags with bitwise OR ('|'), which can be check with a
		//	similar AND method to the "HasFlag();" function. Bitwise AND will only equal 
		//	zero if there are no matching flags among the ones set in FlagState. It will
		//	hit if just one flag is triggered
		//	\see: HasFlag();
		return (mFlagState & (int)multiFlag) != 0;
	}

	/* mFunction Name: Set all Flags
	* Description: Sets all flag bits to true (1)
	* Inputs: none
	* Outputs: none
	*/
	inline void SetAllFlagsTrue()
	{
		this->mFlagState = UINT8_MAX;
	}

	/* mFunction Name: Clear all Flags
	* Description: Sets all flag bits to false (0)
	* Inputs: none
	* Outputs: none
	*/
	inline void SetAllFlagsFalse()
	{
		this->mFlagState = 0;
	}

private:
	uint8_t mFlagState = 0;	// data the flags are actually stored in
};




// Flag variable that holds a number of flags equal to the bit size
//		uint8_t = 8 flags max
//		uint16_t = 16 flags max
//		uint32_t = 32 flags max
template <typename Enum>
class Flag_16 {
public:
	/* mFunction Name: Default Constructor
	* Description: Constructs the flag either will either construct with
	*	all flags set or with none. Defualt is none
	* Inputs: Bool to set all flags to true or false
	* Outputs: none
	*/
	Flag_16(const bool& allFlagsSet = false)
	{
		if (allFlagsSet)
		{
			this->mFlagState = UINT16_MAX;
		}
	}

	/* mFunction Name: Set Flag
	* Description: Sets the Bit_Flag to the indicated input flag
	* Inputs: flag to set to true
	* Outputs: none
	*/
	inline void SetFlag(const Enum& flag)
	{
		// using bit OR, we can set the current flagState to true
		//	by passing the corresponding state we want to be true
		//	  00000000
		//	| 00000100
		//	= 00000100
		mFlagState |= (int)flag;
	}

	/* mFunction Name: Unset Flag
	* Description: Sets the indicated flag to false
	* Inputs: flag to set to false
	* Outputs: none
	*/
	inline void UnsetFlag(const Enum& flag)
	{
		// By inversing the flag's bits and then taking the bit AND,
		//	it assures that the current states of the othere flags are perserved
		//	and that the inputed flag gets set to false in the FlagState variable
		//	   00000100 -> We get Flag3 as input to unset
		//	~= 11111011 -> We flip all the bits of Flag3
		//	then...
		//	   00010110
		//	&  11111011
		//	=  00010010
		mFlagState &= ~(int)flag;
	}

	/* mFunction Name: Flip Flag
	* Description: Flip the state of the input flag. If it is true, it becomes false,
	*	and vice versa
	* Inputs: flag to flip
	* Outputs: none
	*/
	inline void FlipFlag(const Enum& flag)
	{
		// Using the XOR operation, the bits of the flagState variable are maintained
		//	except where the match: at the bit of the inputed flag
		//    00010110
		//  ^ 00000100
		//  = 00010010
		mFlagState ^= (int)flag;
	}

	/* mFunction Name: Has Flag
	* Description: Checks the flags for the indicated flag. Returns true if it has
	*	that flag, false otherwise
	* Inputs: Flag to check if active
	* Outputs: true if flag is set(true), false if not
	*/
	inline bool HasFlag(const Enum& flag) const
	{
		// By using bitwise AND with the flag and the FlagState, the only bit that is 
		//	maintianed is the shared bit, if the flag was set. If it wasn't, the result
		//	will be 0, which will not equal the value of the flag in the lookup table
		return (mFlagState & (int)flag) == (int)flag;
	}

	/* mFunction Name: Check Multi Flags
	* Description: Checks multiple flags at once. If at least one of them is true, returns
	*	true. Otherwise, returns false. Multiple flags can be combines by using "|":
	*		"Flag_Table::Flag1 | Flag_Table::Flag2"
	* Inputs:
	* Outputs:
	*/
	inline bool HasMultiFlag(const Enum& multiFlag) const
	{
		// By combining multiple flags with bitwise OR ('|'), which can be check with a
		//	similar AND method to the "HasFlag();" function. Bitwise AND will only equal 
		//	zero if there are no matching flags among the ones set in FlagState. It will
		//	hit if just one flag is triggered
		//	\see: HasFlag();
		return (mFlagState & (int)multiFlag) != 0;
	}

	/* mFunction Name: Set all Flags
	* Description: Sets all flag bits to true (1)
	* Inputs: none
	* Outputs: none
	*/
	inline void SetAllFlagsTrue()
	{
		this->mFlagState = UINT16_MAX;
	}

	/* mFunction Name: Clear all Flags
	* Description: Sets all flag bits to false (0)
	* Inputs: none
	* Outputs: none
	*/
	inline void SetAllFlagsFalse()
	{
		this->mFlagState = 0;
	}

private:
	uint16_t mFlagState = 0;	// data the flags are actually stored in
};



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