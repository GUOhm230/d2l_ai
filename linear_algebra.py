"""
本段代码：主要进行线性代数以及自动求导的计算
1).向量和矩阵的生成，复制
2).向量和矩阵的求和，并指定维度，也可保留消除的维度信息并置为1
3).向量的点积torch.dot()：向量对应元素的乘积再求和.向量和矩阵的的乘积A*B：表示形状相同的两个矩阵或者向量对应元素做乘积
torch.matmul():哈达玛积:矩阵和向量的乘积。同行元素对应相乘再相加。如果两个都是向量，则等于torch.dot()
矩阵与向量的向量积：torch.mv(A, x):其中A的列数应该等于x的向量个数
矩阵与矩阵之间的代数乘积：torch.mm(A, B)
矩阵或者向量的L2范叔：torch.norm():表示其中元素的平方和再开根号
矩阵或者向量的L1范数：torch.abs().sum():绝对值再求和
矩阵的F范数也是矩阵的L2范数：torch.norm(A)
4).自动求导：
y.backward():只能对标量求导
x.grad：存储导数，梯度
x.grad.zero_():导数清零,由于会累加梯度
y.detach():表示将y踢出计算图外，若此时在函数中，则将其作为常数，而无需参与梯度计算
"""
import torch
x = torch.tensor([3.0])
y = torch.tensor([2.0])

x = torch.arange(20)
print(len(x))
print(x.shape)

A = torch.arange(20, dtype=torch.float32).reshape(5, 4)
B = A.clone()
# print(2+A)
# print(id(A))
# print(id(B))
# print(2*B)
# print(A.T)
# B = torch.tensor([[1, 2, 3], [2, 0, 4]])
# print(B.T)

# X = torch.arange(24).reshape(2, 3, 4)
print(A)
A_sum_axis0 = A.sum(axis=0)  # 按行相加即同列相加成一列,消掉行的维度，最终是一维行向量
A_sum_axis1 = A.sum(axis=1)  # 按列相加即同行相加成一行,消掉列的维度，最终是一维行向量
# 总结：axis=0/1/2 .即表示消掉哪一维的维度
print(A_sum_axis0)
print(A_sum_axis1)
print(A_sum_axis0.shape)
print(A_sum_axis1.shape)
C = torch.arange(24, dtype=torch.float32).reshape((2, 3, 4))
print(C)
C_sum_axis0 = C.sum(axis=0)  # 按行相加即同列相加成一列,消掉行的维度，最终是一维行向量.A
C_sum_axis1 = C.sum(axis=1)  # 按行相加即同列相加成一列,消掉行的维度，最终是一维行向量.A
C_sum_axis2 = C.sum(axis=2)  # 按行相加即同列相加成一列,消掉行的维度，最终是一维行向量.A
C_sum_axis01 = C.sum(axis=[0, 1], keepdims=True)  # 按行相加即同列相加成一列,消掉行的维度，最终是一维行向量.A
C_sum_axis02 = C.sum(axis=[0, 2], keepdims=True)  # 按行相加即同列相加成一列,消掉行的维度，最终是一维行向量.A
C_sum_axis12 = C.sum(axis=[1, 2], keepdims=True)  # 按行相加即同列相加成一列,消掉行的维度，最终是一维行向量.A


print(C_sum_axis01)
print(C_sum_axis01.shape)  # 预计是[3,4]  [4], 加入keepdims=True之后表示之前的维度是保留的
print(C_sum_axis12)
print(C_sum_axis12.shape)  # 预计是[2,4]  [2]
print(C_sum_axis02)
print(C_sum_axis02.shape)  # 预计是[2,3]  [3]
"""
必须搞清楚的维度信息：
tensor([[[60., 66., 72., 78.]]])
torch.Size([1, 1, 4])

tensor([[[ 66.]],

        [[210.]]])
torch.Size([2, 1, 1])

tensor([[[ 60.],
         [ 92.],
         [124.]]])
torch.Size([1, 3, 1])
"""
sum_A1 = A.sum(axis=1, keepdims=True)  #  [5,1]
sum_A0 = A.sum(axis=0, keepdims=True)  #  [1,4]
sum_A = A.sum(axis=0)  #  [4]
print(A)
print(sum_A1)
print(A/sum_A1)
print(sum_A0)
print(A/sum_A0)
print(sum_A)
print(A/sum_A)  # axis = 0 维度[4]表示一个有4个数据的行向量，此时有一个维度与A对应，因此可以做广播机制。
# 而axis=1,维度[5]表示一个有5个数据的行向量，此时无有维度与A相同，因此不可以用作广播机制。
print(A.cumsum(axis=0))  # 表示按行叠加，即相同列逐层叠加

# print(C_sum_axis2)
# print(C_sum_axis2.shape)
x = torch.arange(5, dtype=torch.float32)
y = torch.ones(5, dtype=torch.float32)
print(torch.dot(x, y))  # 点积：相同位置元素乘积再相加.且只能是一维，二维甚至多维，只能用下一行所示的方法
print(torch.dot(x, y)==torch.sum(x*y))
print(torch.sum(A*B))  # 乘积：相同位置元素的乘积
print(x)
print(A)
# x = x.reshape(-1,1)
print(x.shape)
print(A.shape)
print(torch.mv(A.T, x))  # A.T = [4,5]与x = [5]做的是向量积，且必须矩阵的第二维度与向量的维度相同是矩阵的但是只能是前面是矩阵，后面是向量表示，Ax的矩阵向量积
# print(torch.mm(A.T, x))  # 做的是矩阵乘积积，m*n , n*k = m*k.两个都必须是矩阵，也就是说维度必须是两个

# L2范数：向量的平方和并开根号。可以有以下两种写法
print(torch.norm(x))
print(torch.dot(x, x).sqrt())

# L1范数：向量元素的绝对值之和,先绝对值再求和
print(torch.abs(x).sum())

# 矩阵的F范数：所有元素的平方和再开根号
D = torch.ones((4, 9))
print(torch.mm(D, D.T).sum().sqrt())  # 该方法只对方阵有效，如果不是方阵，则该方法并不能取得效果。，因此该方法是错的
print(torch.norm(A))  # 该方法对矩阵和向量都是有效果的


# print(A.sum()/A.numel() == A.mean())

"""以下是进行自动求导的部分"""
print("*"*20, "自动求导", "*"*20)
import torch
x = torch.arange(4, dtype=torch.float32)  # 此处要么4改成4.0,要么加上dtype
x.requires_grad_(True)  # 两者在一起等价于：x = torch.arange(x, requires_grad = True)。后面要计算梯度则必须使用这条语句
# x.grad

y = 2*torch.dot(x, x)  # x不加导数说明：tensor(28.)。加了以后：tensor(28., grad_fn=<MulBackward0>).
y = 2 * torch.norm(x)**2  # y = 2xi^2 + 2x2^2 + 2x3^2 + 2x4^2.其导数（4x1,4x2,4x3,4x4）
print(y)
y.backward()  # 必须加该步，这步才是计算反向传播梯度的方法，其内容储存在x.grad中
x.grad
print(x.grad)
print(x.grad == 4*x)
x.grad.zero_()  # 将梯度全部变为0，否则下次求梯度会累加结果
print(x.grad)
y = x.sum()  # y = x1+x2+x3+x4.其导数为（1,1,1,1）
y.backward()
print(x.grad)

x.grad.zero_()
y = x*x  # y = [x1^2, x2^2, x3^2, x4^2]
print(y)
y.sum().backward()
print(x.grad)  # 只能是标量，而不能是矩阵。因此要对y做求和操作使之成为标量。y.sum()

# 将某些计算移动到记录的计算图之外
x.grad.zero_()
y = x * x
u = y.detach() # 该操作表示：u=x^2。但是相当于u是一个常数，并不参与梯度的计算
z = u * x  # z=x^2 * x。由于将u看做常数，因此其导数=x^2 * 1 = [0, 1, 4, 9]
z.sum().backward()
print(x.grad)


#  即使构建函数的计算图需要通过python控制流，仍然可以计算得到其梯度
def f(a):
    b = a*2
    while b.norm() < 1000:
        b = b*2
        if b.sum() > 0:
            c = b
        else:
            c = 100*b

        return c

a = torch.randn(size=([2]), requires_grad=True)
print(a)
d = f(a)
print(d)
torch.norm(d).backward()
print(a.grad)

x = torch.arange(8.0).reshape(4, 2)
x1 = torch.arange(4.0)
x2 = torch.arange(24.0).reshape(2, 3, 4)
y = torch.ones(4)
print(x.T)
print(torch.matmul(x.T, y))  # 矩阵的哈达玛乘积。可以是矩阵，也可以说向量，但是其列数要相等，即一个最小单元的数字要保持相等
print(torch.matmul(x2, x.T))  # 矩阵的哈达玛乘积。可以是矩阵，也可以说向量，但是其列数要相等，即一个最小单元的数字要保持相等
# print(torch.dot(x1, y))  # 只能是向量
# print(x.T * y)
# print(torch.dot(x, y))
# print((x * y).sum())
# z = torch.arange(20, dtype=torch.float32).reshape(4, 5)
# print(torch.norm(z))
