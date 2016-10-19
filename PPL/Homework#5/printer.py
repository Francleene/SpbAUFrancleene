from model import Scope, Number, Function, FunctionDefinition, Conditional, Print, Read, FunctionCall, Reference, BinaryOperation, UnaryOperation


class PrintVisitor:

    prior = {"-":  7,
             "!":  7,
             "*":  6,
             "/":  6,
             "%":  6,
             "-":  5,
             "+":  5,
             "<":  4,
             "<=": 4,
             ">":  4,
             ">=": 4,
             "==": 3,
             "!=": 3,
             "&&": 2,
             "||": 1}
    

    def visitConditional(self, conditional):
        condition, _ = conditional.condition.accept(self)

        output = "if (" + condition + ") {\n"

        if conditional.if_true:
            for expr, _ in [elem.accept(self) for elem in conditional.if_true]:
                output += "    {0};\n".format(expr)

        if conditional.if_false:
            output += "} else {\n"
            for expr, _ in [elem.accept(self) for elem in conditional.if_false]:
                output += "    {0};\n".format(expr)
                
        output += "}"

        return output, 0


    def visitFunctionDefinition(self, func_def):
        output = "def " + func_def.name

        output += "(" + ", ".join(func_def.function.args) + ") {\n"

        for expr, _ in [elem.accept(self) for elem in func_def.function.body]:
            output += "    {0};\n".format(expr)

        output += "}"

        return output, 8
        

    def visitFunctionCall(self, func_call):
        name, _ = func_call.expr.accept(self)

        output = name

        output += "(" + ", ".join([str(elem.accept(self)[0]) for elem in func_call.args]) + ")"

        return output, 8
        

    def visitPrint(self, prnt):
        expr, _ = prnt.expr.accept(self)

        return "print " + expr, 0

    def visitRead(self, read):
        return "read " + read.name, 0
    
    def visitNumber(self, number):
        return str(number.value), 8

    def visitReference(self, reference):
        return reference.name, 8

    def visitBinaryOperation(self, binaryOperation):
        left_part, left_prior = binaryOperation.left.accept(self)
        right_part, right_prior = binaryOperation.right.accept(self)

        if left_prior < PrintVisitor.prior[binaryOperation.op]:
            left_part = "(" + left_part + ")"

        if right_prior < PrintVisitor.prior[binaryOperation.op]:
            right_part = "(" + right_part + ")"

        return left_part + " " + binaryOperation.op + " " + right_part, PrintVisitor.prior[binaryOperation.op]

    def visitUnaryOperation(self, unaryOperation):
        expr, prior = unaryOperation.expr.accept(self)

        if prior < 7:
            expr = "(" + expr + ")"

        return unaryOperation.op + expr, PrintVisitor.prior[unaryOperation.op]


class PrettyPrinter:
    def visit(self, tree):
        visitor = PrintVisitor()
        value, _ = tree.accept(visitor)
        print(value, end=";\n")
