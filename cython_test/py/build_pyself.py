# -*- coding: utf-8 -*-
import marshal

# without extension
def compilePyFile(filename):
    code = open(filename+'.py').read();
    obj = compile(code,filename,'exec');
    # 新建一个文件来保存marshal字符串
    out = open(filename+'.pyc','wb+');
    marshal.dump(obj,out);
    out.close();

print('Building...');

compilePyFile('./py/pyopcode');
compilePyFile('./py/pyopcode_withdivision');

print('Build Over!');