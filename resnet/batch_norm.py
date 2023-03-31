"""
手动实现批量归一化操作
要求：
1.学习代码编写的技巧
2.学会什么时候创建类
3.归一化技术
"""

import torch
from torch import nn
from d2l import torch as d2l

device = "cuda:0" if torch.cuda.is_available() else "cpu"


def batch_norm(X, gamma, beta, moving_mean, moving_var, eps, momentum):
    if not torch.is_grad_enabled():  # inference期间
        X_hat = (X - moving_mean) / torch.sqrt(moving_var + eps)  # + beta
    else:
        assert len(X.shape) in (2, 4)
        if len(X.shape) == 2:
            # 如果是二维的，第一个维度是
            mean = X.mean(dim=0, keepdim=True)  # 表示按行求取均值，最后求得的维度是除去行维度剩余列维度.所谓按行计算就是每行取一个，计算其中均值，得到的结果是剩余维度
            var = ((X - mean)**2).mean(dim=0)  # 保留维度是为了后面方便做广播计算
        else:
            mean = X.mean(dim=(0, 2, 3), keepdim=True)  # 保留维度是为了后面方便做广播计算
            var = ((X - mean)**2).mean(dim=0)
        X_hat = (X-mean) / torch.sqrt(var+eps)
        # 为什么这样计算迭代
        moving_mean = momentum * moving_mean + (1.0 - momentum) * mean  # 训练时，滑动更新均值和方差。因为当前并不知道全局有多少个样本，因此需要求滑动平均值
        moving_var = momentum * moving_var + (1.0 - momentum) * var
    Y = gamma * X_hat + beta
    return Y, moving_mean.data, moving_var.data


# 创建一个正确的BatchNorm图层
class BatchNorm(nn.Module):
    def __init__(self, num_features, num_dims):  # num_featurs:2维表示特征数，4维表示通道数
        super().__init__()
        if num_dims == 2:
            shape = (1, num_features)
        else:
            shape = (1, num_features, 1, 1)  # 这个维度是计算mean之后的剩余维度，因此mean，var都是这个维度，而对应的gamma beta也是这个维度
        self.gamma = nn.Parameter(torch.ones(shape))
        self.beta = nn.Parameter(torch.zeros(shape))
        self.moving_mean = torch.zeros(shape)
        self.moving_var = torch.ones(shape)

    def forward(self, X):
        if self.moving_mean.device != X.device:
            self.moving_mean = self.moving_mean.to(device)
            self.moving_var = self.moving_var.to(device)
        Y, self.moving_mean, self.moving_var = batch_norm(X, self.gamma, self.beta, self.moving_mean, self.moving_var, eps=1e-5, momentum=0.9)
        return Y


# 应用BatchNorm于LeNet模型
# 卷积网络的一些概念，网络构建时候，这些维度设置的意义和方法
net = nn.Sequential(nn.Conv2d(1, 6, kernel_size=5), BatchNorm(6, num_dims=4),
                    nn.Sigmoid(), nn.MaxPool2d(kernel_size=2, stride=2),
                    nn.Conv2d(6, 16, kernel_size=5), BatchNorm(16, num_dims=4),
                    nn.Sigmoid(), nn.MaxPool2d(kernel_size=2, stride=2),
                    nn.Flatten(), nn.Linear(16*4*4, 120),
                    BatchNorm(120, num_dims=2), nn.Sigmoid(),
                    nn.Linear(120, 84), BatchNorm(84, num_dims=2),
                    nn.Sigmoid(), nn.Linear(84, 10))
# print(net.parameters())
print(net)
# for k, v in net.state_dict().items():
#     # print(v)
#     print(k, v.shape)
# 本处要学习的地方：数据下载怎么写， train部分怎么写，要完全手打，怎么生成训练图
lr, num_epochs, batch_size = 1.0, 10, 256
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size)
d2l.train_ch6(net, train_iter, test_iter, num_epochs, lr, d2l.try_gpu())


# if __name__ =='__main__':
#     a = torch.arange(48, dtype=torch.float32)  # 其内的数据需要进一步提升
#     # print(a)
#     b = a.reshape(2, 2, 3, 4)  # 2行6列
#     # print(b)
#     c = b.mean(dim=[1, 2, 3], keepdims=True)  # 出去0, 2, 3维度，只剩下通道纬，也就是2
#     # print(c)
#     # print(c.shape)
#     device = "cuda:1" if torch.cuda.is_available() else "cpu"
#     x = torch.arange(3)
#     y = torch.arange(3)
#     x = x.cuda()
#     y = y.cuda()
#     print(x+y)

