package plc.project; import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

/**
 * The lexer works through three main functions:
 *
 *  - {@link #lex()}, which repeatedly calls lexToken() and skips whitespace
 *  - {@link #lexToken()}, which lexes the next token
 *  - {@link CharStream}, which manages the state of the lexer and literals
 *
 * If the lexer fails to parse something (such as an unterminated string) you
 * should throw a {@link ParseException} with an index at the character which is
 * invalid or missing.
 *
 * The {@link #peek(String...)} and {@link #match(String...)} functions are
 * helpers you need to use, they will make the implementation a lot easier.
 */
public final class Lexer {

    private final CharStream chars;

    /*
    public static final Pattern
        IDENTIFIER  = Pattern.compile("[A-Za-z_] [A-Za-z0-9_-]*"),
        NUMBER = Pattern.compile("[+-]? [0-9]+ ('.' [0-9]+)?"),
        CHARACTER = Pattern.compile("[\'] ([^\'\\n\\r\\\\] | \\\\) [\']"),
        STRING = Pattern.compile("'\"' ([^\"\\n\\r\\\\] | \\\\)* '\"'"),
        ESCAPE = Pattern.compile("'\\\\' [bnrt'\"\\\\]"),
        OPERATOR = Pattern.compile("[<>!=] '='? | [\\w\\d]"),
        WHITESPACE = Pattern.compile("[a\b\\n\\r\\t]");

     */
    String identifierFirstLetter = "[a-zA-Z_]";
    String identifierAfterFirst = "[A-Za-z0-9_-]";
    String numberStart = "[0-9\\+-]";
    String number = "[0-9]";
    String decimal = "\\.";
    String numberAfter = "[0-9\\.\\+-]";
    String numberAfterDecimal = "[0-9]";
    String characterStart = "\'";
    String stringStartEnd = "\"";
    String escape = "\\\\";
    String escapeSecond = "[bnrt\\'\\\"\\\\]";
    String operator = "((<>!=)=?)|.";
    String pluseOrMinus = "[+-]";
    String whitespace = "[ \\\\b\\n\\r\\t]";


    public Lexer(String input) {
        chars = new CharStream(input);
    }

    /**
     * Repeatedly lexes the input using {@link #lexToken()}, also skipping over
     * whitespace where appropriate.
     */
    public List<Token> lex() {
        List<Token> tokenList = new ArrayList<Token>();
        while (chars.has(0)) {
            if (peek(whitespace)) {
                chars.advance();
                chars.skip();
            }
            else{
                tokenList.add(lexToken());
            }
        }
        return tokenList;
    }

    /**
     * This method determines the type of the next token, delegating to the
     * appropriate lex method. As such, it is best for this method to not change
     * the state of the char stream (thus, use peek not match).
     * * The next character should start a valid token since whitespace is handled
     * by {@link #lex()}
     */
    public Token lexToken() {
        if      (peek(identifierFirstLetter)) { return lexIdentifier(); }
        else if (peek(numberStart))           { return lexNumber(); }
        else if (peek(characterStart))        { return lexCharacter(); }
        else if (peek(stringStartEnd))        { return lexString(); }
        else if (peek(operator))              { return lexOperator(); }
        return null;
    }

    public Token lexIdentifier() {
        while(chars.has(0) && peek(identifierAfterFirst)) {
            match(identifierAfterFirst);
        }
        return chars.emit(Token.Type.IDENTIFIER);
    }

    public Token lexNumber() {
        if (peek(pluseOrMinus) && !chars.has(1)) {
            return lexOperator();
        }
        Token.Type tokenType = Token.Type.INTEGER;
        chars.advance();
        while(chars.has(0) && peek(number)) {
            chars.advance();
        }
        if (peek(decimal) && peekNext(number)) {
            tokenType = Token.Type.DECIMAL;
            chars.advance();
            while(peek(number)) {
                chars.advance();
            }
        }
        else {


        }
        return chars.emit(tokenType);
    }

    public Token lexCharacter() {
        chars.advance();
        if (peek(characterStart)) {
            throw new ParseException("Incorrectly formed char at line ", chars.getIndex());
        }
        if (peek(escape)) {
            lexEscape();
        }
        chars.advance();
        if (!peek(characterStart)) { throw new ParseException("Incorrectly formed char at line ", chars.getIndex()); }
        chars.advance();

        return  chars.emit(Token.Type.CHARACTER);
    }

    public Token lexString() {
        chars.advance();
        while (!peek(stringStartEnd) && chars.has(0)) {
            if (peek(escape)) {
                lexEscape();
            }
            if (peek("\n") || peek("\r")) {
                throw new ParseException("Unterminated string.", chars.getIndex());
            }
            chars.advance();
        }
        if (!chars.has(0)) {
            throw new ParseException("Unterminated string.", chars.getIndex());
        }
        chars.advance();
        return chars.emit(Token.Type.STRING);
    }

    public void lexEscape() {
        chars.advance();
        if (!peek(escapeSecond)) {
            throw new ParseException("Invalid character after escape.", chars.getIndex());
        }
    }

    public Token lexOperator() {
        char item = chars.get(0);
        switch (item) {
            case '<':
            case '>':
            case '!':
            case '=':
                if (chars.has(1) && chars.get(1) == '=') {
                    chars.advance();
                }
                break;
        }
        chars.advance();
        return chars.emit(Token.Type.OPERATOR);
    }

    /**
     * Returns true if the next sequence of characters match the given patterns,
     * which should be a regex. For example, {@code peek("a", "b", "c")} would
     * return true if the next characters are {@code 'a', 'b', 'c'}.
     */
    public boolean peek(String... patterns) {
        for (int i = 0; i < patterns.length; i++) {
            if (!chars.has(i) || !String.valueOf(chars.get(i)).matches(patterns[i])) {
                return false;
            }
        }
        return true;
    }

    public boolean peekNext(String... patterns) {
        for (int i = 0; i < patterns.length; i++) {
            if (!chars.has(i + 1) || !String.valueOf(chars.get(i + 1)).matches(patterns[i])) {
                return false;
            }
        }
        return true;
    }

    /**
     * Returns true in the same way as {@link #peek(String...)}, but also
     * advances the character stream past all matched characters if peek returns
     * true. Hint - it's easiest to have this method simply call peek.
     */
    public boolean match(String... patterns) {
        boolean peek = peek(patterns);
        if (peek) {
            for (int i = 0; i < patterns.length; i++) {
                chars.advance();
            }
        }
        return peek;
    }

    /**
     * A helper class maintaining the input string, current index of the char
     * stream, and the current length of the token being matched.
     *
     * You should rely on peek/match for state management in nearly all cases.
     * The only field you need to access is {@link #index} for any {@link
     * ParseException} which is thrown.
     */
    public static final class CharStream {

        private final String input;
        private int index = 0;
        private int length = 0;

        public CharStream(String input) {
            this.input = input;
        }

        public boolean has(int offset) {
            return index + offset < input.length();
        }

        public char get(int offset) {
            return input.charAt(index + offset);
        }

        public int getIndex() { return index; }

        public void advance() {
            index++;
            length++;
        }

        public void skip() {
            length = 0;
        }

        public Token emit(Token.Type type) {
            int start = index - length;
            skip();
            return new Token(type, input.substring(start, index), start);
        }

    }

}
