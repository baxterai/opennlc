/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * BAIPROJECT is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with BAIPROJECT. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardMath.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u10c 29-September-2016
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardMath.hpp"
#include "NLClibraryStandardOperations.hpp"
#include "SHAREDvars.h"	//required for charInCharArray

#ifdef NLC_USE_MATH_OBJECTS

bool isStringNumberOrFractional(string phrase)
{
	bool stringIsNumberOrFractional = true;
	if(phrase.length() == 0)
	{
		//cout << "isStringNumberOrFractional() error: phrase.length() == 0" << endl;
	}
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];	
		bool numberFound = charInCharArray(c, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
		bool decimalPlaceFound = isDecimalPlace(i, &phrase);
		if(!(numberFound || decimalPlaceFound))
		{
			stringIsNumberOrFractional = false;
		}
	}
	//cout << "isStringNumberOrFractional: " << phrase << " = " << stringIsNumberOrFractional << endl;
	return stringIsNumberOrFractional;
}

bool isDecimalPlace(int indexOfCurrentToken, string* lineContents)
{
	bool decimalPlace = false;
	char currentToken = (*lineContents)[indexOfCurrentToken];
	if(currentToken == CHAR_FULLSTOP) 
	{
		if(indexOfCurrentToken < lineContents->length()-1)	//ensure fullstop is not immediately succeded by an numeric character, which indicates a decimal place, eg "5.5"
		{	
			char characterImmediatelySucceedingPunctuationMark = (*lineContents)[indexOfCurrentToken+1];
			bool isPunctuationMarkImmediatelySucceededByNumericCharacter = charInCharArray(characterImmediatelySucceedingPunctuationMark, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
			if(isPunctuationMarkImmediatelySucceededByNumericCharacter)
			{
				decimalPlace = true;
			}		
		}
	}
	return decimalPlace;
}

#endif

