#coding=utf-8
# 验证MD5算法的有效性
# 修改pwd为你的密码
# 修改EAP_id为md5-request的id
# 修改md5req为request包的md5请求序列
# 看看输出结果和你的inode输出结果是否已知
from hashlib import md5
from binascii import hexlify
pwd = '210010'
EAP_id = '\x02'
md5req = '\x9a\xfb\x0d\xa2\x6e\x68\x36\xc5\x9f\x56\x22\xd7\x1c\x60\xde\xf5'
my_md5 = md5(EAP_id+pwd+md5req).digest()
print hexlify(my_md5)
