
# ifndef PARS
# define PARS
# include <string>
# include <memory>
# include "scanner.h"
# include "toktype.h"

class Parser {
	std::string fileName;
	std::unique_ptr < Scanner > scanner;
	TokenType tokType;

	//used to check conflicts between productions
	TokenType reserved_tokType;
public:
	Parser(std::string name);
	void parse();
private:
	void match(TokenType tt);
	void program();
	void declaration_list();
	void declaration_list1();
	void declaration();
	void var_declaration();
	void type_specifier();
	void fun_declaration();
	void params();
	void param_list();
	void param_list1();
	void param();
	void compound_stmt();
	void local_declarations();
	void local_declarations1();
	void statement_list();
	void statement_list1();
	void statement();
	void expression_stmt();
	void selection_stmt();
	void iteration_stmt();
	void return_stmt();
	void expression();
	void var();
	void simple_expression();
	void relop();
	void additive_expression();
	void additive_expression1();
	void addop();
	void term();
	void term1();
	void mulop();
	void factor();
	void call();
	void args();
	void arg_list();
	void arg_list1();
};

#endif