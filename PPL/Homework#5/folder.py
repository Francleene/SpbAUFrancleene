from model import Scope, Number, Function, FunctionDefinition, Conditional, Print, Read, FunctionCall, Reference, BinaryOperation, UnaryOperation

class ConstantVisitor:

    def visitConditional(self, cond):
        cond_without_const = cond.condition.accept(self)[0]
        if_true_without_const = [elem.accept(self)[0] for elem in cond.if_true] if cond.if_true else None
        if_false_without_const = [elem.accept(self)[0] for elem in cond.if_false] if cond.if_false else None
        
        conditional_without_const = Conditional(cond_without_const, if_true_without_const, if_false_without_const)
        
        return conditional_without_const, None


    def visitFunctionDefinition(self, func_def):
        args_without_const = [elem.accept(self) for elem in func_def.function.args]
        body_without_const = [elem.accept(self) for elem in func_def.function.body]

        func_without_const = Function(args_without_const, body_without_const)

        func_def_without_const = FunctionDefinition(func_def.name, func_without_const)

        return func_def_without_const, None
        

    def visitFunctionCall(self, func_call):
        expr_without_const, _ = func_call.expr.accept(self)
        args_without_const = [elem.accept(self)[0] for elem in func_call.args]

        func_call_without_const = FunctionCall(expr_without_const, args_without_const)

        return func_call_without_const, None
        

    def visitPrint(self, prnt):
        expr_without_const, _ = prnt.expr.accept(self)

        return Print(expr_without_const), None

    def visitRead(self, read):
        return read, None
    
    def visitNumber(self, number):
        return number, 1 if number.value else 0

    def visitReference(self, reference):
        return reference, reference.name

    def visitBinaryOperation(self, binaryOperation):
        left_part, left_type = binaryOperation.left.accept(self)
        right_part, right_type = binaryOperation.right.accept(self)

        if (left_type == 0 or left_type == 1) and (right_type == 0 or right_type == 1):
            number = BinaryOperation.oper[binaryOperation.op](left_part, right_part)
            return number, 1 if number.value else 0

        if left_type == 0 or right_type == 0 and binaryOperation.op == "*":
            return Number(0), 0

        if left_type == right_type and binaryOperation.op == "-":
            return Number(0), 0

        return BinaryOperation(left_part, binaryOperation.op, right_part), None

    def visitUnaryOperation(self, unaryOperation):
        expr, expr_type = unaryOperation.expr.accept(self)

        if expr_type == 0 or expr_type == 1:
            number = UnaryOperation.oper[unaryOperation.op](expr)
            return number, 1 if expr else 0

        return UnaryOperation(unaryOperation.op, expr), None
    
class ConstantFolder:
    def visit(self, tree):
        visitor = ConstantVisitor()
        tree, _ = tree.accept(visitor)
        return tree
