import torch

x = torch.arange(24).reshape(12, 2)
print(x)
print(len(x))
print(x.sum(axis=0))
print(x.shape)
y = x/x.sum(axis=1)
print(y)