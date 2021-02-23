
# ifndef TKTYPE
# define TKTYPE

# include <string>
# include <map>

// enum to store the type of a token
enum class TokenType {
	ID, NUM, INT, VOID, RETURN, IF, WHILE, ELSE, MULT, DIV, PLUS, MINUS,
	ASSIGN, LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,
	COMMA, SEMICOLON, EQ, NEQ, LT, LTE, GT, GTE, END
};
// map used to associate the token type of a keyword
typedef std::map < std::string, TokenType > KeywordMap;
// map used to write the type of a token
typedef std::map < TokenType, std::string > TokenTypeMap;

# endif