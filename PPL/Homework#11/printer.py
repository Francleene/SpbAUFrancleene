from yat.model import Scope, Number, Function, FunctionDefinition, Conditional, Print, Read, FunctionCall, Reference, BinaryOperation, UnaryOperation


class PrintVisitor:

    MIN_PRIORITY = 0
    MAX_PRIORITY = 8

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
        print("if (", end="")
        conditional.condition.accept(self)
        print(") {")

        for elem in conditional.if_true:
            print("    ", end="")
            elem.accept(self) 
            print(";")

        if conditional.if_false != None:
            print("} else {")
            for elem in conditional.if_false:
                print("    ", end="")
                elem.accept(self)
                print(";")
                
        print("}", end="")

        return PrintVisitor.MIN_PRIORITY


    def visitFunctionDefinition(self, func_def):
        print("def " + func_def.name, end="")

        print("(" + ", ".join(func_def.function.args) + ") {")

        for elem in func_def.function.body:
            print("    ", end="")
            elem.accept(self)
            print(";")

        print("}", end="")

        return PrintVisitor.MAX_PRIORITY
        

    def visitFunctionCall(self, func_call):
        func_call.expr.accept(self)

        print("(", end="")
        
        if func_call.args:
            func_call.args[0].accept(self)
        
        for elem in func_call.args[1:]:
            print(", ", end="")
            elem.accept(self)

        print(")", end="")

        return PrintVisitor.MAX_PRIORITY
        

    def visitPrint(self, prnt):
        print("print ", end="")

        prnt.expr.accept(self)

        return PrintVisitor.MIN_PRIORITY

    def visitRead(self, read):
        print("read " + read.name, end="")
        return PrintVisitor.MIN_PRIORITY
    
    def visitNumber(self, number):
        print(number.value, end="")
        return PrintVisitor.MAX_PRIORITY

    def visitReference(self, reference):
        print(reference.name, end="")
        return PrintVisitor.MAX_PRIORITY

    def visitBinaryOperation(self, binaryOperation):
        left_part = binaryOperation.left
        right_part = binaryOperation.right
        op = binaryOperation.op
        
        left_bracket = (isinstance(left_part, BinaryOperation) and
                        PrintVisitor.prior[left_part.op] < PrintVisitor.prior[op])


        right_bracket = (isinstance(right_part, BinaryOperation) and
                        PrintVisitor.prior[right_part.op] < PrintVisitor.prior[op])

        if left_bracket:
            print("(", end="")

        left_part.accept(self)

        if left_bracket:
            print(")", end="")

        print(" " + op + " ", end="")

        if right_bracket:
            print("(", end="")

        right_part.accept(self)

        if right_bracket:
            print(")", end="")
            
        return PrintVisitor.prior[op]

    def visitUnaryOperation(self, unaryOperation):
        expr = unaryOperation.expr
        op = unaryOperation.op

        bracket = (isinstance(expr, BinaryOperation) and
                   PrintVisitor.prior[expr.op] < PrintVisitor.prior[op])

        if bracket:
            print("(", end="")

        expr.accept(self)

        if bracket:
            print(")", end="")
        
        return PrintVisitor.prior[op]


class PrettyPrinter:
    def visit(self, tree):
        visitor = PrintVisitor()
        tree.accept(visitor)
        print(";")
