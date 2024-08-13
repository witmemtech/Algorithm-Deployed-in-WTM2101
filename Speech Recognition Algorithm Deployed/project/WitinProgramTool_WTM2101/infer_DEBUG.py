import numpy as np
import os
import subprocess
import matplotlib.pyplot as plt
import struct
from tempfile import NamedTemporaryFile
import sys
import getopt
from sklearn.metrics.pairwise import cosine_similarity
import time

plt.rcParams.update({'figure.max_open_warning': 0})

WPT_exe = "./WitinProgramTool_DEBUG.exe"

def infer_layer(input, xs, xe, ys, ye, zs, ze, g, infer_avg, skip_fw):

    f1 = NamedTemporaryFile(mode="w", dir=".\\", delete=False)
    np.savetxt(f1, input, fmt="%d")
    f1.close()

    f2 = NamedTemporaryFile(mode="w", dir=".\\", delete=False)
    f2.write(str(xs) + ", " + str(xe) + ", " + str(ys) + ", " + str(ye) + ", " + str(zs) + ", " + str(ze) + ", " + str(g) + "\n")
    f2.close()
	
    if skip_fw == 0:
        subprocess.run([WPT_exe, "-m", "infer", "--infer_avg", str(infer_avg), "-i", f1.name, "-l", f2.name, "-r", str(np.shape(input)[0])])
    else:
        subprocess.run([WPT_exe, "-m", "infer", "--infer_avg", str(infer_avg), "-i", f1.name, "-l", f2.name, "-r", str(np.shape(input)[0]), "--skip_fw"])

    output = np.loadtxt("./infer_output.txt")
    if output.ndim == 1:
        output = np.expand_dims(output, axis=1)

    os.remove("./infer_output.txt")
    os.remove(f1.name)
    os.remove(f2.name)

    return output


def infer_round(path):

    input_file = os.path.join(path, "data_input.txt")

    lines = np.shape(open(input_file, 'r').readlines())[0]

    subprocess.run([WPT_exe, "-m", "infer_round", "-i", input_file, "-l", path, "-r", str(lines)])

    # output: infer_output.txt


def infer_net(path, avg_num):

    layer_txt = os.path.join(path, "layers.txt")
    expected_in = os.path.join(path, "expected_in.bin")
    expected_out = os.path.join(path, "expected_out.bin")
    average_txt = os.path.join(path, "average.txt")

    layer_info = np.loadtxt(layer_txt, delimiter=',')
    if layer_info.ndim == 1:
        layer_info = np.expand_dims(layer_info, axis=0)

    fi = open(expected_in, "rb")
    fo = open(expected_out, "rb")

    row = struct.unpack("h", fi.read(2))[0]
    layer_num = np.shape(layer_info)[0]

    if os.path.exists(average_txt):
        average_info = np.loadtxt(average_txt, dtype=int)
    else:
        average_info = np.ones(layer_num, dtype=int) * 2

    #index = int(row/2)
    index = 0

    for layer in range(layer_num):
        
        if layer == 0:
            skip_fw = 0
        else:
            skip_fw = 1
        
        print("Layer " + str(layer))
        xs, xe, ys, ye, zs, ze, g = layer_info[layer, :].astype(int)
        input_Lx = np.zeros((row, ye-ys+1))
        output_expected_Lx = np.zeros((row, xe-xs+1))

        for i in range(row):
            input_Lx[i, :] = [struct.unpack("h", fi.read(2))[0] for j in range(ye-ys+1)]        
            output_expected_Lx[i, :] = [struct.unpack("h", fo.read(2))[0] for j in range(xe-xs+1)]

        output_Lx = np.zeros((row, xe-xs+1))
        for i in range(avg_num):
            output_Lx += infer_layer(input_Lx, xs, xe, ys, ye, zs, ze, g, average_info[layer], skip_fw)
        output_Lx = output_Lx.astype(int) // avg_num

        diff = np.mean(output_expected_Lx - output_Lx, axis=0).astype(int)
        output_Lx2 = np.clip(output_Lx + diff, -128, 127)
        
        if output_Lx.ndim == 1:
            output_Lx = np.expand_dims(output_Lx, axis=0)

        np.savetxt(os.path.join(path,"tmp_output/I"+str(layer)+".txt"), input_Lx, fmt="%d")
        np.savetxt(os.path.join(path,"tmp_output/EL"+str(layer)+".txt"), output_expected_Lx, fmt="%d")
        np.savetxt(os.path.join(path,"tmp_output/L"+str(layer)+".txt"), output_Lx, fmt="%d")
        
        error = output_Lx - output_expected_Lx
        error2 = output_Lx2 - output_expected_Lx

        ELx = output_expected_Lx.flatten()
        Lx = output_Lx.flatten()
        Lx2 = output_Lx2.flatten()
        p = np.poly1d(np.polyfit(ELx, Lx, deg=1))
        p2 = np.poly1d(np.polyfit(ELx, Lx2, deg=1))

        col_num = np.shape(output_Lx)[1]
        coff = np.zeros((col_num, 2))
        for col in range(0, col_num, 1):
            try:
                fit = np.polyfit(output_expected_Lx[:,col], output_Lx[:,col], deg=1)
                coff[col, :] = np.poly1d(fit)
            except np.linalg.LinAlgError:
                coff[col, :] = 0

        cs_overall = cosine_similarity(np.reshape(output_Lx, (1, -1)), np.reshape(output_expected_Lx, (1, -1)))[0, 0]
        cs_frame = [cosine_similarity(np.reshape(output_Lx[i, :], (1, -1)), np.reshape(output_expected_Lx[i, :], (1, -1)))[0, 0] for i in range(row)]
        cs_output = [cosine_similarity(np.reshape(output_Lx[:, i], (1, -1)), np.reshape(output_expected_Lx[:, i], (1, -1)))[0, 0] for i in range(xe-xs+1)]

        cs_overall_2 = cosine_similarity(np.reshape(output_Lx2, (1, -1)), np.reshape(output_expected_Lx, (1, -1)))[0, 0]
        cs_frame_2 = [cosine_similarity(np.reshape(output_Lx2[i, :], (1, -1)), np.reshape(output_expected_Lx[i, :], (1, -1)))[0, 0] for i in range(row)]
        cs_output_2 = [cosine_similarity(np.reshape(output_Lx2[:, i], (1, -1)), np.reshape(output_expected_Lx[:, i], (1, -1)))[0, 0] for i in range(xe-xs+1)]

        fig1, [[ax1, ax3, ax5], [ax2, ax4, ax6], [ax7, ax8, ax9]] = plt.subplots(3, 3, figsize=(16, 9))
        #fig1.tight_layout()
        ax1.plot(output_Lx[index,:], 'r.', label='chip output')
        ax1.plot(output_expected_Lx[index,:], label='expected output')
        ax1.set_xlabel('layer output index')
        ax1.set_ylabel('layer output value')
        #ax1.legend()
        
        ax2.plot(error[index,:], '.', label='error std = %.2f / %.2f (add diff)'%(np.std(error[index,:]), np.std(error2[index,:])))
        ax2.set_xlabel('layer output index')
        ax2.set_ylabel('output abs error')
        ax2.legend()

        ax3.plot(np.std(error, axis=1), 'b', label='%.2f'%(np.mean(np.std(error, axis=1))))
        ax3.plot(np.std(error2, axis=1), 'b.', label='%.2f'%(np.mean(np.std(error2, axis=1))))
        ax3.plot(np.mean(error, axis=1), 'r')
        ax3.plot(np.mean(error2, axis=1), 'r.')
        ax3.set_xlabel('input frame index')
        ax3.set_ylabel('error statistics')
        ax3.legend()

        ax4.plot(np.std(error, axis=0), 'b', label='%.2f'%(np.mean(np.std(error, axis=0))))
        ax4.plot(np.mean(error, axis=0), 'r', label='%.2f / %.2f'%(np.mean(np.mean(error, axis=0)), np.std(np.mean(error, axis=0))))
        ax4.set_xlabel('layer output index')
        ax4.set_ylabel('error statistics')
        ax4.legend()

        ax5.plot(cs_frame, 'b', label='%.3f'%(cs_overall))
        ax5.plot(cs_frame_2, 'r', label='%.3f (add diff)'%(cs_overall_2))
        ax5.set_xlabel('input frame index')
        ax5.set_ylabel('cosine similarity')
        ax5.legend()

        ax6.plot(cs_output, 'b', label='%.3f'%(cs_overall))
        ax6.plot(cs_output_2, 'r', label='%.3f (add diff)'%(cs_overall_2))
        ax6.set_xlabel('layer output index')
        ax6.set_ylabel('cosine similarity')
        ax6.legend()

        x = np.arange(-128, 128)
        ax7.plot(ELx, Lx, 'r.', label='std = %.3f'%(np.std(error[30:,:])))
        ax7.plot(x, p(x), 'b', label='y =' + str(p))
        ax7.plot(x, x, 'k')
        ax7.set_xlabel('expected output')
        ax7.set_ylabel('real output')
        ax7.legend()

        ax8.plot(coff[:, 0])
        ax8.set_xlabel('layer output index')
        ax8.set_ylabel('scale')

        ax9.plot(ELx, Lx2, 'r.', label='std = %.3f (add diff)'%(np.std(error2[30:,:])))
        ax9.plot(x, p2(x), 'b', label='y =' + str(p2) + '(add diff)')
        ax9.plot(x, x, 'k')
        ax9.set_xlabel('expected output')
        ax9.set_ylabel('real output')
        ax9.legend()

        plt.savefig(os.path.join(path,"result/layer"+str(layer)+".png"))


def main(argv):

    path = './'
    avg_num = 1

    try:
        opts, args = getopt.getopt(argv,"hd:k:")
    except getopt.GetoptError:
        print("infer.py -d <map_dir> -k <avg_num>")
        sys.exit()

    for opt, arg in opts:
        if opt == '-h':
            print("infer.py -d <map_dir> -k <avg_num>")
            sys.exit()
        elif opt in ("-d"):
            path = arg
        elif opt in ("-k"):
            avg_num = int(arg)

    if not os.path.exists(os.path.join(path, "tmp_output")):
        os.mkdir(os.path.join(path, "tmp_output"))
    if not os.path.exists(os.path.join(path, "result")):
        os.mkdir(os.path.join(path, "result"))
		
    infer_net(path, avg_num)

    #infer_round(path)

    plt.show()


if __name__ == '__main__':
    main(sys.argv[1:])