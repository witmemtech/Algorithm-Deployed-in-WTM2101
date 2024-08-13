import numpy as np
import os
import onnx
import torch
import json

def make_tensor(filepath, t_name, tranpose=False, dims=0):

    array = filepath
    if tranpose == True:
        array = np.transpose(array)
    if dims != 0:
        dims = dims
    else:
        dims = np.shape(array)
    tensor_0 = onnx.helper.make_tensor(t_name,
                            data_type=onnx.TensorProto.FLOAT,
                            dims=dims,
                            vals=array.flatten())
    return tensor_0

def make_linear(w_file, b_file, G, inputName, nodeName, tranpose=False):
    linear_w = make_tensor(w_file, nodeName + "_w",tranpose)
    linear_b = make_tensor(b_file, nodeName + "_b")
    output = nodeName + "_output"

    linear_node = onnx.helper.make_node(
        'Gemm',
        inputs=[inputName, nodeName + "_w", nodeName + "_b"],
        outputs=[output],
        name=nodeName)

    linear_scale = onnx.helper.make_node('Scale', [output],
                                          [nodeName + "_scale"],
                                          scale=1/G)


    inits = [linear_w, linear_b]
    nodes = [linear_node, linear_scale]
    return inits, nodes, nodeName + "_scale"

def quant_wb(w, b):
    _w = w.cpu().detach().numpy()
    _b = b.cpu().detach().numpy()
    _w = (_w * 1024).round().clip(-128, 127)
    _b = ((_b * 1024 * 255).round()//128)*128

    return _w, _b

def export_net1():
    name = 'net1'
    weights = torch.load("models/bestModel.pth")

    ### net1
    all_inits = []
    all_nodes = []

    # linear
    w, b = quant_wb(weights['qkv_mat.weight'], weights['qkv_mat.bias'])
    inits, nodes, outputName = make_linear(w, b, G=2048, inputName="in1", nodeName="qkvmat", tranpose=True)
    all_inits = all_inits + inits
    all_nodes = all_nodes + nodes

    # gen graph
    in_shape = (1, 392)
    out_shape = (1, 384)
    graph = onnx.helper.make_graph(
        all_nodes,
        name='net1',
        inputs=[onnx.helper.make_tensor_value_info("in1", onnx.TensorProto.FLOAT, list(in_shape))],
        outputs=[
            onnx.helper.make_tensor_value_info(outputName, onnx.TensorProto.FLOAT, list(out_shape))
        ],
        initializer=all_inits)
    model = onnx.helper.make_model(graph, producer_name="net1")
    with open('models/net1.onnx', "wb") as of:
        of.write(model.SerializeToString())

def export_net2():
    name = 'net2'
    weights = torch.load("models/bestModel.pth")

    ### net1
    all_inits = []
    all_nodes = []

    # linear
    w, b = quant_wb(weights['head.weight'], weights['head.bias'])
    inits, nodes, outputName = make_linear(w, b, G=8192, inputName="in2", nodeName="head", tranpose=True)
    all_inits = all_inits + inits
    all_nodes = all_nodes + nodes

    # gen graph
    in_shape = (1, 256)
    out_shape = (1, 10)
    graph = onnx.helper.make_graph(
        all_nodes,
        name='net2',
        inputs=[onnx.helper.make_tensor_value_info("in2", onnx.TensorProto.FLOAT, list(in_shape))],
        outputs=[
            onnx.helper.make_tensor_value_info(outputName, onnx.TensorProto.FLOAT, list(out_shape))
        ],
        initializer=all_inits)
    model = onnx.helper.make_model(graph, producer_name="net2")
    with open('models/net2.onnx', "wb") as of:
        of.write(model.SerializeToString())


if __name__ == "__main__":
    export_net1()
    export_net2()
    
    print("ok")