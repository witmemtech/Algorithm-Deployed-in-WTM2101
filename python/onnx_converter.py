import os
import numpy as np
import torch

from net.net_dnn import DnnNet, DnnNetDeep
from config import witin_config


def save_node_weight(weight_path):
    torch_weight = torch.load(weight_path, map_location=torch.device('cpu')) 

    save_path = os.path.join(os.path.dirname(weight_path),"params")
    if not os.path.exists(save_path):
        os.mkdir(save_path)
    
    for key in torch_weight.keys():
        key1 = key.replace('.', '_')
        item_save_weightpath = os.path.join(save_path,"{}.npy".format(key1))
        value = (torch_weight[key]*1024).round().clip(min = -128, max = 127)
        np.save(item_save_weightpath, value.detach().cpu().numpy())

if __name__ == '__main__':
    net_type = witin_config['net_type']
    if net_type == 'DNN':
        net = DnnNet()
    elif net_type == 'DNN_DEEP':
        net = DnnNetDeep()
    else:
        raise NameError  
    
    # 存储模型每个结点的权重
    weight_path = 'models/DNN/bestModel.pth'
    save_node_weight(weight_path)

    # onnx格式转换
    onnx_save_path = os.path.join(os.path.dirname(weight_path),"bestModel.onnx")    
    weight_root = os.path.join(os.path.dirname(weight_path),"params")
    net.onnx_convert(weight_root, onnx_save_path)
    print('ONNX model conversion completed!')