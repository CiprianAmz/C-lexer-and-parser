
# ifndef TOK
# define TOK

# include <fstream>
# include "toktype.h"

class Token {
	TokenType type;
	std::string lexeme;
	union {
		int num;
		std::string id;
		short oth;
	};
public:
	Token(TokenType t, std::string word, int n) :
		type(t), lexeme(word), num(n) {}
	Token(TokenType t, std::string word, std::string id) :
		type(t), lexeme(word), id(id) {}
	Token(TokenType t, std::string word) :
		type(t), lexeme(word), oth(1) {}
	// copy constructor is implicit defaulted
	Token(const Token& tok);
	// destructor is implicit defaulted
	~Token() {}
	// assignment operator is implicit defaulted

	Token& operator = (const Token& tok);
	TokenType getType() const { return type; }
	int getNum() const { return num; }
	std::string getId() const { return id; }
	void print(std::ofstream& out) const;
};

#endif