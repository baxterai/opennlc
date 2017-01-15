/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCpreprocessor.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1j2c 06-September-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCpreprocessor.h"
#include "NLCpreprocessorSentenceClass.h"
#include "NLCpreprocessorMath.h"
#include "NLCpreprocessorMathLogicalConditions.h"

//#include "NLCprintDefs.h" //required for progLangOpenParameterSpace
#include "SHAREDvars.h"	//required for convertStringToLowerCase/isWhiteSpace
#include "GIAentityNodeClass.h" //required for GIA_NLP_START_SENTENCE_INDEX and entityNodesActiveListComplete



#ifdef NLC_USE_PREPROCESSOR
bool preprocessTextForNLC(string inputFileName, NLCfunction * firstNLCfunctionInList, bool * detectedFunctions, int * numberOfInputFilesInList, vector<string> * inputTextFileNameList, string outputFileName)
{
	*numberOfInputFilesInList = 1;
	
	bool result = true;
	ifstream parseFileObject(inputFileName.c_str());
	if(!parseFileObject.rdbuf( )->is_open( ))
	{
		//txt file does not exist in current directory.
		cout << "Error: NLC input file does not exist in current directory: " << inputFileName << endl;
		result = false;
	}
	else
	{
		setCurrentDirectory(tempFolderCharStar);	//save output files to temp folder

		NLCfunction * currentNLCfunctionInList = firstNLCfunctionInList;
		NLCsentence * currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		string currentLine;
		int sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;
		*detectedFunctions = false;
		string functionContents = "";
		string functionName = "";
		int currentLineNumber = 0;
		
		while(getline(parseFileObject, currentLine))
		{
			currentLineNumber++;
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << currentLineNumber << ": " << currentLine << endl;
			#endif
			
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
			if(detectFunctionHeader(&currentLine))
			{
				//extract functions from file and generate separate files
				if(*detectedFunctions)
				{
					#ifdef NLC_DEBUG_PREPROCESSOR
					cout << "end function: functionName = " << functionName << endl;
					cout << "create new function = " << functionName << endl;
					cout << "functionContents = " << functionContents << endl;
					#endif
					writeStringToFile(&functionName, &functionContents);
					currentNLCfunctionInList->functionName = functionName;
					currentNLCfunctionInList->next = new NLCfunction();
					currentNLCfunctionInList = currentNLCfunctionInList->next;
					currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
					*numberOfInputFilesInList = *numberOfInputFilesInList+1;
					//create new function file based on current text
				}
				else
				{
					#ifdef NLC_DEBUG_PREPROCESSOR
					cout << "detectedFunctions" << endl;
					#endif
					*detectedFunctions = true;
				}
				sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;
				functionName = getFunctionNameFromFunctionHeader(&currentLine);
				inputTextFileNameList->push_back(functionName);
				functionContents = "";
			}
			else
			{
			#endif
				int currentIndentation = 0;
				string lineContents = "";
				string indentationContents = "";
				extractIndentationFromCurrentLine(&currentLine, &currentIndentation, &lineContents, &indentationContents);	//this will remove the indentation from the current line
				#ifdef NLC_DEBUG_PREPROCESSOR
				//cout << "currentIndentation = " << currentIndentation << endl;
				#endif
				
				#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
				currentNLCsentenceInList->sentenceOriginal = lineContents;
				#endif
				
				#ifdef NLC_PREPROCESSOR_MATH
				if(detectMathSymbolsInLine(&lineContents))
				{
					currentNLCsentenceInList->isMath = true;
				}
				
				int lineLogicalConditionOperator;
				if(detectLogicalConditionOperatorAtStartOfLine(&lineContents, &lineLogicalConditionOperator))
				{
					//cout << "hasLogicalConditionOperator" << endl;
					currentNLCsentenceInList->hasLogicalConditionOperator = true;
					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					currentNLCsentenceInList->logicalConditionOperator = lineLogicalConditionOperator;
					currentNLCsentenceInList->isMath = true;
					#endif
				}
				else
				{
					//#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					if(detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(&lineContents, currentNLCsentenceInList->hasLogicalConditionOperator, currentNLCsentenceInList->isMath))
					{
						currentNLCsentenceInList->isMath = true;
					}
					//#endif
				}
				
				if(currentNLCsentenceInList->isMath)
				{
					#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
					replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(&lineContents);
					#endif
					
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH
					cout << "splitMathDetectedLineIntoNLPparsablePhrases():" << endl;
					#endif
					splitMathDetectedLineIntoNLPparsablePhrases(&lineContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation, &functionContents, currentNLCfunctionInList, firstNLCfunctionInList);
				}
				else
				{				
					#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
					replaceNumericalVariablesWithDummyNameIfNecessary(&lineContents, currentNLCsentenceInList, currentNLCfunctionInList, firstNLCfunctionInList);
					#endif
				#endif
					//cout << "at-1" << endl;
					functionContents = functionContents + indentationContents;
				
					//now for each sentence on line:
					int startOfSentenceIndex = 0;
					bool stillSentenceToParseOnLine = true;
					while(stillSentenceToParseOnLine)
					{
						bool lineFullStopDetected = false;
						int startOfSentenceIndexNew = lineContents.find(NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR, startOfSentenceIndex);
						if(startOfSentenceIndexNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							lineFullStopDetected = true;
						}
						else
						{
							startOfSentenceIndexNew = lineContents.find(NLC_PREPROCESSOR_END_OF_SENTENCE_QUESTION_CHAR, startOfSentenceIndex);	//NB '.' and '?' are currently supported as sentence delimiters
							if(startOfSentenceIndexNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								lineFullStopDetected = true;
							}
						}						
						string sentenceContents = "";
						if(lineFullStopDetected)
						{
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "lineFullStopDetected" << endl;
							#endif
							sentenceContents = lineContents.substr(startOfSentenceIndex, startOfSentenceIndexNew-startOfSentenceIndex+1);	//+1 append the full stop

						}
						else
						{
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "!lineFullStopDetected" << endl;
							#endif
							sentenceContents = lineContents.substr(startOfSentenceIndex, lineContents.length());

						}
						//cout << "sentenceContents = " << sentenceContents << endl;

						bool sentenceIsLogicalCondition = false;
						int sentenceLogicalConditionOperator;
						if(detectLogicalConditionOperatorAtStartOfLine(&sentenceContents, &sentenceLogicalConditionOperator))
						{
							sentenceIsLogicalCondition = true;
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "sentenceIsLogicalCondition: " << logicalConditionOperationsArray[sentenceLogicalConditionOperator] << endl;
							#endif
							currentNLCsentenceInList->hasLogicalConditionOperator = true;
							
							/*logicalConditionOperator is only used by mathText with parsable phrases at present (ie lineLogicalConditionOperator)
							#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							currentNLCsentenceInList->logicalConditionOperator = sentenceLogicalConditionOperator;
							#endif
							*/
												
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
							//cout << "at0" << endl;
							if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
							{
								//cout << "at1" << endl;
								#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
								currentNLCsentenceInList->ifDetected = true;
								#endif
							}
							else if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF)
							{
								//cout << "at2" << endl;
								#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
								currentNLCsentenceInList->elseIfDetected = true;
								//replace "else if" with "If"
								sentenceContents.replace(0, string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF_STRING).length(), string(NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSEIF));
								#else
								//will rely on NLP to add an "else" property to the logicalConditionObject
								#endif
							}
							else if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
							{
								//cout << "at3" << endl;
								#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
								currentNLCsentenceInList->elseDetected = true;
								#endif
								//replace "else" with "If this is done,"
								sentenceContents.replace(0, string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_STRING).length(), string(NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSE));

							}
							#endif	
						}		
						
						if(!lineFullStopDetected)
						{															
							stillSentenceToParseOnLine = false;
							
							bool nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine = false;
							for(int i=startOfSentenceIndex; i<sentenceContents.length(); i++)
							{
								char c = sentenceContents[i];
								if(!isWhiteSpace(c))
								{
									nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine = true;
									//cout << "nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine" << endl;
								}
							}
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
							if(!lineFullStopDetected && nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine && sentenceIsLogicalCondition)
							{
								#ifdef NLC_DEBUG_PREPROCESSOR
								cout << "(!lineFullStopDetected && nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine && sentenceIsLogicalCondition)" << endl;
								#endif
								
								string lowerCaseSentenceContents = convertStringToLowerCase(&sentenceContents);
								string dummyCommand = "";
								if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
								{
									if(sentenceContents.length() == (string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_STRING)).length())
									{
										//sentence was originally "Else" and has not yet been converted to "If this is done,"
										//replace "else" with "If this is done, "
										sentenceContents = string(NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSE);

										dummyCommand = NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND_ELSE;	//append dummy action " do this."
									}
									else
									{
										//sentence was originally "else ___" and has been converted to "If this is done, ___" - it is invalid because it does not contain a full stop.
										cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC() error: \"else\" logical condition operation detected in combination with an incomplete command (no full stop): sentenceContents = " << sentenceContents << endl;
										exit(0);
									}
								}
								else
								{
									dummyCommand = NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND;	//append dummy action ", do this."
								}
								//add dummy text ", do this." to the end of the logical condition, such that NLP can parse the logical condition header, and NLC can parse the multi-sentence logical condition based on its indentation.
								#ifdef NLC_DEBUG_PREPROCESSOR
								cout << "create new sentence" << endl;
								cout << sentenceIndex << ": sentenceContents = " << sentenceContents + string(dummyCommand) << endl;
								#endif
								sentenceContents = sentenceContents + string(dummyCommand);
								currentNLCsentenceInList->sentenceContents = sentenceContents;
								currentNLCsentenceInList->sentenceIndex = sentenceIndex;
								currentNLCsentenceInList->indentation = currentIndentation;
								currentNLCsentenceInList->next = new NLCsentence();
								currentNLCsentenceInList = currentNLCsentenceInList->next;
								sentenceIndex++;
							}
							else 
							#endif
							if(!lineFullStopDetected && nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine)
							{
								cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC() error: NLC_PREPROCESSOR_SUPPORT_MULTILINE_SENTENCES are not currently supported" << endl;
								exit(0);
							}
							else
							{//!lineFullStopDetected && !nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine
								//assume that a sentence has already been created based on a full stop (do not support multiline sentences)
								//redundant white space will be culled from functionContents
							}
						}
						else
						{
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "create new sentence" << endl;
							cout << sentenceIndex << ": sentenceContents = " << sentenceContents << endl;
							#endif
							currentNLCsentenceInList->sentenceContents = sentenceContents;	//full stop should already be appended
							currentNLCsentenceInList->sentenceIndex = sentenceIndex;
							currentNLCsentenceInList->indentation = currentIndentation;
							currentNLCsentenceInList->next = new NLCsentence();
							currentNLCsentenceInList = currentNLCsentenceInList->next;
							sentenceIndex++;
							
							if(startOfSentenceIndexNew == lineContents.length()-1)
							{
								stillSentenceToParseOnLine = false;
							}
						}
						functionContents = functionContents + sentenceContents + CHAR_NEWLINE;
						startOfSentenceIndex = startOfSentenceIndexNew + 1;	//is +1 required? (to prevent current NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR/CHAR_FULLSTOP from being redetected)
					}

				
				#ifdef NLC_PREPROCESSOR_MATH
				}
				#endif
				
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
			}
			#endif
		}
		
		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		if(*detectedFunctions)
		{
			//create a final function based on the final text..
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << "create new function = " << functionName << endl;
			cout << "functionContents = " << functionContents << endl;
			#endif
			writeStringToFile(&functionName, &functionContents);
			//create new function file based on current text
		}
		else
		{
		#endif
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << "create preprocessed file = " << functionName << endl;
			cout  << "functionContents = \n" << functionContents << endl;
			#endif
			writeStringToFile(&outputFileName, &functionContents);
		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		}
		#endif
	}
	
	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	NLCsentence * currentNLCsentenceInList = firstNLCfunctionInList->firstNLCsentenceInFunction;
	while(currentNLCsentenceInList->next != NULL)
	{
		for(int i=0;i<currentNLCsentenceInList->indentation; i++)
		{
			cout << "\t";
		}
		cout << currentNLCsentenceInList->sentenceContents;
		if(currentNLCsentenceInList->isMath)
		{
			cout << " (mathText = " << currentNLCsentenceInList->mathText << ")" << endl;
		}
		else
		{
			cout << endl;
		}
		currentNLCsentenceInList = currentNLCsentenceInList->next;
	}
	#endif
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	cout << "Premature quit for debug" << endl;	
	exit(0);
	#endif

	return result;
}

	


void writeStringToFile(string * fileName, string * s)
{
	ofstream writeFileObject(*fileName);

	for(int i=0; i < s->size(); i++)
	{
		writeFileObject.put((*s)[i]);
	}

	writeFileObject.close();
}

void extractIndentationFromCurrentLine(string * currentLine, int * currentIndentation, string * lineContents, string * indentationContents)
{
	int i = 0; 
	while((i < currentLine->length()) && (isWhiteSpace((*currentLine)[i]) || (*currentLine)[i] == NLC_PREPROCESSOR_INDENTATION_CHAR))	//in case NLC_PREPROCESSOR_INDENTATION_CHAR is not a form of white space
	{
		char c = (*currentLine)[i];
		if(c == NLC_PREPROCESSOR_INDENTATION_CHAR)
		{
			*currentIndentation = *currentIndentation + 1;
		}
		i++;
	}
	*indentationContents = currentLine->substr(0, i);
	*lineContents = currentLine->substr(i, (currentLine->length()-i));
}

#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
bool detectFunctionHeader(string * lineContents)
{
	bool functionHeaderFound = false;
	int index = lineContents->find(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING));
	if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
	{
		functionHeaderFound = true;
		
		//cout << "detectFunctionHeader(): functionHeaderFound = " << NLC_PREPROCESSOR_FUNCTION_HEADER_STRING << endl; 
	}
	return functionHeaderFound;
}
string getFunctionNameFromFunctionHeader(string * lineContents)
{
	string functionName = lineContents->substr(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING).length()+1);	//+1 for NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR
	//cout << "getFunctionNameFromFunctionHeader(): functionName = " << functionName << endl; 
	return functionName;
	
}
#endif


bool detectLogicalConditionOperatorAtStartOfLine(string * lineContents, int * logicalConditionOperator)
{
	//cout << "detectLogicalConditionOperatorAtStartOfLine() lineContents = " << *lineContents << endl;

	*logicalConditionOperator = INT_DEFAULT_VALUE;
	bool logicalConditionOperatorFound = false;
	
	string lowerCaseSentenceContents = convertStringToLowerCase(lineContents);
	//get first word in line
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		int index = lowerCaseSentenceContents.find(logicalConditionOperationsArray[i]);
		if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
		{
			logicalConditionOperatorFound = true;
			*logicalConditionOperator = i;
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << "detectLogicalConditionOperatorAtStartOfLine(): logicalConditionOperatorFound" << logicalConditionOperationsArray[i] << endl;
			#endif
		}
	}
	return logicalConditionOperatorFound;
}
	

#endif




