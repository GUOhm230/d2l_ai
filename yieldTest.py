"""
yield的用法探讨.使用python生成器强于list
"""
def yT(a):
    for i in range(a):
        print(i)
        yield i
        print()

# for j in range(10):
#     b = next(yT(10)) # 本身不输出值，要用next才会最终得到
#     print(b)

print("---"*20)
def foo():
    print("starting...")
    while True:
        res = yield 4
        print("res:", res)
g = foo()
print(g)
print(next(g))
print("*"*20)
print(next(g))
print("+"*20)
print(next(g))
"""
上段代码解释：
g=foo(),检测到其中有yield函数，因此并不会执行当前方法，而是得到一个生成器
在执行next(g)后才会执行该方法。执行到yield，停止且不会给res赋值，输出4
接下来继续执行next()时，从之前的yield以后开始执行即从上一个next停止的地方（res = yield 4）开始执行、
但是由于左边已在上次被传出，因此无值，于是输出res=None
接下来才继续执行当前循环
而之所以要用yield就是因为直接存储会消耗太多空间，因此存入生成器中
"""
def foo(num):

    print("starting...")
    while num<10:

        num=num+1
        yield num

for n in foo(0):

    print(n)