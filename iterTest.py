"""
本段代码测试torch.utils.data.TensorDataset以及DataLoader
"""
import torch
from torch.utils.data import TensorDataset, DataLoader
a = torch.tensor([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12], [13, 14, 15], [16, 17, 18], [7, 8, 9], [7, 8, 9], [7, 8, 9]])
b = torch.tensor([44, 55, 66, 44, 55, 66, 44, 55, 66])
c = (a, b)
train_ids = TensorDataset(*c)
print(train_ids)
print(train_ids[:2])  # 输出都是一组数据，包括：a, b
# 循环取数据
for x_train, y_label in train_ids:
    print(x_train, y_label)


print("**"*20, "DataLoader", "**"*20)
train_loader = DataLoader(dataset=train_ids, batch_size=4, shuffle=False)
print(train_loader)
print(next(iter(train_loader)))  # 输出接下来的一个batch_size的数据
for i, data in enumerate(train_loader, 2):  # enumerate(seq, start=[]),输入来个数据：迭代对象（元组，列表，数组等）和下标开始值。输出两个数据：序号，（data, label）.后面的数据表示第一个数据从什么时候开始
    x_data, label = data
    print(i, x_data, label)