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
 * File Name: NLCglobalDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1i10a 25-August-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#ifndef HEADER_NLC_GLOBAL_DEFS
#define HEADER_NLC_GLOBAL_DEFS

#include "SHAREDglobalDefs.h"


	
//#define NLC_ACTIVATE_PRE1i_CODE_FOR_DEBUG
#ifdef NLC_ACTIVATE_PRE1i_CODE_FOR_DEBUG
	#define NLC_USE_ORIGINAL_INSTANCE_LIST_NAMES	
#else
	#define NLC_STRICT_NO_IMPLICIT_DECLARATIONS	//1i8a+
	#ifdef NLC_STRICT_NO_IMPLICIT_DECLARATIONS
		#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_BASIC_GENERATE_CONTEXT_BLOCKS_IF_SAME_REFERENCE_SET	//1i3d
		#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED	//1i8a+
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED
			//#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION	//added 1i8a, removed 1i8e
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION
				#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_AT_ALL_TIMES	//added 1i8c, removed 1i8e
			#endif
			#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD	//1i8b
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
				//#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT	//1i9a
			#endif
		#endif
	#endif

	#define NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS	//1i7a
	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
		#define NLC_GENERATE_TYPE_LISTS
		#ifdef NLC_GENERATE_TYPE_LISTS
			#define NLC_ITEM_TYPE_TYPEVAR_APPENDITION2 "Type"
			#define NLC_ITEM_TYPE_INSTANCEVAR_APPENDITION2 "Instance"
		#endif
	#endif
	//#define NLC_USE_ORIGINAL_INSTANCE_LIST_NAMES	//changed 1i6a

	#define NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN	//1i1a/19-August-2014/1i3 - categories
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		#define NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_SUBSTANCE_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES	//1i4a
		#define NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION2 "Category"
	#endif
#endif

#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS
	
	#define NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES (9)
	static string logicalConditionOperationsArray[NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES] = {"for", "if", "as", "before", "after", "while", "when", "else", "else if"};	//should be dynamically defined in NLCrules.xml
	#define NLC_LOGICAL_CONDITION_OPERATIONS_IF_STRING "if"
	#define NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_STRING "else"
	#define NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF_STRING "else if"
	#define NLC_LOGICAL_CONDITION_OPERATIONS_WHILE_STRING "while"

	#define NLC_LOGICAL_CONDITION_OPERATIONS_FOR (0)	//default
	#define NLC_LOGICAL_CONDITION_OPERATIONS_IF (1)
	#define NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF (8)
	#define NLC_LOGICAL_CONDITION_OPERATIONS_ELSE (7)	//not used
	#define NLC_LOGICAL_CONDITION_OPERATIONS_WHILE (5)
	
	#define NLC_WHILE_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME "whileLogicalConditionL"	//eg whileLogicalConditionL0

#endif


#define NLC_USE_PREPROCESSOR	//1g17a/18-July-2014	//reimplementation 1h1a+/22-July-2014 //first working 1h1f
#ifdef NLC_USE_PREPROCESSOR
	#define NLC_PREPROCESSOR_GENERATE_COMMENTS
	#define NLC_PREPROCESSOR_MATH	//1h1a/22-July-2014	//requires NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE for preprocessor isLogicalConditionOperator detection	//first working 1h2f
	#ifdef NLC_PREPROCESSOR_MATH
		#define NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR (CHAR_FULLSTOP)	//this is defined by NLP/English
		#define NLC_PREPROCESSOR_END_OF_SENTENCE_QUESTION_CHAR (CHAR_QUESTIONMARK)	//this is defined by NLP/English
		#define NLC_PREPROCESSOR_MATH_TESTING_ALLOW_GENERATION_OF_UNCOMPILABLE_CODE
		#ifdef NLC_PREPROCESSOR_MATH_TESTING_ALLOW_GENERATION_OF_UNCOMPILABLE_CODE
			#define NLC_PREPROCESSOR_MATH_ALLOW_UNDECLARED_MATHTEXT_VARIABLES_TO_BE_REFERENCED_BY_MATH
		#endif
		//#define NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES	//used for automated testing
		#define NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES	
		#define NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN ">"
		#define NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN "<"
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST "=="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_PLUS "+"
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET "="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO ">="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO "<="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN "<="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN ">="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL "!="	//invalid for set
		#define NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO "!="	//invalid for set
		#define NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES (11)
		static string preprocessorMathOperators[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, NLC_PREPROCESSOR_MATH_OPERATOR_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO};
		static string preprocessorMathOperatorsForLogicalConditions[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, NLC_PREPROCESSOR_MATH_OPERATOR_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO};
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR (CHAR_EQUALS)
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_WITH_PADDING " = "
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING " == "
		#define NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS
		
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES (63)
		static char preprocessorMathNLPparsableCharacters[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_MANDATORY_NUMBER_OF_TYPES (53)
		static char preprocessorMathNLPparsableCharactersMandatory[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_MANDATORY_NUMBER_OF_TYPES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_'};
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_DELIMITER_NUMBER_OF_TYPES (1)
		static char preprocessorMathNLPparsableCharactersDelimiter[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_DELIMITER_NUMBER_OF_TYPES] = {CHAR_SPACE};	//CHAR_COMMA removed 1h1e (parsable phrases are divided by commas)
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS (2)
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE "nlpParsablePhraseRef"
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_SENTENCE "S"
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_PHRASE "P"
		//#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_LEVEL "L"	//not currently used
		//#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_CASE "C"	//not currently used
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY "Do this."
		
		#define NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP	//old name: NLC_PREPROCESSOR_SUPPORT_MATH_DETECT_NUMERICAL_VARIABLES
		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
			#define NLC_PREPROCESSOR_MATH_DUMMY_NUMERICAL_VALUE_BASE (9900)
			//#define NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES 	//global defs are disabled by default
		#endif
		
		#if NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS <= 2
			#define NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
			#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
				#define NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES (7)
				static string preprocessorMathNaturalLanguageVariables[NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES] = {"bool", "char", "short", "int", "integer", "float", "double"};
				static string preprocessorMathMathTextVariables[NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES] = {"bool$", "char$", "short$", "int$", "integer$", "float$", "double$"};	//{"$0", "$1", "$2", "$4", "$4", "#4", "#8"};
			#endif
		#endif
		
		#define NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
		#ifdef NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
			#define NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_DEFAULT "double$ "
		#endif
		
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL " is "
		#define NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE	//replaces NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED implementation	//first working 1h3i
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			
			#define NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR '!'
			
			#define NLC_PREPROCESSOR_MATH_PARSABLE_PHRASE_START_TEXT_INDICATING_LOGICAL_CONDITION_COMMAND ", "
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
			#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				//#define NLC_PREPROCESSOR_MATH_SUPPORT_MULTIPLE_LOGICAL_CONDITION_COMMANDS_ON_ONE_LINE		//eg "if the house is blue, write the letter and read the book"/"else write the letter and read the book."	//Not yet implemented
				#define NLC_PREPROCESSOR_MATH_SUPPORT_LOGICAL_CONDITION_MATHTEXT_COMMANDS_ON_SAME_LINE 		//eg "if the house is blue, X = 3+5"	//untested
				#define NLC_PREPROCESSOR_MATH_SUPPORT_LOGICAL_CONDITION_IMPLICIT_CONJUNCTIONS			//eg "if the house is blue, the cat is green, and the bike is tall, ride the bike"	//testing now
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_AND_INDEX (0)	//&&
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_OR_INDEX (1)	//||
			#endif
			
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN "is greater than"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN "is less than"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_EQUALS "equals"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_PLUS "plus"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO "is equal to"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN_OR_EQUAL_TO "is greater than or equal to"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN_OR_EQUAL_TO "is less than or equal to"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_GREATER_THAN "is not greater than"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_LESS_THAN "is not less than"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_DOES_NOT_EQUAL "does not equal"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_EQUAL_TO "is not equal to"
			static string preprocessorMathOperatorsEquivalentNumberOfTypes[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_EQUALS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_EQUAL_TO};
			
			#define NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS		//this is required by NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_PAUSE_ARRAY_NUMBER_OF_TYPES (2)
				static string preprocessorMathOperatorsEquivalentConjunctionsWithPause[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_PAUSE_ARRAY_NUMBER_OF_TYPES] = {", and ", ", or "};
				static string progLangCoordinatingConjunctionsWithPause[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_PAUSE_ARRAY_NUMBER_OF_TYPES] = {") && (", ") || ("};				
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES (4)
				static string preprocessorMathOperatorsEquivalentConjunctions[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES] = {", and ", ", or ", " and ", " or "};		//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print
				static string progLangCoordinatingConjunctions[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES] = {") && (", ") || (", " && ", " || "};	//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print 
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES (2)
				static string preprocessorMathOperatorsEquivalentConjunctionsWithoutPause[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES] = {" and ", " or "};
				static string progLangCoordinatingConjunctionsWithoutPause[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES] = {" && ", " || "};
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_END_WHITESPACE_ARRAY_NUMBER_OF_TYPES (2)
				static string preprocessorMathOperatorsEquivalentConjunctionsWithoutEndWhiteSpace[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_END_WHITESPACE_ARRAY_NUMBER_OF_TYPES] = {" and", " or"};
				static string progLangCoordinatingConjunctionsWithoutWhiteSpace[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_END_WHITESPACE_ARRAY_NUMBER_OF_TYPES] = {" &&", " ||"};
			#else
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES (2)
				static string preprocessorMathOperatorsEquivalentConjunctions[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES] = {"and", "or"};		//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print
				static string progLangCoordinatingConjunctions[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES] = {"&&", "||"};	//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print 

			#endif
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET '('	//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print 
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET ')'	//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET_STRING "("
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET_STRING ")"
			
			#define NLC_LOGICAL_CONDITION_OPERATIONS_IF_ELSE_IF_ELSE_NUMBER_OF_TYPES (3)
			static int logicalConditionOperationsIfElseIfElseArray[NLC_LOGICAL_CONDITION_OPERATIONS_IF_ELSE_IF_ELSE_NUMBER_OF_TYPES] = {NLC_LOGICAL_CONDITION_OPERATIONS_IF, NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF, NLC_LOGICAL_CONDITION_OPERATIONS_ELSE};	
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILLARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES (4)
			static string preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILLARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES] = {"has", "have", "is", "are"};	//don't use lemmas				
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES (2)
			static string preprocessorMathRcmodSameReferenceSetDelimiter[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES] = {"that", "which"};			
			
			#define NLC_PREPROCESSOR_MATH_SEARCH_FOR_CONJUNCTION_SUBJECT_MATCH_NON_IDENTICAL_AUXILLARIES	//introduced 1h6c //test this 
				
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS (10000)
		#endif
		//#define NLC_PREPROCESSOR_PRINT_OUTPUT
	#endif
	//#define NLC_PREPROCESSOR_SUPPORT_MULTILINE_SENTENCES
	//#define NLC_PREPROCESSOR_SUPPORT_MATH_DECIMAL_PLACES
	#define NLC_PREPROCESSOR_INDENTATION_CHAR (CHAR_TAB)
	#define NLC_PREPROCESSOR_FUNCTION_HEADER_STRING "function"
	#define NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR (CHAR_SPACE)
	#define NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS (100)
	#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND ", do this."	//appending to "If" statments without a command (in which it is assumed the following indented lines constitute the command)
	#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION "do"
	#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION_OBJECT "this"
	#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSE "If this is done,"	//replaces "Else"
	#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSEIF "If"		//replaces "Else if"
	#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND_ELSE " do this."	//appending to "Else" statments without a command (in which it is assumed the following indented lines constitute the command)
	#define NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
#endif

#define NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS	//1g16a/16-July-2014

#define NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX	//1g15a/16-July-2014	//requires GIA_STORE_CONNECTION_SENTENCE_INDEX

#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE	//added 1g13b+/15-July-2014

#define NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES	//1g8a+ local variable implementation

#define NLC_CLASS_DEFINITIONS_ORDER_BY_DEPENDENCIES	//1f14b (required for C++ compilation)
#define NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS	//1f14c (a base NLC entity class is required to be defined for integration of generic NLC Library)
#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
	#define NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE "NLCgenericEntity"
#endif
//#define NLC_USE_DESTRUCTORS

#define NLC_SUPPORT_QUANTITIES	//1f3a

#ifndef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED		//1f1a+ if statement support
#endif

#define NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION	//assumes #ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED

	#define NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME "logicalCondition"	//eg logicalCondition	
	#define NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL "L"		//eg logicalConditionL0		//L="level"
	#define NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_CASE "C"		//eg logicalConditionL0C0	//C="case"
	
	#define NLC_ONLY_SUPPORT_LOGICAL_CONJUNCTION_FOR_AT_START_OF_SENTENCE	//this is a more restricted implementation but is faster. It still requires modifications of GIA (it requires entityIndex information to be stored in GIAdatabase.cpp or GIAxmlConversion.cpp)
	#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS	//1gXy+ logical if/while/for support + conjunction support
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
		#define NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE (100)
		//#assert defined NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION
	#endif
	#define NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES (3)
	static string logicalConditionOperationsWordImmediatelySucceedingForArray[NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES] = {"each", "all", "every"};	//should be dynamically defined in NLCrules.xml
	#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS
		#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_DUMMY_REFERENCE_SET_ID (99)
	#endif	
	
	#ifdef GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS	//hasnt been coded [always use substance concept nodes rather than raw concept nodes to store concept relationships]
		#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
			//GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS hasnt been coded therefore NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS cannot be used
			//static bool isIncomingOutgoingConditionArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {false, false, true, true, false, false, false, false, false, false, false, false, false, false};
		#endif
	#endif
#endif

#define NLC_DEBUG_PARSE_CONTEXT2
#define NLC_DEBUG_PARSE_CONTEXT3

//#define NLC_DEBUG_PARSE_CONTEXT_CHILDREN
//#define NLC_DEBUG_PARSE_CONTEXT
//#define NLC_PREPROCESSOR_PRINT_OUTPUT
//#define NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
//#define NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
//#define NLC_DEBUG_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
//#define NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
//#define NLC_DEBUG_PREPROCESSOR_MATH
//#define NLC_DEBUG_PREPROCESSOR
//#define NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
//#define NLC_DEBUG
//#define NLC_DEBUG_PRINT_HIDDEN_CLASSES
//#define NLC_STRICT_MODE_FAVOUR_COMPILATION_RATHER_THAN_DESIGN_USE_MAIN_ENTRY_POINT

#define NLC_LOCAL_LISTS_USE_INSTANCE_NAMES

//#define NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS	//BAD

#define NLC_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES	//1e3a

#define NLC_SUPPORT_INPUT_FILE_LISTS	//added 1d1x
#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	#define NLC_SUPPORT_INPUT_FILE_LISTS_MAX_INHERITANCE_DEPTH_FOR_CLASS_CASTING (99)
	#define NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS	//added 1d1b
	#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER "#"
	#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH (1)
	#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER "+"
	#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH (1)
#endif

#define NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
//#define NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS	//removed 1e1a; now pass action action and action object as arguments cf NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS (do not pass action subject properties and conditions as arguments)
#define NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS	//added 1e1a

#define NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
//#define NLC_BAD_IMPLEMENTATION
//#define NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS

//#define NLC_PRINT_EXPLICIT_LOCAL_CONTEXT
#ifdef NLC_PRINT_EXPLICIT_LOCAL_CONTEXT
	#define NLC_LOCAL_CONTEXT_NAME "locaL"
#endif

#endif
