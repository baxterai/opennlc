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
 * File Name: NLCpreprocessorMathLogicalConditions.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2o2a 08-November-2020
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_MATH_LOGICAL_CONDITIONS
#define HEADER_NLC_PREPROCESSOR_MATH_LOGICAL_CONDITIONS

#include "NLCglobalDefs.hpp"
#include "NLCpreprocessorSentenceClass.hpp"
#include "LRPpreprocessorWordClass.hpp"
#include "SHAREDvars.hpp"

#ifdef NLC_PREPROCESSOR_MATH
#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
class NLCsubphrase
{
public:

	NLCsubphrase(void);
	~NLCsubphrase(void);

	int lineIndexOfFirstWordInPhrase;
	vector<LRPpreprocessorPlainTextWord*> phraseContents;
	bool hasConjunction;
	int conjunctionType;

	NLCsubphrase* next;
};
#endif

class NLCpreprocessorMathLogicalConditionsClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: LRPpreprocessorWordClassClass LRPpreprocessorWordClassObject;

	public: bool replaceLogicalConditionNaturalLanguageMathWithSymbols(vector<LRPpreprocessorPlainTextWord*>* lineContents, int logicalConditionOperator, bool* additionalClosingBracketRequired, const bool parallelReplacement);
	public: bool replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(NLCpreprocessorSentence* fullSentence, const bool additionalClosingBracketRequired);

	public: bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(NLCpreprocessorSentence* fullSentence, const int* sentenceIndex, const bool additionalClosingBracketRequired);

	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	public: bool generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(vector<LRPpreprocessorPlainTextWord*>* lineContents, bool* detectedLogicalConditionCommand, vector<LRPpreprocessorPlainTextWord*>* logicalConditionCommandSubphraseContents, int* logicalConditionCommandSubphraseLineIndex);
	public: bool generateSeparateSentencesFromCommand(vector<LRPpreprocessorPlainTextWord*>* logicalConditionCommandSubphraseContents, int currentIndentation, NLCpreprocessorSentence* firstSentenceInLogicalConditionCommandTemp);
	#endif
};


#endif
#endif

#endif
