//
// StringTest.cpp
//
// $Id: //poco/1.4/Foundation/testsuite/src/StringTest.cpp#1 $
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


#include "StringTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/String.h"
#include "Poco/Format.h"
#include "Poco/MemoryStream.h"
#include "Poco/Stopwatch.h"
#include "Poco/Exception.h"
#include <iostream>
#include <iomanip>
#include <cstdio>


using Poco::trimLeft;
using Poco::trimLeftInPlace;
using Poco::trimRight;
using Poco::trimRightInPlace;
using Poco::trim;
using Poco::trimInPlace;
using Poco::toUpper;
using Poco::toUpperInPlace;
using Poco::toLower;
using Poco::toLowerInPlace;
using Poco::icompare;
using Poco::translate;
using Poco::translateInPlace;
using Poco::replace;
using Poco::replaceInPlace;
using Poco::cat;
using Poco::strToInt;
using Poco::strToFloat;
using Poco::intToStr;
using Poco::uIntToStr;
using Poco::strToDoubleDC;
using Poco::floatToStr;
using Poco::doubleToStr;
using Poco::thousandSeparator;
using Poco::decimalSeparator;
using Poco::format;
using Poco::MemoryInputStream;
using Poco::Stopwatch;
using Poco::RangeException;


StringTest::StringTest(const std::string& name): CppUnit::TestCase(name)
{
}


StringTest::~StringTest()
{
}


void StringTest::testTrimLeft()
{
	{
		std::string s = "abc";
		assert (trimLeft(s) == "abc");
	}
		std::string s = " abc ";
		assert (trimLeft(s) == "abc ");
	{
	std::string s = "  ab c ";
	assert (trimLeft(s) == "ab c ");
	}
}


void StringTest::testTrimLeftInPlace()
{
	{
		std::string s = "abc";
		assert (trimLeftInPlace(s) == "abc");
	}
	{
		std::string s = " abc ";
		assert (trimLeftInPlace(s) == "abc ");
	}
	{
		std::string s = "  ab c ";
		assert (trimLeftInPlace(s) == "ab c ");
	}
}


void StringTest::testTrimRight()
{
	{
		std::string s = "abc";
		assert (trimRight(s) == "abc");
	}
	{
		std::string s = " abc ";
		assert (trimRight(s) == " abc");
	}
	{
		std::string s = "  ab c  ";
		assert (trimRight(s) == "  ab c");
	}
}


void StringTest::testTrimRightInPlace()
{
	{
		std::string s = "abc";
		assert (trimRightInPlace(s) == "abc");
	}
	{
		std::string s = " abc ";
		assert (trimRightInPlace(s) == " abc");
	}
	{
		std::string s = "  ab c  ";
		assert (trimRightInPlace(s) == "  ab c");
	}
}


void StringTest::testTrim()
{
	{
		std::string s = "abc";
		assert (trim(s) == "abc");
	}
	{
		std::string s = "abc ";
		assert (trim(s) == "abc");
	}
	{
		std::string s = "  ab c  ";
		assert (trim(s) == "ab c");
	}
}


void StringTest::testTrimInPlace()
{
	{
		std::string s = "abc";
		assert (trimInPlace(s) == "abc");
	}
	{
		std::string s = " abc ";
		assert (trimInPlace(s) == "abc");
	}
	{
		std::string s = "  ab c  ";
		assert (trimInPlace(s) == "ab c");
	}
}


void StringTest::testToUpper()
{
	{
		std::string s = "abc";
		assert (toUpper(s) == "ABC");
	}
	{
		std::string s = "Abc";
		assert (toUpper(s) == "ABC");
	}
	{
		std::string s = "abc";
		assert (toUpperInPlace(s) == "ABC");
	}
	{
		std::string s = "Abc";
		assert (toUpperInPlace(s) == "ABC");
	}
}


void StringTest::testToLower()
{
	{
		std::string s = "ABC";
		assert (toLower(s) == "abc");
	}
	{
		std::string s = "aBC";
		assert (toLower(s) == "abc");
	}
	{
		std::string s = "ABC";
		assert (toLowerInPlace(s) == "abc");
	}
	{
		std::string s = "aBC";
		assert (toLowerInPlace(s) == "abc");
	}
}


void StringTest::testIcompare()
{
	std::string s1 = "AAA";
	std::string s2 = "aaa";
	std::string s3 = "bbb";
	std::string s4 = "cCcCc";
	std::string s5;
	assert (icompare(s1, s2) == 0);
	assert (icompare(s1, s3) < 0);
	assert (icompare(s1, s4) < 0);
	assert (icompare(s3, s1) > 0);
	assert (icompare(s4, s2) > 0);
	assert (icompare(s2, s4) < 0);
	assert (icompare(s1, s5) > 0);
	assert (icompare(s5, s4) < 0);

	std::string ss1 = "xxAAAzz";
	std::string ss2 = "YaaaX";
	std::string ss3 = "YbbbX";
	assert (icompare(ss1, 2, 3, ss2, 1, 3) == 0);
	assert (icompare(ss1, 2, 3, ss3, 1, 3) < 0);
	assert (icompare(ss1, 2, 3, ss2, 1) == 0);
	assert (icompare(ss1, 2, 3, ss3, 1) < 0);
	assert (icompare(ss1, 2, 2, ss2, 1, 3) < 0);
	assert (icompare(ss1, 2, 2, ss2, 1, 2) == 0);
	assert (icompare(ss3, 1, 3, ss1, 2, 3) > 0);
	
	assert (icompare(s1, s2.c_str()) == 0);
	assert (icompare(s1, s3.c_str()) < 0);
	assert (icompare(s1, s4.c_str()) < 0);
	assert (icompare(s3, s1.c_str()) > 0);
	assert (icompare(s4, s2.c_str()) > 0);
	assert (icompare(s2, s4.c_str()) < 0);
	assert (icompare(s1, s5.c_str()) > 0);
	assert (icompare(s5, s4.c_str()) < 0);
	
	assert (icompare(ss1, 2, 3, "aaa") == 0);
	assert (icompare(ss1, 2, 2, "aaa") < 0);
	assert (icompare(ss1, 2, 3, "AAA") == 0);
	assert (icompare(ss1, 2, 2, "bb") < 0);
	
	assert (icompare(ss1, 2, "aaa") > 0);
}


void StringTest::testTranslate()
{
	std::string s = "aabbccdd";
	assert (translate(s, "abc", "ABC") == "AABBCCdd");
	assert (translate(s, "abc", "AB") == "AABBdd");
	assert (translate(s, "abc", "") == "dd");
	assert (translate(s, "cba", "CB") == "BBCCdd");
	assert (translate(s, "", "CB") == "aabbccdd");
}


void StringTest::testTranslateInPlace()
{
	std::string s = "aabbccdd";
	translateInPlace(s, "abc", "ABC");
	assert (s == "AABBCCdd");
}


void StringTest::testReplace()
{
	std::string s("aabbccdd");
	
	assert (replace(s, std::string("aa"), std::string("xx")) == "xxbbccdd");
	assert (replace(s, std::string("bb"), std::string("xx")) == "aaxxccdd");
	assert (replace(s, std::string("dd"), std::string("xx")) == "aabbccxx");
	assert (replace(s, std::string("bbcc"), std::string("xx")) == "aaxxdd");
	assert (replace(s, std::string("b"), std::string("xx")) == "aaxxxxccdd");
	assert (replace(s, std::string("bb"), std::string("")) == "aaccdd");
	assert (replace(s, std::string("b"), std::string("")) == "aaccdd");
	assert (replace(s, std::string("ee"), std::string("xx")) == "aabbccdd");
	assert (replace(s, std::string("dd"), std::string("")) == "aabbcc");

	assert (replace(s, "aa", "xx") == "xxbbccdd");
	assert (replace(s, "bb", "xx") == "aaxxccdd");
	assert (replace(s, "dd", "xx") == "aabbccxx");
	assert (replace(s, "bbcc", "xx") == "aaxxdd");
	assert (replace(s, "bb", "") == "aaccdd");
	assert (replace(s, "b", "") == "aaccdd");
	assert (replace(s, "ee", "xx") == "aabbccdd");
	assert (replace(s, "dd", "") == "aabbcc");
	
	s = "aabbaabb";
	assert (replace(s, std::string("aa"), std::string("")) == "bbbb");
	assert (replace(s, std::string("a"), std::string("")) == "bbbb");
	assert (replace(s, std::string("a"), std::string("x")) == "xxbbxxbb");
	assert (replace(s, std::string("a"), std::string("xx")) == "xxxxbbxxxxbb");
	assert (replace(s, std::string("aa"), std::string("xxx")) == "xxxbbxxxbb");

	assert (replace(s, std::string("aa"), std::string("xx"), 2) == "aabbxxbb");

	assert (replace(s, "aa", "") == "bbbb");
	assert (replace(s, "a", "") == "bbbb");
	assert (replace(s, "a", "x") == "xxbbxxbb");
	assert (replace(s, "a", "xx") == "xxxxbbxxxxbb");
	assert (replace(s, "aa", "xxx") == "xxxbbxxxbb");
	
	assert (replace(s, "aa", "xx", 2) == "aabbxxbb");
}


void StringTest::testReplaceInPlace()
{
	std::string s("aabbccdd");

	assert (replaceInPlace(s, std::string("aa"), std::string("xx")) == "xxbbccdd");
}


void StringTest::testCat()
{
	std::string s1("one");
	std::string s2("two");
	std::string s3("three");
	std::string s4("four");
	std::string s5("five");
	std::string s6("six");

	assert (cat(s1, s2) == "onetwo");
	assert (cat(s1, s2, s3) == "onetwothree");
	assert (cat(s1, s2, s3, s4) == "onetwothreefour");
	assert (cat(s1, s2, s3, s4, s5) == "onetwothreefourfive");
	assert (cat(s1, s2, s3, s4, s5, s6) == "onetwothreefourfivesix");
	
	std::vector<std::string> vec;
	assert (cat(std::string(), vec.begin(), vec.end()) == "");
	assert (cat(std::string(","), vec.begin(), vec.end()) == "");
	vec.push_back(s1);
	assert (cat(std::string(","), vec.begin(), vec.end()) == "one");
	vec.push_back(s2);
	assert (cat(std::string(","), vec.begin(), vec.end()) == "one,two");
	vec.push_back(s3);
	assert (cat(std::string(","), vec.begin(), vec.end()) == "one,two,three");
}


void StringTest::testStringToInt()
{
//gcc on Mac emits warnings that cannot be suppressed
#ifndef POCO_OS_FAMILY_BSD
	stringToInt<Poco::Int8>();
	stringToInt<Poco::UInt8>();
	stringToInt<Poco::Int16>();
	stringToInt<Poco::UInt16>();
#endif
	stringToInt<Poco::Int32>();
	stringToInt<Poco::UInt32>();
#if defined(POCO_HAVE_INT64)
	stringToInt<Poco::Int64>();
	stringToInt<Poco::UInt64>();
#endif
}


void StringTest::testStringToFloat()
{
#ifndef POCO_NO_FPENVIRONMENT
	
	double result;
	char eu;
	std::string sep(".,");

	for (int i = 0; i < 2; ++i)
	{
		char ds = sep[i];
		for (int j = 0; j < 2; ++j)
		{
			char ts = sep[j];
			if (ts == ds) continue;

			assert(strToFloat("1", result, eu, ds, ts));
			assertEqualDelta(1.0, result, 0.01);
			assert(strToFloat(format("%c1", ds), result, eu, ds, ts));
			assertEqualDelta(.1, result, 0.01);
			assert(strToFloat(format("1%c", ds), result, eu, ds, ts));
			assertEqualDelta(1., result, 0.01);
			assert(strToFloat("0", result, eu, ds, ts));
			assertEqualDelta(0.0, result, 0.01);
			assert(strToFloat(format("0%c", ds), result, eu, ds, ts));
			assertEqualDelta(0.0, result, 0.01);
			assert(strToFloat(format("%c0", ds), result, eu, ds, ts));
			assertEqualDelta(0.0, result, 0.01);
			assert(strToFloat(format("0%c0", ds), result, eu, ds, ts));
			assertEqualDelta(0.0, result, 0.01);
			assert(strToFloat(format("0%c0", ds), result, eu, ds, ts));
			assertEqualDelta(0., result, 0.01);
			assert(strToFloat(format("0%c0", ds), result, eu, ds, ts));
			assertEqualDelta(.0, result, 0.01);
			assert(strToFloat(format("12%c34", ds), result, eu, ds, ts));
			assertEqualDelta(12.34, result, 0.01);
			assert(strToFloat(format("12%c34f", ds), result, eu, ds, ts));
			assertEqualDelta(12.34, result, 0.01);
			assert(strToFloat(format("12%c34", ds), result, eu, ds, ts));
			assertEqualDelta(12.34, result, 0.01);
			assert(strToFloat(format("-12%c34", ds), result, eu, ds, ts));
			assertEqualDelta(-12.34, result, 0.01);
			assert(strToFloat(format("%c34", ds), result, eu, ds, ts));
			assertEqualDelta(.34, result, 0.01);
			assert(strToFloat(format("-%c34", ds), result, eu, ds, ts));
			assertEqualDelta(-.34, result, 0.01);
			assert(strToFloat(format("12%c", ds), result, eu, ds, ts));
			assertEqualDelta(12., result, 0.01);
			assert(strToFloat(format("-12%c", ds), result, eu, ds, ts));
			assertEqualDelta(-12., result, 0.01);
			assert(strToFloat("12", result, eu, ds, ts));
			assertEqualDelta(12, result, 0.01);
			assert(strToFloat("-12", result, eu, ds, ts));
			assertEqualDelta(-12, result, 0.01);
			assert(strToFloat(format("12%c3456789012345678901234567890", ds), result, eu, ds, ts));
			assertEqualDelta(12.34, result, 0.01);

			assert(strToFloat(format("1%c234%c3456789012345678901234567890", ts, ds), result, eu, ds, ts));
			assertEqualDelta(1234.3456789, result, 0.00000001);
			assert(strToFloat(format("12%c345%c3456789012345678901234567890", ts, ds), result, eu, ds, ts));
			assertEqualDelta(12345.3456789, result, 0.00000001);
			assert(strToFloat(format("123%c456%c3456789012345678901234567890", ts, ds), result, eu, ds, ts));
			assertEqualDelta(123456.3456789, result, 0.00000001);
			assert(strToFloat(format("1%c234%c567%c3456789012345678901234567890", ts, ts, ds), result, eu, ds, ts));
			assertEqualDelta(1234567.3456789, result, 0.00000001);
			assert(strToFloat(format("12%c345%c678%c3456789012345678901234567890", ts, ts, ds), result, eu, ds, ts));
			assertEqualDelta(12345678.3456789, result, 0.00000001);
			assert(strToFloat(format("123%c456%c789%c3456789012345678901234567890", ts, ts, ds), result, eu, ds, ts));
			assertEqualDelta(123456789.3456789, result, 0.00000001);

			if ((std::numeric_limits<double>::max() / 10) < 1.23456e10)
				fail ("test value larger than max value for this platform");
			else
			{
				double d = 12e34;
				assert(strToFloat(format("12e34", ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01e34);
			
				d = 1.234e100;
				assert(strToFloat(format("1%c234e100", ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
				assert(strToFloat(format("1%c234E+100", ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
		
				d = 1.234e-100;
				assert(strToFloat(format("1%c234E-100", ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
		
				d = -1.234e100;
				assert(strToFloat(format("-1%c234e+100", ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
				assert(strToFloat(format("-1%c234E100", ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
		
				d = 1.234e-100;
				assert(strToFloat(format(" 1%c234e-100 ", ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
				assert(strToFloat(format(" 1%c234e-100 ", ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
				assert(strToFloat(format("  1%c234e-100 ", ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);

				d = 1234.234e-100;
				assert(strToFloat(format(" 1%c234%c234e-100 ", ts, ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
				d = 12345.234e-100;
				assert(strToFloat(format(" 12%c345%c234e-100 ", ts, ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
				d = 123456.234e-100;
				assert(strToFloat(format("  123%c456%c234e-100 ", ts, ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);

				d = -1234.234e-100;
				assert(strToFloat(format(" -1%c234%c234e-100 ", ts, ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
				d = -12345.234e-100;
				assert(strToFloat(format(" -12%c345%c234e-100 ", ts, ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
				d = -123456.234e-100;
				char ou = 0;
				assert(strToFloat(format("  -123%c456%c234e-100 ", ts, ds), result, eu, ds, ts));
				assertEqualDelta(d, result, 0.01);
				assert (ou == 0);
			}

			double d = 12.34e-10;
			assert(strToFloat(format("12%c34e-10", ds), result, eu, ds, ts));
			assertEqualDelta(d, result, 0.01);
			assert(strToFloat(format("-12%c34", ds), result, eu, ds, ts));
			assertEqualDelta(-12.34, result, 0.01);
	
			assert(strToFloat(format("   12%c34", ds), result, eu, ds, ts));
			assertEqualDelta(12.34, result, 0.01);
			assert(strToFloat(format("12%c34   ", ds), result, eu, ds, ts));
			assertEqualDelta(12.34, result, 0.01);
			assert(strToFloat(format(" 12%c34  ", ds), result, eu, ds, ts));
			assertEqualDelta(12.34, result, 0.01);
		}
	}
#endif // POCO_NO_FPENVIRONMENT
}


void StringTest::testStringToFloatError()
{
#if !defined(POCO_NO_FPENVIRONMENT) && !defined(POCO_NO_LOCALE)
	const char ds = decimalSeparator();
	const char ts = thousandSeparator();

	double result = 0.0;
	char ou;
	assert (!strToFloat(format("a12%c3", ds), result, ou));
	assert (!strToFloat(format("1b2%c3", ds), result, ou));
	assert (!strToFloat(format("12c%c3", ds), result, ou));
	assert (!strToFloat(format("12%cx3", ds), result, ou));

	double d = -123456.234e-100;
	assert(strToFloat(format("123%c456%c234e-1000000", ts, ds), result, ou));
	assert (ou < 0); // loss of precision
	assertEqualDelta(d, result, 0.01); // value still good
	assert(!strToFloat(format("123%c456%c234e1000000", ts, ds), result, ou));
	assert(!strToFloat(format("123%c456%c234e+1000000", ts, ds), result, ou));
	assert(!strToFloat(0, result, ou)); // strToFloat is resilient to null pointers
	assert(!strToFloat("", result, ou));
#endif
}


void StringTest::testNumericLocale()
{
#if !defined(POCO_NO_LOCALE) && POCO_OS == POCO_OS_WINDOWS_NT
	try
	{
		char buffer[POCO_MAX_FLT_STRING_LEN];

		char dp = decimalSeparator();
		char ts = thousandSeparator();
		std::locale loc;
		std::cout << "Original locale: '" << loc.name() << '\'' << std::endl;
		std::cout << "Decimal point: '" << decimalSeparator() << '\'' << std::endl;
		std::cout << "Thousand separator: '" << ts << '\'' << std::endl;
		doubleToStr(buffer, POCO_MAX_FLT_STRING_LEN, 1.23);
		std::cout << "1.23 == '" << buffer << '\'' << std::endl;

		std::locale::global(std::locale("German"));
		std::locale locGerman;
		assert (',' == decimalSeparator());
		assert ('.' == thousandSeparator());
		std::cout << "New locale: '" << locGerman.name() << '\'' << std::endl;
		std::cout << "Decimal point: '" << decimalSeparator() << '\'' << std::endl;
		std::cout << "Thousand separator: '" << thousandSeparator() << '\'' << std::endl;
		doubleToStr(buffer, POCO_MAX_FLT_STRING_LEN, 1.23);
		std::cout << "1.23 == '" << buffer << '\'' << std::endl;

		std::locale::global(std::locale("US"));
		std::locale locUS;
		assert ('.' == decimalSeparator());
		assert (',' == thousandSeparator());
		std::cout << "New locale: '" << locUS.name() << '\'' << std::endl;
		std::cout << "Decimal point: '" << decimalSeparator() << '\'' << std::endl;
		std::cout << "Thousand separator: '" << thousandSeparator() << '\'' << std::endl;
		doubleToStr(buffer, POCO_MAX_FLT_STRING_LEN, 1.23);
		std::cout << "1.23 == '" << buffer << '\'' << std::endl;

		std::locale::global(loc);
		dp = decimalSeparator();
		ts = thousandSeparator();
		std::cout << "Final locale: '" << loc.name() << '\'' << std::endl;
		std::cout << "Decimal point: '" << decimalSeparator() << '\'' << std::endl;
		std::cout << "Thousand separator: '" << thousandSeparator() << '\'' << std::endl;
		doubleToStr(buffer, POCO_MAX_FLT_STRING_LEN, 1.23);
		std::cout << "1.23 == '" << buffer << '\'' << std::endl;

		assert (dp == decimalSeparator());
		assert (ts == thousandSeparator());
	} catch (std::runtime_error& ex)
	{
		std::cout << ex.what() << std::endl;
		warnmsg ("Locale not found, skipping test");
	}
#endif
}


void StringTest::benchmarkStrToInt()
{
	Poco::Stopwatch sw;
	std::string num = "123456789";
	int res;
	sw.start();
	for (int i = 0; i < 1000000; ++i) parseStream(num, res);
	sw.stop();
	std::cout << "parseStream Number: " << res << std::endl;
	double timeStream = sw.elapsed() / 1000.0;

	char* pC = 0;
	sw.restart();
	for (int i = 0; i < 1000000; ++i) res = std::strtol(num.c_str(), &pC, 10);
	sw.stop();
	std::cout << "std::strtol Number: " << res << std::endl;
	double timeStrtol = sw.elapsed() / 1000.0;
	
	sw.restart();
	for (int i = 0; i < 1000000; ++i) strToInt(num.c_str(), res, 10);
	sw.stop();
	std::cout << "strToInt Number: " << res << std::endl;
	double timeStrToInt = sw.elapsed() / 1000.0;
	
	sw.restart();
	for (int i = 0; i < 1000000; ++i) std::sscanf(num.c_str(), "%d", &res);
	sw.stop();
	std::cout << "sscanf Number: " << res << std::endl;
	double timeScanf = sw.elapsed() / 1000.0;

	int graph;
	std::cout << std::endl << "Timing and speedup relative to I/O stream:" << std::endl << std::endl;
	std::cout << std::setw(14) << "Stream:\t" << std::setw(10) << std::setfill(' ') << timeStream << "[ms]" << std::endl;

	std::cout << std::setw(14) << "std::strtol:\t" << std::setw(10) << std::setfill(' ') << timeStrtol << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeStrtol) << '\t' ;
	graph = (int) (timeStream / timeStrtol); for (int i = 0; i < graph; ++i) std::cout << '|';

	std::cout << std::endl << std::setw(14) << "strToInt:\t" << std::setw(10) << std::setfill(' ') << timeStrToInt << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeStrToInt) << '\t' ;
	graph = (int) (timeStream / timeStrToInt); for (int i = 0; i < graph; ++i) std::cout << '|';

	std::cout << std::endl << std::setw(14) << "std::sscanf:\t" << std::setw(10) << std::setfill(' ')  << timeScanf << "[ms]" <<
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeScanf) << '\t' ;
	graph = (int) (timeStream / timeScanf); for (int i = 0; i < graph; ++i) std::cout << '|';
	std::cout << std::endl;
}


void StringTest::benchmarkStrToFloat()
{
	Poco::Stopwatch sw;
	std::string num = "1.0372157551632929e-112";
	std::cout << "The Number: " << num << std::endl;
	double res;
	sw.start();
	for (int i = 0; i < 1000000; ++i) parseStream(num, res);
	sw.stop();
	std::cout << "parseStream Number: " << std::setprecision(std::numeric_limits<double>::digits10) << res << std::endl;
	double timeStream = sw.elapsed() / 1000.0;

	// standard strtod
	char* pC = 0;
	sw.restart();
	for (int i = 0; i < 1000000; ++i) res = std::strtod(num.c_str(), &pC);
	sw.stop();
	std::cout << "std::strtod Number: " << res << std::endl;
	double timeStdStrtod = sw.elapsed() / 1000.0;

	// POCO Way
	sw.restart();
	char ou = 0;
	for (int i = 0; i < 1000000; ++i) strToFloat(num.c_str(), res, ou);
	sw.stop();
	std::cout << "strToFloat Number: " << res << std::endl;
	double timeStrToFloat = sw.elapsed() / 1000.0;
	
	// standard sscanf
	sw.restart();
	for (int i = 0; i < 1000000; ++i) std::sscanf(num.c_str(), "%lf", &res);
	sw.stop();
	std::cout << "sscanf Number: " << res << std::endl;
	double timeScanf = sw.elapsed() / 1000.0;

	// double-conversion Strtod
	sw.restart();
	for (int i = 0; i < 1000000; ++i) strToDoubleDC(num.c_str());
	sw.stop();
	std::cout << "Strtod Number: " << res << std::endl;
	double timeStrtod = sw.elapsed() / 1000.0;

	int graph;
	std::cout << std::endl << "Timing and speedup relative to I/O stream:" << std::endl << std::endl;
	std::cout << std::setw(14) << "Stream:\t" << std::setw(10) << std::setfill(' ') << std::setprecision(4) << timeStream << "[ms]" << std::endl;

	std::cout << std::setw(14) << "std::strtod:\t" << std::setw(10) << std::setfill(' ') << timeStdStrtod << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeStdStrtod) << '\t' ;
	graph = (int) (timeStream / timeStdStrtod); for (int i = 0; i < graph; ++i) std::cout << '#';

	std::cout << std::endl << std::setw(14) << "strToFloat:\t" << std::setw(10) << std::setfill(' ') << timeStrToFloat << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeStrToFloat) << '\t' ;
	graph = (int) (timeStream / timeStrToFloat); for (int i = 0; i < graph; ++i) std::cout << '#';

	std::cout << std::endl << std::setw(14) << "std::sscanf:\t" << std::setw(10) << std::setfill(' ')  << timeScanf << "[ms]" <<
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeScanf) << '\t' ;
	graph = (int) (timeStream / timeScanf); for (int i = 0; i < graph; ++i) std::cout << '#';

	std::cout << std::endl << std::setw(14) << "StrtoD:\t" << std::setw(10) << std::setfill(' ')  << timeScanf << "[ms]" <<
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeStrtod) << '\t' ;
	graph = (int) (timeStream / timeStrtod); for (int i = 0; i < graph; ++i) std::cout << '#';

	std::cout << std::endl;
}


void StringTest::testIntToString()
{
	//intToStr(T number, unsigned short base, std::string& result, bool prefix = false, int width = -1, char fill = ' ', char thSep = 0)

	// decimal
	std::string result;
	assert (intToStr(0, 10, result));
	assert (result == "0");
	assert (intToStr(0, 10, result, false, 10, '0'));
	assert (result == "0000000000");
	assert (intToStr(1234567890, 10, result));
	assert (result == "1234567890");
	assert (intToStr(-1234567890, 10, result));
	assert (result == "-1234567890");
	assert (intToStr(-1234567890, 10, result, false, 15, '0'));
	assert (result == "-00001234567890");
	assert (intToStr(-1234567890, 10, result, false, 15));
	assert (result == "    -1234567890");
	assert (intToStr(-1234567890, 10, result, false, 0, 0, ','));
	assert (result == "-1,234,567,890");

	// binary
	assert (intToStr(1234567890, 2, result));
	assert (result == "1001001100101100000001011010010");
	assert (intToStr(1234567890, 2, result, true));
	assert (result == "1001001100101100000001011010010");
	assert (intToStr(1234567890, 2, result, true, 35, '0'));
	assert (result == "00001001001100101100000001011010010");
	assert (uIntToStr(0xFF, 2, result));
	assert (result == "11111111");
	assert (uIntToStr(0x0F, 2, result, false, 8, '0'));
	assert (result == "00001111");
	assert (uIntToStr(0x0F, 2, result));
	assert (result == "1111");
	assert (uIntToStr(0xF0, 2, result));
	assert (result == "11110000");
	assert (uIntToStr(0xFFFF, 2, result));
	assert (result == "1111111111111111");
	assert (uIntToStr(0xFF00, 2, result));
	assert (result == "1111111100000000");
	assert (uIntToStr(0xFFFFFFFF, 2, result));
	assert (result == "11111111111111111111111111111111");
	assert (uIntToStr(0xFF00FF00, 2, result));
	assert (result == "11111111000000001111111100000000");
	assert (uIntToStr(0xF0F0F0F0, 2, result));
	assert (result == "11110000111100001111000011110000");
#if defined(POCO_HAVE_INT64)
	assert (uIntToStr(0xFFFFFFFFFFFFFFFF, 2, result));
	std::cout << 0xFFFFFFFFFFFFFFFF << std::endl;
	assert (result == "1111111111111111111111111111111111111111111111111111111111111111");
	assert (uIntToStr(0xFF00000FF00000FF, 2, result));
	assert (result == "1111111100000000000000000000111111110000000000000000000011111111");
#endif

	// octal
	assert (uIntToStr(1234567890, 010, result));
	assert (result == "11145401322");
	assert (uIntToStr(1234567890, 010, result, true));
	assert (result == "011145401322");
	assert (uIntToStr(1234567890, 010, result, true, 15, '0'));
	assert (result == "000011145401322");
	assert (uIntToStr(012345670, 010, result, true));
	assert (result == "012345670");
	assert (uIntToStr(012345670, 010, result));
	assert (result == "12345670");

	// hexadecimal
	assert (uIntToStr(0, 0x10, result, true));
	assert (result == "0x0");
	assert (uIntToStr(0, 0x10, result, true, 4, '0'));
	assert (result == "0x00");
	assert (uIntToStr(0, 0x10, result, false, 4, '0'));
	assert (result == "0000");
	assert (uIntToStr(1234567890, 0x10, result));
	assert (result == "499602D2");
	assert (uIntToStr(1234567890, 0x10, result, true));
	assert (result == "0x499602D2");
	assert (uIntToStr(1234567890, 0x10, result, true, 15, '0'));
	assert (result == "0x00000499602D2");
	assert (uIntToStr(0x1234567890ABCDEF, 0x10, result, true));
	assert (result == "0x1234567890ABCDEF");
	assert (uIntToStr(0xDEADBEEF, 0x10, result));
	assert (result == "DEADBEEF");
#if defined(POCO_HAVE_INT64)
	assert (uIntToStr(0xFFFFFFFFFFFFFFFF, 0x10, result));
	assert (result == "FFFFFFFFFFFFFFFF");
	assert (uIntToStr(0xFFFFFFFFFFFFFFFF, 0x10, result, true));
	assert (result == "0xFFFFFFFFFFFFFFFF");
#endif

	try
	{
		char pResult[POCO_MAX_INT_STRING_LEN];
		unsigned sz = POCO_MAX_INT_STRING_LEN;
		intToStr(0, 10, pResult, sz, false, sz + 1, ' ');
		fail ("must throw RangeException");
	} catch (RangeException&) { }
}


void StringTest::testFloatToString()
{
	double val = 1.03721575516329e-112;
	std::string str;
	
	assert (doubleToStr(str, val, 15, 21) == "1.03721575516329e-112");
	assert (doubleToStr(str, val, 15, 22) == " 1.03721575516329e-112");
	val = -val;
	assert (doubleToStr(str, val, 15, 22) == "-1.03721575516329e-112");
	assert (doubleToStr(str, val, 15, 23) == " -1.03721575516329e-112");
	
	val = -10372157551632.9;
	assert (doubleToStr(str, val, 1, 21, ',') == "-10,372,157,551,632.9");
	assert (doubleToStr(str, val, 1, 22, ',') == " -10,372,157,551,632.9");
	assert (doubleToStr(str, val, 2, 22, ',') == "-10,372,157,551,632.90");
	assert (doubleToStr(str, val, 2, 22, '.', ',') == "-10.372.157.551.632,90");
	assert (doubleToStr(str, val, 2, 22, ' ', ',') == "-10 372 157 551 632,90");
}


void formatStream(double value, std::string& str)
{
	char buffer[128];
	Poco::MemoryOutputStream ostr(buffer, sizeof(buffer));
#if !defined(POCO_NO_LOCALE)
	ostr.imbue(std::locale::classic());
#endif
	ostr << std::setprecision(16) << value;
	str.assign(buffer, static_cast<std::string::size_type>(ostr.charsWritten()));
}


void formatSprintf(double value, std::string& str)
{
	char buffer[128];
	std::sprintf(buffer, "%.*g", 16, value);
	str = buffer;
}


void StringTest::benchmarkFloatToStr()
{
	Poco::Stopwatch sw;
	double val = 1.0372157551632929e-112;
	std::cout << "The Number: " << std::setprecision(std::numeric_limits<double>::digits10) << val << std::endl;
	std::string str;
	sw.start();
	for (int i = 0; i < 1000000; ++i) formatStream(val, str);
	sw.stop();
	std::cout << "formatStream Number: " << str << std::endl;
	double timeStream = sw.elapsed() / 1000.0;

	// standard sprintf
	str = "";
	sw.restart();
	for (int i = 0; i < 1000000; ++i) formatSprintf(val, str);
	sw.stop();
	std::cout << "std::sprintf Number: " << str << std::endl;
	double timeSprintf = sw.elapsed() / 1000.0;
	
	// POCO Way (via double-conversion)
	// no padding
	sw.restart();
	char buffer[POCO_MAX_FLT_STRING_LEN];
	for (int i = 0; i < 1000000; ++i) doubleToStr(buffer, POCO_MAX_FLT_STRING_LEN, val);
	sw.stop();
	std::cout << "doubleToStr(char) Number: " << buffer << std::endl;
	double timeDoubleToStrChar = sw.elapsed() / 1000.0;

	// with padding 
	str = "";
	sw.restart();
	for (int i = 0; i < 1000000; ++i) doubleToStr(str, val);
	sw.stop();
	std::cout << "doubleToStr(std::string) Number: " << str << std::endl;
	double timeDoubleToStrString = sw.elapsed() / 1000.0;

	int graph;
	std::cout << std::endl << "Timing and speedup relative to I/O stream:" << std::endl << std::endl;
	std::cout << std::setw(14) << "Stream:\t" << std::setw(10) << std::setfill(' ') << std::setprecision(4) << timeStream << "[ms]" << std::endl;
	
	std::cout << std::setw(14) << "sprintf:\t" << std::setw(10) << std::setfill(' ') << timeSprintf << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeSprintf) << '\t' ;
	graph = (int) (timeStream / timeSprintf); for (int i = 0; i < graph; ++i) std::cout << '#';
	
	std::cout << std::endl << std::setw(14) << "doubleToChar:\t" << std::setw(10) << std::setfill(' ') << timeDoubleToStrChar << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeDoubleToStrChar) << '\t' ;
	graph = (int) (timeStream / timeDoubleToStrChar); for (int i = 0; i < graph; ++i) std::cout << '#';
	
	std::cout << std::endl << std::setw(14) << "doubleToString:\t" << std::setw(10) << std::setfill(' ') << timeDoubleToStrString << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeDoubleToStrString) << '\t' ;
	graph = (int) (timeStream / timeDoubleToStrString); for (int i = 0; i < graph; ++i) std::cout << '#';

	std::cout << std::endl;
}


void StringTest::setUp()
{
}


void StringTest::tearDown()
{
}


CppUnit::Test* StringTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("StringTest");

	CppUnit_addTest(pSuite, StringTest, testTrimLeft);
	CppUnit_addTest(pSuite, StringTest, testTrimLeftInPlace);
	CppUnit_addTest(pSuite, StringTest, testTrimRight);
	CppUnit_addTest(pSuite, StringTest, testTrimInPlace);
	CppUnit_addTest(pSuite, StringTest, testTrim);
	CppUnit_addTest(pSuite, StringTest, testTrimRightInPlace);
	CppUnit_addTest(pSuite, StringTest, testToUpper);
	CppUnit_addTest(pSuite, StringTest, testToLower);
	CppUnit_addTest(pSuite, StringTest, testIcompare);
	CppUnit_addTest(pSuite, StringTest, testTranslate);
	CppUnit_addTest(pSuite, StringTest, testTranslateInPlace);
	CppUnit_addTest(pSuite, StringTest, testReplace);
	CppUnit_addTest(pSuite, StringTest, testReplaceInPlace);
	CppUnit_addTest(pSuite, StringTest, testCat);
	CppUnit_addTest(pSuite, StringTest, testStringToInt);
	CppUnit_addTest(pSuite, StringTest, testStringToFloat);
	CppUnit_addTest(pSuite, StringTest, testStringToFloatError);
	CppUnit_addTest(pSuite, StringTest, testNumericLocale);
	CppUnit_addTest(pSuite, StringTest, benchmarkStrToFloat);
	//CppUnit_addTest(pSuite, StringTest, benchmarkStrToInt);
	CppUnit_addTest(pSuite, StringTest, testIntToString);
	CppUnit_addTest(pSuite, StringTest, testFloatToString);
	CppUnit_addTest(pSuite, StringTest, benchmarkFloatToStr);

	return pSuite;
}
