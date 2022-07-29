package plc.project;


import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * See the specification for information about what the different visit
 * methods should do.
 */
public final class Analyzer implements Ast.Visitor<Void> {

    public Scope scope;
    private Ast.Method method;

    public Analyzer(Scope parent) {
        scope = new Scope(parent);
        scope.defineFunction("print", "System.out.println", Arrays.asList(Environment.Type.ANY), Environment.Type.NIL, args -> Environment.NIL);
    }

    public Scope getScope() {
        return scope;
    }

    @Override
    public Void visit(Ast.Source ast) {
        boolean hasMain = false;
        List<Ast.Field> fieldList = ast.getFields();
        List<Ast.Method> methodList = ast.getMethods();
        for (Ast.Field field : fieldList) {
            visit(field);
        }
        for (Ast.Method method : methodList) {
            visit(method);
            if (method.getName().equals("main")) {
                hasMain = true;
                if (!method.getReturnTypeName().get().equals("Integer")) {
                    throw new RuntimeException("Main does not return type Integer.");
                }
            }
        }
        if (!hasMain) {
            throw new RuntimeException("There is no main.");
        }
        return null;
    }

    @Override
    public Void visit(Ast.Field ast) {
        Environment.Type type = Environment.getType(ast.getTypeName());
        if (ast.getValue().isPresent()) {
            visit(ast.getValue().get());

            requireAssignable(type, ast.getValue().get().getType());
        }
        ast.setVariable(scope.defineVariable(ast.getName(), ast.getName(), type, Environment.NIL));

        return null;
    }

    @Override
    public Void visit(Ast.Method ast) {
        Environment.Function function;
        List<Environment.Type> paramTypes = new ArrayList<>();
        Environment.Type returnType;

        // The funcitons param types and return types are retrieved from the environment using the corresponding names in the method.
       for (String paramName : ast.getParameterTypeNames()) {
           paramTypes.add(Environment.getType(paramName));
       }
       if (ast.getReturnTypeName().isPresent()) {
           returnType = Environment.getType(ast.getReturnTypeName().get());
       }
       else {
           returnType = Environment.Type.NIL;
       }

       scope.defineVariable("returnVariable", "returnVariable", returnType, Environment.NIL);

        ast.setFunction( scope.defineFunction(ast.getName(), ast.getName(), paramTypes, returnType, args -> Environment.NIL));
        //scope.defineFunction(ast.getName(), ast.getName(), paramTypes, returnType, args -> Environment.NIL);
        // visit all the method's statements inside of a new scope containing variables for each parameter,.

        scope = new Scope(scope);
        // containing variables for each parameter?
        List<String> params = ast.getParameters();
        for (int i = 0; i < ast.getParameters().size(); i++) {
            scope.defineVariable(params.get(i), params.get(i), paramTypes.get(i), Environment.NIL);

        }
        for (Ast.Stmt statement : ast.getStatements()) {
            visit(statement);
        }
        // TODO handle return situation
        scope = scope.getParent();

        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Expression ast) {
        // TODO: Validates the expression statement?
        visit(ast.getExpression());

        // The expr in stmt needs to be a function

        //requireAssignable(Ast.Expr.Function, ast.getExpression().getType());

        if (ast.getExpression() instanceof Ast.Expr.Function) {
            // Northing right now
        }
        else {
            throw new RuntimeException("expression is not of type function.");
        }

        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Declaration ast) {
        // 'LET' identifier (':' identifier)? ('=' expression)? ';

        /*
        Optional optTypeName = ast.getTypeName();
        Optional<Ast.Expr> optValue = ast.getValue();

        if (!optTypeName.isPresent() && !optValue.isPresent()) {
            throw new RuntimeException("Declaration must have type or value to infer type.");
        }
        Environment.Type type = null;
        if (optTypeName.isPresent()) {
             type = Environment.getType(optTypeName.get());

            Object obj = optTypeName.get();
            String typeName = null;
            if (obj instanceof String) {
                typeName = (String) obj;
            }
            type = Environment.getType(typeName);
        }
        */

        // Solution from lecture

        if (!ast.getTypeName().isPresent() && !ast.getValue().isPresent()) {
            throw new RuntimeException("Declaration must have type or value to infer type.");
        }
        Environment.Type type = null;
        if (ast.getTypeName().isPresent()) {
            type = Environment.getType(ast.getTypeName().get());
        }

        if (ast.getValue().isPresent()) {
            visit(ast.getValue().get());
            if (type == null) {
                // case no type
                type = ast.getValue().get().getType();
            }
            requireAssignable(type, ast.getValue().get().getType());
        }
        ast.setVariable(scope.defineVariable(ast.getName(), ast.getName(), type, Environment.NIL));


        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Assignment ast) {

        if (ast.getReceiver() instanceof Ast.Expr.Access) {

        }
        else {
            throw new RuntimeException("Receiver is not an access expression");
        }
        // Validate an assignment statement
        visit(ast.getValue());
        visit(ast.getReceiver());
        requireAssignable(ast.getValue().getType(), ast.getReceiver().getType());

        return null;
    }

    @Override
    public Void visit(Ast.Stmt.If ast) {
        visit(ast.getCondition());
        // Validates and iff statement
        requireAssignable(Environment.Type.BOOLEAN, ast.getCondition().getType());

        if (ast.getThenStatements().isEmpty()) {
            throw new RuntimeException("The \'then statements\' in if statement.");
        }
        try {
            scope = new Scope(scope);
            for ( Ast.Stmt stmt : ast.getThenStatements()) {
                visit(stmt);
            }
        }
        finally {
            scope = scope.getParent();
        }
        try {
            scope = new Scope(scope);
            for ( Ast.Stmt stmt : ast.getElseStatements()) {
                visit(stmt);
            }
        }
        finally {
            scope = scope.getParent();
        }
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.For ast) {
        visit(ast.getValue());

        if ((ast.getStatements().size() == 0) || (ast.getValue().getType() != Environment.Type.INTEGER_ITERABLE)) {
            throw new RuntimeException("No statements in FOR.");
        }
        else {
            scope = new Scope(scope);

            // Scope should have variable defined
            scope.defineVariable(ast.getName(), ast.getName(), Environment.Type.INTEGER_ITERABLE, Environment.NIL);

            // Visit all of the for loops statements in a new scope
            for (Ast.Stmt statement : ast.getStatements()) {
                visit(statement);
            }

            scope = scope.getParent();

        }

        return null;
    }

    @Override
    public Void visit(Ast.Stmt.While ast) {
        visit(ast.getCondition());

        requireAssignable(Environment.Type.BOOLEAN, ast.getCondition().getType());

        scope = new Scope(scope);

        for (Ast.Stmt statements : ast.getStatements()) {
            visit(statements);
        }

        scope = scope.getParent();


        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Return ast) {
        visit(ast.getValue());

        Environment.Variable returnVariable = scope.lookupVariable("returnVariable");

        requireAssignable(returnVariable.getType(), ast.getValue().getType());

        return null;
    }

    @Override
    public Void visit(Ast.Expr.Literal ast) {

        if (ast.getLiteral() == Environment.NIL) {
            ast.setType(Environment.Type.NIL);
        }
        else if (ast.getLiteral() instanceof Boolean) {
            ast.setType(Environment.Type.BOOLEAN);
        }
        else if (ast.getLiteral() instanceof Character) {
            ast.setType(Environment.Type.CHARACTER);
        }
        else if (ast.getLiteral() instanceof String) {
            ast.setType(Environment.Type.STRING);
        }
        else if (ast.getLiteral() instanceof BigInteger) {
            ast.setType(Environment.Type.INTEGER);
            BigInteger bigInteger = (BigInteger) ast.getLiteral();
            if (    (bigInteger.compareTo(BigInteger.valueOf(Integer.MAX_VALUE)) > 0) ||
                    (bigInteger.compareTo(BigInteger.valueOf(Integer.MIN_VALUE)) < 0)) {
                throw new RuntimeException("BigInt is out of range.");
            }
        }
        else if (ast.getLiteral() instanceof BigDecimal) {
            ast.setType(Environment.Type.DECIMAL);
            BigDecimal bigDecimal = (BigDecimal) ast.getLiteral();
            if ((Double.compare(Double.POSITIVE_INFINITY, bigDecimal.doubleValue()) == 0) ||
                 (Double.compare(Double.NEGATIVE_INFINITY, bigDecimal.doubleValue()) == 0)) {
                throw new RuntimeException("BigDecimal is out of range.");
            }
        }
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Group ast) {
        if (ast.getExpression() instanceof Ast.Expr.Binary) {
            visit(ast.getExpression());
            ast.setType(ast.getExpression().getType());
        }
        else {
            throw new RuntimeException("Not a binary expression.");
        }
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Binary ast) {
        // Validate binary expression.
        visit(ast.getLeft());
        visit(ast.getRight());

        // Use this to determine what happens
        String operator = ast.getOperator();

        if (operator.equals("AND") || operator.equals("OR")) {
            requireAssignable(Environment.Type.BOOLEAN, ast.getLeft().getType());
            requireAssignable(Environment.Type.BOOLEAN, ast.getRight().getType());
            ast.setType(Environment.Type.BOOLEAN); // set the type for hte operation
        }
        else if (operator.equals("<")  ||
                 operator.equals("<+") ||
                 operator.equals(">")  ||
                 operator.equals(">=") ||
                 operator.equals("==") ||
                 operator.equals("!=")) {
            requireAssignable(Environment.Type.COMPARABLE, ast.getRight().getType());
            requireAssignable(Environment.Type.COMPARABLE, ast.getRight().getType());
            requireAssignable(ast.getLeft().getType(), ast.getRight().getType());
            requireAssignable(ast.getRight().getType(), ast.getLeft().getType());
            ast.setType(Environment.Type.BOOLEAN); // set the type for hte operation
        }
        else if (operator.equals("+")) {
            if (ast.getLeft().getType() == Environment.Type.STRING || ast.getRight().getType() == Environment.Type.STRING) {
                ast.setType(Environment.Type.STRING); // set the type for hte operation
            }
            else if (ast.getLeft().getType() == Environment.Type.INTEGER) {
                requireAssignable(ast.getLeft().getType(), ast.getRight().getType());
                ast.setType(Environment.Type.INTEGER); // set the type for hte operation
            }
            else if (ast.getLeft().getType() == Environment.Type.DECIMAL) {
                requireAssignable(ast.getLeft().getType(), ast.getRight().getType());
                ast.setType(Environment.Type.DECIMAL); // set the type for hte operation
            }
            else {
                throw new RuntimeException("Binary opeartion types are not compatible");
            }
        }
        else if (operator.equals("-") ||
                 operator.equals("*") ||
                 operator.equals("/")) {
            if (ast.getLeft().getType() == Environment.Type.INTEGER) {
                requireAssignable(ast.getLeft().getType(), ast.getRight().getType());
                ast.setType(Environment.Type.INTEGER); // set the type for hte operation
            }
            else if (ast.getLeft().getType() == Environment.Type.DECIMAL) {
                requireAssignable(ast.getLeft().getType(), ast.getRight().getType());
                ast.setType(Environment.Type.DECIMAL); // set the type for hte operation
            }
            else {
                throw new RuntimeException("Binary operation types are not compatible");
            }
        }
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Access ast) {
        if (ast.getReceiver().isPresent()) {
            Ast.Expr receiver = ast.getReceiver().get();
            visit(receiver);
            //scope = new Scope(scope);
            ast.setVariable(receiver.getType().getField(ast.getName()));
            //scope = scope.getParent();
        }
        else {
            ast.setVariable(scope.lookupVariable(ast.getName()));
        }

        return null;
    }

    @Override
    public Void visit(Ast.Expr.Function ast) {

        if (ast.getReceiver().isPresent()) {
            // If receiver is present
            // check that arguments are assignable to the corresponding parameter type.
            for (int i = 0; i < ast.getArguments().size(); i++) {
                requireAssignable(scope.lookupFunction(ast.getName(), ast.getArguments().size()).getParameterTypes().get(i + 1), ast.getArguments().get(i).getType());
            }

            //The function is a method of the receiver, if present, otherwise it is a function in teh current scope.
            visit(ast.getReceiver().get());
            Ast.Expr receiver = ast.getReceiver().get();
            Environment.Function receiverFunction = receiver.getType().getMethod(ast.getName(), ast.getArguments().size());
            // set the function of the express

            // Validates teh funciton expression
            // Set the type of the expression to be the return type of the funciton.
            for (int i = 0; i < ast.getArguments().size(); i++) {
                visit(ast.getArguments().get(i));
                requireAssignable(scope.lookupFunction(ast.getName(), ast.getArguments().size()).getParameterTypes().get(i), ast.getArguments().get(i).getType());
            }
            ast.setFunction(receiverFunction);
        }
        else {
            // otherwise it is a function in the current scope.
            for (int i = 0; i < ast.getArguments().size(); i++) {
                visit(ast.getArguments().get(i));
                requireAssignable(scope.lookupFunction(ast.getName(), ast.getArguments().size()).getParameterTypes().get(i), ast.getArguments().get(i).getType());
            }
            ast.setFunction(scope.lookupFunction(ast.getName(), ast.getArguments().size()));
        }
        return null;
    }

    public static void requireAssignable(Environment.Type target, Environment.Type type) {
        // The two types must be the same
        if (target != Environment.Type.ANY) {
            if (Environment.Type.COMPARABLE == target) {
                // good to go
                if (    type == Environment.Type.INTEGER   ||
                        type == Environment.Type.DECIMAL   ||
                        type == Environment.Type.CHARACTER ||
                        type == Environment.Type.STRING) {
                    // Good to goooo
                }
                else {
                    throw new RuntimeException("Comparable can only be assigned Integer, Decimal, String, or Character Type.");
                }
            }
            else if  (target != type) {
                throw new RuntimeException("Types are not the same.");
            }
        }
        else { // Good to go!
        }
    }
}
