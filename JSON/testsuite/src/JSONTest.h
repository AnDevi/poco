//
// JSONTest.h
//
// $Id: //poco/1.4/JSON/testsuite/src/JSONTest.h#1 $
//
// Definition of the JSONTest class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef JSONTest_INCLUDED
#define JSONTest_INCLUDED


#include "Poco/JSON/JSON.h"
#include "CppUnit/TestCase.h"


class JSONTest: public CppUnit::TestCase
{
public:
	JSONTest(const std::string& name);
	~JSONTest();

	void testNullProperty();
	void testTrueProperty();
	void testFalseProperty();
	void testNumberProperty();
	void testUnsignedNumberProperty();
#if defined(POCO_HAVE_INT64)
	void testNumber64Property();
	void testUnsignedNumber64Property();
#endif
	void testStringProperty();
	void testEmptyObject();
	void testComplexObject();
	void testDoubleProperty();
	void testDouble2Property();
	void testDouble3Property();
	void testObjectProperty();
	void testObjectArray();
	void testArrayOfObjects();
	void testEmptyArray();
	void testNestedArray();
	void testNullElement();
	void testTrueElement();
	void testFalseElement();
	void testNumberElement();
	void testStringElement();
	void testEmptyObjectElement();
	void testDoubleElement();
	void testOptValue();
	void testQuery();
	void testPrintHandler();
	void testStringify();
	void testStringifyPreserveOrder();

	void testValidJanssonFiles();
	void testInvalidJanssonFiles();
	void testTemplate();
	void testItunes();
	void testUnicode(); 
	void testInvalidUnicodeJanssonFiles();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	std::string getTestFilesPath(const std::string& type);
};


#endif // JSONTest_INCLUDED
