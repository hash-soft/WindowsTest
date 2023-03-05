// UnitTestTarget.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <memory>
#include "Operations.h"

int main()
{
	std::unique_ptr<Operations> ope;

	std::cout << "add = " << ope->add(1, 2) << "\n";
	std::cout << "sub = " << ope->sub(1, 2) << "\n";
	std::cout << "mul = " << ope->mul(1, 2) << "\n";
	std::cout << "div = " << ope->div(1, 2) << "\n";
}
