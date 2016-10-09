class Scope:

    """Scope - представляет доступ к значениям по именам
    (к функциям и именованным константам).
    Scope может иметь родителя, и если поиск по имени
    в текущем Scope не успешен, то если у Scope есть родитель,
    то поиск делегируется родителю.
    Scope должен поддерживать dict-like интерфейс доступа
    (см. на специальные функции __getitem__ и __setitem__)
    """

    def __init__(self, parent=None):
        self.d = {}
        self.parent = parent

    def __getitem__(self, name):
        if name in self.d.keys():
            return self.d[name]
        else:
            return self.parent[name]

    def __setitem__(self, name, value):
        self.d[name] = value


class Number:

    """Number - представляет число в программе.
    Все числа в нашем языке целые."""

    def __init__(self, value):
        self.value = value

    def evaluate(self, scope):
        return self

    def __add__(self, other):
        return Number(self.value + other.value)

    def __sub__(self, other):
        return Number(self.value - other.value)

    def __mul__(self, other):
        return Number(self.value * other.value)

    def __truediv__(self, other):
        return Number(self.value / other.value)

    def __mod__(self, other):
        return Number(self.value % other.value)

    def __eq__(self, other):
        return Number(self.value == other.value)

    def __ne__(self, other):
        return Number(self.value != other.value)

    def __lt__(self, other):
        return Number(self.value < other.value)

    def __le__(self, other):
        return Number(self.value <= other.value)

    def __gt__(self, other):
        return Number(self.value > other.value)

    def __ge__(self, other):
        return Number(self.value >= other.value)


class Function:

    """Function - представляет функцию в программе.
    Функция - второй тип поддерживаемый языком.
    Функции можно передавать в другие функции,
    и возвращать из функций.
    Функция состоит из тела и списка имен аргументов.
    Тело функции это список выражений,
    т. е.  у каждого из них есть метод evaluate.
    Во время вычисления функции (метод evaluate),
    все объекты тела функции вычисляются последовательно,
    и результат вычисления последнего из них
    является результатом вычисления функции.
    Список имен аргументов - список имен
    формальных параметров функции."""

    def __init__(self, args, body):
        self.args = args
        self.body = body

    def evaluate(self, scope):
        for expr in self.body[:-1]:
            expr.evaluate(scope)

        return self.body[-1].evaluate(scope)
        


class FunctionDefinition:

    """FunctionDefinition - представляет определение функции,
    т. е. связывает некоторое имя с объектом Function.
    Результатом вычисления FunctionDefinition является
    обновление текущего Scope - в него
    добавляется новое значение типа Function."""

    def __init__(self, name, function):
        self.name = name
        self.function = function

    def evaluate(self, scope):
        scope[self.name] = self.function


class Conditional:

    """
    Conditional - представляет ветвление в программе, т. е. if.
    """

    def __init__(self, condtion, if_true, if_false=None):
        raise NotImplementedError

    def evaluate(self, scope):
        raise NotImplementedError


class Print:

    """Print - печатает значение выражения на отдельной строке."""

    def __init__(self, expr):
        self.expr = expr

    def evaluate(self, scope):
        num = self.expr.evaluate(scope)
        print(num.value)
        return num
        

class Read:

    """Read - читает число из стандартного потока ввода
     и обновляет текущий Scope.
     Каждое входное число располагается на отдельной строке
     (никаких пустых строк и лишних символов не будет).
     """

    def __init__(self, name):
        self.name = name

    def evaluate(self, scope):
        value = Number(int(input()))
        scope[self.name] = value
        return value


#done
class FunctionCall:

    """
    FunctionCall - представляет вызов функции в программе.
    В результате вызова функции должен создаваться новый объект Scope,
    являющий дочерним для текущего Scope
    (т. е. текущий Scope должен стать для него родителем).
    Новый Scope станет текущим Scope-ом при вычислении тела функции.
    """

    def __init__(self, fun_expr, args):
        self.expr = fun_expr
        self.args = args

    def evaluate(self, scope):
        self.func = self.expr.evaluate(scope)

        child = Scope(scope)
        for index, value in enumerate(self.args):
            child[self.func.args[index]] = value.evaluate(scope)

        return self.func.evaluate(child)
        

#done
class Reference:

    """Reference - получение объекта
    (функции или переменной) по его имени."""

    def __init__(self, name):
        self.name = name

    def evaluate(self, scope):
        return scope[self.name]


#done
class BinaryOperation:

    """BinaryOperation - представляет бинарную операцию над двумя выражениями.
    Результатом вычисления бинарной операции является объект Number.
    Поддерживаемые операции:
    “+”, “-”, “*”, “/”, “%”, “==”, “!=”,
    “<”, “>”, “<=”, “>=”, “&&”, “||”."""

    def __init__(self, lhs, op, rhs):
        self.left = lhs
        self.right = rhs
        self.op = op

    def evaluate(self, scope):
        left_num = self.left.evaluate(scope)
        right_num = self.right.evaluate(scope)

        if self.op == "+":
            return left_num + right_num

        if self.op == "-":
            return left_num - right_num

        if self.op == "*":
            return left_num * right_num

        if self.op == "/":
            return left_num / right_num

        if self.op == "%":
            return left_num % right_num

        if self.op == "==":
            return left_num == right_num

        if self.op == "!=":
            return left_num != right_num

        if self.op == "<":
            return left_num < right_num

        if self.op == ">":
            return left_num > right_num

        if self.op == "<=":
            return left_num <= right_num

        if self.op == ">=":
            return left_num >= right_num

        if self.op == "&&":
            return Number(left_num.value and right_num.value)

        if self.op == "||":
            return Number(left_num.value or right_num.value)

#done
class UnaryOperation:

    """UnaryOperation - представляет унарную операцию над выражением.
    Результатом вычисления унарной операции является объект Number.
    Поддерживаемые операции: “-”, “!”."""

    def __init__(self, op, expr):
        self.op = op
        self.expr = expr

    def evaluate(self, scope):
        num = self.expr.evaluate(scope)

        if op == "-":
            return Number(-num.value)

        if op == "!":
            return Number(not num.value)


def example():
    parent = Scope()
    parent["foo"] = Function(('hello', 'world'),
                             [Print(BinaryOperation(Reference('hello'),
                                                    '+',
                                                    Reference('world')))])
    parent["bar"] = Number(10)
    scope = Scope(parent)
    assert 10 == scope["bar"].value
    scope["bar"] = Number(20)
    assert scope["bar"].value == 20
    print('It should print 2: ', end=' ')
    FunctionCall(FunctionDefinition('foo', parent['foo']),
                 [Number(5), UnaryOperation('-', Number(3))]).evaluate(scope)

def my_tests():
    scope = Scope()
    
    Print(Number(10)).evaluate(scope)
    Print(BinaryOperation(Number(10), "+", Number(20))).evaluate(scope)
    
    scope["a"] = Number(10)
    scope["b"] = Number(20)
    
    Print(Reference("a")).evaluate(scope)
    Print(BinaryOperation(Reference("a"), "*", Reference("b"))).evaluate(scope)

    child_scope = Scope(scope)

    Print(Reference("a")).evaluate(child_scope)

    child_scope["a"] = Number(40)
    Print(Reference("a")).evaluate(child_scope)

    scope["print10"] = Function((), [Print(Number(10))])
    FunctionCall(Reference("print10"), ()).evaluate(scope)

    scope["print_sum"] = Function(("first", "second"), [Print(BinaryOperation(Reference("first"), "+", Reference("second")))])
    FunctionCall(Reference("print_sum"), [Number(10), Number(20)]).evaluate(scope)
    FunctionCall(Reference("print_sum"), [Reference("a"), Reference("b")]).evaluate(child_scope)

    FunctionDefinition("print_sub", Function(("first", "second"), [Print(BinaryOperation(Reference("first"), "-", Reference("second")))])).evaluate(scope)
    FunctionCall(Reference("print_sub"), [Number(10), Number(20)]).evaluate(scope)
    FunctionCall(Reference("print_sub"), [Reference("a"), Reference("b")]).evaluate(child_scope)

    FunctionDefinition("print_sub", Function(("first", "second"), [Print(BinaryOperation(Reference("second"), "-", Reference("first")))])).evaluate(child_scope)
    FunctionCall(Reference("print_sub"), [Reference("a"), Reference("b")]).evaluate(child_scope)
    
    FunctionDefinition("print(a*b*c)", Function(("first", "second", "third"), [Print(BinaryOperation(Reference("first"), "*", BinaryOperation(Reference("second"), "*", Reference("third"))))])).evaluate(scope)
    FunctionCall(Reference("print(a*b*c)"), [Number(5), Number(7), Number(11)]).evaluate(scope)

    FunctionDefinition("mul", Function(("first", "second"), [BinaryOperation(Reference("first"), "*", Reference("second"))])).evaluate(scope)
    FunctionDefinition("add", Function(("first", "second"), [BinaryOperation(Reference("first"), "+", Reference("second"))])).evaluate(scope)
    FunctionDefinition("a*b + c*d", Function(("a", "b", "c", "d", "mul", "add"), [Print(FunctionCall(Reference("add"), [FunctionCall(Reference("mul"), [Reference("a"), Reference("b")]), FunctionCall(Reference("mul"), [Reference("c"), Reference("d")])]))])).evaluate(scope)
    FunctionCall(Reference("a*b + c*d"), [Number(10), Number(20), Number(30), Number(40), Reference("mul"), Reference("add")]).evaluate(scope)

    FunctionDefinition("Mul or add? That is a question!", Function(("func", "a", "b"), [Print(FunctionCall(Reference("func"), [Reference("a"), Reference("b")]))])).evaluate(scope)
    FunctionCall(Reference("Mul or add? That is a question!"), [Reference("mul"), Number(2), Number(3)]).evaluate(scope)
    FunctionCall(Reference("Mul or add? That is a question!"), [Reference("add"), Number(2), Number(3)]).evaluate(scope)

if __name__ == '__main__':
    #example()
    my_tests()


