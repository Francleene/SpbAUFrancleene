import pytest
import sys
import io
from model import *
from random import randint


class Utils:
	INFTY = 10 ** 9

	bo = [[BinaryOperation(Number(4),    "-",  Number(7)), -3],
		  [BinaryOperation(Number(76),   "/",  Number(3)), 25],
		  [BinaryOperation(Number(-15), "&&",  Number(0)),  0]]

	uo = ["-", "!"]

	def get_value(self, number):
		src_stdout = sys.stdout
		sys.stdout = io.StringIO()

		scope = Scope()
		Print(number).evaluate(scope)
		value = int(sys.stdout.getvalue())

		sys_stdout = src_stdout
		return value

	def rand_number(self):
		value = randint(-self.INFTY, self.INFTY)
		num = Number(value)
		return num

class TestNumber(Utils):
	def test_number_value(self):
		for i in range(50):
			value = randint(-self.INFTY, self.INFTY)
			num = Number(value)
			assert value == self.get_value(num)

	def test_number_evaluate(self):
		scope = Scope()

		for i in range(50):
			num = self.rand_number()
			assert num is num.evaluate(scope)

class TestBinaryOperation(Utils):
	def test_add_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 10):
			for right_value in range(-100, 101, 10):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "+", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value + right_value

				assert correct_value == result_value

	def test_sub_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 10):
			for right_value in range(-100, 101, 10):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "-", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value - right_value

				assert correct_value == result_value

	def test_mul_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 10):
			for right_value in range(-100, 101, 10):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "*", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value * right_value

				assert correct_value == result_value

	def test_div_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 9):
			for right_value in range(-100, 101, 9):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "/", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value // right_value

				assert correct_value == result_value

	def test_mod_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 9):
			for right_value in range(-100, 101, 9):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "%", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value % right_value

				assert correct_value == result_value

	def test_equal_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 10):
			for right_value in range(-100, 101, 10):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "==", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value == right_value

				assert (    correct_value and     result_value or 
				        not correct_value and not result_value)

	def test_not_equal_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 10):
			for right_value in range(-100, 101, 10):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "!=", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value != right_value

				assert (    correct_value and     result_value or 
				        not correct_value and not result_value)

	def test_less_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 10):
			for right_value in range(-100, 101, 10):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "<", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value < right_value

				assert (    correct_value and     result_value or 
				        not correct_value and not result_value)


	def test_greater_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 10):
			for right_value in range(-100, 101, 10):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, ">", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value > right_value

				assert (    correct_value and     result_value or 
				        not correct_value and not result_value)

	def test_less_equal_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 10):
			for right_value in range(-100, 101, 10):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "<=", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value <= right_value

				assert (    correct_value and     result_value or 
				        not correct_value and not result_value)

	def test_greater_equals_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 10):
			for right_value in range(-100, 101, 10):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, ">=", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value >= right_value

				assert (    correct_value and     result_value or 
				        not correct_value and not result_value)

	def test_logical_and_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 9):
			for right_value in range(-100, 101, 9):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "&&", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value and right_value

				assert (    correct_value and     result_value or 
				        not correct_value and not result_value)

	def test_logical_or_operation(self):
		scope = Scope()

		for left_value in range(-100, 101, 9):
			for right_value in range(-100, 101, 9):
				left_num  = Number(left_value)
				right_num = Number(right_value)

				result_num = BinaryOperation(left_num, "||", right_num).evaluate(scope)
				
				result_value  = self.get_value(result_num)
				correct_value = left_value or right_value

				assert (    correct_value and     result_value or 
				        not correct_value and not result_value)

	def test_evaluate(self):
		scope = Scope()

		for inside_bo, correct_value in self.bo:
			bo = BinaryOperation(inside_bo, "+", Number(0))

			result_num = bo.evaluate(scope)
			result_value = self.get_value(result_num)

			assert correct_value == result_value

class TestUnaryOperation(Utils):
	def test_unar_minus(self):
		scope = Scope()

		for value in range(-100, 101, 10):
			num = Number(value)

			result_num = UnaryOperation("-", num).evaluate(scope)
			result_value = self.get_value(result_num)

			assert -value == result_value

	def test_logical_not(self):
		scope = Scope()

		for value in range(-100, 101, 10):
			num = Number(value)

			result_num = UnaryOperation("!", num).evaluate(scope)
			result_value = self.get_value(result_num)

			assert (not value and result_value) or (value and not result_value)

	def test_evaluate(self):
		scope = Scope()

		for inside_bo, correct_value in self.bo:
			uo = UnaryOperation("-", inside_bo)

			result_num = uo.evaluate(scope)
			result_value = self.get_value(result_num)

			assert -correct_value == result_value

class TestFunction(Utils):
	def test_return_value(self):
		scope = Scope()

		func = Function([], [Number(1), Number(2), Number(239)])

		return_num = func.evaluate(scope)
		return_value = self.get_value(return_num)

		assert 239 == return_value

	def test_empty_func(self):
		scope = Scope()

		try:
			func = Function((), [])
			func.evaluate(scope)
			assert True
		except:
			assert False

	def test_evaluate(self):
		scope = Scope()

		func = Function([], [self.bo[0][0], self.bo[1][0]])

		return_num = func.evaluate(scope)
		return_value = self.get_value(return_num)

		assert 25 == return_value

class TestFunctionDefinition(Utils):
	def test_return_value(self):
		scope = Scope()

		func = Function([], [self.bo[0][0], Number(239)])
		func_def  = FunctionDefinition("foo", func)
		evaluate_func = func_def.evaluate(scope)

		assert func is evaluate_func

	def test_evaluate(self):
		scope = Scope()

		func = Function([], [self.bo[0][0], Number(239)])
		func_def  = FunctionDefinition("foo", func)
		func_def.evaluate(scope)

		assert func is scope["foo"]

class TestFunctionCall(Utils):
	def test_call(self):
		scope = Scope()

		func = Function([], [Number(1), Number(2), Number(239)])
		func_def = FunctionDefinition("foo", func)
		func_call = FunctionCall(func_def, [])

		return_num = func_call.evaluate(scope)
		return_value = self.get_value(return_num)

		assert 239 == return_value

	def test_reference_args(self):
		scope = Scope()

		scope["first"]  = Number(254)
		scope["second"] = Number(-15)

		func = Function(["first", "second"], [BinaryOperation(Reference("first"), "+", Reference("second"))])
		func_def = FunctionDefinition("sum of two", func)
		func_call = FunctionCall(func_def, [Reference("first"), Reference("second")])

		return_num = func_call.evaluate(scope)
		return_value = self.get_value(return_num)

		assert 239 == return_value

	def test_evaluate_reference_args(self):
		scope = Scope()

		scope["first"] = Number(7)

		func = Function(["first"], [BinaryOperation(self.bo[0][0], "*", Reference("first"))])
		func_def = FunctionDefinition("mul of two", func)
		func_call = FunctionCall(func_def, [Reference("first")])

		return_num = func_call.evaluate(scope)
		return_value = self.get_value(return_num)

		assert -21 == return_value

class TestConditional(Utils):
	def test_chose(self):
		scope = Scope()

		cond_true = Conditional(Number(1), [Number(239)], [Number(-239)])
		result_num_true = cond_true.evaluate(scope)
		result_value_true = self.get_value(result_num_true)

		assert 239 == result_value_true

		cond_false = Conditional(Number(0), [Number(239)], [Number(-239)])
		result_num_false = cond_false.evaluate(scope)
		result_value_false = self.get_value(result_num_false)

		assert -239 == result_value_false

	def test_evaluate_parts(self):
		scope = Scope()

		cond_true = Conditional(Number(1), [self.bo[0][0]], [self.bo[1][0]])
		result_num_true = cond_true.evaluate(scope)
		result_value_true = self.get_value(result_num_true)

		assert -3 == result_value_true

		cond_false = Conditional(Number(0), [self.bo[0][0]], [self.bo[1][0]])
		result_num_false = cond_false.evaluate(scope)
		result_value_false = self.get_value(result_num_false)

		assert 25 == result_value_false

	def test_empty_parts(self):
		scope = Scope()

		try:
			Conditional(Number(0), [Number(239)], []).evaluate(scope)
			Conditional(Number(1), [], [Number(239)]).evaluate(scope)

			Conditional(Number(0), [Number(230)], None).evaluate(scope)
			Conditional(Number(1), None, [Number(239)]).evaluate(scope)

			Conditional(Number(0), [], []).evaluate(scope)
			Conditional(Number(1), [], []).evaluate(scope)

			Conditional(Number(0), None, None).evaluate(scope)
			Conditional(Number(1), None, None).evaluate(scope)
			assert True
		except:
			assert False

class TestScope(Utils):
	def test_find(self):
		scope = Scope()

		num  = Number(239)
		func = Function([], [Number(239)])

		scope["num"]  = num
		scope["func"] = func

		assert scope["num"]  is num
		assert scope["func"] is func

	def test_parent_scope(self):
		parent = Scope()
		child = Scope(parent)

		num  = Number(239)
		func = Function([], [Number(239)])

		parent["num"]  = num
		parent["func"] = func

		assert child["num"]  is num
		assert child["func"] is func

	def test_overwriting_parent_scope(self):
		parent = Scope()
		child  = Scope(parent)

		parent_num = Number(-239)
		child_num  = Number(239)

		parent_func = Function([], [Number(-239)])
		child_func  = Function([], [Number(239)])

		parent["num"]  = parent_num
		parent["func"] = parent_func

		child["num"]  = child_num
		child["func"] = child_func

		assert child["num"]  is child_num
		assert child["func"] is child_func

class TestReference(Utils):
	def test_return_value(self):
		scope = Scope()

		num  = Number(239)
		func = Function([], [Number(239)])

		scope["num"]  = num
		scope["func"] = func

		ret_num = Reference("num").evaluate(scope)
		ret_func = Reference("func").evaluate(scope)

		assert ret_num is num
		assert ret_func is func

class TestPrint(Utils):
	def test_output(self, monkeypatch):
		scope = Scope()
		num = Number(239)

		monkeypatch.setattr(sys, "stdout", io.StringIO())

		Print(num).evaluate(scope)
		ret_num = int(sys.stdout.getvalue())

		assert ret_num == 239

	def test_output_evaluate(self, monkeypatch):
		scope = Scope()

		bin_op = BinaryOperation(Number(239), '/', Number(10))
		monkeypatch.setattr(sys, "stdout", io.StringIO())

		Print(bin_op).evaluate(scope)
		ret_num = int(sys.stdout.getvalue())

		assert ret_num == 23

class TestRead(Utils):
    def test_input(self, monkeypatch):
        scope = Scope()

        monkeypatch.setattr(sys, 'stdin', io.StringIO('239'))
        ret_number = Read('a').evaluate(scope)
        ret_num = self.get_value(ret_number)

        assert ret_num == 239


if __name__ == "__main__":
	pytest.main()