package plc.project;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.regex.Pattern;

/**
 * The parser takes the sequence of tokens emitted by the lexer and turns that
 * into a structured representation of the program, called the Abstract Syntax
 * Tree (AST).
 *
 * The parser has a similar architecture to the lexer, just with {@link Token}s
 * instead of characters. As before, {@link #peek(Object...)} and {@link
 * #match(Object...)} are helpers to make the implementation easier.
 *
 * This type of parser is called <em>recursive descent</em>. Each rule in our
 * grammar will have it's own function, and reference to other rules correspond
 * to calling that functions.
 */
public final class Parser {

    private final TokenStream tokens;

    public Parser(List<Token> tokens) {
        this.tokens = new TokenStream(tokens);
    }

    /**
     * Parses the {@code source} rule.
     */
    String let = "LET";
    String def = "DEF";
    public Ast.Source parseSource() throws ParseException {
        List<Ast.Field> fields = new ArrayList<>();
        List<Ast.Method> methods = new ArrayList<>();
        while (match(let)) {
            fields.add(parseField());
        }
        while (match(def)) {
            methods.add(parseMethod());
        }
        return new Ast.Source(fields, methods);
    }

    /**
     * Parses the {@code field} rule. This method should only be called if the
     * next tokens start a field, aka {@code LET}.
     */
    public Ast.Field parseField() throws ParseException {
        Optional<Ast.Expr> value = Optional.empty();
        if (!match(Token.Type.IDENTIFIER)) {
            throw new ParseException("Expected identifier.", tokens.index);
        }
        String name = tokens.get(-1).getLiteral();
        if (match("=")) {
            value = Optional.of(parseExpression());
        }
        if (!match(";")) {
            throw new ParseException("Expected semicolon.", tokens.index);
        }
        return new Ast.Field(name, value);
    }

    /**
     * Parses the {@code method} rule. This method should only be called if the
     * next tokens start a method, aka {@code DEF}.
     */
    String do_PLC = "DO";
    String end_PLC = "END";
    public Ast.Method parseMethod() throws ParseException {
        List<String> parameters = new ArrayList<>();
        List<Ast.Stmt> statements = new ArrayList<>();
        if (!match(Token.Type.IDENTIFIER)) {
            throw new ParseException("Expected identifier.", tokens.index);
        }
        String name = tokens.get(-1).getLiteral();
        if (!match("(")) {
            throw new ParseException("Expected open paranthesis.", tokens.index);
        }
        if (match(Token.Type.IDENTIFIER)) {
            parameters.add(tokens.get(-1).getLiteral());
        }
        while (!match(")")) {
            if (!match(",")) {
                throw new ParseException("Expected comma.", tokens.index);
            }
            if (!match(Token.Type.IDENTIFIER)) {
                throw new ParseException("Expected identifier.", tokens.index);
            }
            parameters.add(tokens.get(-1).getLiteral());
        }
        if (!match(do_PLC)) {
            throw new ParseException("Expected \"DO\".", tokens.index);
        }

        while (!match(end_PLC)) {
            statements.add(parseStatement());
        }

        return new Ast.Method(name, parameters, statements);
    }

    /**
     * Parses the {@code statement} rule and delegates to the necessary method.
     * If the next tokens do not start a declaration, if, while, or return
     * statement, then it is an expression/assignment statement.
     */
    String declaration_PLC = "LET";
    String for_PLC = "FOR";
    String if_PLC = "IF";
    String while_PLC = "WHILE";
    String return_PLC = "RETURN";
    String else_PLC = "ELSE";
    public Ast.Stmt parseStatement() throws ParseException {
        if(peek(declaration_PLC)) {
            return parseDeclarationStatement();
        }
        if(peek(if_PLC)) {
            return parseIfStatement();
        }
        if(peek(for_PLC)) {
            return parseForStatement();
        }
        if(peek(while_PLC)) {
            return parseWhileStatement();
        }
        if(peek(return_PLC)) {
            return parseReturnStatement();
        }
        else {
            Ast.Expr expr = parseExpression();
            // TODO: If the next token is =, then need to handle and assignment.
            if (match("=")) {
                Ast.Expr exprValue = parseExpression();
                if (!match(";")) {
                    throw new ParseException("Expected semicolon.", tokens.index);
                }
                return new Ast.Stmt.Assignment(expr, exprValue);
            }
            if (!match(";")) {
                throw new ParseException("Expected semicolon.", tokens.index);
            }
            return new Ast.Stmt.Expression((expr));
        }
    }

    /**
     * Parses a declaration statement from the {@code statement} rule. This
     * method should only be called if the next tokens start a declaration
     * statement, aka {@code LET}.
     */
    public Ast.Stmt.Declaration parseDeclarationStatement() throws ParseException {
        match(declaration_PLC);
        if(!match(Token.Type.IDENTIFIER)) {
            throw new ParseException("Expected identifier", tokens.index);
        }
        String name = tokens.get(-1).getLiteral();

        Optional<Ast.Expr> value = Optional.empty();
        // Below does the check if we are going to have the optional empty or not.
        if (match("=")) {
            value = Optional.of(parseExpression());
        }

        if(!match(";")) {
            throw new ParseException("Expected semicolon.", tokens.index);
        }
        return new Ast.Stmt.Declaration(name, value);
    }

    /**
     * Parses an if statement from the {@code statement} rule. This method
     * should only be called if the next tokens start an if statement, aka
     * {@code IF}.
     */
    public Ast.Stmt.If parseIfStatement() throws ParseException {
        match(if_PLC);
        List<Ast.Stmt> thenStatements = new ArrayList<>();
        List<Ast.Stmt> elseStatements = new ArrayList<>();

        Ast.Expr condition = parseExpression();
        if (!match(do_PLC)) {
            throw new ParseException("Expected \"DO\".", tokens.index);
        }
        while (!peek(else_PLC) & !peek(end_PLC)) {
            thenStatements.add(parseStatement());
        }
        if(match(else_PLC)) {
            while (!match(end_PLC)) {
                elseStatements.add(parseStatement());
            }
        }
        return new Ast.Stmt.If(condition, thenStatements, elseStatements);
    }

    /**
     * Parses a for statement from the {@code statement} rule. This method
     * should only be called if the next tokens start a for statement, aka
     * {@code FOR}.
     */
    String in_PLC = "IN";
    public Ast.Stmt.For parseForStatement() throws ParseException {
        match((for_PLC));
        if (!match(Token.Type.IDENTIFIER)) {
            throw new ParseException("Expected identifier", tokens.index);
        }
        String name = tokens.get(-1).getLiteral();
        if (!match(in_PLC)) {
            throw new ParseException("Expected \"IN\"", tokens.index);
        }
        Ast.Expr value = parseExpression();
        List<Ast.Stmt> statements = new ArrayList<>();
        if (!match(do_PLC)) {
            throw new ParseException("Expected \"DO\"", tokens.index);
        }
        while (!match(end_PLC)) {
            statements.add(parseStatement());
        }
        return new Ast.Stmt.For(name, value, statements);
    }

    /**
     * Parses a while statement from the {@code statement} rule. This method
     * should only be called if the next tokens start a while statement, aka
     * {@code WHILE}.
     */
    public Ast.Stmt.While parseWhileStatement() throws ParseException {
        match(while_PLC);
        Ast.Expr condition = parseExpression();
        if (!match(do_PLC)) {
            throw new ParseException("Expected \"DO\"", tokens.index);
        }
        List<Ast.Stmt> statements = new ArrayList<>();
        while (!match(end_PLC)) {
            statements.add(parseStatement());
        }
        return new Ast.Stmt.While(condition, statements);
    }

    /**
     * Parses a return statement from the {@code statement} rule. This method
     * should only be called if the next tokens start a return statement, aka
     * {@code RETURN}.
     */
    public Ast.Stmt.Return parseReturnStatement() throws ParseException {
        match(return_PLC);
        Ast.Expr expression = parseExpression();
        if (!match(";")) {
            throw new ParseException("Expected \";\"", tokens.index);
        }
        return new Ast.Stmt.Return(expression);
    }

    /**
     * Parses the {@code expression} rule.
     */
    public Ast.Expr parseExpression() throws ParseException {
        Ast.Expr expr = parseLogicalExpression();
        return expr;
    }

    /**
     * Parses the {@code logical-expression} rule.
     */
    String logicalExpression = "((\\bAND\\b)|(OR)|(<)|(>)|(>=)|(<=)|(!=))";
    String and = "AND";
    String or = "OR";
    String lessThan = "<";
    String greaterThan = ">";
    String lessThanOrEqual = "<=";
    String greaterThanOrEqual = ">=";
    String notEqual = "!=";
    String equal = "==";
    String add = "+";
    String subtract = "-";
    String multiply = "*";
    String divide = "/";

    public Ast.Expr parseLogicalExpression() throws ParseException {
        Ast.Expr left = parseEqualityExpression();
        Ast.Expr right;
        String operator;

        if (match(and)) {
            operator = tokens.get(-1).getLiteral(); // This will return the literal string of the variable
            right = parseAdditiveExpression();
            return new Ast.Expr.Binary(operator, left, right);
        }
        else if (match(or)) {
            operator = tokens.get(-1).getLiteral(); // This will return the literal string of the variable
            right = parseAdditiveExpression();
            return new Ast.Expr.Binary(operator, left, right);
        }
        return left;
    }

    /**
     * Parses the {@code equality-expression} rule.
     */
    public Ast.Expr parseEqualityExpression() throws ParseException {
        Ast.Expr left = parseAdditiveExpression();
        Ast.Expr right;
        String operator;

        if (match(equal)) {
            operator = tokens.get(-1).getLiteral(); // This will return the literal string of the variable
            right = parseAdditiveExpression();
            return new Ast.Expr.Binary(operator, left, right);
        }
        else if (match(notEqual)) {
            operator = tokens.get(-1).getLiteral(); // This will return the literal string of the variable
            right = parseAdditiveExpression();
            return new Ast.Expr.Binary(operator, left, right);
        }
        return left;
    }

    /**
     * Parses the {@code additive-expression} rule.
     */
    String additiveExpr = "(+)|(-)";
    public Ast.Expr parseAdditiveExpression() throws ParseException {
        Ast.Expr left = parseMultiplicativeExpression();
        Ast.Expr right;
        String operator;

        if (match(add)) {
            operator = tokens.get(-1).getLiteral(); // This will return the literal string of the variable
            right = parseAdditiveExpression();
            return new Ast.Expr.Binary(operator, left, right);
        }
        else if (match(subtract)) {
            operator = tokens.get(-1).getLiteral(); // This will return the literal string of the variable
            right = parseAdditiveExpression();
            return new Ast.Expr.Binary(operator, left, right);
        }
        return left;
    }

    /**
     * Parses the {@code multiplicative-expression} rule.
     */
    String multiplicativeExpr = "(*)|(/)";
    public Ast.Expr parseMultiplicativeExpression() throws ParseException {
        Ast.Expr left = parseSecondaryExpression();
        Ast.Expr right;
        String operator;

        if (match(multiply)) {
            operator = tokens.get(-1).getLiteral(); // This will return the literal string of the variable
            right = parseAdditiveExpression();
            return new Ast.Expr.Binary(operator, left, right);
        }
        else if (match(divide)) {
            operator = tokens.get(-1).getLiteral(); // This will return the literal string of the variable
            right = parseAdditiveExpression();
            return new Ast.Expr.Binary(operator, left, right);
        }
        return left;
    }

    /**
     * Parses the {@code secondary-expression} rule.
     */
    public Ast.Expr parseSecondaryExpression() throws ParseException {
        Ast.Expr expr = parsePrimaryExpression();
        if (match(".")) {
            if (!match(Token.Type.IDENTIFIER)) {
                throw new ParseException("Expected Identifier.", tokens.index);
            }
            else {
                Optional<Ast.Expr> reciever = Optional.empty();
                reciever = Optional.of(expr);
                List<Ast.Expr> arguments = new ArrayList<Ast.Expr>(); // Only if funciton is used
                String name = tokens.get(-1).getLiteral(); // This will return the literal string of the variable

                if (match("(")) {
                    Ast.Expr.Function exprFunction;
                    if (match(")")) {
                        return new Ast.Expr.Function( reciever, name, arguments);
                    } else {
                        while (!match(")")) {
                            if (!match(",")) {
                                throw new ParseException("Expected comma between arguments", tokens.index);
                            }
                            arguments.add(parseExpression());
                        }
                    }
                    // TODO: Need to figure out how to handle reciever
                    exprFunction = new Ast.Expr.Function(Optional.empty(), name, arguments);
                    return exprFunction;
                } else {
                    return new Ast.Expr.Access(reciever, name);
                }
            }
        }
        return expr;
    }

    /**
     * Parses the {@code primary-expression} rule. This is the top-level rule
     * for expressions and includes literal values, grouping, variables, and
     * functions. It may be helpful to break these up into other methods but is
     * not strictly necessary.
     */
    String aTrue = "TRUE";
    String aFalse = "FALSE";
    String nil = "NIL";
    private String correctString(String input) {
        input = input.substring(1, input.length() - 1);
        input = input.replace("\\n", "\n");
        input = input.replace("\\t", "\t");
        input = input.replace("\\b", "\b");
        input = input.replace("\\r", "\r");
        input = input.replace("\\'", "\'");
        input = input.replace("\\\"", "\"");
        input = input.replace("\\\\", "\\");
        return input;
    }
    public Ast.Expr parsePrimaryExpression() throws ParseException {
        if (match(aTrue))       { return new Ast.Expr.Literal(true); }
        else if (match(aFalse)) { return new Ast.Expr.Literal(false); }
        else if (match(nil))    { return new Ast.Expr.Literal(null); }
        else if (match(Token.Type.INTEGER)) {
            BigInteger integer = new BigInteger(tokens.get(-1).getLiteral());
            return new Ast.Expr.Literal(integer);
        } else if (match(Token.Type.DECIMAL)) {
            BigDecimal decimal = new BigDecimal(tokens.get(-1).getLiteral());
            return new Ast.Expr.Literal(decimal);
        } else if (match(Token.Type.CHARACTER)) {
            Character character = new Character((tokens.get(-1).getLiteral().replaceAll("(\\')", "")).charAt(0));
            return new Ast.Expr.Literal(character);
        } else if (match(Token.Type.STRING)) {
            String newString = new String(tokens.get(-1).getLiteral());
            newString = correctString(newString);
            return new Ast.Expr.Literal(newString);
        } else if (match("(")) {
            Ast.Expr.Group exprGroup = new Ast.Expr.Group(parseExpression());
            if(!match(")")) {
                throw new ParseException("Expected Closing Parenthesis.", tokens.index);
            }
            return exprGroup;
        } else if (match(Token.Type.IDENTIFIER)) {
            String name = tokens.get(-1).getLiteral(); // This will return the literal string of the variable
            List<Ast.Expr> arguments = new ArrayList<Ast.Expr>();
            if (match("(")) {
                Ast.Expr.Function exprFunction;
                if (match(")")) {
                    return new Ast.Expr.Function(Optional.empty(), name, arguments);
                }
                else {
                    arguments.add(parseExpression());
                    while (!match(")")) {
                        if (!match(",")) {
                            throw new ParseException("Expected comma between arguments", tokens.index);
                        }
                        arguments.add(parseExpression());
                    }
                }
                // TODO: Need to figure out how to handle reciever
                exprFunction = new Ast.Expr.Function(Optional.empty(),name, arguments);
                return exprFunction;
            }
            return new Ast.Expr.Access( Optional.empty(), name);
            // obj.method(), obj is the reciever
        } else if (match("(")) {
            Ast.Expr expr = parseExpression();
            if (!match(")")) {
                throw new ParseException("Expected closing parenthesis.", tokens.index);
            }
            return new Ast.Expr.Group(expr);
        } else {
            throw new ParseException("Invalid Primary Expression", tokens.index); //TODO
        }
    }

    /**
     * As in the lexer, returns {@code true} if the current sequence of tokens
     * matches the given patterns. Unlike the lexer, the pattern is not a regex;
     * instead it is either a {@link Token.Type}, which matches if the token's
     * type is the same, or a {@link String}, which matches if the token's
     * literal is the same.
     *
     * In other words, {@code Token(IDENTIFIER, "literal")} is matched by both
     * {@code peek(Token.Type.IDENTIFIER)} and {@code peek("literal")}.
     */
    private boolean peek(Object... patterns) {
        for (int i =0; i < patterns.length; i++) {
            if ( !tokens.has(i)) {
                return false;
            }
            else if(patterns[i] instanceof Token.Type) {
                if (patterns[i] != tokens.get(i).getType()) {
                    return false;
                }
            }
            else if(patterns[i] instanceof String) {
                if (!patterns[i].equals(tokens.get(i).getLiteral())) {
                    return false;
                }
            }
            else {
                throw new AssertionError("Invalid pattern object: " + patterns[i].getClass());
            }
        }
        return true;
    }

    /**
     * As in the lexer, returns {@code true} if {@link #peek(Object...)} is true
     * and advances the token stream.
     */
    private boolean match(Object... patterns) {
        boolean peek = peek(patterns);
        if (peek) {
            for (int i = 0; i < patterns.length; i++) {
                tokens.advance();
            }
        }
        return peek;
    }

    private static final class TokenStream {

        private final List<Token> tokens;
        private int index = 0;

        private TokenStream(List<Token> tokens) {
            this.tokens = tokens;
        }

        /**
         * Returns true if there is a token at index + offset.
         */
        public boolean has(int offset) {
            return index + offset < tokens.size();
        }

        /**
         * Gets the token at index + offset.
         */
        public Token get(int offset) {
            return tokens.get(index + offset);
        }

        /**
         * Advances to the next token, incrementing the index.
         */
        public void advance() {
            index++;
        }

    }

}
