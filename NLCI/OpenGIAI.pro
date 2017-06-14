QT += widgets
QT += svg

CONFIG += c++11
CONFIG += warn_off

LIBS+= -lglut -lGL -lGLU -lwordnet

QMAKE_CXXFLAGS += -I../NLC/
QMAKE_CXXFLAGS += -I../GIA/GIA/
QMAKE_CXXFLAGS += -I../RT/RT/

HEADERS         = NLCIeditorSyntaxHighlighter.hpp NLCIeditorWindow.hpp NLCImainWindow.hpp NLCImain.hpp NLCIeditorOperations.hpp NLCIglobalDefs.hpp NLCItextDisplayOperations.hpp NLCItextDisplayWindow.hpp NLCIoperations.hpp \
../GIA/GIA/GIAmain.hpp ../GIA/GIA/GIAnlpParser.hpp ../GIA/GIA/GIAtranslator.hpp ../GIA/GIA/GIAtranslatorDefineGrammar.hpp ../GIA/GIA/GIAtranslatorDefineReferencing.hpp ../GIA/GIA/GIAtranslatorRedistributeRelations.hpp ../GIA/GIA/GIAtranslatorRedistributeRelationsStanford.hpp ../GIA/GIA/GIAtranslatorRedistributeRelationsRelex.hpp ../GIA/GIA/GIAtranslatorDefineSubstances.hpp ../GIA/GIA/GIAtranslatorLinkEntities.hpp ../GIA/GIA/GIAtranslatorLinkEntitiesDynamic.hpp ../GIA/GIA/GIAtranslatorApplyAdvancedFeatures.hpp ../GIA/GIA/GIAtranslatorOperations.hpp ../GIA/GIA/GIAentityNodeClass.hpp ../GIA/GIA/GIAentityConnectionClass.hpp ../GIA/GIA/GIAconditionNodeClass.hpp ../GIA/GIA/GIAsentenceClass.hpp ../GIA/GIA/GIAdraw.hpp ../GIA/GIA/GIAxmlConversion.hpp ../GIA/GIA/GIAcxlConversion.hpp ../GIA/GIA/GIAquery.hpp ../GIA/GIA/GIAdatabase.hpp ../GIA/GIA/GIAnlp.hpp ../GIA/GIA/GIAwordnet.hpp ../GIA/GIA/GIAnlg.hpp ../GIA/GIA/GIApreprocessor.hpp ../GIA/GIA/GIApreprocessorSentenceClass.hpp ../GIA/GIA/GIApreprocessorMultiwordReduction.hpp ../GIA/GIA/GIApreprocessorMultiwordReductionClass.hpp ../GIA/GIA/GIApreprocessorLogicReference.hpp ../GIA/GIA/GIApreprocessorReferenceSet.hpp ../GIA/GIA/GIAbot.hpp ../GIA/GIA/GIAtranslatorGeneric.hpp ../GIA/GIA/GIAtranslatorRules.hpp ../GIA/GIA/GIAsemanticParser.hpp ../GIA/GIA/GIAsemanticParserOperations.hpp ../GIA/GIA/GIAsemanticParserTranslator.hpp ../GIA/GIA/GIAsemanticParserDatabase.hpp ../RT/RT/XMLparserClass.hpp ../RT/RT/XMLrulesClass.hpp ../RT/RT/LDsvg.hpp ../RT/RT/LDopengl.hpp ../RT/RT/LDparser.hpp ../RT/RT/LDsprite.hpp ../RT/RT/LDreferenceManipulation.hpp ../RT/RT/LDreferenceClass.hpp ../RT/RT/RTpixelMaps.hpp ../RT/RT/RTppm.hpp ../RT/RT/RTviewinfo.hpp ../RT/RT/SHAREDglobalDefs.hpp ../RT/RT/SHAREDvector.hpp ../RT/RT/SHAREDvars.hpp \
../GIA/GIA/GIAglobalDefs.hpp ../GIA/GIA/GIAtranslatorDefs.hpp

SOURCES         = NLCIeditorSyntaxHighlighter.cpp NLCIeditorWindow.cpp NLCImainWindow.cpp NLCImain.cpp NLCIeditorOperations.cpp NLCItextDisplayOperations.cpp NLCItextDisplayWindow.cpp NLCIoperations.cpp \
../GIA/GIA/GIAmain.cpp ../GIA/GIA/GIAnlpParser.cpp ../GIA/GIA/GIAtranslator.cpp ../GIA/GIA/GIAtranslatorDefineGrammar.cpp ../GIA/GIA/GIAtranslatorDefineReferencing.cpp ../GIA/GIA/GIAtranslatorRedistributeRelations.cpp ../GIA/GIA/GIAtranslatorRedistributeRelationsStanford.cpp ../GIA/GIA/GIAtranslatorRedistributeRelationsRelex.cpp ../GIA/GIA/GIAtranslatorDefineSubstances.cpp ../GIA/GIA/GIAtranslatorLinkEntities.cpp ../GIA/GIA/GIAtranslatorLinkEntitiesDynamic.cpp ../GIA/GIA/GIAtranslatorApplyAdvancedFeatures.cpp ../GIA/GIA/GIAtranslatorOperations.cpp ../GIA/GIA/GIAentityNodeClass.cpp ../GIA/GIA/GIAentityConnectionClass.cpp ../GIA/GIA/GIAconditionNodeClass.cpp ../GIA/GIA/GIAsentenceClass.cpp ../GIA/GIA/GIAdraw.cpp ../GIA/GIA/GIAxmlConversion.cpp ../GIA/GIA/GIAcxlConversion.cpp ../GIA/GIA/GIAquery.cpp ../GIA/GIA/GIAdatabase.cpp ../GIA/GIA/GIAnlp.cpp ../GIA/GIA/GIAwordnet.cpp ../GIA/GIA/GIAnlg.cpp ../GIA/GIA/GIApreprocessor.cpp ../GIA/GIA/GIApreprocessorSentenceClass.cpp ../GIA/GIA/GIApreprocessorMultiwordReduction.cpp ../GIA/GIA/GIApreprocessorMultiwordReductionClass.cpp ../GIA/GIA/GIApreprocessorLogicReference.cpp ../GIA/GIA/GIApreprocessorReferenceSet.cpp ../GIA/GIA/GIAbot.cpp ../GIA/GIA/GIAtranslatorGeneric.cpp ../GIA/GIA/GIAtranslatorRules.cpp ../GIA/GIA/GIAsemanticParser.cpp ../GIA/GIA/GIAsemanticParserOperations.cpp ../GIA/GIA/GIAsemanticParserTranslator.cpp ../GIA/GIA/GIAsemanticParserDatabase.cpp ../RT/RT/XMLparserClass.cpp ../RT/RT/XMLrulesClass.cpp ../RT/RT/LDsvg.cpp ../RT/RT/LDopengl.cpp ../RT/RT/LDparser.cpp ../RT/RT/LDsprite.cpp ../RT/RT/LDreferenceManipulation.cpp ../RT/RT/LDreferenceClass.cpp ../RT/RT/RTpixelMaps.cpp ../RT/RT/RTppm.cpp ../RT/RT/RTviewinfo.cpp ../RT/RT/SHAREDglobalDefs.cpp ../RT/RT/SHAREDvector.cpp ../RT/RT/SHAREDvars.cpp \

# install
target.path = .
INSTALLS += target
