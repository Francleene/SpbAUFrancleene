from yat.model import Scope, Number, Function, FunctionDefinition, Conditional, Print, Read, FunctionCall, Reference, BinaryOperation, UnaryOperation


class ConstantVisitor:

    def visitConditional(self, cond):
        cond_without_const = cond.condition.accept(self)
        if_true_without_const = [elem.accept(self) for elem in cond.if_true] if cond.if_true != None else None
        if_false_without_const = [elem.accept(self) for elem in cond.if_false] if cond.if_false != None else None
        
        conditional_without_const = Conditional(cond_without_const, if_true_without_const, if_false_without_const)
        
        return conditional_without_const


    def visitFunctionDefinition(self, func_def):
        args_without_const = [elem.accept(self) for elem in func_def.function.args]
        body_without_const = [elem.accept(self) for elem in func_def.function.body]

        func_without_const = Function(args_without_const, body_without_const)

        func_def_without_const = FunctionDefinition(func_def.name, func_without_const)

        return func_def_without_const
        

    def visitFunctionCall(self, func_call):
        expr_without_const = func_call.expr.accept(self)
        args_without_const = [elem.accept(self) for elem in func_call.args]

        func_call_without_const = FunctionCall(expr_without_const, args_without_const)

        return func_call_without_const
        

    def visitPrint(self, prnt):
        expr_without_const = prnt.expr.accept(self)

        return Print(expr_without_const)

    def visitRead(self, read):
        return read
    
    def visitNumber(self, number):
        return number

    def visitReference(self, reference):
        return reference

    def visitBinaryOperation(self, binaryOperation):
        left_part = binaryOperation.left.accept(self)
        right_part = binaryOperation.right.accept(self)
        op = binaryOperation.op

        left_is_num = isinstance(left_part, Number)
        right_is_num = isinstance(right_part, Number)

        if left_is_num and right_is_num:
            scope = Scope()
            bin_operation_with_number = BinaryOperation(left_part, op, right_part)
            return bin_operation_with_number.evaluate(scope)

        if op == "*" and (left_is_num and left_part.value == 0 or
                          right_is_num and right_part.value == 0):
            return Number(0)

        if op == "-" and left_part == right_part:
            return Number(0)

        return BinaryOperation(left_part, binaryOperation.op, right_part)

    def visitUnaryOperation(self, unaryOperation):
        expr = unaryOperation.expr.accept(self)

        if isinstance(expr, Number):
            scope = Scope()
            unar_operation_with_number = UnaryOperation(unaryOperation.op, expr)
            return unar_operation_with_number.evaluate(scope)

        return UnaryOperation(unaryOperation.op, expr)
    
class ConstantFolder:
    def visit(self, tree):
        visitor = ConstantVisitor()
        tree = tree.accept(visitor)
        return tree
