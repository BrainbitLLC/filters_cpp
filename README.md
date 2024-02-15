# Filters SDK
## Description
It is a cross-platform library that allows you to filter the signal with a given set of filters for a specified sampling rate.

The library provides built-in filters of the following types:
1. high pass - high pass filter (HPF). Cuts off all frequencies below the filter pass frequency
2. low pass - low pass filter (LPF). Cuts off all frequencies above filter pass frequency.
3. band pass - bandpass filter. Passes a certain bandwidth
4. band stop is a band reject filter. Suppresses a certain band.

Digital signal processing involves the formation of the necessary bandwidth and suppression of network interference. The bandwidth is formed by sequential application of VFD and LPF filters. The HPF removes the constant component of the signal and the drift of the isoline, attracting the signal to 0. The LPF removes high-frequency noise from the signal. Mains interference caused by mains interference usually has the frequency of the mains itself - 50 Hz for Russia and CIS countries and 60 Hz for America and some other countries. Mains interference often has a very high amplitude signal and even when outside the signal bandwidth it still gives significant distortion, which leads to the need to suppress it with regenerative filters.

Maximum available signal bandwidth directly depends on sampling frequency and according to Nyquest law does not exceed half of sampling frequency. In practice, usually guided by the rule - Fh=Fd/4. Thus, if we have a sampling frequency of 1000 Hz, the maximum signal frequency will be 250 Hz. This value can be pushed higher, up to 400 Hz, but the higher the frequency, the lower the accuracy of the signal transmission will be.

Thus, a typical signal processing chain is the use of LPF, LPF and the required number of notch filters. The order in which the filters are applied does not matter.

> Each filter has a set of internal coefficients, which are recalculated after each new sample of the signal. This means that you cannot use the same instance of the filter class to process multiple signals at once. The rule 1 filter - 1 signal works here.

## Install

### Windows (cpp)

Download from [GitHub](https://github.com/BrainbitLLC/filters_cpp) and add .dll from folder `windows` to your project by your preferred way.

### Linux (cpp)

Download from [GitHub](https://github.com/BrainbitLLC/filters_cpp) and add .so from folder `linux_x86_64` to your project by your preferred way.

Library buit on Astra Linux CE 2.12.46, kernel 5.15.0-70-generic. Arch: x86_64 GNU/Linux

```
user@astra:~$ ldd --version
ldd (Debian GLIBC 2.28-10+deb10u1) 2.28
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
Written by Roland McGrath and Ulrich Drepper.
```

That library depends from others library, for instance:
```
linux-vdso.so.1
libblkid.so.1
libc++.so.1
libc++abi.so.1 
libc.so.6
libdl.so.2
libffi.so.6
libgcc_s.so.1
libgio-2.0.so.0
libglib-2.0.so.0
libgmodule-2.0.so.0
libgobject-2.0.so.0
libm.so.6
libmount.so.1
libpcre.so.3
libpthread.so.0
libresolv.so.2 
librt.so.1
libselinux.so.1
libstdc++.so.6
libudev.so.1
libuuid.so.1
libz.so.1
ld-linux-x86-64.so.2
```

If you are using a OS other than ours, these dependencies will be required for the library. You can download dependencies from [here](https://github.com/BrainbitLLC/linux_neurosdk2/tree/main/dependencies).

## Types
#### FilterType
Type of filter, enum with values:
1. FtHP - high pass filter
2. FtLP - low pass filter
3. FtBandStop - band stop filter
4. FtBandPass - band pass filter
5. FtNone - default value, type not set

#### FilterParam
Parameters of filter, structure with fields:
1. type - type of filter
2. samplingFreq - sampling frequency of raw signal, integer value
3. cutoffFreq - central frequency, double value
## Preinstalled filters
Library contains a list of some filters. The full list you can get with functions:

```cpp
TOpStatus error;
int fcount = 0;
get_preinstalled_filter_count(&fcount, &error);

FilterParam* preinstallFilters = new FilterParam[fcount];
get_preinstalled_filter_list(preinstallFilters, &error);
```

## Initialization
For work with filter you need to create a `Filter` object and optionally `FilterList` object. The `FilterList` contains objects of the `Filter` type and manipulates them.

```cpp
TOpStatus error;
// creating filter
FilterParam param;
param.type = FtBandStop;
param.samplingFreq = 250;
param.cutoffFreq = 50.0f;
TFilter* filter = create_TFilter_by_param(param, &error);

// then create list of filters
TFilterList* flist = create_TFilterList(&error);

// and add the filter
TFilterList_AddFilter(flist, filter, &error);
```

## Work with library

Filter one value:
```cpp
TOpStatus error;
// by one filter
double sample = SAMPLE;
double filteredValue = TFilter_Filter(filter, sample, &error);

// by list of filters
double sample = SAMPLE;
double filteredValue = TFilterList_Filter(flist, sample, &error);
```

Filter array of values:
```cpp
TOpStatus error;
// by one filter
double samples[max_samples];
TFilterList_Filter_array(filter, samples, max_samples, &error);

// by list of filters
double samples[max_samples];
TFilterList_Filter_array(flist, samples, max_samples, &error);
```

## Finishing work with the library
```cpp
TOpStatus error;
// removing filters
delete_TFilter(filter, &error);

// removing list of filters
delete_TFilterList(flist, &error);
```