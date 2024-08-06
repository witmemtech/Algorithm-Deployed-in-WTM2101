# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
import numpy as np
import math
import onnx
import os
from onnx import helper, TensorProto, mapping
import scipy
import sys
import witin
from witin import *

#### 改成自己路径
DIR_ROOT = "/home/yxt/input/"

def get_tvm_output(onnx_path, quant_path):

    ## 名字与graph输入名称保持一致
    input_name = 'in' 
    shape_dict = dict()
    shape_dict[input_name] = (1, 800)
    
    onnx_model = onnx.load(onnx_path)
    mod, params = witin_frontend.frontend.from_onnx(onnx_model, shape_dict)
    
    feats = np.load(quant_path).astype('float32')
    print("src shape:",feats.shape)

    input_dt = {}
    ## 名字与节点保持一致
    input_dt[input_name] = witin.nd.array(feats)

    with witin.transform.PassContext(opt_level=3):
        _, _, _, npu_graph = witin_frontend.build_module.build(mod,
                                        target='npu',
                                        target_host='npu',
                                        params=params, input_data=input_dt,
                                        chip="BB04P1"
                                        )


if __name__ == '__main__':

    onnx_path = DIR_ROOT+'bestModel.onnx'
    quant_data_path = DIR_ROOT+"test_data_0_100.npy"
    get_tvm_output(onnx_path,quant_data_path)
