# include "parser.h"
# include "exceptions.h"
# include <string>
# include <iostream>

Parser::Parser(std::string name) :
	scanner(std::make_unique < Scanner >(name)) {
	tokType = scanner->nextToken().getType();

	reserved_tokType = TokenType::END;
}
void Parser::match(TokenType tt) {
	if (tokType == tt) {
		Token tok = scanner->nextToken();
		tokType = tok.getType();
	}
	else if (tokType == TokenType::END) {
		std::cout << "End of file!!\n";
		exit(1);
	}
	else {
		throw Exception(" Illegal token type!");
	}
}
void Parser::parse() {
	program();
	std::cout << "The program is syntactically correct \n";
}

void Parser::program(){ 
	switch (tokType) {
	case TokenType::INT:
	case TokenType::VOID:
		declaration_list();
		break;
	default:
		throw Exception("<Program>: Illegal token!");
	}
}

void Parser::declaration_list(){
	switch (tokType) {
	case TokenType::INT:
	case TokenType::VOID:
		declaration();
		declaration_list1();
		break;
	default:
		throw Exception("<Declaration_list>: Illegal token!");
	}
}

void Parser::declaration_list1(){
	switch (tokType) {
	case TokenType::INT:
	case TokenType::VOID:
		declaration();
		declaration_list1();
		break;
	case TokenType::END:
		//Epsilon
		break;
	default:
		throw Exception("<Declaration_list>: Illegal token!");
	}
}

void Parser::declaration(){
	switch (tokType) {
	case TokenType::INT:
	case TokenType::VOID:
		type_specifier();
		match(TokenType::ID);

		reserved_tokType = TokenType::ID;
		
		switch(tokType) {
			case TokenType::SEMICOLON:
			case TokenType::LBRACKET:
				var_declaration();
				break;
			case TokenType::LPAREN:
				fun_declaration();
				break;
			default:
				throw Exception("<Declaration>: Illegal token!");
		}

		break;
	default:
		throw Exception("<Declaration>: Illegal token!");
	}
}

void Parser::var_declaration(){
	switch (tokType) {
	case TokenType::SEMICOLON:
		if(TokenType::ID == reserved_tokType)
		{
			reserved_tokType = TokenType::END;

			match(TokenType::SEMICOLON);
		}
		else {
			throw Exception("<Variable Declaration>: Illegal token!");
		}
		break;
	case TokenType::LBRACKET:
		if(TokenType::ID == reserved_tokType)
		{
			reserved_tokType = TokenType::END;

			match(TokenType::LBRACKET);
			match(TokenType::NUM);
			match(TokenType::RBRACKET);
			match(TokenType::SEMICOLON);
		}
		else {
			throw Exception("<Variable Declaration>: Illegal token!");
		}
		break;

	case TokenType::INT:
	case TokenType::VOID:
	if(TokenType::END == reserved_tokType)
	{
		type_specifier();
		match(TokenType::ID);

		if(TokenType::LBRACKET == tokType){
			match(TokenType::LBRACKET);
			match(TokenType::NUM);
			match(TokenType::RBRACKET);
		}

		match(TokenType::SEMICOLON);
	}
	else {
		throw Exception("<Variable Declaration>: Illegal token!");
	}
	break;

	default:
		throw Exception("<Variable Declaration>: Illegal token!");
	}
}

void Parser::type_specifier(){
	switch (tokType) {
	case TokenType::INT:
		match(TokenType::INT);
		break;
	case TokenType::VOID:
		match(TokenType::VOID);
		break;
	default:
		throw Exception("<Type Specifier>: Illegal token!");
	}
}

void Parser::fun_declaration(){
	switch (tokType) {
	case TokenType::LPAREN:
		if(TokenType::ID == reserved_tokType)
		{
			reserved_tokType = TokenType::END;
			
			match(TokenType::LPAREN);
			params();
			match(TokenType::RPAREN);
			compound_stmt();
		}
		else {
			throw Exception("<Function Declaration>: Illegal token!");
		}

		break;
	default:
		throw Exception("<Function Declaration>: Illegal token!");
	}
}

void Parser::params(){
	switch (tokType) {
	case TokenType::VOID:
		match(TokenType::VOID);
		break;
	case TokenType::INT:
		param_list();
		break;
	default:
		throw Exception("<Params>: Illegal token!");
	}
}

void Parser::param_list(){
	switch (tokType) {
	case TokenType::INT:
		param();
		param_list1();
		break;
	default:
		throw Exception("<Param list>: Illegal token!");
	}
}

void Parser::param_list1(){
	switch (tokType) {
	case TokenType::COMMA:
		match(TokenType::COMMA);
		param();
		param_list1();
		break;
	default:
		//Epsilon
		break;
	}
}

void Parser::param(){
	switch (tokType) {
	case TokenType::VOID:
	case TokenType::INT:
		type_specifier();
		match(TokenType::ID);
		
		if(TokenType::LBRACKET == tokType) {
			match(TokenType::LBRACKET);
			match(TokenType::ID);
			match(TokenType::RBRACKET);
		}

		break;
	default:
		throw Exception("<Param>: Illegal token!");
	}
}

void Parser::compound_stmt(){
	switch (tokType) {
	case TokenType::LBRACE:
		match(TokenType::LBRACE);
		local_declarations();
		statement_list();
		match(TokenType::RBRACE);
		break;
	default:
		throw Exception("<Compound Stmt>: Illegal token!");
	}
}

void Parser::local_declarations(){
	local_declarations1();
}

void Parser::local_declarations1(){
	switch (tokType) {
	case TokenType::INT:
	case TokenType::VOID:
		var_declaration();
		local_declarations1();
		break;
	default:
		//Epsilon
		break;
	}
}

void Parser::statement_list(){
	statement_list1();
}

void Parser::statement_list1(){
	switch (tokType) {
	case TokenType::ID:
	case TokenType::LPAREN:
	case TokenType::NUM:
	case TokenType::LBRACE:
	case TokenType::IF:
	case TokenType::WHILE:
	case TokenType::RETURN:
		statement();
		statement_list1();
		break;
	default:
		//Epsilon
		break;
	}
}

void Parser::statement(){
	switch (tokType) {
	case TokenType::ID:
	case TokenType::LPAREN:
	case TokenType::NUM:
		expression_stmt();
		break;
	case TokenType::LBRACE:
		compound_stmt();
		break;
	case TokenType::IF:
		selection_stmt();
		break;
	case TokenType::WHILE:
		iteration_stmt();
		break;
	case TokenType::RETURN:
		return_stmt();
		break;
	default:
		throw Exception("<Statement>: Illegal token!");
	}
}

void Parser::expression_stmt(){
	switch (tokType) {
	case TokenType::ID:
	case TokenType::LPAREN:
	case TokenType::NUM:
		expression();
		match(TokenType::SEMICOLON);
		break;
	case TokenType::COMMA:
		match(TokenType::SEMICOLON);
		break;
	default:
		throw Exception("<Expression Stmt>: Illegal token!");
	}
}

void Parser::selection_stmt(){
	switch (tokType) {
	case TokenType::IF:
		match(TokenType::IF);
		match(TokenType::LPAREN);
		expression();
		match(TokenType::RPAREN);
		statement();

		if(TokenType::ELSE == tokType) {
			match(TokenType::ELSE);
			statement();
		}

		break;
	default:
		throw Exception("<Selection Stmt>: Illegal token!");
	}
}

void Parser::iteration_stmt(){
	switch (tokType) {
	case TokenType::WHILE:
		match(TokenType::WHILE);
		match(TokenType::LPAREN);
		expression();
		match(TokenType::RPAREN);
		statement();
		break;
	default:
		throw Exception("<Iteration Stmt>: Illegal token!");
	}
}

void Parser::return_stmt(){
	switch (tokType) {
	case TokenType::RETURN:
		match(TokenType::RETURN);

		switch (tokType)
		{
		case TokenType::ID:
		case TokenType::LPAREN:
		case TokenType::NUM:
			expression();
			match(TokenType::SEMICOLON);
			break;
		case TokenType::SEMICOLON:
			match(TokenType::SEMICOLON);
			break;
		default:
			throw Exception("<Return Stmt>: Illegal token!");
			break;
		}

		break;
	default:
		throw Exception("<Return Stmt>: Illegal token!");
	}
}

void Parser::expression(){
	switch (tokType) {
	case TokenType::ID:
		var();

		// it the following item is one of the enumerated ones, that means the token is really a var
		if (TokenType::RPAREN != tokType &&
			TokenType::COMMA != tokType &&
			TokenType::SEMICOLON != tokType) {
			// check if it is an expression or just a term from a simple expression
			if (TokenType::ASSIGN == tokType) {
				match(TokenType::ASSIGN);
				expression();
			}
			else {
				reserved_tokType = TokenType::ID;
				simple_expression();
			}
		}

		break;
	case TokenType::LPAREN:
	case TokenType::NUM:
		simple_expression();
		break;
	default:
		throw Exception("<Expression>: Illegal token!");
	}
}

void Parser::var(){
	switch (tokType) {
	case TokenType::ID:
		match(TokenType::ID);

		if (TokenType::LBRACKET == tokType) {
			match(TokenType::LBRACKET);
			expression();
			match(TokenType::RBRACKET);
		}
		break;
	default:
		// ID was already matched as expression
		if(TokenType::ID == reserved_tokType) {
			reserved_tokType = TokenType::END;
	
			if (TokenType::LBRACKET == tokType) {
				match(TokenType::LBRACKET);
				expression();
				match(TokenType::RBRACKET);
			}
			break;
		}
		else {
			throw Exception("<Variable>: Illegal token!");
		}
	}
}

void Parser::simple_expression(){
	switch (tokType) {
	case TokenType::NUM:
	case TokenType::LPAREN:
	case TokenType::LBRACKET:
	case TokenType::ID:
		additive_expression();
		
		if(TokenType::LTE == tokType 
		|| TokenType::LT == tokType 
		|| TokenType::GT == tokType 
		|| TokenType::GTE == tokType 
		|| TokenType::EQ == tokType 
		|| TokenType::NEQ == tokType) {
			relop();
			additive_expression();
			}
		break;
	case TokenType::PLUS:
	case TokenType::MINUS: 
		if(TokenType::ID == reserved_tokType) {
			reserved_tokType = TokenType::END; 
			additive_expression1();
		}
		break;
	case TokenType::LTE:
	case TokenType::LT:
	case TokenType::GT:
	case TokenType::GTE:
	case TokenType::EQ:
	case TokenType::NEQ:
		if(TokenType::ID == reserved_tokType) {
			reserved_tokType = TokenType::END; 

			relop();
			additive_expression();
		}
		else {
			throw Exception("<Simple Expression>: Illegal token!");
		}

		break;
	default:
		throw Exception("<Simple Expression>: Illegal token!");
	}
}

void Parser::relop(){
	switch (tokType) {
	case TokenType::LTE:
		match(TokenType::LTE);
		break;
	case TokenType::LT:
		match(TokenType::LT);
		break;
	case TokenType::GT:
		match(TokenType::GT);
		break;
	case TokenType::GTE:
		match(TokenType::GTE);
		break;
	case TokenType::EQ:
		match(TokenType::EQ);
		break;
	case TokenType::NEQ:
		match(TokenType::NEQ);
		break;
	default:
		throw Exception("<Relop>: Illegal token!");
	}
}

void Parser::additive_expression(){
	switch (tokType) {
	case TokenType::NUM:
	case TokenType::LPAREN:
	case TokenType::LBRACKET:
	case TokenType::ID:
		term();
		additive_expression1();
		break;
	default:
		throw Exception("<Additive Expression>: Illegal token!");
	}
}

void Parser::additive_expression1(){
	switch (tokType) {
	case TokenType::PLUS:
	case TokenType::MINUS:
		addop();
		term();
		additive_expression1();
		break;
	default:
		// Epsilon
		break;
	}
}

void Parser::addop(){
	switch (tokType) {
	case TokenType::PLUS:
		match(TokenType::PLUS);
		break;
	case TokenType::MINUS:
		match(TokenType::MINUS);
		break;
	default:
		throw Exception("<Addop>: Illegal token!");
	}
}

void Parser::term(){
	switch (tokType) {
	case TokenType::NUM:
	case TokenType::LPAREN:
	case TokenType::LBRACKET:
	case TokenType::ID:
		factor();
		term1();
		break;
	default:
		throw Exception("<Term>: Illegal token!");
	}
}

void Parser::term1(){
	switch (tokType) {
	case TokenType::MULT:
	case TokenType::DIV:
		mulop();
		factor();
		term1();
		break;
	default:
		// Epsilon
		break;
	}
}

void Parser::mulop(){
	switch (tokType) {
	case TokenType::MULT:
		match(TokenType::MULT);
		break;
	case TokenType::DIV:
		match(TokenType::DIV);
		break;
	default:
		throw Exception("<Mulop>: Illegal token!");
	}
}

void Parser::factor(){
	switch (tokType) {
	case TokenType::NUM:
		match(TokenType::NUM);
		break;
	case TokenType::LPAREN:
		if(TokenType::END == reserved_tokType) {
			expression();
		}
		else {
			call();
		}
		break;
	case TokenType::LBRACKET:
		if(TokenType::END == reserved_tokType) {
			throw Exception("<Factor>: Illegal token!");
		}
		else {
			var();
		}
		break;
	case TokenType::ID:
		if(TokenType::ID == reserved_tokType) {
			throw Exception("<Factor>: Illegal token!");
		}
		else {
			match(TokenType::ID);
			reserved_tokType = TokenType::ID;
			
			if(TokenType::LPAREN == tokType){
				call();
			}
			else {
				var();
			}
		}

		break;
	default:
		throw Exception("<Factor>: Illegal token!");
	}
}

void Parser::call(){
	switch (tokType) {
	case TokenType::ID:
		if(TokenType::ID == reserved_tokType) {
			throw Exception("<Call>: Illegal token!");
		}
		else {
			match(TokenType::ID);
			match(TokenType::LPAREN);
			args();
			match(TokenType::RPAREN);
		}
		break;
	case TokenType::LPAREN:
		if(TokenType::END == reserved_tokType) {
			throw Exception("<Call>: Illegal token!");
		}
		else {
			reserved_tokType = TokenType::END;

			match(TokenType::LPAREN);
			args();
			match(TokenType::RPAREN);
		}
		break;
	default:
		throw Exception("<Call>: Illegal token!");
	}
}

void Parser::args(){
	switch (tokType) {
	case TokenType::ID:
	case TokenType::LPAREN:
	case TokenType::NUM:
		arg_list();
		break;
	default:
		// Epsilon - no args
		break;
	}
}

void Parser::arg_list(){
	switch (tokType) {
	case TokenType::ID:
	case TokenType::LPAREN:
	case TokenType::NUM:
		expression();
		arg_list1();
		break;
	default:
		throw Exception("<Arg List>: Illegal token!");
	}
}

void Parser::arg_list1(){
	switch (tokType) {
	case TokenType::COMMA:
		match(TokenType::COMMA);
		expression();
		arg_list1();
		break;
	default:
		//Epsilon
		break;
	}
}