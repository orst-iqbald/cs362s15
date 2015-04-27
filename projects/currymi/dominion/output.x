gcc -c dominion.c -g  -Wall -fpic -coverage -lm
In file included from /usr/include/stdio.h:34,
                 from dominion.c:5:
/usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stddef.h:211: error: storage class specified for parameter ‘size_t’
In file included from /usr/include/stdio.h:36,
                 from dominion.c:5:
/usr/include/bits/types.h:31: error: storage class specified for parameter ‘__u_char’
/usr/include/bits/types.h:32: error: storage class specified for parameter ‘__u_short’
/usr/include/bits/types.h:33: error: storage class specified for parameter ‘__u_int’
/usr/include/bits/types.h:34: error: storage class specified for parameter ‘__u_long’
/usr/include/bits/types.h:37: error: storage class specified for parameter ‘__int8_t’
/usr/include/bits/types.h:38: error: storage class specified for parameter ‘__uint8_t’
/usr/include/bits/types.h:39: error: storage class specified for parameter ‘__int16_t’
/usr/include/bits/types.h:40: error: storage class specified for parameter ‘__uint16_t’
/usr/include/bits/types.h:41: error: storage class specified for parameter ‘__int32_t’
/usr/include/bits/types.h:42: error: storage class specified for parameter ‘__uint32_t’
/usr/include/bits/types.h:44: error: storage class specified for parameter ‘__int64_t’
/usr/include/bits/types.h:45: error: storage class specified for parameter ‘__uint64_t’
/usr/include/bits/types.h:53: error: storage class specified for parameter ‘__quad_t’
/usr/include/bits/types.h:54: error: storage class specified for parameter ‘__u_quad_t’
In file included from /usr/include/stdio.h:36,
                 from dominion.c:5:
/usr/include/bits/types.h:134: error: storage class specified for parameter ‘__dev_t’
/usr/include/bits/types.h:135: error: storage class specified for parameter ‘__uid_t’
/usr/include/bits/types.h:136: error: storage class specified for parameter ‘__gid_t’
/usr/include/bits/types.h:137: error: storage class specified for parameter ‘__ino_t’
/usr/include/bits/types.h:138: error: storage class specified for parameter ‘__ino64_t’
/usr/include/bits/types.h:139: error: storage class specified for parameter ‘__mode_t’
/usr/include/bits/types.h:140: error: storage class specified for parameter ‘__nlink_t’
/usr/include/bits/types.h:141: error: storage class specified for parameter ‘__off_t’
/usr/include/bits/types.h:142: error: storage class specified for parameter ‘__off64_t’
/usr/include/bits/types.h:143: error: storage class specified for parameter ‘__pid_t’
/usr/include/bits/types.h:144: error: storage class specified for parameter ‘__fsid_t’
/usr/include/bits/types.h:145: error: storage class specified for parameter ‘__clock_t’
/usr/include/bits/types.h:146: error: storage class specified for parameter ‘__rlim_t’
/usr/include/bits/types.h:147: error: storage class specified for parameter ‘__rlim64_t’
/usr/include/bits/types.h:148: error: storage class specified for parameter ‘__id_t’
/usr/include/bits/types.h:149: error: storage class specified for parameter ‘__time_t’
/usr/include/bits/types.h:150: error: storage class specified for parameter ‘__useconds_t’
/usr/include/bits/types.h:151: error: storage class specified for parameter ‘__suseconds_t’
/usr/include/bits/types.h:153: error: storage class specified for parameter ‘__daddr_t’
/usr/include/bits/types.h:154: error: storage class specified for parameter ‘__swblk_t’
/usr/include/bits/types.h:155: error: storage class specified for parameter ‘__key_t’
/usr/include/bits/types.h:158: error: storage class specified for parameter ‘__clockid_t’
/usr/include/bits/types.h:161: error: storage class specified for parameter ‘__timer_t’
/usr/include/bits/types.h:164: error: storage class specified for parameter ‘__blksize_t’
/usr/include/bits/types.h:169: error: storage class specified for parameter ‘__blkcnt_t’
/usr/include/bits/types.h:170: error: storage class specified for parameter ‘__blkcnt64_t’
/usr/include/bits/types.h:173: error: storage class specified for parameter ‘__fsblkcnt_t’
/usr/include/bits/types.h:174: error: storage class specified for parameter ‘__fsblkcnt64_t’
/usr/include/bits/types.h:177: error: storage class specified for parameter ‘__fsfilcnt_t’
/usr/include/bits/types.h:178: error: storage class specified for parameter ‘__fsfilcnt64_t’
/usr/include/bits/types.h:180: error: storage class specified for parameter ‘__ssize_t’
/usr/include/bits/types.h:184: error: storage class specified for parameter ‘__off64_t’
/usr/include/bits/types.h:184: error: conflicting types for ‘__off64_t’
/usr/include/bits/types.h:142: note: previous definition of ‘__off64_t’ was here
/usr/include/bits/types.h:184: error: expected ‘;’, ‘,’ or ‘)’ before ‘__loff_t’
make: *** [dominion.o] Error 1
