/* example.i */
%module calculate_channel_mean_module
%{
#include "../calculate_channel_mean.h"

%}
%include "std_string.i"
%include "typemaps.i"
%include "stl.i"
%include "calculate_channel_mean.h"