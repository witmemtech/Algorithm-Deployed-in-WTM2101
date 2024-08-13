"""
audio_to_mfccs.get_mfcc 
python 源码
"""
# calculate filterbank features. Provides e.g. fbank and mfcc features for use in ASR applications
# Author: James Lyons 2012
import numpy
import numpy as np
from scipy.fftpack import dct
import decimal
import math
import logging

from scipy.fftpack import fft,ifft

import scipy.io.wavfile as wav
#import pylab as plt
#from dll_itf import *


def get_file_list(path,ext):
    f_dict = {}
    for (dirpath, dirnames, filenames) in os.walk(path):
        for filename in filenames:
            if filename.endswith(ext):
                filename_path = os.path.join(dirpath, filename)
                #files.append(filename_path)
                name,ext = os.path.splitext(filename)
                f_dict[name] = filename_path
                
    return f_dict

def load_phones_txt(file):
    phones_dict = {}
    f = open(file,"r",encoding="utf8")
    for line in f:
        line = line.strip()
        kv = line.split(" ")
        phone = str(kv[0])
        num = int(kv[1])
        phones_dict[num] = phone
    return phones_dict 

def get_text_dict(txt_path):
    f = open(txt_path,"r",encoding="utf8")
    txt_dict = {}
    for line in f:
        line = line.strip()
        if len(line) is 0:
            continue
        if line.startswith('#'):
            continue
        spltidx = line.index(" ")
        k = line[:spltidx]
        v = line[spltidx:]
        v = v.strip()
        txt_dict[k] = v
    f.close()
    return txt_dict	    

def hz2mel(hz):
    """Convert a value in Hertz to Mels.  Hz -- Mel

    :param hz: a value in Hz. This can also be a numpy array, conversion proceeds element-wise.
    :returns: a value in Mels. If an array was passed in, an identical sized array is returned.
    """
    return 2595 * numpy.log10(1+hz/700.)

def mel2hz(mel):
    """Convert a value in Mels to Hertz.  Mel -- Hz

    :param mel: a value in Mels. This can also be a numpy array, conversion proceeds element-wise.
    :returns: a value in Hertz. If an array was passed in, an identical sized array is returned.
    """
    return 700*(10**(mel/2595.0)-1)

def preemphasis(signal,coeff=0.95):
    """perform preemphasis on the input signal.  预加重

    :param signal: The signal to filter.
    :param coeff: The preemphasis coefficient. 0 is no filter, default is 0.95.
    :returns: the filtered signal.
    """
    return numpy.append(signal[0],signal[1:]-coeff*signal[:-1])

def round_half_up(number):
    return int(decimal.Decimal(number).quantize(decimal.Decimal('1'), rounding=decimal.ROUND_HALF_UP))


def framesig(sig,frame_len,frame_step):
    """Frame a signal into overlapping frames.

    :param sig: the audio signal to frame.
    :param frame_len: length of each frame measured in samples.
    :param frame_step: number of samples after the start of the previous frame that the next frame should begin.
    :returns: an array of frames. Size is NUMFRAMES by frame_len.
    """
    slen = len(sig)
    frame_len = int(round_half_up(frame_len))
    frame_step = int(round_half_up(frame_step))
    if slen <= frame_len:
        numframes = 1
    else:
        numframes = 1 + int(math.ceil((1.0*slen - frame_len)/frame_step))

    padlen = int((numframes-1)*frame_step + frame_len)

    zeros = numpy.zeros((padlen - slen,))
    padsignal = numpy.concatenate((sig,zeros))

    indices = numpy.tile(numpy.arange(0,frame_len),(numframes,1)) + numpy.tile(numpy.arange(0,numframes*frame_step,frame_step),(frame_len,1)).T
    indices = numpy.array(indices,dtype=numpy.int32)
    frames = padsignal[indices]

    return frames,frame_len,numframes

def magspec(frames,NFFT):
    """Compute the magnitude spectrum of each frame in frames. If frames is an NxD matrix, output will be Nx(NFFT/2+1).  计算每帧的幅度谱

    :param frames: the array of frames. Each row is a frame.
    :param NFFT: the FFT length to use. If NFFT > frame_len, the frames are zero-padded.
    :returns: If frames is an NxD matrix, output will be Nx(NFFT/2+1). Each row will be the magnitude spectrum of the corresponding frame.
    """
    if numpy.shape(frames)[1] > NFFT:
        logging.warn('frame length (%d) is greater than FFT size (%d), frame will be truncated. Increase NFFT to avoid.', numpy.shape(frames)[1], NFFT)
    complex_spec = numpy.fft.rfft(frames,NFFT) # complex_spec Q15
    #complex_spec_Q6 = complex_spec/512
    #print(complex_spec)
    x = numpy.absolute(complex_spec) # x Q15
    #res = x*x # res Q30
    #res_Q12 = res/ 262144 #2^18
    #return numpy.absolute(complex_spec)
    #return res
    return x

def powspec(frames,NFFT):
    """Compute the power spectrum of each frame in frames. If frames is an NxD matrix, output will be Nx(NFFT/2+1). 计算每帧的功率谱  

    :param frames: the array of frames. Each row is a frame.
    :param NFFT: the FFT length to use. If NFFT > frame_len, the frames are zero-padded.
    :returns: If frames is an NxD matrix, output will be Nx(NFFT/2+1). Each row will be the power spectrum of the corresponding frame.
    """
    return 1.0/NFFT * numpy.square(magspec(frames,NFFT))

def get_filterbanks(nfilt=20,nfft=512,samplerate=16000,lowfreq=0,highfreq=None):
    """Compute a Mel-filterbank. The filters are stored in the rows, the columns correspond
    to fft bins. The filters are returned as an array of size nfilt * (nfft/2 + 1)  计算梅尔滤波器组

    :param nfilt: the number of filters in the filterbank, default 20.
    :param nfft: the FFT size. Default is 512.
    :param samplerate: the samplerate of the signal we are working with. Affects mel spacing.
    :param lowfreq: lowest band edge of mel filters, default 0 Hz
    :param highfreq: highest band edge of mel filters, default samplerate/2
    :returns: A numpy array of size nfilt * (nfft/2 + 1) containing filterbank. Each row holds 1 filter.
    """
    highfreq= highfreq or samplerate/2
    assert highfreq <= samplerate/2, "highfreq is greater than samplerate/2"

    # compute points evenly spaced in mels
    lowmel = hz2mel(lowfreq)  # Hz -- Mel
    highmel = hz2mel(highfreq)
    melpoints = numpy.linspace(lowmel,highmel,nfilt+2)

    # our points are in Hz, but we use fft bins, so we have to convert
    #  from Hz to fft bin number
    bin = numpy.floor((nfft+1)*mel2hz(melpoints)/samplerate)

    fbank = numpy.zeros([nfilt,nfft//2+1])
    
    for j in range(0,nfilt):
        for i in range(int(bin[j]), int(bin[j+1])):
            fbank[j,i] = (i - bin[j]) / (bin[j+1]-bin[j])
        for i in range(int(bin[j+1]), int(bin[j+2])):
            fbank[j,i] = (bin[j+2]-i) / (bin[j+2]-bin[j+1])
    
    return fbank

def get_filterbanks_kaldi(nfilt=20,nfft=512,samplerate=16000,lowfreq=0,highfreq=None):
    
    highfreq= highfreq or samplerate/2
    assert highfreq <= samplerate/2, "highfreq is greater than samplerate/2"

    # compute points evenly spaced in mels
    lowmel = hz2mel(lowfreq)  # Hz -- Mel
    highmel = hz2mel(highfreq)
    melpoints = numpy.linspace(lowmel,highmel,nfilt+2)
    
    # kaldi采用以下这种方法来得到mel滤波器组。
    mfbank = numpy.zeros([nfilt,nfft//2+1])
    mel_delta = (highmel - lowmel)/(nfilt+1)
    for j in range(0,nfilt):
        mleft = melpoints[j]
        mcenter = melpoints[j+1]
        mright = melpoints[j+2]
        for i in range(0,nfft//2+1):
            hz = i*(samplerate)/nfft
            mel = hz2mel(hz)
            weight = 0
            if mleft <=mel and mel <=mcenter:
                weight = (mel - mleft) /(mcenter - mleft)
            elif  mcenter <=mel and mel <=mright: 
                weight = (mright - mel) /(mright - mcenter)
            mfbank[j,i] = weight
    return mfbank

def get_filterbanks_other(nfilt=20,nfft=512,samplerate=16000,lowfreq=0,highfreq=None):
    fs = 8000
    fl = 0
    fh = fs/2
    bl = 1125*np.log(1+fl/700) # 把 Hz 变成 Mel
    bh = 1125*np.log(1+fh/700)
    p = nfilt
    NFFT=nfft
    B = bh-bl
    y = np.linspace(0,B,p+2)# 将梅尔刻度等间隔
    #print(y)
    Fb = 700*(np.exp(y/1125)-1)# 把 Mel 变成 Hz
    #print(Fb)
    W2 = int(NFFT / 2 + 1)
    df = fs/NFFT
    freq = []#采样频率值
    for n in range(0,W2):
        freqs = int(n*df)
        freq.append(freqs)
    bank = np.zeros((nfilt,W2))
    for k in range(1,p+1):
        f1 = Fb[k-1]
        f2 = Fb[k+1]
        f0 = Fb[k]
        n1=np.floor(f1/df)
        n2=np.floor(f2/df)
        n0=np.floor(f0/df)
        for i in range(1,W2):
            if i>=n1 and i<=n0:
                bank[k-1,i]=(i-n1)/(n0-n1)
            elif i>n0 and i<=n2:
                bank[k-1,i]=(n2-i)/(n2-n0)
        # print(k)
        # print(bank[k-1,:])
        #plt.plot(freq,bank[k-1,:],'r')
        #plt.plot(bank[k-1,:],'r')
    #plt.show()
    return bank

def lifter(cepstra, L=22):
    """Apply a cepstral lifter the the matrix of cepstra. This has the effect of increasing the
    magnitude of the high frequency DCT coeffs.  应用倒谱提升器倒谱矩阵。这会增加高频离散余弦变换系数的大小。

    :param cepstra: the matrix of mel-cepstra, will be numframes * numcep in size.
    :param L: the liftering coefficient to use. Default is 22. L <= 0 disables lifter.
    """
    if L > 0:
        nframes,ncoeff = numpy.shape(cepstra)
        n = numpy.arange(ncoeff)
        lift = 1 + (L/2.)*numpy.sin(numpy.pi*n/L)
        return lift*cepstra
    else:
        # values of L <= 0, do nothing
        return cepstra

def povey(M):
    if M < 1:
        return numpy.array([])
    if M == 1:
        return numpy.ones(1, float)
    n = numpy.arange(0, M)
    haming = 0.5 - 0.5*numpy.cos(2.0*numpy.pi*n/(M-1))
    return pow(haming,0.85)

def fbank(signal,samplerate=16000,winlen=0.025,winstep=0.01,
          nfilt=26,nfft=512,lowfreq=0,highfreq=None,preemph=0.97,
          winfunc=lambda x:numpy.ones((x,)),remove_dc_offset=False):
    """Compute Mel-filterbank energy features from an audio signal.

    :param signal: the audio signal from which to compute features. Should be an N*1 array
    :param samplerate: the samplerate of the signal we are working with.
    :param winlen: the length of the analysis window in seconds. Default is 0.025s (25 milliseconds)
    :param winstep: the step between successive windows in seconds. Default is 0.01s (10 milliseconds)
    :param nfilt: the number of filters in the filterbank, default 26.
    :param nfft: the FFT size. Default is 512.
    :param lowfreq: lowest band edge of mel filters. In Hz, default is 0.
    :param highfreq: highest band edge of mel filters. In Hz, default is samplerate/2
    :param preemph: apply preemphasis filter with preemph as coefficient. 0 is no filter. Default is 0.97.
    :param winfunc: the analysis window to apply to each frame. By default no window is applied. You can use numpy window functions here e.g. winfunc=numpy.hamming
    :returns: 2 values. The first is a numpy array of size (NUMFRAMES by nfilt) containing features. Each row holds 1 feature vector. The
        second return value is the energy in each frame (total energy, unwindowed)
    """
    highfreq= highfreq or samplerate/2

    #分帧
    frames,frame_len,numframes = framesig(signal, winlen*samplerate, winstep*samplerate)
    #预加重
    frames_ = []
    for f in frames:
        if remove_dc_offset:
            f_mean=np.mean(f)
            f = f - f_mean
        tmp = preemphasis(f,preemph)
        frames_.append(tmp)
    #窗函数    
    win = numpy.tile(winfunc(frame_len),(numframes,1))
    frames = frames_*win
    pspec = magspec(frames,nfft) #power[Q30] magnitude[Q15]
    energy = numpy.sum(pspec,1) # this stores the total energy in each frame
    energy = numpy.where(energy == 0,numpy.finfo(float).eps,energy) # if energy is zero, we get problems with log

    fb = get_filterbanks_kaldi(nfilt,nfft,samplerate,lowfreq,highfreq)
    feat = numpy.dot(pspec,fb.T) # compute the filterbank energies power[Q30] magnitude[Q15]
    #feat = numpy.where(feat == 0,numpy.finfo(float).eps,feat) # if feat is zero, we get problems with log
    feat = numpy.where(feat <= 1,1,feat) # if feat is zero, we get problems with log
    return feat,energy

def mfcc(signal,samplerate=16000,winlen=0.025,winstep=0.01,numcep=13,
         nfilt=26,nfft=512,lowfreq=0,highfreq=None,preemph=0.97,ceplifter=22,appendEnergy=True,
         winfunc=lambda x:numpy.ones((x,))):
    """Compute MFCC features from an audio signal.  计算mfcc特征

    :param signal: the audio signal from which to compute features. Should be an N*1 array
    :param samplerate: the samplerate of the signal we are working with.
    :param winlen: the length of the analysis window in seconds. Default is 0.025s (25 milliseconds)
    :param winstep: the step between successive windows in seconds. Default is 0.01s (10 milliseconds)
    :param numcep: the number of cepstrum to return, default 13
    :param nfilt: the number of filters in the filterbank, default 26.
    :param nfft: the FFT size. Default is 512.
    :param lowfreq: lowest band edge of mel filters. In Hz, default is 0.
    :param highfreq: highest band edge of mel filters. In Hz, default is samplerate/2
    :param preemph: apply preemphasis filter with preemph as coefficient. 0 is no filter. Default is 0.97.
    :param ceplifter: apply a lifter to final cepstral coefficients. 0 is no lifter. Default is 22.
    :param appendEnergy: if this is true, the zeroth cepstral coefficient is replaced with the log of the total frame energy.
    :param winfunc: the analysis window to apply to each frame. By default no window is applied. You can use numpy window functions here e.g. winfunc=numpy.hamming
    要应用于每个帧的分析窗口。默认情况下不应用任何窗口。您可以在这里使用numpy窗口函数，例如winfunc=numpy.hamming
    :returns: A numpy array of size (NUMFRAMES by numcep) containing features. Each row holds 1 feature vector.
    """
    feat,energy = fbank(signal,samplerate,winlen,winstep,nfilt,nfft,lowfreq,highfreq,preemph,winfunc)
    feat = numpy.log(feat)
    feat = dct(feat, type=2, axis=1, norm='ortho')[:,:numcep]
    feat = lifter(feat,ceplifter)
    if appendEnergy: feat[:,0] = numpy.log(energy) # replace first cepstral coefficient with log of frame energy
    return feat


def logfbank(signal,samplerate=16000,winlen=0.025,winstep=0.05,
          nfilt=26,nfft=512,lowfreq=0,highfreq=None,preemph=0.97):
    """Compute log Mel-filterbank energy features from an audio signal.  计算log-fbank特征

    :param signal: the audio signal from which to compute features. Should be an N*1 array
    :param samplerate: the samplerate of the signal we are working with.
    :param winlen: the length of the analysis window in seconds. Default is 0.025s (25 milliseconds)
    :param winstep: the step between successive windows in seconds. Default is 0.01s (10 milliseconds)
    :param nfilt: the number of filters in the filterbank, default 26.
    :param nfft: the FFT size. Default is 512.
    :param lowfreq: lowest band edge of mel filters. In Hz, default is 0.
    :param highfreq: highest band edge of mel filters. In Hz, default is samplerate/2
    :param preemph: apply preemphasis filter with preemph as coefficient. 0 is no filter. Default is 0.97.
    :returns: A numpy array of size (NUMFRAMES by nfilt) containing features. Each row holds 1 feature vector.
    """
    feat,energy = fbank(signal,samplerate,winlen,winstep,nfilt,nfft,lowfreq,highfreq,preemph,winfunc=povey)#,winfunc= numpy.hamming)
    return numpy.log(feat)

def get_fbank(waveform):
    # fs, audio = wav.read(fn)
    out = logfbank(waveform,nfilt=40,lowfreq=20)
    fb = numpy.rint(out*8)
    return fb

def get_fbank_4_frame(frames):
    out = logfbank(frames,nfilt=40,lowfreq=20)
    return numpy.rint(out*8)

def apply_cmvn(feat,cmvn_file):
    cmvn = np.loadtxt(cmvn_file,dtype=np.float32)
    
    sp = np.shape(cmvn)
    assert np.shape(cmvn)[0] == 2
    
    mean = cmvn[0]
    count = mean[-1]
    mean = np.delete(mean,-1)
    mean = -mean/count
    feat_ok = feat + mean
    feat_ok_mean = np.mean(feat_ok);
    feat_ok_var = np.var(feat_ok);
    return feat_ok

def mk_ark_t(k,fn_wav,fn_ark):
    feat = get_fbank(fn_wav)
    fn_ark.write("%s  [\n"%k)
    np.savetxt(fn_ark,feat,fmt="%d")
    fn_ark.write("]\n")


def test_feature_tools():
    audio_u16 = [2914,4961,1740,2976,2806,2119,-367,260,-82,-826,-2523,-2224,-3047,-3154,-4142,-4608,-4234,-1059,2129,-2716,-6216,-7663,-640,327,-1715,-3456,-1885,-1058,-916,2411,4306,3131,2617,4747,5026,4147,3403,5125,7624,6741,3748,2486,5955,7638,6773,4907,5944,5719,4096,2969,4654,3862,1441,594,2211,1417,-2128,-1758,388,457,-885,-2484,-1933,-2427,-2982,-3389,-3142,-5565,-5915,-7270,-6177,-7753,-8678,-8996,-8747,-10941,-7314,-4574,-8844,-12791,-11932,-5200,-4355,-5713,-7065,-6471,-5640,-5064,-2108,-282,-867,-1896,-448,835,1527,-728,1701,5666,5640,1033,-239,5562,6036,4232,2745,4018,3366,1192,767,2907,1401,-841,-359,1325,-867,-3156,-2008,1176,1503,-1749,-3549,-2296,-1756,-2929,-3873,-3343,-4262,-5630,-6397,-4727,-5833,-5233,-7339,-6127,-9270,-4179,-2893,-6066,-10502,-8855,-1364,-1607,-3839,-5821,-2718,-1339,-147,1960,2988,1543,2178,4627,5692,4619,1815,6387,9051,8079,3641,4944,9085,9296,7364,7010,8462,7444,6461,6381,7998,5726,4208,3919,5687,3843,2341,4050,6069,4389,1083,1876,3896,3778,1577,1016,1644,-140,-1939,-2251,-1996,-2806,-3717,-4458,-5433,-6980,180,-2383,-7009,-10603,-5114,-1037,-3473,-5271,-5494,-2676,-2399,-1161,-116,263,-286,1941,3010,2371,809,680,5089,6626,5579,2559,6049,7714,6846,4467,5193,6750,5891,3661,4398,4976,2905,1360,1677,3049,1198,687,1900,2491,-30,-2271,94,215,-906,-3209,-2336,-3455,-4271,-6334,-4266,-5516,-6835,-8558,-8574,-10251,-5684,-2567,-8050,-11438,-11496,-3907,-4265,-6087,-7281,-5221,-3778,-3037,-566,55,-549,166,3276,2769,2598,1706,4457,6818,6296,2898,2583,8143,7185,5268,4013,6601,5748,3495,2264,3411,2141,799,205,1444,723,-1074,-359,524,55,-2869,-3990,-1920,-1825,-4096,-5911,-5015,-5627,-6227,-7045,-5927,-8005,-8057,-9802,-8168,-10014,-3262,-4857,-8844,-12338,-9196,-2098,-3213,-4539,-5390,-2127,-2254,-1881,444,2762,2725,3714,5106,5090,4982,2810,8636,10717,9486,4544,7664,10839,9843,7840,9381,11028,8917,6289,7175,9009,7183,6290,6162,7286,5479,3730,4600,6570,5555,2064,3145,3822,2696,-306,143,959,503,-1836,-1491,-1283,-2538,-4680,-3683,-5610,-2971,2229,-5220,-8002,-10589,-662,-716,-3147,-4502,-3123,-1069,-2018,507,2243,1672,879,3489,3458,3540,1561,4270,8008,6406,3691,1427,8092,8564,7079,5219,6479,5913,4548,2156,4082,3623,1739,732,1692,1306,-1801,-1522,470,1395,-1725,-3941,-1173,-1402,-3142,-4678,-4013,-5530,-6326,-7932,-5953,-8565,-8962,-11361,-8459,-11809,-6917,-3205,-9818,-12624,-14564,-3964,-4413,-6209,-9296,-6460,-4504,-4798,-2201,249,497,-411,1482,805,2087,93,4354,8013,7784,2922,1756,7596,7525,5657,2935,5225,4219,2052,191,3584,2691,876,-1139,714,1,-2740,-1752,664,818,-4036,-5654,-3696,-2644,-4388,-4509,-2729,-3887,-5286,-6522,-3849,-6634,-5597,-8139,-5895,-9071,-2762,-1600,-7687,-9775,-8268,1173,-838,-2364,-4839,-971,488,1114,2620,4309,3931,2970,4643,4772,5879,3034,7691,9927,9302,4205,6517,11761,10597,8039,6958,9515,8156,6358,5695,8902,6750,4669,3864,5666,4076,2391,3525,5839,4672,521,864,2715,2423,-161,-22,592,-600,-2478,-3145,-2149,-4640,-5092,-7523,-5675,-9200,-987,-3211,-7646,-11453,-8787,-212,-1543,-3431,-6497,-2930,-2789,-1796,-1179,725,-176,946,1482,2422,2419,623,6278,8165,7088,2506,4312,8012,6911,3808,4621,6678,4876,2266,2686,5578,3780,1786,1415,3784,994,-760,-605,1530,150,-2627,-2009,-398,-1106,-3149,-1799,-1042,-3652,-5270,-5159,-4128,-5743,-7614,-8705,-7688,-10882,-3950,-6912,-10571,-14295,-10003,-2179,-3969,-5805,-8893,-4496,-4613,-4256,-1694,-147,-1524,148,682,1143,703,210,5492,6135,4998,647,4171,6849,6308,4176,4559,5754,3821,2007,2494,5218,3662,1994,879,2143,-291,-1124,-766,1998,330,-2559,-2323,-708,-1971,-3881,-2784,-2272,-4785,-7076,-6329,-5982,-7319,-8976,-8396,-7490,-11097,-3066,-5123,-7581,-12475,-8472,-425,-2944,-5031,-7346,-2535,-2195,-2397,-31,1951,1338,2323,2851,5255,4777,3570,9117,11468,9358,3031,6240,11012,10915,7912,8599,10703,8186,5554,6792,9888,7717,5720,4748,7220,3672,1885,2981,6057,3225,148,640,3147,2562,615,1376,1945,-528,-2338,-2818,-2108,-5006,-4537,-7484,-5748,-8644,-2676,-1756,-7252,-9449,-9049,530,-2085,-4088,-7225,-3596,-2046,-2318,-697,1563,519,79,2583,4116,4930,2167,6480,8599,7181,2066,4709,10312,8995,6604,6958,9700,6997,5222,5162,7448,4597,2709,1859,3501,1335,-560,317,2997,918,-2771,-2240,-135,-858,-3175,-2951,-3408,-5612,-7474,-7873,-6917,-8798,-9686,-12296,-10225,-14906,-7924,-5788,-10960,-15179,-15775,-5528,-5782,-8195,-11566,-7658,-5909,-6483,-5134,-1915,-1782,-1523,36,1628,2317,-856,4604,6945,6161,785,1795,7185,7406,4242,3954,7506,6779,4158,3942,7049,4862,3287,1759,4164,2773,173,389,3613,2886,131,219,2493,2216,-263,16,734,-1709,-4078,-2812,-1408,-3766,-5508,-8185,-4920,-9078,-3207,-722,-4958,-9078,-10713,-1187,-736,-2800,-6236,-2899,-773,-1439,-679,3243,4364,4123,4798,5919,6500,2949,7375,11338,12531,7720,7047,11678,11569,9279,7876,10931,10530,6998,5734,8478,7663,5464,4097,6484,4465,984,1447,5022,5412,1947,573,1920,1641,-555,-1584,-636,-2374,-4615,-5453,-4984,-6514,-8138,-9796,-6519,-10254,-8207,-3127,-6329,-10367,-14780,-4660,-1377,-3743,-7392,-6042,-3202,-3535,-1858,1193,2492,1600,2563,4053,4469,1068,4262,9185,10803,6560,4333,9387,9974,8292,7543,10050,9443,6168,3687,5761,6389,4159,2120,3422,2270,-1233,-1154,2307,2845,-695,-2288,-898,-1482,-4209,-4138,-2970,-3884,-6681,-8238,-8443,-9983,-10408,-12150,-9923,-14412,-11691];
    #audio_u16 = [30,97,-12,50,-37,17,-73,-37,-62,-84,-49,-85,-51,-43,-41,-41,-1,-24,4,-33,12,-28,-39,-10,-84,-35,-83,-125,-63,-137,-140,-72,-145,-96,-54,-96,9,-15,-5,57,9,55,67,63,95,92,111,103,185,82,207,154,111,199,68,116,115,-19,134,-49,44,15,-51,58,-12,0,84,32,72,91,60,84,47,17,51,-46,-59,2,-171,-49,-99,-139,-71,-51,-158,21,-68,-46,31,-21,-18,69,-73,80,-37,1,43,-49,57,-30,22,1,-10,22,-20,-20,34,-71,28,-43,-23,-33,-37,-38,-17,-81,1,-76,-38,-9,-84,71,-57,89,55,47,146,97,102,150,102,69,160,0,104,20,41,28,2,93,0,77,60,75,22,128,-21,49,-6,-124,-1,-181,-95,-94,-151,-115,-8,-201,-8,-54,-139,4,-98,-94,-37,-89,-109,17,-108,-28,61,-70,54,62,22,69,80,78,57,147,29,115,65,42,44,17,18,1,-5,37,-12,93,68,69,173,43,133,85,15,18,-28,-85,-72,-71,-95,-82,5,-72,50,19,75,54,98,107,56,129,37,101,43,56,-4,56,-42,-38,50,-111,4,6,-104,25,-71,-49,-66,-120,-80,-185,-152,-165,-171,-173,-103,-123,-90,-16,-59,26,-59,37,-78,-34,-30,-108,-31,-61,-28,-67,37,-52,14,-28,-10,-17,-72,-11,-44,-117,10,-66,-111,39,-129,9,-76,-24,-50,-16,0,-29,88,-3,129,50,114,90,88,98,74,58,93,20,82,88,55,144,69,159,130,140,165,206,137,227,173,174,163,156,68,120,27,-29,61,-123,31,-124,24,-115,2,-36,-55,0,-64,-21,-69,-17,-88,4,-93,33,-99,-5,-19,-116,-18,-95,-93,-66,-95,-66,-59,-41,-19,-40,34,-33,-30,36,-79,-29,-36,-102,-23,-85,-85,-30,-91,-74,-44,-62,-82,31,-69,43,25,19,78,-20,79,-38,-8,-19,-69,-49,-76,-43,-39,-70,54,-58,60,29,41,78,49,27,95,20,55,125,5,134,85,56,102,62,1,42,14,-53,4,-33,]
    #out = logfbank(audio_u16,nfilt=40,lowfreq=20)
    #res = numpy.rint(out*16)
    res = get_fbank_4_frame(audio_u16)
    print(res)

def get_wav_frames(file,winlen=0.025,winstep=0.01):
    fs, audio = wav.read(file)
    samplerate=16000    
    frames,frame_len,numframes = framesig(audio, winlen*samplerate, winstep*samplerate)
    return frames,frame_len,numframes

if __name__ == '__main__':
    audio_filename = '14_3466_20170826171159.wav'
    fs, audio = wav.read(audio_filename)
    out = logfbank(audio,nfilt=40,lowfreq=20)#,winlen=0.032)
    fb = numpy.rint(out*8)
    print("pause")
    #fbs = get_fbank(audio_filename)
    #test_feature_tools()
    #create_ark_txt_for_path("tmp/","tmp/fbtxt/")
    