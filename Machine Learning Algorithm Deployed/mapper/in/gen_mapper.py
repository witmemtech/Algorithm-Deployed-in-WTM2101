import numpy as np
import math
import onnx
import os
from onnx import helper, TensorProto, mapping
import scipy
import sys
import datetime
import witin
from witin import *

#### 改成自己路径
DIR_ROOT = "/your/path/"


def gen_info(name, onnx_path, shape, data_path, do_pn=False):
    shape_dict1 = {}
    #名字与graph输入名称保持一致
    shape_dict1[name] = shape
    mod1, params1 = witin_frontend.frontend.from_onnx(onnx.load(onnx_path), shape_dict1)
    input_dt1 = {}
    _data = np.load(data_path).astype('float32')
    if do_pn:
        _data = np.concatenate((_data, _data * (-1)), axis=1) 
        _data[_data < 0] = 0
    print(name, "----data shape", _data.shape)
    input_dt1['input_data'] = witin.nd.array(_data)
    return mod1, params1, input_dt1

def gen_mapper():

    models = []
    params = []
    inputs = []

    ## net1
    _model1, _params1, _input1 = gen_info(name="in1", onnx_path=DIR_ROOT+"net1.onnx", shape=(1,392), data_path=DIR_ROOT+"qkv_input.npy")
    ## net2
    _model2, _params2, _input2 = gen_info(name="in2", onnx_path=DIR_ROOT+"net2.onnx", shape=(1,256), data_path=DIR_ROOT+"head_input.npy", do_pn=True)

    models.append(_model1)
    models.append(_model2)
    params.append(_params1)
    params.append(_params2)
    inputs.append(_input1)
    inputs.append(_input2)

    build_dir = "./output_attention"
    with witin.transform.PassContext(opt_level=3):
        _, _, _, npu_graphs = witin_frontend.build_module.build(models,
                                                                target='npu',
                                                                target_host='npu',
                                                                params=params,
                                                                input_data=inputs,
                                                                chip="BB04P1",
                                                                output_dir=build_dir,
                                                                optimize_method_config=DIR_ROOT+"opt.protobuf",
                                                                )



if __name__ == '__main__':
    gen_mapper()
