#include "pch.h"
#include "CppUnitTest.h"
#include "Operations.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestMS
{
	TEST_CLASS(UnitTestMS)
	{
	public:

		TEST_METHOD(TestAdd)
		{
			std::unique_ptr<Operations> ope;
			Assert::AreEqual(2, ope->add(1, 1));
			Assert::AreEqual(4, ope->add(1, 3));
		}

		TEST_METHOD(TestSub)
		{
			std::unique_ptr<Operations> ope;
			Assert::AreEqual(0, ope->sub(1, 1));
		}

		TEST_METHOD(TestMul)
		{
			std::unique_ptr<Operations> ope;
			Assert::AreEqual(1, ope->mul(1, 1));
		}

		TEST_METHOD(TestDiv)
		{
			std::unique_ptr<Operations> ope;
			Assert::AreEqual(1, ope->div(1, 1));
		}
	};
}
