/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCprint.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2o2a 08-November-2020
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT
#define HEADER_NLC_PRINT

#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
#include "NLCpreprocessorSentenceClass.hpp"	//required for NLC_CLASS_DEFINITIONS_PRINT_UNDEFINED_BUT_REFERENCED_FUNCTIONS
#include "NLCprintClassDefinitions.hpp"
#include "NLCprintCodeBlocks.hpp"
#include "NLCprintDefs.hpp"

#ifndef NLC_INPUT_FUNCTION_LISTS
class NLCprintClass
{
	private: NLCprintClassDefinitionsClass NLCprintClassDefinitions;
	private: NLCprintCodeBlocksClass NLCprintCodeBlocks;
	public: bool printCode(NLCcodeblock* firstCodeBlockInLevel, vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, NLCfunction* firstNLCfunctionInList);
};
#endif

#endif
