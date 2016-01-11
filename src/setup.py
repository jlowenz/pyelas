from distutils.core import setup, Extension
from distutils.sysconfig import get_config_vars
import numpy
import os

(opt,) = get_config_vars('OPT')
os.environ['OPT'] = " ".join(
    flag for flag in opt.split() if flag != '-Wstrict-prototypes'
)

setup(name="pyelas",
      version="0.1.0",
      py_modules=["elas"],
      ext_modules=[Extension("_elas",
                             sources=["descriptor.cpp", "elas.cpp", "filter.cpp", "matrix.cpp", "triangle.cpp", 
                                      "ccomp.cpp", "elas.i"],
                             language="c++",
                             swig_opts=['-c++','-threads'],
                             extra_compile_args=['-msse3','-g'],
                             include_dirs=[numpy.get_include()])])
