#include <regex>

class Lexer
{
	std::smatch match;
	std::string str;
	int line;
public:
	Lexer();
	Lexer(std::string const & str, int line);
	Lexer(Lexer const & rv);
	~Lexer();
	
	Lexer & operator=(Lexer const & rv);

	bool is_command1();
	bool is_command2();
	bool command_on_the_begin();
	bool is_arg();
	bool is_space();
	bool good_command();

	void check_lexer();

	class LexerException : public std::exception
	{
		std::string comment;
		int			line;
	public:
		LexerException();
		LexerException(std::string comment, int line);
		LexerException(LexerException const & rv);
		~LexerException() throw();
		
		LexerException & operator=(LexerException const & rv);

		virtual const char *what() const throw();
	};
};