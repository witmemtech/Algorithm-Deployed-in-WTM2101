import torch.nn as nn
import torch.nn.functional as F
import numpy as np
import onnx
from onnx import helper
from abc import abstractmethod,ABCMeta


class WitmemBaseNet(nn.Module, metaclass=ABCMeta):
    def __init__(self): 
        super().__init__()    
        self.initializer = []
        self.all_nodes = []
    
    def makeNodeConv2d(self, weight_path, idx, input_name, strides, padding):
        weight = np.load(weight_path)
        weight_t_name = 'weight_tensor'+str(idx)
        bias_t_name = 'bias_tensor'+str(idx)

        weight_t = helper.make_tensor(weight_t_name, data_type=onnx.TensorProto.FLOAT, dims=weight.shape, vals=weight.flatten())
        bias_t = helper.make_tensor(bias_t_name, data_type=onnx.TensorProto.FLOAT, dims=[weight.shape[0]], vals=np.zeros(weight.shape[0]))

        node_conv2d = helper.make_node('Conv',
                                    inputs = [input_name, weight_t_name, bias_t_name],
                                    outputs = ['conv2d_out'+str(idx)],
                                    strides = strides,
                                    kernel_shape = [weight.shape[2], weight.shape[3]],
                                    pads = padding,
                                    name = 'conv2d_'+str(idx)
                                    )
        return node_conv2d, [weight_t,bias_t]

    def makeNodeScale(self, input_name, output_name, G):
        node_scale = onnx.helper.make_node("Scale", inputs=[input_name], outputs=[output_name], scale=1/G)
        return node_scale

    def makeNodeRelu(self, input_name, output_name):
        node_relu = onnx.helper.make_node('Relu', [input_name], [output_name])
        return node_relu

    def makeNodeAdd(self, input_name, output_name):
        node_add = onnx.helper.make_node('Add', input_name, [output_name])
        return node_add

    def makeNodeGlobalAveragePool(self, input_name, output_name, scale_in = 1, scale_out = 1):
        node_scale = onnx.helper.make_node('GlobalAveragePool', [input_name], [output_name], scale_in=scale_in, scale_out=scale_out)
        return node_scale
    def makeNodeLinear(self, weight_path, idx, input_name):
        weight = np.load(weight_path)
        weight_t_name = 'weight_tensor'+str(idx)
        bias_t_name = 'bias_tensor'+str(idx)

        weight_t = helper.make_tensor(weight_t_name, data_type=onnx.TensorProto.FLOAT, dims=np.shape(np.transpose(weight)), vals=np.transpose(weight).flatten())
        bias_t = helper.make_tensor(bias_t_name, data_type=onnx.TensorProto.FLOAT, dims=[weight.shape[0]], vals=np.zeros(weight.shape[0]))

        node_conv2d = helper.make_node('Gemm',
                                    inputs = [input_name, weight_t_name, bias_t_name],
                                    outputs = ['linear_out'+str(idx)],
                                    name = 'linear_'+str(idx)
                                    )
        return node_conv2d, [weight_t,bias_t]

    @abstractmethod
    def forward(self, _input):
        '''
            浮点模型前向
        '''
        raise NotImplemented
    
    @abstractmethod
    def forward_quant(self, _input):
        '''
            定点模型前向
        '''
        raise NotImplemented
    
    @abstractmethod
    def onnx_convert(self, weight_root, onnx_save_path):
        '''
            根据网络结构构建onnx
        '''
        raise NotImplemented