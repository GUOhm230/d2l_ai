"""
二维卷积层
"""

# 实现互相关运算
import numpy as np
from mxnet.gluon import nn
from mxnet import autograd, nd
def corr2d(X, K):
    h, w = K.shape
    Y = np.zeros((X.shape[0]-h+1, X.shape[1]-w+1))
    for i in range(Y.shape[0]):
        for j in range(Y.shape[1]):
            Y[i, j] = (X[i: i+h, j: j+w] * K).sum()
    return Y

# 父类关键字super的使用
class person():
    def __init__(self, *args):
        self.name = args[0]
        self.age = args[1]
        self.sex = args[2]

    def get_name(self):
        return self.name

    def get_sex(self):
        return self.sex

    def last_year(self):
        return 100 - self.age

# 如果子类需要引用父类中的方法和属性的时候，需要集成，而子类中也要初始化的时候，则需要使用super关键字。注意传入参数也要传入父类的
class guo(person):
    def __init__(self, *args):
        super(guo, self).__init__(self, *args)
        self.age = 18
        self.sex = "man"

    def get_job(self):
        return "算法工程师"

    def get_name(self):
        return self.name

# 实现二维卷积运算。包括构造类以及创建init和使用提供的包
# super关键字的使用：当子类重写了父类方法时，又想调用父类的同名方法时
class Conv2D(nn.Block):
    def __init__(self, kernel_size, **kwargs):
        super(Conv2D, self).__init__(**kwargs)
        self.weight = self.params.get('weight', shape=kernel_size)
        self.bias = self.params.get('bias', shape=(1,))

    def forward(self, x):
        return corr2d(x, self.weight.data()) + self.bias.data()


if __name__ == "__main__":
    X = np.array([[0, 1, 2], [3, 4, 5], [6, 7, 8]])
    K = np.array([[0, 1], [2, 3]])
    Y = corr2d(X, K)
    # print(Y)
    p = person("郭辉铭", 18, "man")
    print(p.get_sex())
    g = guo("郭辉铭", 18, "man")
    print(g.get_name())