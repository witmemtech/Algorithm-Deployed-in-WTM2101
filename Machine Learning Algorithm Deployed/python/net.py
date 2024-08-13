import torch
import torch.nn as nn
import torch.nn.functional as F

class WitmemDemoNet(nn.Module):
    def __init__(self):
        '''
        mnist gray image shape is [28,28]
        '''
        super(WitmemDemoNet, self).__init__()
        self.qkv_mat = nn.Linear(in_features=28*14, out_features=128*3, bias=True)
        self.head = nn.Linear(in_features=128*2, out_features=10, bias=True)

        ## quant
        self.first_quant = True
      
    def forward(self, _input):
        q, k, v= self.qkv_mat(_input).split(128, dim=-1)
        qk = q @ k.transpose(-2,-1)
        softmax_qk = F.softmax(qk, dim=-1)
        qkv = softmax_qk @ v
        qkv = qkv.reshape(qkv.shape[0], -1)
        out = self.head(qkv)
        return out