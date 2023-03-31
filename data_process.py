"""
李沐深度学习课程第一节：数据操作的基本方法。
主要内容：
1）.掌握有关tensor的几个常用方法: torch.arange()
2）.切片处理
"""
import torch
x = torch.arange(12)# 生成一个一维张量，并在括号内指定长度
print(x.shape)
print(x.numel())# 返回元素总个数
y = x.reshape((-1, 1))
print(y.shape)
print(y)

zeros_tensor = torch.zeros(2,3,4)
ones_tensor = torch.ones((2,3,4))
print(zeros_tensor)
print(ones_tensor)

r = torch.randn(10, 10)
print(r)
print(r[:8:2, :5]) # 二维数据的切片，用逗号分开行和列，而每个逗号的m:n:k。表示开始于行/列的第m行/列结束于第n行/列,
# 且前一个数字比后一个小k.若m缺位，则表示第一行/列，n缺则最后一行/列

x = torch.tensor([1.0, 2, 3, 4])
y = torch.tensor([2, 2, 2, 2])
print(x+y)
print(x-y)
print(x*y)
print(x/y)
print(x**y)
print(torch.exp(x))
print(torch.exp(y))

# 将多个张量连接在一起
X = torch.arange(24, dtype=torch.float32).reshape((2, 3, 4))
Y = torch.tensor([[[2.0, 1, 4, 3], [1, 2, 3, 4], [4, 3, 2, 1]],
                  [[2.0, 1, 4, 3], [1, 2, 3, 4], [4, 3, 2, 1]]
                  ])  # tensor.size([2,3,4]).最后一维度是看最里面那层的
print(Y.shape)
# Z1 = torch.cat((X, Y), dim=0)  # 表示按行拼接，torch.size([6, 4])
# Z2 = torch.cat((X, Y), dim=1)  # 表示按列拼接，torch.size([3, 8])
# 总结：按照谁的拼接方式，则除了该维度可以不同外，其余维度则必须相同
# print(Z1)
# print(Z2)
print(X.sum()) # 表示其中所有元素的和
print(X.sum())
print("**"*30)
before = id(Y)
Y = X + Y # 会另外增加内存开销，但是Y[:] = Y+X。Y += X均不会增加内存开销
print(before)
print(before == id(Y))
Z = torch.zeros_like(Y)
print("id(Z): ", id(Z))
Z[:] = X + Y  # 必须加入该操作，不然还相当于另外的Z赋值
print("id(Z): ", id(Z))
A = X.numpy()
B = torch.tensor(A)
print(type(A))
print(type(B))
a = torch.tensor([3.5])
b = X.item()
print(type(b))
c = float(a)
print(type(c))