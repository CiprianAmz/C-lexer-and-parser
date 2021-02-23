# include "token.h"
# include <iostream>
# include <string>
# include <map>

// map used to write the type of a token
TokenTypeMap tokenTypeMap{ { TokenType::ID , "ID"},
	{ TokenType::NUM , "NUM"}, { TokenType::INT , "INT" },
	{ TokenType::VOID , "VOID"}, { TokenType::RETURN , "RETURN" },
	{ TokenType::IF , "IF"}, { TokenType::WHILE , "WHILE" },
	{ TokenType::ELSE , "ELSE" },
	{ TokenType::PLUS , "PLUS" }, { TokenType::MINUS , "MINUS" },
	{ TokenType::MULT , "MULT" }, { TokenType::DIV , "DIV" },
	{ TokenType::ASSIGN , "ASSIGN" }, { TokenType::LPAREN , "LPAREN" },
	{ TokenType::RPAREN , "RPAREN" }, { TokenType::LBRACKET , "LBRACKET" },
	{ TokenType::RBRACKET , "RBRACKET" }, { TokenType::LBRACE , "LBRACE" },
	{ TokenType::RBRACE , "RBRACE" }, { TokenType::COMMA , "COMMA" },
	{ TokenType::SEMICOLON , "SEMICOLON" } , { TokenType::EQ , "EQ" },
	{ TokenType::NEQ , "NEQ" } , { TokenType::LT , "LT" },
	{ TokenType::LTE , "LTE" } , { TokenType::GT , "GT" },
	{ TokenType::GTE , "GTE" } , { TokenType::END , "END" }
};

Token::Token(const Token& tok) {
	lexeme = tok.lexeme;
	// copy operations
	switch (tok.type) {
	case TokenType::NUM:
		num = tok.num;
		break;

	case TokenType::ID:
		new (&id)(std::string)(tok.id);
		break;
	default:
		oth = tok.oth;
		break;
	}
	type = tok.type;
}

Token& Token :: operator =(const Token& tok) {
	lexeme = tok.lexeme;
	if (type == TokenType::ID && tok.type == TokenType::ID) {
		id = tok.id;
		return *this;
	}
	// the current token type = id
	if (type == TokenType::ID) {
		id.~basic_string <char >(); // destroy explicitly
	}
	// copy operations
	switch (tok.type) {
	case TokenType::NUM:
		num = tok.num;
		break;
	case TokenType::ID:
		new (&id)(std::string)(tok.id);
		break;
	default:
		oth = tok.oth;
		break;
	}
	type = tok.type;
	return *this;
}

void Token::print(std::ofstream& out) const {
	out << " Token {\n";
	out << "\tLexeme = " << lexeme << std::endl;
	out << "\tToken type = " << tokenTypeMap[type] << std::endl;
	switch (type) {
	case TokenType::NUM:
		out << "\tLValue = ";
		out << num << std::endl;
		break;
	case TokenType::ID:
		out << "\tLValue = ";
		out << id << std::endl;
		break;
	default:
		break;
	}
	out << "}\n";
}