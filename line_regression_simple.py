import torch
from d2l import torch as d2l
from torch.utils import data
import numpy as np

# 生成真实训练数据：成线性相关
true_w = torch.tensor([2, -3.4])
true_b = 4.2
NUM_SAMPLE = 1000
features, labels = d2l.synthetic_data(true_w, true_b, NUM_SAMPLE)
print(features)

# 构造数据迭代器:dataset和dataloader函数的使用
def load_array(data_arrays, batch_size, is_train=True):
   dataset = data.TensorDataset(*data_arrays)  # *号的用法，元祖取值。TensorDataset是对数据进行打包
   return data.DataLoader(dataset, batch_size, shuffle=True)


batch_size = 10
data_iter = load_array((features, labels), batch_size)

print(next(iter(data_iter)))

# 使用torch中预定义好的层
from torch import nn
net = nn.Sequential(nn.Linear(2, 1))  # 线性回归相当于就是一个线性层也就是全链接层，里面输入的维度是2：表示每个样本的输入特征是两个，输出一个值
print(net)


# 初始化模型参数
net[0].weight.data.normal_(0, 0.01)
net[0].bias.data.fill_(0.01)
print("参数输出：")
print(next(iter(net.parameters())))  # 只输出了权重w的值
print(net[0].weight)
print(net[0].bias)
print("done!")


# 损失函数：使用均方误差
loss = nn.MSELoss()

# 实例化SGD
trainer = torch.optim.SGD(net.parameters(), lr=0.002)

# 开始训练
num_epochs = 1
for epoch in range(num_epochs):
   i = 0
   for X, y in data_iter:
      i += 1
      l = loss(net(X), y)
      trainer.zero_grad()
      l.backward()
      print("w的梯度：", net[0].weight.grad)
      # print("shuchu:", net(X), y)
      # print(loss(net(X), y))
      # break
      # print("b的梯度：", true_w.grad)
      trainer.step()
   l = loss(net(features), labels)
   print(i)
   print(f'epoch {epoch + 1}, loss {1:f}')

