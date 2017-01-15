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
 * File Name: NLCprint.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1v13a 25-October-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCprint.h"
#include "NLCprintClassDefinitions.h"
#include "NLCprintCodeBlocks.h"
#include "NLCprintDefs.h"

#ifndef NLC_SUPPORT_INPUT_FUNCTION_LISTS
bool printCode(NLCcodeblock* firstCodeBlockInLevel, vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, NLCfunction* firstNLCfunctionInList)
{
	bool result = true;

	#ifndef NLC_NONOO_DISABLE_CLASS_HEIRACHY
	if(!printClassDefinitions(classDefinitionList, progLang, code, false, firstNLCfunctionInList))
	{
		result = false;
	}
	#endif

	int level = 0;
	if(!printCodeBlocks(firstCodeBlockInLevel, classDefinitionList, progLang, code, level))
	{
		result = false;
	}

	return result;
}
#endif
