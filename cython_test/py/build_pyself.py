# -*- coding: utf-8 -*-
import marshal
code = open('testm.py').read();
obj = compile(code,'testm273p','exec');

# 新建一个文件来保存marshal字符串
out = open('testm273p.pyc','wb+');
marshal.dump(obj,out);
out.close();