#! /bin/bash
python synAES.py --en 0 ALL >& aes-dis.log
python synAES.py --en 1 ALL >& aes-en.log
python synAESuinst.py --en 1 >& aes-uinst-en.log
python synAESuinst.py --en 0 >& aes-uinst-dis.log
