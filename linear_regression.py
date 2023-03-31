"""
线性回归的从零开始实现：Y = Xw + b
搞清楚两个问题
1）.输入输出以及w参数的形状问题 X.shape = [样本容量，每个样本的特征数] ， w = [样本特征数，分类数]，b = [分类数]， +b部分应用的是广播机制
2）.怎么做梯度回归，反向传播计算的
"""
import random
import torch
from d2l import torch as d2l


"""
step1：生成数据：通过随机初始化x，得到真实y值
"""
def synthetic_data(w, b, num_examples):
    X = torch.normal(0, 1, (num_examples, len(w)))  # 生成一个x的数据，长度应该是1000*2
    y = torch.matmul(X, w) + b  # 表示x和w做哈达玛乘积，<1000*2,1*2>=<1000*1>
    y += torch.normal(0, 0.1, y.shape)  # 添加部分噪声
    return X, y.reshape((-1, 1))  # 防止错误起见，将y转化为列


true_w = torch.tensor([2, -3.4])
true_b = 4.2
features, labels = synthetic_data(true_w, true_b, 1000) # 获取输入数据和y的真实值

print(features.shape, labels.shape)
print(features[:, 1].detach().shape)
d2l.set_figsize()
d2l.plt.scatter(features[:, (1)].detach().numpy(), labels.detach().numpy(), 1)
# d2l.plt.show()


"""
生成迭代对象:当前的这个用法要记住
其中yield的作用类似于return，只是不会直接返回值，而是返回一个生成器，下一次迭代则从yield后面开始执行
"""
def data_iter(batch_size, features, labels):
    num_examples = len(features)
    indices = list(range(num_examples))  # 将获取0-999的数据标签，并通过shuffle()打乱
    random.shuffle(indices)
    for i in range(0, num_examples, batch_size):
        batch_indices = torch.tensor(indices[i:min(i+batch_size, num_examples)])
        yield features[batch_indices], labels[batch_indices]


batch_size = 10
# 每次都传入一个batch_size的大小
for X, y in data_iter(batch_size, features, labels):
    print(X, "\n", y)
    break


# 定义初始化模型参数
w = torch.normal(0, 0.01, size= (2, 1), requires_grad= True)
b = torch.zeros(1, requires_grad= True)


# 定义模型
def linereg(X, w, b):
    return torch.matmul(X, w) + b


# 定义损失函数为均方损失
def squared_loss(y_hat, y):
    return (y_hat - y.reshape(y_hat.shape))**2 / 2


# 定义优化算法SGD,主要是更新w,b并不计算，因此无需梯度下降
def sgd(params, lr, batch_size):
     with torch.no_grad():
         for param in params:
             param -= lr*param.grad / batch_size
             param.grad.zero_() # torch中对梯度具有累加的性质，因此需要先清零


# 开始训练
lr = 0.03
num_epochs = 3 # 遍历全部数据的次数
net = linereg # 可对函数名进行赋值
loss = squared_loss


for epoch in range(num_epochs):
    for X, y in data_iter(batch_size, features, labels):
        l = loss(net(X, w, b), y)
        l.sum().backward() # 对每个batch_size都需要做反向传播算法,得到梯度
        sgd([w, b], lr, batch_size)
        with torch.no_grad():
            train_l = loss(net(features, w, b), labels) # 同样的数据输入，查看其中的预测值的效果
    print(f'epoch {epoch + 1 }, loss {float(train_l.mean()): f}')
