import torch
import torch.nn as nn
import torch.nn.functional as F
import numpy as np
import cv2
from net.net_base import WitmemBaseNet
import os
import onnx
from onnx import helper


class DnnNet(WitmemBaseNet):
    def __init__(self,data_len = 64):
        '''
        mnist gray image shape is [28,28]
        '''
        super().__init__()

        self.layer1 = nn.Linear(data_len,256, bias = False) 
        self.relu1 = nn.ReLU(True)
        self.layer2 = nn.Linear(256,256, bias = False) 
        self.relu2 = nn.ReLU(True)
        self.layer3 = nn.Linear(256,256, bias = False) 
        self.relu3 = nn.ReLU(True)
        self.layer4 = nn.Linear(256,256, bias = False) 
        self.relu4 = nn.ReLU(True)
        self.layer5 = nn.Linear(256,2, bias = False) 

        self.model_in_name = 'in'
        self.model_out_name = 'out'
        self.model_input_shape = [1,800]
        self.model_output_shape = [1,2]
        self.quant_layer = dict()

    def forward(self, _input):
        x = self.layer1(_input)
        x = self.relu1(x)
        x = self.layer2(x)
        x = self.relu2(x)
        x = self.layer3(x)
        x = self.relu3(x)
        x = self.layer4(x)
        x = self.relu4(x)
        out = self.layer5(x)
        return out
    
    def degbug_forward(self, _input):
        x1 = self.layer1(_input)
        x2 = self.relu1(x1)
        x3 = self.layer2(x2)
        x4 = self.relu2(x3)
        x5 = self.layer3(x4)
        x6 = self.relu3(x5)
        x7 = self.layer4(x6)
        x8 = self.relu4(x7)
        out = self.layer5(x8)
        return out, x1
    
    def forward_quant(self, _input):
        def quant_linear(src_layer, _input, name, G=1024):
            if name not in self.quant_layer:
                w = src_layer.weight.data
                w_temp = G * w
                w_temp = torch.clip_(torch.round(w_temp),-128,127)
                b = None
                self.quant_layer[name] = [w_temp,b]
            output = F.linear(_input, self.quant_layer[name][0])
            output /= G
            output = torch.clip_(torch.round(output),-128,127)
            return output
        
        output1 = quant_linear(self.layer1, _input , "layer_1")
        output1 = self.relu1(output1)
        output1 = quant_linear(self.layer2, output1 , "layer_2")
        output1 = self.relu2(output1)
        output1 = quant_linear(self.layer3, output1 , "layer_3")
        output1 = self.relu3(output1)
        output1 = quant_linear(self.layer4, output1 , "layer_4")
        output1 = self.relu4(output1)
        output1 = quant_linear(self.layer5, output1 , "layer_5")
        return output1

    def onnx_convert(self, weight_root, onnx_save_path):
        node_linear_1, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer1_weight.npy'), idx = 1, input_name=self.model_in_name)
        node_scale1 = self.makeNodeScale('linear_out1', 'scale_out1', 1024)
        node_relu1 = self.makeNodeRelu('scale_out1','relu_out1')
        self.all_nodes.extend([node_linear_1, node_scale1, node_relu1])
        self.initializer.extend(w_b)

        node_linear_2, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer2_weight.npy'), idx = 2, input_name='relu_out1')
        node_scale2 = self.makeNodeScale('linear_out2', 'scale_out2', 1024)
        node_relu2 = self.makeNodeRelu('scale_out2','relu_out2')
        self.all_nodes.extend([node_linear_2, node_scale2, node_relu2])
        self.initializer.extend(w_b)

        node_linear_3, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer3_weight.npy'), idx = 3, input_name='relu_out2')
        node_scale3 = self.makeNodeScale('linear_out3', 'scale_out3', 1024)
        node_relu3 = self.makeNodeRelu('scale_out3','relu_out3')
        self.all_nodes.extend([node_linear_3, node_scale3, node_relu3])
        self.initializer.extend(w_b)

        node_linear_4, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer4_weight.npy'), idx = 4, input_name='relu_out3')
        node_scale4 = self.makeNodeScale('linear_out4', 'scale_out4', 1024)
        node_relu4 = self.makeNodeRelu('scale_out4','relu_out4')
        self.all_nodes.extend([node_linear_4, node_scale4, node_relu4])
        self.initializer.extend(w_b)

        node_linear_5, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer5_weight.npy'), idx = 5, input_name='relu_out4')
        node_scale5 = self.makeNodeScale('linear_out5', self.model_out_name, 1024)
        self.all_nodes.extend([node_linear_5, node_scale5])
        self.initializer.extend(w_b)
        

        inputs = [helper.make_tensor_value_info(self.model_in_name, onnx.TensorProto.FLOAT, list(self.model_input_shape))]
        outputs = [helper.make_tensor_value_info(self.model_out_name, onnx.TensorProto.FLOAT, list(self.model_output_shape))]

        graph = helper.make_graph(self.all_nodes,'model',inputs,outputs,self.initializer)
        model = helper.make_model(graph)

        with open(onnx_save_path,"wb") as of:
            of.write(model.SerializeToString())

class DnnNetDeep(WitmemBaseNet):
    def __init__(self,data_len = 800):
        '''
        mnist gray image shape is [28,28]
        '''
        super().__init__()

        self.layer1 = nn.Linear(data_len,256, bias = False) 
        self.relu1 = nn.ReLU(True)
        self.layer2 = nn.Linear(256,256, bias = False) 
        self.relu2 = nn.ReLU(True)
        self.layer3 = nn.Linear(256,256, bias = False) 
        self.relu3 = nn.ReLU(True)
        self.layer4 = nn.Linear(256,256, bias = False) 
        self.relu4 = nn.ReLU(True)
        self.layer5 = nn.Linear(256,256, bias = False) 
        self.relu5 = nn.ReLU(True)
        self.layer6 = nn.Linear(256,256, bias = False)
        self.relu6 = nn.ReLU(True)
        self.layer7 = nn.Linear(256,128, bias = False)
        self.relu7 = nn.ReLU(True)
        self.layer8 = nn.Linear(128,64, bias = False)
        self.relu8 = nn.ReLU(True)
        self.layer9 = nn.Linear(64,2, bias = False)

        self.model_in_name = 'in'
        self.model_out_name = 'out'
        self.model_input_shape = [1,800]
        self.model_output_shape = [1,2]
        self.quant_layer = dict()

    def forward(self, _input):
        x = self.layer1(_input)
        x = self.relu1(x)
        x = self.layer2(x)
        x = self.relu2(x)
        x = self.layer3(x)
        x = self.relu3(x)
        x = self.layer4(x)
        x = self.relu4(x)
        x = self.layer5(x)
        x = self.relu5(x)
        x = self.layer6(x)
        x = self.relu6(x)
        x = self.layer7(x)
        x = self.relu7(x)
        x = self.layer8(x)
        x = self.relu8(x)
        out = self.layer9(x)
        return out
    
    def forward_quant(self, _input):
        def quant_linear(src_layer, _input, name, G=1024):
            if name not in self.quant_layer:
                w = src_layer.weight.data
                w_temp = G * w
                w_temp = torch.clip_(torch.round(w_temp),-128,127)
                b = None
                self.quant_layer[name] = [w_temp,b]
            output = F.linear(_input, self.quant_layer[name][0])
            output /= G
            output = torch.clip_(torch.round(output),-128,127)
            return output
        
        output1 = quant_linear(self.layer1, _input , "layer_1")
        output1 = self.relu1(output1)
        output1 = quant_linear(self.layer2, output1 , "layer_2")
        output1 = self.relu2(output1)
        output1 = quant_linear(self.layer3, output1 , "layer_3")
        output1 = self.relu3(output1)
        output1 = quant_linear(self.layer4, output1 , "layer_4")
        output1 = self.relu4(output1)
        output1 = quant_linear(self.layer5, output1 , "layer_5")
        output1 = self.relu5(output1)
        output1 = quant_linear(self.layer6, output1 , "layer_6")
        output1 = self.relu6(output1)
        output1 = quant_linear(self.layer7, output1 , "layer_7")
        output1 = self.relu7(output1)
        output1 = quant_linear(self.layer8, output1 , "layer_8")
        output1 = self.relu8(output1)
        output1 = quant_linear(self.layer9, output1 , "layer_9")
        return output1

    def onnx_convert(self, weight_root, onnx_save_path):
        node_linear_1, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer1_weight.npy'), idx = 1, input_name=self.model_in_name)
        node_scale1 = self.makeNodeScale('linear_out1', 'scale_out1', 1024)
        node_relu1 = self.makeNodeRelu('scale_out1','relu_out1')
        self.all_nodes.extend([node_linear_1, node_scale1, node_relu1])
        self.initializer.extend(w_b)

        node_linear_2, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer2_weight.npy'), idx = 2, input_name='relu_out1')
        node_scale2 = self.makeNodeScale('linear_out2', 'scale_out2', 1024)
        node_relu2 = self.makeNodeRelu('scale_out2','relu_out2')
        self.all_nodes.extend([node_linear_2, node_scale2, node_relu2])
        self.initializer.extend(w_b)

        node_linear_3, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer3_weight.npy'), idx = 3, input_name='relu_out2')
        node_scale3 = self.makeNodeScale('linear_out3', 'scale_out3', 1024)
        node_relu3 = self.makeNodeRelu('scale_out3','relu_out3')
        self.all_nodes.extend([node_linear_3, node_scale3, node_relu3])
        self.initializer.extend(w_b)

        node_linear_4, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer4_weight.npy'), idx = 4, input_name='relu_out3')
        node_scale4 = self.makeNodeScale('linear_out4', 'scale_out4', 1024)
        node_relu4 = self.makeNodeRelu('scale_out4','relu_out4')
        self.all_nodes.extend([node_linear_4, node_scale4, node_relu4])
        self.initializer.extend(w_b)

        node_linear_5, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer5_weight.npy'), idx = 5, input_name='relu_out4')
        node_scale5 = self.makeNodeScale('linear_out5', 'scale_out5', 1024)
        node_relu5 = self.makeNodeRelu('scale_out5','relu_out5')
        self.all_nodes.extend([node_linear_5, node_scale5, node_relu5])
        self.initializer.extend(w_b)

        node_linear_6, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer6_weight.npy'), idx = 6, input_name='relu_out5')
        node_scale6 = self.makeNodeScale('linear_out6', 'scale_out6', 1024)
        node_relu6 = self.makeNodeRelu('scale_out6','relu_out6')
        self.all_nodes.extend([node_linear_6, node_scale6, node_relu6])
        self.initializer.extend(w_b)

        node_linear_7, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer7_weight.npy'), idx = 7, input_name='relu_out6')
        node_scale7 = self.makeNodeScale('linear_out7', 'scale_out7', 1024)
        node_relu7 = self.makeNodeRelu('scale_out7','relu_out7')
        self.all_nodes.extend([node_linear_7, node_scale7, node_relu7])
        self.initializer.extend(w_b)

        node_linear_8, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer8_weight.npy'), idx = 8, input_name='relu_out7')
        node_scale8 = self.makeNodeScale('linear_out8', 'scale_out8', 1024)
        node_relu8 = self.makeNodeRelu('scale_out8','relu_out8')
        self.all_nodes.extend([node_linear_8, node_scale8, node_relu8])
        self.initializer.extend(w_b)

        node_linear_9, w_b = self.makeNodeLinear(os.path.join(weight_root, 'layer9_weight.npy'), idx = 9, input_name='relu_out8')
        node_scale9 = self.makeNodeScale('linear_out9', self.model_out_name, 1024)
        self.all_nodes.extend([node_linear_9, node_scale9])
        self.initializer.extend(w_b)
        

        inputs = [helper.make_tensor_value_info(self.model_in_name, onnx.TensorProto.FLOAT, list(self.model_input_shape))]
        outputs = [helper.make_tensor_value_info(self.model_out_name, onnx.TensorProto.FLOAT, list(self.model_output_shape))]

        graph = helper.make_graph(self.all_nodes,'model',inputs,outputs,self.initializer)
        model = helper.make_model(graph)

        with open(onnx_save_path,"wb") as of:
            of.write(model.SerializeToString())
    

def getTestImage():
    img = cv2.imread("data//val//0aIGIzhLjERwBnH.bmp",cv2.IMREAD_GRAYSCALE)
    img = img[np.newaxis,np.newaxis,...]
    img = torch.tensor(img,dtype=torch.float32)
    return img

if __name__ == "__main__":
    net = DnnNet()
    img = getTestImage()

    output = net(img)
    # print('output:', output)

    onnx_save_path = 'models/dnn/bestModel.onnx'
    net.onnx_convert(onnx_save_path)
    print('done!')
