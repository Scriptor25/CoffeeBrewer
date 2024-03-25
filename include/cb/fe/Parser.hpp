#pragma once

#include <cb/Frontend.hpp>
#include <cb/fe/Token.hpp>

#include <vector>

namespace cb::fe
{
	class Parser
	{
	public:
		static bool Parse(std::istream& stream);

	private:
		Parser(std::istream& stream);

		int Get();
		void Mark();
		void Reset();

		Token& Next();

		bool AtEOF() const;
		bool At(const std::string& value) const;
		bool At(const uint32_t type) const;
		bool NextIfAt(const std::string& value);
		void Expect(const std::string& value);
		Token Expect(uint32_t type);
		Token Eat();

		SymbolPtr NextSymbol();
		GlobalVariablePtr NextGlobalVariable(const std::string& name, TypePtr type);
		FunctionPtr NextFunction(const std::string& name, FunctionTypePtr type);

		StatementPtr NextStatement(InsertablePtr& insertable);

		ExpressionPtr NextExpression();

		TypePtr NextType();
		TypePtr NextType(TypePtr base);

		std::string NextName();

	private:
		std::istream& m_Stream;

		bool m_Marked = false;
		std::vector<int> m_Buffer;

		size_t m_Line = 1;
		Token m_Token;
	};
}
