# include <algorithm>
# include <iostream>
# include <string>
# include "scanner.h"
# include "token.h"
# include "toktype.h"
# include "exceptions.h"

// map used to associate the token type of a keyword
KeywordMap keywordMap{ {"int", TokenType::INT } ,
{"void", TokenType::VOID } , {"while", TokenType::WHILE } ,
{"return", TokenType::RETURN } , {"if", TokenType::IF } ,
{"else", TokenType::ELSE } ,
};

Scanner::Scanner(std::string name) : fileName(name) {
	inputFile.open(name);
	if (!inputFile.is_open()) {
		throw new Exception(" Input file does not exist ");
	}
	currPosition = inputFile.tellg();
};

Token Scanner::nextToken() {
	char c, c1;
	// read from the current position
	inputFile.seekg(currPosition, std::ios::beg);
	while ((c = inputFile.get()) && inputFile.good()) {
		if ((c == ' ') || (c == '\n') || (c == '\t')) { // skip spaces
			while ((c = inputFile.get()) && (c == ' ' || c == '\n') || (c == '\t' || c == '\r'));
		}

		// check comment and skip the comment block
		if (c == '/') {
			c1 = inputFile.get();
			if (c1 == '*') {
				bool commentClosed = false;
				c = inputFile.get();

				while (c && commentClosed == false && !inputFile.eof()) {
					c = inputFile.get();

					if (c == '*') {
						c1 = inputFile.get();

						if (c1 == '/') {
							commentClosed = true;
						}
					}
				}

				// check if the comment block is closed
				if (commentClosed != true) {
					throw new Exception("Unclosed comment block.");
				}

				c = inputFile.get();
				if ((c == ' ') || (c == '\n') || (c == '\t')) { // skip spaces
					while ((c = inputFile.get()) && (c == ' ' || c == '\n') || (c == '\t'));
				}
			}
			else {
				// push back the last char in the stream if there is no comment
				inputFile.putback(c1);
			}
		}

		switch (c) {
			case '+':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::PLUS, tLexeme);
				// save the current position

				currPosition = inputFile.tellg();
				return t;
			}
			case '-':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::MINUS, tLexeme);
				// save the current position

				currPosition = inputFile.tellg();
				return t;
			}
			case '*':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::MULT, tLexeme);
				// save the current position
				currPosition = inputFile.tellg();
				return t;
			}
			case '/':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::DIV, tLexeme);
				// save the current position
				currPosition = inputFile.tellg();
				return t;
			}
			case ',':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::COMMA, tLexeme);
				// save the current position
				currPosition = inputFile.tellg();
				return t;
			}
			case ';':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::SEMICOLON, tLexeme);
				// save the current position
				currPosition = inputFile.tellg();
				return t;
			}
			case '(':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::LPAREN, tLexeme);

				// save the current position
				currPosition = inputFile.tellg();
				return t;
			}
			case ')':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::RPAREN, tLexeme);
				// save the current position
				currPosition = inputFile.tellg();
				return t;
			}
			case '[':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::LBRACKET, tLexeme);

				// save the current position
				currPosition = inputFile.tellg();
				return t;
			}
			case ']':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::RBRACKET, tLexeme);
				// save the current position
				currPosition = inputFile.tellg();
				return t;
			}
			case '{':
			{
					// lexeme
					std::string tLexeme;
					tLexeme.push_back(c);
					// token
					Token t(TokenType::LBRACE , tLexeme);
					// save the current position
					currPosition = inputFile.tellg();
					return t;
					}
			case '}':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				// token
				Token t(TokenType::RBRACE, tLexeme);
				// save the current position
				currPosition = inputFile.tellg();
				return t;
			}
			case '!':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				inputFile >> c1;

				if (c1 == '=') {
					tLexeme.push_back(c1);
					// token
					Token t(TokenType::NEQ, tLexeme);
					// save the current position
					currPosition = inputFile.tellg();
					return t;
				}
				else {
					throw new Exception(" Illegal character after!");
				}
			}
			case '=':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				inputFile >> c1;
				if (c1 == '=') {
					tLexeme.push_back(c1);
					// token
					Token t(TokenType::EQ, tLexeme);
					// save the current position
					currPosition = inputFile.tellg();
					return t;
				}
				else {
					// assignment operator
					// push back the last char in the stream
					inputFile.putback(c1);
					// token
					Token t(TokenType::ASSIGN, tLexeme);
					// save the current position
					currPosition = inputFile.tellg();
					return t;
				}
			}
			case '<':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				inputFile >> c1;

				if (c1 == '=') {
					tLexeme.push_back(c1);
					// token
					Token t(TokenType::LTE, tLexeme);
					// save the current position
					currPosition = inputFile.tellg();
					return t;
				}
				else {
					// < operator
					// push back the last char in the stream
					inputFile.putback(c1);
					// token
					Token t(TokenType::LT, tLexeme);
					// save the current position
					currPosition = inputFile.tellg();
					return t;
				}
			}
			case '>':
			{
				// lexeme
				std::string tLexeme;
				tLexeme.push_back(c);
				inputFile >> c1;
				if (c1 == '=') {
					tLexeme.push_back(c1);
					// token
					Token t(TokenType::GTE, tLexeme);
					// save the current position
					currPosition = inputFile.tellg();
					return t;
				}
				else {
					// > operator
					// push back the last char in the stream
					inputFile.putback(c1);
					// token
					Token t(TokenType::GT, tLexeme);
					// save the current position
					currPosition = inputFile.tellg();
					return t;
				}

			}
			case '0': // 0 constant or 0.x constant
			{
				std::string tLexeme;
				tLexeme.push_back(c);
				// numerical values are stored in these variables
				int iVal = 0;
				double xVal = 0.0;
				inputFile >> c1;
				if (isdigit(c1)) {
					throw new Exception("A decimal constant must start with 1-9");
				}
				else { // 0 constant
				// push back the last char in the stream
					inputFile.putback(c1);
					// the token
					Token t(TokenType::NUM, tLexeme, iVal);
					// save the current position
					currPosition = inputFile.tellg();
					return t;
				}
			}
			default:
			{
				if (isdigit(c)) { // a n constant or a x.y constant
				// lexeme
					std::string tLexeme;
					tLexeme.push_back(c);
					// numerical values are stored in these variables
					int iVal = 0;
					double xVal = 0.0;
					// update the values
					iVal = 10 * iVal + c - '0';
					xVal = 10 * xVal + c - '0';
					while ((c1 = inputFile.get()) && isdigit(c1)) { // decimal part
						iVal = 10 * iVal + c1 - '0';
						xVal = 10 * xVal + c1 - '0';
						tLexeme.push_back(c1);
					}

					// push back the last char in the stream
					inputFile.putback(c1);
					// the token
					Token t(TokenType::NUM, tLexeme, iVal);
					// save the current position
					currPosition = inputFile.tellg();

					return t;
				}
				else if (isalpha(c)) { // keyword or idifier
				// lexeme
					std::string tLexeme;
					tLexeme.push_back(c);
					// store lexeme characters
					while ((c1 = inputFile.get()) && (isalnum(c1) || c1 == '_')) {
						tLexeme.push_back(c1);
					}
					// push back the last char in the stream
					inputFile.putback(c1);
					// keyword test
					if (keywordMap.find(tLexeme) != keywordMap.end())
					{
						// keyword detected
						// search the keyword token type
						Token t(keywordMap[tLexeme], tLexeme);
						// save the current position
						currPosition = inputFile.tellg();
						return t;
					}
					else {
						// idifier
						// the token - the last tLexeme is the idifier
						Token t(TokenType::ID, tLexeme, tLexeme);
						// save the current position
						currPosition = inputFile.tellg();
						return t;
					}
				}
				else {
					throw new Exception(" Unknown character ");
				}
			}
		}
	} 
	// end of the file - the special token END
	std::string s("END");
	Token t(TokenType::END, s);
	return t;
}