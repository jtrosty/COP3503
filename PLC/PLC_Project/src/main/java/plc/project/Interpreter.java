package plc.project;

//import com.sun.org.apache.xpath.internal.operations.Bool;
//import sun.invoke.empty.Empty;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Interpreter implements Ast.Visitor<Environment.PlcObject> {

    private Scope scope = new Scope(null);

    public Interpreter(Scope parent) {
        scope = new Scope(parent);
        scope.defineFunction("print", 1, args -> {
            System.out.println(args.get(0).getValue());
            return Environment.NIL;
        });
    }

    public Scope getScope() {
        return scope;
    }

    @Override
    public Environment.PlcObject visit(Ast.Source ast) {
        List<Ast.Field> fields = ast.getFields();
        List<Ast.Method> methods = ast.getMethods();
        for (Ast.Field field : fields) {
            visit(field);
        }
        for (Ast.Method method : methods) {
            visit(method);
        }
        List<Environment.PlcObject> emptyListToInvokeMain = new ArrayList<>();
        return (scope.lookupFunction("main", 0)).invoke(emptyListToInvokeMain);
    }

    @Override
    public Environment.PlcObject visit(Ast.Field ast) {
        if (ast.getValue().isPresent()) {
            scope.defineVariable(ast.getName(), visit(ast.getValue().get()));
        }
        else {
            scope.defineVariable(ast.getName(), Environment.NIL);
        }

        return Environment.NIL;
    }

    @Override
    public Environment.PlcObject visit(Ast.Method ast) {
        List<Ast.Stmt> statements = ast.getStatements();
        List<String> parameters = ast.getParameters();
        // Define a function in the current scope
        // java.util.function.Function<List<Environment.PlcObject>, Environment.PlcObject> function;
        scope.defineFunction(ast.getName(),ast.getParameters().size(), (args) -> {
            // set the scope to be a new child where the function is defined.
            scope = new Scope(scope);
            // define variables for incoming arguments, use parameter names.
            for (int i = 0; i < parameters.size(); i++) {
                scope.defineVariable(parameters.get(i), args.get(i));
            }

            // Evaluate the methods statements, returns the value contained in a return exception
            // TODO: need to catch the return error "returns the value contained in a 'return' exception if thrown.
            try {
                for (Ast.Stmt statement : statements) {
                    visit(statement);
                }
            }
            catch (Return statementReturn){
                return statementReturn.value;
            }
            finally {
            }
            scope = scope.getParent();
            return Environment.NIL;
        });
        return Environment.NIL;
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.Expression ast) {
        // Evaluate the expression, return NIL.
        visit(ast.getExpression());
        return Environment.NIL;
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.Declaration ast) {
        if (ast.getValue().isPresent()) {
            scope.defineVariable(ast.getName(), visit(ast.getValue().get()));
        }
        else {
            scope.defineVariable(ast.getName(), Environment.NIL);
        }
        return Environment.NIL; // there is nothing to reurn
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.Assignment ast) {
        // Check if ast first argument is an access type.
        Ast.Expr receiver = ast.getReceiver();
        if (receiver instanceof Ast.Expr.Access) {
            Ast.Expr.Access accessReceiver = (Ast.Expr.Access) receiver;
            // now check if the access type has a receiver itself
            // TODO: looked up optional class maybe use isPresent below
            if (!(accessReceiver.getReceiver()).equals(Optional.empty())) {
                // INFO: in this case AST is ast(Ast.Expr.Access(receiver, name), Expr value)
                // evaluate the receiver in the access expression.
                Environment.PlcObject evaluatedAccessReceiver = visit(accessReceiver.getReceiver().get());
                // set a field
                evaluatedAccessReceiver.setField(accessReceiver.getName(), visit(ast.getValue()));
            }
            else {
                // In this case, ast(a ast.expr of some kind, Expr value)  need name to lookup variable and set it in scope?
                Environment.Variable variableToUpdate = scope.lookupVariable(accessReceiver.getName());
                variableToUpdate.setValue(visit(ast.getValue()));
            }
        }
        else {
            //TODO: Maybe do something here?
        }
        return Environment.NIL;
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.If ast) {
        if (requireType(Boolean.class, visit((ast.getCondition())))) {
            scope = new Scope(scope);
            for (Ast.Stmt thenStmt : ast.getThenStatements()) {
                visit(thenStmt);
            }
        }
        else {
            scope = new Scope(scope);
            for (Ast.Stmt elseStmt : ast.getElseStatements()) {
                visit(elseStmt);
            }
        }
        scope = scope.getParent();

        return  Environment.NIL;
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.For ast) {
        // ensure ast.getvalue evaluateds to an Iterable.
        Iterable<Environment.PlcObject> iter = requireType(Iterable.class, visit(ast.getValue()));
        // assume the contents are PlcObjetcs
        // for each element, inside of a new scope, define a variable with the for loop's name and evaluate the statemetns

        for (Environment.PlcObject object : iter) {
            scope = new Scope(scope);
            scope.defineVariable(ast.getName(), object);
            for (Ast.Stmt stmt : ast.getStatements()) {
                visit(stmt);
            }
            scope = scope.getParent();
        }

        return Environment.NIL;
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.While ast) {
        while (requireType(Boolean.class, visit(ast.getCondition()))) {
            try {
                scope = new Scope(scope);
                for (Ast.Stmt stmt : ast.getStatements()) {
                    visit(stmt);
                }
              // ast.getStatements().forEach(this::visit); // Alt way of doing the above for loop that is 2 lines up.
            }
            finally {
                scope = scope.getParent();
            }
        }
        return Environment.NIL;
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.Return ast) {
        throw new Return(visit(ast.getValue()));
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Literal ast) {
        if (ast.getLiteral() == null) return Environment.NIL;
        return Environment.create(ast.getLiteral());
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Group ast) {
        return visit(ast.getExpression());
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Binary ast) {
        // Evlauts arg based on the specific binary operator

        switch (ast.getOperator()) {
            case "AND": {
                if (requireType(Boolean.class, visit(ast.getLeft())) && requireType(Boolean.class, visit(ast.getRight()))) {
                    return Environment.create(true);
                }
                else {
                    return Environment.create(false);
                }
            }
            case "OR": {
                if (requireType(Boolean.class, visit(ast.getLeft())) || requireType(Boolean.class, visit(ast.getRight()))) {
                    return Environment.create(true);
                }
                else {
                    return Environment.create(false);
                }
            }
            case "<": {
                Comparable<Comparable<Environment.PlcObject>> leftSide = requireType(Comparable.class, visit(ast.getLeft()));
                Comparable<Environment.PlcObject> rightSide = requireType(Comparable.class, visit(ast.getRight()));
                if (leftSide.compareTo(rightSide) < 0) {
                    return Environment.create(true);
                }
                else {
                    return Environment.create(false);
                }
            }
            case "<=": {
                Comparable<Comparable<Environment.PlcObject>> leftSide = requireType(Comparable.class, visit(ast.getLeft()));
                Comparable<Environment.PlcObject> rightSide = requireType(Comparable.class, visit(ast.getRight()));
                if (leftSide.compareTo(rightSide) <= 0) {
                    return Environment.create(true);
                }
                else {
                    return Environment.create(false);
                }
            }
            case ">": {
                Comparable<Comparable<Environment.PlcObject>> leftSide = requireType(Comparable.class, visit(ast.getLeft()));
                Comparable<Environment.PlcObject> rightSide = requireType(Comparable.class, visit(ast.getRight()));
                if (leftSide.compareTo(rightSide) > 0) {
                    return Environment.create(true);
                }
                else {
                    return Environment.create(false);
                }
            }
            case ">=": {
                Comparable<Comparable<Environment.PlcObject>> leftSide = requireType(Comparable.class, visit(ast.getLeft()));
                Comparable<Environment.PlcObject> rightSide = requireType(Comparable.class, visit(ast.getRight()));
                if (leftSide.compareTo(rightSide) >= 0) {
                    return Environment.create(true);
                }
                else {
                    return Environment.create(false);
                }
            }
            case "==": {
                Comparable<Comparable<Environment.PlcObject>> leftSide = requireType(Comparable.class, visit(ast.getLeft()));
                Comparable<Environment.PlcObject> rightSide = requireType(Comparable.class, visit(ast.getRight()));
                if (leftSide.equals(rightSide)) {
                    return Environment.create(true);
                }
                else {
                    return Environment.create(false);
                }
            }
            case "!=": {
                Comparable<Comparable<Environment.PlcObject>> leftSide = requireType(Comparable.class, visit(ast.getLeft()));
                Comparable<Environment.PlcObject> rightSide = requireType(Comparable.class, visit(ast.getRight()));
                if (!leftSide.equals(rightSide)) {
                    return Environment.create(true);
                }
                else {
                    return Environment.create(false);
                }
            }
            case "+": {
                Environment.PlcObject leftSide = visit(ast.getLeft());
                Environment.PlcObject rightSide = visit(ast.getRight());
                if ((leftSide.getValue() instanceof String) || (rightSide.getValue() instanceof String)) {
                    String left = (String)leftSide.getValue();
                    String right = (String)rightSide.getValue();
                    return Environment.create(left + right);
                }
                else if ((leftSide.getValue() instanceof BigInteger && rightSide.getValue() instanceof BigInteger)) {
                    BigInteger leftResult = (BigInteger)leftSide.getValue();
                    BigInteger rightResult = (BigInteger)rightSide.getValue();
                    return Environment.create(leftResult.add(rightResult));
                }
                else if ((leftSide.getValue() instanceof BigDecimal && rightSide.getValue() instanceof BigDecimal)) {
                    BigDecimal leftResult = (BigDecimal) leftSide.getValue();
                    BigDecimal rightResult = (BigDecimal) rightSide.getValue();
                    return Environment.create(leftResult.add(rightResult));
                }
                else {
                    throw new RuntimeException("Each value must be of the same type, BigInteger or BigDecimal.");
                }
            }
            case "-": {
                Environment.PlcObject leftSide = visit(ast.getLeft());
                Environment.PlcObject rightSide = visit(ast.getRight());
                if ((leftSide.getValue() instanceof BigInteger && rightSide.getValue() instanceof BigInteger)) {
                    BigInteger leftResult = (BigInteger)leftSide.getValue();
                    BigInteger rightResult = (BigInteger)rightSide.getValue();
                    return Environment.create(leftResult.subtract(rightResult));
                }
                else if ((leftSide.getValue() instanceof BigDecimal && rightSide.getValue() instanceof BigDecimal)) {
                    BigDecimal leftResult = (BigDecimal) leftSide.getValue();
                    BigDecimal rightResult = (BigDecimal) rightSide.getValue();
                    return Environment.create(leftResult.subtract(rightResult));
                }
                else {
                    throw new RuntimeException("Each value must be of the same type, BigInteger or BigDecimal.");
                }
            }
            case "*": {
                Environment.PlcObject leftSide = visit(ast.getLeft());
                Environment.PlcObject rightSide = visit(ast.getRight());
                if ((leftSide.getValue() instanceof BigInteger && rightSide.getValue() instanceof BigInteger)) {
                    BigInteger leftResult = (BigInteger)leftSide.getValue();
                    BigInteger rightResult = (BigInteger)rightSide.getValue();
                    return Environment.create(leftResult.multiply(rightResult));
                }
                else if ((leftSide.getValue() instanceof BigDecimal && rightSide.getValue() instanceof BigDecimal)) {
                    BigDecimal leftResult = (BigDecimal) leftSide.getValue();
                    BigDecimal rightResult = (BigDecimal) rightSide.getValue();
                    return Environment.create(leftResult.multiply(rightResult));
                }
                else {
                    throw new RuntimeException("Each value must be of the same type, BigInteger or BigDecimal.");
                }
            }
            case "/": {
                Environment.PlcObject leftSide = visit(ast.getLeft());
                Environment.PlcObject rightSide = visit(ast.getRight());
                if ((leftSide.getValue() instanceof BigInteger && rightSide.getValue() instanceof BigInteger)) {
                    BigInteger leftResult = (BigInteger)leftSide.getValue();
                    BigInteger rightResult = (BigInteger)rightSide.getValue();
                    return Environment.create(leftResult.divide(rightResult));
                }
                else if ((leftSide.getValue() instanceof BigDecimal && rightSide.getValue() instanceof BigDecimal)) {
                    BigDecimal leftResult = (BigDecimal) leftSide.getValue();
                    BigDecimal rightResult = (BigDecimal) rightSide.getValue();
                    if (rightResult == BigDecimal.ZERO) {
                        throw new RuntimeException("Denominator is zero.");
                    }
                    return Environment.create(leftResult.divide(rightResult, RoundingMode.HALF_DOWN));
                }
            }
        }
        throw new RuntimeException("Error, operator did not match defined operations.");
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Access ast) {
        if (ast.getReceiver().isPresent()) {
            Environment.PlcObject receiverValue = visit(ast.getReceiver().get());
            return receiverValue.getField(ast.getName()).getValue();
            // receiverValue is one level down.
            // create a new PlcObject with the value fo the PlcObject created above.
            //return Environment.create(recieverValue.getValue());
        }
        else {
            // NOTE(Jon): If we don't have the variable we can look it up in scope, there we can lookup variable.
            // The variable should be defined if we are trying to access it. Lookup variable has a
            // a error for if it cannot find the variable.

            // The below returns an enviornment variable, which get value gets the PlcObject.
            return scope.lookupVariable(ast.getName()).getValue();
        }
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Function ast) {
        // If it has a receiver evaluate and return the result of calling the appropriate method.
        // Need to get argumetns and invoke them.
        List<Environment.PlcObject> arguments = new ArrayList<>(); // TODO: delete?
        scope = new Scope(scope);
        for (Ast.Expr arg : ast.getArguments()) {
            arguments.add(visit(arg));
        }

        if (ast.getReceiver().isPresent()) {
            Environment.PlcObject receiverObject = visit(ast.getReceiver().get());
            scope = scope.getParent();
            return receiverObject.callMethod(ast.getName(), arguments);
        }
        else {
            scope = scope.getParent();
            return scope.lookupFunction(ast.getName(), ast.getArguments().size()).invoke(arguments);
        }
    }

    /**
     * Helper function to ensure an object is of the appropriate type.
     */
    private static <T> T requireType(Class<T> type, Environment.PlcObject object) {
        if (type.isInstance(object.getValue())) {
            return type.cast(object.getValue());
        } else {
            throw new RuntimeException("Expected type " + type.getName() + ", received " + object.getValue().getClass().getName() + ".");
        }
    }

    private static <T> boolean checkType(Class<T> type, Environment.PlcObject object) {
        if (type.isInstance(object.getValue())) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Exception class for returning values.
     */
    public static class Return extends RuntimeException {

        private final Environment.PlcObject value;

        private Return(Environment.PlcObject value) {
            this.value = value;
        }

    }

}
