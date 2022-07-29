package plc.project;

import java.io.PrintWriter;
import java.math.BigDecimal;
import java.math.BigInteger;

public final class Generator implements Ast.Visitor<Void> {

    private final PrintWriter writer;
    private int indent = 0;

    public Generator(PrintWriter writer) {
        this.writer = writer;
    }

    private void print(Object... objects) {
        for (Object object : objects) {
            if (object instanceof Ast) {
                visit((Ast) object);
            } else {
                writer.write(object.toString());
            }
        }
    }

    private void newline(int indent) {
        writer.println();
        for (int i = 0; i < indent; i++) {
            writer.write("    ");
        }
    }

    @Override
    public Void visit(Ast.Source ast) {
        // Create a "Class Main {"
        print("public class Main {");
        // Declare fields
        newline(0);
        if(!ast.getFields().isEmpty()) {
            newline(++indent);
            for (int i = 0; i < ast.getFields().size(); i++) {
                if (i != 0) {
                    newline(indent);
                }
                print(ast.getFields().get(i));
            }
            newline(--indent);
        }

        // Declare "public static void main(String[] args) {
        //                System.exit(new Main().main();
        //          }"
        newline(++indent);
        print("public static void main(String[] args) {");
        newline(++indent);
        print("System.exit(new Main().main());");
        newline(--indent);
        print("}");
        newline(0);

        // declare each of our methods
        if (!ast.getMethods().isEmpty()) {
            newline(indent);
            for (int i = 0; i < ast.getMethods().size(); i++) {
                if (i !=0) {
                    newline(indent);
                }
                print(ast.getMethods().get(i));
                newline(0);
            }
        }
        // print "}" to close the class main
        newline(--indent);
        print("}");

        return null;
    }

    @Override
    public Void visit(Ast.Field ast) {
        // write TYPE variable_name
        print(ast.getVariable().getType().getJvmName(), " ", ast.getVariable().getJvmName());

        // if so, write = and assigned value
        if (ast.getValue().isPresent()) {
            print(" = ", ast.getValue().get());
        }

        // write: ;
        print(";");

        return null;
    }

    @Override
    public Void visit(Ast.Method ast) {
        print(ast.getFunction().getReturnType().getJvmName(), " ", ast.getName(), "(");
        // Setup  line of parameters
        if (!ast.getParameters().isEmpty()) {
            for (int i = 0; i < ast.getParameters().size(); i++) {
                // General case
                if (i != ast.getParameters().size() -1 ) {
                    print(ast.getFunction().getParameterTypes().get(i).getJvmName(), " ", ast.getParameters().get(i), ", ");
                }
                // Last parameter
                else{
                    print(ast.getFunction().getParameterTypes().get(i).getJvmName(), " ", ast.getParameters().get(i), ") {");
                }
            }
        }
        else {
            print(") {");
        }
        // Enter into method, and begin writing statements
        if (!ast.getStatements().isEmpty()) {
            newline(++indent);
            for (int i = 0; i < ast.getStatements().size(); i++) {
                if (i != 0) {
                    newline(indent);
                }
                print(ast.getStatements().get(i));
            }
            newline(--indent);
        }
        // In cse of no statements, this will be on the same line as the method name
        print("}");

        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Expression ast) {
        print(ast.getExpression(), ";");
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Declaration ast) {
        // write TYPE variable_name
        print(ast.getVariable().getType().getJvmName(), " ", ast.getVariable().getJvmName());

        // if so, write = and assigned value
        if (ast.getValue().isPresent()) {
            print(" = ", ast.getValue().get());
        }

        // write: ;
        print(";");

        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Assignment ast) {
        print(ast.getReceiver());
        print(" = ");
        print(ast.getValue());
        print(";");
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.If ast) {
        print("if (", ast.getCondition(), ") {");
        newline(++indent);
        for (int i = 0; i < ast.getThenStatements().size(); i++) {
            if (i != 0) {
                newline(indent);
            }
            print(ast.getThenStatements().get(i));
        }
        newline(--indent);
        if (!ast.getElseStatements().isEmpty()) {
            print("} else {");
            newline(++indent);
            for (int i = 0; i < ast.getElseStatements().size(); i++) {
                if (i != 0) {
                    newline(indent);
                }
                print(ast.getElseStatements().get(i));
            }
            newline(--indent);
        }
        print("}");

        return null;
    }

    @Override
    public Void visit(Ast.Stmt.For ast) {
        print("for (int", " ", ast.getName(), " : ", ast.getValue(), ") {");
        newline(++indent);
        for (int i = 0; i < ast.getStatements().size(); i++) {
            if (i != 0) {
                newline(indent);
            }
            print(ast.getStatements().get(i));
        }
        newline(--indent);
        print("}");

        return null;
    }

    @Override
    public Void visit(Ast.Stmt.While ast) {
        print("while (");
        print(ast.getCondition());
        print(") {");

        // determine if there are statements to process
        if (!ast.getStatements().isEmpty()) {
            newline(++indent); // handles i == 0 case
            for (int i = 0; i < ast.getStatements().size(); i++) {
                if (i != 0) {
                    newline(indent);
                }
                // print the next statement
                print(ast.getStatements().get(i));
            }
            //setup the next line
            newline(--indent);
        }
        // close the while
        print("}");

        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Return ast) {
        print("return ");
        print(ast.getValue());
        print(";");

        return null;
    }

    @Override
    public Void visit(Ast.Expr.Literal ast) {
        if(ast.getType() == Environment.Type.BOOLEAN) {
            print(ast.getLiteral().toString());
        }
        else if (ast.getType() == Environment.Type.STRING) {
            print("\"", ast.getLiteral().toString(), "\"");
        }
        else if (ast.getType() == Environment.Type.CHARACTER) {
            print("\'", ast.getLiteral().toString(), "\'");
        }
        else if (ast.getType() == Environment.Type.INTEGER) {
            BigInteger temp = (BigInteger) ast.getLiteral();
            print(temp.intValue());
        }
        else if (ast.getType() == Environment.Type.DECIMAL) {
            // Big decimal string?? BigDecimal(String)
            BigDecimal temp = (BigDecimal) ast.getLiteral();
            print(temp.doubleValue());
        }
        else {
            print(ast.getLiteral());
        }
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Group ast) {
        print("(");
        print(ast.getExpression());
        print(")");
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Binary ast) {
        print(ast.getLeft());
        print(" ");
        if (ast.getOperator().equals("AND")) {
            print("&&");
        } else if (ast.getOperator().equals("OR")) {
            print("||");
        } else {
            print(ast.getOperator());
        }
        print(" ");
        print(ast.getRight());

        return null;
    }

    @Override
    public Void visit(Ast.Expr.Access ast) {
        if(ast.getReceiver().isPresent()) {
            //TODO I'm not sure if this is correct, the way I'm getting the receiver. I I just have it
            // TODO print the reciever, then it will go to the expression by itself, or at least the type of
            // TODO expression, this is what i had -> print(ast.getReceiver().get().getType().getJvmName());
            //*********************************************************************************************
            print(ast.getReceiver().get());
            print(".");
        }
        print(ast.getVariable().getJvmName());
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Function ast) {
        // TODO: Figure out what is going on with the semicolon here, i would expect a semicolon at the end of
        // TODO: every funciton in java..?
        // If a receiver is present, start with that, followed by period
        if (ast.getReceiver().isPresent()) {
            print(ast.getReceiver().get(), ".");
        }
        print(ast.getFunction().getJvmName(), "(");
        if (!ast.getArguments().isEmpty()) {
            for (int i = 0; i < ast.getArguments().size(); i++) {
                if (i == (ast.getArguments().size() - 1)) {
                    // last argument
                    print(ast.getArguments().get(i), ")");
                } else {
                    // Common case
                    print(ast.getArguments().get(i), ", ");
                }
            }
        }
        else {
            print(")");
        }

        return null;
    }

}
